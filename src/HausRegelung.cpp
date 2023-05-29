#include <iostream>

#include <mosquitto.h>

#include "Daten.h"
#include "GrundStruktur.h"
#include "Dachgeschoss.h"
#include <memory>
#include <gtkmm/application.h>
#include <gtkmm/button.h>

// die mosquitto handler kriege ich nicht in eine class oder einen namespace rein
// da die *_set-Methoden (z.B.: mosquitto_message_callback_set) der mosquitto API (*void) als Returnierwert verlangen, wüsste ich nicht wie ich auf eine Funktion innerhalb eines namepsaces casten kann...
// Deklaration hier - Definition unten
void mosq_message_callback(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message);

// Globales Signal, dass auch in Handlern aus Fremdbibliotheken (mosquitto) genutzt (emittiert) werden kann, die sonst nicht weitere Parameter kriegen können...
// Wird signal_info_erhalten emittiert, wird über Umwege die queue_draw()-methode der aktuellen Anzeige getriggert
sigc::signal<void ()> signal_info_erhalten;

int main (int argc, char *argv[])
{
  //GTK-Applikation
  auto app = Gtk::Application::create(argc, argv, "LBW.Touchscreen.DG");

  // Shared Pointer zum Manipulieren der Daten auf Datenonjekt
  // (z.B.: Sollwerte über Programm oder Istwerte über Sensoren...)
  auto data = std::make_shared<Daten>();

  // Selbstgebaute Inhalte, die in der Mitte durchgetoggelt werden können.
  // Es müssen Zeiger auf Gtk::Widget (Gtk::Grid) sein.
  // Unique_ptr (mit oder ohne std::make_unique) tun es nicht, da die Grundstruktur mit einer Initializer List instanziiert wird.
  Gtk::Widget* ho = new Gtk::Button("");
  Gtk::Widget* hey = new Gtk::Button("Oha");
  ho->set_size_request(55,200);
  Gtk::Widget* pDachgeschoss = new Dachgeschoss(data);

  GrundStruktur* pGrundStruktur = new GrundStruktur{pDachgeschoss, ho, hey};
  // Verknüpfung zum globalen Signal, wenn der mosquitto Handler gelaufen ist. 
  signal_info_erhalten.connect(sigc::mem_fun(*pGrundStruktur, &GrundStruktur::draw));

  //Mosquitto-Instanz (reine C-Bibliothek) zur Kommunikation über mqtt
  struct mosquitto *mosq;
  mosq = mosquitto_new(NULL, true, data.get());
  //mosq = mosquitto_new(NULL, true, grundStruktur);
  mosquitto_message_callback_set(mosq, mosq_message_callback);
  mosquitto_connect(mosq, "localhost", 1883, 60);
  mosquitto_subscribe(mosq, NULL, "Sensoren/T/+", 0);
  mosquitto_loop_start(mosq);

  // Start der GUI
  int eStatus = app->run(*pGrundStruktur);

  // Aufräumen
  delete ho;
  delete hey;
  delete pDachgeschoss;
  delete pGrundStruktur;

  mosquitto_unsubscribe(mosq, NULL, "Sensoren/T/+");
  mosquitto_destroy(mosq);
  mosquitto_lib_cleanup();

  return eStatus;
}

void mosq_log_light(std::string text)
{
    auto now = std::chrono::system_clock::now().time_since_epoch();
    long millis = static_cast<long>(std::chrono::duration_cast<std::chrono::milliseconds>(now).count());
    long seccis = millis/1000;
    millis = millis%1000;
    std::cerr << seccis << "." << millis << ": " << text << std::endl; 
}

void mosq_message_callback(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message)
{
  bool match = 0;
	std::string payL((char*)message->payload);
  std::string top((char*)message->topic);
  
	// std::cout << "Got message " << payL << " for topic " << top << std::endl;

	mosquitto_topic_matches_sub("Sensoren/T/+", message->topic, &match);
  if (match) {
    if (top == "Sensoren/T/KiVo") {
      try { static_cast<Daten *>(obj)->set_t(T_KiVo_IST, std::stof(payL)); }
      catch (...) { mosq_log_light("MQTT Wert unplausibel für T_KiVo_IST!"); }
    }
    if (top == "Sensoren/T/KiHi") {
      try { static_cast<Daten *>(obj)->set_t(T_KiHi_IST, std::stof(payL)); }
      catch (...) { mosq_log_light("MQTT Wert unplausibel für T_KiHi_IST!"); }
    }
    if (top == "Sensoren/T/Bad") {
      try { static_cast<Daten *>(obj)->set_t(T_BAD_IST, std::stof(payL)); }
      catch (...) { mosq_log_light("MQTT Wert unplausibel für T_BAD_IST!"); }
    }
    if (top == "Sensoren/T/Elt") {
      try { static_cast<Daten *>(obj)->set_t(T_ELT_IST, std::stof(payL)); }
      catch (...) { mosq_log_light("MQTT Wert unplausibel für T_ELT_IST!"); }
    }
  }
  signal_info_erhalten.emit();
}