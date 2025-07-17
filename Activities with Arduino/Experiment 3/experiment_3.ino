int LEDarray[8] = {3,4,5,6,7,8,9,10};
int Sound = A0;
int Light = A1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(LEDarray[8], OUTPUT);
  pinMode(Sound, INPUT);
  pinMode(Light, INPUT);
  
}

void loop() {
  int Sound_val = analogRead(Sound);
  
  if(Sound_val >= 800) {
    digitalWrite(LEDarray[7],HIGH);
  }
  else{
    digitalWrite(LEDarray[7],LOW);
  }
    
  if(Sound_val>=750) {
    digitalWrite(LEDarray[6],HIGH);
  }
  else{
    digitalWrite(LEDarray[6],LOW);
  }

  if(Sound_val >= 700) {
    digitalWrite(LEDarray[5],HIGH);
  }
  else{
    digitalWrite(LEDarray[5],LOW);
  }
      
  if(Sound_val >= 650) {
    digitalWrite(LEDarray[4],HIGH);
  }
  else{
    digitalWrite(LEDarray[4],LOW);
  }

  int Light_val = analogRead(Light);
  int level = (Light_val/1023)*100;
  
  if(level >= 0) {
    digitalWrite(LEDarray[3],HIGH);
  }
  else{
    digitalWrite(LEDarray[3],LOW);
  }

  if(level >= 5) {
    digitalWrite(LEDarray[2],HIGH);
  }
  else{
    digitalWrite(LEDarray[2],LOW);
  }

  if(level >= 10) {
    digitalWrite(LEDarray[1],HIGH);
  }
  else{
    digitalWrite(LEDarray[1],LOW);
  }

  if(level >= 50) {
    digitalWrite(LEDarray[0],HIGH);
  }
  else{
    digitalWrite(LEDarray[0],LOW);
  }
}
    
