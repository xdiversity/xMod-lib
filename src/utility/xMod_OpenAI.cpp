#include "xMod_OpenAI.hpp"

namespace xdiversity
{
    String xMod_OpenAI::GPT(String text){
        String returnText = "";

        if (firstTry){
            wifiSecure.setInsecure();  //https用
            http.setTimeout(100000);

            GPTTalkLog.clear();
            GPTTalkLog["model"] = model;
            JsonArray messages = GPTTalkLog.createNestedArray("messages");
            JsonObject systemMessageObj = messages.createNestedObject();
            systemMessageObj["role"] = "system";
            systemMessageObj["content"] = "You are a helpful assistant.";
            firstTry = false;
        }

        if (WiFi.status() == WL_CONNECTED) {
            Serial.println("connect GPT");
            http.begin(wifiSecure, "https://api.openai.com/v1/chat/completions");
            http.addHeader("Content-Type", "application/json");
            http.addHeader("Authorization" , "Bearer " + api_key);

            DynamicJsonDocument jsonDoc(JSON_BUFFER_LEN);

            JsonObject messageObj = GPTTalkLog["messages"].createNestedObject();
            messageObj["role"] = "user";
            messageObj["content"] = text;

            String jsonStr;
            serializeJson(GPTTalkLog, jsonStr);
            Serial.println("Request: " + jsonStr);

            int httpCode = http.POST(jsonStr);
            
            if (httpCode > 0) {
            String response = http.getString();
            Serial.println("GPT complete. ");
            Serial.println("httpCode: " + String(httpCode));
            Serial.println("Response: " + response);
            jsonDoc.clear();
            deserializeJson(jsonDoc, response);
            const char* content = jsonDoc["choices"][0]["message"]["content"];
            returnText = String(content);
            Serial.println("Response Content: " + returnText);

            JsonObject messageObj = GPTTalkLog["messages"].createNestedObject();
            messageObj["role"] = "assistant";
            messageObj["content"] = returnText;
            } else {
            Serial.println("Error: " + http.errorToString(httpCode));
            }
            wifiSecure.stop();

        } else {
            Serial.println("Error: WiFi Disconnected");
        }

        return returnText;
    }

    void xMod_OpenAI::SetAPIKey(String key){
        api_key = key;
    }

    void xMod_OpenAI::SetModel(String modelName){
        model = modelName;
    }
}