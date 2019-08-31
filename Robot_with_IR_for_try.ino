#include <IRremote.h>   //ใช้คำสั่งรีโมท
#include <Servo.h>      //ใช้คำสั่งมอเตอร์เวอร์โว
#define forward  25245 //ประกาศให้ชุดคำสั่งทำงานถ้าค่าที่เข้ามาตรง
#define backward  43095 //ตัวเลขที่ระบุคือเลขของค่าirที่รับมาถ้าตรงกับคำสั่งไหนก็ทำคำสั่งนั้น
#define left  8925
#define right 49725
#define collup  41565
#define colldown  57885

// ขั้วต่อสำหรับมอเตอร์ A 
int EN_A = 13;  
int IN_1 = 12;
int IN_2 = 11;

// ขั้วต่อสำหรับมอเตอร์ B
int EN_B = 8;
int IN_3 = 10;
int IN_4 = 9;

int receiver_pin = 4;   //ขั้วรับค่าจาก IR
int vcc = 5;            //ขั้วจ่ายไฟบวกให้ IR
int gnd = 6;            //ขั้วจ่ายไฟลบให้ IR


int sersep = 20; //ความเร็วของมอเตอรืเซอโว
char command;  //กันBUG
IRrecv receiver(receiver_pin); //ตั้งให้IRเป็นตัวส่งค่า 
decode_results output;//แปลงค่าดิบให้เป็นเลข
Servo myservo;  //เปิดการใช้งานเซอโว

void setup()
{
  Serial.begin(9600); //ตั้งค่าการสื่อสาร
  receiver.enableIRIn();  // เริ่มรับค่า IR
  myservo.attach(7);
  //สั่งค่าให้ทุกขาต่อไปนี้เป็ร output
  pinMode(vcc, OUTPUT);
  pinMode(gnd, OUTPUT);
  pinMode(EN_A, OUTPUT);
  pinMode(EN_B, OUTPUT);
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT);

  
// สั่งค่า + ไปที่ ENA, ENB และ vcc
  digitalWrite(vcc, HIGH);
  digitalWrite(EN_A, HIGH);
  digitalWrite(EN_B, HIGH);
}

void loop() {
  if (receiver.decode(&output)) {      //ถ้ารับค่าได้จะไปถอดรหัส
    unsigned int value = output.value; //ถอดรหัสด้วยการขยับจุดและตัดตัวแปลกๆออก
    
    switch(value) {   //เหมือนif elseค่าที่รับมาตรงตามข้อไหนจะทำข้อนั้น
     
  case forward: 
      //เดินหน้า
  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW); 
  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);
  delay(300);
          break; //ออกจากloopทันที
       
case backward:
      //ถอยหลัง
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH); 
  digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
  delay(300);
         break; //ออกจากloopทันที
       
case left:
       //หันซ้าย
  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, HIGH);

  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, HIGH);
  delay(150);
          break; //ออกจากloopทันที  
        
  case right:
        //หันขวา
  digitalWrite(IN_1, HIGH);
  digitalWrite(IN_2, LOW);

    digitalWrite(IN_3, HIGH);
  digitalWrite(IN_4, LOW);
  delay(150);
          break; //ออกจากloopทันที

   case collup: //คำสั่งยกแขนขึ้น
    myservo.write(120);         
    delay(sersep);
    myservo.write(150);         
    delay(sersep);
    myservo.write(180);         
    delay(sersep);
    myservo.write(210);         
    delay(sersep);
    myservo.write(240);         
    delay(sersep);
    myservo.write(270);         
    delay(sersep);
break;

  case colldown: //คำสั่งยกแขนลง
    myservo.write(240);         
    delay(sersep);
    myservo.write(210);         
    delay(sersep);
    myservo.write(180);         
    delay(sersep);
    myservo.write(150);         
    delay(sersep);
    myservo.write(120);         
    delay(sersep);
    break;
}
    Serial.println(value); //แสดงค่าที่ได้รับออกมาให้เราดู
    receiver.resume(); //ปิดการรับค่า
}
  //พออกจากคำสั่งในเงื่อนไขก็หยุดนิ่ง
  digitalWrite(IN_1, LOW);
  digitalWrite(IN_2, LOW); 
  digitalWrite(IN_3, LOW);
  digitalWrite(IN_4, LOW);
}
