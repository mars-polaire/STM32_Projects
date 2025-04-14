/*
 * utils.c
 *
 *  Created on: Apr 14, 2025
 *      Author: huawei
 */
#include <stm32l4xx_hal.h>
#include <stdio.h>
#include "stm32l4xx_hal.h"
#include "utils.h"
#include "main.h"
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;


// Define a structure to hold GPS data
typedef struct {
    float latitude;
    float longitude;
    char ns;
    char ew;
} GPS_Data;

#define BUFFER_SIZE 128

// Global buffer and position data
char buffer[BUFFER_SIZE];
GPS_Data position;

void setup(void) {
	 // This code will be run once

    // Initialize UART, GPIO, peripherals if necessary
    printf("System initialized. Waiting for GPS data...\n\r");
}

void loop(void) {
	 // This code will run indefinitly.
    int size = fillBuffer(buffer, BUFFER_SIZE);  // Step 1: Receive NMEA frame

    if (size < 0) {
        printf("UART Read Error!\n\r");
        return;  // Skip to the next loop iteration
    }

    // Step 2: Validate the frame using checksum and header
    if (!checkFrame(buffer)) {
        printf("Corrupted or invalid NMEA frame!\n\r");
        return;
    }

    // Step 3: Extract latitude & longitude from the frame
    position.latitude = getLatitude(buffer);
    position.longitude = getLongitude(buffer);

    // Step 4: Determine N/S and E/W based on coordinates
    position.ns = (position.latitude >= 0) ? 'N' : 'S';
    position.ew = (position.longitude >= 0) ? 'E' : 'W';

    // Step 5: Display the extracted position
    printf("\n--- GPS Position ---\n\r");
    printf("Latitude :  %.4f° %c\n\r", (position.latitude >= 0) ? position.latitude : -position.latitude, position.ns);
    printf("Longitude:  %.4f° %c\n\r", (position.longitude >= 0) ? position.longitude : -position.longitude, position.ew);
}

int fillBuffer(char *buffer, int size) {
    int total = 0;
    char received_char = 0;
    int i;

    // Initialize the buffer with zeros
    for (i = 0; i < size; i++) {
        buffer[i] = 0;
    }

    // Abort any ongoing UART reception
    HAL_UART_Abort(&huart1);

    // Wait for the start character '$'
    do {
        HAL_UART_Receive(&huart1, (uint8_t *)&received_char, 1, HAL_MAX_DELAY);
    } while (received_char != '$');

    // Store incoming characters until '\n' is received or buffer is full
    total = 0;
    while (total < size - 1) {
        buffer[total++] = received_char;

        // Receive the next character
        HAL_UART_Receive(&huart1, (uint8_t *)&received_char, 1, HAL_MAX_DELAY);

        // Stop if end-of-line is detected
        if (received_char == '\n') {
            buffer[total++] = received_char;
            break;
        }
    }

    // Null-terminate the string to prevent buffer overflows
    if (total < size)
        buffer[total] = '\0';
    else
        buffer[size - 1] = '\0';

    return total;  // Return the number of characters read (including '\n')
}
int isGPGGA(char *frame) {
    const char prefix[] = "$GPGGA";  // Expected frame header

    // Compare the first 6 characters of the frame
    for (int i = 0; i < 6; i++) {
        if (prefix[i] != frame[i]) {
            return -1;  // Prefix does not match
        }
    }
    return 1;  // Prefix matches
}
int extractChecksum(char *buffer) {
    // Search for the '*' character indicating the checksum start
    while (*buffer != '*' && *buffer != '\0') {
        buffer++;
    }

    if (*buffer == '\0') {
        return -1;  // No checksum found
    }

    char hex1 = buffer[1];
    char hex2 = buffer[2];
    int checksum = 0;

    // Convert first hex character to integer
    if (hex1 >= '0' && hex1 <= '9') checksum += (hex1 - '0') * 16;
    else if (hex1 >= 'A' && hex1 <= 'F') checksum += (hex1 - 'A' + 10) * 16;
    else if (hex1 >= 'a' && hex1 <= 'f') checksum += (hex1 - 'a' + 10) * 16;

    // Convert second hex character to integer
    if (hex2 >= '0' && hex2 <= '9') checksum += (hex2 - '0');
    else if (hex2 >= 'A' && hex2 <= 'F') checksum += (hex2 - 'A' + 10);
    else if (hex2 >= 'a' && hex2 <= 'f') checksum += (hex2 - 'a' + 10);

    return checksum;
}
int calculateChecksum(char *buffer) {
    int checksum = 0;

    // Skip the initial '$' character
    buffer++;

    // XOR all characters until '*' or end of string
    while (*buffer != '*' && *buffer != '\0') {
        checksum ^= *buffer;
        buffer++;
    }

    return checksum;
}
int checkFrame(char *buffer) {
    if (buffer == NULL) return 0;  // Null pointer check

    // Check if the frame is a GPGGA sentence
    if (isGPGGA(buffer) != 1) {
        return 0;  // Not a valid GPGGA frame
    }

    // Extract checksum from the frame
    int extracted = extractChecksum(buffer);
    int calculated = calculateChecksum(buffer);

    // Validate checksums
    if (extracted == -1) {
        return 0;  // Extraction error
    }

    return (extracted == calculated) ? 1 : 0;
}
int recherchevirg(char *frame, int i) {
    if (frame == NULL) return -1;  // Null pointer check

    // Look for the next comma in the string
    while (frame[i] != ',' && frame[i] != '\0') {
        i++;
    }

    return (frame[i] == ',') ? i : -1;  // Return comma position or -1 if not found
}
float getLatitude(char *frame) {
    if (frame == NULL) return 0.0f;

    int count = 0;
    int index = 0;

    // Locate the 2nd comma, which precedes the latitude field
    while (count < 2) {
        index = recherchevirg(frame, index);
        if (index == -1) return 0.0f;
        count++;
    }

    // Extract latitude string
    char latField[16];
    strncpy(latField, &frame[index + 1], 15);
    latField[15] = '\0';

    // Convert NMEA field to float
    float raw = atof(latField);
    int degrees = (int)(raw / 100);  // Extract degrees
    float minutes = raw - degrees * 100;  // Extract minutes
    float latitude = degrees + minutes / 60.0f;

    // Determine hemisphere (N/S)
    int directionIndex = recherchevirg(frame, index);
    if (directionIndex == -1) return 0.0f;
    char ns = frame[directionIndex + 1];

    return (ns == 'N' || ns == 'n') ? latitude : -latitude;
}
float getLongitude(char *frame) {
    if (frame == NULL) return 0.0f;

    int count = 0;
    int index = 0;

    // Locate the 4th comma, which precedes the longitude field
    while (count < 4) {
        index = recherchevirg(frame, index);
        if (index == -1) return 0.0f;
        count++;
    }

    // Extract longitude string
    char longField[16];
    strncpy(longField, &frame[index + 1], 15);
    longField[15] = '\0';

    // Convert NMEA field to float
    float raw = atof(longField);
    int degrees = (int)(raw / 100);  // Extract degrees
    float minutes = raw - degrees * 100;  // Extract minutes
    float longitude = degrees + minutes / 60.0f;

    // Determine hemisphere (E/W)
    int directionIndex = recherchevirg(frame, index);
    if (directionIndex == -1) return 0.0f;
    char ew = frame[directionIndex + 1];

    return (ew == 'E' || ew == 'e') ? longitude : -longitude;
}


