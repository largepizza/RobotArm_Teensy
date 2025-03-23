#include "control.hpp"


configDataStruct configData;

Scheduler scheduler;

controlStatus_t controlStatus = CONTROL_JOINT_CONTROLLER;
controlStatus_t last_controlStatus = CONTROL_JOINT_CONTROLLER;

//Axis Limits
//Joint 0 = {-150,180}
//Joint 1 = {-15, 128}
//Joint 2 = {-120, 120}
//Joint 3 = {-90, 90}
//Joint 4 = {-180, 180}
//Joint 5 = {-110, 180}


uint32_t t_pidButton;


void control_init() {
    controlStatus = CONTROL_JOINT_CONTROLLER;


}

void joint_pid() {
  // Joint PID control
  for (uint8_t i = 0; i < 7; i++) {
    joint[i]->pid->Compute();
    if (joint[i]->pid->GetMode() == AUTOMATIC) {

      joint[i]->setSpeed(abs(joint[i]->control), getOppositeDir(floatToDir(joint[i]->control)));

    }
  }
  // Get target angles
  for (uint8_t i = 0; i < 7; i++) {
    joint[i]->setpoint = rxData.joint_targets[i];
  }
}

void joint_controller() {
  // Joint control
  // Joint 0 - YAW
  if (abs(rxData.controller_axis[0]) > 0.2f ) {
    joint[0]->setSpeed(abs(rxData.controller_axis[0]) * 255.0f, floatToDir(rxData.controller_axis[0]));
  }
  else {
    joint[0]->setSpeed(0, DIR_OFF);
  }
  // Joint 1 - SHOULDER
  if (abs(rxData.controller_axis[1]) > 0.2f ) {
    joint[1]->setSpeed(abs(rxData.controller_axis[1]) * 255.0f,floatToDir(rxData.controller_axis[1]));
  }
  else {
    joint[1]->setSpeed(0, DIR_OFF);
  }
  // Joint 2 - ELBOW
  if (abs(rxData.controller_axis[3]) > 0.2f ) {
    joint[2]->setSpeed(abs(rxData.controller_axis[3]) * 255.0f,floatToDir(rxData.controller_axis[3]));
  }
  else {
    joint[2]->setSpeed(0, DIR_OFF);
  }
  // Joint 3 - WRIST
  if (abs(rxData.controller_axis[2]) > 0.2f ) {
    joint[3]->setSpeed(abs(rxData.controller_axis[2]) * 255.0f,floatToDir(rxData.controller_axis[2]));
  }
  else {
    joint[3]->setSpeed(0, DIR_OFF);
  }
  // Joint 4 - WRIST ROTATION
  if (rxData.controller_buttons[5] > 0) {
    joint[4]->setSpeed(100, DIR_PLUS);
  }
  else if (rxData.controller_buttons[4] > 0) {
    joint[4]->setSpeed(100, DIR_MINUS);
  }
  else {
    joint[4]->setSpeed(0, DIR_OFF);
  }
  // Joint 5 - GRIPPER
  if (rxData.controller_buttons[0] > 0) {
    joint[5]->setSpeed(100, DIR_PLUS);
  }
  else if (rxData.controller_buttons[1] > 0) {
    joint[5]->setSpeed(100, DIR_MINUS);
  }
  else {
    joint[5]->setSpeed(0, DIR_OFF);
  }
  // Joint 6 - TRANSLATION
  float transControl = (rxData.controller_axis[4]+1.0f)/2.0f - (rxData.controller_axis[5]+1.0f)/2.0f;
  if (abs(transControl) > 0.2f ) {
    joint[6]->setSpeed(abs(transControl) * 255.0, floatToDir(transControl));
  }
  else {
    joint[6]->setSpeed(0, DIR_OFF);
  }

}


