/*************************************************************************
                           Catalogue  -  Classe decrivant le catalogue
                             -------------------
    début                : 20/11/2018
    copyright            : (C) 2018 par Andréa CROC and Sophie LABOUCHEIX
    e-mail               : andrea.croc@insa-lyon.fr and sophie.laboucheix@insa-lyon.fr
*************************************************************************/


//---------- Réalisation de la classe <Catalogue> (fichier Catalogue.cpp) ------------
#define _CRT_SECURE_NO_WARNINGS
//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include système
#include <string>
#include <fstream>
#include <cstring>
#include <iostream>
using namespace std;

//------------------------------------------------------ Include personnel
#include "Catalogue.h"

//------------------------------------------------------------- Constantes
#define TAILLE 100
#define TAILLE_CHAR_MAX 100
//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Méthodes publiques

void Catalogue::ecritureDansFichier(int choix, string cheminFic)
//Algorithme :
{
	ofstream fichier;
	fichier.open(cheminFic.c_str(), ios::out | ios::trunc);
	while(!fichier)
	{
		cout << "erreur à l'ouverture du fichier, essayez de nouveau :" << endl;
		cin >> cheminFic;
		cout << "" << endl;
		fichier.open(cheminFic.c_str(), ios::out | ios::trunc);
	}
	if (nbTrajetsC!=0)
	{
		int j=0;
		if (choix==1) // sauvegarde de tout
		{
			for (int i=0 ; i<nbTrajetsC ; i++)
			{
				j++;
				fichier << j << ",";
				tabTrajetCatalogue[i]->ecrire(fichier);
			}	
		}
		else if (choix==2) //sauvegarde selon le type de trajets
		{
			cout << "Quel type de trajets voulez vous sauvegarder? Simple(S) ou Composé(C)?" << endl;
			char resp;
			cin >> resp;
			while (resp!='S' && resp!='C')
			{
				cout << "caractère non reconnu, recommencez svp :" << endl;
				cin >> resp;
			}
			for (int i=0 ; i<nbTrajetsC ; i++)
			{
				if (tabTrajetCatalogue[i]->type == resp)
				{
					j++;
					fichier << j << ",";
					tabTrajetCatalogue[i]->ecrire(fichier);
				}
			}
		}
		else if (choix==3) //sauvegarde selon la ville d'arrivée et/ou de départ
		{
			cout << "Entrez le nom de la ville de départ que vous souhaitez sélectionner," << endl;
		        cout <<	"entrez \"empty\" si vous ne souhaitez pas effectuer de sélection sur la ville de départ :" << endl;
			string vd;
			cin >> vd;
			cout << "Entrez le nom de la ville d'arrivée que vous souhaitez séléctionner," << endl;
			cout << "entrez \"empty\" si vous ne souhaitez pas effectuer de sélection sur la ville d'arrivée :" << endl;
			string va; 
			cin >> va;
		}
		else if (choix==4) //sauvegarde dans un intervalle défini
		{
			cout << "entrez la borne inférieure de votre intervalle de sélection :" << endl;
			int borneInf;
			cin >> borneInf;
			while (cin.fail())
			{
				cout << "Erreur, entrez un nombre";
				cin.clear();
				cin.ignore(256,'\n');
				cin >> borneInf;
				cout << "" << endl;
			}
			if (borneInf<=0)
			{
				cout << "Votre nombre est négatif ou nul, il a été remplacé par 1" << endl;
				borneInf=1;
			}
			else if (borneInf > nbTrajetsC)
			{
				cout << "Votre nombre est supérieur au nombre de trajets présents dans le catalogue" << endl;
				cout << "il a été remplacé par " << nbTrajetsC << endl;
				borneInf=nbTrajetsC;
			}
			cout << "Entrez la borne supérieure de votre intervalle de sélection :" << endl;
			int borneSup;
			cin >> borneSup;
			while (cin.fail())
			{
				cout << "Erreur, entrez un nombre :";
				cin.clear();
				cin.ignore(256,'\n');
				cin >> borneSup;
				cout << "" <<endl;
			}
			if (borneSup < borneInf)
			{
				cout << "Votre borne supérieure est plus petite que votre borne inférieure" << endl;
				cout << "elle a été remplacée par la borne inférieure : " << borneInf << endl;
				borneSup = borneInf;
			}
			else if (borneSup > nbTrajetsC)
			{
				cout << "Votre borne supérieure est plus grande que le nombre de trajets présents dans le catalogue" << endl;
				cout << "elle a été remplacée par " << nbTrajetsC << endl;
				borneSup = nbTrajetsC;
			}
			for (int i=borneInf-1; i<borneSup; i++)
			{
				j++;
				fichier << j << ",";
				tabTrajetCatalogue[i]->ecrire(fichier);
			}
		}
		cout << j << " trajet(s) sauvegardé(s) avec succès ! " << endl;
	} 
	else
		cout << "Le catalogue actuel ne contient aucun trajets, sauvegarde impossible" << endl;
	fichier.close();

}// -- Fin de EcritureDansUnFichier

