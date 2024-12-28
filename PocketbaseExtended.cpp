#include "PocketbaseExtended.h"

PocketbaseExtended::PocketbaseExtended(const char *baseUrl)
{
    base_url = baseUrl;
    if (base_url.endsWith("/"))
    {
        base_url.remove(base_url.length() - 1);
    }
    base_url += "/api/";
    current_endpoint = base_url;
}

PocketbaseExtended &PocketbaseExtended::collection(const char *collection)
{
    current_endpoint = "collections/" + String(collection) + "/";
    return *this;
}

void PocketbaseExtended::initializeHttpClient(HTTPClient &http, const char *endpoint)
{
#if defined(ESP32)
    std::unique_ptr<WiFiClientSecure> client(new WiFiClientSecure);
    client->setInsecure();
    if (strncmp(endpoint, "https", 5) == 0)
    {
        http.begin(*client, endpoint);
    }
    else
    {
        http.begin(endpoint);
    }
#elif defined(ESP8266)
    std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);
    client->setInsecure();
    if (strncmp(endpoint, "https", 5) == 0)
    {
        http.begin(*client, endpoint);
    }
    else
    {
        http.begin(endpoint);
    }
#endif
}

String PocketbaseExtended::performGETRequest(const char *endpoint)
{
    HTTPClient http;
    initializeHttpClient(http, endpoint);

    int httpCode = http.GET();
    if (httpCode > 0)
    {
        String payload = http.getString();
        http.end();
        return payload;
    }
    else
    {
        http.end();
        return ""; // Return an empty string on failure
    }
}

String PocketbaseExtended::performDELETERequest(const char *endpoint)
{
    HTTPClient http;
    initializeHttpClient(http, endpoint);

    int httpCode = http.sendRequest("DELETE");
    if (httpCode > 0)
    {
        String payload = http.getString();
        http.end();
        return payload;
    }
    else
    {
        http.end();
        return ""; // Return an empty string on failure
    }
}

String PocketbaseExtended::performPOSTRequest(const char *endpoint, const String &requestBody)
{
    HTTPClient http;
    initializeHttpClient(http, endpoint);

    int httpCode = http.POST(requestBody);
    if (httpCode > 0)
    {
        String payload = http.getString();
        http.end();
        return payload;
    }
    else
    {
        http.end();
        return ""; // Return an empty string on failure
    }
}

String PocketbaseExtended::getOne(const char *recordId, const char *expand, const char *fields)
{
    String fullEndpoint = base_url + String(current_endpoint) + "records/" + recordId;

    if (expand != nullptr && strlen(expand) > 0)
    {
        fullEndpoint += "?expand=" + String(expand);
    }

    if (fields != nullptr && strlen(fields) > 0)
    {
        fullEndpoint += (fullEndpoint.indexOf('?') == -1) ? "?" : "&";
        fullEndpoint += "fields=" + String(fields);
    }

    return performGETRequest(fullEndpoint.c_str());
}

String PocketbaseExtended::getList(const char *page, const char *perPage, const char *sort, const char *filter, const char *skipTotal, const char *expand, const char *fields)
{
    String fullEndpoint = base_url + String(current_endpoint) + "records/";

    auto appendQueryParam = [&](const char *paramName, const char *paramValue)
    {
        if (paramValue != nullptr && strlen(paramValue) > 0)
        {
            fullEndpoint += (fullEndpoint.indexOf('?') == -1) ? "?" : "&";
            fullEndpoint += String(paramName) + "=" + String(paramValue);
        }
    };

    appendQueryParam("expand", expand);
    appendQueryParam("fields", fields);
    appendQueryParam("page", page);
    appendQueryParam("perPage", perPage);
    appendQueryParam("sort", sort);
    appendQueryParam("skipTotal", skipTotal);
    appendQueryParam("filter", filter);

    return performGETRequest(fullEndpoint.c_str());
}

String PocketbaseExtended::deleteRecord(const char *recordId)
{
    String fullEndpoint = base_url + String(current_endpoint) + "records/" + recordId;
    return performDELETERequest(fullEndpoint.c_str());
}

String PocketbaseExtended::create(const String &requestBody)
{
    String fullEndpoint = current_endpoint + "records/";
    return performPOSTRequest(fullEndpoint.c_str(), requestBody);
}