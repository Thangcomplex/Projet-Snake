#include <iostream>
#include <cassert>
#include "jeu.hpp"
#include <vector>

using namespace std;


vector<vector<string>>liste_de_niveau = {
    {  // 15 lignes, 21 colonne.
		"####################",
		"#..................#",
		"#..................#",
		"#.......@..........#",
		"#..................#",
		"#..................#",
		"#..................#",
		"#..................#",
		"#..................#",
		"#..................#",
		"#..................#",
		"#..................#",
		"#..................#",
		"#..................#",
        "####################"
    },
    {  // 15 lignes, 21 colonne.
		"####################",
		"#...!!!!!!!!!!!!...#",
		"#.@................#",
		"#...!!!!!!!!!!!!...#",
		"#..................#",
		"#...!!!!!!!!!!!!...#",
		"#..................#",
		"#...!!!!!!!!!!!!...#",
		"#..................#",
		"#...!!!!!!!!!!!!...#",
		"#..................#",
		"#...!!!!!!!!!!!!...#",
		"#..................#",
		"#...!!!!!!!!!!!!...#",
        "####################"
    },
    {  // 15 lignes, 21 colonne.
		"####################",
		"#...!.......!......#",
		"#...!...!...!...!..#",
		"#.@.!...!...!...!..#",
		"#...!...!...!...!..#",
		"#...!...!...!...!..#",
		"#...!...!...!...!..#",
		"#...!...!...!...!..#",
		"#...!...!...!...!..#",
		"#...!...!...!...!..#",
		"#...!...!...!...!..#",
		"#...!...!...!...!..#",
		"#...!...!...!...!..#",
		"#.......!.......!..#",
        "####################"
    }
    };

Position::Position()
{
}

Position::Position(int a, int b)
{
    x=a;
    y=b;
}

bool Position::operator==(const Position &pos) const
{
    return (x==pos.x && y==pos.y);
}

bool Position::operator!=(const Position &pos) const
{
    return (x!=pos.x || y!=pos.y);
}

Jeu::Jeu()
{
    terrain = nullptr;
    largeur = 0; hauteur = 0;
    dirSnake = DROITE;
}

// quand on ecrit snake(jeu.snake), on appelle en fait le constructeur de recopie de std::list
Jeu::Jeu(const Jeu &jeu):snake(jeu.snake) // apres : c'est la liste d'initialisation. On demande au C++
// de copier toute la liste du serpent du modele vers le nouveau jeu
{
    largeur = jeu.largeur;
    hauteur = jeu.hauteur;
    dirSnake = jeu.dirSnake;

    if (jeu.terrain!=nullptr)
    {
        terrain = new Case[largeur*hauteur];
        for (int c=0; c<largeur*hauteur; c++)
            terrain[c] = jeu.terrain[c];
    }
    else
        terrain = nullptr;
}

Jeu::~Jeu()
{
    sonMiam->release();
    fmodSystem->close();
    fmodSystem->release();
    if (terrain!=nullptr)
        delete[] terrain;
}

Jeu &Jeu::operator=(const Jeu &jeu)
{
    if (terrain!=nullptr)
        delete[] terrain;

    largeur = jeu.largeur;
    hauteur = jeu.hauteur;
    dirSnake = jeu.dirSnake;
    snake = jeu.snake;

    if (jeu.terrain!=nullptr)
    {
        terrain = new Case[largeur*hauteur];
        for (int c=0; c<largeur*hauteur; c++)
            terrain[c] = jeu.terrain[c];
    }
    else
        terrain = nullptr;
    return *this;
}

bool Jeu::init()
{
	int x, y;
    dirSnake = DROITE;
	niveau = 0;
	Nb_Fruits_Manges = 0;
	TempsRestant = 50;
	collision_detecte =false;

	// list<Position>::iterator itSnake;

	const vector<string>terrain_defaut = liste_de_niveau[0];

	largeur = 20;
	hauteur = 15;

	terrain = new Case[largeur*hauteur]; // la taille de terrain = largeur * hauteur de liste

	for(y=0;y<hauteur;++y)
		for(x=0;x<largeur;++x)
            if (terrain_defaut[y][x]=='#')
                terrain[y*largeur+x] = MUR;
            else if (terrain_defaut[y][x] == '@')
                terrain[y*largeur+x] = FRUIT;
            else
                terrain[y*largeur+x] = VIDE;
    int longueurSerpent = 5;
    snake.clear();

    Position posTete;
    posTete.x = 15;
    posTete.y = 8;
	for (int i=0; i<longueurSerpent; i++)
    {
        snake.push_back(posTete);
        posTete.x--;
    }
        FMOD::System_Create(&fmodSystem);
        fmodSystem->init(32,FMOD_INIT_NORMAL,0);
        FMOD_RESULT resultat = fmodSystem->createSound("./Sound/shut_up_ghost-eating-a-crunchy-crisp-135544.mp3",FMOD_DEFAULT,0,&sonMiam);
        if (resultat != FMOD_OK) {
        // Petit message d'erreur si le fichier est introuvable
            std::cout << "Erreur : Impossible de trouver miam.wav" << std::endl;
        }
    return true;
}

