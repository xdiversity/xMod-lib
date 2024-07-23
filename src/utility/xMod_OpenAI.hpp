#ifndef __XMOD_OPENAI_CLASS_H__
#define __XMOD_OPENAI_CLASS_H__

#include "xMod_common.h"

#define JSON_BUFFER_LEN (1024 * 80) 

namespace xdiversity
{
    class xMod_OpenAI {
        public:
            xMod_OpenAI(){}

            String GPT(String text);

            void SetAPIKey(String key);

            void SetModel(String modelName);

        private:
            WiFiClientSecure wifiSecure;
            HTTPClient http;
            bool firstTry = true;
            DynamicJsonDocument GPTTalkLog{JSON_BUFFER_LEN};
            String api_key;
            String model;

    };
}

#endif