/*

  code.nxc
  05/03/2026





  Issues : turn, didn't work lastly
  
*/

/*
struct MaClass {
       int nombre;
       string text;
};

struct Enfant {
       MaClass parent;
       int nombre2;
};*/

/// Constantes

#define pi 3.141592653589793

#define POWER 50
#define MOV_DUR 5000
#define PAUSE 500

#define WHEEL_RADIUS 4.1395
#define ROBOT_RADIUS 8.547

// Sensors & Actors

#define MOT_1 OUT_A
#define MOT_2 OUT_C
#define MOTS OUT_AC

#define LuxL IN_1
#define LuxR IN_4
#define IN_US IN_2
#define IN_Touch IN_3

/// Variables

int tolerance = 50;

int shadow=100;                 //init val

int lum[11];
int offset[11];

/// Fonctions

/*
       Debug avec des sons
*/
inline void debug(string type) {
       if (type == "error") {
              PlayTone(TONE_A5, 500);
              SetSensorType(LuxL, IN_TYPE_LIGHT_ACTIVE);
              SetSensorType(LuxR, IN_TYPE_LIGHT_ACTIVE);
              Wait(500);
              SetSensorType(LuxL, IN_TYPE_LIGHT_INACTIVE);
              SetSensorType(LuxR, IN_TYPE_LIGHT_INACTIVE);
       } else if (type == "warn") {
              PlayTone(TONE_B5, 250);
       } else {
              PlayTone(TONE_C5, 100);
       }
}

/*
       Initilization des sorties capteurs
*/
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
// Pour arreter le robot et afficher qu'il s'arrete
inline void pause() {

       // Pause
       TextOut(1, LCD_LINE1, "Pause", true);
       Off(MOTS);
       Wait(PAUSE);

}

task clash() { //fait du bruit

       int q = 100;   // noire
       int h = 200;   // blanche

       // Phrase 1
       PlayTone(TONE_CS5, q);  Wait(q);
       PlayTone(TONE_FS5, q);  Wait(q);
       PlayTone(TONE_GS5, q); Wait(q);
       PlayTone(TONE_CS6, q);  Wait(q);
       PlayTone(TONE_F6, q);  Wait(q);

       Wait(1000);

       // Phrase 2
       PlayTone(TONE_AS5, q); Wait(h);
       PlayTone(TONE_A5, q);  Wait(q);
       PlayTone(TONE_G5, q); Wait(q);
       PlayTone(TONE_F5, q);  Wait(q);

       // Descente finale
       PlayTone(TONE_D6, q); Wait(q);
       PlayTone(TONE_C6, h);  Wait(h);

}

/*
Gestion des capteurs de lumières et de la direction à suivre

Args:(int) LSensor_Val , (int) RSensor_Val

Return:(int) Direction and strenght to turn

0 : forward
<0 : left
>0 : right
*/

inline float lux(int L, int R) {

    lum[10] = moy(L,R);
    offset[10] = R-L;

    int turn;
    int i=10;

    if((lum[10]<shadow && lum[0]-lum[10]>50)|| lum[0]<shadow){            //check for shade
        bool shadowrealm=true;
    } else {bool shadowrealm=false;}
    
    if(shadowrealm==false){                         //calculate turning hysteresis
        int lvl=lum[10]/100;
        if(L-R<=lvl ||R-L<=lvl){
            turn=0;
        } else {
              turn=R-L;
       }
       }
    else {
         while(lum[i]<shadow && i>= 0){                   //get turning value from past data
            i=i-1;
        }
        if(offset[i]<0){turn=-900;}
        else{turn=900;}
    }
  
    pop(lum[0]);pop(offset[0]);       //Deviate time
    for(i=0,i++,1<10){
        lum[i]=lum[i+1];
        offset[i]=offset[i+1];
    }
    //Wait(100);
    return turn;
}

/*
  Calcul la distance en centimetres a partir
  du nombre de rotation des moteurs.
  
  Args : (int) MOTORS_IDS
  Return : (float) distance
*/
inline float distance_from_rot(int MOTORS_IDS) {
       return (2*pi*WHEEL_RADIUS*(MotorRotationCount(MOTORS_IDS)/360));
}

