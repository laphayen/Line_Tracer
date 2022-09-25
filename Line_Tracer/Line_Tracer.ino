// SPAC2 블루투스 무선 구동실험

int Left_motor_back=8;     //좌측모터후진(IN1)
int Left_motor_go=9;     //좌측모터전진(IN2)

int Right_motor_go=10;    // 우측모터전진(IN3)
int Right_motor_back=11;    // 우측모터후진(IN4)

char command; 

void setup()
{
  //모터구동을을 위한 초기화
  pinMode(Left_motor_go,OUTPUT); // PIN 8 (PWM)
  pinMode(Left_motor_back,OUTPUT); // PIN 9 (PWM)
  pinMode(Right_motor_go,OUTPUT);// PIN 10 (PWM) 
  pinMode(Right_motor_back,OUTPUT);// PIN 11 (PWM)
  pinMode(13, OUTPUT);////포트설정 출력

  Serial.begin(9600);  //전송속도9600
}
void run()     // 전진
{
  //digitalWrite(Right_motor_go,HIGH);  //우측모터전진
  //digitalWrite(Right_motor_back,LOW);     
  analogWrite(Right_motor_go,205);//PWM값 0~255 조정,모터의 회전속도 조절.
 analogWrite(Right_motor_back,0);
  //digitalWrite(Left_motor_go,HIGH);  //좌측모터전진
  //digitalWrite(Left_motor_back,LOW);
  analogWrite(Left_motor_go,196  );//PWM값 0~255 조정,모터의 회전속도 조절.
  analogWrite(Left_motor_back,0);
  //delay(time * 100);   //딜레이  
}

void brake()         //제동, 정지
{
  digitalWrite(Right_motor_go,LOW);
  digitalWrite(Right_motor_back,LOW);
  digitalWrite(Left_motor_go,LOW);
  digitalWrite(Left_motor_back,LOW);
  //delay(time * 100);//딜레이  
}

void left()         //좌회전(좌측정지，우측직진)
{
  //digitalWrite(Right_motor_go,HIGH);  // 우측모터전진
  //digitalWrite(Right_motor_back,LOW);
  analogWrite(Right_motor_go,200); 
  analogWrite(Right_motor_back,0);//PWM값 0~255 조정,모터의 회전속도 조절.
  //digitalWrite(Left_motor_go,LOW);   //좌측모터정지
  //digitalWrite(Left_motor_back,LOW);
  analogWrite(Left_motor_go,0); 
  analogWrite(Left_motor_back,0);//PWM값 0~255 조정,모터의 회전속도 조절.
  //delay(time * 100);  //딜레이  
}

void spin_left()         //좌측스핀(좌측후진，우측직진)
{
  //digitalWrite(Right_motor_go,HIGH );  // 우측모터전진
  //digitalWrite(Right_motor_back,LOW);
  analogWrite(Right_motor_go,200); 
  analogWrite(Right_motor_back,0);//PWM값 0~255 조정,모터의 회전속도 조절.
  //digitalWrite(Left_motor_go,LOW);   //좌측모터후진
  //digitalWrite(Left_motor_back,HIGH);
  analogWrite(Left_motor_go,0); 
  analogWrite(Left_motor_back,200);//PWM값 0~255 조정,모터의 회전속도 조절.
  //delay(time * 100);  //딜레이  
}

void right()        //우회전(우측정지, 좌측직진)
{
  //digitalWrite(Right_motor_go,LOW);   //우측모터정지
  //digitalWrite(Right_motor_back,LOW);
  analogWrite(Right_motor_go,0); 
  analogWrite(Right_motor_back,0);//PWM값 0~255 조정,모터의 회전속도 조절.
  //digitalWrite(Left_motor_go,HIGH);//좌측모터전진
  //digitalWrite(Left_motor_back,LOW);
  analogWrite(Left_motor_go,200); 
  analogWrite(Left_motor_back,0);//PWM값 0~255 조정,모터의 회전속도 조절.
  //delay(time * 100);  //딜레이  
}

void spin_right()        //우측스핀(우측후진, 좌측전진)
{
  //digitalWrite(Right_motor_go,LOW);   //우측모터후진
  //digitalWrite(Right_motor_back,HIGH);
  analogWrite(Right_motor_go,0); 
  analogWrite(Right_motor_back,200);//PWM값 0~255 조정,모터의 회전속도 조절.
  //digitalWrite(Left_motor_go,HIGH);//좌측모터전진
  //digitalWrite(Left_motor_back,LOW);
  analogWrite(Left_motor_go,200); 
  analogWrite(Left_motor_back,0);//PWM값 0~255 조정,모터의 회전속도 조절.
  //delay(time * 100);  //딜레이  
}

void back()          //후진
{
  digitalWrite(Right_motor_go,LOW);  //우측모터후진
  digitalWrite(Right_motor_back,HIGH);
  //analogWrite(Right_motor_go,0);
  //analogWrite(Right_motor_back,155);//PWM값 0~255 조정,모터의 회전속도 조절.
  digitalWrite(Left_motor_go,LOW);  //좌측모터후진
  digitalWrite(Left_motor_back,HIGH);
  //analogWrite(Left_motor_go,0);
  //analogWrite(Left_motor_back,150);//PWM값 0~255 조정,모터의 회전속도 조절.
  //delay(time * 100);     //딜레이  
}

void loop(){
  if(Serial.available() > 0){ 
    command = Serial.read(); 
    brake(); //initialize with motors stoped
    //Change pin mode only if new command is different from previous.   
    //Serial.println(command);
    switch(command){
    case 'F':  
      run();
      break;
    case 'B':  
       back();
      break;
    case 'L':  
      left();
      break;
    case 'R':
      right();
      break;
     case 'I':
     spin_right();
     break; 
     case 'G':
     spin_left();
     break; 

    }
  } 
}
/*
switch (command) { case 'F':goAhead();break;
case 'B':goBack();break; 
case 'L':goLeft();break; 
case 'R':goRight();break; 
case 'I':goAheadRight();break; 
case 'G':goAheadLeft();break; 
case 'J':goBackRight();break; 
case 'H':goBackLeft();break; 
case '0':speedCar = 100;break; 
case '1':speedCar = 115;break; 
case '2':speedCar = 130;break; 
case '3':speedCar = 145;break; 
case '4':speedCar = 160;break; 
case '5':speedCar = 175;break; 
case '6':speedCar = 190;break; 
case '7':speedCar = 205;break; 
case '8':speedCar = 220;break; 
case '9':speedCar = 235;break; 
case 'q':speedCar = 255;break; 
case 'W':lightFront = true;break; 
case 'w':lightFront = false;break; 
case 'U':lightBack = true;break;
case 'u':lightBack = false;break; 
case 'V':horn = true;break; 
case 'v':horn = false;break;

}*/
