#include<Windows.h>
#include <iostream>
#include <GL/glut.h>
#include"Game.h"
#include<string>
using namespace std;

// Les deux vlrs seront utiliser par l'écran et la grille
#define Columns 40
#define Rows 40
// Définir un nombre d'images par seconde
#define FPS 10

// Une varible pour stocker le score
int score = 0;


// On récupère la variable de direction du serpent
extern short SerpentDirection;

// Une expression booléanne pour savoir si le game se termine ou pas
bool GameOver = false;

void timer_callback(int);
void display_callback();
void reshape_callback(int, int);
// le premier argument : la touche pressée
// le deuxième argument : la position de la souris au moment de la pression de la touche
void keyboard_callback(int ,int ,int);

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    initGrid(Columns,Rows);
}

int main(int argc, char** argv)
{
    // Initialisation de GLUT
    glutInit(&argc,argv);
    // Le mode d'affichage   . GLUT_DOUBLE pour une fenetre de double tampon c-à-d pendant que l'utilisateur voit une image,OpenGl dessine la suivante en coulisses 
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    // Initialiser la position de la fenetre 
    glutInitWindowPosition(250,250);
    // Initialiser la taille de la fenetre
    glutInitWindowSize(500,500);
    // Créer la fenetre
    glutCreateWindow("SNAKEGAME");
    // Enregistrer la fonction de rappel d'affichage et le rappel quand il est nécessaire
    glutDisplayFunc(display_callback);
    // Enregistrer la fonction de rappel de redimensionnement et le rappel quand il est nécessaire
    glutReshapeFunc(reshape_callback);
    // Configurer le FPS , le déplacement de la serpent 
    glutTimerFunc(0,timer_callback,0);
    // Keyboard input
    // Prend trois arguments : une fonction de rappel avec une liste de paramètre contenant un caractère générique
    // Lorsqu'une touche est pressée cette fonction de rappel est déclenchée et transmet la valeur de la touche s
    // Le deuxième argument représente la position du souris (les coordonnées au moment où la touche est pressée 
    // On va utiliser les touches haut droite gauche bas
    // glutKeyboardFunc();
    // Cette fonction contient une fonction de rappel qui contient des arguments constantes
    glutSpecialFunc(keyboard_callback);
    // Le premier argument (un entier) permet d'identifier la touche pressée
    // Initialiser la couleur
    init();
    // Lancement de la boucle
    glutMainLoop();



    return 0;
}
// Pour suivre la position
int index = 0;

// Dessine les éléments à l'écran , une fois le dessin terminé vous devez échanger le tampon de dessin avec le tampon d'affichage
void display_callback() {
    // Effacer le tampon de couleur
    glClear(GL_COLOR_BUFFER_BIT); 
    // Dessiner la grille avant l'échangement des tampons et après l'effacement de la tampon du couleur
    drawGrid();
    // Dessiner le serpent
    drawSnake();
    // Dessiner la nourritue
    drawFood();
    // échanger les tampons et l'image suivante s'affichera à l'écran
    glutSwapBuffers();

    if (GameOver) {
        wstring Message = L"Your Score : " + std::to_wstring(score);
        // Afficher un message 
        MessageBox(NULL,Message.c_str(), L"GAME OVER", 0);// la valeur 0 -> si tu cliques sur quelque chose le champ restera 0
        exit(0);
    }
}
// Configure la zone d'affichage , la zone d'affichage :une zone rectangulaire dans laquelle les objets que nous dessinons seront affichés et la projection 
void reshape_callback(int w, int h) {
    // La portée de la fenetre
    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    // La projection : pour la configurer elle faut changer le mode da la matrice (modèle_vue) en matrice de projection 
    glMatrixMode(GL_PROJECTION);
    // Pour aucune modification (sur la matrice) ne sera prise en compte dès le départ , les modifications seront définies par défaut au début
    glLoadIdentity();
    // La projection orthographique est idéale pour les jeux 2D
    // (-1.0) : la distance minimale à partir de laquelle les objets seront visibles 
    // (1.0) : la distance maximale
    // Une valeur négative de l'axe z correspond à un objet sortent de l'écran vers la gauche
    // Une valeur positive de l'axe z correspond à un objet entrant
    glOrtho(0.0,Columns, 0.0,Rows, -1.0,1.0);
    // Revenir à la matrice ModelView , car la suite des opérations se déroulera dans cette matrice
    //glMatrixMode(GL_MODELVIEW);
}

void timer_callback(int) {
    
    // Permet à OpenGL d'appeler la fonction d'affichage dès que possible
    glutPostRedisplay();
    // Enregistrer la fonction de configuration du FPS une autre fois
    // Pour créer une boucle continue d'affichage d'images toutes les 100 ms
    glutTimerFunc(1000/FPS,timer_callback,0);
}

// C'est pas nécessaire de connaître la position de la souris

void keyboard_callback(int key, int, int) {

    switch (key) {

    case GLUT_KEY_UP:
        if (SerpentDirection != DOWN) {
            SerpentDirection = UP;
        }
        break;
    case GLUT_KEY_DOWN:
        if(SerpentDirection!=UP){
            SerpentDirection = DOWN;
        }
        break;
    case GLUT_KEY_RIGHT:
        if (SerpentDirection != LEFT) {
            SerpentDirection = RIGHT;
        }
        break;
    case GLUT_KEY_LEFT:
        if (SerpentDirection != RIGHT) {
            SerpentDirection = LEFT;
        }
        break;
    }
}

// REMARQUES:

// Créer un carré de cote 1 unité pour chaque unité de cote
// Dessiner les éléments à l'écran :nous avons besoin d'une grille assez précise  , car il est plus facile de travailler avec des carrés
// Dessiner la nourriture dans une place aléatoire dans l'écran , quand le serpent atteint l'élément ciblé le score augmente et la position sera redessinée
// Quand le serpent tout la partie en rouge -> GAME OVER