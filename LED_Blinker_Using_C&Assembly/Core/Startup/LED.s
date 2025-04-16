
  .syntax unified
  .cpu cortex-m4
  .fpu softvfp
  .thumb


  .equ RCC_AHB2ENR,   (0x4002104C)
  .equ GPIOA_MODER,   (0x48000000)
  .equ GPIOA_ODR,    (0x48000014)
  .global LED_On
  .type  LED_On, %function
  .text
LED_On:
    PUSH {R4, LR}

    // GPIOA enabled
    LDR R4, =RCC_AHB2ENR
    LDR R0, [R4]
    ORR R0, R0, #(1 << 0)
    STR R0, [R4]

    // Configurer PA5 en mode sortie
    LDR R4, =GPIOA_MODER
    LDR R0, [R4]
    BIC R0, R0, #(0b11 << (5 * 2))
    ORR R0, R0, #(0b01 << (5 * 2))
    STR R0, [R4]

    // Allumer/éteindre la LED
    LDR R4, =GPIOA_ODR
    LDR R0, [R4]
    ORR R0, R0, #(1 << 5)
    STR R0, [R4]

    POP {R4, PC}
  .global LED_Enable
  .type  LED_Enable, %function
  .text
LED_Enable:
    PUSH {R4, LR}

    LDR R4, =RCC_AHB2ENR
    LDR R0, [R4]
    ORR R0, R0, #(1 << 0)
    STR R0, [R4]

    POP {R4, PC}
  .global LED_Configure
  .type  LED_Configure, %function
  .text
LED_Configure:
    PUSH {R4, LR}

    LDR R4, =GPIOA_MODER
    LDR R0, [R4]
    BIC R0, R0, #(0b11 << (5 * 2))
    ORR R0, R0, #(0b01 << (5 * 2))
    STR R0, [R4]

    POP {R4, PC}
.global LED_DriveGreen
.type LED_DriveGreen, %function
.text

LED_DriveGreen:
    PUSH {R4, LR}

    LDR R4, =GPIOA_ODR
    LDR R1, [R4]
    CMP R0, #0
    BEQ Turn_Off

    ORR R1, R1, #(1 << 5)
    B End

Turn_Off:
    BIC R1, R1, #(1 << 5)

End:
    STR R1, [R4]
    POP {R4, PC}









