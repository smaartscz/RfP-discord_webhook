#include "time.h"
void RfP();
void RfP_check(){
  struct tm timeinfo;    
if (timeinfo.tm_yday >= 90 && timeinfo.tm_yday <= 301){
        if (timeinfo.tm_hour == 12 && timeinfo.tm_min == 00 && timeinfo.tm_sec == 0){
            RfP(); // Trigger RfP funkci
        }
        
}
else if (timeinfo.tm_hour == 13 && timeinfo.tm_min == 00 && timeinfo.tm_sec == 0){
    RfP(); // Trigger RfP funkci
}
}