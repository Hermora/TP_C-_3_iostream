/*************************************************************************
                           TrajetSimple  -  Classe decrivant les trajets simples
                             -------------------
    début                : 20/11/2018
    copyright            : (C) 2018 par Andréa CROC and Sophie LABOUCHEIX
    e-mail               : andrea.croc@insa-lyon.fr and sophie.laboucheix@insa-lyon.fr
*************************************************************************/


//---------- Réalisation de la classe <TrajetSimple> (fichier TrajetSimple.cpp) ------------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <cstring>
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "TrajetSimple.h"


void TrajetSimple::AfficheTrajetPossibleSimple() const
// Algorithme :
// Rien à préciser
{
	Trajet::AfficheTrajetPossibleSimple();
	cout << " en " << moyenTransport << " -- "; 

}  //----- Fin de AfficherTrajetPossibleSimple


void TrajetSimple::AfficherTrajet(int i) const
// Algorithme :
// Rien à préciser
{
	int j;
	Trajet::AfficherTrajet(i);
	for(j=0;j<i;j++) 
	{
		cout << "    " ;
	}
	cout << "Moyen de transport : " << moyenTransport << endl;
	cout << "" << endl;
}  //----- Fin de AfficherTrajet


//-------------------------------------------- Constructeurs - destructeur


TrajetSimple::TrajetSimple (const char * villeDep,const char * villeArr,const char * moyenTrans)
	:Trajet(villeDep,villeArr)
// Algorithme :
// Rien à préciser
{
	moyenTransport= new char[strlen(moyenTrans)+1];
	strcpy(moyenTransport,moyenTrans);

	#ifdef MAP
	    cout << "Appel au constructeur de <TrajetSimple>" << endl;
	#endif
} //----- Fin du constrcuteur de TrajetSimple


TrajetSimple::~TrajetSimple ( )
// Algorithme :
// Rien à préciser
{
	delete[]moyenTransport;
	#ifdef MAP
	    cout << "Appel au destructeur de <TrajetSimple>" << endl;
	#endif
} //----- Fin du destructeur de TrajetSimple


