// ensure this library description is only included once
#ifndef mqtt_h
#define mqtt_h
#include <Arduino.h>

// library interface description
class StepperMRTO
{
public:
  // constructors:
  MQTT(void);

  // speed setter method:
  void setSpeed(long rpmSpeed);
  uint32_t getSpeed();

  // set the magnitude of the stroke in steps
  void setStrokeSteps(int strokeSteps);
  uint32_t getStrokeSteps();

  // limit length of individual step to control torque
  void setTorqueLimit(unsigned long stepLimit);
  uint32_t getTorqueLimit();

  // set the default run direction
  void setReversed(bool reversed);
  bool getReversed();

  // start method primes the code to run on subsequent loops
  // either a button push or a remote command could call this
  void setReady(bool direction);

  // repeatedly called in the loop
  bool run(void);

  // set current to zero at end of stroke to prevent stressing output pin
  void release(void);

  //check running state, running or not
  bool getRunState();

  //get ready to run state
  bool getReadyState();

  // report the last position
  int getLastCommanded();

  int version(void);

private:
  void stepMotor(int this_step);

  bool _direction;          // Direction of rotation
  uint32_t _stepInterval;   // delay between steps, in ms, based on speed
  uint32_t _torqueInterval; // shortened interval to reduce torque and average current
  uint16_t _strokeSteps;    // steps to take in this run
  uint32_t _now;
  uint32_t _lastStepStartTime; // time stamp in us of when the last step was started
  bool _isRunning;
  bool _readyToRun;
  bool _currentDirection;
  uint32_t _currentStep; // which step the motor is on
  uint32_t _stepsLeftToGo;
  uint32_t _stepsPerRevolution;
  int _lastCommanded;
  uint32_t _rpmSpeed;
  bool _reversed;

  // motor pin numbers:
  int _motorAPlus;
  int _motorAMinus;
  int _motorBPlus;
  int _motorBMinus;

};

#endif
