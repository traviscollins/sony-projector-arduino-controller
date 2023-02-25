// The arduino pin to use for detecting input voltage from the amplifier
// MUST USE A 12v to 5v circuit! Do not connect directly from amplifier!
int inPin = 7;

// Holds the prior state;
int pastVal = 0;

void setup() {
  
  pinMode(LED_BUILTIN, OUTPUT);

  // Start serial port
  // must match projector settings
  // 38400 and SERIAL_8E1 are common sony projector defaults
  Serial.begin(38400, SERIAL_8E1);

  // sets the digital pin 7 as input
  pinMode(inPin, INPUT);   

  // Read once at startup to set initial state
  // But take no action. Keeps a restarting arduino
  // from randomly turning projector on and off 
  // when the arduino restarts for whatever reason
  pastVal = digitalRead(inPin);

  if(pastVal == 1)
    digitalWrite(LED_BUILTIN, HIGH);
  else 
    digitalWrite(LED_BUILTIN, LOW);

}

void loop() {

  // To protect against "quickly flagging" input
  delay(500);

  // Pull from the buffer, but do nothing with it
  while(Serial.available() > 0) {
    Serial.read();
  }

  // read the input pin
  int currentVal = digitalRead(inPin);

  // Handle change
  if(currentVal != pastVal) {

    if(currentVal == 1) 
        turnOnProjector();
    else 
        turnOffProjector();

    // Update state with new state   
    pastVal = currentVal;
  }



}


void turnOnProjector() {
  digitalWrite(LED_BUILTIN, HIGH);
  Serial.write("power \"on\"\r\n");
}

void turnOffProjector() {
  digitalWrite(LED_BUILTIN, LOW);
  Serial.write("power \"off\"\r\n");
}