int Catalogue::LectureIntervalleTrajetFichier(string cheminFichier, int borneInf, int borneSup)
//Algorithme :
//On gère les erreurs liées au chemin d'accès du fichier
//Et on ajoute au catalogue les trajets dont le numéro fait partie de l'intervalle 
//dont les bornes sont données en paramètre
{
	ifstream fic;
	fic.open(cheminFichier.c_str());
	
	//si le chemin d'accès donné ne permet pas l'ouverture du fichier
	//on demande de nouveau le chemin d'accès au fichier
	while (!fic) 
	{
		cout << "Erreur à l'ouverture du fichier, entrez de nouveau le chemin :" << endl;
		cin >> cheminFichier;
		cout << "" << endl;
		fic.open(cheminFichier.c_str()); 
	}

	int comptTrajet = 0;

	while (!fic.eof()) //Tant qu'on n'est pas à la fin du fichier, on continue
	{
		string ligne, borneInter;
		int borneInt;

		getline(fic, borneInter, ',');
		getline(fic, ligne, ',');

		borneInt = atoi(borneInter.c_str());

		if (ligne == "C") //Si le trajet qu'on lit dans le fichier est un trajet composé
		{
			string villeDep;
			string villeArr;

			getline(fic, villeDep, ',');
			getline(fic, villeArr, ',');

			// On crée le trajet composé
			Trajet * trajetCompose = new TrajetCompose(villeDep.c_str(), villeArr.c_str());

			string nbLigne;
			getline(fic, nbLigne);
			int nbTraj = atoi(nbLigne.c_str());

			//On rajoute des trajets simples au trajet composé
			for (int i = 0; i < nbTraj; i++)
			{
				getline(fic, ligne, ',');

				if (ligne == "S")
				{
					string villeD;
					string villeA;
					string moyenT;

					getline(fic, villeD, ',');
					getline(fic, villeA, ',');
					getline(fic, moyenT);

					Trajet * trajetS = new TrajetSimple(villeD.c_str(), villeA.c_str(), moyenT.c_str());
					trajetCompose->AjoutTrajet(trajetS);
				}
			}
			//On ajoute le trajet composé au catalogue que si le numéro du trajet fait partie de l'intervalle des trajets 
			if (borneInt >= borneInf && borneInt <= borneSup)
			{
				AjouterTrajet(trajetCompose);
				comptTrajet++;
			}
		}
		else if (ligne == "S") //Si le trajet qu'on lit dans le fichier est un trajet simple
		{
			string villeDep;
			string villeArr;
			string moyenTransp;

			getline(fic, villeDep, ',');
			getline(fic, villeArr, ',');
			getline(fic, moyenTransp);

			//On crée le trajet simple
			Trajet * trajetSimple = new TrajetSimple(villeDep.c_str(), villeArr.c_str(), moyenTransp.c_str());

			//On l'ajoute au catalogue seulement si le numéro du trajet fait partie de l'intervalle
			if (borneInt >= borneInf && borneInt <= borneSup) 
			{
				AjouterTrajet(trajetSimple);
				comptTrajet++;
			}

		}

	}
	fic.close();
	return comptTrajet;
} // -- Fin de LectureIntervalleTrajetFichier

