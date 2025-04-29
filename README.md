# ESPStockViewer

**ESPStockViewer** zeigt in Echtzeit den aktuellen Kurs deiner gewünschten Aktien direkt auf einem 1.77" TFT-Display an.  
Das Projekt basiert auf einem ESP32-Board in Kombination mit einem ST7735-LCD und einem 4x4-Keypad zur Benutzereingabe.

## Materialien

- [ESP32 NodeMCU](https://www.amazon.de/dp/B0CR9R6334?ref_=ppx_hzsearch_conn_dt_b_fed_asin_title_2&th=1)
- [1.77" SPI TFT Display 128x160 RGB](https://www.az-delivery.de/en/products/1-77-zoll-spi-tft-display?_pos=1&_sid=30a5b0271&_ss=r)
- [4x4 Matrix Keypad](https://www.az-delivery.de/en/products/4x4-matrix-keypad?variant=8192016023648)
- Jumper-Kabel (Female-Female / Female-Male):
  - [40x Female to Male, 20 cm](https://www.az-delivery.de/en/products/40-stk-jumper-wire-female-to-male-20-zentimeter?_pos=1&_sid=7cc3825b4&_ss=r)
  - [40x Female to Female, 20 cm](https://www.az-delivery.de/en/products/40-stk-jumper-wire?_pos=1&_sid=7cc3825b4&_ss=r)



## Schaltplan: ESP32 zu ST7735 (1.77" TFT Display)

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


## Schaltplan: ESP32 zu Keypad 4x4

Das Keypad wird mit insgesamt 8 Pins angeschlossen. Die Zuordnung kann je nach Bibliothek angepasst werden. Ein Beispiel:

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

Den vollständigen Code findest du in der Datei [`ESPStockViewer.ino`](https://github.com/RiccardoDAndrea/ESPStockViewer/blob/main/ESPStockViewer.ino)


Viel Spaß beim Basteln und Programmieren!