inline void turn(int angle) {

       ResetRotationCount(MOTS);
       
       //OnFwdSyncEx(MOTS, POWER, 100, RESET_ALL);

       OnFwdSyncPID(MOTS, POWER, 100,30, 50, 90);

       until (abs(MotorRotationCount(MOT_1)) >= (angle*ROBOT_RADIUS) / WHEEL_RADIUS);
       //while (abs(MotorRotationCount(MOT_1)) < 180{//(angle*ROBOT_RADIUS) / WHEEL_RADIUS) {
       //      TextOut(1, LCD_LINE1, StrCat(NumToStr(MotorRotationCount(MOT_1)), "   ", NumToStr((angle*ROBOT_RADIUS) / WHEEL_RADIUS)), true);
       //}
       
       Off(MOTS);
}

/*
  Avance de x centimetres en utilisant
  la synchronisation moteurs
  
  Args : (float) distance
  Return : void
*/
inline void sync_cm(float distance) {

       OnFwdSyncEx(MOTS, POWER, 0, RESET_ALL);

       until (distance_from_rot(MOT_1) >= distance);

       Off(MOTS);
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

/*
  Fait suivre le perimetre d'un carre
  de 50 centimetre de cote par le robot
*/
task square() {
     repeat(4) {

              TextOut(1, LCD_LINE1, "Avance", true);
              ResetRotationCount(MOTS);
              sync_cm(50.0);

              TextOut(1, LCD_LINE1, "Pause", true);
              OffEx(MOTS, RESET_NONE);
              Wait(PAUSE);

              debug("error");

              TextOut(1, LCD_LINE1, "Tourne", true);
              ResetRotationCount(MOTS);
              turn(85);

              TextOut(1, LCD_LINE1, "Pause", true);
              OffEx(MOTS, RESET_NONE);
              Wait(PAUSE);

     };
}

/*
       Tourne pour egaliser la quantité de lumière
       recue par le capteur. 
       Args : None
       Return : None
*/
task follow_light() {

       while (true) {
       
              if (get_to_light(tolerance)=="gauche"){
                     //faire tourner a gauche jusqu'a ce que les niveaux soient egaux
                     OnFwdSyncPID(MOTS, POWER, 100, 30, 50, 90);
                     until (get_to_light(tolerance)=="egal");
              }
              else if(get_to_light(tolerance)=="droite"){
              //faire tourner a droite jusqu'a ce que les niveaux soient egaux  
                     OnFwdSyncPID(MOTS, POWER, -100, 30, 50, 90);
                     until (get_to_light(tolerance)=="egal");             
              }
              else if(get_to_light(tolerance)=="nul"){
                     //cas ou le robot ne capte rien, on tourne jusqu'à capter
                     OnFwdSyncPID(MOTS, POWER, 100, 30, 50, 90);
                     until (get_to_light(tolerance)=="egal");
              }
              else{
                     //nous sommes en face, on avance
                     OnFwdSyncPID(MOTS, POWER, 0, 30, 50, 90);
              }

       }
       
}

inline void print_light_lux() {

       int light_left = Sensor(LuxL);
       int light_right = Sensor(LuxR);
       int moy = (light_right+light_left)  /2;

       //ClearScreen();
       TextOut(1, LCD_LINE1, StrCat(NumToStr(lux(light_left, light_right)), " ", NumToStr(light_left), " ", NumToStr(light_right)), true);
       //TextOut(1, LCD_LINE2, NumToStr(moy), true);

}

task follow_light_lux() {

       while (true) {

              int light_left = Sensor(LuxL);
              int light_right = Sensor(LuxR);
       
              if (lux(Sensor(LuxL), Sensor(LuxR))<0){
                     //faire tourner a gauche jusqu'a ce que les niveaux soient egaux
                     OnFwdSyncPID(MOTS, POWER, 100, 30, 50, 90);
                     //until (lux(light_left, light_right)==0);
                     PlayTone(TONE_F6, 100);
                     while (lux(Sensor(LuxL), Sensor(LuxR)) != 0) {
                            print_light_lux()
                     }
              } else if(lux(Sensor(LuxL), Sensor(LuxR))<0){
              //faire tourner a droite jusqu'a ce que les niveaux soient egaux  
                     OnFwdSyncPID(MOTS, POWER, -100, 30, 50, 90);
                     //until (lux(light_left, light_right)==0);
                     PlayTone(TONE_C5, 100);
                     while (lux(Sensor(LuxL), Sensor(LuxR)) != 0) {
                            print_light_lux()
                     }            
              } else{
                     //nous sommes en face, on avance
                     PlayTone(TONE_A3, 200);
                     OnFwdSyncPID(MOTS, POWER, 0, 30, 50, 90);
                     print_light_lux()
              }

       }
       
}

task main() {
       init_sensors();
       Follows(clash, follow_light);
}