#include "menu.hpp"

Menu::Menu(QWidget *parent) : QWidget(parent) {

    QVBoxLayout *layout = new QVBoxLayout(this);

    // Creation des boutons
    btnPlay    = new QPushButton(" Jouer ", this); // Retire le "QPushButton*" devant
    btnQuitter = new QPushButton(" Quitter ", this);
    btnNiveaux = new QPushButton(" MODE AVENTURE (Niveaux) ", this);
    btnInfini  = new QPushButton(" MODE ARCADE (Infini) ", this);

    // Cacher les modes au demarrage:
    btnNiveaux->hide();
    btnInfini->hide();

    // Ajouter les boutons
    layout->addWidget(btnPlay);
    layout->addWidget(btnQuitter);
    layout->addWidget(btnNiveaux);
    layout->addWidget(btnInfini);

    // Connexion:
    connect(btnPlay,&QPushButton::clicked, this, &Menu::afficherChoixModes);
    connect(btnQuitter, &QPushButton::clicked, qApp, &QCoreApplication::quit); //prend toujours 4 arguement
}

void Menu::afficherChoixModes()
{
    btnPlay->hide();

    btnNiveaux->show();
    btnInfini->show();

    btnQuitter->setText(" Retour ");
}
