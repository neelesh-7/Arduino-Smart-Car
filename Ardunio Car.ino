#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
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
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0

int RMotorpin1 = 12;
int RMotorpin2 = 11;
int LMotorpin1 = 3;
int LMotorpin2 = 2;
int Forward = 9;
int Backward = 10;
int Music = LED_BUILTIN;
int buzzer = 8;
int red = 4;
int green = 5;
int echoPin = 7;
int trigPin = 6;


// makes the song slower or faster
int tempo = 126;

// notes of the melody followed by the duration.
// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
// negative numbers are used to represent dotted notes,
// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
int melody[] = {

  NOTE_DS4, 8,
  NOTE_E4, -4, REST, 8, NOTE_FS4, 8, NOTE_G4, -4, REST, 8, NOTE_DS4, 8,
  NOTE_E4, -8, NOTE_FS4, 8,  NOTE_G4, -8, NOTE_C5, 8, NOTE_B4, -8, NOTE_E4, 8, NOTE_G4, -8, NOTE_B4, 8,
  NOTE_AS4, 2, NOTE_A4, -16, NOTE_G4, -16, NOTE_E4, -16, NOTE_D4, -16,
  NOTE_E4, 2, REST, 4, REST, 8, NOTE_DS4, 4,

  NOTE_E4, -4, REST, 8, NOTE_FS4, 8, NOTE_G4, -4, REST, 8, NOTE_DS4, 8,
  NOTE_E4, -8, NOTE_FS4, 8,  NOTE_G4, -8, NOTE_C5, 8, NOTE_B4, -8, NOTE_G4, 8, NOTE_B4, -8, NOTE_E5, 8,
  NOTE_D5, 2, REST, 4, REST, 8, NOTE_DS4, 8,
  NOTE_E4, -4, REST, 8, NOTE_FS4, 8, NOTE_G4, -4, REST, 8, NOTE_DS4, 8,
  NOTE_E4, -8, NOTE_FS4, 8,  NOTE_G4, -8, NOTE_C5, 8, NOTE_B4, -8, NOTE_E4, 8, NOTE_G4, -8, NOTE_B4, 8,

  NOTE_AS4, 2, NOTE_A4, -16, NOTE_G4, -16, NOTE_E4, -16, NOTE_D4, -16,
  NOTE_E4, -4, REST, 4,
  REST, 4, NOTE_E5, -8, NOTE_D5, 8, NOTE_B4, -8, NOTE_A4, 8, NOTE_G4, -8, NOTE_E4, -8,
  NOTE_AS4, 16, NOTE_A4, -8, NOTE_AS4, 16, NOTE_A4, -8, NOTE_AS4, 16, NOTE_A4, -8, NOTE_AS4, 16, NOTE_A4, -8,
  NOTE_G4, -16, NOTE_E4, -16, NOTE_D4, -16, NOTE_E4, 16, NOTE_E4, 16, NOTE_E4, 2,

};

// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
// there are two values per note (pitch and duration), so for each note there are four bytes
int notes = sizeof(melody) / sizeof(melody[0]) / 2;

// this calculates the duration of a whole note in ms
int wholenote = (60000 * 4) / tempo;

int divider = 0, noteDuration = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(RMotorpin1, OUTPUT);
  pinMode(RMotorpin2, OUTPUT);
  pinMode(LMotorpin1, OUTPUT);
  pinMode(LMotorpin2, OUTPUT);
  pinMode(Forward, OUTPUT);
  pinMode(Backward, OUTPUT);
  pinMode(Music, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
}

