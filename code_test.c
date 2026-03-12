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

#define LuxL IN_1
#define LuxR IN_4
#define IN_US IN_2
#define IN_Touch IN_3

/// Fonctions

inline void init_sensors() {

       // Light right
       SetSensorType(LuxR, SENSOR_TYPE_LIGHT_INACTIVE);
       SetSensorMode(LuxR, SENSOR_MODE_RAW);

       // Light left
       SetSensorType(LuxL, SENSOR_TYPE_LIGHT_INACTIVE);
       SetSensorMode(LuxL, SENSOR_MODE_RAW);

       // Ultrasound
       SetSensorLowspeed(IN_US);

       // Touch
       SetSensorTouch(IN_Touch);

}

/*
  Trouve le capteur qui observe le plus
  de lumiere

  Args :
       (int) tolerance
  Returns :
       "gauche" || "droite" || "egal" || "nul"
*/
inline string get_to_light(int tolerance) {

       int light_left = Sensor(LuxL);
       int light_right = Sensor(LuxR);

       int dif = light_right-light_left;

       if (abs(dif) < tolerance) {
              return "egal";
       } else if (light_right < tolerance && light_left < tolerance) {
              return "nul";
       } else if (light_left > light_right) {
              return "gauche";
       } else if (light_right > light_left) {
              return "droite";
       }
}

task main() {

       init_sensors();
       
       SetSensorType(LuxL, IN_TYPE_LIGHT_ACTIVE);
       SetSensorType(LuxR, IN_TYPE_LIGHT_ACTIVE);
       Wait(500);
       SetSensorType(LuxL, IN_TYPE_LIGHT_INACTIVE);
       SetSensorType(LuxR, IN_TYPE_LIGHT_INACTIVE);

       int tolerance = 0;

       while (true) {

              if (ButtonState(3) == 0) {
                     tolerance = tolerance - 1;
              }
              if (ButtonState(2) == 0) {
                     tolerance = tolerance + 1;
              }

              int light_left = Sensor(LuxL);
              int light_right = Sensor(LuxR);

              TextOut(1, LCD_LINE1, StrCat(NumToStr(tolerance), " ", get_to_light(tolerance), " ", NumToStr(light_left), " ", NumToStr(light_right)), true);

       }

}