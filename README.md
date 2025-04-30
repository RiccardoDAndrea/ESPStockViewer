# ESPStockViewer

**ESPStockViewer** displays real-time stock prices of your selected companies directly on a 1.77" TFT display.  
The project is built using an ESP32 board, an ST7735 LCD screen, and a 4x4 keypad for user input.

## Materials

- [ESP32 NodeMCU](https://www.amazon.de/dp/B0CR9R6334?ref_=ppx_hzsearch_conn_dt_b_fed_asin_title_2&th=1)
- [1.77" SPI TFT Display 128x160 RGB](https://www.az-delivery.de/en/products/1-77-zoll-spi-tft-display?_pos=1&_sid=30a5b0271&_ss=r)
- [4x4 Matrix Keypad](https://www.az-delivery.de/en/products/4x4-matrix-keypad?variant=8192016023648)
- Jumper wires (Female-Female / Female-Male):
  - [40x Female to Male, 20 cm](https://www.az-delivery.de/en/products/40-stk-jumper-wire-female-to-male-20-zentimeter?_pos=1&_sid=7cc3825b4&_ss=r)
  - [40x Female to Female, 20 cm](https://www.az-delivery.de/en/products/40-stk-jumper-wire?_pos=1&_sid=7cc3825b4&_ss=r)


## Wiring Diagram: ESP32 to ST7735 (1.77" TFT Display)

| ESP32 Pin | ST7735 Pin  |
|-----------|-------------|
| GND       | GND         |
| 5V        | VCC         |
| 18        | SCK         |
| 23        | SDA (MOSI)  |
| 14        | RES (RST)   |
| 13        | RS (DC)     |
| 12        | CS          |
| 3.3V      | LEDA        |


## Wiring Diagram: ESP32 to 4x4 Keypad

The keypad uses 8 pins in total. The exact pin mapping may vary depending on the library you use. Here's an example:

| ESP32 Pin | Keypad Pin |
|-----------|------------|
| 35        | R1         |
| 32        | R2         |
| 33        | R3         |
| 25        | R4         |
| 26        | C1         |
| 27        | C2         |
| 14        | C3         |
| 12        | C4         |

## Code

You can find the complete code in the file [`ESPStockViewer.ino`](https://github.com/RiccardoDAndrea/ESPStockViewer/blob/main/ESPStockViewer.ino)


Happy building and coding!
