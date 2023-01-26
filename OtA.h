WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP    
WiFi.setSleepMode(WIFI_NONE_SLEEP);
WiFi.begin(ssid, pass); 
while (WiFi.waitForConnectResult() != WL_CONNECTED) {
  Serial.println("Connection Failed! Rebooting...");
  delay(5000);
  ESP.restart();
}

WiFi.config(ip, gateIP, subIP);

ArduinoOTA.setHostname(HOSTNAME);
ArduinoOTA.setPort(8266);
ArduinoOTA.begin();

Udp.begin(udpPort);
//Udp.beginMulticast(ip, multicast, udpPort);
