#include "Particle.h"

SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);

void setup() // Put setup code here to run once
{

        pinMode(D7, OUTPUT);

}

void loop() // Put code here to loop forever
{

        digitalWrite(D7, !digitalRead(D7));
        delay(500);

}
