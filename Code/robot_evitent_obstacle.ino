#include<HCSR04.h>
#include<Servo.h>

//Définition des broches de contrôle du L298N
const int ENA = 5;  // Broche de vitesse pour moteur gauche
const int ENB = 6;  // Broche de vitesse pour moteur droit
const int IN1 = 7;  // Direction moteur gauche
const int IN2 = 8;  
const int IN3 = 9;  // Direction moteur droit
const int IN4 = 10;
//Définition des broches du capteur ultrason HC-SR04
const int brocheTrig = 3;
const int brocheEcho = 2;
//Déclaration du servomoteur
Servo servoTete;
int distanceObstacle, distanceDroite, distanceGauche;
void setup(){
    Serial.begin(9600);
    servoTete.attach(11);
    servoTete.write(90); // Position initiale
    // Configuration des broches des moteurs en sortie
    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);
    // Activer les moteurs avec une vitesse initiale
    analogWrite(ENA, 150);  // Vitesse du moteur gauche (0-255)
    analogWrite(ENB, 150);  // Vitesse du moteur droit (0-255)
}

void loop(){
    distanceObstacle = mesurerDistance();
    Serial.print("Distance détectée : ");
    Serial.println(distanceObstacle);
    delay(50);
    if(distanceObstacle > 0 && distanceObstacle < 15){
        arreterMoteurs();
        delay(500);
        reculer();
        delay(500);
        arreterMoteurs();
        // Scanner droite et gauche
        distanceDroite = scannerDirection(10);
        distanceGauche = scannerDirection(170);
        servoTete.write(90);
        delay(500);

        if(distanceDroite > distanceGauche){
            tournerDroite();
        }else{
            tournerGauche();
        }
    }else if(distanceObstacle > 0){
        avancer();
    }
}
//Fonction pour Mesurer la distance
int mesurerDistance(){
    digitalWrite(brocheTrig, LOW);
    delayMicroseconds(2);
    digitalWrite(brocheTrig, HIGH);
    delayMicroseconds(10);
    digitalWrite(brocheTrig, LOW);

    long duree = pulseIn(brocheEcho, HIGH);
    return duree * 0.034 / 2; // Conversion en cm
}
//Fonction pour scanner une direction avec le capteur ultrason
int scannerDirection(int angle){
    servoTete.write(angle);
    delay(500);
    return mesurerDistance();
}
//Fonction pour avancer le robot
void avancer(){
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
}
//Fonction pour reculer le robot
void reculer(){
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
}
//Fonction pour tourner à gauche
void tournerGauche(){
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    delay(1000);
    arreterMoteurs();
}
//Fonction pour tourner à droite
void tournerDroite(){
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    delay(1000);
    arreterMoteurs();
}
//Fonction pour stopper le robot
void arreterMoteurs(){
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
}


