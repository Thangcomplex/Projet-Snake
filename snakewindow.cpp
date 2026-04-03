#include <iostream>
#include "snakewindow.hpp"
#include "snakebutton.hpp"

using namespace std;

SnakeWindow::SnakeWindow(QWidget *pParent, Qt::WindowFlags flags):QFrame(pParent, flags) // SnakeWindow herite de QFrame
{

    // Taille des cases en pixels
    int largeurCase, hauteurCase;
    // QPixmap  = image utilisee pour dessiner
    if (pixmapCorps.load("./data/snake_corps.png")== false)
    {
        cout<<"Impossible d'ouvrir snake_corps.png"<<endl;
        exit(-1);
    }
    if (pixmapTete.load("./data/snake_tete.png")==false)
    {
        cout<<"Impossible d'ouvrir snake_tete.png"<<endl;
        exit(-1);
    }
    if (pixmapMur.load("./data/mur.bmp")==false)
    {
        cout<<"Impossible d'ouvrir mur.bmp"<<endl;
        exit(-1);
    }
    if (pixFruit.load("./data/Melon.png")==false)
    {
        cout<<"Impossible d'ouvrir Melon.png"<<endl;
        exit(-1);
    }
    if (pixMort.load("./data/Wooden_Fence.png") == false)
    {
        cout<<"Impossible d'ouvrir Wooden_Fence.png"<<endl;
        exit(-1);
    }
    //connect(btn, &QPushButton::clicked, this, &SnakeButton::clickMonBouton);
    jeu.init();
    const int OFFSET_y = 40;
    // QPushButton: est une classe qui fait partie de la bibliotheque officiele de Qt.

    //QTimer *timer = new QTimer(this); //Le Qtimer est comme un metronome (may dem nhip)
    timerJeu = new QTimer(this);
    connect(timerJeu, &QTimer::timeout, this, &SnakeWindow::handleTimer);
    //timer->start(100); // Ici il sonne toutes les 100 ms ( 10 fois par seconde)
    // a chaque fois qu'il sonne, il appelle la fonction handleTimer, c'est cette fonction qui demande au jeu de calculer la nouvelle position
    //(jeu.evolue()) et dit a` Qt : "Hé, les choses ont changé, redessine l'écran !" (update()).

//    connect(btn, &QPushButton:clicked, this, &SnakeWindow::clickMonBouton)
    largeurCase = pixmapMur.width();    // recupere la largeur de kl'image en pixels
    hauteurCase = pixmapMur.height();   // Recupere la hauteur de l'image en pixels.

    // ex: si mon image fait 20x20 pixels, alors chaque case du jeu fera 20x20 pixels.
    // donc la taille du ma terasse change automatiquement selon la taille du mur, tu veut dire ?
                //largeur  ca nous donne la taille en pixels                    //hauteur
    //resize(jeu.getNbCasesX()*largeurCase, jeu.getNbCasesY()*hauteurCase + OFFSET_y); // on ajuste la taille de la fenetre pour qu'elle corresponde exactement au nobmre de cases multuplie par la taille d'une image.
    this->setFixedSize(jeu.getNbCasesX()*largeurCase, jeu.getNbCasesY()*hauteurCase + OFFSET_y);
    // Bouton ajouter d'un mur:
    SnakeButton *btnAjouter = new SnakeButton("Ajouter",this);
    btnAjouter->setGeometry(0,0,150,40); // x,y,largeur,hauteur
    connect(btnAjouter, &QPushButton::clicked, this, &SnakeWindow::Clicker_Ajouter_Mur);

    // Bouton Retirer un mur:
    SnakeButton *btnRetirer = new SnakeButton("Retirer un mur", this);
    btnRetirer ->setGeometry(170,0,150,40);
    connect(btnRetirer, &QPushButton::clicked, this, &SnakeWindow::Clicker_Retirer_Mur);

    timerTemps = new QTimer(this);
    connect(timerTemps,&QTimer::timeout,this,&SnakeWindow::Temps_ecoule);
    //timerTemps->start(1000); // 1000ms = 1s
}

void SnakeWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this); // sans lui, on ne peut pas dessiner. Qpainter est une classe, ici on appele un constructeur.

    painter.fillRect(rect(),Qt::white); // rect(): renvoie un objet de type Qrect
    // Ce rectangle contient quatre information sur la fenetre:
    // x: 0 (le bord gauche) ,  y : 0 (le bord haut), width: la largeur actuelle de ma fenetre, height: la hauteur  actuelle de ta fenetre

    const int OFFSET_Y = 40;
    Position pos;

    // Taille des cases en pixels
    int largeurCase, hauteurCase;

    largeurCase = pixmapMur.width();
    hauteurCase = pixmapMur.height();

    // Dessine les trucs:
    for (pos.y=0;pos.y<jeu.getNbCasesY();pos.y++) // < hauteur
        for (pos.x=0;pos.x<jeu.getNbCasesX();pos.x++)
			if (jeu.getCase(pos)==MUR)
                painter.drawPixmap(pos.x*largeurCase, pos.y*hauteurCase + OFFSET_Y, pixmapMur);
            else if (jeu.getCase(pos) == FRUIT)
                painter.drawPixmap(pos.x*largeurCase, pos.y*hauteurCase + OFFSET_Y, pixFruit);
            else if (jeu.getCase(pos) == MORT)
                painter.drawPixmap(pos.x*largeurCase, pos.y*hauteurCase + OFFSET_Y, pixMort);
            // ici il faut savoir aussi qu'il y a encore un else pour dire que sinon, on ne fait rien comme ca.
    // Dessine le serpent
    const list<Position> &snake = jeu.getSnake();
    if (!snake.empty())
    {
        list<Position>::const_iterator itSnake;
        const Position &posTete = snake.front();
        painter.drawPixmap(posTete.x*largeurCase, posTete.y*hauteurCase +OFFSET_Y, pixmapTete);

        for (itSnake=++snake.begin(); itSnake!=snake.end(); itSnake++)
            painter.drawPixmap(itSnake->x*largeurCase, itSnake->y*hauteurCase+OFFSET_Y, pixmapCorps);
    }
    painter.drawText(340,20, "Niveau: "  + QString::number(jeu.getNiveau()));
    if (jeu.getModeTeleportation())
    {
            painter.drawText(440,20, "Fruits: "  + QString::number(jeu.getFruitsManges()));
    }
    else
    {
            painter.drawText(440,20, "Fruits: "  + QString::number(jeu.getFruitsManges()) +"/3");

    }
    painter.drawText(540,20, "Temps:  "  + QString::number(jeu.getTempsRestant())+ "s");
}

void SnakeWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key()==Qt::Key_Left)
        jeu.setDirection(GAUCHE); //  etant donne que POSITION est un enum => Gauche = 0 comme valeur commence'
    else if (event->key()==Qt::Key_Right)
        jeu.setDirection(DROITE); // 1 // fait la conversion en 0, 1 ,2 ,3
    else if (event->key()==Qt::Key_Up)
        jeu.setDirection(HAUT);// 2
    else if (event->key()==Qt::Key_Down)
        jeu.setDirection(BAS);// 3
    update();
}

void SnakeWindow::Clicker_Ajouter_Mur()
{
    int x = rand() % jeu.getNbCasesX();
    int y = rand() % jeu.getNbCasesY();
    Position pos(x,y);

    if (jeu.getCase(Position(x,y))== VIDE){
        jeu.setCase(pos,MUR);
        update();
    }
}

void SnakeWindow::Clicker_Retirer_Mur()
{
    int x = rand() % jeu.getNbCasesX();
    int y = rand() % jeu.getNbCasesY();
    Position pos(x,y);

    if (jeu.getCase(Position(x,y))== MUR){
    jeu.setCase(pos,VIDE);
    update();
    }
}

void SnakeWindow::handleTimer()
{
// On ne fait évoluer le jeu que si ce n'est pas déjà fini
    jeu.evolue();
    if (jeu.NiveauSuivant()&& !jeu.getModeTeleportation())
    {
        if(jeu.passerNiveauSuivant())
        {
        QMessageBox::information(this, "Niveau suivant ! ⭐",
            "Bien joué ! Tu passes au niveau "
            + QString::number(jeu.getNiveau()) + " !\n"
            "Attention, il y a plus de murs !");
           // jeu.passerNiveauSuivant();
        }
        else
        {
            // passerNiveauSuivant() a renvoyé FALSE :
            // Ça veut dire qu'il n'y a plus de niveaux dans la liste !
            QMessageBox::information(this, "🎉 Félicitations !",
                "Bravo ! Tu as terminé TOUS les niveaux !\n"
                "Tu es un vrai champion du Snake ! 🐍");

            jeu.init(); // On repart au niveau 0
        }
    }
    if (jeu.Echoue()||jeu.Terminer())
    {
        timerJeu->stop();
        timerTemps->stop();
        QMessageBox msgBox;
        msgBox.setWindowTitle("Game Over 🐍");
        msgBox.setInformativeText("Veux-tu rejouer ou quitter?");
        QPushButton *rejouerBtn = msgBox.addButton("Rejouer", QMessageBox::ActionRole);
        QPushButton *quitterBtn = msgBox.addButton("Quitter", QMessageBox::RejectRole);
        msgBox.exec(); // On affiche la boîte et on attend le clic

    if (msgBox.clickedButton() == rejouerBtn) {
        // --- CAS REJOUER ---

        if (jeu.getModeTeleportation())
        {
            jeu.init_Infini();
            jeu.setModeTeleportation(true);
        }
        else
        {
            jeu.init();             // On remet le serpent à zéro
        }
        timerJeu->start(100);    // On relance les chronos
        timerTemps->start(1000);
        update();
    }
    else if (msgBox.clickedButton() == quitterBtn) {
        // --- CAS QUITTER ---
        qApp->quit(); // Ferme complètement l'application
    }
    }
    update();
}

void SnakeWindow::Temps_ecoule()
{
    jeu.Temps_Ecoule();
    update();

    if (jeu.Terminer())
    {
        QMessageBox::information(this, "Game Over 💀",
            "Temps écoulé ! Tu n'as mangé que "
            + QString::number(jeu.getFruitsManges())
            + " fruits sur 3.\nEssaie encore !");
        jeu.init();
        update();
    }
}

void SnakeWindow::DemarrerJeu(bool mode_teleportation)
{
    if(mode_teleportation)
    {
        jeu.init_Infini();
        jeu.setModeTeleportation(true);
    }
    else
    {
        jeu.init();
        jeu.setModeTeleportation(false);
    }
    timerJeu->start(100);
    timerTemps->start(1000);
    this->setFocus();
}

Jeu& SnakeWindow::get_Jeu()
{
    return jeu;
}
