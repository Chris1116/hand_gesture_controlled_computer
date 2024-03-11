const int trigger1 = 11; //Trigger pin of 1st Sesnor
const int echo1 = 10; //Echo pin of 1st Sesnor
const int trigger2 = 6; //Trigger pin of 2nd Sesnor
const int echo2 = 5;//Echo pin of 2nd Sesnor

long time_taken;
int dist,distL,distR;

long duration; 
float r;
unsigned long temp=0;
int temp1=0;
int l=0;
void find_distance (void);
void find_distance (void)                   
{ 
  digitalWrite(trigger1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger1, LOW);
  duration = pulseIn(echo1, HIGH, 5000);
  r = 3.4 * duration / 2;                      
  distL = r / 100.00;
   digitalWrite(trigger2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger2, LOW);

  duration = pulseIn(echo2, HIGH, 5000);
  r = 3.4 * duration / 2;     
  distR = r / 100.00;
  delay(100);
}
void setup() {
Serial.begin(9600); 
  
pinMode(trigger1, OUTPUT); 
pinMode(echo1, INPUT); 
pinMode(trigger2, OUTPUT); 
pinMode(echo2, INPUT); 
}

/*###Function to calculate distance###*/
void calculate_distance(int trigger, int echo)
{
digitalWrite(trigger, LOW);
delayMicroseconds(2);
digitalWrite(trigger, HIGH);
delayMicroseconds(10);
digitalWrite(trigger, LOW);

time_taken = pulseIn(echo, HIGH);
dist= time_taken*0.034/2;
if (dist>50)
dist = 50;
}

void loop() { //infinite loopy
calculate_distance(trigger1,echo1);
distL =dist; //get distance of left sensor

calculate_distance(trigger2,echo2);
distR =dist; //get distance of right sensor

//Uncomment for debudding
/*Serial.print("L=");
Serial.println(distL);
Serial.print("R=");
Serial.println(distR);
*/
/*
//Pause Modes -Hold
if ((distL >25 && distR>25) && (distL <40 && distR<40)) //Detect both hands
{Serial.println("Play/Pause"); delay (500);}
*/
if (distL <20 && distR<20) //Detect both hands
{Serial.println("Play/Pause"); delay (500);}

calculate_distance(trigger1,echo1);
distL =dist;

calculate_distance(trigger2,echo2);
distR =dist;
//Control Modes

//Lock Left - Control Mode
if (distL>=10 && distL<=20)
{
  delay(50); //Hand Hold Time
  calculate_distance(trigger1,echo1);
  distL =dist;
  if (distL>=10 && distL<=20)
  {
    Serial.println("Left Locked");
    while(distL<=40)
    {
      calculate_distance(trigger1,echo1);
      distL =dist;
      if (distL<15) //Hand pushed in 
      {Serial.println ("Vup"); delay (300);}
      if (distL>18) //Hand pulled out
      {Serial.println ("Vdown"); delay (300);}
    }
  }
}
//Lock Right - Control Mode
if (distR>=10 && distR<=20)
{
  delay(50); //Hand Hold Time
  calculate_distance(trigger2,echo2);
  distR =dist;
  if (distR>=10 && distR<=20)
  {
    Serial.println("Right Locked");
    while(distR<=40)
    {
      calculate_distance(trigger2,echo2);
      distR =dist;
      if (distR<15 ) //Right hand pushed in
      {Serial.println ("Rewind"); delay (1000);}
      if (distR>18) //Right hand pulled out
      {Serial.println ("Forward"); delay (1000);}
    }
  }
}
//Swipe Next - Control Mode
calculate_distance(trigger2,echo2);
distR =dist;
 if(distR<=5 && distR>=0) 
  { 
    temp=millis();                   
    while(millis()<=(temp+300))     
    find_distance();                              
    {
      Serial.println("next");            
    }
  }
delay(100);

//Swipe Back - Control Mode
calculate_distance(trigger1,echo1);
distL =dist;
 if(distL<=5 && distL>=0) 
  { 
    temp=millis();                   
    while(millis()<=(temp+300))     
    find_distance();                          
    {
      Serial.println("back");             
    }
  }
delay(100);

// Change screen
calculate_distance(trigger1,echo1);
distL =dist;
 if(distL<=40 && distL>=25) 
  { 
    temp=millis();                   
    while(millis()<=(temp+300))     
    find_distance();                          
    {
      Serial.println("change_L"); 
      delay(300);             
    }
  }
delay(100);

calculate_distance(trigger2,echo2);
distR =dist;
 if(distR<=40 && distR>=25) 
  { 
    temp=millis();                   
    while(millis()<=(temp+300))     
    find_distance();                          
    {
      Serial.println("change_R");    
      delay(300);                
    }
  }
delay(100);

}






