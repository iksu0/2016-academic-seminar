const int GSR = A2;
int threshold;
int sensorValue;
int relay1=2;   
int relay2=3;
int relay3=4;
const int numberOfSamples=50;

void step1();
void step2();
void step3();

void setup() {
  int sum = 0;
  Serial.begin(9600);
  delay(1000);
  for (int i = 0; i < 500; i++){
    sensorValue = analogRead(GSR);
    sum += sensorValue;
    delay(5);
  }
  threshold = sum / 500;                
  pinMode (relay1, OUTPUT); 
  pinMode (relay2, OUTPUT); 
  pinMode (relay3, OUTPUT); 
 

  digitalWrite (relay1, HIGH);
  digitalWrite (relay2, HIGH);
  digitalWrite (relay3, HIGH);
}

void loop() {
  int  temp, sumValue, sensorValue;
  for(int i=0; i<numberOfSamples; i++){
      temp = analogRead(GSR);
      sumValue+=temp;
  }
  sensorValue=sumValue/50;
  Serial.print("sensorValue=");
  Serial.println(sensorValue);
  if(sensorValue>390){
    Serial.println("sensor ready");
  }
  else if(350<sensorValue && sensorValue<390){
    Serial.println("STEP_1----OH MY GOD!!!!!!");
    step1();
  }
  else if(200<sensorValue && sensorValue<350){
    Serial.println("STEP_2----My type");
    step2();
  }
  else if(sensorValue<200){
    Serial.println("STEP_3----I click you");
    step3();
  }
  delay(3000);
}

void step1()
{
  digitalWrite (relay1, LOW); 
  delay (10000);            
  digitalWrite (relay1, HIGH); 
  delay (1000);              
}
void step2()
{
  digitalWrite (relay1, LOW); 
  delay (6000);            
  digitalWrite (relay1, HIGH);
  digitalWrite (relay2, LOW); 
  delay (4000);            
  digitalWrite (relay2, HIGH); 
  delay (1000);          
}

void step3()
{
  digitalWrite (relay1, LOW); 
  delay (6000);            
  digitalWrite (relay1, HIGH);
  digitalWrite (relay3, LOW); 
  delay (4000);            
  digitalWrite (relay3, HIGH); 
  delay (1000);       
}
