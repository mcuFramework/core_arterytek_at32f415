# at32f415 function pin out
***
## ADC
```
ADC1
  ADC1_IN0    - PA0
  ADC1_IN1    - PA1
  ADC1_IN2    - PA2
  ADC1_IN3    - PA3
  ADC1_IN4    - PA4
  ADC1_IN5    - PA5
  ADC1_IN6    - PA6
  ADC1_IN7    - PA7
  ADC1_IN8    - PB0
  ADC1_IN9    - PB1
  ADC1_IN10   - PC0
  ADC1_IN11   - PC1
  ADC1_IN12   - PC2
  ADC1_IN13   - PC3
  ADC1_IN14   - PC4
  ADC1_IN15   - PC5
```

## I2C
```
I2C1
  I2C1_SCL    - PB6  / PB8  / PF6
  I2C1_SDA    - PB7  / PB9  / PF7
  I2C1_SMBA   - PB5  / PB5  / PB5
  
I2C2
  I2C2_SCL    - PB10 / PA8  / PA8  / PF6
  I2C2_SDA    - PB11 / PC9  / PB4  / PF7
  I2C2_SMBA   - PB12 / PA9  / PA9  / PA9
```

## USART

```
USART1
  USART1_TX   - PA9  / PB6
  USART1_RX   - PA10 / PB7
  USART1_CK   - PA8  /
  USART1_CTS  - PA11 /
  USART1_RTS  - PA12 /
  
USART2: 
  USART2_TX   - PA2
  USART2_RX   - PA3
  USART2_CK   - PA4
  USART2_CTS  - PA0
  USART2_RTS  - PA1

USART3:
  USART3_TX   - PB10 / PA7
  USART3_RX   - PB11 / PA6 
  USART3_CK   - PB12 / PA5
  USART3_CTS  - PB13 / PB1
  USART3_RTS  - PB14 / PB0

UART4:
  UART4_TX    - PC10 / PF4
  UART4_RX    - PC11 / PF5

UART5:
  UART5_TX    - PC12
  UART5_RX    - PD2
```

***
## SPI

```
SPI1:
  SPI1_MOSI   - PA7  / PB5
  SPI1_MISO   - PA6  / PB4
  SPI1_SCK    - PA5  / PB3
  SPI1_NSS	  - PA4  / PA15

SPI2:
  SPI2_MOSI   - PB15 / PB5
  SPI2_MISO   - PB14 / PB4
  SPI2_SCK    - PB13 / PB3
  SPI2_NSS	  - PB12 / PA15

```

## TMR

```
TMR1:
  TMR1_CH1	  - PA8  / PC6
  TMR1_CH1N   - PB13 / PA7
  TMR1_CH2    - PA9  / PC7
  TMR1_CH2N   - PB14 / PB0
  TMR1_CH3    - PA10 / PC8
  TMR1_CH3N   - PB15 / PB1
  TMR1_CH4    - PA11 / PC9
  
TMR2:
  TMR1_CH1    - PA0  / PA15
  TMR1_CH2    - PA1  / PB3
  TMR1_CH3    - PA2  / PB10
  TMR1_CH4    - PA3  / PB11
  
TMR3:
  TMR3_CH1    - PA6  / PC6
  TMR3_CH2    - PA7  / PC7
  TMR3_CH3    - PB0  / PC8
  TMR3_CH4    - PB1  / PC9
  
TMR4:
  TMR4_CH1    - PB6
  TMR4_CH2    - PB7
  TMR4_CH3    - PB8
  TMR4_CH4    - PB9
  
TMR5:
  TMR5_CH1    - PA0  / PF4
  TMR5_CH2    - PA1  / PF5
  TMR5_CH3    - PA2
  TMR5_CH4    - PA3
  
TMR9:
  TMR5_CH1    - PA2  / PB14
  TMR5_CH2    - PA3  / PB15
  
TMR10:
  TMR10_CH1   - PB8  / PA6
  
TMR11:
  TMR11_CH1   - PB9  / PA7
```