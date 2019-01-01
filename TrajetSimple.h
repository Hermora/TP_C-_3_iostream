/*************************************************************************
                           TrajetSimple  -  Classe decrivant les trajets simples
                             -------------------
    début                : 20/11/2018
    copyright            : (C) 2018 par Andréa CROC and Sophie LABOUCHEIX
    e-mail               : andrea.croc@insa-lyon.fr and sophie.laboucheix@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <TrajetSimple> (fichier TrajetSimple.h) ----------------
#if ! defined ( TRAJETSIMPLE_H )
#define TRAJETSIMPLE_H


//-----------------------------------------------------------------------------
// Rôle de la classe <TrajetSimple>
//
// Classe qui hérite de la classe Trajet 
// Elle permet de faire plusieurs opérations sur des trajets simples.
// Un trajet simple est caractérisé par son moyen de transport
// Il est possible d'afficher un trajet simple, et d'afficher tous les trajets
// simples trouvés par la recherche simple
//
//-----------------------------------------------------------------------------



//--------------------------------------------------- Interfaces utilisées
#include "Trajet.h"


// Rôle de la classe <TrajetSimple>
//
//
//------------------------------------------------------------------------

class TrajetSimple : public Trajet
{
	//----------------------------------------------------------------- PUBLIC

	public:
	//----------------------------------------------------- Méthodes publiques
	
	     void ecrire(ofstream& fichier);	
	
	     void AfficherTrajet(int i) const;
	     //Mode d'emploi : Affiche un trajet simple
	     // Paramètres :
	     //     - i est un indice qui permet d'indenter les affichages des trajets simples
	     // Contract : aucun

	     void AfficheTrajetPossibleSimple() const;
	     //Mode d'emploi : Affiche les trajets simples qui ont été trouvés par la recherche simple
	     //Paramètres : aucun
	     // Contract : aucun


	//-------------------------------------------- Constructeurs - destructeurs


	    TrajetSimple (const char * villeDep,const char * villeArr,const char * moyenTrans);
	    // Mode d'emploi : Construit un trajet simple
	    // Paramètres : 
	    //    - villeArr est la ville d'arrivée qui sera affectée à l'attribut villeArrivée
	    //    - villeDep est la ville de départ qui sera affectée à l'attribut villeDépart
	    // Contrat : aucun

	    virtual ~TrajetSimple ( );
	    // Mode d'emploi : Détruit le trajet simple
	    // Paramètres : aucun
	    // Contrat : aucun

	//------------------------------------------------------------------ PROTEGE

	protected:

	    //----------------------------------------------------- Attributs protégés

	    char * moyenTransport; //moyen de transport d'un trajet simple

};


#endif // TRAJETSIMPLE_H

