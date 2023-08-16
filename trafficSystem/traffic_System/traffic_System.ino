#define RedOne 2
#define GreenOne 3
#define RedTwo 4
#define GreenTwo 5
#define irOne 6
#define irTwo 7

unsigned long prev = 0;
unsigned long cur = 0;

int time = 10;

int roadOne = 0, roadTwo =1;

void setup() {
  pinMode(RedOne,OUTPUT);
  pinMode(GreenOne,OUTPUT);
  pinMode(RedTwo,OUTPUT);
  pinMode(GreenTwo,OUTPUT);
  pinMode(irOne,INPUT);
  pinMode(irTwo,INPUT);
  Serial.begin(9600);

}

void loop() {

  cur = millis();
  int sensorValueOne = digitalRead(irOne);
  int sensorValueTwo = digitalRead(irTwo);

  if(cur-prev>=1000){
    if(time>6){
      if(sensorValueOne==HIGH && roadTwo== 0){
        time = 10;
      }else if(sensorValueTwo==HIGH && roadOne== 0){
        time = 10;
      }
    }
    
    if(time==10){
      if(roadTwo==1 && roadOne == 0){
        roadOneSystem();
      }else if(roadTwo==0 && roadOne == 1){
        roadTwoSystem();
      }
      time = 0;
    }
    Serial.println(time);
    prev=cur;
    time++;
  }
}

void roadOneSystem(){
  digitalWrite(GreenOne,HIGH);
  digitalWrite(RedOne,LOW);
  digitalWrite(RedTwo,HIGH);
  digitalWrite(GreenTwo,LOW);
  roadOne = 1;
  roadTwo = 0;
}

void roadTwoSystem(){
  digitalWrite(RedOne,HIGH);
  digitalWrite(GreenOne,LOW);
  digitalWrite(RedTwo,LOW);
  digitalWrite(GreenTwo,HIGH);
  roadOne = 0;
  roadTwo = 1;
}
