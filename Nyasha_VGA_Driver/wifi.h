#include <WiFi.h>

#define AP_NAME "Notice-Board"
#define AP_PASS "1234567890"

void initWiFiAP(){
  WiFi.softAP(AP_NAME, AP_PASS);
}
