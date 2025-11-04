## PINOUT
| Modul       | Signal       | GPIO    |
|-------------|--------------|---------|
| **RFID**    | CS ("SDA")   | GPIO 4  |
| **DISPLAY** | CS           | GPIO 15 |
|             | RS/DC        | GPIO 16 |
|             | RST          | GPIO 7  |
| **SD-Karte**| CS           | GPIO 5  |
|	      | VDD          | 5V!     |
| **ENCODER** | SW           | GPIO 42 |
|             | DT ("B")     | GPIO 40 |
|             | CLK ("A")    | GPIO 41 |

## SPI-Bus-Zuweisungen

### SPI für SD-Karte

| Signal | GPIO |
|--------|------|
| SCK    | 12   |
| MISO   | 13   |
| MOSI   | 11   |

### SPI für TFT & RFID

| Signal | GPIO |
|--------|------|
| SCK    | 36   |
| MISO   | 37   |
| MOSI   | 35   |

## Aufbau der Datenbank

| ID  | NAME       | SALDO   | COUNTER |
|-----|------------|---------|---------|
| 1234   | Max Mustermann | 20.50  | 3456       |

## Aufbau State Machine

stateDiagram-v2
    [*] --> S1
    S1: warten auf scan
    S1 --> S2

    S2: modus auswahl
    S2 --> S3
    S2 --> S4

    S3: bezug
    S3 --> S2

    S4: aufladen
    S4 --> S5

    S5: aufladen bestätigen
    S5 --> S2

