// Simple Iambic Keyer v1.1
//
// Authors:
// Ernest PA3HCM
// Antti OH3HMU

#define P_DOT    2   // Connects to the dot lever of the paddle
#define P_DASH   3   // Connects to the dash lever of the paddle
#define P_AUDIO 12   // Audio output
#define P_CW    13   // Output of the keyer, connect to your radio
#define P_SPEED A0   // Attached to center pin of potmeter, allows you
                     // to set the keying speed.

// Minimum and maximum adjustable WPM speeds.
// Change to your preferred values
#define SPEED_MIN 10
#define SPEED_MAX 35

// 60 kilomillisecs in minute
#define MS_PER_MIN 60000
// 44 dot-long intervals in one "PARIS"
#define DOTS_PER_WORD 44

// Initializing the Arduino
void setup()
{
  pinMode(P_DOT, INPUT);
  pinMode(P_DASH, INPUT);
  pinMode(P_AUDIO, OUTPUT);
  pinMode(P_CW, OUTPUT);
  digitalWrite(P_CW, LOW);      // Start with key up
}

// Main routine
void loop()
{
  // Read the keying speed from potmeter
  int raw_wpm = analogRead(P_SPEED);
  // Scale it to requested interval. To change potentiometer
  // direction, either swap SPEED_MAX and SPEED_MIN or
  // swap the wires.
  int wpm = map(raw_wpm, 0, 1023, SPEED_MAX, SPEED_MIN);
  int delay_for_wpm = MS_PER_MIN / (DOTS_PER_WORD * 44);

  if(!digitalRead(P_DOT))        // If the dot lever is presssed..
  {
    keyAndBeep(delay_for_wpm);           // ... send a dot at the given speed
    delay(delay_for_wpm);                //     and wait before sending next
  }
  if(!digitalRead(P_DASH))       // If the dash lever is pressed...
  {
    keyAndBeep(3 * delay_for_wpm);       // ... send a dash at the given speed
    delay(delay_for_wpm);                //     and wait before sending next
  }
}

// Key the transmitter and sound a beep
void keyAndBeep(int speed)
{
  digitalWrite(P_CW, HIGH);              // Key down
  for (int i = 0; i < (speed / 2); ++i)  // Beep loop
  {
    digitalWrite(P_AUDIO, HIGH);
    delay(1);
    digitalWrite(P_AUDIO, LOW);
    delay(1);
  }
  digitalWrite(P_CW, LOW);               // Key up
}