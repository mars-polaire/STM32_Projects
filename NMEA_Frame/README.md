# GPS Data Acquisition

## Overview

This project enables the retrieval and decoding of GPS information from NMEA sentences. The functions for receiving, validating, and extracting data (time, latitude, longitude, etc.) are implemented in the files `utils.c` and `utils.h`.

## Features

- Reception of NMEA sentences via USART.
- Verification and extraction of GPS data.
- Display of information on the console to monitor activity.

## Project Structure

- **`utils.c` / `utils.h`**: Contain all the functions for managing and processing GPS sentences.
- **`main.c`**: Entry point of the project, handling initialization and the main loop for retrieving sentences.
