/*************************************************************************
                           Trajet  -  Classe decrivant les trajets
                             -------------------
    début                : 20/11/2018
    copyright            : (C) 2018 par Andréa CROC and Sophie LABOUCHEIX
    e-mail               : andrea.croc@insa-lyon.fr and sophie.laboucheix@insa-lyon.fr
*************************************************************************/

//---------- Interface de la classe <Trajet> (fichier Trajet.h) ----------------
#if ! defined ( TRAJET_H )
#define TRAJET_H

//-----------------------------------------------------------------------------
// Rôle de la classe <Trajet>
//
// Classe générale qui permet de faire plusieurs opérations sur des trajets.
// Un trajet est caractérisé par une ville de départ et une ville d'arrivée.
// Il est possible d'afficher un trajet, connaître sa ville de départ et d'arrivée,
// modifier sa ville de départ et d'arrivée
//
//-----------------------------------------------------------------------------

class Trajet
{
	//----------------------------------------------------------------- PUBLIC

	public:
		//----------------------------------------------------- Attribut public

		char type; //attribut permettant de connaître le type de trajets (simple ou composé) 

		//----------------------------------------------------- Méthodes publiques
		

		virtual void ecrire(ofstream& fichier);
		// Mode d'emploi : écrit les villes de départ et d'arrivée du trajet
		// dans le fichier passé en paramètre
		// Paramètre :
		// - fichier est le fichier ouvert dans catalogue.cpp dans lequel on écrit
		// Contrat : aucun
	
		virtual void AjoutTrajet (Trajet * trajet);
		// Mode d'emploi : Ajoute un trajet
		// Paramètre :
		//     - trajet est le trajet à ajouter
		// Contrat : aucun

		char * GetVilleDepart() const;
		// Mode d'emploi : Retourne la valeur de la ville de départ du trajet
		// Paramètres : aucun
		// Contrat : aucun

		char * GetVilleArrivee() const;
		// Mode d'emploi : Retourne la valeur de la ville d'arrivée du trajet
		// Paramètres : aucun
		// Contrat : aucun
	
		void SetVilleArrivee(const char * villeArr);
		// Mode d'emploi : Modifie la valeur de la ville d'arrivée du trajet
		// Paramètres : 
		//    - villeArr est la nouvelle ville qui sera affectée à l'attribut villeArrivee
		// Contrat : aucun
	
        	void SetVilleDepart(const char * villeDep);
		// Mode d'emploi : Modifie la valeur de la ville de départ du trajet
		// Paramètres : 
		//    - villeDep est la nouvelle ville qui sera affectée à l'attribut villeDepart
		// Contrat : aucun
	
		virtual void AfficherTrajet(int i) const;
 		// Mode d'emploi : Afficher tous les trajets 
		// Paramètres : 
		//    - i est un indice qui permet d'indenter les affichages des trajets
		// Contrat : aucun
	
		virtual void AfficheTrajetPossibleSimple() const;
		// Mode d'emploi : Affiche les trajets qui satisfont la recherche simple
		// Paramètres : aucun
		// Contrat : aucun
	
	
		//-------------------------------------------- Constructeurs - destructeurs publics
	
		virtual ~Trajet ( );
		// Mode d'emploi : Détruit le trajet
		// Paramètres : aucun
		// Contrat : aucun
			
	
	
	//----------------------------------------------------------------- PROTEGE

	protected:


		//-------------------------------------------- Constructeurs - destructeur protégé

		Trajet (const char * villeDep, const char * villeArr);
		// Mode d'emploi : Construit un trajet
		// Paramètres : 
		//    - villeArr est la ville d'arrivée qui sera affectée à l'attribut villeArrivée
		//    - villeDep est la ville de départ qui sera affectée à l'attribut villeDépart
		// Contrat : aucun
	
		    
	
		//----------------------------------------------------- Attributs protégés
	
		char * villeDepart; //La ville de départ d'un trajet
		char * villeArrivee; //La ville d'arrivée d'un trajet

};


#endif // TRAJET_H

