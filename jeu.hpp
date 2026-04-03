#ifndef JEU_HPP
#define JEU_HPP

#include <vector>
#include <list>
#include "fmod.hpp"
#include <QtCore/QtCore>
#include <QtWidgets/QtWidgets>
typedef enum {VIDE, MUR, FRUIT, MORT} Case; //enumeration, on a nouveau type qui s'appelle Case, qui contient 2 valeur, Vide = 0 et Mur =1
typedef enum {GAUCHE, DROITE, HAUT, BAS} Direction; // pareil

extern std::vector<std::vector<std::string>> liste_de_niveau;
class Position
{
  public:
    int x, y;
    Position(); // constructeur par defaut
    Position(int,int);
    bool operator==(const Position &) const; //surcharge d'operateur
    bool operator!=(const Position &) const; // const a la` fin signifie que cette fonction ne modifiera pas l'objet.
    // On fait juste une comparaison, on ne change pas les coordonnees.
};

class Jeu: public QWidget
{
  protected:
    Case *terrain;
    int largeur, hauteur; // Nombre de cases en largeur et en hauteur
    std::list<Position> snake; // C'est le corps du serpent, avec les chevrons, on precise de quel type s'agit-il le variable
    // donc cette syntaxe nous donne une liste d'objet de type Position
    int niveau;
    const int NB_Niveau_max = 2;
    int Nb_Fruits_Manges;
    int TempsRestant;
    Direction dirSnake;
    bool collision_detecte;
    FMOD::System *fmodSystem;
    FMOD::Sound  *sonMiam;
    FMOD::Channel *channel;
    bool modeTeleportation = false;

  public:

    Jeu();
    Jeu(const Jeu &);
    ~Jeu(); // Destructeur

    Jeu &operator=(const Jeu &);

    bool init(); // Pour le mode niveau
    bool init_Infini();
    void evolue();

    // Retourne les dimensions (en nombre de cases)
    int getNbCasesX() const;
    int getNbCasesY() const;

    // Retourne la case � une position donn�e
    Case getCase(const Position &) const;

    void setCase(const Position &pos, Case type);

    // Retourne la liste des elements du serpent en lecture seule
    const std::list<Position> &getSnake() const;

    // Indique si la case � une position donn�e existe et est libre
    bool posValide(const Position &) const;

    // Modifie la direction
    void setDirection(Direction);

    // Placer Fruite Aleatoire
    void Placer_fruite_aleatoire();
    int getNiveau() const;
    int getFruitsManges() const;
    int getTempsRestant() const;
    bool Terminer() const; // Le jeu est termine?
    bool NiveauSuivant() const; // C'est le niveau suivant?
    void Temps_Ecoule();           // appelée chaque seconde
    bool passerNiveauSuivant();  // appelle quand le nb fruits est manges.
    bool Jeu_Terminer() const;
    bool Echoue() const;
    void setModeTeleportation(bool b);
    bool getModeTeleportation() const;
    void nettoyerTerrain();
    Position calculerNouvellePosition(Direction dir) const;
};

#endif
