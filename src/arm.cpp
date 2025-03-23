///////////////////////////////////////////////////////////////////////////////
/*                                                                           */
/*                                 Arm                                       */
/*                                v0.1                                       */
///////////////////////////////////////////////////////////////////////////////
/*

-Nicodemus Phaklides

Description: Provides general global variables and functions for the robotic arm
             

Changelog 
v0.1:
- Initial release


*/
///////////////////////////////////////////////////////////////////////////////
/*                                                                           */
/*                              INCLUDES                                     */
/*                                                                           */
///////////////////////////////////////////////////////////////////////////////

#include <Arduino.h>
#include "arm.hpp"
#include <Servo.h>
#include <Encoder.h>


/*

 ██████  ██       ██████  ██████   █████  ██      ███████ 
██       ██      ██    ██ ██   ██ ██   ██ ██      ██      
██   ███ ██      ██    ██ ██████  ███████ ██      ███████ 
██    ██ ██      ██    ██ ██   ██ ██   ██ ██           ██ 
 ██████  ███████  ██████  ██████  ██   ██ ███████ ███████ 
                                                          
                                                        
*/

double joint_limits[7][2] = {
    {-150, 180},
    {-15, 128},
    {-120, 120},
    {-90, 90},
    {-180, 180},
    {-110, 180},
    {-110, 110}
};


// Axis
Actuator axis1(PIN_AXIS_1_DIR, PIN_AXIS_1_PWM);
Actuator axis2(PIN_AXIS_2_DIR, PIN_AXIS_2_PWM);
Actuator axis3(PIN_AXIS_3_DIR, PIN_AXIS_3_PWM);
Actuator axis4(PIN_AXIS_4_DIR, PIN_AXIS_4_PWM);
Actuator axis5(PIN_AXIS_5_DIR, PIN_AXIS_5_PWM);

// Grip
Actuator axisGrip(PIN_GRIP_DIR, PIN_GRIP_PWM);

// Translational Platform
Actuator axisTrans(PIN_TRANS_DIR, PIN_TRANS_PWM);


Actuator* axis[7] = {&axis1, &axis2, &axis3, &axis4, &axis5, &axisGrip, &axisTrans};


//Encoder
Encoder axis1Enc(PIN_AXIS_1_A, PIN_AXIS_1_B);
Encoder axis2Enc(PIN_AXIS_2_A, PIN_AXIS_2_B);
Encoder axis3Enc(PIN_AXIS_3_A, PIN_AXIS_3_B);
Encoder axis4Enc(PIN_AXIS_4_A, PIN_AXIS_4_B);
Encoder axis5Enc(PIN_AXIS_5_A, PIN_AXIS_5_B);
Encoder axisGripEnc(PIN_GRIP_A, PIN_GRIP_B);
Encoder axisTransEnc(PIN_TRANS_A, PIN_TRANS_B);

Encoder* encoder[7] = {&axis1Enc, &axis2Enc, &axis3Enc, &axis4Enc, &axis5Enc, &axisGripEnc, &axisTransEnc};

//Joints
Joint joint1;
Joint joint2;
Joint joint3;
Joint joint4;
Joint joint5;
Joint jointGrip;
Joint jointTrans;

Joint* joint[7] = {&joint1, &joint2, &joint3, &joint4, &joint5, &jointGrip, &jointTrans};

double inputCurrent;
double temp;


axisDirection_t getOppositeDir(axisDirection_t dir) {
  switch (dir) {
    case DIR_PLUS:
      return DIR_MINUS;
      break;
    case DIR_MINUS:
      return DIR_PLUS;
      break;
    default:
      return DIR_OFF;
      break;
  }
}


