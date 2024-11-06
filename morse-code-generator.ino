String alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

String morseAlphabet[] = {
  ".-",     // A
  "-...",   // B
  "-.-.-",  // C
  "-..",    // D
  ".",      // E
  "..-.",   // F
  "--.",    // G
  "....",   // H
  "..",     // I
  ".---",   // J
  "-.-.",   // K
  ".-..",   // L
  "--",     // M
  "-.",     // N
  "---",    // O
  ".--.",   // P
  "--.-",   // Q
  ".-.",    // R
  "...",    // S
  "-",      // T
  "..-",    // U
  "...-",   // V
  ".--",    // W
  "-..-",   // X
  "-.--",   // Y
  "--..",   // Z
  "-----",  // 0
  ".----",  // 1
  "..---",  // 2
  "...--",  // 3
  "....-",  // 4
  ".....",  // 5
  "-....",  // 6
  "--...",  // 7
  "---..",  // 8
  "----."   // 9
};

// Settings
const int unitLength = 100;
const int dashLength = unitLength * 3;
const int delayBetweenSymbol = dashLength + unitLength;
const int delayBetweenChars = dashLength;
const int delayBetweenWords = 1500;
const int buzzerFrequency = 1000;
int morseBuzzer = 7;

void setup() {
  Serial.begin(9600);
  Serial.println("Type your content");
  pinMode(morseBuzzer, OUTPUT);
}

void loop() {
  if (Serial.available()) {
    String convertable = Serial.readStringUntil('\n');
    if (!convertable.length()) {
      Serial.println("No word provided");
    } else {
      Serial.println("Entered: " + convertable);
      convertable.toUpperCase();
      for (int i = 0; i < convertable.length(); i++) {
        if (convertable[i] == ' ') {
          Serial.print("_");
          delay(delayBetweenWords);
        } else {
          int charIndex = alphabet.indexOf(convertable[i]);
          if (charIndex >= 0) {
            String morseCharCode = morseAlphabet[charIndex];
            playMorseCode(morseCharCode);
            delay(delayBetweenChars);
          }
        }
      }
      Serial.println();
    }
  }
}

void playMorseCode(String morse) {
  for (int i = 0; i < morse.length(); i++) {
    if (morse[i] == '.') {
      tone(morseBuzzer, buzzerFrequency, unitLength);
    } else {
      tone(morseBuzzer, buzzerFrequency, dashLength);
    }
    Serial.print(morse[i]);
    delay(delayBetweenSymbol);
  }
}
