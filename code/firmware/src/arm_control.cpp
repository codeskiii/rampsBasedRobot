/*
  Zakladam 6 osiowosc ramienia 
*/
  // if (Serial.available() > 0) {
  //   char recivedChar = Serial.read();
  //   String strRecived = String(recivedChar);
  
  //   if (strRecived == "100X") {
  //     Serial.println("RECIVED 100 DEEGRES IN X");
  //     digitalWrite(X_STEP_PIN , HIGH);

  //     /* 
  //     WZOR NA DELAY ->

  //     czas w sekundach = kąt w stopniach / prędkość kątowa w stopniach na sekundę
  //     */

  //     delay(100.0/motor_angular_velocity);
      
  //     digitalWrite(X_STEP_PIN , LOW);
  //   }
  //}

#include <Servo.h>

/* 
 5-dimensional movement vector in radians
*/
struct vec6 {
  float x;
  float y;
  float z;
  float e;
  float q;
};

/* 
 Structure representing the arm and motor details 
*/
struct arm {
  int x_axis_pin;
  int y_axis_pin;
  int z_axis_pin;
  int e_axis_pin;
  int q_axis_pin;

  float motor_angular_velocity;  // velocity of all motors in radians per second

  float x_axis_position;
  float y_axis_position;
  float z_axis_position;
  float e_axis_position;
  float q_axis_position;
};

/* 
 Function to calculate the required delay based on the motor's angular velocity and the angle (in degrees) you want to move
*/
float countTheDelay(float degreesWanted, arm arm_given) {
  return degreesWanted / arm_given.motor_angular_velocity * 1000; // Delay in milliseconds
}

/* 
 Function to move all axes of the arm by the given vector (u_vector) 
*/
arm moveAxisByVector(vec6 u_vector, arm arm_given) {
  
    // Move X axis
  arm_given.x_axis_position += u_vector.x; 
  digitalWrite(arm_given.x_axis_pin, HIGH);
  delay(countTheDelay(u_vector.x, arm_given));
  digitalWrite(arm_given.x_axis_pin, LOW);

  // Move Y axis
  arm_given.y_axis_position += u_vector.y; 
  digitalWrite(arm_given.y_axis_pin, HIGH);
  delay(countTheDelay(u_vector.y, arm_given));
  digitalWrite(arm_given.y_axis_pin, LOW);

  // Move Z axis
  arm_given.z_axis_position += u_vector.z; 
  digitalWrite(arm_given.z_axis_pin, HIGH);
  delay(countTheDelay(u_vector.z, arm_given));
  digitalWrite(arm_given.z_axis_pin, LOW);

  // Move E axis
  arm_given.e_axis_position += u_vector.e; 
  digitalWrite(arm_given.e_axis_pin, HIGH);
  delay(countTheDelay(u_vector.e, arm_given));
  digitalWrite(arm_given.e_axis_pin, LOW);

  // Move Q axis
  arm_given.q_axis_position += u_vector.q; 
  digitalWrite(arm_given.q_axis_pin, HIGH);
  delay(countTheDelay(u_vector.q, arm_given));
  digitalWrite(arm_given.q_axis_pin, LOW);

  return arm_given;
}