int Catalogue::LectureVilleTrajetFichier(string cheminFichier, string option,string villed,string villea)
// Algorithme :
//On ajoute au catalogue tous les trajets qui ont la même ville de départ et/ou d'arrivée 
//que celle(s) mentionnée(s) par l'utilisateur
//On récupère le choix de l'option de l'utilisateur pour savoir la ou les types de villes de sélection:
//soit la ville de départ, soit la ville d'arrivée, soit les deux
{
	ifstream fic;
	fic.open(cheminFichier.c_str());
	int comptTrajet = 0;

	//Tant qu'on n'est pas à la fin du fichier, on continue
	while (!fic.eof())
	{
		string ligne;
		getline(fic, ligne, ',');
		getline(fic, ligne, ',');

		if (ligne == "C") //Si le trajet qu'on lit dans le fichier est un trajet composé
		{
			string villeDep;
			string villeArr;

			getline(fic, villeDep, ',');
			getline(fic, villeArr, ',');

			Trajet * trajetCompose = new TrajetCompose(villeDep.c_str(), villeArr.c_str());

			string nbLigne;
			getline(fic, nbLigne);
			int nbTraj = atoi(nbLigne.c_str());

			//On récupère les trajets simples du trajet composé
			for (int i = 0; i < nbTraj; i++)
			{
				getline(fic, ligne, ',');

				if (ligne == "S")
				{
					string villeD;
					string villeA;
					string moyenT;

					getline(fic, villeD, ',');
					getline(fic, villeA, ',');
					getline(fic, moyenT);

					Trajet * trajetS = new TrajetSimple(villeD.c_str(), villeA.c_str(), moyenT.c_str());
					trajetCompose->AjoutTrajet(trajetS);
				}
			}

			//On ajoute le trajet au catalogue que si la ville de départ et/ou d'arrivée du trajet 
			//sont celles dites par l'utilisateur
			if (option == "D" && villeDep==villed)
			{
				AjouterTrajet(trajetCompose);
				comptTrajet++;
			}
			else if (option == "A" && villeArr == villea)
			{
				AjouterTrajet(trajetCompose);
				comptTrajet++;
			}
			else if (option == "DA" && villeDep == villed && villeArr == villea)
			{
				AjouterTrajet(trajetCompose);
				comptTrajet++;
			}
		}

		else if (ligne == "S") //Si le trajet qu'on lit dans le fichier est simple
		{
			string villeDep;
			string villeArr;
			string moyenTransp;

			getline(fic, villeDep, ',');
			getline(fic, villeArr, ',');
			getline(fic, moyenTransp);

			Trajet * trajetSimple = new TrajetSimple(villeDep.c_str(), villeArr.c_str(), moyenTransp.c_str());

			//On l'ajoute au catalogue que si la ville de départ et/ou d'arrivée du trajet 
			//sont celles dites par l'utilisateur
			if (option == "D" && villeDep == villed)
			{
				AjouterTrajet(trajetSimple);
				comptTrajet++;
			}
			else if (option == "A" && villeArr == villea)
			{
				AjouterTrajet(trajetSimple);
				comptTrajet++;
			}
			else if (option == "DA" && villeDep == villed && villeArr == villea)
			{
				AjouterTrajet(trajetSimple);
				comptTrajet++;
			}
		}

	}
	fic.close();
	return comptTrajet;
} //-- Fin de LectureVilleTrajetFichier