void control_loop() {
    // Handle changed control status
    if (controlStatus != last_controlStatus) {
        // Stop all motors
        for (uint8_t i = 0; i < 7; i++) {
            joint[i]->setSpeed(0, DIR_OFF);
        }

        // Do first time setup for new control status
        switch (controlStatus) {
            case CONTROL_NONE:
                break;
            case CONTROL_JOINT_CONTROLLER:
                // Disable PID control
                disablePID();
                break;
            case CONTROL_ZERO:
                // Disable PID control
                disablePID();
                // Add commands to queue
                scheduler.clear();                                              // Clear scheduler queue
                //--------------------------------------------------------------------------------
                // Zero joint 0
                //--------------------------------------------------------------------------------
                // Run joint 0 until encoder threshold
                scheduler.add(std::make_shared<RunJointThreshold>(0, -128, 10)); 
                // Wait 50ms
                scheduler.add(std::make_shared<WaitMs>(50));
                // Move in the opposite direction and find the limit
                scheduler.add(std::make_shared<RunJointLimit>(0, 255));
                // Wait 500ms
                scheduler.add(std::make_shared<WaitMs>(50));
                // Move back slowly a for 1 second
                scheduler.add(std::make_shared<RunJointTime>(0, -80, 1000));
                // Move to the limit again slowly
                scheduler.add(std::make_shared<RunJointLimit>(0, 50));
                // Wait 500ms
                scheduler.add(std::make_shared<WaitMs>(50));
                // Zero joint 0
                scheduler.add(std::make_shared<ZeroJoint>(0));
                //--------------------------------------------------------------------------------
                // Zero joint 1
                //--------------------------------------------------------------------------------
                // Run joint 1 until encoder threshold
                scheduler.add(std::make_shared<RunJointLimit>(1, -128));
                // Wait 500ms
                scheduler.add(std::make_shared<WaitMs>(500));
                // Move slowly in the opposite direction for 1 second
                scheduler.add(std::make_shared<RunJointTime>(1, 80, 1000));
                // Move to the limit again slowly
                scheduler.add(std::make_shared<RunJointLimit>(1, -50));
                // Wait 50ms
                scheduler.add(std::make_shared<WaitMs>(50));
                // Zero joint 1
                scheduler.add(std::make_shared<ZeroJoint>(1, -120-14+10));
                //--------------------------------------------------------------------------------
                // Zero joint 2
                //--------------------------------------------------------------------------------
                // Run joint 2 until limit 
                scheduler.add(std::make_shared<RunJointLimit>(2, -128));
                // Wait 50ms
                scheduler.add(std::make_shared<WaitMs>(50));
                // Move same direction for 1 second
                scheduler.add(std::make_shared<RunJointTime>(2, -80, 1000));
                // Move to the limit again slowly
                scheduler.add(std::make_shared<RunJointLimit>(2, 20));
                // Wait 50ms
                scheduler.add(std::make_shared<WaitMs>(50));
                // Zero joint 2
                scheduler.add(std::make_shared<ZeroJoint>(2, -90+130-92));

                //--------------------------------------------------------------------------------
                // Zero joint 3
                //--------------------------------------------------------------------------------
                // Run joint 3 until threshold
                //scheduler.add(std::make_shared<RunJointThreshold>(3, -50, 10));
                // Wait 50ms
                //scheduler.add(std::make_shared<WaitMs>(500));
                // Move in the opposite direction and find the limit
                scheduler.add(std::make_shared<RunJointLimit>(3, 60));
                // Wait 50ms
                scheduler.add(std::make_shared<WaitMs>(500));
                // Move back slowly a for 1 second
                scheduler.add(std::make_shared<RunJointTime>(3, -60, 1000));
                // Move to the limit again slowly
                scheduler.add(std::make_shared<RunJointLimit>(3, 40));
                // Wait 50ms
                scheduler.add(std::make_shared<WaitMs>(50));
                // Zero joint 3
                scheduler.add(std::make_shared<ZeroJoint>(3, -45+130-90));

                //--------------------------------------------------------------------------------
                // Zero joint 4
                //--------------------------------------------------------------------------------
                // Run joint 4 until limit
                scheduler.add(std::make_shared<RunJointLimit>(4, 128));
                // Wait 50ms
                scheduler.add(std::make_shared<WaitMs>(50));
                // Move in the opposite direction one second
                scheduler.add(std::make_shared<RunJointTime>(4, -80, 1000));
                // Move to the limit again slowly
                scheduler.add(std::make_shared<RunJointLimit>(4, 50));
                // Wait 50ms
                scheduler.add(std::make_shared<WaitMs>(50));
                // Zero joint 4
                scheduler.add(std::make_shared<ZeroJoint>(4, -20+30));

                //--------------------------------------------------------------------------------
                // Zero joint 5 (Gripper)
                //--------------------------------------------------------------------------------
                // Run joint 5 until threshold
                scheduler.add(std::make_shared<RunJointThreshold>(5, -255, 10));
                // Wait 50ms
                scheduler.add(std::make_shared<WaitMs>(50));
                // Zero joint 5
                scheduler.add(std::make_shared<ZeroJoint>(5, -180));




                //scheduler.add(std::make_shared<StopJoint>(0));                 // Stop joint 0
            
                break;
            case CONTROL_JOINT_PID:
                // Enable PID control
                enablePID();
                break;
            default:
                break;
        }
    }

    last_controlStatus = controlStatus;

    // Handle control status
    switch (controlStatus) {
        case CONTROL_NONE:
            break;
        case CONTROL_JOINT_CONTROLLER:
            joint_controller();
            

            break;
        case CONTROL_ZERO:

            scheduler.run();

            if (scheduler.isEmpty()) {
                controlStatus = CONTROL_JOINT_CONTROLLER;
            }
            break;
        case CONTROL_JOINT_PID:
            joint_pid();

            break;
        default:
            break;
    }



    //Handle change of control status

    //Zeroing control triggered by buttons[7]
    if (rxData.controller_buttons[7] > 0) {
        controlStatus = CONTROL_ZERO;
    }

    //PID control triggered by buttons[6]
    if (rxData.controller_buttons[6] > 0 && millis() - t_pidButton > 500) {
        t_pidButton = millis();

        if (controlStatus == CONTROL_JOINT_PID) {
            controlStatus = CONTROL_JOINT_CONTROLLER;
        }
        else {
            controlStatus = CONTROL_JOINT_PID;
        }
    }
    


    
}