bool Jeu::init_Infini()
{
    int x, y;
    dirSnake = DROITE;
	niveau = 0;
	Nb_Fruits_Manges = 0;
	TempsRestant = 9999999;
	collision_detecte =false;

	// list<Position>::iterator itSnake;

	const vector<string>terrain_defaut = liste_de_niveau[0];

	largeur = 20;
	hauteur = 15;

    delete[] terrain;
	terrain = new Case[largeur*hauteur]; // la taille de terrain = largeur * hauteur de liste

    for (int i = 0; i < largeur * hauteur; i++)
        terrain[i] = VIDE;


    int longueurSerpent = 5;
    snake.clear();

    Position posTete;
    posTete.x = 15;
    posTete.y = 8;
	for (int i=0; i<longueurSerpent; i++)
    {
        snake.push_back(posTete);
        posTete.x--;
    }

    Placer_fruite_aleatoire();
        FMOD::System_Create(&fmodSystem);
        fmodSystem->init(32,FMOD_INIT_NORMAL,0);
        FMOD_RESULT resultat = fmodSystem->createSound("./Sound/shut_up_ghost-eating-a-crunchy-crisp-135544.mp3",FMOD_DEFAULT,0,&sonMiam);
        if (resultat != FMOD_OK) {
        // Petit message d'erreur si le fichier est introuvable
            std::cout << "Erreur : Impossible de trouver miam.wav" << std::endl;
        }
    return true;
}

void Jeu::evolue()
{
     if (Terminer() && NiveauSuivant()&& !modeTeleportation)
        return;

    Position posTest;
	list<Position>::iterator itSnake; //  itSnake est une variable qui sert de curseur. Elle te permet de
	// voyager d'un segment a` l'autre du serpent pour lire sa position,....

    int depX[] = {-1, 1, 0, 0};
    int depY[] = {0, 0, -1, 1};

    posTest.x = snake.front().x + depX[dirSnake]; // la fonction front() permet de d'acceder au tout premier element de la list
    posTest.y = snake.front().y + depY[dirSnake]; // donc il nous donne dans ce cas les coordonne de la tete

    if(modeTeleportation)
    {
        posTest.x =(posTest.x + largeur)%largeur;
        posTest.y =(posTest.y + hauteur)%hauteur;

    }
    if (posValide(posTest))
    {
        if (getCase(posTest)== FRUIT)
        {
            fmodSystem->playSound(sonMiam,0,false,&channel);
            snake.push_front(posTest);
            setCase(posTest,VIDE);
            Nb_Fruits_Manges++;
            if(!modeTeleportation)
            {
                if (!NiveauSuivant())
                    Placer_fruite_aleatoire();
            }
            else
                Placer_fruite_aleatoire();
        }
        else
        {
                snake.pop_back();
                snake.push_front(posTest);
        }
    }
    else
    {
        collision_detecte = true;
    }
    fmodSystem->update();
}

int Jeu::getNbCasesX() const  // cela garantit que cette fonction est une simple consultation
{
    return largeur;  // retourne le nb de colonne
}

int Jeu::getNbCasesY() const
{
    return hauteur; // retourne le nb de lignes
}

Case Jeu::getCase(const Position &pos) const
{
    assert(pos.x>=0 && pos.x<largeur && pos.y>=0 && pos.y<hauteur);
    return terrain[pos.y*largeur+pos.x]; // on lit ligne par ligne par contre on peut lit quand meme colonne par colonne
    // cette fonction retournera soit un mur soit un vide.
}

const list<Position> &Jeu::getSnake() const
{
    return snake;
}

