#include <SoftwareSerial.h>
#include <AFMotor.h>

AF_DCMotor motor_L(3);              
AF_DCMotor motor_R(4); 

#define BT_TXD A5
#define BT_RXD A4
SoftwareSerial bluetooth(BT_TXD, BT_RXD);       // TX: A5, RX: A4

char rec_data;
bool rec_chk = false;

int i;
int j;

void setup() {
  Serial.begin(9600);              // PC와의 시리얼 통신속도
  bluetooth.begin(9600);            // 스마트폰 블루투스 통신속도
  Serial.println("Eduino Smart Car Start!");

  // turn on motor
  motor_L.setSpeed(500);              // 왼쪽 모터의 속도   
  motor_L.run(RELEASE);
  motor_R.setSpeed(500);              // 오른쪽 모터의 속도   
  motor_R.run(RELEASE);

}

void loop() {

 if(bluetooth.available()){         // 블루투스 명령 수신
     rec_data = bluetooth.read();
     Serial.write(rec_data);
     rec_chk = true;
  }    

  
 if(rec_data == 'g'){  // 전진, go
     motor_L.run(FORWARD);  motor_R.run(FORWARD);        
  } 
  else if(rec_data == 'b'){ // 후진, back
     motor_L.run(BACKWARD);  motor_R.run(BACKWARD);    
  }
  else if(rec_data == 'l'){ // 좌회전, Go Left
   motor_L.run(RELEASE);  motor_R.run(FORWARD);     
  }
  else if(rec_data == 'r'){ // 우회전, Go Right
    motor_L.run(FORWARD);  motor_R.run(RELEASE);                
  }
  else if(rec_data == 'w'){ // 제자리 회전, Right Rotation
     motor_L.run(BACKWARD);   motor_R.run(FORWARD);      
  }
  else if(rec_data == 'q'){ // 제자리 회전, Left Rotation
      motor_L.run(FORWARD);   motor_R.run(BACKWARD);    
  }
  else if(rec_data == 's'){  } // Stop 

  if(rec_data == 's' ){       // 정지
    if(rec_chk == true){
       for (i=250; i>=0; i=i-20) {
          motor_L.setSpeed(i);  motor_R.setSpeed(i);  
          delay(10);
       }  
       motor_L.run(RELEASE);       motor_R.run(RELEASE);
    }
  }
  else{
    if(rec_chk == true){
      if(rec_data == 'l'){  // Left
        for (i=20; i<200; i=i+10) {
          motor_L.setSpeed(i);  motor_R.setSpeed(i);
          delay(30);
        }
       }
       else if(rec_data == 'r'){       // Right
        for (i=20; i<200; i=i+10) {
          motor_L.setSpeed(i);  motor_R.setSpeed(i);
          delay(30);
        }
       }
       else if(rec_data == 'w' || rec_data == 'q'){ // Rotation Left, Right
        for (i=0; i<250; i=i+20) {
          motor_L.setSpeed(i);  motor_R.setSpeed(i);  
          delay(20);
        }
       }
       else if(rec_data == 'g'){ //Go
        for (i=0; i<250; i=i+20) { 
           motor_L.setSpeed(i);  motor_R.setSpeed(i);  
          delay(10);   
        }
       }
       else{
        for (i=0; i<250; i=i+20) { //  Back
           motor_L.setSpeed(i);  motor_R.setSpeed(i);  
          delay(10);                         
        }
       }
     }
    else{     
          motor_L.setSpeed(250);  motor_R.setSpeed(250);  
    }
  }
  rec_chk = false;
}
