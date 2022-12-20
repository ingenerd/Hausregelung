/*
 * helloworld.cpp
 *
 *  Created on: Dec 13, 2022
 *      Author: bejo
 */

#include "helloworld.h"
#include <iostream>
#include <gtkmm/cssprovider.h>

HelloWorld::HelloWorld()
: m_button("Hello World"), m_label("Toll!")  // creates a new button with label "Hello World".
{
  set_default_size(400, 400);
  set_border_width(20);

  // When the button receives the "clicked" signal, it will call the
  // on_button_clicked() method defined below.
  m_button.signal_clicked().connect(sigc::mem_fun(*this,&HelloWorld::on_button_clicked));

  m_grid.set_row_spacing(1);
  m_grid.set_column_spacing(2);

  m_grid.attach(m_button, 0, 0);
  m_grid.attach(m_label, 0, 1);

  add(m_grid);

  Glib::RefPtr<Gtk::CssProvider> css_provider = Gtk::CssProvider::create();
  css_provider->load_from_path("/home/bejo/eclipse-workspace/HausRegelung/style/styles.css");
  /*css_provider->load_from_data(
    "button {background-image: image(cyan);}\
     button:hover {background-image: image(green);}\
     button:active {background-image: image(brown);}\
     label {background-image: none;}\
	 window.background {background-image: url(\"/home/bejo/eclipse-workspace/HausRegelung/pics/test.jpeg\") }");
  */
  m_button.get_style_context()->add_provider(css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);
  m_label.get_style_context()->add_provider(css_provider, GTK_STYLE_PROVIDER_PRIORITY_USER);
  get_style_context()->add_provider(css_provider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

  // The final step is to display this newly created widget...
  m_button.show();
  show_all_children();
}

HelloWorld::~HelloWorld()
{
}

void HelloWorld::on_button_clicked()
{
  std::cout << "Hello World" << std::endl;
}



