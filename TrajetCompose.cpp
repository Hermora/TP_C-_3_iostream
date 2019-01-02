/*************************************************************************
                           TrajetCompose  -  Classe decrivant les trajets composes
                             -------------------
    début                : 20/11/2018
    copyright            : (C) 2018 par Andréa CROC and Sophie LABOUCHEIX
    e-mail               : andrea.croc@insa-lyon.fr and sophie.laboucheix@insa-lyon.fr
*************************************************************************/

//---------- Réalisation de la classe <TrajetCompose> (fichier TrajetCompose.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "TrajetCompose.h"

//------------------------------------------------------------- Constantes
#define TAILLE 100

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void TrajetCompose::Ecrire(ofstream& fichier)
// Algorithme :
// Ecrit le type du trajet, puis les villes de départ et d'arrivée à l'aide de la 
// méthode de Trajet, puis le nombre de trajets simples dans le trajet composé suivi
// d'un retour à la ligne. Et pour chaque trajet du trajet composé, appelle sa méthode
// d'écriture dans le fichier.
{
	fichier << "C,";
	Trajet::Ecrire(fichier);
	fichier << nbTrajetsTC << endl;
	for(int j=0; j<nbTrajetsTC; j++)
	{
		tabTrajetsSimpleEtCompose[j]->Ecrire(fichier);
	}
} //---- fin de Ecrire

void TrajetCompose::AfficherTrajet(int i) const
// Algorithme :
// On affiche les trajets contenus dans le tableau
{

	int j;
	Trajet::AfficherTrajet(i);
	for(j=0;j<nbTrajetsTC;j++)  //Parcours du tableau
	{
		tabTrajetsSimpleEtCompose[j]->AfficherTrajet(i+1);
	}
	
} // -- fin de AfficherTrajet



int TrajetCompose::GetNbTrajets() const
// Algorithme :
// Rien à préciser
{
	return nbTrajetsTC;
} // -- fin de GetNbTrajets



void TrajetCompose::AfficheTrajetPossibleSimple() const
// Algorithme :
// Uniquement pour la recherche simple
{

	int i;
	for(i = 0;i<nbTrajetsTC;i++) //Parcours du tableau
	{
		tabTrajetsSimpleEtCompose[i] -> AfficheTrajetPossibleSimple();
	}
} // -- fin de AfficheTrajetPossibleSimple


void TrajetCompose::AjoutTrajet (Trajet * trajet) 
// Algorithme :
// Si la taille du tableau est trop petite, on en creer un nouveau
// plus grand
{

	if(nbTrajetsTC==tailleTC) //Agrandissement de la taille du tableau si nécessaire
	{
		int i;
		tailleTC+=10;
		Trajet ** tabNouveau = new Trajet* [tailleTC];
       		Trajet ** temp = tabTrajetsSimpleEtCompose;
		for(i = 0;i<tailleTC-10;i++) 
		{
			tabNouveau[i] = tabTrajetsSimpleEtCompose[i];
		}
		tabTrajetsSimpleEtCompose = tabNouveau;
		delete[]temp;              

	}

	tabTrajetsSimpleEtCompose[nbTrajetsTC]=trajet; //Ajout au tableau
	nbTrajetsTC ++;


} // -- fin de AjoutTrajet


//-------------------------------------------- Constructeurs - destructeur

TrajetCompose::TrajetCompose (const char * villeDep, const char * villeArr)
	:Trajet(villeDep,villeArr)
// Algorithme :
// Rien à préciser
{

	tabTrajetsSimpleEtCompose = new Trajet* [TAILLE];
	tailleTC = TAILLE;
	nbTrajetsTC = 0;
	type = 'C';
	#ifdef MAP
	    cout << "Appel au constructeur de <TrajetCompose>" << endl;
	#endif
} //----- Fin du constructeur de TrajetCompose


TrajetCompose::~TrajetCompose ( )
// Algorithme :
// Rien à préciser
{

	int i;
	for(i=0;i<nbTrajetsTC;i++) 
	{
		delete tabTrajetsSimpleEtCompose[i];
	}
	delete [] tabTrajetsSimpleEtCompose;
	#ifdef MAP
	    cout << "Appel au destructeur de <TrajetCompose>" << endl;
	#endif
} //----- Fin du destructeur de TrajetCompose


