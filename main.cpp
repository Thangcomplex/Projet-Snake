#include <ctime>
#include "snakewindow.hpp"
#include "snakebutton.hpp"
#include <iostream>
#include "menu.hpp"
using namespace std;

int main(int argc, char *argv[])
{

    QApplication app(argc, argv); // mise en place de Qt

// 1. On crée le conteneur principal (La Fenêtre Unique)
    QStackedWidget pile;
    Menu menu;
    SnakeWindow jeu;

    pile.addWidget(&menu);
    pile.addWidget(&jeu);

    pile.setFixedSize(jeu.size());

    QObject::connect(menu.btnNiveaux,&QPushButton::clicked,[&]()
    {
        //jeu.get_Jeu().setModeTeleportation(false);
        pile.setCurrentIndex(1);
        jeu.DemarrerJeu(false);
    });
    QObject::connect(menu.btnInfini,&QPushButton::clicked,[&]()
    {
        //jeu.get_Jeu().setModeTeleportation(true);
        pile.setCurrentIndex(1);
        jeu.DemarrerJeu(true);
    });
    pile.show();
   // SnakeWindow wnd;
   // wnd.show();
    return app.exec();
  //    QWidget *w = new QWidget();
  //  w->show();
}
