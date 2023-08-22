#define MOSFET 9
#define MAX_BRIGHTNESS 100
#define FADE_SPEED 80

int brightness = 0;

#define PIR_PIN 2

int state = LOW;  
int val = 0;  

void setup() {
  // put your setup code here, to run once:
  pinMode(MOSFET, OUTPUT);

  pinMode(PIR_PIN, INPUT);

  // TurnOn();
  // delay(5000);
  // TurnOff();

  Serial.begin(9600); 
}

void TurnOn() { 
  Serial.println("Turning On.");
  for (int i = 0; i <= MAX_BRIGHTNESS; i++) {
    if (brightness == MAX_BRIGHTNESS) {
      return;
    }
    analogWrite(MOSFET, brightness);
    brightness += 1;
    delay(FADE_SPEED);
  }
}

void TurnOff() {
  Serial.println("Turning Off.");
  for (int i = 0; i < MAX_BRIGHTNESS; i++) {
    if (brightness == 0) {
      return;
    }
    // Serial.print("Writing brightness: ");
    // Serial.println(brightness, DEC);
    analogWrite(MOSFET, brightness);
    brightness -= 1;
    delay(FADE_SPEED);
  }
  analogWrite(MOSFET, 0);
}

void loop() {
  // put your main code here, to run repeatedly:
  val = digitalRead(PIR_PIN);
  if (val == HIGH) {           // check if the sensor is HIGH
    TurnOn();  // turn LED strip ON
    delay(10000);                // delay milliseconds 
    
    if (state == LOW) {
      Serial.println("Motion detected!"); 
      state = HIGH;       // update variable state to HIGH
    }
  } else {
      TurnOff(); // turn LED strip OFF
      delay(200);             // delay 200 milliseconds 
      
      if (state == HIGH){
        Serial.println("Motion stopped!");
        state = LOW;       // update variable state to LOW
    }
  } 
}


