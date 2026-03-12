#include"Game.h"
#include<GL/glut.h>
#include<ctime>

extern int score;

// Une variable qui contient les blocs où le corps du serpent existe au début du jeu

int SnakeLength = 5;// 5 blocs

// Une variable de type booléanne pour vérifier si nous pouvons changer la place de la nourriture ou non
bool place_of_food = true;

// Deux variables pour stocker la postion du nourriture
int posX_Food;
int posY_Food;


// Deux variables de la grille
int gridX, gridY;

// Pour définir la position du serpent
// La position de la serpent est convertit en une surface
// On utilise des entiers pour stocker la position da chaque partie du corps du serpent
//int posX = 20;// le serpent sera dans le centre de l'écran car la grille 40*40
//int posY = 20;



// On va utiliser un tableau des entiers qui contient la postion du corps du serpent 

int posX[MAXBODYSERPENT] = { 20,20,20,20,20 }, posY[MAXBODYSERPENT] = { 20,19,18,17,16 };

// Une variable pour stocker la direction actuelle du déplacement du serpent
short SerpentDirection=RIGHT;// on va l'utiliser dans la fct main pour récupérer l'entrée clavier

extern bool GameOver;

// Initialiser la grille
void initGrid(int x, int y) {
	gridX = x;// Les colonnes
	gridY = y;// Les lignes
}

// Dessiner la grille
void drawGrid() {
	// Dessiner plusieurs carrés à différents endroits de l'écran
	for (int x = 0; x < gridX; x++) {
		for(int y=0;y<gridY;y++){
			unit(x,y);
		}
	}

}

// Dessiner une seule unité carrée

void unit(int x, int y) {

	if (x == 0 || y == 0 || x == gridX - 1 || y == gridY - 1) {
		//l'épaisser de la ligne
		float width = 2.0;
		glLineWidth(width);
		// la couleur de la ligne 
		glColor3f(1.0, 0.0, 0.0); 
	}
	else {
		//l'épaisser de la ligne
		float width = 2.0;
		glLineWidth(width);
		// la couleur de la ligne
		glColor3f(1.0, 1.0, 1.0);
	}


	// Commencer de dessiner
	glBegin(GL_LINE_LOOP);
	// Spécifier les sommets
	glVertex2f(x,y);
	glVertex2f(x + 1, y);
	glVertex2f(x+1, y + 1);
	glVertex2f(x,y+1);

	glEnd();
}

// Dessiner la nourriture dans une position aléatoire 

void drawFood() {
	if (place_of_food) {
		random(posX_Food, posY_Food);
	}
	place_of_food = false;
	glPointSize((GLfloat)10.00);
	glBegin(GL_POINTS);
	glVertex2d(posX_Food + 0.5, posY_Food + 0.5);
	//glVertex2d(posX_Food + 1, posY_Food);
	//glVertex2d(posX_Food + 0.5, posY_Food + 1);
	glEnd();
}



// On déplace le dessin du corps du serpent  car nous avons le besoin plusieurs fois
void drawSnake() {
	/*
	   On va utiliser la variable
	   de SerpentDirection pour
	   modifier la position du
	   bloc dessiné	à l'écran afin
	   de le déplacer en fonction
	   de l'entrée clavier

	*/
	for (int i = SnakeLength - 1; i > 0;i--)
	{
		posX[i] = posX[i - 1];
		posY[i] = posY[i - 1];
	}
	

	if (SerpentDirection == UP) {
		posY[0]++;
	}
	else if (SerpentDirection == DOWN) {
		posY[0]--;
	}
	else if (SerpentDirection == RIGHT) {
		posX[0]++;
	}
	else if (SerpentDirection == LEFT) {
		posX[0]--;
	}

	// On va utiliser une boucle pour dessiner tous les éléments
	for (int i = 0; i < SnakeLength; i++) {
		
		// Si on a dans le tete du serpent on va changer la couleur
		if (i == 0) {
			glColor3ub(0, 200, 0);
		}
		else {
			glColor3ub(100, 100, 100);
		}
		// Pour dessiner un bloc du rectangle
		glRectd(posX[i], posY[i], posX[i] + 1, posY[i] + 1);
		
	}



	// Vérifier si la tete du serpent est dans la partie rouge de l'écran , 
	// c'est pas l'appel de verifier tout le corps du serpent car si la tete 
	// du serpent ne passe pas dans un chemin tout ce qui précèdent la tete 
	// ne seront pas passés
	if (posX [0] == 0 || posX[0] == gridX - 1 || posY[0] == 0 || posY[0] == gridY - 1) {
		GameOver = true;
	}
	// La couleur du nourriture
	glColor3ub(200,0,0);
	// Vérifier si la tete du serpent atteint la nourriture
	if (posX[0] == posX_Food && posY[0] == posY_Food) // -> les coordonnées du serpent et les coordonnées du nourriture sont identiques
	{
		// Le score du serpent augmente quand il atteind l'objet ciblé 
		score++;


		// La longueur du serpent augmente quand il atteind l'objet ciblé
		SnakeLength++;
		if (SnakeLength > MAXBODYSERPENT) {
			SnakeLength = MAXBODYSERPENT;
		}
		place_of_food = true;
	}


}



// Une fonction qui prend deux référence
void random(int& x, int& y) {
	int minV_X = 1,maxV_X = gridX - 2;
	int minV_Y = minV_X,maxV_Y = gridY - 2;
	// Initialiser rand() avec un entier différent pour éviter que les vlrs soient identiques -> on va utiliser l'heure de laptop 
	srand(time(NULL));
	// Pour obtenir un nombre aléatoire , qui est assez grand - > pour éviter ce problème on va convertir les vlrs obtenues par rand() entre 1 et 38

	x = minV_X + rand() % (maxV_X - minV_X);
	y = minV_X + rand() % (maxV_Y - minV_X);
}


// Le corps du serpent quand atteint la nourriture chaque fois
