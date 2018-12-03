int h_dis = 50;

int trigPin = 11;
int echoPin_1 = 9;
int echoPin_2 = 10;
int echoPin_3 = 8;

int Enable = 6;
int Step = 13;
int Dir = 12;

int home_up = 2;
int home_down = 3;

int LED = 5;



void setup()
{
  pinMode(trigPin, OUTPUT); //Sensor
  pinMode(echoPin_1, INPUT); //Sensor
  pinMode(echoPin_2, INPUT); //Sensor
  pinMode(echoPin_3, INPUT); //Sensor

  pinMode(Enable, OUTPUT); // Enable
  pinMode(Step, OUTPUT); // Step
  pinMode(Dir, OUTPUT); // Dir

  pinMode(LED, OUTPUT); //LED

  pinMode(home_up, INPUT_PULLUP);
  pinMode(home_down, INPUT_PULLUP);

  digitalWrite(Enable, LOW); // Set Enable low
  digitalWrite(Step, LOW); // Set Step low
  Serial.begin(9600);
    int homed = digitalRead(home_down);
    int homeu = digitalRead(home_up);
    Serial.print (homed);
    Serial.print (",");
    Serial.print (homeu);
    Serial.print (";;;");

  while (digitalRead(home_down) == HIGH) {
    down(100);
    delay(10);
    digitalWrite(Dir, HIGH);
  }

}

void loop()
{
  int dis1, dis2, dis3;
  dis1 = distance(echoPin_1);
  delayMicroseconds(5);
  dis2 = distance(echoPin_2);
  delayMicroseconds(5);
  dis3 = distance(echoPin_3);

  Serial.print (dis1);
  Serial.print ("cm ");
  Serial.print(',');
  Serial.print (dis2);
  Serial.print ("cm ");
  Serial.print(',');
  Serial.print (dis3);
  Serial.print ("cm ");
  Serial.print (";;; ");

  int L = map(dis2, 0, 20, 255, 0);
  //Serial.print (L);
  //Serial.print(',');

 //set mindistance
  float disminp = min(dis1,dis2);
  float dismin = min(disminp,dis3);

  if (dis2 <= h_dis) {
    // digitalWrite(LED, HIGH); // set the LED on
    analogWrite(LED, L);

    delayMicroseconds(2);

    int homed = digitalRead(home_down);
    int homeu = digitalRead(home_up);
    Serial.print (homed);
    Serial.print (",");
    Serial.print (homeu);
    Serial.print (";;;");


      if ( homed == HIGH && homeu == HIGH ) {
      if (digitalRead(Dir) == LOW){
        down(800);
      }
      else if (digitalRead(Dir) == HIGH){
        up(800);
      }
      Serial.print ("A");
      Serial.print (",");
      delayMicroseconds(5);
    }
    else if ( homed == LOW && homeu == HIGH ) {
      up(800);
      Serial.print ("B");
      Serial.print (",");
      delayMicroseconds(5);
    }

    else if ( homed == HIGH && homeu == LOW ) {
      down(800);
      Serial.print ("C");
      Serial.print (",");
      delayMicroseconds(5);
    }

    else if ( homed == LOW && homeu == LOW ) {
      Serial.print ("Warning!");
      Serial.print (",");
      delay(10);
    }

  }



  else if (dis2 > h_dis) {
    digitalWrite(LED, LOW); // set the LED off
    int homed = digitalRead(home_down);
    int homeu = digitalRead(home_up);
    if ( homed == HIGH && homeu == HIGH ) {
      down(500);
      Serial.print ("A");
      Serial.print (",");
      delayMicroseconds(5);
    }
    else if ( homed == LOW && homeu == HIGH ) {
      delay(20);
      digitalWrite(Dir, HIGH);
    }
  }
}//



void up(int MAX)
{
  digitalWrite(Dir, HIGH); // Set Dir high
  for (int x = 0; x < MAX; x++) // Loop n times
  {
    digitalWrite(Step, HIGH); // Output high
    delayMicroseconds(500); // Wait
    digitalWrite(Step, LOW); // Output low
    delayMicroseconds(500); // Wait
  }
}


void down(int MAX)
{
  digitalWrite(Dir, LOW); // Set Dir high
  for (int x = 0; x < MAX; x++) // Loop n times
  {
    digitalWrite(Step, HIGH); // Output high
    delayMicroseconds(500); // Wait
    digitalWrite(Step, LOW); // Output low
    delayMicroseconds(500); // Wait
  }
}

void motorStep( int MAX) {

  for (int x = 0; x < MAX; x++) {
    digitalWrite(Step, HIGH);
    delayMicroseconds(500);
    digitalWrite(Step, LOW);
    delayMicroseconds(500);
  }
}



  float distance(int EchoPin) //distance
  {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    return pulseIn(EchoPin, HIGH, 300000L) / 58.0;
  }
