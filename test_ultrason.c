//Values
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
int US_SENSOR_A = 1;

/*
  Retourne TRUE si un obstacle est détecté

  Arg: None
  Return : (bool) True | False
*/
bool is_obstacle(){

    int distance = SensorUS(IN_US);

    if(distance <= 30){
        return TRUE;
    } else {
        return FALSE;
    }
}

/*
  Retourne la distance de l'obstacle

  Arg: None
  return: (int) distance  | -1 [aucun obstacle]
*/
int get_distance(){

    while(US_SENSOR_A == 1){

        int distance = SensorUS(IN_US);

        if(distance <= 30){
            return distance;
        }
        else{
            return -1; // si aucun obstacle
        }
    }

  
}

