#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include <Keypad.h>

// TFT Display Pins
#define TFT_CS    5
#define TFT_RST   4
#define TFT_DC    2
Adafruit_ST7735 tft(TFT_CS, TFT_DC, TFT_RST);

// // TODO: Enter your WiFi Credentials
const char* ssid     = "SSID";
const char* password = "PASSWORD";

// API Configuration

const char* host    = "api.twelvedata.com";
const int   port    = 443;
// TODO: Enter your API KEY
const char* apikey  = "yourAPIKey"; // Change to your API Key
String      urlBase = "/price?symbol=";

// Keypad Setup
const byte ROWS = 4, COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {35, 32, 33, 25};
byte colPins[COLS] = {26, 27, 14, 12};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

WiFiClientSecure client;

// State Machine
enum Mode { WAIT, SELECT };
Mode mode = WAIT;

// TODO: Enter your prefred Stocks
const char* stockOptions[9] = {
  "AAPL","MSFT","TSLA","GOOG","AMZN","NVDA","NFLX","UBER","MCD"
}; 

// Wartet auf eine **echte** neue Taste (entprellt und flush)
char waitForValidKey() {
  char k;
  // Reste wegleeren
  do { k = keypad.getKey(); } while (k);
  // Auf echten Druck warten
  do {
    k = keypad.getKey();
    delay(10);
  } while (!k);
  return k;
}

void setup() {
  Serial.begin(115200);
  tft.initR(INITR_BLACKTAB);
  tft.setRotation(1);
  tft.setTextSize(1);
  tft.setTextColor(ST77XX_WHITE);
  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(10,10);
  tft.println("Connecting to WiFi...");
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected!");
  client.setInsecure();
  
  displayWait();
}

void loop() {
  if (mode == WAIT) {
    // Nur auf '#' prüfen, non-blocking
    char k = keypad.getKey();
    if (k == '#') {
      mode = SELECT;
      displayPrompt();
    }
  }
  else { // SELECT
    // Blockierend auf 1–9 oder '#'
    char sel = waitForValidKey();
    if (sel == '#') {
      mode = WAIT;
      displayWait();
      return;
    }
    if (sel >= '1' && sel <= '9') {
      int idx = sel - '1';
      fetchAndShow(stockOptions[idx]);
      // Nach der Anzeige sofort wieder ins WAIT zurück
      mode = WAIT;
    }
    // alle anderen ignorieren
  }
}

void displayWait() {
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.setCursor(10,10);
  tft.println("Druecke '#' zum Start");
}

void displayPrompt() {
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.setCursor(10,10);
  tft.println("Waehle Aktie:");
  tft.println("1:AAPL 2:MSFT");
  tft.println("3:TSLA 4:GOOG");
  tft.println("5:AMZN 6:NVDA");
  tft.println("7:NFLX 8:UBER");
  tft.println("9:MCD  #=Abbrechen");
}

void fetchAndShow(const char* symbol) {
  String fullURL = urlBase + symbol + "&" + apikey;
  if (!client.connect(host, port)) {
    showError("API Verb. fehlgeschl.");
    return;
  }

  client.print(
    "GET " + fullURL + " HTTP/1.1\r\n" +
    "Host: " + host + "\r\n" +
    "Connection: close\r\n\r\n"
  );

  // Header überspringen
  while (client.connected()) {
    if (client.readStringUntil('\n') == "\r") break;
  }
  String payload = client.readString();
  Serial.println(payload);

  StaticJsonDocument<128> doc;
  DeserializationError err = deserializeJson(doc, payload);
  if (err || !doc.containsKey("price")) {
    client.stop();
    showError("JSON Fehler");
    return;
  }

  float price = doc["price"].as<float>();
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.setCursor(10,10);
  tft.print(symbol);
  tft.println(" Preis:");
  tft.setTextSize(2);
  tft.setCursor(10,40);
  tft.print("$"); tft.println(price,2);
  tft.setTextSize(1);
  
  client.stop();
}

void showError(const char *msg) {
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_RED);
  tft.setCursor(10,10);
  tft.println(msg);
  tft.setTextColor(ST77XX_WHITE);
}
