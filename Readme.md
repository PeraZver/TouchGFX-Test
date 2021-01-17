# TouchGFX Test

I am trying to learn how to use the graphics engine TouchGFX by STMicro. 
This is an educational project, so the purpose is only fun and learning.

## Hardware 
 * A NUCLEO-F411RE board with STM32F411RET6 (100 MHz SYSCLK)
 * A TFT-LCD with ILI9341 driver and XPT2046 touchscreen controller from [AliExpress](https://www.aliexpress.com/item/32815224002.html?spm=a2g0s.9042311.0.0.6f9d4c4dv0T4OV), with SPI (100 MHz SCK)

### Wiring

|LCD Board|Nucleo |STM32F411RE| Description       |
| ------- |:-----:| ---------:|	--------------:	  |
|VCC      |CN6-4  | -         | 3.3V              |
|GND      |CN6-6  | -         | GND	              |
|CS       |CN5-3  | PB6       | D10, Chip Select  |
|RST      |CN9-5  | PB5       | D4,  LCD Reset    |
|DC       |CN7-21 | PB7       | Data control      |
|MOSI     |CN5-4  | PA7       | D11, MOSI         |
|SCK      |CN5-6  | PA5       | D13, SCK          |
|LED      |CN7-5  | VDD       | 5V                |
|MISO     |CN5-5  | PA6       | D12, MISO         |
|T_CLK    |CN9-7  | PB10      | D6, Touch CLK     |
|T_CS     |CN10-6 | PC5       | Touch Chip Select |
|T_DIN    |CN7-37 | PC3       | Touch Data In  	  |
|T_DO     |CN7-35 | PC2       | Touch Data OUt 	  |
|T_IRQ    |CN10-24| PB1       | Touch Interrupt   |

## To-Do

 - [x] Partial framebuffer 
 - [x] Touchscreen
 - [ ] Graphs
 - [ ] FreeRTOS 

## Resources

 - [Official documentation](https://support.touchgfx.com/docs/introduction/welcome)
 - [Blog post](https://helentronica.com)

 Pero, 2021