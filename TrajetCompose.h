/*************************************************************************
                           TrajetCompose  -  Classe decrivant les trajets composes
                             -------------------
    début                : 20/11/2018
    copyright            : (C) 2018 par Andréa CROC and Sophie LABOUCHEIX
    e-mail               : andrea.croc@insa-lyon.fr and sophie.laboucheix@insa-lyon.fr
*************************************************************************/


//---------- Interface de la classe <TrajetCompose> (fichier TrajetCompose.h) ----------------
#if ! defined ( TRAJETCOMPOSE_H )
#define TRAJETCOMPOSE_H

//--------------------------------------------------- Interfaces utilisées
#include "Trajet.h"

// Rôle de la classe <TrajetCompose>
//
// Classe qui hérite de la classe Trajet 
// Elle permet de faire plusieurs opérations sur des trajets composés.
// Un trajet composé est caractérisé par ses trajets (contenus dans un tableau),
// le nombre de trajets qu'il contient, et la taille actuelle du tableau
// Il est possible d'afficher un trajet composé, d'ajouter un trajet composé,
// de récuperer le nombre de trajets contenus dans le tableau, d'afficher tous les trajets
// trouvés par la recherche simple
//
//------------------------------------------------------------------------

class TrajetCompose : public Trajet
{
	//----------------------------------------------------------------- PUBLIC

	public:
	//----------------------------------------------------- Méthodes publiques
	   
	void ecrire(ofstream& fichier);

	   void AjoutTrajet (Trajet * trajet);
	   //Mode d'emploi : Ajoute un trajet composé
	   // Paramètres :
	   //     - trajet est le trajet composé à ajouter
	   // Contract : aucun

	    int GetNbTrajets() const;
	   //Mode d'emploi : Renvoie le nombre actuel de trajets dans le tableau 
	   // Paramètres :aucun
	   // Contract : aucun

	    void AfficherTrajet(int i) const;
	   //Mode d'emploi : Affiche un trajet composé
	   // Paramètres :
	   //     - i est un indice qui permet d'indenter les affichages des trajets
	   // Contract : aucun

	    void AfficheTrajetPossibleSimple() const;
	   // Mode d'emploi : Affiche les trajets composés qui satisfont la recherche simple
	   // Paramètres : aucun
	   // Contrat : aucun


	//-------------------------------------------- Constructeurs - destructeur

	    TrajetCompose (const char * villeDep,const char * villeArr);
	    // Mode d'emploi : Construit un trajet composé
	    // Paramètres : 
	    //    - villeArr est la ville d'arrivée qui sera affectée à l'attribut villeArrivée
	    //    - villeDep est la ville de départ qui sera affectée à l'attribut villeDépart
	    // Contrat : aucun

	    virtual ~TrajetCompose ( );
	    // Mode d'emploi : Détruit le trajet composé
	    // Paramètres : aucun
	    // Contrat : aucun

	//------------------------------------------------------------------ PROTEGE

	protected:

	//----------------------------------------------------- Attributs protégés

	Trajet ** tabTrajetsSimpleEtCompose; //Le tableau contenant des pointeurs sur des trajets simples et des trajets composés
	int tailleTC; //La taille actuelle du tableau tabTrajetsSimpleEtCompose
	int nbTrajetsTC; // Le nombre actuel de trajets contenus dans le tableau tabTrajetsSimpleEtCompose

};


#endif // TRAJETCOMPOSE_H

