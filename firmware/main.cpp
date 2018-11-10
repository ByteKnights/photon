#include "Particle.h"

SYSTEM_MODE(MANUAL);
SYSTEM_THREAD(ENABLED);

void setup() { // Put setup code here to run once
        pinMode(D7, OUTPUT);
        Serial.begin(115200);
        Particle.connect();
}

const size_t READ_BUF_SIZE = 622;
char readBuf[READ_BUF_SIZE];
size_t readBufOffset = 0;

void processBuffer() {
  if (Particle.connected()) {
    Particle.publish("discord", readBuf, PRIVATE);
  }
}

void serialHandler() {
        while(Serial.available()) {
                if (readBufOffset < READ_BUF_SIZE) {
                        char c = Serial.read();
                        if (c != '\n') {
                                // Add character to buffer
                                readBuf[readBufOffset++] = c;
                        } else {
                                // End of line character found, process line
                                readBuf[readBufOffset] = 0;
                                processBuffer();
                                readBufOffset = 0;
                        }
                } else {
                        Serial.println("readBuf overflow, emptying buffer");
                        readBufOffset = 0;
                }
        }
}

void loop() { // Put code here to loop forever
        if (Serial.available()) {
                serialHandler();
        }
}