int Catalogue::LectureChoixVilleTrajetFichier(string cheminFichier, string option)
// Algorithme :
// On gère les erreurs liées au chemin d'accès du fichier 
//et au choix de l'option sur la sélection des trajets
{
	ifstream fic;
	fic.open(cheminFichier.c_str());
	
	//si le chemin d'accès donné ne permet pas l'ouverture du fichier
	//on demande de nouveau le chemin d'accès au fichier
	while (!fic)
	{
		cout << "Erreur à l'ouverture du fichier, entrez de nouveau le chemin :" << endl;
		cin >> cheminFichier;
		cout <<""<< endl;
		fic.open(cheminFichier.c_str());
	}

	fic.close();

	//Si l'option saisie par l'utilisateur ne fait pas partie des trois proposées
	//On lui demande de nouveau d'en choisir une 
	while (option != "D" && option != "A" && option != "DA") {
		cout << "Erreur dans le choix de l'option" << endl;
		cout << " - Tapez D pour récupérer les trajets suivant leur ville de départ " << endl;
		cout << " - Tapez A pour récupérer les trajets suivant leur ville d'arrivée " << endl;
		cout << " - Tapez DA pour récupérer les trajets suivant leurs villes de départ et d'arrivée" << endl;
		cout << "Choisissez un nom d'option valide : ";
		cin >> option;
		cout <<""<< endl;
	}

	int nbTrajet = 0;
	if (option == "D")
	{
		string villed;
		cout << "Indiquez le nom de la ville de départ que les trajets doivent avoir : ";
		cin >> villed;

		nbTrajet = LectureVilleTrajetFichier(cheminFichier, option, villed, "inconnue");
		//Détail des paramètres dans le .h correspondant

		return nbTrajet;
	}
	else if (option == "A")
	{
		string villea;
		cout << "Indiquez le nom de la ville d'arrivée que les trajets doivent avoir : ";
		cin >> villea;

		nbTrajet = LectureVilleTrajetFichier(cheminFichier, option, "inconnue", villea);
		//Détail des paramètres dans le .h correspondant

		return nbTrajet;
	}
	else if (option == "DA")
	{
		string villed;
		cout << "Indiquez le nom de la ville de départ que les trajets doivent avoir : ";
		cin >> villed;

		string villea;
		cout << "Indiquez le nom de la ville d'arrivée que les trajets doivent avoir : ";
		cin >> villea;

		nbTrajet = LectureVilleTrajetFichier(cheminFichier, option, villed, villea);
		//Détail des paramètres dans le .h correspondant

		return nbTrajet;
	}

	return nbTrajet;
} // -- Fin de LectureChoixVilleTrajetFichier

