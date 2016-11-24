#include <iostream>
#include "cellule.h"
#include <cstdlib>
#include <ctime>
#include <math.h>
#include <vector>
#include <fstream>


using namespace std;


int main()
{
    /**************************
    Initialiser la taille maximum de la cellule
    Initialiser la valeur de taux
    ****************************/
    // Pour le moment les deux variables sont fixes
    float taille_max_cell = 0.02;
    float taux = 1;
    /***************************/


    /*****************************
    Initialiser le nombre ce cellules
    ********************************/
    cout << "saisir le nombre de cellules" << endl;
    int nbrCellule = 0;
    cin >> nbrCellule;
    cin.ignore(); // flasher le buffer d'entrée
    /*******************************/


    /*******************************
    Initialiser les cellules
        - Les callules seront gardées dans un verteur de cellules
    *******************************/
    //ToDo
        // Déclaration du vecteur de cellules
        vector<Cellule> myvector;
        myvector.reserve(20);

        // Initialisation des cellules une par une tout en les insérant dans le vecteur de cellules
        for (int i=1; i<=nbrCellule; i++)
    {
        cout << "vector is being loaded " << i <<endl;
        srand (time(0)*i*11); // Astuce : utiliser la variable temps pour la fonction aléaoire
        cout << time(0)*i*11 << endl;
        Cellule nouvelle_cellule = Cellule(taille_max_cell,taux);
        myvector.push_back(nouvelle_cellule);
    }
    /*********************************/


    /********************************
    Initialiser le fichier de données qui seront représentées dans le graphe finale
    *********************************/
        // open a file in write mode.
       fstream outfile;
       outfile.open("file.dat",ios::out|ios::trunc|ios::ate);
       outfile << "#X....Y" << endl;
        // close the opened file.
       outfile.close();


    /*******************************
    Parcours dans le temps
        Evolution des cellules au cours du temps
    *******************************/


    // Boucle de parcours du temps
    for (int t=1; t<=20; t++)
    {
        cout << "itération n " << t << " dans le temps" << endl;
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
        cout << "a l'instant  " << t  << endl;
        cout << "myvector contains:";
        // boucle de parcours du vecteur des cellules
        for (int k=0; k<myvector.size(); k++)
        {
            cout << ' ' << myvector[k].getTailleInitCellule();
            cout << '\n';
            // Calucul de la taille totale de la tumeur
            taille_totale = taille_totale + myvector[k].getTailleActuCellule();
        }


        /******************************
        Enregistrer les données dans un fichier file.dat
        *******************************/
        fstream outfile; // déclarer un variable fichier
        outfile.open("file.dat",ios::out|ios::app|ios::ate); // ouvrir le fichier en mode écriture et ne pas écraser les données existantes si elles existent
        outfile << t << "...." << taille_totale << endl; // écrire dans le fichier file.dat la taille totale de la tumeur ainsi que le temps
        outfile.close(); // fermer le fichier
        /*************************************

 

    }
    /*******************************************************************************/


    return 0;
}
