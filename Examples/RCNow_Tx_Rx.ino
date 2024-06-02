#include <RCNow.h>

RCNow rcnow;

void onReceive(uint16_t senderID, double v1, double v2, double v3, double v4, double v5, double v6, double v7, double v8, double v9, double v10, double v11, double v12, double v13, double v14, double v15, double v16) {
    Serial.print("Received from: ");
    Serial.println(senderID);
    Serial.print("Values: ");
    Serial.print(v1); Serial.print(", ");
    Serial.print(v2); Serial.print(", ");
    Serial.print(v3); Serial.print(", ");
    Serial.print(v4); Serial.print(", ");
    Serial.print(v5); Serial.print(", ");
    Serial.print(v6); Serial.print(", ");
    Serial.print(v7); Serial.print(", ");
    Serial.print(v8); Serial.print(", ");
    Serial.print(v9); Serial.print(", ");
    Serial.print(v10); Serial.print(", ");
    Serial.print(v11); Serial.print(", ");
    Serial.print(v12); Serial.print(", ");
    Serial.print(v13); Serial.print(", ");
    Serial.print(v14); Serial.print(", ");
    Serial.print(v15); Serial.print(", ");
    Serial.println(v16);
}

void setup() {
    Serial.begin(115200);
    if (rcnow.begin(0x1234)) {
        Serial.println("RCNow initialized successfully");
        rcnow.onReceive(onReceive);
    } else {
        Serial.println("Failed to initialize RCNow");
    }
}

void loop() {
    // Send example values
    if (rcnow.send(1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.10, 11.11, 12.12, 13.13, 14.14, 15.15, 16.16)) {
        Serial.println("Values sent successfully");
    } else {
        Serial.println("Failed to send values");
    }
    delay(2000);
}