int Catalogue::LectureTypeTrajetFichier(string cheminFichier, string type)
//Algorithme :
//On ajoute au catalogue tous les trajets du fichier dont le type est donné en paramètre
{
	ifstream fic;
	fic.open(cheminFichier.c_str());
	
	int comptTrajet = 0;
	//Tant qu'on n'est pas à la fin du fichier, on continue
	while (!fic.eof())
	{
		string ligne;
		getline(fic, ligne, ',');
		getline(fic, ligne, ',');

		if (ligne == "C") //Si le trajet qu'on lit dans le fichier est un trajet composé
		{
			string villeDep;
			string villeArr;

			getline(fic, villeDep, ',');
			getline(fic, villeArr, ',');

			Trajet * trajetCompose = new TrajetCompose(villeDep.c_str(), villeArr.c_str());

			string nbLigne;
			getline(fic, nbLigne);
			int nbTraj = atoi(nbLigne.c_str());

			//On ajoute les trajets simples du trajet composé au trajet composé
			for (int i = 0; i < nbTraj; i++)
			{
				getline(fic, ligne, ',');

				if (ligne == "S")
				{
					string villeD;
					string villeA;
					string moyenT;

					getline(fic, villeD, ',');
					getline(fic, villeA, ',');
					getline(fic, moyenT);

					Trajet * trajetS = new TrajetSimple(villeD.c_str(), villeA.c_str(), moyenT.c_str());
					trajetCompose->AjoutTrajet(trajetS);
				}
			}

			//On ajoute le trajet composé au catalogue que si le type de trajet choisit par l'utilisateur est composé
			if (type == "C")
			{
				AjouterTrajet(trajetCompose);
				comptTrajet++;
			}
		}

		else if (ligne == "S") //Si le trajet qu'on lit dans le fichier est un trajet simple
		{
			string villeDep;
			string villeArr;
			string moyenTransp;

			getline(fic, villeDep, ',');
			getline(fic, villeArr, ',');
			getline(fic, moyenTransp);

			Trajet * trajetSimple = new TrajetSimple(villeDep.c_str(), villeArr.c_str(), moyenTransp.c_str());

			//On ajoute le trajet simple au catalogue que si le type de trajet choisit par l'utilisateur est simple
			if (type=="S")
			{
				AjouterTrajet(trajetSimple);
				comptTrajet++;
			}	
		}

	}
	fic.close();
	return comptTrajet;

	/*while (!fic.eof())
	{
		string ligne;
		getline(fic, ligne, ',');
		getline(fic, ligne, ',');

		if (type == "C" && ligne == "C")
		{
			string villeDep;
			string villeArr;

			getline(fic, villeDep, ',');
			getline(fic, villeArr, ',');

			Trajet * trajetCompose = new TrajetCompose(villeDep.c_str(), villeArr.c_str());

			string nbLigne;
			getline(fic, nbLigne);
			int nbTraj = atoi(nbLigne.c_str());

			for (int i = 0; i < nbTraj; i++)
			{
				getline(fic, ligne, ',');

				if (ligne == "S")
				{
					string villeD;
					string villeA;
					string moyenT;

					getline(fic, villeD, ',');
					getline(fic, villeA, ',');
					getline(fic, moyenT);

					Trajet * trajetS = new TrajetSimple(villeD.c_str(), villeA.c_str(), moyenT.c_str());
					trajetCompose->AjoutTrajet(trajetS);
				}
			}
			AjouterTrajet(trajetCompose);
		}
		else if (type == "C" && ligne == "S")
		{
			getline(fic, ligne);
		}

		else if (type == "S" && ligne == "S")
		{
			string villeDep;
			string villeArr;
			string moyenTransp;

			getline(fic, villeDep, ',');
			getline(fic, villeArr, ',');
			getline(fic, moyenTransp);


			Trajet * trajetSimple = new TrajetSimple(villeDep.c_str(), villeArr.c_str(), moyenTransp.c_str());

			AjouterTrajet(trajetSimple);

		}
		else if (type == "S" && ligne == "C")
		{

			getline(fic, ligne, ',');
			getline(fic, ligne, ',');

			string nbLigne;
			getline(fic, nbLigne);
			int nbTraj = atoi(nbLigne.c_str());
			for (int i = 0; i < nbTraj; i++)
			{
				getline(fic, ligne);
			}

		}

	}
	
	fic.close();*/

} // -- Fin de LectureTypeTrajetFichier

int Catalogue::LectureChoixTypeTrajetFichier(string cheminFichier, string type)
// Algorithme :
//On gère les erreurs liées au chemin d'accès du fichier
//et celles liées au choix de l'utilisateur sur le type de trajet voulu : simple ou composé
{
	ifstream fic;
	fic.open(cheminFichier.c_str());

	//si le chemin d'accès donné ne permet pas l'ouverture du fichier
	//on demande de nouveau le chemin d'accès au fichier
	while(!fic)
	{
		cout<<"Erreur à l'ouverture du fichier, entrez de nouveau le chemin :"<<endl;
		cin>> cheminFichier;
		cout << "" << endl;
		fic.open(cheminFichier.c_str()); 
	}
	fic.close();

	//Tant que l'utilisateur ne choisit pas une des deux options
	//On lui demande d'en choisir une de nouveau
	while(type!="S" && type!="C")
	{
		cout << "Erreur dans l'option choisie" << endl;
		cout << " - Tapez S pour récupérer uniquement les trajets simples" << endl;
		cout << " - Tapez C pour récupérer uniquement les trajets composés" << endl;
		cout<<"Choisissez une option avec un nom valide : ";
		cin>>type;	
		cout << "" << endl;
	}
	
	int nbTrajet = LectureTypeTrajetFichier(cheminFichier, type);
	//Détails des paramètres dans le .h correspondant

	return nbTrajet;
	
} // --Fin de LectureChoixTypeTrajetFichier

