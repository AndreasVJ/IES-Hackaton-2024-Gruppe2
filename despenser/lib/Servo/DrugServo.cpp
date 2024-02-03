#include <DrugServo.h>
#include <old.h>

void ServoSetup() {
    Servo servo1;
    Servo servo2;
    Servo servo3;
    Servo servo4;

    servo1.attach(32);
    servo2.attach(33);
    servo3.attach(25);
    servo4.attach(26);
}

void ServoDispence(OldPerson gamlis) {
    gamlis.GetDrugs
}