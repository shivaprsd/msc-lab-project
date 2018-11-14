#define PIN_A  4
#define PIN_A_ 5
#define PIN_B  6
#define PIN_B_ 7
#define PIN_SENSOR A0
#define SENSOR_CONV (5.0 / 1023)  // Sensor conversion factor

#define DRIVER_STEPS 4
#define STEPPER_RES 1.8
#define MAX_RPM 60
#define CLOCKWISE 1
#define ANTICLOCKWISE -1

// Tracking and scanning statuses
#define NOT_STARTED -1
#define STARTED 1
#define FINISHED 0

int get_bit(int n, int pos);
void tick(int n, int del, int dir, int i);
void turn(float deg, float rpm, int dir);
void reset(int dir);
void relax();
int sensor();

// Decimal equivalents of the binary codes to drive the motor
int driver[DRIVER_STEPS] = { 8, 2, 4, 1 };

int scan = NOT_STARTED;
int tracking = NOT_STARTED;
int stepper_pos = 0;
int sensor_out = 0;
int sensor_max = 0;
int scan_delay = (60000 * STEPPER_RES) / (360 * MAX_RPM);

void setup() {
  Serial.begin(9600);   // initialise the console
  pinMode(PIN_A, OUTPUT);
  pinMode(PIN_A_, OUTPUT);
  pinMode(PIN_B, OUTPUT);
  pinMode(PIN_B_, OUTPUT);
  reset(CLOCKWISE);
  scan = true;
}

void loop() {
  if (scan == STARTED) {    // The motor has been set to rotate
    sensor_out = sensor();
    if (tracking == STARTED) {    // The detector has started receiving input
      if (sensor_out > sensor_max) {
        sensor_max = sensor_out;  // Store the maximum obtained value till now
      } else if (sensor_out < sensor_max / 10) {
        Serial.print("Intensity peak of direct beam: ");
        Serial.print(sensor_max * SENSOR_CONV, 8);
        Serial.print(" V\n");
        tracking = FINISHED;
      }
    } else if (tracking == NOT_STARTED && sensor_out > 0) {
      scan_delay *= 4;            // Slow down the motor for fine tracking
      tracking = STARTED;         // Start tracking
    } else if (tracking == FINISHED && sensor_out == 0) {
      scan = FINISHED;            // We have crossed the LASER spot, stop tracking
      return;
    }
    tick(1, scan_delay, CLOCKWISE, ++stepper_pos);  // Turn the stepper motor by a single step
  } else {
    relax();                      // Release the motor
  }
}

// Turn deg degress at a speed of rpm, in given dir (assumes resetted)
void turn(float deg, float rpm, int dir) {
  int del = (60000 * STEPPER_RES) / (360 * rpm);
  tick(deg / STEPPER_RES, del, dir, 0);
}

void reset(int dir) {
  tick(DRIVER_STEPS, 50, dir, 0);
  delay(1000);
}

// Release the motor by zeroing out all the voltages
void relax() {
  digitalWrite(PIN_A, 0);
  digitalWrite(PIN_A_, 0);
  digitalWrite(PIN_B, 0);
  digitalWrite(PIN_B_, 0);
}

// Rotate the motor for n ticks, separated by del ms, in dir direction, starting
// from the i-th position of the step cycle
void tick(int n, int del, int dir, int i) {
  int j = 0;
  for (; n > 0; --n, i += dir) {
    j = (dir == CLOCKWISE) ? i % DRIVER_STEPS : DRIVER_STEPS + (i-1) % DRIVER_STEPS - 1;
    digitalWrite(PIN_A, get_bit(driver[j], 3));
    digitalWrite(PIN_A_, get_bit(driver[j], 2));
    digitalWrite(PIN_B, get_bit(driver[j], 1));
    digitalWrite(PIN_B_, get_bit(driver[j], 0));
    delay(del);
  }
}

int get_bit(int n, int pos) {
  // n >> i shifts the i-th bit to LSB
  // then Bitwise-and with 1 gives the bit value 
  if ((n >> pos) & 1)
    return HIGH;
  else
    return LOW;
}

int sensor() {
  return analogRead(PIN_SENSOR);
}
