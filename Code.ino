#include <U8g2lib.h>

U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0);

#define BUTTON1_PIN 2
#define BUTTON2_PIN 3
#define BUZZER_PIN 8

#define HIT_LINE_X 36
#define NOTE_RADIUS 3
#define MAX_NOTES_TOTAL 128  // massimo teorico di note per tutta la canzone

#define HIT_TOLERANCE 5
#define VELOCITA 2
#define NOTE_X_spawn 64

#define WHOLE_N 8
#define DOTTED_HALF_N 6
#define HALF_N 4
#define DOTTED_QUARTER_N 3
#define QUARTER_N 2
#define EIGHTH_N 1
#define SIXTEENTH_N 0.5


struct Nota {
  byte x;
  byte y;
  byte traccia;
  byte indiceFrequenza;
  float frequenza;
  bool attiva;
  int durata;
};

const byte TRACCIA_Y[2] = { 28, 52 };

#define _R 0.00
#define _C0 16.35
#define _CS0 17.32
#define _D0 18.35
#define _DS0 19.45
#define _E0 20.60
#define _F0 21.83
#define _FS0 23.12
#define _G0 24.50
#define _GS0 25.96
#define _A0 27.50
#define _AS0 29.14
#define _B0 30.87

#define _C1 32.70
#define _CS1 34.65
#define _D1 36.71
#define _DS1 38.89
#define _E1 41.20
#define _F1 43.65
#define _FS1 46.25
#define _G1 49.00
#define _GS1 51.91
#define _A1 55.00
#define _AS1 58.27
#define _B1 61.74

#define _C2 65.41
#define _CS2 69.30
#define _D2 73.42
#define _DS2 77.78
#define _E2 82.41
#define _F2 87.31
#define _FS2 92.50
#define _G2 98.00
#define _GS2 103.83
#define _A2 110.00
#define _AS2 116.54
#define _B2 123.47

#define _C3 130.81
#define _CS3 138.59
#define _D3 146.83
#define _DS3 155.56
#define _E3 164.81
#define _F3 174.61
#define _FS3 185.00
#define _G3 196.00
#define _GS3 207.65
#define _A3 220.00
#define _AS3 233.08
#define _B3 246.94

#define _C4 261.63
#define _CS4 277.18
#define _D4 293.66
#define _DS4 311.13
#define _E4 329.63
#define _F4 349.23
#define _FS4 369.99
#define _G4 392.00
#define _GS4 415.30
#define _A4 440.00
#define _AS4 466.16
#define _B4 493.88

#define _C5 523.25
#define _CS5 554.37
#define _D5 587.33
#define _DS5 622.25
#define _E5 659.25
#define _F5 698.46
#define _FS5 739.99
#define _G5 783.99
#define _GS5 830.61
#define _A5 880.00
#define _AS5 932.33
#define _B5 987.77

#define _C6 1046.50
#define _CS6 1108.73
#define _D6 1174.66
#define _DS6 1244.51
#define _E6 1318.51
#define _F6 1396.91
#define _FS6 1479.98
#define _G6 1567.98
#define _GS6 1661.22
#define _A6 1760.00
#define _AS6 1864.66
#define _B6 1975.53

#define _C7 2093.00
#define _CS7 2217.46
#define _D7 2349.32
#define _DS7 2489.02
#define _E7 2637.02
#define _F7 2793.83
#define _FS7 2959.96
#define _G7 3135.96
#define _GS7 3322.44
#define _A7 3520.00
#define _AS7 3729.31
#define _B7 3951.07

#define _C8 4186.01
#define _CS8 4434.92
#define _D8 4698.63

const int canzone[][2] = {
  { _E5, QUARTER_N },
  { _B4, EIGHTH_N },
  { _C5, EIGHTH_N },
  { _D5, QUARTER_N },
  { _C5, EIGHTH_N },
  { _B4, EIGHTH_N },
  { _A4, QUARTER_N },
  { _A4, EIGHTH_N },
  { _C5, EIGHTH_N },
  { _E5, QUARTER_N },
  { _D5, EIGHTH_N },
  { _C5, EIGHTH_N },
  { _B4, QUARTER_N },
  { _B4, EIGHTH_N },
  { _C5, EIGHTH_N },
  { _D5, QUARTER_N },
  { _E5, QUARTER_N },
  { _C5, QUARTER_N },
  { _A4, QUARTER_N },
  { _A4, QUARTER_N },
  { _R, QUARTER_N },
  { _D5, DOTTED_QUARTER_N },
  { _F5, EIGHTH_N },
  { _A5, QUARTER_N },
  { _G5, EIGHTH_N },
  { _F5, EIGHTH_N },
  { _E5, DOTTED_QUARTER_N },
  { _C5, EIGHTH_N },
  { _E5, QUARTER_N },
  { _D5, EIGHTH_N },
  { _C5, EIGHTH_N },
  { _B4, QUARTER_N },
  { _B4, EIGHTH_N },
  { _C5, EIGHTH_N },
  { _D5, QUARTER_N },
  { _E5, QUARTER_N },
  { _C5, QUARTER_N },
  { _A4, QUARTER_N },
  { _A4, QUARTER_N },
  { _R, QUARTER_N },

  // Part 2
  { _E4, HALF_N },
  { _C4, HALF_N },
  { _D4, HALF_N },
  { _B3, HALF_N },
  { _C4, HALF_N },
  { _A3, HALF_N },
  { _GS3, HALF_N },
  { _B3, HALF_N },

  { _E4, HALF_N },
  { _C4, HALF_N },
  { _D4, HALF_N },
  { _B3, HALF_N },
  { _C4, QUARTER_N },
  { _E4, QUARTER_N },
  { _A4, QUARTER_N },
  { _A4, QUARTER_N },
  { _GS4, DOTTED_HALF_N },
  { _R, QUARTER_N }
};
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9
#define SS_PIN 10
MFRC522 mfrc522(SS_PIN, RST_PIN);

