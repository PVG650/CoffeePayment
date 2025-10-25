// Struktur für einen Datensatz
struct Datensatz {
  int ID;
  float saldo;
};


float selectedSaldo = 123;
int currentID = 999;  // aktuell anliegende RFID ID aus dem RFID reader

const int arraySize = 50;
int i = 0;
Datensatz database[arraySize];  // Array mit bis zu 50 structs
int aktuellerArrayPlatz = 0;    // Beginnt bei 0 und inkrementiert wenn eine unbekannte RFID ID zum ersten mal eingelesen wird. Stellt also den höchsten belegten array Platz dar

void setup() {
  Serial.begin(115200);
  delay(3000);
  database[0].ID = 111;
  database[0].saldo = 6.50;
  database[1].ID = 999;
  database[1].saldo = 7.50;
   while (i < arraySize) {
    if (database[i].ID == currentID) {
      selectedSaldo = database[i].saldo;
      Serial.print("i: ");
      Serial.println(i);
      Serial.print("saldo: ");
      Serial.println(selectedSaldo);
      i=1000; // Schleife stoppen
    }

    i = i + 1;
  }
}

void loop() {
 
}