bool Jeu::posValide(const Position &pos) const
{
    if(!modeTeleportation)
    {
        if (pos.x < 0 || pos.x >largeur || pos.y < 0 || pos.y > hauteur)
        {
            return false;
        }
        if (terrain [pos.y *largeur + pos.x]== MORT)
        {
            return false;
        }
    }

    if (pos.x>=0 && pos.x<largeur && pos.y>=0 && pos.y<hauteur
&& (terrain[pos.y*largeur+pos.x]==VIDE ||terrain[pos.y*largeur+pos.x]==FRUIT) )
    {

        list<Position>::const_iterator itSnake; // il sert a` parcourir tout le corps du serpent, precisement, dans ce cas il parcout tout les pair de position de corp
        // const_iterator est une classe imbriquee dans la classe on va appeler list => itSnake est un objet de la classe imbriquee const_iterator
        itSnake = snake.begin(); // renvoie un iterator qui pointe sur ce tout premier wagon du trains
        //snake.end(): position apres le dernier element donc la boucle while continue tant qu'on a encore l'element.
        while (itSnake!=snake.end() && *itSnake!=pos) // *itSnake lit le  wagon pointe donc dans ce cas c'est la position
            itSnake++;// Deplace le doigt vers le wagon suivant  // cette boucle dit qu'il parcours tout le corps du serpent. S'il trouve un morceau du corps
            return (itSnake==snake.end());
            // qui est exactement a la position pos ou`  je veux aller, je m'arrete.
    //Le serpent se d�place en mettant sa t�te sur une nouvelle case.
    //La fonction posValide doit v�rifier que cette nouvelle case n'est pas D�J� occup�e par un morceau de son propre corps.
    }
    return false;
}

bool Jeu::Echoue() const
{
    return collision_detecte;
}

void Jeu::setDirection(Direction dir)
{
    dirSnake = dir;
}

void Jeu::setCase(const Position &pos, Case type)
{
    if (pos.x >= 0 && pos.x < largeur && pos.y >=0 && pos.y <hauteur)
    {
        terrain[pos.y * largeur + pos.x] = type;
    }
}

void Jeu::Placer_fruite_aleatoire()
{
    Position pos_placer;
    do
    {
    pos_placer.x = rand() % largeur;
    pos_placer.y = rand() % hauteur;
    } while (!posValide(pos_placer));

    setCase(pos_placer,FRUIT);
}

int Jeu::getNiveau() const
{
    return niveau;
}

int Jeu::getFruitsManges() const
{
    return Nb_Fruits_Manges;
}

 Jeu::getTempsRestant() const
{
    return TempsRestant;
}

bool Jeu::Terminer() const
{
    return TempsRestant <= 0 && Nb_Fruits_Manges <3;
}

bool Jeu::NiveauSuivant() const
{
    return Nb_Fruits_Manges == 3;
}

void Jeu::Temps_Ecoule()
{
    if(!NiveauSuivant() && !Terminer())
    {
        TempsRestant = TempsRestant - 2;
    }
}

bool Jeu::passerNiveauSuivant()
{
    if (niveau + 1 >= (int)liste_de_niveau.size())
        return false;
    niveau++;
    if (niveau == 2)
        dirSnake = BAS;
    else
        dirSnake = DROITE;
    Nb_Fruits_Manges = 0;
    TempsRestant = 60;
    collision_detecte = false;

    const vector<string>terrain_defaut = liste_de_niveau[niveau];

	largeur = 20;
	hauteur = 15;

    if (Jeu_Terminer())
        return 1;

    terrain = new Case[largeur*hauteur]; // la taille de terrain = largeur * hauteur de liste

	for(int y=0;y<hauteur;++y)
		for(int x=0;x<largeur;++x)
            if (terrain_defaut[y][x]=='#')
                terrain[y*largeur+x] = MUR;
            else if (terrain_defaut[y][x] == '@')
                terrain[y*largeur+x] = FRUIT;
            else if (terrain_defaut[y][x] == '!')
                terrain[y*largeur+x] = MORT;
            else
                terrain[y*largeur+x] = VIDE;

    int longueurSerpent = 5;
    snake.clear();

    Position posTete;
    posTete.x = 15;
    posTete.y = 8;
    if(niveau != 2)
    {
        for (int i=0; i<longueurSerpent; i++)
        {
            snake.push_back(posTete);
            posTete.x--;
        }
    }
    else
    {
        for (int i=0; i<longueurSerpent; i++)
        {
            snake.push_back(posTete);
            posTete.y--;
        }
    }
    return true;
}

bool Jeu::Jeu_Terminer() const
{
    return niveau > NB_Niveau_max;
}

bool Jeu::getModeTeleportation() const
{
  return modeTeleportation;
}

void Jeu::setModeTeleportation(bool b)
{
    modeTeleportation = b;
}

void Jeu::nettoyerTerrain()
{
    for (int i = 0; i < largeur *hauteur; i++)
    {
        terrain[i] = VIDE;
    }
    init();
}
