/*************************************************************************
                           TestTrajet  -  Classe qui test nos programmes
                             -------------------
    début                : 20/11/2018
    copyright            : (C) 2018 par Andréa CROC and Sophie LABOUCHEIX
    e-mail               : andrea.croc@insa-lyon.fr and sophie.laboucheix@insa-lyon.fr
*************************************************************************/


//---------- Réalisation du module <TestTrajet> (fichier TestTrajet.cpp) ---------------

/////////////////////////////////////////////////////////////////  INCLUDE
//-------------------------------------------------------- Include système
using namespace std;
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>

//------------------------------------------------------ Include personnel
#include "Trajet.h"
#include "TrajetSimple.h"
#include "TrajetCompose.h"
#include "Catalogue.h"

///////////////////////////////////////////////////////////////////  PRIVE
//------------------------------------------------------------- Constantes
#define TAILLE_CHAR_MAX 100
#define TAILLE_TRAJET_MAX 100


static Trajet * ajoutTrajetSimple (int nbTab, char * villeDepart) 
// Algorithme : 
// On retourne le nouveau trajet crée
// Le strcpy final permet de forcer l'utilisateur a avoir une ville de départ
// qui correpond à la ville d'arrivée précédente
{
	
	char villeArr [TAILLE_CHAR_MAX];
	char moyTrans [TAILLE_CHAR_MAX];
	int i;

	//Cette boucle permet de faire l'indentation
	for(i = 0;i<nbTab;i++) 
	{
		cout << "       ";
	}
	//Rappel de la ville de départ donnée
	cout << "Ville de départ précédemment saisie : " << villeDepart << endl;
	for(i = 0;i<nbTab;i++) 
	{
		cout << "       ";
	}
	cout << "Saisissez votre ville d'arrivée : ";
	cin >> villeArr;

	for(i = 0;i<nbTab;i++) 
	{
		cout << "       ";
	}
	cout << "Saisissez votre moyen de transport : ";
	cin >> moyTrans;

	//Création du trajet simple
	Trajet * trajetSimple = new TrajetSimple(villeDepart,villeArr,moyTrans);

	//Actualisation de la future ville de départ (utile pour l'appel avec le trajet composé)
	strcpy(villeDepart,villeArr);

	return trajetSimple;

	
} // -- fin de ajoutTrajetSimple


static Trajet * ajoutTrajetCompose(int nbTab, char * villeDepart) 
// Algorithme :
// Appels récursifs pour ajouter des trajets au tableau
// A la toute fin, on réactualise la ville d'arrivée graĉe aux actualisations faites dans l'appel de ajoutTrajetSimple
{

	int typeTrajet;
	int i;
	char * villeArr = new char [TAILLE_CHAR_MAX];

	//Au départ, la ville d'arrivée est inconnue. Elle
	// sera actualisée à la toute fin de la saisie de l'utilisateur
	strcpy(villeArr,"villeArriveeInconnuePourLeMoment"); 
	int continueQuestions = 1; //Si on continue l'insertion de trajets

	//Création du nouveau trajet composé
	Trajet * nouveauTrajetCompose = new TrajetCompose(villeDepart,villeArr);

	//Pour l'indentation
	for(i = 0;i<nbTab;i++) 
	{
		cout << "       ";
	}
	cout << "Ville de départ précédemment saisie : " << villeDepart << endl; //Rappel de la ville de départ donnée
	
	for(i = 0;i<nbTab;i++) 
	{
		cout << "       ";
	}
	cout << " - Tapez 1 pour insérer un trajet simple " << endl;
	
	/*

	On le retire pour la démonstration -- permet d'insérer un trajet composé dans un trajet composé

	for(i = 0;i<nbTab;i++) 
	{
		cout << "       ";
	}
	cout << " - Tapez 2 pour insérer un trajet composé " << endl;

	*/
	
	for(i = 0;i<nbTab;i++) 
	{
		cout << "       ";
	}
	cout << " - Tapez 0 pour arrêter : " ;
	cin >> typeTrajet;

	while(cin.fail())
	{
		cout<<"Erreur, entrez un nombre : ";
		cin.clear();
		cin.ignore(256,'\n');
		cin>>typeTrajet;
	}

	while (continueQuestions != 0) 
	{
		if(typeTrajet == 1) //Ajout d'un trajet simple (ajoutTrajet) graĉe au retour de la fonction ajoutTrajetSimple
		{
			nouveauTrajetCompose->AjoutTrajet(ajoutTrajetSimple(nbTab+1,villeDepart));
		}
		else if (typeTrajet == 2) //Ajout d'un trajet composé (ajoutTrajet) grâce au retour de la fonction ajoutTrajetCompose
		{
			nouveauTrajetCompose->AjoutTrajet(ajoutTrajetCompose(nbTab+1,villeDepart));
		}
		else if (typeTrajet == 0) //Fin des ajouts
		{
			nouveauTrajetCompose->SetVilleArrivee(villeDepart); //Grâce à l'actualisation faite dans la méthode ajoutTrajetSimple
			continueQuestions = 0;	//On arrête la saisie		
			break;
		}
		
		
		// On repose les questions
		for(i = 0;i<nbTab+1;i++) 
		{
			cout << "       ";
		}
		cout << " - Tapez 1 pour insérer un trajet simple " << endl;
		for(i = 0;i<nbTab+1;i++) 
		{
			cout << "       ";
		}
		
		/*

		On le retire pour la démonstration

		cout << " - Tapez 2 pour insérer un trajet composé " << endl;
		for(i = 0;i<nbTab+1;i++) 
		{
			cout << "       ";
		}
		*/

		cout << " - Tapez 0 pour arrêter : " ;

		cin >> typeTrajet;

	}

	//Mise à jour de la ville d'arrivée
	nouveauTrajetCompose->SetVilleArrivee(villeDepart);

	delete [] villeArr;

	return nouveauTrajetCompose;

} // -- fin de ajoutTrajetCompose

