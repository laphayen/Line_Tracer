#include <IRremote.h>				//IR리모컨라이브러리
 		//IR Recv (IR Receiver): 적외선 수신기
int RECV_PIN = A4;					//포트설정: 적외선 수신기가 받은 값을 A4핀에서 받는다
IRrecv irrecv(RECV_PIN);				//IRrecv 클래스 선언. 해당 클래스에서 리모컨 수신 처리
decode_results results;				//적외선 수신기 초기화: 수신 데이터를 result 변수에 저장
						  ( IRremote.h 파일에 선언되어 있는 구조체)
int on = 0;					//플래그(수신 데이터의 존재여부 표시)
unsigned long last = millis( );				//양수 long타입 변수 last 선언 및 시간 저장
//millis( ): 프로그램을 시작한 이후 경과한 시간을 ms 초 단위로 반환. 약 50일 이후 오버플로가 발생하여 0이 됨

//리모컨 버튼에 이름 붙이기
long run_car = 0x00FF18E7;				//2번 버튼: 전진
long back_car = 0x00FF4AB5;				//8번 버튼: 후진
long left_car = 0x00FF10EF;				//4번 버튼: 왼쪽
long right_car = 0x00FF5AA5;			//6번 버튼: 오른쪽
long stop_car = 0x00FF38C7;				//5번 버튼: 정지
long left_turn = 0x00ff30CF;				//1번 버튼: 왼쪽으로 회전
long right_turn = 0x00FF7A85;			//3번 버튼: 오른쪽으로 회전

//모터(motor)와 연결된 핀 지정: 속도 조절을 위해서 PWM(펄스폭변조)을 지원하는 핀과 연결
int Left_motor_back=8;    	 //좌측모터후진(IN1)
int Left_motor_go=9;    	 //좌측모터전진(IN2)

int Right_motor_go=10;      // 우측모터전진(IN3)
int Right_motor_back=11;    // 우측모터후진(IN4)

void setup( )
{
  //모터 구동을을 위한 입출력 초기화: LED처럼, 모터는 아두이노로부터 출력값만 받음.
  pinMode(Left_motor_go, OUTPUT); 			// PIN 8 (PWM)
  pinMode(Left_motor_back, OUTPUT);			// PIN 9 (PWM)
  pinMode(Right_motor_go, OUTPUT);			// PIN 10 (PWM) 
  pinMode(Right_motor_back, OUTPUT);		// PIN 11 (PWM)
  pinMode(13, OUTPUT);				// 포트설정 출력 (리모컨 신호를 받으면 불이 들어옴)

  irrecv.enableIRIn(); 				// Start the receiver (리모컨 수신 개시)
}

//전진 함수
void run()     					// 전진 함수-좌우의 전진하는 모터만 HIGH상태로
{
  digitalWrite(Right_motor_go,HIGH);  		//우측모터전진: HIGH
  digitalWrite(Right_motor_back,LOW);     		
  digitalWrite(Left_motor_go,HIGH);  			//좌측모터전진: HIGH
digitalWrite(Left_motor_back,LOW);			
analogWrite(Right_motor_go, 70);			//우측전진모터 속도 설정
analogWrite(Left_motor_go, 77.75);			//좌측전진모터 속도 설정
}

//정지 함수
void brake()         				// 제동·정지 함수 – 모든 모터를 LOW상태로
{
  digitalWrite(Right_motor_go,LOW);
  digitalWrite(Right_motor_back,LOW);
  digitalWrite(Left_motor_go,LOW);
  digitalWrite(Left_motor_back,LOW);
}

//좌회전 함수
void left()         					//좌회전(좌측정지，우측직진)
{
  digitalWrite(Right_motor_go,HIGH); 			//우측모터전진
  digitalWrite(Right_motor_back,LOW);
  digitalWrite(Left_motor_go,LOW);   			//좌측모터정지
digitalWrite(Left_motor_back,LOW);
analogWrite(Right_motor_go, 70);			//우측전진모터 속도 설정
}

