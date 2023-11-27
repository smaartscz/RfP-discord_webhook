#define mqtt_version "2023.11.27"

#define currTime_mqtt "RfP/currTime"
#define currTime_mqtt_name "Current time"
#define unixTime_mqtt "RfP/unixTime"
#define unixTime_mqtt_name "Unix time"

#define currTime_auto "{\"state_topic\": \""currTime_mqtt"\",\"name\": \""currTime_mqtt_name"\",\"icon\": \"mdi:clock-check-outline\",\"dev\": {\"ids\": [\""my_hostname"\"],\"name\": \""my_hostname"\",\"manufacturer\": \"DIY\",\"mdl\": \"ESP32\",\"sw\": \""mqtt_version"\"}}"
#define unixTime_auto "{\"state_topic\": \""unixTime_mqtt"\",\"name\": \""unixTime_mqtt_name"\",\"icon\": \"mdi:clock-check-outline\",\"dev\": {\"ids\": [\""my_hostname"\"],\"name\": \""my_hostname"\",\"manufacturer\": \"DIY\",\"mdl\": \"ESP32\",\"sw\": \""mqtt_version"\"}}"