void loop() {
  //Stop
  digitalWrite(RMotorpin1, LOW);
  digitalWrite(LMotorpin1, LOW);
  digitalWrite(RMotorpin2, LOW);
  digitalWrite(LMotorpin2, LOW);

  digitalWrite(green, LOW);
  digitalWrite(red, HIGH);

  //Ultrasonic Configuration
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;

  if (distance < 30) {
    digitalWrite(red, HIGH);
    digitalWrite(green, HIGH);

    //Stop
    digitalWrite(RMotorpin1, LOW);
    digitalWrite(LMotorpin1, LOW);
    digitalWrite(RMotorpin2, LOW);
    digitalWrite(LMotorpin2, LOW);
    delay(1000);

    //Reverse
    digitalWrite(LMotorpin1, HIGH);  // Left Motor moves Backwards
    digitalWrite(LMotorpin2, LOW);
    digitalWrite(RMotorpin1, HIGH);  // Right Motor moves Backwards
    digitalWrite(RMotorpin2, LOW);
    delay(5000);

    //Turn_Right
    digitalWrite(LMotorpin1, HIGH);  // Left Motor moves One way
    digitalWrite(LMotorpin2, LOW);

    digitalWrite(RMotorpin1, LOW);   // Right Motor moves the Other way
    digitalWrite(RMotorpin2, HIGH);

    delay(800);                   // The value  800 is to get perfect 180 degree Right Turn

    //Stop
    digitalWrite(RMotorpin1, LOW);
    digitalWrite(LMotorpin1, LOW);
    digitalWrite(RMotorpin2, LOW);
    digitalWrite(LMotorpin2, LOW);
    delay(1000);
  }
  //Ultrasonic Configuration
  if (distance >= 200 || distance <= 0) {
    Serial.println("Out of range");
  }
  else {
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay(100);

  while (digitalRead(Music) == HIGH) {      //When the music button is pressed:
    //Stop
    digitalWrite(RMotorpin1, LOW);
    digitalWrite(LMotorpin1, LOW);
    digitalWrite(RMotorpin2, LOW);
    digitalWrite(LMotorpin2, LOW);
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
    for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

      // calculates the duration of each note
      divider = melody[thisNote + 1];
      if (divider > 0) {
        // regular note, just proceed
        noteDuration = (wholenote) / divider;
      } else if (divider < 0) {
        // dotted notes are represented with negative durations
        noteDuration = (wholenote) / abs(divider);
        noteDuration *= 1.5; // increases the duration in half for dotted notes
      }

      // playing the note for 90% of the duration, leaving 10% as a pause
      tone(buzzer, melody[thisNote], noteDuration * 0.9);

      // Wait for the specific duration before playing the next note.
      delay(noteDuration);

      // stop the waveform generation before the next note.
      noTone(buzzer);
    }
  }

  while (digitalRead(Forward) == HIGH) {
    digitalWrite(green, HIGH);
    digitalWrite(red, LOW);

    //Move_Forward
    digitalWrite(LMotorpin1, LOW); // Left Motor moves Forward
    digitalWrite(LMotorpin2, HIGH);

    digitalWrite(RMotorpin1, LOW); // Right Motor moves Forward
    digitalWrite(RMotorpin2, HIGH);

    delay(500);

    //Ultrasonic Configuration
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); // Added this line
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) / 29.1;

    if (distance < 30) {
      digitalWrite(red, HIGH);
      digitalWrite(green, HIGH);

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);

      //Reverse
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves Backwards
      digitalWrite(LMotorpin2, LOW);
      digitalWrite(RMotorpin1, HIGH);  // Right Motor moves Backwards
      digitalWrite(RMotorpin2, LOW);
      delay(5000);

      //Turn_Right
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves One way
      digitalWrite(LMotorpin2, LOW);

      digitalWrite(RMotorpin1, LOW);   // Right Motor moves the Other way
      digitalWrite(RMotorpin2, HIGH);

      delay(800);                   // The value  800 is to get perfect 180 degree Right Turn

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);
    }
    //Ultrasonic Configuration
    if (distance >= 200 || distance <= 0) {
      Serial.println("Out of range");
    }
    else {
      Serial.print(distance);
      Serial.println(" cm");
    }

    while (digitalRead(Music) == HIGH) {      //When the music button is pressed:
      //Stop
    digitalWrite(RMotorpin1, LOW);
    digitalWrite(LMotorpin1, LOW);
    digitalWrite(RMotorpin2, LOW);
    digitalWrite(LMotorpin2, LOW);
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
      for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

        // calculates the duration of each note
        divider = melody[thisNote + 1];
        if (divider > 0) {
          // regular note, just proceed
          noteDuration = (wholenote) / divider;
        } else if (divider < 0) {
          // dotted notes are represented with negative durations
          noteDuration = (wholenote) / abs(divider);
          noteDuration *= 1.5; // increases the duration in half for dotted notes
        }

        // playing the note for 90% of the duration, leaving 10% as a pause
        tone(buzzer, melody[thisNote], noteDuration * 0.9);

        // Wait for the specific duration before playing the next note.
        delay(noteDuration);

        // stop the waveform generation before the next note.
        noTone(buzzer);
      }
    }

    delay(500);


    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); // Added this line
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) / 29.1;

    if (distance < 30) {
      digitalWrite(red, HIGH);
      digitalWrite(green, HIGH);

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);

      //Reverse
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves Backwards
      digitalWrite(LMotorpin2, LOW);
      digitalWrite(RMotorpin1, HIGH);  // Right Motor moves Backwards
      digitalWrite(RMotorpin2, LOW);
      delay(5000);

      //Turn_Right
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves One way
      digitalWrite(LMotorpin2, LOW);

      digitalWrite(RMotorpin1, LOW);   // Right Motor moves the Other way
      digitalWrite(RMotorpin2, HIGH);

      delay(800);                   // The value  800 is to get perfect 180 degree Right Turn

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);
    }
    //Ultrasonic Configuration
    if (distance >= 200 || distance <= 0) {
      Serial.println("Out of range");
    }
    else {
      Serial.print(distance);
      Serial.println(" cm");
    }

    while (digitalRead(Music) == HIGH) {      //When the music button is pressed:
      //Stop
    digitalWrite(RMotorpin1, LOW);
    digitalWrite(LMotorpin1, LOW);
    digitalWrite(RMotorpin2, LOW);
    digitalWrite(LMotorpin2, LOW);
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
      for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

        // calculates the duration of each note
        divider = melody[thisNote + 1];
        if (divider > 0) {
          // regular note, just proceed
          noteDuration = (wholenote) / divider;
        } else if (divider < 0) {
          // dotted notes are represented with negative durations
          noteDuration = (wholenote) / abs(divider);
          noteDuration *= 1.5; // increases the duration in half for dotted notes
        }

        // playing the note for 90% of the duration, leaving 10% as a pause
        tone(buzzer, melody[thisNote], noteDuration * 0.9);

        // Wait for the specific duration before playing the next note.
        delay(noteDuration);

        // stop the waveform generation before the next note.
        noTone(buzzer);
      }
    }

    delay(500);


    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); // Added this line
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) / 29.1;

    if (distance < 30) {
      digitalWrite(red, HIGH);
      digitalWrite(green, HIGH);

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);

      //Reverse
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves Backwards
      digitalWrite(LMotorpin2, LOW);
      digitalWrite(RMotorpin1, HIGH);  // Right Motor moves Backwards
      digitalWrite(RMotorpin2, LOW);
      delay(5000);

      //Turn_Right
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves One way
      digitalWrite(LMotorpin2, LOW);

      digitalWrite(RMotorpin1, LOW);   // Right Motor moves the Other way
      digitalWrite(RMotorpin2, HIGH);

      delay(800);                   // The value  800 is to get perfect 180 degree Right Turn

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);
    }
    //Ultrasonic Configuration
    if (distance >= 200 || distance <= 0) {
      Serial.println("Out of range");
    }
    else {
      Serial.print(distance);
      Serial.println(" cm");
    }

    while (digitalRead(Music) == HIGH) {      //When the music button is pressed:
      //Stop
    digitalWrite(RMotorpin1, LOW);
    digitalWrite(LMotorpin1, LOW);
    digitalWrite(RMotorpin2, LOW);
    digitalWrite(LMotorpin2, LOW);
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
      for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

        // calculates the duration of each note
        divider = melody[thisNote + 1];
        if (divider > 0) {
          // regular note, just proceed
          noteDuration = (wholenote) / divider;
        } else if (divider < 0) {
          // dotted notes are represented with negative durations
          noteDuration = (wholenote) / abs(divider);
          noteDuration *= 1.5; // increases the duration in half for dotted notes
        }

        // playing the note for 90% of the duration, leaving 10% as a pause
        tone(buzzer, melody[thisNote], noteDuration * 0.9);

        // Wait for the specific duration before playing the next note.
        delay(noteDuration);

        // stop the waveform generation before the next note.
        noTone(buzzer);
      }
    }

    delay(500);

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); // Added this line
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) / 29.1;

    if (distance < 30) {
      digitalWrite(red, HIGH);
      digitalWrite(green, HIGH);

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);

      //Reverse
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves Backwards
      digitalWrite(LMotorpin2, LOW);
      digitalWrite(RMotorpin1, HIGH);  // Right Motor moves Backwards
      digitalWrite(RMotorpin2, LOW);
      delay(5000);

      //Turn_Right
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves One way
      digitalWrite(LMotorpin2, LOW);

      digitalWrite(RMotorpin1, LOW);   // Right Motor moves the Other way
      digitalWrite(RMotorpin2, HIGH);

      delay(800);                   // The value  800 is to get perfect 180 degree Right Turn

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);
    }
    //Ultrasonic Configuration
    if (distance >= 200 || distance <= 0) {
      Serial.println("Out of range");
    }
    else {
      Serial.print(distance);
      Serial.println(" cm");
    }

    while (digitalRead(Music) == HIGH) {      //When the music button is pressed:
      //Stop
    digitalWrite(RMotorpin1, LOW);
    digitalWrite(LMotorpin1, LOW);
    digitalWrite(RMotorpin2, LOW);
    digitalWrite(LMotorpin2, LOW);
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
      for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

        // calculates the duration of each note
        divider = melody[thisNote + 1];
        if (divider > 0) {
          // regular note, just proceed
          noteDuration = (wholenote) / divider;
        } else if (divider < 0) {
          // dotted notes are represented with negative durations
          noteDuration = (wholenote) / abs(divider);
          noteDuration *= 1.5; // increases the duration in half for dotted notes
        }

        // playing the note for 90% of the duration, leaving 10% as a pause
        tone(buzzer, melody[thisNote], noteDuration * 0.9);

        // Wait for the specific duration before playing the next note.
        delay(noteDuration);

        // stop the waveform generation before the next note.
        noTone(buzzer);
      }
    }

    delay(500);


    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); // Added this line
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) / 29.1;

    if (distance < 30) {
      digitalWrite(red, HIGH);
      digitalWrite(green, HIGH);

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);

      //Reverse
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves Backwards
      digitalWrite(LMotorpin2, LOW);
      digitalWrite(RMotorpin1, HIGH);  // Right Motor moves Backwards
      digitalWrite(RMotorpin2, LOW);
      delay(5000);

      //Turn_Right
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves One way
      digitalWrite(LMotorpin2, LOW);

      digitalWrite(RMotorpin1, LOW);   // Right Motor moves the Other way
      digitalWrite(RMotorpin2, HIGH);

      delay(800);                   // The value  800 is to get perfect 180 degree Right Turn

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);
    }
    //Ultrasonic Configuration
    if (distance >= 200 || distance <= 0) {
      Serial.println("Out of range");
    }
    else {
      Serial.print(distance);
      Serial.println(" cm");
    }

    while (digitalRead(Music) == HIGH) {      //When the music button is pressed:
      //Stop
    digitalWrite(RMotorpin1, LOW);
    digitalWrite(LMotorpin1, LOW);
    digitalWrite(RMotorpin2, LOW);
    digitalWrite(LMotorpin2, LOW);
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
      for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

        // calculates the duration of each note
        divider = melody[thisNote + 1];
        if (divider > 0) {
          // regular note, just proceed
          noteDuration = (wholenote) / divider;
        } else if (divider < 0) {
          // dotted notes are represented with negative durations
          noteDuration = (wholenote) / abs(divider);
          noteDuration *= 1.5; // increases the duration in half for dotted notes
        }

        // playing the note for 90% of the duration, leaving 10% as a pause
        tone(buzzer, melody[thisNote], noteDuration * 0.9);

        // Wait for the specific duration before playing the next note.
        delay(noteDuration);

        // stop the waveform generation before the next note.
        noTone(buzzer);
      }
    }

    delay(500);


    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); // Added this line
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) / 29.1;

    if (distance < 30) {
      digitalWrite(red, HIGH);
      digitalWrite(green, HIGH);

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);

      //Reverse
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves Backwards
      digitalWrite(LMotorpin2, LOW);
      digitalWrite(RMotorpin1, HIGH);  // Right Motor moves Backwards
      digitalWrite(RMotorpin2, LOW);
      delay(5000);

      //Turn_Right
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves One way
      digitalWrite(LMotorpin2, LOW);

      digitalWrite(RMotorpin1, LOW);   // Right Motor moves the Other way
      digitalWrite(RMotorpin2, HIGH);

      delay(800);                   // The value  800 is to get perfect 180 degree Right Turn

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);
    }
    //Ultrasonic Configuration
    if (distance >= 200 || distance <= 0) {
      Serial.println("Out of range");
    }
    else {
      Serial.print(distance);
      Serial.println(" cm");
    }

    while (digitalRead(Music) == HIGH) {      //When the music button is pressed:
      //Stop
    digitalWrite(RMotorpin1, LOW);
    digitalWrite(LMotorpin1, LOW);
    digitalWrite(RMotorpin2, LOW);
    digitalWrite(LMotorpin2, LOW);
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
      for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

        // calculates the duration of each note
        divider = melody[thisNote + 1];
        if (divider > 0) {
          // regular note, just proceed
          noteDuration = (wholenote) / divider;
        } else if (divider < 0) {
          // dotted notes are represented with negative durations
          noteDuration = (wholenote) / abs(divider);
          noteDuration *= 1.5; // increases the duration in half for dotted notes
        }

        // playing the note for 90% of the duration, leaving 10% as a pause
        tone(buzzer, melody[thisNote], noteDuration * 0.9);

        // Wait for the specific duration before playing the next note.
        delay(noteDuration);

        // stop the waveform generation before the next note.
        noTone(buzzer);
      }
    }

    delay(500);


    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); // Added this line
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) / 29.1;

    if (distance < 30) {
      digitalWrite(red, HIGH);
      digitalWrite(green, HIGH);

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);

      //Reverse
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves Backwards
      digitalWrite(LMotorpin2, LOW);
      digitalWrite(RMotorpin1, HIGH);  // Right Motor moves Backwards
      digitalWrite(RMotorpin2, LOW);
      delay(5000);

      //Turn_Right
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves One way
      digitalWrite(LMotorpin2, LOW);

      digitalWrite(RMotorpin1, LOW);   // Right Motor moves the Other way
      digitalWrite(RMotorpin2, HIGH);

      delay(800);                   // The value  800 is to get perfect 180 degree Right Turn

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);
    }
    //Ultrasonic Configuration
    if (distance >= 200 || distance <= 0) {
      Serial.println("Out of range");
    }
    else {
      Serial.print(distance);
      Serial.println(" cm");
    }

    while (digitalRead(Music) == HIGH) {      //When the music button is pressed:
      //Stop
    digitalWrite(RMotorpin1, LOW);
    digitalWrite(LMotorpin1, LOW);
    digitalWrite(RMotorpin2, LOW);
    digitalWrite(LMotorpin2, LOW);
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
      for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

        // calculates the duration of each note
        divider = melody[thisNote + 1];
        if (divider > 0) {
          // regular note, just proceed
          noteDuration = (wholenote) / divider;
        } else if (divider < 0) {
          // dotted notes are represented with negative durations
          noteDuration = (wholenote) / abs(divider);
          noteDuration *= 1.5; // increases the duration in half for dotted notes
        }

        // playing the note for 90% of the duration, leaving 10% as a pause
        tone(buzzer, melody[thisNote], noteDuration * 0.9);

        // Wait for the specific duration before playing the next note.
        delay(noteDuration);

        // stop the waveform generation before the next note.
        noTone(buzzer);
      }
    }

    delay(500);


    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); // Added this line
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) / 29.1;

    if (distance < 30) {
      digitalWrite(red, HIGH);
      digitalWrite(green, HIGH);

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);

      //Reverse
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves Backwards
      digitalWrite(LMotorpin2, LOW);
      digitalWrite(RMotorpin1, HIGH);  // Right Motor moves Backwards
      digitalWrite(RMotorpin2, LOW);
      delay(5000);

      //Turn_Right
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves One way
      digitalWrite(LMotorpin2, LOW);

      digitalWrite(RMotorpin1, LOW);   // Right Motor moves the Other way
      digitalWrite(RMotorpin2, HIGH);

      delay(800);                   // The value  800 is to get perfect 180 degree Right Turn

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);
    }
    //Ultrasonic Configuration
    if (distance >= 200 || distance <= 0) {
      Serial.println("Out of range");
    }
    else {
      Serial.print(distance);
      Serial.println(" cm");
    }

    while (digitalRead(Music) == HIGH) {      //When the music button is pressed:
      //Stop
    digitalWrite(RMotorpin1, LOW);
    digitalWrite(LMotorpin1, LOW);
    digitalWrite(RMotorpin2, LOW);
    digitalWrite(LMotorpin2, LOW);
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
      for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

        // calculates the duration of each note
        divider = melody[thisNote + 1];
        if (divider > 0) {
          // regular note, just proceed
          noteDuration = (wholenote) / divider;
        } else if (divider < 0) {
          // dotted notes are represented with negative durations
          noteDuration = (wholenote) / abs(divider);
          noteDuration *= 1.5; // increases the duration in half for dotted notes
        }

        // playing the note for 90% of the duration, leaving 10% as a pause
        tone(buzzer, melody[thisNote], noteDuration * 0.9);

        // Wait for the specific duration before playing the next note.
        delay(noteDuration);

        // stop the waveform generation before the next note.
        noTone(buzzer);
      }
    }

    delay(500);


    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); // Added this line
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) / 29.1;

    if (distance < 30) {
      digitalWrite(red, HIGH);
      digitalWrite(green, HIGH);

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);

      //Reverse
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves Backwards
      digitalWrite(LMotorpin2, LOW);
      digitalWrite(RMotorpin1, HIGH);  // Right Motor moves Backwards
      digitalWrite(RMotorpin2, LOW);
      delay(5000);

      //Turn_Right
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves One way
      digitalWrite(LMotorpin2, LOW);

      digitalWrite(RMotorpin1, LOW);   // Right Motor moves the Other way
      digitalWrite(RMotorpin2, HIGH);

      delay(800);                   // The value  800 is to get perfect 180 degree Right Turn

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);
    }
    //Ultrasonic Configuration
    if (distance >= 200 || distance <= 0) {
      Serial.println("Out of range");
    }
    else {
      Serial.print(distance);
      Serial.println(" cm");
    }

    while (digitalRead(Music) == HIGH) {      //When the music button is pressed:
      //Stop
    digitalWrite(RMotorpin1, LOW);
    digitalWrite(LMotorpin1, LOW);
    digitalWrite(RMotorpin2, LOW);
    digitalWrite(LMotorpin2, LOW);
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
      for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

        // calculates the duration of each note
        divider = melody[thisNote + 1];
        if (divider > 0) {
          // regular note, just proceed
          noteDuration = (wholenote) / divider;
        } else if (divider < 0) {
          // dotted notes are represented with negative durations
          noteDuration = (wholenote) / abs(divider);
          noteDuration *= 1.5; // increases the duration in half for dotted notes
        }

        // playing the note for 90% of the duration, leaving 10% as a pause
        tone(buzzer, melody[thisNote], noteDuration * 0.9);

        // Wait for the specific duration before playing the next note.
        delay(noteDuration);

        // stop the waveform generation before the next note.
        noTone(buzzer);
      }
    }

    delay(500);

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); // Added this line
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) / 29.1;

    if (distance < 30) {
      digitalWrite(red, HIGH);
      digitalWrite(green, HIGH);

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);

      //Reverse
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves Backwards
      digitalWrite(LMotorpin2, LOW);
      digitalWrite(RMotorpin1, HIGH);  // Right Motor moves Backwards
      digitalWrite(RMotorpin2, LOW);
      delay(5000);

      //Turn_Right
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves One way
      digitalWrite(LMotorpin2, LOW);

      digitalWrite(RMotorpin1, LOW);   // Right Motor moves the Other way
      digitalWrite(RMotorpin2, HIGH);

      delay(800);                   // The value  800 is to get perfect 180 degree Right Turn

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);
    }
    //Ultrasonic Configuration
    if (distance >= 200 || distance <= 0) {
      Serial.println("Out of range");
    }
    else {
      Serial.print(distance);
      Serial.println(" cm");
    }

    while (digitalRead(Music) == HIGH) {      //When the music button is pressed:
      //Stop
    digitalWrite(RMotorpin1, LOW);
    digitalWrite(LMotorpin1, LOW);
    digitalWrite(RMotorpin2, LOW);
    digitalWrite(LMotorpin2, LOW);
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
      for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

        // calculates the duration of each note
        divider = melody[thisNote + 1];
        if (divider > 0) {
          // regular note, just proceed
          noteDuration = (wholenote) / divider;
        } else if (divider < 0) {
          // dotted notes are represented with negative durations
          noteDuration = (wholenote) / abs(divider);
          noteDuration *= 1.5; // increases the duration in half for dotted notes
        }

        // playing the note for 90% of the duration, leaving 10% as a pause
        tone(buzzer, melody[thisNote], noteDuration * 0.9);

        // Wait for the specific duration before playing the next note.
        delay(noteDuration);

        // stop the waveform generation before the next note.
        noTone(buzzer);
      }
    }

    //Turn_Left
    digitalWrite(LMotorpin1, LOW);  // Left Motor moves One way
    digitalWrite(LMotorpin2, HIGH);

    digitalWrite(RMotorpin1, HIGH); // Right Motor moves the Other way
    digitalWrite(RMotorpin2, LOW);

    delay(400);                   // The value 800 is to get perfect 180 Turn

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); // Added this line
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) / 29.1;

    if (distance < 30) {
      digitalWrite(red, HIGH);
      digitalWrite(green, HIGH);

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);

      //Reverse
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves Backwards
      digitalWrite(LMotorpin2, LOW);
      digitalWrite(RMotorpin1, HIGH);  // Right Motor moves Backwards
      digitalWrite(RMotorpin2, LOW);
      delay(5000);

      //Turn_Right
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves One way
      digitalWrite(LMotorpin2, LOW);

      digitalWrite(RMotorpin1, LOW);   // Right Motor moves the Other way
      digitalWrite(RMotorpin2, HIGH);

      delay(800);                   // The value  800 is to get perfect 180 degree Right Turn

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);
    }
    //Ultrasonic Configuration
    if (distance >= 200 || distance <= 0) {
      Serial.println("Out of range");
    }
    else {
      Serial.print(distance);
      Serial.println(" cm");
    }

    while (digitalRead(Music) == HIGH) {      //When the music button is pressed:
      //Stop
    digitalWrite(RMotorpin1, LOW);
    digitalWrite(LMotorpin1, LOW);
    digitalWrite(RMotorpin2, LOW);
    digitalWrite(LMotorpin2, LOW);
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
      for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

        // calculates the duration of each note
        divider = melody[thisNote + 1];
        if (divider > 0) {
          // regular note, just proceed
          noteDuration = (wholenote) / divider;
        } else if (divider < 0) {
          // dotted notes are represented with negative durations
          noteDuration = (wholenote) / abs(divider);
          noteDuration *= 1.5; // increases the duration in half for dotted notes
        }

        // playing the note for 90% of the duration, leaving 10% as a pause
        tone(buzzer, melody[thisNote], noteDuration * 0.9);

        // Wait for the specific duration before playing the next note.
        delay(noteDuration);

        // stop the waveform generation before the next note.
        noTone(buzzer);
      }
    }

    delay(400);

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); // Added this line
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) / 29.1;

    if (distance < 30) {
      digitalWrite(red, HIGH);
      digitalWrite(green, HIGH);

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);

      //Reverse
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves Backwards
      digitalWrite(LMotorpin2, LOW);
      digitalWrite(RMotorpin1, HIGH);  // Right Motor moves Backwards
      digitalWrite(RMotorpin2, LOW);
      delay(5000);

      //Turn_Right
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves One way
      digitalWrite(LMotorpin2, LOW);

      digitalWrite(RMotorpin1, LOW);   // Right Motor moves the Other way
      digitalWrite(RMotorpin2, HIGH);

      delay(800);                   // The value  800 is to get perfect 180 degree Right Turn

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);
    }
    //Ultrasonic Configuration
    if (distance >= 200 || distance <= 0) {
      Serial.println("Out of range");
    }
    else {
      Serial.print(distance);
      Serial.println(" cm");
    }

    while (digitalRead(Music) == HIGH) {      //When the music button is pressed:
      //Stop
    digitalWrite(RMotorpin1, LOW);
    digitalWrite(LMotorpin1, LOW);
    digitalWrite(RMotorpin2, LOW);
    digitalWrite(LMotorpin2, LOW);
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
      for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

        // calculates the duration of each note
        divider = melody[thisNote + 1];
        if (divider > 0) {
          // regular note, just proceed
          noteDuration = (wholenote) / divider;
        } else if (divider < 0) {
          // dotted notes are represented with negative durations
          noteDuration = (wholenote) / abs(divider);
          noteDuration *= 1.5; // increases the duration in half for dotted notes
        }

        // playing the note for 90% of the duration, leaving 10% as a pause
        tone(buzzer, melody[thisNote], noteDuration * 0.9);

        // Wait for the specific duration before playing the next note.
        delay(noteDuration);

        // stop the waveform generation before the next note.
        noTone(buzzer);
      }
    }

    //zigzag_Forward
    for (int f = 0; f < 4; f++)     // this moves car forward in zig zag for 4 steps
    {
      digitalWrite(LMotorpin1, LOW); // Left Motor moves Forward
      digitalWrite(LMotorpin2, HIGH);
      digitalWrite(RMotorpin1, LOW); // Right Motor does not move
      digitalWrite(RMotorpin2, LOW);

      delay(500);                   // time to shorten or increase the stride

      digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); // Added this line
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) / 29.1;

    if (distance < 30) {
      digitalWrite(red, HIGH);
      digitalWrite(green, HIGH);

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);

      //Reverse
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves Backwards
      digitalWrite(LMotorpin2, LOW);
      digitalWrite(RMotorpin1, HIGH);  // Right Motor moves Backwards
      digitalWrite(RMotorpin2, LOW);
      delay(5000);

      //Turn_Right
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves One way
      digitalWrite(LMotorpin2, LOW);

      digitalWrite(RMotorpin1, LOW);   // Right Motor moves the Other way
      digitalWrite(RMotorpin2, HIGH);

      delay(800);                   // The value  800 is to get perfect 180 degree Right Turn

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);
    }
    //Ultrasonic Configuration
    if (distance >= 200 || distance <= 0) {
      Serial.println("Out of range");
    }
    else {
      Serial.print(distance);
      Serial.println(" cm");
    }

    while (digitalRead(Music) == HIGH) {      //When the music button is pressed:
      //Stop
    digitalWrite(RMotorpin1, LOW);
    digitalWrite(LMotorpin1, LOW);
    digitalWrite(RMotorpin2, LOW);
    digitalWrite(LMotorpin2, LOW);
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
      for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

        // calculates the duration of each note
        divider = melody[thisNote + 1];
        if (divider > 0) {
          // regular note, just proceed
          noteDuration = (wholenote) / divider;
        } else if (divider < 0) {
          // dotted notes are represented with negative durations
          noteDuration = (wholenote) / abs(divider);
          noteDuration *= 1.5; // increases the duration in half for dotted notes
        }

        // playing the note for 90% of the duration, leaving 10% as a pause
        tone(buzzer, melody[thisNote], noteDuration * 0.9);

        // Wait for the specific duration before playing the next note.
        delay(noteDuration);

        // stop the waveform generation before the next note.
        noTone(buzzer);
      }
    }

      delay(500);

      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10); // Added this line
      digitalWrite(trigPin, LOW);
      duration = pulseIn(echoPin, HIGH);
      distance = (duration / 2) / 29.1;

      if (distance < 30) {
        digitalWrite(red, HIGH);
        digitalWrite(green, HIGH);

        //Stop
        digitalWrite(RMotorpin1, LOW);
        digitalWrite(LMotorpin1, LOW);
        digitalWrite(RMotorpin2, LOW);
        digitalWrite(LMotorpin2, LOW);
        delay(1000);

        //Reverse
        digitalWrite(LMotorpin1, HIGH);  // Left Motor moves Backwards
        digitalWrite(LMotorpin2, LOW);
        digitalWrite(RMotorpin1, HIGH);  // Right Motor moves Backwards
        digitalWrite(RMotorpin2, LOW);
        delay(5000);

        //Turn_Right
        digitalWrite(LMotorpin1, HIGH);  // Left Motor moves One way
        digitalWrite(LMotorpin2, LOW);

        digitalWrite(RMotorpin1, LOW);   // Right Motor moves the Other way
        digitalWrite(RMotorpin2, HIGH);

        delay(800);                   // The value  800 is to get perfect 180 degree Right Turn

        //Stop
        digitalWrite(RMotorpin1, LOW);
        digitalWrite(LMotorpin1, LOW);
        digitalWrite(RMotorpin2, LOW);
        digitalWrite(LMotorpin2, LOW);
        delay(1000);
      }
      //Ultrasonic Configuration
      if (distance >= 200 || distance <= 0) {
        Serial.println("Out of range");
      }
      else {
        Serial.print(distance);
        Serial.println(" cm");
      }

      while (digitalRead(Music) == HIGH) {      //When the music button is pressed:
        //Stop
    digitalWrite(RMotorpin1, LOW);
    digitalWrite(LMotorpin1, LOW);
    digitalWrite(RMotorpin2, LOW);
    digitalWrite(LMotorpin2, LOW);
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
        for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

          // calculates the duration of each note
          divider = melody[thisNote + 1];
          if (divider > 0) {
            // regular note, just proceed
            noteDuration = (wholenote) / divider;
          } else if (divider < 0) {
            // dotted notes are represented with negative durations
            noteDuration = (wholenote) / abs(divider);
            noteDuration *= 1.5; // increases the duration in half for dotted notes
          }

          // playing the note for 90% of the duration, leaving 10% as a pause
          tone(buzzer, melody[thisNote], noteDuration * 0.9);

          // Wait for the specific duration before playing the next note.
          delay(noteDuration);

          // stop the waveform generation before the next note.
          noTone(buzzer);
        }
      }

      digitalWrite(RMotorpin1, LOW); // Right Motor moves Forward
      digitalWrite(RMotorpin2, HIGH);
      digitalWrite(LMotorpin1, LOW); // Left Motor does not move
      digitalWrite(LMotorpin2, LOW);

      delay(500);                   // time to shorten or increase the stride

      digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); // Added this line
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) / 29.1;

    if (distance < 30) {
      digitalWrite(red, HIGH);
      digitalWrite(green, HIGH);

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);

      //Reverse
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves Backwards
      digitalWrite(LMotorpin2, LOW);
      digitalWrite(RMotorpin1, HIGH);  // Right Motor moves Backwards
      digitalWrite(RMotorpin2, LOW);
      delay(5000);

      //Turn_Right
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves One way
      digitalWrite(LMotorpin2, LOW);

      digitalWrite(RMotorpin1, LOW);   // Right Motor moves the Other way
      digitalWrite(RMotorpin2, HIGH);

      delay(800);                   // The value  800 is to get perfect 180 degree Right Turn

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);
    }
    //Ultrasonic Configuration
    if (distance >= 200 || distance <= 0) {
      Serial.println("Out of range");
    }
    else {
      Serial.print(distance);
      Serial.println(" cm");
    }

    while (digitalRead(Music) == HIGH) {      //When the music button is pressed:
      //Stop
    digitalWrite(RMotorpin1, LOW);
    digitalWrite(LMotorpin1, LOW);
    digitalWrite(RMotorpin2, LOW);
    digitalWrite(LMotorpin2, LOW);
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
      for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

        // calculates the duration of each note
        divider = melody[thisNote + 1];
        if (divider > 0) {
          // regular note, just proceed
          noteDuration = (wholenote) / divider;
        } else if (divider < 0) {
          // dotted notes are represented with negative durations
          noteDuration = (wholenote) / abs(divider);
          noteDuration *= 1.5; // increases the duration in half for dotted notes
        }

        // playing the note for 90% of the duration, leaving 10% as a pause
        tone(buzzer, melody[thisNote], noteDuration * 0.9);

        // Wait for the specific duration before playing the next note.
        delay(noteDuration);

        // stop the waveform generation before the next note.
        noTone(buzzer);
      }
    }
      
      delay(500);

      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);
      digitalWrite(trigPin, HIGH);
      delayMicroseconds(10); // Added this line
      digitalWrite(trigPin, LOW);
      duration = pulseIn(echoPin, HIGH);
      distance = (duration / 2) / 29.1;

      if (distance < 30) {
        digitalWrite(red, HIGH);
        digitalWrite(green, HIGH);

        //Stop
        digitalWrite(RMotorpin1, LOW);
        digitalWrite(LMotorpin1, LOW);
        digitalWrite(RMotorpin2, LOW);
        digitalWrite(LMotorpin2, LOW);
        delay(1000);

        //Reverse
        digitalWrite(LMotorpin1, HIGH);  // Left Motor moves Backwards
        digitalWrite(LMotorpin2, LOW);
        digitalWrite(RMotorpin1, HIGH);  // Right Motor moves Backwards
        digitalWrite(RMotorpin2, LOW);
        delay(5000);

        //Turn_Right
        digitalWrite(LMotorpin1, HIGH);  // Left Motor moves One way
        digitalWrite(LMotorpin2, LOW);

        digitalWrite(RMotorpin1, LOW);   // Right Motor moves the Other way
        digitalWrite(RMotorpin2, HIGH);

        delay(800);                   // The value  800 is to get perfect 180 degree Right Turn

        //Stop
        digitalWrite(RMotorpin1, LOW);
        digitalWrite(LMotorpin1, LOW);
        digitalWrite(RMotorpin2, LOW);
        digitalWrite(LMotorpin2, LOW);
        delay(1000);
      }
      //Ultrasonic Configuration
      if (distance >= 200 || distance <= 0) {
        Serial.println("Out of range");
      }
      else {
        Serial.print(distance);
        Serial.println(" cm");
      }

      while (digitalRead(Music) == HIGH) {      //When the music button is pressed:
        //Stop
    digitalWrite(RMotorpin1, LOW);
    digitalWrite(LMotorpin1, LOW);
    digitalWrite(RMotorpin2, LOW);
    digitalWrite(LMotorpin2, LOW);
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
        for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

          // calculates the duration of each note
          divider = melody[thisNote + 1];
          if (divider > 0) {
            // regular note, just proceed
            noteDuration = (wholenote) / divider;
          } else if (divider < 0) {
            // dotted notes are represented with negative durations
            noteDuration = (wholenote) / abs(divider);
            noteDuration *= 1.5; // increases the duration in half for dotted notes
          }

          // playing the note for 90% of the duration, leaving 10% as a pause
          tone(buzzer, melody[thisNote], noteDuration * 0.9);

          // Wait for the specific duration before playing the next note.
          delay(noteDuration);

          // stop the waveform generation before the next note.
          noTone(buzzer);
        }
      }
    }

    //Turn_Left
    digitalWrite(LMotorpin1, LOW);  // Left Motor moves One way
    digitalWrite(LMotorpin2, HIGH);

    digitalWrite(RMotorpin1, HIGH); // Right Motor moves the Other way
    digitalWrite(RMotorpin2, LOW);

    delay(400);                   // The value 800 is to get perfect 180 Turn
    
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); // Added this line
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) / 29.1;

    if (distance < 30) {
      digitalWrite(red, HIGH);
      digitalWrite(green, HIGH);

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);

      //Reverse
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves Backwards
      digitalWrite(LMotorpin2, LOW);
      digitalWrite(RMotorpin1, HIGH);  // Right Motor moves Backwards
      digitalWrite(RMotorpin2, LOW);
      delay(5000);

      //Turn_Right
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves One way
      digitalWrite(LMotorpin2, LOW);

      digitalWrite(RMotorpin1, LOW);   // Right Motor moves the Other way
      digitalWrite(RMotorpin2, HIGH);

      delay(800);                   // The value  800 is to get perfect 180 degree Right Turn

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);
    }
    //Ultrasonic Configuration
    if (distance >= 200 || distance <= 0) {
      Serial.println("Out of range");
    }
    else {
      Serial.print(distance);
      Serial.println(" cm");
    }

    while (digitalRead(Music) == HIGH) {      //When the music button is pressed:
      //Stop
    digitalWrite(RMotorpin1, LOW);
    digitalWrite(LMotorpin1, LOW);
    digitalWrite(RMotorpin2, LOW);
    digitalWrite(LMotorpin2, LOW);
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
      for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

        // calculates the duration of each note
        divider = melody[thisNote + 1];
        if (divider > 0) {
          // regular note, just proceed
          noteDuration = (wholenote) / divider;
        } else if (divider < 0) {
          // dotted notes are represented with negative durations
          noteDuration = (wholenote) / abs(divider);
          noteDuration *= 1.5; // increases the duration in half for dotted notes
        }

        // playing the note for 90% of the duration, leaving 10% as a pause
        tone(buzzer, melody[thisNote], noteDuration * 0.9);

        // Wait for the specific duration before playing the next note.
        delay(noteDuration);

        // stop the waveform generation before the next note.
        noTone(buzzer);
      }
    }

    delay(400);

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); // Added this line
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) / 29.1;

    if (distance < 30) {
      digitalWrite(red, HIGH);
      digitalWrite(green, HIGH);

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);

      //Reverse
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves Backwards
      digitalWrite(LMotorpin2, LOW);
      digitalWrite(RMotorpin1, HIGH);  // Right Motor moves Backwards
      digitalWrite(RMotorpin2, LOW);
      delay(5000);

      //Turn_Right
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves One way
      digitalWrite(LMotorpin2, LOW);

      digitalWrite(RMotorpin1, LOW);   // Right Motor moves the Other way
      digitalWrite(RMotorpin2, HIGH);

      delay(800);                   // The value  800 is to get perfect 180 degree Right Turn

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);
    }
    //Ultrasonic Configuration
    if (distance >= 200 || distance <= 0) {
      Serial.println("Out of range");
    }
    else {
      Serial.print(distance);
      Serial.println(" cm");
    }

    while (digitalRead(Music) == HIGH) {      //When the music button is pressed:
      //Stop
    digitalWrite(RMotorpin1, LOW);
    digitalWrite(LMotorpin1, LOW);
    digitalWrite(RMotorpin2, LOW);
    digitalWrite(LMotorpin2, LOW);
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
      for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

        // calculates the duration of each note
        divider = melody[thisNote + 1];
        if (divider > 0) {
          // regular note, just proceed
          noteDuration = (wholenote) / divider;
        } else if (divider < 0) {
          // dotted notes are represented with negative durations
          noteDuration = (wholenote) / abs(divider);
          noteDuration *= 1.5; // increases the duration in half for dotted notes
        }

        // playing the note for 90% of the duration, leaving 10% as a pause
        tone(buzzer, melody[thisNote], noteDuration * 0.9);

        // Wait for the specific duration before playing the next note.
        delay(noteDuration);

        // stop the waveform generation before the next note.
        noTone(buzzer);
      }
    }

    //Stop
    digitalWrite(RMotorpin1, LOW);
    digitalWrite(LMotorpin1, LOW);
    digitalWrite(RMotorpin2, LOW);
    digitalWrite(LMotorpin2, LOW);
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
  }

  while (digitalRead(Backward) == HIGH) {
    digitalWrite(green, HIGH);
    digitalWrite(red, LOW);
    //Move_Backward
    digitalWrite(LMotorpin1, HIGH);  // Left Motor moves Backwards
    digitalWrite(LMotorpin2, LOW);

    digitalWrite(RMotorpin1, HIGH);  // Right Motor moves Backwards
    digitalWrite(RMotorpin2, LOW);

    delay(500);

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); // Added this line
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) / 29.1;

    if (distance < 30) {
      digitalWrite(red, HIGH);
      digitalWrite(green, HIGH);

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);

      //Reverse
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves Backwards
      digitalWrite(LMotorpin2, LOW);
      digitalWrite(RMotorpin1, HIGH);  // Right Motor moves Backwards
      digitalWrite(RMotorpin2, LOW);
      delay(5000);

      //Turn_Right
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves One way
      digitalWrite(LMotorpin2, LOW);

      digitalWrite(RMotorpin1, LOW);   // Right Motor moves the Other way
      digitalWrite(RMotorpin2, HIGH);

      delay(800);                   // The value  800 is to get perfect 180 degree Right Turn

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);
    }
    //Ultrasonic Configuration
    if (distance >= 200 || distance <= 0) {
      Serial.println("Out of range");
    }
    else {
      Serial.print(distance);
      Serial.println(" cm");
    }

    while (digitalRead(Music) == HIGH) {      //When the music button is pressed:
      //Stop
    digitalWrite(RMotorpin1, LOW);
    digitalWrite(LMotorpin1, LOW);
    digitalWrite(RMotorpin2, LOW);
    digitalWrite(LMotorpin2, LOW);
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
      for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

        // calculates the duration of each note
        divider = melody[thisNote + 1];
        if (divider > 0) {
          // regular note, just proceed
          noteDuration = (wholenote) / divider;
        } else if (divider < 0) {
          // dotted notes are represented with negative durations
          noteDuration = (wholenote) / abs(divider);
          noteDuration *= 1.5; // increases the duration in half for dotted notes
        }

        // playing the note for 90% of the duration, leaving 10% as a pause
        tone(buzzer, melody[thisNote], noteDuration * 0.9);

        // Wait for the specific duration before playing the next note.
        delay(noteDuration);

        // stop the waveform generation before the next note.
        noTone(buzzer);
      }
    }

    delay(500);

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); // Added this line
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) / 29.1;

    if (distance < 30) {
      digitalWrite(red, HIGH);
      digitalWrite(green, HIGH);

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);

      //Reverse
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves Backwards
      digitalWrite(LMotorpin2, LOW);
      digitalWrite(RMotorpin1, HIGH);  // Right Motor moves Backwards
      digitalWrite(RMotorpin2, LOW);
      delay(5000);

      //Turn_Right
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves One way
      digitalWrite(LMotorpin2, LOW);

      digitalWrite(RMotorpin1, LOW);   // Right Motor moves the Other way
      digitalWrite(RMotorpin2, HIGH);

      delay(800);                   // The value  800 is to get perfect 180 degree Right Turn

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);
    }
    //Ultrasonic Configuration
    if (distance >= 200 || distance <= 0) {
      Serial.println("Out of range");
    }
    else {
      Serial.print(distance);
      Serial.println(" cm");
    }

    while (digitalRead(Music) == HIGH) {      //When the music button is pressed:
      //Stop
    digitalWrite(RMotorpin1, LOW);
    digitalWrite(LMotorpin1, LOW);
    digitalWrite(RMotorpin2, LOW);
    digitalWrite(LMotorpin2, LOW);
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
      for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

        // calculates the duration of each note
        divider = melody[thisNote + 1];
        if (divider > 0) {
          // regular note, just proceed
          noteDuration = (wholenote) / divider;
        } else if (divider < 0) {
          // dotted notes are represented with negative durations
          noteDuration = (wholenote) / abs(divider);
          noteDuration *= 1.5; // increases the duration in half for dotted notes
        }

        // playing the note for 90% of the duration, leaving 10% as a pause
        tone(buzzer, melody[thisNote], noteDuration * 0.9);

        // Wait for the specific duration before playing the next note.
        delay(noteDuration);

        // stop the waveform generation before the next note.
        noTone(buzzer);
      }
    }

    delay(500);

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); // Added this line
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) / 29.1;

    if (distance < 30) {
      digitalWrite(red, HIGH);
      digitalWrite(green, HIGH);

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);

      //Reverse
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves Backwards
      digitalWrite(LMotorpin2, LOW);
      digitalWrite(RMotorpin1, HIGH);  // Right Motor moves Backwards
      digitalWrite(RMotorpin2, LOW);
      delay(5000);

      //Turn_Right
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves One way
      digitalWrite(LMotorpin2, LOW);

      digitalWrite(RMotorpin1, LOW);   // Right Motor moves the Other way
      digitalWrite(RMotorpin2, HIGH);

      delay(800);                   // The value  800 is to get perfect 180 degree Right Turn

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);
    }
    //Ultrasonic Configuration
    if (distance >= 200 || distance <= 0) {
      Serial.println("Out of range");
    }
    else {
      Serial.print(distance);
      Serial.println(" cm");
    }

    while (digitalRead(Music) == HIGH) {      //When the music button is pressed:
      //Stop
    digitalWrite(RMotorpin1, LOW);
    digitalWrite(LMotorpin1, LOW);
    digitalWrite(RMotorpin2, LOW);
    digitalWrite(LMotorpin2, LOW);
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
      for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

        // calculates the duration of each note
        divider = melody[thisNote + 1];
        if (divider > 0) {
          // regular note, just proceed
          noteDuration = (wholenote) / divider;
        } else if (divider < 0) {
          // dotted notes are represented with negative durations
          noteDuration = (wholenote) / abs(divider);
          noteDuration *= 1.5; // increases the duration in half for dotted notes
        }

        // playing the note for 90% of the duration, leaving 10% as a pause
        tone(buzzer, melody[thisNote], noteDuration * 0.9);

        // Wait for the specific duration before playing the next note.
        delay(noteDuration);

        // stop the waveform generation before the next note.
        noTone(buzzer);
      }
    }

    delay(500);

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); // Added this line
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) / 29.1;

    if (distance < 30) {
      digitalWrite(red, HIGH);
      digitalWrite(green, HIGH);

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);

      //Reverse
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves Backwards
      digitalWrite(LMotorpin2, LOW);
      digitalWrite(RMotorpin1, HIGH);  // Right Motor moves Backwards
      digitalWrite(RMotorpin2, LOW);
      delay(5000);

      //Turn_Right
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves One way
      digitalWrite(LMotorpin2, LOW);

      digitalWrite(RMotorpin1, LOW);   // Right Motor moves the Other way
      digitalWrite(RMotorpin2, HIGH);

      delay(800);                   // The value  800 is to get perfect 180 degree Right Turn

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);
    }
    //Ultrasonic Configuration
    if (distance >= 200 || distance <= 0) {
      Serial.println("Out of range");
    }
    else {
      Serial.print(distance);
      Serial.println(" cm");
    }

    while (digitalRead(Music) == HIGH) {      //When the music button is pressed:
      //Stop
    digitalWrite(RMotorpin1, LOW);
    digitalWrite(LMotorpin1, LOW);
    digitalWrite(RMotorpin2, LOW);
    digitalWrite(LMotorpin2, LOW);
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
      for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

        // calculates the duration of each note
        divider = melody[thisNote + 1];
        if (divider > 0) {
          // regular note, just proceed
          noteDuration = (wholenote) / divider;
        } else if (divider < 0) {
          // dotted notes are represented with negative durations
          noteDuration = (wholenote) / abs(divider);
          noteDuration *= 1.5; // increases the duration in half for dotted notes
        }

        // playing the note for 90% of the duration, leaving 10% as a pause
        tone(buzzer, melody[thisNote], noteDuration * 0.9);

        // Wait for the specific duration before playing the next note.
        delay(noteDuration);

        // stop the waveform generation before the next note.
        noTone(buzzer);
      }
    }

    delay(500);

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); // Added this line
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) / 29.1;

    if (distance < 30) {
      digitalWrite(red, HIGH);
      digitalWrite(green, HIGH);

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);

      //Reverse
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves Backwards
      digitalWrite(LMotorpin2, LOW);
      digitalWrite(RMotorpin1, HIGH);  // Right Motor moves Backwards
      digitalWrite(RMotorpin2, LOW);
      delay(5000);

      //Turn_Right
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves One way
      digitalWrite(LMotorpin2, LOW);

      digitalWrite(RMotorpin1, LOW);   // Right Motor moves the Other way
      digitalWrite(RMotorpin2, HIGH);

      delay(800);                   // The value  800 is to get perfect 180 degree Right Turn

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);
    }
    //Ultrasonic Configuration
    if (distance >= 200 || distance <= 0) {
      Serial.println("Out of range");
    }
    else {
      Serial.print(distance);
      Serial.println(" cm");
    }

    while (digitalRead(Music) == HIGH) {      //When the music button is pressed:
      //Stop
    digitalWrite(RMotorpin1, LOW);
    digitalWrite(LMotorpin1, LOW);
    digitalWrite(RMotorpin2, LOW);
    digitalWrite(LMotorpin2, LOW);
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
      for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

        // calculates the duration of each note
        divider = melody[thisNote + 1];
        if (divider > 0) {
          // regular note, just proceed
          noteDuration = (wholenote) / divider;
        } else if (divider < 0) {
          // dotted notes are represented with negative durations
          noteDuration = (wholenote) / abs(divider);
          noteDuration *= 1.5; // increases the duration in half for dotted notes
        }

        // playing the note for 90% of the duration, leaving 10% as a pause
        tone(buzzer, melody[thisNote], noteDuration * 0.9);

        // Wait for the specific duration before playing the next note.
        delay(noteDuration);

        // stop the waveform generation before the next note.
        noTone(buzzer);
      }
    }

    delay(500);

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); // Added this line
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) / 29.1;

    if (distance < 30) {
      digitalWrite(red, HIGH);
      digitalWrite(green, HIGH);

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);

      //Reverse
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves Backwards
      digitalWrite(LMotorpin2, LOW);
      digitalWrite(RMotorpin1, HIGH);  // Right Motor moves Backwards
      digitalWrite(RMotorpin2, LOW);
      delay(5000);

      //Turn_Right
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves One way
      digitalWrite(LMotorpin2, LOW);

      digitalWrite(RMotorpin1, LOW);   // Right Motor moves the Other way
      digitalWrite(RMotorpin2, HIGH);

      delay(800);                   // The value  800 is to get perfect 180 degree Right Turn

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);
    }
    //Ultrasonic Configuration
    if (distance >= 200 || distance <= 0) {
      Serial.println("Out of range");
    }
    else {
      Serial.print(distance);
      Serial.println(" cm");
    }

    while (digitalRead(Music) == HIGH) {      //When the music button is pressed:
      //Stop
    digitalWrite(RMotorpin1, LOW);
    digitalWrite(LMotorpin1, LOW);
    digitalWrite(RMotorpin2, LOW);
    digitalWrite(LMotorpin2, LOW);
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
      for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

        // calculates the duration of each note
        divider = melody[thisNote + 1];
        if (divider > 0) {
          // regular note, just proceed
          noteDuration = (wholenote) / divider;
        } else if (divider < 0) {
          // dotted notes are represented with negative durations
          noteDuration = (wholenote) / abs(divider);
          noteDuration *= 1.5; // increases the duration in half for dotted notes
        }

        // playing the note for 90% of the duration, leaving 10% as a pause
        tone(buzzer, melody[thisNote], noteDuration * 0.9);

        // Wait for the specific duration before playing the next note.
        delay(noteDuration);

        // stop the waveform generation before the next note.
        noTone(buzzer);
      }
    }

    delay(500);

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); // Added this line
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) / 29.1;

    if (distance < 30) {
      digitalWrite(red, HIGH);
      digitalWrite(green, HIGH);

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);

      //Reverse
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves Backwards
      digitalWrite(LMotorpin2, LOW);
      digitalWrite(RMotorpin1, HIGH);  // Right Motor moves Backwards
      digitalWrite(RMotorpin2, LOW);
      delay(5000);

      //Turn_Right
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves One way
      digitalWrite(LMotorpin2, LOW);

      digitalWrite(RMotorpin1, LOW);   // Right Motor moves the Other way
      digitalWrite(RMotorpin2, HIGH);

      delay(800);                   // The value  800 is to get perfect 180 degree Right Turn

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);
    }
    //Ultrasonic Configuration
    if (distance >= 200 || distance <= 0) {
      Serial.println("Out of range");
    }
    else {
      Serial.print(distance);
      Serial.println(" cm");
    }

    while (digitalRead(Music) == HIGH) {      //When the music button is pressed:
      //Stop
    digitalWrite(RMotorpin1, LOW);
    digitalWrite(LMotorpin1, LOW);
    digitalWrite(RMotorpin2, LOW);
    digitalWrite(LMotorpin2, LOW);
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
      for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

        // calculates the duration of each note
        divider = melody[thisNote + 1];
        if (divider > 0) {
          // regular note, just proceed
          noteDuration = (wholenote) / divider;
        } else if (divider < 0) {
          // dotted notes are represented with negative durations
          noteDuration = (wholenote) / abs(divider);
          noteDuration *= 1.5; // increases the duration in half for dotted notes
        }

        // playing the note for 90% of the duration, leaving 10% as a pause
        tone(buzzer, melody[thisNote], noteDuration * 0.9);

        // Wait for the specific duration before playing the next note.
        delay(noteDuration);

        // stop the waveform generation before the next note.
        noTone(buzzer);
      }
    }

    delay(500);

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); // Added this line
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) / 29.1;

    if (distance < 30) {
      digitalWrite(red, HIGH);
      digitalWrite(green, HIGH);

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);

      //Reverse
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves Backwards
      digitalWrite(LMotorpin2, LOW);
      digitalWrite(RMotorpin1, HIGH);  // Right Motor moves Backwards
      digitalWrite(RMotorpin2, LOW);
      delay(5000);

      //Turn_Right
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves One way
      digitalWrite(LMotorpin2, LOW);

      digitalWrite(RMotorpin1, LOW);   // Right Motor moves the Other way
      digitalWrite(RMotorpin2, HIGH);

      delay(800);                   // The value  800 is to get perfect 180 degree Right Turn

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);
    }
    //Ultrasonic Configuration
    if (distance >= 200 || distance <= 0) {
      Serial.println("Out of range");
    }
    else {
      Serial.print(distance);
      Serial.println(" cm");
    }

    while (digitalRead(Music) == HIGH) {      //When the music button is pressed:
      //Stop
    digitalWrite(RMotorpin1, LOW);
    digitalWrite(LMotorpin1, LOW);
    digitalWrite(RMotorpin2, LOW);
    digitalWrite(LMotorpin2, LOW);
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
      for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

        // calculates the duration of each note
        divider = melody[thisNote + 1];
        if (divider > 0) {
          // regular note, just proceed
          noteDuration = (wholenote) / divider;
        } else if (divider < 0) {
          // dotted notes are represented with negative durations
          noteDuration = (wholenote) / abs(divider);
          noteDuration *= 1.5; // increases the duration in half for dotted notes
        }

        // playing the note for 90% of the duration, leaving 10% as a pause
        tone(buzzer, melody[thisNote], noteDuration * 0.9);

        // Wait for the specific duration before playing the next note.
        delay(noteDuration);

        // stop the waveform generation before the next note.
        noTone(buzzer);
      }
    }

    delay(500);

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); // Added this line
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) / 29.1;

    if (distance < 30) {
      digitalWrite(red, HIGH);
      digitalWrite(green, HIGH);

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);

      //Reverse
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves Backwards
      digitalWrite(LMotorpin2, LOW);
      digitalWrite(RMotorpin1, HIGH);  // Right Motor moves Backwards
      digitalWrite(RMotorpin2, LOW);
      delay(5000);

      //Turn_Right
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves One way
      digitalWrite(LMotorpin2, LOW);

      digitalWrite(RMotorpin1, LOW);   // Right Motor moves the Other way
      digitalWrite(RMotorpin2, HIGH);

      delay(800);                   // The value  800 is to get perfect 180 degree Right Turn

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);
    }
    //Ultrasonic Configuration
    if (distance >= 200 || distance <= 0) {
      Serial.println("Out of range");
    }
    else {
      Serial.print(distance);
      Serial.println(" cm");
    }

    while (digitalRead(Music) == HIGH) {      //When the music button is pressed:
      //Stop
    digitalWrite(RMotorpin1, LOW);
    digitalWrite(LMotorpin1, LOW);
    digitalWrite(RMotorpin2, LOW);
    digitalWrite(LMotorpin2, LOW);
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
      for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

        // calculates the duration of each note
        divider = melody[thisNote + 1];
        if (divider > 0) {
          // regular note, just proceed
          noteDuration = (wholenote) / divider;
        } else if (divider < 0) {
          // dotted notes are represented with negative durations
          noteDuration = (wholenote) / abs(divider);
          noteDuration *= 1.5; // increases the duration in half for dotted notes
        }

        // playing the note for 90% of the duration, leaving 10% as a pause
        tone(buzzer, melody[thisNote], noteDuration * 0.9);

        // Wait for the specific duration before playing the next note.
        delay(noteDuration);

        // stop the waveform generation before the next note.
        noTone(buzzer);
      }
    }

    delay(500);

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); // Added this line
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) / 29.1;

    if (distance < 30) {
      digitalWrite(red, HIGH);
      digitalWrite(green, HIGH);

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);

      //Reverse
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves Backwards
      digitalWrite(LMotorpin2, LOW);
      digitalWrite(RMotorpin1, HIGH);  // Right Motor moves Backwards
      digitalWrite(RMotorpin2, LOW);
      delay(5000);

      //Turn_Right
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves One way
      digitalWrite(LMotorpin2, LOW);

      digitalWrite(RMotorpin1, LOW);   // Right Motor moves the Other way
      digitalWrite(RMotorpin2, HIGH);

      delay(800);                   // The value  800 is to get perfect 180 degree Right Turn

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);
    }
    //Ultrasonic Configuration
    if (distance >= 200 || distance <= 0) {
      Serial.println("Out of range");
    }
    else {
      Serial.print(distance);
      Serial.println(" cm");
    }

    while (digitalRead(Music) == HIGH) {      //When the music button is pressed:
      //Stop
    digitalWrite(RMotorpin1, LOW);
    digitalWrite(LMotorpin1, LOW);
    digitalWrite(RMotorpin2, LOW);
    digitalWrite(LMotorpin2, LOW);
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
      for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

        // calculates the duration of each note
        divider = melody[thisNote + 1];
        if (divider > 0) {
          // regular note, just proceed
          noteDuration = (wholenote) / divider;
        } else if (divider < 0) {
          // dotted notes are represented with negative durations
          noteDuration = (wholenote) / abs(divider);
          noteDuration *= 1.5; // increases the duration in half for dotted notes
        }

        // playing the note for 90% of the duration, leaving 10% as a pause
        tone(buzzer, melody[thisNote], noteDuration * 0.9);

        // Wait for the specific duration before playing the next note.
        delay(noteDuration);

        // stop the waveform generation before the next note.
        noTone(buzzer);
      }
    }

    //Turn_Left
    digitalWrite(LMotorpin1, LOW);  // Left Motor moves One way
    digitalWrite(LMotorpin2, HIGH);

    digitalWrite(RMotorpin1, HIGH); // Right Motor moves the Other way
    digitalWrite(RMotorpin2, LOW);

    delay(400);                   // The value 800 is to get perfect 180 Turn

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); // Added this line
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) / 29.1;

    if (distance < 30) {
      digitalWrite(red, HIGH);
      digitalWrite(green, HIGH);

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);

      //Reverse
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves Backwards
      digitalWrite(LMotorpin2, LOW);
      digitalWrite(RMotorpin1, HIGH);  // Right Motor moves Backwards
      digitalWrite(RMotorpin2, LOW);
      delay(5000);

      //Turn_Right
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves One way
      digitalWrite(LMotorpin2, LOW);

      digitalWrite(RMotorpin1, LOW);   // Right Motor moves the Other way
      digitalWrite(RMotorpin2, HIGH);

      delay(800);                   // The value  800 is to get perfect 180 degree Right Turn

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);
    }
    //Ultrasonic Configuration
    if (distance >= 200 || distance <= 0) {
      Serial.println("Out of range");
    }
    else {
      Serial.print(distance);
      Serial.println(" cm");
    }

    while (digitalRead(Music) == HIGH) {      //When the music button is pressed:
      //Stop
    digitalWrite(RMotorpin1, LOW);
    digitalWrite(LMotorpin1, LOW);
    digitalWrite(RMotorpin2, LOW);
    digitalWrite(LMotorpin2, LOW);
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
      for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

        // calculates the duration of each note
        divider = melody[thisNote + 1];
        if (divider > 0) {
          // regular note, just proceed
          noteDuration = (wholenote) / divider;
        } else if (divider < 0) {
          // dotted notes are represented with negative durations
          noteDuration = (wholenote) / abs(divider);
          noteDuration *= 1.5; // increases the duration in half for dotted notes
        }

        // playing the note for 90% of the duration, leaving 10% as a pause
        tone(buzzer, melody[thisNote], noteDuration * 0.9);

        // Wait for the specific duration before playing the next note.
        delay(noteDuration);

        // stop the waveform generation before the next note.
        noTone(buzzer);
      }
    }

    delay(400);

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); // Added this line
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) / 29.1;

    if (distance < 30) {
      digitalWrite(red, HIGH);
      digitalWrite(green, HIGH);

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);

      //Reverse
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves Backwards
      digitalWrite(LMotorpin2, LOW);
      digitalWrite(RMotorpin1, HIGH);  // Right Motor moves Backwards
      digitalWrite(RMotorpin2, LOW);
      delay(5000);

      //Turn_Right
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves One way
      digitalWrite(LMotorpin2, LOW);

      digitalWrite(RMotorpin1, LOW);   // Right Motor moves the Other way
      digitalWrite(RMotorpin2, HIGH);

      delay(800);                   // The value  800 is to get perfect 180 degree Right Turn

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);
    }
    //Ultrasonic Configuration
    if (distance >= 200 || distance <= 0) {
      Serial.println("Out of range");
    }
    else {
      Serial.print(distance);
      Serial.println(" cm");
    }

    while (digitalRead(Music) == HIGH) {      //When the music button is pressed:
      //Stop
    digitalWrite(RMotorpin1, LOW);
    digitalWrite(LMotorpin1, LOW);
    digitalWrite(RMotorpin2, LOW);
    digitalWrite(LMotorpin2, LOW);
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
      for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

        // calculates the duration of each note
        divider = melody[thisNote + 1];
        if (divider > 0) {
          // regular note, just proceed
          noteDuration = (wholenote) / divider;
        } else if (divider < 0) {
          // dotted notes are represented with negative durations
          noteDuration = (wholenote) / abs(divider);
          noteDuration *= 1.5; // increases the duration in half for dotted notes
        }

        // playing the note for 90% of the duration, leaving 10% as a pause
        tone(buzzer, melody[thisNote], noteDuration * 0.9);

        // Wait for the specific duration before playing the next note.
        delay(noteDuration);

        // stop the waveform generation before the next note.
        noTone(buzzer);
      }
    }

    //zigzag_Backward
    for (int b = 0; b < 4; b++)     // this moves the car backwards in zig zag for 4 steps
    {
      digitalWrite(LMotorpin1, HIGH); // Left Motor moves Backward
      digitalWrite(LMotorpin2, LOW);
      digitalWrite(RMotorpin1, LOW); // Right Motor does not move
      digitalWrite(RMotorpin2, LOW);

      delay(500);                     // Change delay time to shorten or increase the stride

      digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); // Added this line
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) / 29.1;

    if (distance < 30) {
      digitalWrite(red, HIGH);
      digitalWrite(green, HIGH);

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);

      //Reverse
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves Backwards
      digitalWrite(LMotorpin2, LOW);
      digitalWrite(RMotorpin1, HIGH);  // Right Motor moves Backwards
      digitalWrite(RMotorpin2, LOW);
      delay(5000);

      //Turn_Right
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves One way
      digitalWrite(LMotorpin2, LOW);

      digitalWrite(RMotorpin1, LOW);   // Right Motor moves the Other way
      digitalWrite(RMotorpin2, HIGH);

      delay(800);                   // The value  800 is to get perfect 180 degree Right Turn

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);
    }
    //Ultrasonic Configuration
    if (distance >= 200 || distance <= 0) {
      Serial.println("Out of range");
    }
    else {
      Serial.print(distance);
      Serial.println(" cm");
    }

    while (digitalRead(Music) == HIGH) {      //When the music button is pressed:
      //Stop
    digitalWrite(RMotorpin1, LOW);
    digitalWrite(LMotorpin1, LOW);
    digitalWrite(RMotorpin2, LOW);
    digitalWrite(LMotorpin2, LOW);
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
      for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

        // calculates the duration of each note
        divider = melody[thisNote + 1];
        if (divider > 0) {
          // regular note, just proceed
          noteDuration = (wholenote) / divider;
        } else if (divider < 0) {
          // dotted notes are represented with negative durations
          noteDuration = (wholenote) / abs(divider);
          noteDuration *= 1.5; // increases the duration in half for dotted notes
        }

        // playing the note for 90% of the duration, leaving 10% as a pause
        tone(buzzer, melody[thisNote], noteDuration * 0.9);

        // Wait for the specific duration before playing the next note.
        delay(noteDuration);

        // stop the waveform generation before the next note.
        noTone(buzzer);
      }
    } 

      delay(500);

      digitalWrite(RMotorpin1, HIGH); // Right Motor moves Forward
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin1, LOW); // Left Motor does not move
      digitalWrite(LMotorpin2, LOW);

      delay(500);                     // Change delay time to shorten or increase the stride

      digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); // Added this line
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) / 29.1;

    if (distance < 30) {
      digitalWrite(red, HIGH);
      digitalWrite(green, HIGH);

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);

      //Reverse
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves Backwards
      digitalWrite(LMotorpin2, LOW);
      digitalWrite(RMotorpin1, HIGH);  // Right Motor moves Backwards
      digitalWrite(RMotorpin2, LOW);
      delay(5000);

      //Turn_Right
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves One way
      digitalWrite(LMotorpin2, LOW);

      digitalWrite(RMotorpin1, LOW);   // Right Motor moves the Other way
      digitalWrite(RMotorpin2, HIGH);

      delay(800);                   // The value  800 is to get perfect 180 degree Right Turn

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);
    }
    //Ultrasonic Configuration
    if (distance >= 200 || distance <= 0) {
      Serial.println("Out of range");
    }
    else {
      Serial.print(distance);
      Serial.println(" cm");
    }

    while (digitalRead(Music) == HIGH) {      //When the music button is pressed:
      //Stop
    digitalWrite(RMotorpin1, LOW);
    digitalWrite(LMotorpin1, LOW);
    digitalWrite(RMotorpin2, LOW);
    digitalWrite(LMotorpin2, LOW);
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
      for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

        // calculates the duration of each note
        divider = melody[thisNote + 1];
        if (divider > 0) {
          // regular note, just proceed
          noteDuration = (wholenote) / divider;
        } else if (divider < 0) {
          // dotted notes are represented with negative durations
          noteDuration = (wholenote) / abs(divider);
          noteDuration *= 1.5; // increases the duration in half for dotted notes
        }

        // playing the note for 90% of the duration, leaving 10% as a pause
        tone(buzzer, melody[thisNote], noteDuration * 0.9);

        // Wait for the specific duration before playing the next note.
        delay(noteDuration);

        // stop the waveform generation before the next note.
        noTone(buzzer);
      }
    }

      delay(500);
    }

    //Turn_Left
    digitalWrite(LMotorpin1, LOW);  // Left Motor moves One way
    digitalWrite(LMotorpin2, HIGH);

    digitalWrite(RMotorpin1, HIGH); // Right Motor moves the Other way
    digitalWrite(RMotorpin2, LOW);

    delay(400);                   // The value 800 is to get perfect 180 Turn

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); // Added this line
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) / 29.1;

    if (distance < 30) {
      digitalWrite(red, HIGH);
      digitalWrite(green, HIGH);

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);

      //Reverse
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves Backwards
      digitalWrite(LMotorpin2, LOW);
      digitalWrite(RMotorpin1, HIGH);  // Right Motor moves Backwards
      digitalWrite(RMotorpin2, LOW);
      delay(5000);

      //Turn_Right
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves One way
      digitalWrite(LMotorpin2, LOW);

      digitalWrite(RMotorpin1, LOW);   // Right Motor moves the Other way
      digitalWrite(RMotorpin2, HIGH);

      delay(800);                   // The value  800 is to get perfect 180 degree Right Turn

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);
    }
    //Ultrasonic Configuration
    if (distance >= 200 || distance <= 0) {
      Serial.println("Out of range");
    }
    else {
      Serial.print(distance);
      Serial.println(" cm");
    }

    while (digitalRead(Music) == HIGH) {      //When the music button is pressed:
      //Stop
    digitalWrite(RMotorpin1, LOW);
    digitalWrite(LMotorpin1, LOW);
    digitalWrite(RMotorpin2, LOW);
    digitalWrite(LMotorpin2, LOW);
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
      for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

        // calculates the duration of each note
        divider = melody[thisNote + 1];
        if (divider > 0) {
          // regular note, just proceed
          noteDuration = (wholenote) / divider;
        } else if (divider < 0) {
          // dotted notes are represented with negative durations
          noteDuration = (wholenote) / abs(divider);
          noteDuration *= 1.5; // increases the duration in half for dotted notes
        }

        // playing the note for 90% of the duration, leaving 10% as a pause
        tone(buzzer, melody[thisNote], noteDuration * 0.9);

        // Wait for the specific duration before playing the next note.
        delay(noteDuration);

        // stop the waveform generation before the next note.
        noTone(buzzer);
      }
    }

    delay(400);

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); // Added this line
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) / 29.1;

    if (distance < 30) {
      digitalWrite(red, HIGH);
      digitalWrite(green, HIGH);

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);

      //Reverse
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves Backwards
      digitalWrite(LMotorpin2, LOW);
      digitalWrite(RMotorpin1, HIGH);  // Right Motor moves Backwards
      digitalWrite(RMotorpin2, LOW);
      delay(5000);

      //Turn_Right
      digitalWrite(LMotorpin1, HIGH);  // Left Motor moves One way
      digitalWrite(LMotorpin2, LOW);

      digitalWrite(RMotorpin1, LOW);   // Right Motor moves the Other way
      digitalWrite(RMotorpin2, HIGH);

      delay(800);                   // The value  800 is to get perfect 180 degree Right Turn

      //Stop
      digitalWrite(RMotorpin1, LOW);
      digitalWrite(LMotorpin1, LOW);
      digitalWrite(RMotorpin2, LOW);
      digitalWrite(LMotorpin2, LOW);
      delay(1000);
    }
    //Ultrasonic Configuration
    if (distance >= 200 || distance <= 0) {
      Serial.println("Out of range");
    }
    else {
      Serial.print(distance);
      Serial.println(" cm");
    }

    while (digitalRead(Music) == HIGH) {      //When the music button is pressed:
      //Stop
    digitalWrite(RMotorpin1, LOW);
    digitalWrite(LMotorpin1, LOW);
    digitalWrite(RMotorpin2, LOW);
    digitalWrite(LMotorpin2, LOW);
    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
      for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

        // calculates the duration of each note
        divider = melody[thisNote + 1];
        if (divider > 0) {
          // regular note, just proceed
          noteDuration = (wholenote) / divider;
        } else if (divider < 0) {
          // dotted notes are represented with negative durations
          noteDuration = (wholenote) / abs(divider);
          noteDuration *= 1.5; // increases the duration in half for dotted notes
        }

        // playing the note for 90% of the duration, leaving 10% as a pause
        tone(buzzer, melody[thisNote], noteDuration * 0.9);

        // Wait for the specific duration before playing the next note.
        delay(noteDuration);

        // stop the waveform generation before the next note.
        noTone(buzzer);
      }
    }

    digitalWrite(green, LOW);
    digitalWrite(red, HIGH);
  }
}