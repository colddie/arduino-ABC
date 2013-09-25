const int sigin = 2;
const int ledPin = 2; // the pin that the LED is attached to
int sig_sensor;
int sig_close;

void setup()
{
Serial.begin(9600); //initialisation of the port
pinMode(sigin, INPUT);
pinMode(ledPin, OUTPUT);
}



void loop()
{


sig_sensor = analogRead(sigin);
Serial.write(sig_sensor); //sending of the number
delay(50); //wait 0.1 second


// read the most recent byte (which will be from 0 to 255):
// check if data has been sent from the computer:
if (Serial.available()) {
sig_close = Serial.read();

//sigout = map(sig_close,-50,50,-512,512);

// set the brightness of the LED:
digitalWrite(ledPin, sig_close);
//delay(5000);
//digitalWrite(ledPin, 0);

} 
}