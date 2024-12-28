#include <AUnit.h>
#include "PocketbaseExtended.h"

// Mock WiFi and HTTPClient for testing
class MockWiFiClientSecure : public WiFiClientSecure
{
public:
    void setInsecure() {}
};

class MockHTTPClient : public HTTPClient
{
public:
    void begin(WiFiClientSecure &client, const char *url) {}
    void begin(const char *url) {}
    int GET() { return 200; }
    int POST(const String &payload) { return 200; }
    int sendRequest(const char *method) { return 200; }
    String getString() { return "{\"result\":\"success\"}"; }
    void end() {}
};

PocketbaseExtended pocketbase("http://example.com");

test(getOneTest)
{
    pocketbase.collection("testCollection");
    String result = pocketbase.getOne("recordId");
    assertEqual(result, "{\"result\":\"success\"}");
}

test(getListTest)
{
    pocketbase.collection("testCollection");
    String result = pocketbase.getList("1", "10");
    assertEqual(result, "{\"result\":\"success\"}");
}

test(createTest)
{
    pocketbase.collection("testCollection");
    String result = pocketbase.create("{\"name\":\"test\"}");
    assertEqual(result, "{\"result\":\"success\"}");
}

test(deleteRecordTest)
{
    pocketbase.collection("testCollection");
    String result = pocketbase.deleteRecord("recordId");
    assertEqual(result, "{\"result\":\"success\"}");
}

void setup()
{
    // Initialize AUnit
    aunit::TestRunner::run();
}

void loop()
{
    // Run AUnit tests
    aunit::TestRunner::run();
}