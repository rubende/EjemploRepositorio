#ifndef MQTTHANDLER_H_
#define MQTTHANDLER_H_

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

class MQTTHandler
{
	public:
		MQTTHandler(WiFiClient client);
		int sendData(String topic, String datos);
		void loop();
	private:
		PubSubClient* _client;
		void reconnect();
};

#endif
