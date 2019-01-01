/*************************************************************************
                           Trajet  -  Classe decrivant les trajets
                             -------------------
    début                : 20/11/2018
    copyright            : (C) 2018 par Andréa CROC and Sophie LABOUCHEIX
    e-mail               : andrea.croc@insa-lyon.fr and sophie.laboucheix@insa-lyon.fr
*************************************************************************/

//---------- Réalisation du module <Trajet> (fichier Trajet.cpp) ---------------

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
#include <cstring>
#include <iostream>
#include <fstream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Trajet.h"


//////////////////////////////////////////////////////////////////  PUBLIC
//---------------------------------------------------- Fonctions publiques

void Trajet::ecrire(ofstream& fichier)
{
	fichier << villeDepart << "," << villeArrivee << ",";
}

void Trajet::AfficheTrajetPossibleSimple() const
// Algorithme :
// Rien à préciser
{
	cout << "De " << villeDepart << " à " << villeArrivee; 
} //----- fin de AfficheTrajetPossibleSimple


char * Trajet::GetVilleDepart() const
{
// Algorithme :
// Rien à préciser
	return villeDepart;
} //----- fin de GetVilleDepart


char * Trajet::GetVilleArrivee() const
{
// Algorithme :
// Rien à préciser
	return villeArrivee;
} //----- fin de GetVilleArrivee


void Trajet::SetVilleArrivee(const char * villeArr)
// Algorithme :
// Rien à préciser
{
	strcpy(villeArrivee,villeArr);
} //----- fin de SetVilleArrivee


void Trajet::SetVilleDepart(const char * villeDep)
// Algorithme :
// Rien à préciser
{
	strcpy(villeDepart,villeDep);
} //----- fin de SetVilleDepart


void Trajet::AfficherTrajet(int i) const
// Algorithme :
// Rien à préciser
{
	int j;	
	for(j=0;j<i;j++) 
	{
		cout << "    " ;
	}
	cout << "Ville de départ : " << villeDepart << endl;
	for(j=0;j<i;j++) 
	{
		cout << "    " ;
	}	
	cout << "Ville d'arrivée : " << villeArrivee << endl;

} //----- fin de AfficherTrajet


void Trajet::AjoutTrajet (Trajet * trajet)
//Algorithme :
// Définition obligatoire pour son usage dans les classes filles
{
	//C'est dans les descendants
} //-- fin de AjoutTrajet


Trajet::Trajet(const char * villeDep,const char * villeArr)
// Algorithme :
// Rien à préciser
{
	villeDepart = new char [strlen(villeDep)+1];
	villeArrivee = new char [strlen(villeArr)+1];

	strcpy(villeDepart,villeDep);
	strcpy(villeArrivee,villeArr);

	#ifdef MAP
		cout << "Appel au constructeur de <Trajet>" << endl;
	#endif	


} // -- fin du constructeur de Trajet


Trajet::~Trajet ()
// Algorithme :
// Rien à préciser
{
	delete [] villeDepart;
	delete [] villeArrivee;

	#ifdef MAP
		cout << "Appel au destructeur de <Trajet> \r\n" << endl;
	#endif

} // -- fin du destructeur de Trajet

