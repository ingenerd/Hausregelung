// Anzeige.h
// Die Anzeige als DrawingArea links im goldenen Schnitt des Bildschirms

#ifndef SRC_ANZEIGE_H_
#define SRC_ANZEIGE_H_

#include "definitions.h"
#include "Punkt.h"
#include <string>

#include <gtkmm/drawingarea.h>

class Anzeige : public Gtk::DrawingArea
{
public:
  Anzeige();
  virtual ~Anzeige(); 
  void set_t(float value, ZimmerTemp identifier);
  void set_modus(Visualisierung akt);
  Visualisierung get_modus();
  int get_pos(char Richtung, ZimmerRolladen identifier);
  int get_RollBoxBreite();
  void toggle_r_auswahl(ZimmerRolladen identifier);

private:
  //signal handler:
  bool on_anzeige_clicked(GdkEventButton*); //Reaktion auf Klick in Anzeige
  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
  void zeigeGrundriss(const Cairo::RefPtr<Cairo::Context>& cr);
  void zeigeSchema(const Cairo::RefPtr<Cairo::Context>& cr);
  void zeigeTemp(const Cairo::RefPtr<Cairo::Context>& cr, float t_IST, float t_SOLL, Punkt pkt);
  void zeigeRolladenBox(const Cairo::RefPtr<Cairo::Context>& cr, bool auswahl, Punkt pkt);

  //Temperaturen
  float t_Bad_IST;
  float t_Bad_SOLL;
  float t_KiVo_IST;
  float t_KiVo_SOLL;
  float t_KiHi_IST;
  float t_KiHi_SOLL;
  float t_Elt_IST;
  float t_Elt_SOLL;

  //Rolläden
  bool wahl_Bad;
  bool wahl_KiVo1;
  bool wahl_KiVo2;
  bool wahl_KiHi1;
  bool wahl_KiHi2;
  bool wahl_Elt;

  RolladenZust r_Bad;
  RolladenZust r_KiVo1;
  RolladenZust r_KiVo2;
  RolladenZust r_KiHi1;
  RolladenZust r_KiHi2;
  RolladenZust r_Elt;

  //Positionen 
  //Temperaturanzeigen
  Punkt pkt_t_Bad;
  Punkt pkt_t_KiVo;
  Punkt pkt_t_KiHi;
  Punkt pkt_t_Elt;

  Punkt pkt_r_Bad;
  Punkt pkt_r_KiVo1;
  Punkt pkt_r_KiVo2;
  Punkt pkt_r_KiHi1;
  Punkt pkt_r_KiHi2;
  Punkt pkt_r_Elt;

  int breiteBox;
  int x_rBox_Bad;
  int y_rBox_Bad;
  int x_rBox_KiVo1;
  int y_rBox_KiVo1;
  int x_rBox_KiVo2;
  int y_rBox_KiVo2;
  int x_rBox_KiHi1;
  int y_rBox_KiHi1;
  int x_rBox_KiHi2;
  int y_rBox_KiHi2;
  int x_rBox_Elt;
  int y_rBox_Elt;

  //aktuelle Ansicht
  Visualisierung aktModus;
};

#endif /* SRC_ANZEIGE_H_ */