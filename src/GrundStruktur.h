#ifndef SRC_GRUNDSTRUKTUR_H_
#define SRC_GRUNDSTRUKTUR_H_

#include <memory>
#include <gtkmm/window.h>
#include <gtkmm/grid.h>
#include <gtkmm/button.h>
#include <gtkmm/label.h>

class GrundStruktur : public Gtk::Window
{
    public:
        //GrundStruktur(std::initializer_list<std::unique_ptr<Gtk::Widget> > il);
        //GrundStruktur(std::unique_ptr<Gtk::Widget>);
        //GrundStruktur(Gtk::Widget*);
        GrundStruktur(std::initializer_list<Gtk::Widget* > il);
        ~GrundStruktur();
        void draw();

        //Gtk::Widget* get_akt_it();

    private:
        //Bildschirmaufteilung:
        Gtk::Grid grid_haupt_teilung;
        Gtk::Label spacer_links, spacer_rechts;

        //=rechts und links Platz für button zum toggeln der Mitte
        
        //buttons links und rechts zum durchtoggeln
        Gtk::Button button_mitte_wechsel_links;
        Gtk::Button button_mitte_wechsel_rechts;

        //Container für Widgets, die in der Mitte durchgetoggelt werden können
        std::vector<Gtk::Widget* > Mitte;
        std::vector<Gtk::Widget* >::iterator akt_it;
        
        //Signal handlers:
        void links_modus();  //durchtoggeln links
        void rechts_modus(); //durchtoggeln rechts
        //eine Funktion, die von GTK immer wieder getriggert wird
        //zum Beispiel um die aktuellsten Wetterdaten abzufragen
        bool again_and_again();
        //mit zugehöriger sigc::connection, um später aufräumen zu können
        sigc::connection dauerTrigger;
};

#endif /* SRC_GRUNDSTRUKTUR_H_ */