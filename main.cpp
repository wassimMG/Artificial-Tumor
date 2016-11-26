#include <iostream>
#include "cellule.h"
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <vector>
#include <fstream>

using namespace std;

/******************************
FONCTION PRINCIPALE : MAIN
*******************************/
int main()
{
    /***************************************************
    1----------------------------------------
    Initialiser la taille maximum de la cellule
    Initialiser la valeur de taux
    ***************************************************/
    // Pour le moment les trois variables sont fixes
    float taille_init_max_cell = 0.000099; // Lo_max (en mètre)
    float taille_max_cell = 0.000198; // 2*taille_init_max_cell = 2*Lo_max = 2*99.10^(-6) = 198.10^(-6)
    float taux = 1;


    /***************************************************
    2----------------------------------------
    Initialiser le nombre ce cellules
    ***************************************************/
    cout << "saisir le nombre de cellules" << endl;
    int nbrCellule = 0;
    cin >> nbrCellule;
    cin.ignore(); // flasher le buffer d'entrée


    /***************************************************
    3----------------------------------------
    Initialiser les cellules
        - Les callules seront gardées dans un verteur de cellules
    ***************************************************/
    //ToDo
        // Déclaration du vecteur de cellules
        vector<Cellule> myvector;
        myvector.reserve(20);

        // Initialisation des cellules une par une tout en les insérant dans le vecteur de cellules
        for (int i=1; i<=nbrCellule; i++)
    {
        srand (time(0)*i*11); // Astuce : utiliser la variable temps pour la fonction aléaoire
        Cellule nouvelle_cellule = Cellule(taille_max_cell,taux);
        myvector.push_back(nouvelle_cellule);
    }


    /***************************************************
    4----------------------------------------
    Initialiser le fichier de données qui seront représentées dans le graphe finale
    ***************************************************/
       fstream outfile; // déclarer une variable fichier
       outfile.open("2D_tumeur_fx_temps.dat",ios::out|ios::trunc|ios::ate); // ouvrir le fichier en mode écriture et ne pas écraser les données existantes si elles existent
       outfile << "# tumeur en fct du temps" << endl;
       outfile.close(); // fermer le fichier

        fstream outfile1; // déclarer une variable fichier
        outfile1.open("2D_nbr_cellule_fx_temps.dat",ios::out|ios::trunc|ios::ate); // ouvrir le fichier en mode écriture et ne pas écraser les données existantes si elles existent
        outfile1 << "# nbr_cellule en fct du temps" << endl; // écrire dans le fichier file.dat la taille totale de la tumeur ainsi que le temps
        outfile1.close(); // fermer le fichier

        fstream outfile2; // déclarer une variable fichier
        outfile2.open("3D_tumeur_fxy_nbr_cellule_fxy_temps.dat",ios::out|ios::trunc|ios::ate); // ouvrir le fichier en mode écriture et ne pas écraser les données existantes si elles existent
        outfile2 << "# Longueur tumeur nbr_cellule temps" << endl; // écrire dans le fichier file.dat la taille totale de la tumeur ainsi que le temps
        outfile2.close(); // fermer le fichier

    /***************************************************
    5----------------------------------------
    Parcours dans le temps
        Evolution des cellules au cours du temps
    ***************************************************/


    // Boucle de parcours du temps
    for (int t=1; t<=20; t++)
    {
        // boucle de parcours du vecteur de cellules
        for (int j=1; j<=nbrCellule; j++)
        {
            // Si la cellule n'est pas arrivée à l'age de division
            if (myvector[j].getAgeDiv() > myvector[j].getAge())
            {
                // Alors agrandir la cellule selon le modèle
                myvector[j].agrradirCellule(taux,t/10);
            }
            // Sinon c'est la division
            else
            {
                // créer deux cellules filles à partir de la cellule qui se divise
                Cellule cellule_fille_1 = Cellule(taille_max_cell,taux);
                Cellule cellule_fille_2 = Cellule(taille_max_cell,taux,cellule_fille_1.getTailleInitCellule());
                Cellule arrayinsert [] = { cellule_fille_1 , cellule_fille_2 };

                //  inserer les deux nouvelles cellules dans le vecteur de cellules
                myvector.insert (myvector.begin()+j, arrayinsert, arrayinsert+2);

                // Effacer la cellule mère qui vient de se diviser
                myvector.erase (myvector.begin()+j);
            }
            /**/
        }

        float taille_totale = 0;
        // boucle de parcours du vecteur des cellules
        for (int k=0; k<myvector.size(); k++)
        {
            // Calucul de la taille totale de la tumeur
            taille_totale = taille_totale + myvector[k].getTailleActuCellule();
        }


        /***************************************************
        6----------------------------------------
        Enregistrer les données dans un fichier
        ***************************************************/
        outfile.open("2D_tumeur_fx_temps.dat",ios::out|ios::app|ios::ate); // ouvrir le fichier en mode écriture et ne pas écraser les données existantes si elles existent
        outfile << t << " " << taille_totale << endl; // écrire dans le fichier file.dat la taille totale de la tumeur ainsi que le temps
        outfile.close(); // fermer le fichier

        outfile1.open("2D_nbr_cellule_fx_temps.dat",ios::out|ios::app|ios::ate); // ouvrir le fichier en mode écriture et ne pas écraser les données existantes si elles existent
        outfile1 << t << " " << myvector.size() << endl; // écrire dans le fichier file.dat la taille totale de la tumeur ainsi que le temps
        outfile1.close(); // fermer le fichier

        outfile2.open("3D_tumeur_fxy_nbr_cellule_fxy_temps.dat",ios::out|ios::app|ios::ate); // ouvrir le fichier en mode écriture et ne pas écraser les données existantes si elles existent
        outfile2 << t << " " << taille_totale << " " << myvector.size() << endl; // écrire dans le fichier file.dat la taille totale de la tumeur ainsi que le temps
        outfile2.close(); // fermer le fichier


    }


    /***************************************************
    7----------------------------------------
    Entrer le script de GNUPLOT dans un fichier SCRIPT.DAT
    ***************************************************/
        //open a file in write mode.
       fstream outfile3;
       outfile3.open("script.dat",ios::out|ios::trunc|ios::ate);
       outfile3 << "splot '3D_tumeur_fxy_nbr_cellule_fxy_temps.dat' with linespoints title 'variation de la tumeur' ;set xlabel 'temps' ;set ylabel 'metre'; set zlabel 'nbr_cellules'" << endl;
        // close the opened file.
       outfile3.close();

        // Afficher le graphe de varation de la taille totale de la tumeur en fonction du temps
       system("gnuplot -persist script.dat");


    return 0;
}
