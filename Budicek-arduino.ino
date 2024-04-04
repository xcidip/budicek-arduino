int btn1 = 9;
int btn2 = 8;
bool isIdle = false;

void setup() {
  Serial.begin(9600);
  pinMode(btn1, INPUT);  // Set button 1 pin as input
  pinMode(btn2, INPUT);  // Set button 2 pin as input
  
}

// the loop routine runs over and over again forever:
void loop() {
  int val1 = digitalRead(btn1);
  int val2 = digitalRead(btn2);
  int val3 = 1;
  int val4 = 1;
  if (analogRead(A5) > 530)
  {
    val3 = 0;
    val4 = 0;
  }
  else if(analogRead(A5) > 500)
  {
    val4 = 0;
  }
  else if(analogRead(A5) > 150 && analogRead(A5) < 300)
  {
    val3 = 0;
  }

  Serial.println("------");
  Serial.println(val1);
  Serial.println(val2);
  Serial.println(val3);
  Serial.println(val4);

  if (val1 == 0){
    Serial.println("button 1 is active");
  }
  else if (val2 == 0){
    Serial.println("button 2 is active");
  }
  else if (val3 == 0){
    Serial.println("button 3 is active");
  }
  else if (val4 == 0){
    Serial.println("button 4 is active");
  }

  delay(300);  // delay in between reads for stability
}
