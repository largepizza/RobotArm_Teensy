#include "control.hpp"


Scheduler scheduler;

controlStatus_t controlStatus = CONTROL_JOINT_CONTROLLER;
controlStatus_t last_controlStatus = CONTROL_JOINT_CONTROLLER;


void control_init() {
    controlStatus = CONTROL_JOINT_CONTROLLER;
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
                break;
            case CONTROL_ZERO:
                // Add commands to queue
                scheduler.clear();                                              // Clear scheduler queue
                //--------------------------------------------------------------------------------
                // Zero joint 0
                //--------------------------------------------------------------------------------
                // Run joint 0 until encoder threshold
                scheduler.add(std::make_shared<RunJointThreshold>(0, -128, 10)); 
                // Wait 500ms
                scheduler.add(std::make_shared<WaitMs>(500));
                // Zero joint 0
                scheduler.add(std::make_shared<ZeroJoint>(0));
                //--------------------------------------------------------------------------------
                // Zero joint 1
                //--------------------------------------------------------------------------------
                // Run joint 1 until encoder threshold
                scheduler.add(std::make_shared<RunJointThreshold>(1, -128, 10));
                // Wait 800ms
                scheduler.add(std::make_shared<WaitMs>(800));
                // Zero joint 1
                scheduler.add(std::make_shared<ZeroJoint>(1));
                //--------------------------------------------------------------------------------
                // Zero joint 2
                //--------------------------------------------------------------------------------
                // Run joint 2 until encoder threshold
                // scheduler.add(std::make_shared<RunJointThreshold>(2, 128, 10));
                // // Wait 20ms
                // scheduler.add(std::make_shared<WaitMs>(200));
                // // Move slowly in the opposite direction and find the limit
                // scheduler.add(std::make_shared<RunJointLimit>(2, -80));
                // // Zero joint 2
                // scheduler.add(std::make_shared<ZeroJoint>(2));



                //scheduler.add(std::make_shared<StopJoint>(0));                 // Stop joint 0
            
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
        default:
            break;
    }



    //Handle change of control status

    //Zeroing control triggered by buttons[7]
    if (rxData.controller_buttons[7] > 0) {
        controlStatus = CONTROL_ZERO;
    }


    
}