//좌측 스핀 함수
void spin_left()        				//좌측스핀(좌측후진，우측직진)
{
  digitalWrite(Right_motor_go,HIGH);			//우측모터전진
  digitalWrite(Right_motor_back,LOW);
  digitalWrite(Left_motor_go,LOW);   			//좌측모터후진
digitalWrite(Left_motor_back,HIGH);
analogWrite(Right_motor_go, 70);			//우측전진모터 속도 설정
analogWrite(Left_motor_back, 70);			//좌측후진모터 속도 설정
}
//우회전 함수
void right()       					 //우회전(우측정지, 좌측직진)
{
  digitalWrite(Right_motor_go,LOW);   		//우측모터정지
  digitalWrite(Right_motor_back,LOW);
  digitalWrite(Left_motor_go,HIGH);			//좌측모터전진
digitalWrite(Left_motor_back,LOW);
analogWrite(Left_motor_go, 70);			//좌측 전진모터 속도 설정
}

//우측 스핀 함수
void spin_right()       				//우측스핀(우측후진, 좌측전진)
{
  digitalWrite(Right_motor_go,LOW); 			//우측모터후진
  digitalWrite(Right_motor_back,HIGH);
  digitalWrite(Left_motor_go,HIGH); 			//좌측모터전진
digitalWrite(Left_motor_back,LOW);
analogWrite(Left_motor_go, 70); 			//좌측전진모터 속도 설정
analogWrite(Right_motor_back, 70);			//우측후진모터 속도 설정
}

//후진 함수
void back()          				//후진 – 좌우의 후진하는 모터만 HIGH 상태로
{
  digitalWrite(Right_motor_go,LOW);
  digitalWrite(Right_motor_back,HIGH);
  digitalWrite(Left_motor_go,LOW);
digitalWrite(Left_motor_back,HIGH);
analogWrite(Right_motor_back, 70);			//우측후진모터 속도 설정
analogWrite(Left_motor_back, 70);			//좌측후진모터 속도 설정
}

// Dump함수(출력함수)
// dump
①	컴퓨터 내부에 기억된 내용을 외부로 내보낸다
②	컴퓨터로 어떤 장애가 발생했을 때, 그 상태를 표시하기 위해서 주기억 장치의 내용을 표시하거나 프로그램의 디버그를 위하여 프로그램의 내용을 표시하는 것을 말한다.
void dump(decode_results *results)			// 수신 데이터를 함수의 매개변수로 받아서
{
int count = results->rawlen;

  if (results->decode_type == UNKNOWN) 		// 수신 데이터의 디코딩 타입을 알 수 없는 경우 정지
    brake( );					// 즉, 수신 데이터의 디코딩 결과가 위 7가지 경우에
}						  해당하지 않는 경우 일단 정지 (예외처리: 7, 9버튼)

void loop()
{
//리모컨의 신호를 받으면, 아두이노 우노의 13번 LED가 켜지게 하는 함수
if ( irrecv.decode(&results) ) 			// IR리모컨 라이브러리 호출 (입력받은 값이 있으면)
						//* irrecv.decode(&results): 입력되는 리모컨 데이터 디코딩
  {
     if (millis( ) - last > 250) 			//수신신호 결정 ( 켜 진지 0.25초가 지났다면 )
    {
      on = !on;					//수신신호 반전 ( 0을 반전시키면 1(=true) )
      digitalWrite(13, on ? HIGH : LOW);		//수신신호를 LED(13)로 표시, (삼항연산자)
						//13번 핀이 받은 값이 1(true)이면 HIGH, 0이면 LOW
      dump(&results);				// 수신데이터를 디코딩한 결과(result)를 출력.
    }
	//result.value(result의 결과값)에 따라 함수 실행
    if (results.value == run_car )			// result.value가 2번 버튼이면 전진
      run();
    if (results.value == back_car )			// result.value가 8번 버튼이면 후진
      back();
    if (results.value == left_car )			// result.value가 4번 버튼이면 좌회전
      left();
    if (results.value == right_car )			// result.value가 6번 버튼이면 우회전
      right();
    if (results.value == stop_car )			// result.value가 5번 버튼이면 정지
      brake();
    if (results.value == left_turn )			// result.value가 1번 버튼이면 좌측 스핀
      spin_left();
    if (results.value == right_turn )			// result.value가 3번 버튼이면 우측 스핀
      spin_right();
    last = millis();      				// last 변수 초기화
    irrecv.resume(); 				// Receive the next value (다음 신호 수신)
  }
}
