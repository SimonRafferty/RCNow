#ifndef RCNow_h
#define RCNow_h

#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

typedef void (*ReceiveCallback)(uint16_t senderID, double v1, double v2, double v3, double v4, double v5, double v6, double v7, double v8, double v9, double v10, double v11, double v12, double v13, double v14, double v15, double v16);

class RCNow {
public:
    RCNow();
    bool begin(uint16_t id);
    bool send(double v1, double v2, double v3, double v4, double v5, double v6, double v7, double v8, double v9, double v10, double v11, double v12, double v13, double v14, double v15, double v16);
    void onReceive(ReceiveCallback callback);

private:
    static void onDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len);
    static ReceiveCallback receiveCallback;
    static uint16_t myID;
    static const uint8_t broadcastAddress[6];
};

#endif
