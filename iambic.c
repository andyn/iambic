// Simple Iambic Keyer v1.1
//
// Authors:
// Ernest PA3HCM
// Antti OH3HMU

// Minimum and maximum adjustable WPM speeds.
// Change to your preferred values
#define SPEED_MIN_WPM 10
#define SPEED_MAX_WPM 35

// Pin configuration
// Connects to the dot lever of the paddle
#define P_DOT    2
// Connects to the dash lever of the paddle
#define P_DASH   3
// Speaker output  
#define P_AUDIO 12
// Output of the keyer, connect to your radio
#define P_CW    13
// Middle analog pin of potentiometer for adjusting keyer speed.
#define P_SPEED A0

// 60 kilomillisecs in minute
#define MS_PER_MIN 60000

// 44 dot-long intervals in one "PARIS".
// XXX Quick and dirty calculation, correct if wrong.
#define DOTS_PER_WORD 44

// Initializing the Arduino
void setup() {
  pinMode(P_DOT, INPUT);
  pinMode(P_DASH, INPUT);
  pinMode(P_AUDIO, OUTPUT);
  pinMode(P_CW, OUTPUT);
  digitalWrite(P_CW, LOW);      // Start with key up
}

// Main routine
void loop() {
    // Read the keying speed from potmeter
    int raw_wpm = analogRead(P_SPEED);

    // Scale it to requested interval. To change potentiometer
    // direction, either swap SPEED_MAX_WPM and SPEED_MIN_WPM or
    // swap the wires.
    int wpm = map(raw_wpm, 0, 1023, SPEED_MAX_WPM, SPEED_MIN_WPM);
    int delay_for_wpm = MS_PER_MIN / (DOTS_PER_WORD * 44);

    // Send alternating dots and dashes (and wait the intervals)
    if(!digitalRead(P_DOT)) {
        keyAndBeep(delay_for_wpm);
        delay(delay_for_wpm);
    }
    if(!digitalRead(P_DASH)) {
        keyAndBeep(3 * delay_for_wpm);
        delay(delay_for_wpm);
    }
}

// Key the transmitter and sound a beep
void keyAndBeep(int speed) {

    // Output to radio on
    digitalWrite(P_CW, HIGH);

    // Square wave beep
    for (int i = 0; i < (speed / 2); ++i) {
        digitalWrite(P_AUDIO, HIGH);
        delay(1);
        digitalWrite(P_AUDIO, LOW);
        delay(1);
    }

    // Output to radio off
    digitalWrite(P_CW, LOW);
}