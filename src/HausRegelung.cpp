#include "Dachgeschoss.h"
#include <gtkmm/application.h>
/*
#include <iostream>
#include <stdio.h>

#include <mosquitto.h>
void message_callback(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message)
{
	bool match = 0;
	printf("got message '%.*s' for topic '%s'\n", message->payloadlen, (char*) message->payload, message->topic);

	mosquitto_topic_matches_sub("test", message->topic, &match);
	if (match) {
		printf("got message for ADC topic\n");
	}
}


// to make sure, mosquitto quits on termination, I guess...
#include <signal.h> 
static int run = 1;
void handle_signal(int s)
{
	run = 0;
}
*/
int main (int argc, char *argv[])
{
  /*
  signal(SIGINT, handle_signal);
	signal(SIGTERM, handle_signal);
  struct mosquitto *mosq;
  mosq = mosquitto_new(NULL, true, 0);
  mosquitto_message_callback_set(mosq, message_callback);
  int what;
  what= mosquitto_connect(mosq, "localhost", 1883, 60);
  std::cout << "Connect: " << what << std::endl;

  mosquitto_subscribe(mosq, NULL, "test", 0);

  
  while (1)
  {
    what = mosquitto_loop(mosq, 1000, 1);
    std::cout << "Loop: " << what << std::endl;
    sleep(10);
  }*/

  auto app = Gtk::Application::create(argc, argv, "LBW.Dachgeschoss");

  Dachgeschoss dachgeschoss;
  
  //Shows the window and returns when it is closed.
  return app->run(dachgeschoss);
}
