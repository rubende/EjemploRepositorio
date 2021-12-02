#include "MQTTHandler.h"


void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}


MQTTHandler::MQTTHandler(WiFiClient client)
{
  _client = new PubSubClient(client);
  _client->setServer("mqtt_server", 1883);
  _client->setCallback(callback);
}

int MQTTHandler::sendData(String topic, String datos)
{
	_client->publish(topic.c_str(), datos.c_str());
}

void MQTTHandler::loop()
{
	if (!_client->connected()) {
    	reconnect();
 	}
 	_client->loop();
}

void MQTTHandler::reconnect() {
  // Loop until we're reconnected
  while (!_client->connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (_client->connect(clientId.c_str())) {
      Serial.println("connected");
      // ... and resubscribe
      _client->subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(_client->state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}