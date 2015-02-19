#include "stdafx.h"
#include "IA.h"




IA::~IA()
{
}

Action IA::operator() (Unit* unit, Army armyOne, Army armyTwo){
	// teste si l'unit courante peut tirer
	// si oui, choisir sa cible en fonction du code ia
		// si la cible est à portée => tirer desssus
		// si non, se rapprocher d'elle ( en fonction de sa speed ?)
	// si non aller dans la direction opposée au centre des ennemis ou de l'ennemi le + proche (à voir)	
}