static void affichageMenuPrincipal()
// Algorithme :
// Menu principal
{
	cout << " *********************************   MENU PRINCIPAL   ***************************** " << endl;
	cout << "- 1 pour afficher les trajets du catalogue " << endl;
	cout << "- 2 pour ajouter un trajet simple au catalogue " << endl;
	cout << "- 3 pour ajouter un trajet composé au catalogue " << endl;
	cout << "- 4 pour faire une recherche simple sur le catalogue " << endl;
	cout << "- 5 pour faire une recherche composée sur le catalogue " << endl;
	cout << "- 6 pour faire une sauvegarde des trajets du catalogue dans un fichier " << endl; 
	cout << "- 7 pour récupérer les trajets présents dans un fichier " << endl; 
	cout << "- 0 pour quitter l'application " << endl; 
	cout << " ********************************************************************************** " << endl;
	cout << "Que souhaitez-vous faire ? : ";
}


int main ()
// Algorithme :
// Menu principal où l'utilisateur fait ses choix de commandes
{

	Catalogue * catalogue = new Catalogue();
	int choix;


	//Menu proposé à l'utilisateur
	affichageMenuPrincipal();

	cin >> choix;
	cout << "" << endl;

	while(choix != 0) {

		if(choix == 1) // Affichage du catalogue
		{		
			cout << "Voici la liste des voyages actuels : " << endl;
			catalogue->AfficherTrajetsCatalogue();
		}
		else if (choix == 2) //Insertion d'un trajet simple
		{
			char * villeDepart = new char[TAILLE_CHAR_MAX];

			cout << "Saisissez une ville de départ : " ;
			cin >> villeDepart;
			catalogue -> AjouterTrajet(ajoutTrajetSimple(0,villeDepart)); //Détail des paramètres dans le .h correspondant
			cout << "Voyage ajouté avec succès ! " << endl;
			cout << "" << endl;

			delete [] villeDepart;
		}
		else if (choix == 3) //Insertion d'un trajet composé
		{
			char * villeDepart = new char[TAILLE_CHAR_MAX];

			cout << "Saisissez une ville de départ : " ;
			cin >> villeDepart;
			catalogue -> AjouterTrajet(ajoutTrajetCompose(0,villeDepart)); //Détail des paramètres dans le .h correspondant
			cout << "Voyage ajouté avec succès ! " << endl;
			cout << "" << endl;

			delete [] villeDepart;
		}
		else if (choix == 4) //Recherche simple
		{
			char * villeDepart = new char [TAILLE_CHAR_MAX];
			char * villeArrivee = new char [TAILLE_CHAR_MAX];

			cout << "Indiquez une ville de départ : ";
			cin >> villeDepart;
			cout << "Indiquez une ville d'arrivée : ";
			cin >> villeArrivee;
			catalogue -> RechercheSimple(villeDepart,villeArrivee); //Détail des paramètres dans le .h correspondant

			delete [] villeDepart;
			delete [] villeArrivee;
		}
		else if (choix == 5) //Recherche complète
		{
			char * villeDepart = new char [TAILLE_CHAR_MAX];
			char * villeArrivee = new char [TAILLE_CHAR_MAX];
		    	Trajet ** enchainementsPossible = new Trajet * [TAILLE_TRAJET_MAX];
			int caseSuivante = 0;
			int contientTrajet = 0;

			cout << "Indiquez une ville de départ : ";
			cin >> villeDepart;
			cout << "Indiquez une ville d'arrivée : ";
			cin >> villeArrivee;
			catalogue -> RechercheComplete(villeDepart,villeArrivee,enchainementsPossible,caseSuivante,&contientTrajet); 
			//Détail des paramètres dans le .h correspondant

			if(contientTrajet == 0)
			{
				cout << "" << endl;
				cout << "Il n'y a pas de trajets qui satisfont votre demande." << endl;
			}

			delete [] villeDepart;
			delete [] villeArrivee;
			delete [] enchainementsPossible;
		}
		else if (choix == 6) //Ecriture dans un fichier
		{
			
		}
		else if (choix == 7) //Lecture dans un fichier
		{
			cout << "Indiquez le chemin d'accès du fichier dans lequel vous voulez récupérer les trajets : "<<endl;
			string nomFichier; // /home/acroc/Documents/TP2C++2/TP2C++_VersionFinale/Test.txt
			cin >> nomFichier;
			//catalogue->LectureToutTrajetFichier(nomFichier);
			
			int choixLect;
			cout<<endl;

			cout << " *********************************   MENU LECTURE   ***************************** " << endl;
			cout << "- 1 pour récupérer tous les trajets du fichier" << endl;
			cout << "- 2 pour récupérer les trajets simples ou composés du fichier" << endl;
			cout << "- 3 pour récupérer les trajets selon la ville de départ et/ou la ville d'arrivée du fichier" << endl;
			cout << "- 4 pour récupérer les trajets compris dans un intervalle présent dans le fichier" << endl;
			cout << "- 0 pour retourner au menu principal" << endl;
			cout << " ********************************************************************************* " << endl;
			cout << "Quel type de récupération souhaitez-vous faire? : ";

			cin >> choixLect;
			cout << "" << endl;
			
			while(cin.fail())
			{
				cout<<"Erreur, entrez un nombre : ";
				cin.clear();
				cin.ignore(256,'\n');
				cin>>choixLect;
				cout<<""<<endl;
			}
			
			while(choixLect!=0)
			{
				while(cin.fail())
				{
					cout<<"Erreur, entrez un nombre : ";
					cin.clear();
					cin.ignore(256,'\n');
					cin>>choixLect;
					cout<<""<<endl;
				}

				if (choixLect == 1) //Lecture generale dans un fichier
				{
					catalogue->LectureToutTrajetFichier(nomFichier);
					cout << "Succès de la récupération des trajets présents dans le fichier" << endl;
						
				}
				else if (choixLect == 2) //Lecture selon type trajet dans un fichier
				{	
					string type;
					
					cout << " - Tapez S pour récupérer uniquement les trajets simples " << endl;
					cout << " - Tapez C pour récupérer uniquement les trajets composés " << endl;
					cout<< "Choisissez une option : ";
					cin>>type;
					catalogue->LectureTypeTrajetFichier(nomFichier,type);					
						
				}
				else if (choixLect == 3) //Lecture des trajets dans un fichier selon ville d'arrivé et/ou de depart 
				{
					
				}
				else if (choixLect == 4) //Lecture dans un fichier d'une selection de trajets compris dans un intervalle
				{
					
						
				}
				else  //Si la donnée entrée n'est pas correcte
				{
					cout << "La donnée saisie est incorrecte." << endl;
				}
				
				cout<<""<<endl;
				cout << "Quel type de récupération souhaitez-vous faire? : ";
				cin >> choixLect;
			}
			cout<<"Retour au menu principal"<<endl;

		}
		else //Si la donnée entrée n'est pas correcte
		{
			cout << "La donnée saisie est incorrecte." << endl;
		}

		cout << "" << endl;
		//Menu proposé à l'utilisateur
		affichageMenuPrincipal();
		
		//Choix de l'option
		cin >> choix;
		cout << "" << endl;


	}

	cout << "*******************************  Merci et à bientôt ! *****************************" << endl;
	cout << "" << endl;

	delete catalogue;

	return 0;

} //----- fin de main

