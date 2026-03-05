/*

  code.nxc
  05/02/2026
  OBJECTIF : tester la fonction get_to_light, savoir si nos capteurs
  sont capables de recuperer nos donnees. 

  ==> resultats : success



*/

/// Constantes

#define pi 3.141592653589793

#define POWER 50
#define MOV_DUR 5000
#define PAUSE 500

#define WHEEL_COEF 0.069
#define WHEEL_RADIUS 4.1395

#define ROBOT_RADIUS 8.5

// Sensors & Actors

#define MOT_1 OUT_A
#define MOT_2 OUT_C
#define MOTS OUT_AC

#define IN_LIGHT_LEFT IN_1
#define IN_LIGHT_RIGHT IN_4
#define IN_US IN_2
#define IN_Touch IN_3

/// Fonctions

 inline void init_sensors() {

       // Light right
       SetSensorType(IN_LIGHT_RIGHT, SENSOR_TYPE_LIGHT_INACTIVE);
       SetSensorMode(IN_LIGHT_RIGHT, SENSOR_MODE_RAW);

       // Light left
       SetSensorType(IN_LIGHT_LEFT, SENSOR_TYPE_LIGHT_INACTIVE);
       SetSensorMode(IN_LIGHT_LEFT, SENSOR_MODE_RAW);

       // Ultrasound
       SetSensorLowspeed(IN_US);

       // Touch
       SetSensorTouch(IN_Touch);

}

inline string get_to_light() {

       int light_left = Sensor(IN_LIGHT_LEFT);
       int light_right = Sensor(IN_LIGHT_RIGHT);

       if (light_left > light_right) {
              return "gauche";
       } else if (light_right > light_left) {
              return "droite";
       } else if (light_right == 0 && light_left == 0) {
              return "nul";
       } else {
              return "egal";
       }

}





task main() {

       init_sensors();
       TextOut(1, LCD_LINE1, get_to_light(), true);

}