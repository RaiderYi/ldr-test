#define BUF_SIZE 2000

const byte pinLaser = 8;
const byte pinLDR = A0;

const uint16_t impulses[] = {10, 500, 50, 500, 100, 500, 200, 500};
const byte impNum = sizeof(impulses) / sizeof(uint16_t);

volatile unsigned long t = 0, l;
volatile byte n = 0;
volatile byte state = LOW;
//int luminance[BUF_SIZE];

void setup() {
  Serial.begin(115200);

  pinMode(pinLaser, OUTPUT);
  pinMode(pinLDR, INPUT);

  noInterrupts();
  setRxTimer();
  setTxTimer();
  interrupts();
}

void loop() {
  // Nothing to do here…
}

void setRxTimer() {             // Timer3
  TCCR3A = TCCR3B = TCNT3 = 0;  // Reset registers
  OCR3B = F_CPU / 1000 - 1;     // Set frequency
  bitSet(TCCR3B, WGM32);        // CTC mode
  bitSet(TCCR3B, CS30);         // Internal clock
  bitSet(TIMSK3, OCIE3B);       // Enable compare handler
}

void setTxTimer() {             // Timer4
  TCCR4A = TCCR4B = TCNT4 = 0;  // Reset registers
  OCR4B = F_CPU / 1000 - 1;     // Set frequency
  bitSet(TCCR4B, WGM42);        // CTC mode
  bitSet(TCCR4B, CS40);         // Internal clock
  bitSet(TIMSK4, OCIE4B);       // Enable compare handler
}

ISR(TIMER3_COMPB_vect) {
  TCNT3 = 0;

  t++;
  if (impulses[n] == t) {
    digitalWrite(pinLaser, state ^= 1);
    n++; t = 0;
    if (n >= impNum) n = 0;
  }
}

ISR(TIMER4_COMPB_vect) {
  TCNT4 = 0;

  Serial.print(millis());
  Serial.print(',');
  Serial.println(analogRead(pinLDR));
}

