#ifndef PocketbaseExtended_h
#define PocketbaseExtended_h

#include "Arduino.h"

#if defined(ESP8266)
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <BearSSLHelpers.h>
#elif defined(ESP32)
#include <HTTPClient.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#endif

class PocketbaseExtended
{
public:
    PocketbaseExtended(const char *baseUrl);

    PocketbaseExtended &collection(const char *collection);

    String getOne(const char *recordId, const char *expand = nullptr, const char *fields = nullptr);
    String deleteRecord(const char *recordId);
    String getList(const char *page = nullptr, const char *perPage = nullptr, const char *sort = nullptr, const char *filter = nullptr, const char *skipTotal = nullptr, const char *expand = nullptr, const char *fields = nullptr);
    String create(const String &requestBody);

private:
    String base_url;
    String current_endpoint;

    String performGETRequest(const char *endpoint);
    String performDELETERequest(const char *endpoint);
    String performPOSTRequest(const char *endpoint, const String &requestBody);
};

#endif