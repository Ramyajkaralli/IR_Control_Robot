#include <IRremote.h>

int MLa = 6;  //Motor left 1st pin
int MLb = 9;  //Motor left 2nd pin
int MRa = 10; //Motor Right 1st pin
int MRb = 11; //Motor Right 2nd pin

unsigned long data;

int RECV_PIN = 4;

void setup() {
  Serial.begin(9600);
  IrReceiver.begin(RECV_PIN);
  pinMode(MLa, OUTPUT);   
  pinMode(MLb, OUTPUT);   
  pinMode(MRa, OUTPUT);   
  pinMode(MRb, OUTPUT);
}

void loop() {
  if (IrReceiver.decode()) {
    data = IrReceiver.decodedIRData.decodedRawData;
    Serial.println(data, HEX);
    // Check if button is held down (repeat code)
    if (data == 0xFFFFFFFF) {
      // Keep the current action (don't change anything)
      data = 0;  // Skip the rest of the loop
    }

    Serial.println(data);
    
    // Move forward when "2" is pressed
    if (data == 0xE718FF00) { // 2 = Forward //0xE41B7F80
      digitalWrite(MLa, HIGH);
      digitalWrite(MLb, LOW);
      digitalWrite(MRa, LOW);
      digitalWrite(MRb, HIGH);
      Serial.println("Moving Forward");
    }
    
    // Move backward when "8" is pressed
    if (data == 0xAD52FF00) { // 8 = Backward //0xF00F7F80
      digitalWrite(MLa, LOW);
      digitalWrite(MLb, HIGH);
      digitalWrite(MRa, HIGH);
      digitalWrite(MRb, LOW);
      Serial.println("Moving Backward");
    }

    // Turn right for 500 milliseconds when "6" is pressed
    if (data == 0xA55AFF00) { // 6 = Right //0xF10E7F80
      digitalWrite(MLa, HIGH);
      digitalWrite(MLb, LOW);
      digitalWrite(MRa, HIGH);
      digitalWrite(MRb, LOW);
      Serial.println("Turning Right");
      delay(500); // Turn for 500 milliseconds
    }

    // Turn left for 500 milliseconds when "4" is pressed
    if (data == 0xF708FF00) { // 4 = Left //0xF30C7F80
      digitalWrite(MLa, LOW);
      digitalWrite(MLb, HIGH);
      digitalWrite(MRa, LOW);
      digitalWrite(MRb, HIGH);
      Serial.println("Turning Left");
      delay(500); // Turn for 500 milliseconds
    }

    // Stop the robot when "5" is pressed
    if (data == 0xE31CFF00) { // 5 = Stop //0xF20D7F80
      digitalWrite(MLa, LOW);
      digitalWrite(MLb, LOW);
      digitalWrite(MRa, LOW);
      digitalWrite(MRb, LOW);
      Serial.println("Stopped");
    }
    
    IrReceiver.resume(); // Ready to receive the next code
  }
}