int Catalogue::LectureToutTrajetFichier(string cheminFichier)
// Algorithme :
//On ajoute au catalogue tous les trajets qui sont contenus dans le fichier
{
	ifstream fic;
	fic.open(cheminFichier.c_str());

	//si le chemin d'accès donné ne permet pas l'ouverture du fichier
	//on demande de nouveau le chemin d'accès au fichier
	while(!fic)
	{
		cout<<"Erreur à l'ouverture du fichier, entrez de nouveau le chemin :"<<endl;
		cin>> cheminFichier;
		fic.open(cheminFichier.c_str()); //Ne cree pas de fichier permet juste d'en ouvrir un existant
	}

	int compteurTrajet = 0;
	//Tant qu'on n'est pas à la fin du fichier, on continue
	while(!fic.eof())
	{
		string ligne;
		getline(fic,ligne,',');
		getline(fic,ligne,',');
		
		if(ligne == "C") //Si le trajet qu'on lit dans le fichier est composé
		{			
			
			string villeDep;
			string villeArr;
			
			getline(fic,villeDep,',');
			getline(fic,villeArr,',');

			//On le crée
			Trajet * trajetCompose = new TrajetCompose(villeDep.c_str(),villeArr.c_str());
			
			string nbLigne;
			getline(fic,nbLigne);
			int nbTraj =atoi(nbLigne.c_str());
			
			//On récupère ses trajets simples
			for(int i=0; i<nbTraj; i++)  
			{
				getline(fic,ligne,',');
				
				if(ligne =="S")
				{
					string villeD;
					string villeA;
					string moyenT;
					
					getline(fic,villeD,',');
					getline(fic,villeA,',');
					getline(fic,moyenT);
					
					Trajet * trajetS= new TrajetSimple(villeD.c_str(),villeA.c_str(),moyenT.c_str());
					trajetCompose->AjoutTrajet(trajetS);
				}
			}
			//On l'ajoute au catalogue
			AjouterTrajet(trajetCompose);
			compteurTrajet++;
			
		} 
		
		else if(ligne == "S") //Si le trajet lu dans le fichier est simple
		{

			string villeDep;
			string villeArr;
			string moyenTransp;
		
			getline(fic,villeDep,',');
			getline(fic,villeArr,',');
			getline(fic,moyenTransp);
			
			
			Trajet * trajetSimple= new TrajetSimple(villeDep.c_str(),villeArr.c_str(),moyenTransp.c_str());
			
			//On l'ajoute au catalogue
			AjouterTrajet(trajetSimple);
			compteurTrajet++;

		}

	}
	
	fic.close();
	return compteurTrajet;

} // --Fin de LectureTrajetFichier

int Catalogue::RechercheComplete (const char * villeDepart, const char * villeArrivee, Trajet ** enchainementsPossible, int caseSuivante,int * contientTrajet) const
// Algorithme :
// Appels récursifs à la recherche complète
// Si les élements de recherche correspondent, on continue la recherche
// On évite les boucles infinies grâce à l'usage des boucles FOR
//Si un trajet est trouvé, on incrémente contientTrajet
{
	int i;
	for(i=0;i<nbTrajetsC;i++) 
	{
		//Si un chemin est trouvé, on l'ajoute au tableau et on l'affiche
		if(strcmp(villeDepart,tabTrajetCatalogue[i]->GetVilleDepart()) == 0 && strcmp(villeArrivee,tabTrajetCatalogue[i]->GetVilleArrivee()) == 0)
		{
			*contientTrajet = *contientTrajet + 1;
			enchainementsPossible[caseSuivante] = tabTrajetCatalogue[i];
			afficheCheminRechercheComplete(enchainementsPossible,caseSuivante);
		
		} else if (strcmp(villeDepart,tabTrajetCatalogue[i]->GetVilleDepart()) == 0) // Sinon si la ville de départ correspond, on l'ajoute au tableau et on continue la recherche
		{
			enchainementsPossible[caseSuivante] = tabTrajetCatalogue[i];
			RechercheComplete(tabTrajetCatalogue[i]->GetVilleArrivee(),villeArrivee,enchainementsPossible,caseSuivante+1,contientTrajet);
		}
	}

	return 0;

} // -- fin de RechercheComplete

