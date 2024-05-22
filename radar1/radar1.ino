// Define ultrasonic sensor pins
const int trigPin = 12;
const int echoPin = 13;
char curr = 1;
int dist;
// Variables to store distance and duration
float distance;
long duration;

void displayDigit(int number, int digitPin) {
  // Initialize segment pins as outputs
  const int segmentPins[] = {5, 6, 7, 8, 9, 10, 11};

  for (int i = 0; i < 7; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }

  // Clear all segment pins
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], LOW);
  }

  // Turn off the digit pin to disable the segment pins
  for (int i = 1; i < 5; i++) {
        digitalWrite(i, HIGH);
      }

  // Determine which segments to turn on based on the input number
  switch (number) {
    case 0:
      for (int i = 0; i < 7; i++) {
        digitalWrite(segmentPins[i], HIGH);
      }
      digitalWrite(segmentPins[6], LOW); // Turn off the decimal point
      break;

    case 1:
      digitalWrite(segmentPins[1], HIGH);
      digitalWrite(segmentPins[2], HIGH);
      break;

    case 2:
      digitalWrite(segmentPins[0], HIGH);
      digitalWrite(segmentPins[1], HIGH);
      digitalWrite(segmentPins[3], HIGH);
      digitalWrite(segmentPins[4], HIGH);
      digitalWrite(segmentPins[6], HIGH);
      break;

    case 3:
      digitalWrite(segmentPins[0], HIGH);
      digitalWrite(segmentPins[1], HIGH);
      digitalWrite(segmentPins[2], HIGH);
      digitalWrite(segmentPins[3], HIGH);
      digitalWrite(segmentPins[6], HIGH);
      break;

    case 4:
      digitalWrite(segmentPins[1], HIGH);
      digitalWrite(segmentPins[2], HIGH);
      digitalWrite(segmentPins[5], HIGH);
      digitalWrite(segmentPins[6], HIGH);
      break;

    case 5:
      digitalWrite(segmentPins[0], HIGH);
      digitalWrite(segmentPins[2], HIGH);
      digitalWrite(segmentPins[3], HIGH);
      digitalWrite(segmentPins[5], HIGH);
      digitalWrite(segmentPins[6], HIGH);
      break;

    case 6:
      digitalWrite(segmentPins[0], HIGH);
      digitalWrite(segmentPins[2], HIGH);
      digitalWrite(segmentPins[3], HIGH);
      digitalWrite(segmentPins[4], HIGH);
      digitalWrite(segmentPins[5], HIGH);
      digitalWrite(segmentPins[6], HIGH);
      break;

    case 7:
      digitalWrite(segmentPins[1], HIGH);
      digitalWrite(segmentPins[2], HIGH);
      digitalWrite(segmentPins[5], HIGH);
      break;

    case 8:
      for (int i = 0; i < 7; i++) {
        digitalWrite(segmentPins[i], HIGH);
      }
      break;

    case 9:
      digitalWrite(segmentPins[0], HIGH);
      digitalWrite(segmentPins[1], HIGH);
      digitalWrite(segmentPins[2], HIGH);
      digitalWrite(segmentPins[3], HIGH);
      digitalWrite(segmentPins[5], HIGH);
      digitalWrite(segmentPins[6], HIGH);
      break;

    default:
      // Display blank
      break;
  }

  Serial.println(digitPin);
    Serial.println("HEREHEREHERE");
  // Set the digit pin to high to enable the selected segment pins
  digitalWrite(digitPin, LOW);

  // Delay for a short period to allow the display to update
  //delay(10);

}



void setup() {
  // Start serial communication
  Serial.begin(9600);

  // Define trigPin as an OUTPUT
  pinMode(trigPin, OUTPUT);
  // Define echoPin as an INPUT
  pinMode(echoPin, INPUT);
  curr=1;
}

void loop() {
  // Generate a pulse for the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the duration of the pulse from the echoPin
  duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in centimeters
  distance = (duration * 0.0343) / 2;

  // Print the distance to the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Convert distance to integer to ignore decimals
  dist = int(distance);

  //displayDigit(0, 4);
  //displayDigit(dist%10, 4);
  displayDigit(0, 3);
  //displayDigit(1, 1);

  // Debug statement to see the value of curr
  Serial.print("curr: ");
  Serial.println(curr);

  // Debug statement to see the value of dist
  Serial.print("dist: ");
  Serial.println(dist);

  // Increase the delay if needed to control the display speed
  delay(100); // Increase the delay to see if the issue persists
}

