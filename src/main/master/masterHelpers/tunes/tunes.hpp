#ifndef TUNES_HPP
#define TUNES_HPP

#define NOTE_E7 2637
#define NOTE_G7 3136
#define NOTE_A7 3520
#define NOTE_B7 3951
#define NOTE_C7 2093
#define NOTE_D7 2349
#define NOTE_F7 2794
#define NOTE_E6 1319
#define NOTE_G6 1568
#define NOTE_A6 1760
#define NOTE_B6 1976
#define NOTE_C6 1047
#define NOTE_D6 1175
#define NOTE_F6 1397
#define NOTE_G5 784
#define NOTE_E5 659
#define NOTE_C5 523
#define NOTE_D5 587
#define NOTE_B5 988

#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047

#define NOTE_E5  659
#define NOTE_A5  880
#define NOTE_B5  988
#define NOTE_E6 1319
#define NOTE_B6 1976
#define NOTE_REST 0   


#define TONE_PIN 10

int marioMelody[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7,
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_A6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0
};

int crayFrogMelody[] = {
  NOTE_F4, NOTE_GS4, NOTE_F4, NOTE_F4, NOTE_AS4, NOTE_F4, NOTE_DS4, NOTE_F4,
  NOTE_C4, NOTE_F4, NOTE_F4, NOTE_CS4, NOTE_C4, NOTE_GS4, NOTE_F4, NOTE_C4,
  NOTE_F4, NOTE_F4, NOTE_DS4, NOTE_DS4, NOTE_C4, NOTE_G4, NOTE_F4
};

int windowsMelody[] = {
  NOTE_E6, NOTE_E6, NOTE_E5,
  NOTE_B5, NOTE_A5, NOTE_A5,
  NOTE_E6, NOTE_B6
};

int marioNoteDurations[] = {
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12
};

int crayFrogNoteDurations[] = {
  8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 8, 8,
  8, 8, 8, 8, 8, 8, 4
};


int windowsNoteDurations[] = {
  8, 16, 8,
  4, 4, 8,
  4, 2
};

void marioPlayMusic() {
  for (int thisNote = 0; thisNote < sizeof(marioMelody)/sizeof(int); thisNote++) {
    int noteDuration = 1000 / marioNoteDurations[thisNote];
    tone(TONE_PIN, marioMelody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(TONE_PIN);
  }
}

void crayFrogPlayMusic() {
  for (int thisNote = 0; thisNote < sizeof(crayFrogMelody)/sizeof(int); thisNote++) {
    int noteDuration = 1000 / crayFrogNoteDurations[thisNote];
    tone(TONE_PIN, crayFrogMelody[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(TONE_PIN);
  }
}

void windowsPlayMusic(){
const int notes = sizeof(windowsMelody) / sizeof(int);
  for (int i = 0; i < notes; i++) {
    int beatMs = 1000 / windowsNoteDurations[i];     // basic length
    if (windowsMelody[i] == NOTE_REST) {
      delay(beatMs);
    } else {
      tone(TONE_PIN, windowsMelody[i], beatMs);
      delay(beatMs * 1.3);                    // gap between notes
      noTone(TONE_PIN);
    }
  }
}

#endif