void Catalogue::afficheCheminRechercheComplete(Trajet ** enchainementsPossible, int caseSuivante) const
// Algorithme :
// Rien à préciser
{
	int i;
	cout << "" << endl;
	cout << "Voici une possibilité : " << endl;
	for(i=0;i<=caseSuivante;i++)
	{
		enchainementsPossible[i]->AfficherTrajet(1);
	}

} // -- fin de afficheCheminRechercheComplete

void Catalogue::RechercheSimple (const char * villeDepart, const char * villeArrivee) const
// Algorithme :
// Parcours du catalogue pour regader si certains trajets peuvent correspondre aux paramètres donnés à la fonction
{
	int i;
	int nbPossibilites = 0;
	for(i=0;i<nbTrajetsC;i++) //Parcours de tous les trajets
	{
		if(strcmp(tabTrajetCatalogue[i]->GetVilleDepart(),villeDepart)==0 && strcmp(tabTrajetCatalogue[i]->GetVilleArrivee(),villeArrivee) == 0)
		{
			nbPossibilites ++;
			cout << "" << endl;
			cout << "Possibilité " << nbPossibilites << endl;
			tabTrajetCatalogue[i] -> AfficheTrajetPossibleSimple();
			cout << "" << endl;
		}
	}

	if(nbPossibilites == 0) //Si aucun trajet n'a été trouvé, on informe l'utilisateur
	{
		cout << "" << endl;
		cout << "Aucun trajet ne peut satisfaire votre demande." << endl;
	}
} // -- fin de RechercheSimple


void Catalogue::AfficherTrajetsCatalogue()  const
// Algorithme :
// Rien à préciser
{

	int i;
	if(nbTrajetsC == 0) //S'il n'y a aucun trajet, on informe l'utilisateur
	{
		cout << "Aucun trajet n'a été inséré pour le moment." << endl;
	}
	for(i=0;i<nbTrajetsC;i++) //Parcours de tous les trajets
	{
		cout << "VOYAGE " << i+1 << " : " << endl;
		tabTrajetCatalogue[i]->AfficherTrajet(1);
		cout << "" << endl;
	}

	cout << "" << endl;


} // -- fin de AfficherTrajetsCatalogue


void Catalogue::AjouterTrajet (Trajet * trajet) 
// Algorithme :
// Si la taille du tableau du catalogue est trop petite, on l'agrandie
// Puis, on l'ajoute
{

	int i;

	if(nbTrajetsC==tailleC) //S'il faut agrandir le tableau
	{
		tailleC+=10;
		Trajet ** tabNouveau = new Trajet* [tailleC];
       		Trajet ** temp = tabTrajetCatalogue;
		for(i = 0;i<tailleC-10;i++) 
		{
			tabNouveau[i] = tabTrajetCatalogue[i];
		}
		tabTrajetCatalogue = tabNouveau;
		delete[]temp;              

	}

	tabTrajetCatalogue[nbTrajetsC]=trajet; //Ajout
	nbTrajetsC ++;

		
	
} // -- fin de AjouterTrajet


//-------------------------------------------- Constructeurs - destructeur


Catalogue::Catalogue ()
// Algorithme :
// Rien à préciser
{

	tabTrajetCatalogue = new Trajet* [TAILLE];
	nbTrajetsC = 0;
	tailleC = TAILLE;
	#ifdef MAP
	    cout << "Appel au constructeur de <Catalogue>" << endl;
	#endif
} //----- Fin de Catalogue


Catalogue::~Catalogue ( )
// Algorithme :
// Rien à préciser
{

	int i;
	for(i=0;i<nbTrajetsC;i++) 
	{
		delete tabTrajetCatalogue[i];
	}
	delete [] tabTrajetCatalogue;
	#ifdef MAP
	    cout << "Appel au destructeur de <Catalogue>" << endl;
	#endif
} //----- Fin de ~Catalogue


