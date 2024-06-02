#include "RCNow.h"

ReceiveCallback RCNow::receiveCallback = nullptr;
uint16_t RCNow::myID = 0xFFFF;
const uint8_t RCNow::broadcastAddress[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

struct Message {
    uint16_t conversationID;
    uint16_t senderID;
    double values[16];
};

RCNow::RCNow() {}

bool RCNow::begin(uint16_t id) {
    myID = id;

    WiFi.mode(WIFI_STA);
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return false;
    }

    esp_now_register_recv_cb(onDataRecv);

    esp_now_peer_info_t peerInfo = {};
    memcpy(peerInfo.peer_addr, broadcastAddress, 6);
    peerInfo.channel = 0;  
    peerInfo.encrypt = false;

    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Failed to add broadcast peer");
        return false;
    }

    return true;
}

bool RCNow::send(double v1, double v2, double v3, double v4, double v5, double v6, double v7, double v8, double v9, double v10, double v11, double v12, double v13, double v14, double v15, double v16) {
    Message msg = { myID, myID, {v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11, v12, v13, v14, v15, v16} };
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &msg, sizeof(msg));

    if (result != ESP_OK) {
        Serial.print("Failed to send values. Error code: ");
        Serial.println(result);

        switch (result) {
            case ESP_ERR_ESPNOW_NOT_INIT:
                Serial.println("ESP-NOW is not initialized.");
                break;
            case ESP_ERR_ESPNOW_ARG:
                Serial.println("Invalid argument.");
                break;
            case ESP_ERR_ESPNOW_INTERNAL:
                Serial.println("Internal error.");
                break;
            case ESP_ERR_ESPNOW_NO_MEM:
                Serial.println("ESP-NOW out of memory.");
                break;
            case ESP_ERR_ESPNOW_NOT_FOUND:
                Serial.println("Peer not found.");
                break;
            case ESP_ERR_ESPNOW_IF:
                Serial.println("Interface error.");
                break;
            default:
                Serial.println("Unknown error.");
                break;
        }
    }

    return result == ESP_OK;
}

void RCNow::onReceive(ReceiveCallback callback) {
    receiveCallback = callback;
}

void RCNow::onDataRecv(const uint8_t *mac, const uint8_t *incomingData, int len) {
    Message msg;
    memcpy(&msg, incomingData, sizeof(msg));

    if (receiveCallback && msg.conversationID == myID) {
        receiveCallback(msg.senderID, msg.values[0], msg.values[1], msg.values[2], msg.values[3], msg.values[4], msg.values[5], msg.values[6], msg.values[7], msg.values[8], msg.values[9], msg.values[10], msg.values[11], msg.values[12], msg.values[13], msg.values[14], msg.values[15]);
    }
}
