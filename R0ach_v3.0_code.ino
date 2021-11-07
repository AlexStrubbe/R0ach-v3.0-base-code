#include <AFMotor.h>
#include <IRremote.h>

#define IR A0                               //Assigning the IR sensor reciever on pin A0

/*Assigns the signal commands to a certain button*/
#define button_fw 96                        
#define button_bw 97                       
#define button_lf 101
#define button_rg 98


IRrecv IRsensor(IR);                        //Assigns variable name for IR sensor

AF_DCMotor motor1(1);                       //This is the left side motor
AF_DCMotor motor2(2);                       //This is the right side motor

int basespeed = 100;                        // Base speed of the motors

void setup() {
  Serial.begin(9600);                       // Begin in serial monitor
  IRsensor.enableIRIn();


  /*Motor Initiation*/
  motor1.setSpeed(basespeed);
  motor2.setSpeed(basespeed);

  motor1.run(RELEASE);
  motor2.run(RELEASE);
}

void loop() {

  if (IrReceiver.decode()) {
    IrReceiver.printIRResultShort(&Serial);           //Prints recieved signal on serial monitor
    IrReceiver.resume();                              //Resumes to recieve the next signal
    Serial.println(IrReceiver.decodedIRData.command); //Used to identify the command for the buttons

    delay(165);                                       //Used to delay the signal input

    motorControll(IrReceiver.decodedIRData.command); 

    if (!IrReceiver.decode()) {                       //If the sensor does not recieve a signal, the 
                                                      //motors stop running
      motor1.run(RELEASE);
      motor2.run(RELEASE);

    }
  }

}

void motorControll(int dir) {
/* The comands may seem contradictory, but it all depends on the direction of the motors on the robot*/
  switch (dir) {
    case button_bw:

      motor1.run(FORWARD);
      motor2.run(FORWARD);
      break;

    case button_fw:

      motor1.run(BACKWARD);
      motor2.run(BACKWARD);
      break;

    case button_rg:

      motor1.run(BACKWARD);
      motor2.run(FORWARD);
      break;

    case button_lf:

      motor1.run(FORWARD);
      motor2.run(BACKWARD);
      break;
  }
}
