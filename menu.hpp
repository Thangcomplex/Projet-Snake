#ifndef MENU_HPP
#define MENU_HPP

#include <QtCore/QtCore>
#include <QtWidgets/QtWidgets>

class Menu: public QWidget{

public:
    QPushButton *btnPlay;
    QPushButton *btnInfini;
    QPushButton *btnNiveaux;
    QPushButton *btnQuitter;
    Menu(QWidget *parent = nullptr);
public slots:
    void afficherChoixModes();
};


#endif
