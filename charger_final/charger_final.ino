#include <TM1637Display.h>

TM1637Display display(2,3);

#define ptn A0  //potentiometer
#define btn 4  //touch sensor //push button can be used instead //active high
#define relay 5  //relay  //active low      

float on_cycle=25; //minute
float off_cycle=5;  //minute

float delay_unit=1000;  //1000ms=1s
int inp;  //input from potentiometer

void setup() 
{
  Serial.begin(9600);
  pinMode(ptn,INPUT);
  pinMode(btn,INPUT);
  pinMode(relay,OUTPUT);

  pinMode(LED_BUILTIN,OUTPUT);  //turn of led_builtin which is on by default
  digitalWrite(LED_BUILTIN,LOW);

  display.setBrightness(7);
  digitalWrite(relay,HIGH);

  int ar1=analogRead(ptn); //Analog Read
  inp=ar1/93.1; //this gives 0,1,...,11 to inp
  inp=(inp+2)*10; //this gives 20,30,...120 to input
  while(digitalRead(btn)==LOW)
  {
    int ar2=analogRead(ptn);
    if(abs(ar2-ar1)>93.1) //because of jumps and bounces in analog read of potentiometer, 
    //if difference between last confirmed analogread is more than a certain treshold(93.1 here)
    //we have next confirmed read, if you dont use this software smoothing, you get a jumpy read that
    //bounces between different values without changing the potentiometer 
    {
      inp=ar2/93.1;
      inp=(inp+2)*10;
      ar1=ar2;
    }

    display.showNumberDec(inp);
    delay(10);
  }

  display_8888();

  if(digitalRead(btn)==HIGH)
  {
    display.showNumberDec(8888);
    delay(delay_unit);  //if user wants to have initial relax, his hand is on touch sensor(or push button)
    //if i dont make this delay, after relax phase is executed(relax function), instead of displayig 8888
    //remaining time will be displayed which is not good, because at first i want to see 8888 which confirms 
    //initial relaxation
    relax(off_cycle);
  }
}

int alfa=1;   //timer //elapsed time in total
int beta=1;   //elapsed time in on_cycle 
int landa=on_cycle*60;

void loop() 
{
  digitalWrite(relay,LOW);
  beta=beta%landa;

  while(alfa<=inp*60 && beta<=on_cycle*60)
  {
    if(digitalRead(btn)==HIGH)
    {
      int show_time_delay=2.0;
      int panta=on_cycle*60-beta+1;
      int show_time_actual=min(show_time_delay,panta);  //exmple: if show_time_delay is 2 seconds and 1 second 
      //of on_cycle phase remains, show_time would be displayed 1 seconds,not 2 seconds, it ensures exact on_cycle
      show_time(show_time_actual);
      alfa+=show_time_actual;
      beta+=show_time_actual;
    }    
    else
    {
      alfa++;
      beta++;
      delay(delay_unit);
    }
  }

  if(alfa<=inp*60)
  {
    relax(off_cycle);
  }
  else
  {
    digitalWrite(relay,HIGH);
    while(1)
    {
      delay(1000);
    }
  }
}

void relax(float off)
{
    digitalWrite(relay,HIGH);

    int teta=0;
    display.showNumberDec(8888);

    while(teta<off*60)
    {
      if(digitalRead(btn)==HIGH)
      {
        int show_time_delay=2;
        int panta=off*60-teta;
        int show_time_actual=min(show_time_delay,panta);//exmple: if show_time_delay is 2 seconds and 1 second 
        //of off_cycle phase remains, show_time would be displayed 1 seconds,not 2 seconds, it ensures exact off_cycle
        show_time(show_time_actual);  
        teta+=show_time_actual;
        display.showNumberDec(8888);
      }
      else
      {
        teta++;
        delay(delay_unit);
      }
    }
    display.clear();
}

void show_time(float del)  //del: delay of show_time in seconds (s)
{
  int remaining_time=ceil((inp*60-alfa)/60);
  display.showNumberDec(remaining_time);
  delay(del*delay_unit);
  display.clear();
}

void display_8888()
{
  display.showNumberDec(8);
  delay(delay_unit);
  display.showNumberDec(88);
  delay(delay_unit);
  display.showNumberDec(888);
  delay(delay_unit);
  display.showNumberDec(8888);
  display.clear();
}