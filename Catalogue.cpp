/*************************************************************************
                           TrajetCompose  -  Classe decrivant les trajets composes
                             -------------------
    début                : 20/11/2018
    copyright            : (C) 2018 par Andréa CROC and Sophie LABOUCHEIX
    e-mail               : andrea.croc@insa-lyon.fr and sophie.laboucheix@insa-lyon.fr
*************************************************************************/


//---------- Réalisation de la classe <Catalogue> (fichier Catalogue.cpp) ------------

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

void Catalogue::LectureTypeTrajetFichier(string nomFichier, string type)
// Algorithme :
{
	ifstream fic;
	fic.open(nomFichier.c_str());
	while(!fic)
	{
		cout<<"Erreur à l'ouverture du fichier, entrez de nouveau le chemin :"<<endl;
		cin>>nomFichier;
		fic.open(nomFichier.c_str()); //Ne cree pas de fichier permet juste d'en ouvrir un existant
	}
	
	while(type!="S" || type!="C")
	{
		cout << " - Tapez S pour récupérer uniquement les trajets simples " << endl;
		cout << " - Tapez C pour récupérer uniquement les trajets composés " << endl;
		cin>>type;
	}

	while(!fic.eof())
	{
		string ligne;
		getline(fic,ligne,',');
		
		if(type=="C")
		{
		
			if(ligne == "C")
			{			
				
				string villeDep;
				string villeArr;
				
				getline(fic,villeDep,',');
				getline(fic,villeArr,',');
				
				Trajet * trajetCompose = new TrajetCompose(villeDep.c_str(),villeArr.c_str());
				
				string nbLigne;
				getline(fic,nbLigne);
				int nbTraj =atoi(nbLigne.c_str());
				
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
				AjouterTrajet(trajetCompose);
				
			} 
		}
		else if(type=="S")
		{
			
			 if(ligne == "S")
			 {

				string villeDep;
				string villeArr;
				string moyenTransp;
			
				getline(fic,villeDep,',');
				getline(fic,villeArr,',');
				getline(fic,moyenTransp);
				
				
				Trajet * trajetSimple= new TrajetSimple(villeDep.c_str(),villeArr.c_str(),moyenTransp.c_str());
				
				AjouterTrajet(trajetSimple);	

			}
		}

	}
	
	fic.close();
} // --Fin de LectureTypeTrajetFichier

void Catalogue::LectureToutTrajetFichier(string nomFichier)
// Algorithme :
{
	ifstream fic;
	fic.open(nomFichier.c_str());
	while(!fic)
	{
		cout<<"Erreur à l'ouverture du fichier, entrez de nouveau le chemin :"<<endl;
		cin>>nomFichier;
		fic.open(nomFichier.c_str()); //Ne cree pas de fichier permet juste d'en ouvrir un existant
	}

	while(!fic.eof())
	{
		string ligne;
		getline(fic,ligne,',');
		
		if(ligne == "C")
		{			
			
			string villeDep;
			string villeArr;
			
			getline(fic,villeDep,',');
			getline(fic,villeArr,',');
			
			Trajet * trajetCompose = new TrajetCompose(villeDep.c_str(),villeArr.c_str());
			
			string nbLigne;
			getline(fic,nbLigne);
			int nbTraj =atoi(nbLigne.c_str());
			
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
			AjouterTrajet(trajetCompose);
			
		} 
		
		else if(ligne == "S")
		{

			string villeDep;
			string villeArr;
			string moyenTransp;
		
			getline(fic,villeDep,',');
			getline(fic,villeArr,',');
			getline(fic,moyenTransp);
			
			
			Trajet * trajetSimple= new TrajetSimple(villeDep.c_str(),villeArr.c_str(),moyenTransp.c_str());
			
			AjouterTrajet(trajetSimple);	

		}

	}
	
	fic.close();

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


