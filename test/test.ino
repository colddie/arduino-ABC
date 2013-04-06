const int ledPin = 13; // the pin that the LED is attached to

void setup()
{
// initialize the serial communication:
Serial.begin(9600);
// initialize the ledPin as an output:
pinMode(ledPin, OUTPUT);
}

void loop() {
byte brightness;

// check if data has been sent from the computer:
if (Serial.available()) {
// read the most recent byte (which will be from 0 to 255):
brightness = Serial.read();
}
if (brightness == 1)
{
// set the brightness of the LED:
digitalWrite(ledPin, brightness);
delay(5000);
digitalWrite(ledPin, 0);

}
}