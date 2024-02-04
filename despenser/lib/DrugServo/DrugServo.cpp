#include <DrugServo.h>

void ServoDispence(String drugs) {
    const int totalDrugs = 2;

    static const int servosPins[totalDrugs] = {32, 33};
    Servo s[totalDrugs];

    for(int i = 0; i < totalDrugs; ++i) {
        if(!s[i].attach(servosPins[i])) {
            Serial.print("Servo ");
            Serial.print(i);
            Serial.println("attach error");
        }
    }

    int defaultDeg = 0;
    int degPerMed = 45;
    int med;
    int resolution = 15;

    for(int i = 0; i<totalDrugs; i++) {


        med = drugs.charAt(i)-65;

        s[i].write(defaultDeg);
        delay(1000);

        for(int k = 0; k<(med/2); k++) {
            for(int j = 0; j<(med*resolution); j++) {
                s[i].write((degPerMed/resolution)*j);
                delay(10);
            }
            delay(1000);

            for(int j = 0; j<(med*resolution); j++) {
                s[i].write((degPerMed*med)-(degPerMed/resolution)*j);
                delay(10);
            }

            s[i].write(defaultDeg);
            delay(1000);
        }
    }
}

