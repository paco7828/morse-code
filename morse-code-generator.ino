String alphabet = "abcdefghijklmnopqrstuvwxyz";

String morseAlphabet[] = {
  "short-long",
  "long-short-short-short",
  "long-short-long-short",
  "long-short-short",
  "short",
  "short-short-long-short",
  "long-long-short",
  "short-short-short-short",
  "short-short",
  "short-long-long-long",
  "long-short-long",
  "short-long-short-short",
  "long-long",
  "long-short",
  "long-long-long",
  "short-long-long-short",
  "long-long-short-long",
  "short-long-short",
  "short-short-short",
  "long",
  "short-short-long",
  "short-short-short-long",
  "short-long-long",
  "long-short-short-long",
  "long-short-long-long",
  "long-long-short-short"
};

int morseBuzzer = 7;

void setup() {
  Serial.begin(9600);
  Serial.println("Type your word");
  Serial.println();
  pinMode(morseBuzzer, OUTPUT);
}

void loop() {
  if (Serial.available()) {
    String convertable = Serial.readStringUntil('\n');
    if (!convertable.length()) {
      Serial.println("No word provided");
    } else {
      Serial.println("Entered: " + convertable);
      convertable.toLowerCase();
      for (int i = 0; i < convertable.length(); i++) {
        if (convertable[i] == ' ') {
          delay(700);
        } else {
          int charIndex = alphabet.indexOf(convertable[i]);
          String morseCharCode = morseAlphabet[charIndex];
          playMorseCode(morseCharCode);
          delay(300);
        }
      }
      Serial.println();
    }
  }
}

void playMorseCode(String morse) {
  int startIndex = 0;
  int endIndex = morse.indexOf("-");

  while (endIndex != -1) {
    String part = morse.substring(startIndex, endIndex);
    longOrShort(part);
    delay(100);
    startIndex = endIndex + 1;
    endIndex = morse.indexOf("-", startIndex);
  }
  String part = morse.substring(startIndex);
  longOrShort(part);
}

void longOrShort(String part) {
  part.toLowerCase();
  if (part == "short") {
    tone(morseBuzzer, 1000, 100);
    Serial.print(".");
  } else if (part == "long") {
    tone(morseBuzzer, 1000, 300);
    Serial.print("-");
  } else {
    Serial.print(" ");
  }
}