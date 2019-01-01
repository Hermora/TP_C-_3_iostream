/*************************************************************************
                           Catalogue  -  Classe decrivant le catalogue
                             -------------------
    début                : 20/11/2018
    copyright            : (C) 2018 par Andréa CROC and Sophie LABOUCHEIX
    e-mail               : andrea.croc@insa-lyon.fr and sophie.laboucheix@insa-lyon.fr
*************************************************************************/
#define _CRT_SECURE_NO_WARNINGS

//---------- Interface de la classe <Catalogue> (fichier Catalogue.h) ----------------
#if ! defined ( CATALOGUE_H )
#define CATALOGUE_H

//--------------------------------------------------- Interfaces utilisées
#include "Trajet.h"
#include "TrajetSimple.h"
#include "TrajetCompose.h"

#include <string>

// Rôle de la classe <Catalogue>
//
// Elle permet de faire plusieurs opérations sur un catalogue de trajets.
// Un catalogue est caractérisé par ses trajets (contenus dans un tableau),
// le nombre de trajets qu'il contient, et la taille actuelle du tableau
//
// Il est possible d'afficher ses trajets, d'ajouter un trajet,
// de faire un recherche simple et une recherche complète sur les trajets que le tableau contient,
// et sait afficher les trajets trouvés lors des recherches
//
//------------------------------------------------------------------------

class Catalogue
{
//----------------------------------------------------------------- PUBLIC

	public:
	//----------------------------------------------------- Méthodes publiques

	    void AfficherTrajetsCatalogue() const;
	    //Mode d'emploi : Affiche les trajets contenus dans le catalogue
	    // Paramètres : aucun
	    // Contrat : aucun

	    void AjouterTrajet(Trajet * trajet);
	    //Mode d'emploi : Ajoute un trajet dans le catalogue
	    // Paramètres : trajet est le trajet ajouté au catalogue
	    // Contrat : aucun

 	    void RechercheSimple (const char * villeDepart, const char * villeArrivee) const;
	    //Mode d'emploi : Fait une recherche simple sur le catalogue
	    // Paramètres : 
	    //   - villeDepart est la ville de départ de la recherche simple
            //   - villeArrivee est la ville d'arrivée de la recherche simple
	    // Contrat : aucun

	    int RechercheComplete (const char * villeDepart, const char * villeArrivee, Trajet ** enchainementsPossible, int caseSuivante, int * contientTrajet) const;
	    //Mode d'emploi : Fait une recherche complète sur le catalogue
	    // Paramètres : 
	    //   - villeDepart est la ville de départ de la recherche complète
        //   - villeArrivee est la ville d'arrivée de la recherche complète
	    //   - enchainementsPossible contient les trajets possibles qui vérifient la recherche complète
        //   - caseSuivante l'indice de la case suivante à complétée dans le tableau enchainementsPossible
	    //   - contientTrajet compte le nombre de possibilités de trajets
	    // Contrat : aucun

		void ecritureDansFichier(int choix, string cheminFic);

	    int LectureToutTrajetFichier(string cheminFichier);
	    //Mode d'emploi : Recupère les trajets qui sont dans le fichier   
        //dont le chemin d'accès est donné en paramètre
	    // Paramètre :
	    // - cheminFichier est le chemin d'accès du fichier à lire
        // Contrat : aucun

		int LectureChoixTypeTrajetFichier(string cheminFichier, string type);
		//Mode d'emploi : Recupère le chemin d'accès du fichier et le type de trajet 
		//que l'utilisateur veut mettre dans le catalogue pour gérer les erreurs de saisies
		// Paramètres :
		// - cheminFichier est le chemin d'accès du fichier à lire
		// - type est le type de trajet que l'utilisateur veut récupérer soit simple soit composé
		// Contrat : aucun

        int LectureTypeTrajetFichier(string cheminFichier, string type);
	    //Mode d'emploi : Recupère seulement les trajets simples ou composés qui sont dans le fichier   
        //dont le chemin d'accès est donné en paramètre
	    // Paramètres :
	    // - cheminFichier est le chemin d'accès du fichier à lire
		// - type est le type de trajet que l'utilisateur veut récupérer soit simple soit composé
        // Contrat : aucun

		int LectureChoixVilleTrajetFichier(string cheminFichier, string option);
		//Mode d'emploi : Recupère le chemin d'accès du fichier à lire et l'option choisie par l'utilisateur  
		//pour savoir si il veut récupérer les trajets suivant la ville de départ et/ou d'arrivée  
		//et pouvoir gérer les erreurs de saisies
		// Paramètres :
		// - cheminFichier est le chemin d'accès du fichier à lire
		// - option est le nom de l'option choisi par l'utilisateur
		// Contrat : aucun

		int LectureVilleTrajetFichier(string cheminFichier, string option, string villed, string villea);
		//Mode d'emploi : Recupère seulement les trajets qui sont dans le fichier 
		//dont le chemin d'accès est donné en paramètre et qui ont la meme ville 
		//de départ et/ou d'arrivée que celle mentionnée par l'utilisateur   
		// Paramètres :
		// - cheminFichier est le chemin d'accès du fichier à lire
		// - option est le nom de l'option choisi par l'utilisateur
		// - villed est le nom de la ville de départ choisie par l'utilisateur pour séléctionner les trajets
		// - villea est le nom de la ville d'arrivée choisie par l'utilisateur pour séléctionner les trajets
		// Contrat : aucun

		int LectureIntervalleTrajetFichier(string cheminFichier, int borneInf, int borneSup);
		//Mode d'emploi : Recupère seulement les trajets qui sont dans le fichier 
		//dont le chemin d'accès est donné en paramètre et qui sont dans l'intervalle
		//mentionné par l'utilisateur   
		// Paramètres :
		// - cheminFichier est le chemin d'accès du fichier à lire
		// - borneInf est la valeur de la borne inférieure de l'intervalle correspondant au premier trajet
		// - borneSup est la valeur de la borne supérieure de l'intervalle correspondant au dernier trajet
		// Contrat : aucun



	//-------------------------------------------- Constructeurs - destructeur

	    Catalogue ();
	    // Mode d'emploi : Construit un catalogue
	    // Paramètres : aucun
	    // Contrat : aucun

	    virtual ~Catalogue ( );
	    // Mode d'emploi : Détruit un catalogue
	    // Paramètres : aucun
	    // Contrat : aucun
	

	//------------------------------------------------------------------ PROTEGE

	protected:

	 void afficheCheminRechercheComplete(Trajet ** enchainementsPossible, int caseSuivante) const;
	    //Mode d'emploi : Permet d'afficher les trajets trouvés lors de la recherche complète
	    // Paramètres : 
	    //   - enchainementsPossible contient les trajets possibles qui vérifient la recherche complète
	    //   - caseSuivante l'indice de la case suivante à complétée dans le tableau enchainementsPossible
	    // Contrat : aucun

	//----------------------------------------------------- Attributs protégés
	Trajet ** tabTrajetCatalogue; //Le tableau contenant des pointeurs sur des trajets simples et des trajets composés
	int tailleC; //La taille actuelle du tableau tabTrajetCatalogue
	int nbTrajetsC; // Le nombre actuel de trajets contenus dans le tableau tabTrajetCatalogue

};

//-------------------------------- Autres définitions dépendantes de <Catalogue>

#endif // CATALOGUE_H

