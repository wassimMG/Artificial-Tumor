#include <iostream>
#include "cellule.h"
#include <stdlib.h>
#include <ctime>
#include <math.h>

using namespace std;


void Cellule::agrradirCellule(float v_taux , float v_time)
{
    m_age=m_age+v_time;
    m_taille_actu = m_taille_init * exp(m_age/v_taux);
}

 float Cellule::getTailleInitCellule()
 {
     return m_taille_init;
 }

 float Cellule::getTailleActuCellule()
 {

     return m_taille_actu;
 }

 float Cellule::getAge()
 {
     return m_age;
 }


float Cellule::getAgeDiv()
{
        return m_age_division;
}


 Cellule::Cellule(float v_taille_max, float v_taux)
 {
     /**ToDo - passer taille_max en parametre*/
     //float taille_max = 0.02;

     /**ToDo - passer taux en param�tres*/
     //int taux = 1;

    /** initialiser l'age de la cellule � z�ro*/
     m_age = 0;

    /***************************************************
    //Initialiser la taille de la cellule : valeure al�atoire
    /***************************************************/
    //cout << "Initialiser la taille de la cellule : valeure al�atoire" << endl;
    //srand (time(0)); // initialiser la fonction random
    float rand_value = 1+(rand() % 100); // choisir un nombre al�atoire entre 1 et 100
    //cout << rand_value << endl;
    m_taille_init = rand_value/10000; // m_taille_init est une valeure al�atoire entre 10^(-4) et 10^(-2)
    //cout << m_taille_init << endl;
    /***************************************************/


    m_taille_actu = m_taille_init; // au moment de cr�ation de la cellule la taille actuelle est �gale � la taille initiale

    /***************************************************
    // Calculer l'age de division de la cellule
    // En fonction de la taille initiale de la cellule
    // Et tenant compte la taille maximum qu'une cellule
    // peut atteindre avant de se diviser par mitose
    // Dans ce calcul le r�sultat sera arrondi au dixi�me
    // afin de pouvoir utiliser apr�s la valeur
    ***************************************************/
    if (m_taille_init!=0)
    {
        /** calcul de la valeure r�elle de l'age de la cellule apr�s lequel elle va se diviser */
        float age_div_reel = v_taux*log(v_taille_max/m_taille_init);
        //cout << "calcul de la valeure r�elle de l'age de la cellule apr�s lequel elle va se diviser" << endl;
        //cout << age_div_reel << endl;
       /** valeur finale arrondie au dixi�me pr�s */
        m_age_division = round(age_div_reel*10)/10;
        //cout << " valeur finale arrondie au dixi�me pr�s" << endl;
        //cout << m_age_division << endl;
    }
 }


 Cellule::Cellule(float v_taille_max, float v_taux, float v_taille_init_soeur)
 {
     /** initialiser l'age de la cellule � z�ro*/
     m_age = 0;

    /***************************************************
    //Initialiser la taille de la cellule : taille de la cellule m�re moins la taille de la soeur
    /***************************************************/
    m_taille_init = v_taille_max - v_taille_init_soeur;


    m_taille_actu = m_taille_init; // au moment de cr�ation de la cellule la taille actuelle est �gale � la taille initiale

    /***************************************************
    // Calculer l'age de division de la cellule
    // En fonction de la taille initiale de la cellule
    // Et tenant compte la taille maximum qu'une cellule
    // peut atteindre avant de se diviser par mitose
    // Dans ce calcul le r�sultat sera arrondi au dixi�me
    // afin de pouvoir utiliser apr�s la valeur
    ***************************************************/
    if (m_taille_init!=0)
    {
        /** calcul de la valeure r�elle de l'age de la cellule apr�s lequel elle va se diviser */
        float age_div_reel = v_taux*log(v_taille_max/m_taille_init);
        //cout << "calcul de la valeure r�elle de l'age de la cellule apr�s lequel elle va se diviser" << endl;
        cout << age_div_reel << endl;
       /** valeur finale arrondie au dixi�me pr�s */
        m_age_division = round(age_div_reel*10)/10;
        //cout << " valeur finale arrondie au dixi�me pr�s" << endl;
        //cout << m_age_division << endl;
    }
 }


 Cellule::~Cellule()
{
    /* Rien � mettre ici car on ne fait pas d'allocation dynamique
    dans la classe Personnage. Le destructeur est donc inutile mais
    je le mets pour montrer � quoi cela ressemble.
    En temps normal, un destructeur fait souvent des delete et quelques
    autres v�rifications si n�cessaire avant la destruction de l'objet. */
}
