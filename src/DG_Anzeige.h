// Anzeige.h
// Die Anzeige als DrawingArea links im goldenen Schnitt des Bildschirms

#ifndef SRC_DG_ANZEIGE_H_
#define SRC_DG_ANZEIGE_H_

#include "definitions.h"
#include "Punkt.h"
#include "Daten.h"
#include <string>

#include <gtkmm/drawingarea.h>

// forward declaration hier, da eine Referenz zum Dachgeschoss eingesetzt wird...
// im cpp die komplette Einbindung über include, da darin auch Methoden genutzt werden...
class Dachgeschoss; 

class DG_Anzeige : public Gtk::DrawingArea
{
public:
  DG_Anzeige(std::shared_ptr<Daten>& data, Dachgeschoss& mutter);
  virtual ~DG_Anzeige(); 
  
  // Was angezeigt wird
  void set_modus(Visualisierung akt);
  Visualisierung get_modus();

  int get_pos(char Richtung, ZimmerRolladen identifier);
  void toggle_r_auswahl(ZimmerRolladen identifier);

private:
  std::shared_ptr<Daten>& allData;

  //für die Solltemperatur
  sigc::signal<void (TEMP_ENUM)> signal_tSollMenu;

  //signal handler:
  bool on_anzeige_clicked(GdkEventButton*); //Reaktion auf Klick in Anzeige
  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
  void zeigeGrundriss(const Cairo::RefPtr<Cairo::Context>& cr);
  void zeigeSchema(const Cairo::RefPtr<Cairo::Context>& cr);
  void zeigeTemp(const Cairo::RefPtr<Cairo::Context>& cr, float t_IST, float t_SOLL, Punkt pkt);
  void zeigeRolladenBox(const Cairo::RefPtr<Cairo::Context>& cr, bool auswahl, Punkt pkt);

  //Positionen Grundriss
  //Temperaturanzeigen
  Punkt pkt_t_Bad;
  Punkt pkt_t_KiVo;
  Punkt pkt_t_KiHi;
  Punkt pkt_t_Elt;
  //Rolläden Hakenbox
  Punkt pkt_r_Bad;
  Punkt pkt_r_KiVo1;
  Punkt pkt_r_KiVo2;
  Punkt pkt_r_KiHi1;
  Punkt pkt_r_KiHi2;
  Punkt pkt_r_Elt;
  int breiteBox;

  //aktuelle Ansicht
  Visualisierung aktModus;
};

#endif /* SRC_DG_ANZEIGE_H_ */