/*

██ ███    ██ ██ ████████ 
██ ████   ██ ██    ██    
██ ██ ██  ██ ██    ██    
██ ██  ██ ██ ██    ██    
██ ██   ████ ██    ██    
                         
                         
*/
void arm_init() {

  pinMode(PIN_RX_ESP, INPUT);
  pinMode(PIN_TX_ESP, OUTPUT);
  pinMode(PIN_TRANS_SW, INPUT);
  pinMode(PIN_AXIS_1_A, INPUT);
  pinMode(PIN_AXIS_1_B, INPUT);
  pinMode(PIN_AXIS_2_A, INPUT);
  pinMode(PIN_AXIS_2_B, INPUT);
  pinMode(PIN_AXIS_3_A, INPUT);
  pinMode(PIN_AXIS_3_B, INPUT);
  pinMode(PIN_FAN_PWM, OUTPUT);
  pinMode(PIN_AXIS_4_A, INPUT);
  pinMode(PIN_AXIS_4_B, INPUT);
  pinMode(PIN_AXIS_5_A, INPUT);
  pinMode(PIN_AXIS_4_PWM, OUTPUT);
  pinMode(PIN_AXIS_5_PWM, OUTPUT);
  pinMode(PIN_GRIP_PWM, OUTPUT);
  pinMode(PIN_AXIS_4_DIR, OUTPUT);
  pinMode(PIN_AXIS_4_SW, INPUT);
  pinMode(PIN_TRANS_PWM, OUTPUT);
  pinMode(PIN_AXIS_5_DIR, OUTPUT);
  pinMode(PIN_AXIS_5_SW, INPUT);
  pinMode(PIN_GRIP_DIR, OUTPUT);
  pinMode(PIN_GRIP_SW, INPUT);
  pinMode(PIN_TRANS_DIR, OUTPUT);
  pinMode(PIN_AXIS_5_B, INPUT);
  pinMode(PIN_GRIP_A, INPUT);
  pinMode(PIN_CURRENT_SENSE, INPUT);
  pinMode(PIN_BUZZER, INPUT);
  pinMode(PIN_GRIP_B, INPUT);
  pinMode(PIN_TRANS_A, INPUT);
  pinMode(PIN_TRANS_B, INPUT);
  pinMode(PIN_AXIS_3_SW, INPUT);
  pinMode(PIN_DISABLE, OUTPUT);
  pinMode(PIN_AXIS_1_PWM, OUTPUT);
  pinMode(PIN_AXIS_1_DIR, OUTPUT);
  pinMode(PIN_AXIS_1_SW, INPUT);
  pinMode(PIN_AXIS_2_PWM, OUTPUT);
  pinMode(PIN_AXIS_3_PWM, OUTPUT);
  pinMode(PIN_AXIS_2_DIR, OUTPUT);
  pinMode(PIN_AXIS_2_SW, INPUT);
  pinMode(PIN_AXIS_3_DIR, OUTPUT);
  pinMode(PIN_TEMP, INPUT);

  joint1.init(0, PIN_AXIS_1_SW);
  joint2.init(1, PIN_AXIS_2_SW);
  joint3.init(2, PIN_AXIS_3_SW);
  joint4.init(3, PIN_AXIS_4_SW);
  joint5.init(4, PIN_AXIS_5_SW);
  jointGrip.init(5, PIN_GRIP_SW);
  jointTrans.init(6, PIN_TRANS_SW);


  axis2.inverted = true;
  
  

}

/*

██████  ██ ██████      ███████ ██    ██ ███    ██  ██████ ████████ ██  ██████  ███    ██ ███████ 
██   ██ ██ ██   ██     ██      ██    ██ ████   ██ ██         ██    ██ ██    ██ ████   ██ ██      
██   ██ ██ ██████      █████   ██    ██ ██ ██  ██ ██         ██    ██ ██    ██ ██ ██  ██ ███████ 
██   ██ ██ ██   ██     ██      ██    ██ ██  ██ ██ ██         ██    ██ ██    ██ ██  ██ ██      ██ 
██████  ██ ██   ██     ██       ██████  ██   ████  ██████    ██    ██  ██████  ██   ████ ███████ 
                                                                                                                                                                                                                                                                                      
*/

float dirToFloat(axisDirection_t dir) {
    switch (dir) {
    case DIR_PLUS:
      return 1.0F;
      break;
    case DIR_MINUS:
      return -1.0F;
      break;
    default:
      return 0;
      break;
  }
}

axisDirection_t floatToDir(float val) {
    if (val > 0) { return DIR_PLUS;}
    else if (val < 0) {return DIR_MINUS;}
    else {return DIR_OFF;}
}

/*

 █████   ██████ ██    ██  █████  ████████  ██████  ██████       ██████ ██       █████  ███████ ███████ 
██   ██ ██      ██    ██ ██   ██    ██    ██    ██ ██   ██     ██      ██      ██   ██ ██      ██      
███████ ██      ██    ██ ███████    ██    ██    ██ ██████      ██      ██      ███████ ███████ ███████ 
██   ██ ██      ██    ██ ██   ██    ██    ██    ██ ██   ██     ██      ██      ██   ██      ██      ██ 
██   ██  ██████  ██████  ██   ██    ██     ██████  ██   ██      ██████ ███████ ██   ██ ███████ ███████ 
                                                                                                       
                                                                                                       
*/
void Actuator::runMotor(axisDirection_t dir, uint8_t speed) {
  speed_ = speed;
  dir_ = dir;

  if (inverted) {dir_ = getOppositeDir(dir);}
  

    switch (dir_) {
        case DIR_OFF:
            digitalWrite(dir_pin_, LOW);
            analogWrite(pwm_pin_, 0);
            break;
        case DIR_PLUS:
            digitalWrite(dir_pin_, HIGH);
            analogWrite(pwm_pin_, speed);
            break;
        case DIR_MINUS:
            digitalWrite(dir_pin_, LOW);
            analogWrite(pwm_pin_, speed);
            break;
        default:
            break;
    }
}