// UID carte
byte card1_uid[4] = {0x61, 0x20, 0x47, 0x05};
byte card2_uid[4] = {0xCF, 0x17, 0x89, 0xC2};

bool compareUID(byte *uid, byte *knownUID) {
  for (byte i = 0; i < 4; i++) {
    if (uid[i] != knownUID[i]) return false;
  }
  return true;
}

bool line1pressed = false;
bool line2pressed = false;
unsigned long lastCardRead = 0;
const int tapDuration = 1000; // durata pressione in ms


int punteggio = 0;
int notaCorrente = 0;
int durataNota = 0;
int nextSpawnX = 128;  // posizione iniziale di spawn note (a destra del display)
unsigned long notaInizio = 0;
unsigned long ultimaNota = 0;
unsigned long intervallo = 0;

Nota note[32];
int noteAttive = 0;  // quante sono attive ORA sullo schermo
const int lenght_canzone = sizeof(canzone) / sizeof(canzone[0]);

void rimuoviNota(int i);
Nota generaNota(int notaCorrente);
void Dysplay();
bool ciSonoNoteAttive();

void setup() {
  SPI.begin();
  mfrc522.PCD_Init();
  pinMode(BUZZER_PIN, OUTPUT);
  u8g2.begin();
  Serial.begin(9600);
}

void loop() {
  // Muove le note
  leggiRFID();  // leggere eventuale carta ogni ciclo
  for (int i = 0; i < noteAttive; i++) {
    note[i].x -= VELOCITA;

    bool hittable = abs(note[i].x - HIT_LINE_X) <= HIT_TOLERANCE;



    if (note[i].x <= 0) {
      // Nota persa
      rimuoviNota(i);
      i--;  // attenzione: perché ora l’array è stato shiftato!
      continue;
    }

    if (hittable) {
      if ((line1pressed && note[i].traccia == 0) || (line2pressed && note[i].traccia == 1)) {
        tone(BUZZER_PIN, note[i].frequenza, note[i].durata * 100);
        punteggio++;
        rimuoviNota(i);
        i--;
        continue;
      }
    }
  }

  // Generazione nuove note con distanza proporzionale alla durata
  if (notaCorrente < lenght_canzone && millis() - ultimaNota >= intervallo) {
    if (noteAttive < MAX_NOTES_TOTAL) {
      Nota nuova = generaNota(notaCorrente);
      nuova.x = 128;  // posizione iniziale a destra del display
      note[noteAttive++] = nuova;

      intervallo = canzone[notaCorrente][1] * 500;  // riduci questo moltiplicatore se le note sono troppo lente
      ultimaNota = millis();
      notaCorrente++;
    }
  }


// Fine gioco
if (notaCorrente >= lenght_canzone && !ciSonoNoteAttive()) {
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB08_tr);  // Font leggibile
    u8g2.setCursor(40, 25);
    u8g2.print("FINE");

    u8g2.setCursor(40, 54);
    u8g2.print("Points: ");
    u8g2.print(punteggio);  // Stampa il punteggio numerico
  } while (u8g2.nextPage());

  while (true);  // Blocca tutto
}


  Dysplay();
}

void Dysplay() {
  u8g2.firstPage();
  do {
    u8g2.drawBox(HIT_LINE_X, 0, 2, 64);
    for (int i = 0; i < 2; i++) {
      u8g2.drawHLine(0, TRACCIA_Y[i], 128);
    }
    for (int i = 0; i < noteAttive; i++) {
      if (note[i].attiva) {
        u8g2.drawDisc(note[i].x, note[i].y, NOTE_RADIUS);
      }
    }
  } while (u8g2.nextPage());
}
void rimuoviNota(int i) {
  for (int j = i; j < noteAttive - 1; j++) {
    note[j] = note[j + 1];  // shift a sinistra
  }
  noteAttive--;
}
Nota generaNota(int notaCorrente) {
  Nota nota;
  nota.traccia = random(0, 2);
  // nota.x = 128;  // RIMUOVI questa riga
  nota.y = TRACCIA_Y[nota.traccia];
  nota.frequenza = canzone[notaCorrente][0];
  nota.durata = canzone[notaCorrente][1];
  nota.attiva = true;
  return nota;
}

bool ciSonoNoteAttive() {
  return noteAttive > 0;
}
void leggiRFID() {
  // Reset lettura dopo durata tap
  if (millis() - lastCardRead > tapDuration) {
    line1pressed = false;
    line2pressed = false;
  }

  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) return;

  byte *uid = mfrc522.uid.uidByte;
  if (compareUID(uid, card1_uid)) {
    line1pressed = true;
    lastCardRead = millis();
    Serial.println("Carta 1 letta (linea 1)");
  }
  if (compareUID(uid, card2_uid)) {
    line2pressed = true;
    lastCardRead = millis();
    Serial.println("Carta 2 letta (linea 2)");
  }

  mfrc522.PICC_HaltA();
}
