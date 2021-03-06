#include "main.h"


/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////


const int DRIVE_SPEED = 110; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
                             // If this is 127 and the robot tries to heading correct, it's only correcting by
                             // making one side slower.  When this is 87%, it's correcting by making one side
                             // faster and one side slower, giving better heading correction.
const int TURN_SPEED  = 90;
const int SWING_SPEED = 90;



///
// Constants
///

// It's best practice to tune constants when the robot is empty and with heavier game objects, or with lifts up vs down.
// If the objects are light or the cog doesn't change much, then there isn't a concern here.

void default_constants() {
  chassis.set_slew_min_power(127, 127);
  chassis.set_slew_distance(1, 1);
  chassis.set_pid_constants(&chassis.headingPID, 16, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.6, 0, 5.2, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.6, 0, 5.2, 0);
  chassis.set_pid_constants(&chassis.turnPID, 7.22, 0.003, 3, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

/*

void one_mogo_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(chassis.swingPID, 7, 0, 45, 0);
}

void two_mogo_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(chassis.swingPID, 7, 0, 45, 0);
}
*/
void soloAWP(){
  liftclamp_auto(true);
  pros::delay(10);
  chassis.set_drive_pid(-3, DRIVE_SPEED, true);
  chassis.wait_drive();
  set_lift_position(100,100);
  pros::delay(10);
  set_conveyor(true);
  pros::delay(100);
  set_conveyor(false);
  chassis.set_swing_pid(ez::RIGHT_SWING, 90, SWING_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-3, DRIVE_SPEED, true);
  chassis.wait_drive();
  chassis.set_swing_pid(ez::RIGHT_SWING, 180, SWING_SPEED);
  chassis.wait_drive();
  set_lift_position(0,100);
  chassis.set_drive_pid(-52, DRIVE_SPEED, true);
  chassis.wait_drive();
  mogoclamp_auto(true);
  pros::delay(10);
  chassis.set_drive_pid(5, DRIVE_SPEED, true);
  chassis.wait_drive();

}

void soloAWP2() {
  set_lift_position(100,100);
  chassis.set_drive_pid(-4, DRIVE_SPEED, true);
  chassis.wait_drive();
  mogoclamp_auto(true);
  pros::delay(10);
  chassis.set_drive_pid(6, DRIVE_SPEED, true);
  chassis.wait_drive();
  chassis.set_swing_pid(ez::LEFT_SWING, 90, SWING_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(3, DRIVE_SPEED, true);
  chassis.wait_drive();
  chassis.set_swing_pid(ez::LEFT_SWING, 180, SWING_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(45, DRIVE_SPEED, true);
  set_conveyor(true);
  pros::delay(500);
  set_conveyor(false);
  chassis.wait_drive();
  set_lift_position(0,100);
  chassis.set_drive_pid(5, 40, true);
  chassis.wait_drive();
  liftclamp_auto(true);
  pros::delay(100);
  chassis.set_drive_pid(-10, DRIVE_SPEED, true);
  chassis.wait_drive();

  
  
}

///
// Drive Example
///
void drive_example() {
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater then the slew distance + a few inches


  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_drive_pid(-12, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_drive_pid(-12, DRIVE_SPEED, true);
  chassis.wait_drive();
}



///
// Turn Example
///
void turn_example() {
  // The first parameter is target degrees
  // The second parameter is max speed the robot will drive at


  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();

  pros::delay(300);

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();
  pros::delay(300);

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();
}



///
// Combining Turn + Drive
///
void drive_and_turn() {
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_drive();
}



///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed() {
  // wait_until will wait until the robot gets to a desired position


  // When the robot gets to 6 inches, the robot will travel the remaining distance at a max speed of 40
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_until(6);
  chassis.set_max_speed(40); // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  // When the robot gets to -6 inches, the robot will travel the remaining distance at a max speed of 40
  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_until(-6);
  chassis.set_max_speed(40); // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
  chassis.wait_drive();
}



///
// Swing Example
///
void swing_example() {
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is target degrees
  // The third parameter is speed of the moving side of the drive


  chassis.set_swing_pid(ez::LEFT_SWING, 45, SWING_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_until(3);

  chassis.set_swing_pid(ez::RIGHT_SWING, 0, SWING_SPEED);
  chassis.wait_drive();
}



///
// Auto that tests everything
///
void combining_movements() {
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(ez::RIGHT_SWING, -45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_drive();
}



///
// Interference example
///
void tug (int attempts) {
  for (int i=0; i<attempts-1; i++) {
    // Attempt to drive backwards
    printf("i - %i", i);
    chassis.set_drive_pid(-12, 127);
    chassis.wait_drive();

    // If failsafed...
    if (chassis.interfered) {
      chassis.reset_drive_sensor();
      chassis.set_drive_pid(-2, 20);
      pros::delay(1000);
    }
    // If robot succesfully drove back, return
    else {
      return;
    }
  }
}

// If there is no interference, robot will drive forward and turn 90 degrees. 
// If interfered, robot will drive forward and then attempt to drive backwards. 
void interfered_example() {
 chassis.set_drive_pid(24, DRIVE_SPEED, true);
 chassis.wait_drive();

 if (chassis.interfered) {
   tug(3);
   return;
 }

 chassis.set_turn_pid(90, TURN_SPEED);
 chassis.wait_drive();
}



// . . .
// Make your own autonomous functions here!
// . . .