int Actuator::getVelocity() {
  return speed_ * dirToFloat(dir_);
}

  
  /*
  
     ██  ██████  ██ ███    ██ ████████      ██████ ██       █████  ███████ ███████ 
     ██ ██    ██ ██ ████   ██    ██        ██      ██      ██   ██ ██      ██      
     ██ ██    ██ ██ ██ ██  ██    ██        ██      ██      ███████ ███████ ███████ 
██   ██ ██    ██ ██ ██  ██ ██    ██        ██      ██      ██   ██      ██      ██ 
 █████   ██████  ██ ██   ████    ██         ██████ ███████ ██   ██ ███████ ███████ 
                                                                                                                                                                      
*/

void Joint::init(uint8_t index, uint8_t sw_pin) {
  index_ = index;
  sw_pin_ = sw_pin;

  // Construct PI
  pid = new PID(&jointAngle, &control, &setpoint, kp, kd, ki, DIRECT);

  // Set output limits
  pid->SetOutputLimits(-255, 255);
  pid->SetSampleTime(10);



}

void Joint::setControl(bool control) {
  if (control) {
    pid->SetMode(AUTOMATIC);
  }
  else {
    pid->SetMode(MANUAL);
  }
}

void Joint::update() {
  int velocity3;
  int velocity4;



  //Update encoder position based, motor status, and switch status
  switch (index_) {
    case 3:
      encPos_ = encoder[3]->read()-encoder[4]->read() - encPosOffset_;
      break;
    case 4:
      encPos_ = encoder[3]->read()+encoder[4]->read() - encPosOffset_;
      velocity3 = constrain(joint4.getVelocity() + joint5.getVelocity(), -255, 255);
      velocity4 = constrain(-joint4.getVelocity() + joint5.getVelocity(), -255, 255);


      axis[3]->runMotor(floatToDir(velocity3), abs(velocity3));
      axis[4]->runMotor(floatToDir(velocity4), abs(velocity4));
      

      break;
    default:
      encPos_ = encoder[index_]->read();
      if (axis[index_]->inverted) {
        encPos_ *= -1;
      }
      
      encPos_ -= encPosOffset_;

      axis[index_]->runMotor(dir_,speed_);

      break;
  }

}



void Joint::setSpeed(uint8_t speed, axisDirection_t dir) {
  speed_ = speed;
  dir_ = dir;
}

uint8_t Joint::getIndex() {
  return index_;
}

int Joint::getVelocity() {
  return speed_ * dirToFloat(dir_);
}

int Joint::getSpeed() {
  return speed_;
}

bool Joint::getLimit() {
  switchState_ = !digitalRead(sw_pin_);
  return switchState_;
}

axisDirection_t Joint::getDir() {
  axisDirection_t dir_;
}

int Joint::getEncPos() {
  return encPos_;
}

void Joint::zero(int offset = 0) { 
  encPosOffset_ = encPos_ + offset;
}

double Joint::getAngle() {
  return ((double)encPos_) / gearRatios[index_];
}

void getJointAngles() {
  for (uint8_t i = 0; i < 7; i++) {
    switch (i) {
      case 2:
        joint[i]->jointAngle = (joint[2]->getAngle() - joint[1]->getAngle());
        break;
      case 3:
        joint[i]->jointAngle = (joint[3]->getAngle() - joint[2]->getAngle());
        break;
      default:
        joint[i]->jointAngle = joint[i]->getAngle();
        break;
    }
  }
}




// Sensor Functions
void getSensors() {

  //Current sense

  inputCurrent = (((analogRead(PIN_CURRENT_SENSE)/1023.0*3.3)/100.0)/(0.0015));

  //ERT-J1VG103FA NTC Thermistor
  //Beta = 3380K
  //R0 = 10kOhm
  //T0 = 25C = 298.15 K
  float Temp_V = analogRead(PIN_TEMP)*(3.3)/(1023);
  float Temp_R = Temp_V/((3.3-Temp_V)/10000);
  float Temp_K = 3380/(log(Temp_R/(10000*exp(-3380/298.15))));
  temp = (Temp_K-273.15)*(9.0/5.0)+32; //Fahrenheit

}


void enablePID() {
  for (uint8_t i = 0; i < 7; i++) {
    joint[i]->setControl(true);
  }
}

void disablePID() {
  for (uint8_t i = 0; i < 7; i++) {
    joint[i]->setControl(false);
  }
}