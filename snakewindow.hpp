#ifndef SNAKEWINDOW_HPP
#define SNAKEWINDOW_HPP

#include <QtCore/QtCore>
#include <QtWidgets/QtWidgets>
#include "jeu.hpp"


class SnakeWindow : public QFrame // le mot public signifie que SnakeWindow est un QFrame. Elle herite donc de toutes les capacites de QFrame. Et QFrame herite lui-meme de Qwidget.
// c'est dans la classe Qwidget ( la classe mere de toutes les fenetres Qt) que la fonction rect() est definie.
// Comme SnakeWindow est un classe fille donc elle herite tous les fonctionalite de la mere.
{

  protected:
    Jeu jeu;
    QPixmap pixmapCorps, pixmapTete, pixmapMur, pixFruit, pixMort;

  public:
    SnakeWindow(QWidget *pParent=nullptr, Qt::WindowFlags flags=Qt::WindowFlags());
    void handleTimer();
    void DemarrerJeu(bool b = true);
    Jeu& get_Jeu();
  protected:
    void paintEvent(QPaintEvent *);
    virtual void keyPressEvent(QKeyEvent *); //keyPressEvent est definie dans la classe QWidget (la classe mere de toutes les fenetres et widgets Qt)
    //Qt appelle cette fonction automatiquement quand l’utilisateur appuie sur une touche du clavier sur le widget qui a le focus.
    //Quand l’utilisateur appuie sur une touche dans la fenêtre → Qt appelle automatiquement SnakeWindow::keyPressEvent
  private slots:
    void Clicker_Ajouter_Mur();
    void Clicker_Retirer_Mur();
    void Temps_ecoule();
    QTimer *timerJeu;
    QTimer *timerTemps;


};

// Quand tu ajoutes un bouton (QPushButton) dans la fenêtre, le bouton prend le focus clavier.
// Le focus d’un widget, c’est l’objet qui reçoit les événements clavier à un moment donné.

#endif // SNAKEWINDOW_HPP
