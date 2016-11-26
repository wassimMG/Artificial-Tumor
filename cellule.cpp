#include <iostream>
#include "cellule.h"
#include <stdlib.h>
#include <ctime>
#include <math.h>
#include "SimpleRNG.h"

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

    /***************************************************
     1-------------------------------------------------
     Initialiser l'age de la cellule � z�ro
     ***************************************************/
     m_age = 0;

    /***************************************************
    2-------------------------------------------------
    Initialiser la taille de la cellule : valeure al�atoire
    ***************************************************/
    SimpleRNG var1 = SimpleRNG();
    int ecart_type = time(NULL) % 10; // l'�cart type re�oit une valeur semi-al�atoire en fonction du temps du syst�me entre 0 et 99
    int moyenne = 50; // la moyenne qui va �tre utlis�e dans la loi normale
    float var_normal = round(var1.GetNormal(moyenne,ecart_type));

    while ((var_normal < 1) && (var_normal >99))
    {
        var_normal = round(var1.GetNormal(moyenne,ecart_type)); // g�n�rer un nombre al�atoire selon la loi normale de moyenne 50 et d'�cart type �gal � une valeur al�atoire entre 1 et 10
    }
    m_taille_init = var_normal * 0.0000001; // La taille initiale de la cellule est une valeur al�atoire entre 1.10^(-6) et 99.10^(-6) en m�tre


    /***************************************************
    3-------------------------------------------------
    La taille actuelle de la cellule est �gale �
    la taille initiale au moment de cr�ation
    ***************************************************/
    m_taille_actu = m_taille_init; //

    /***************************************************
    4-------------------------------------------------
    Calculer l'age de division de la cellule
    En fonction de la taille initiale de la cellule
    Et tenant compte la taille maximum qu'une cellule
    peut atteindre avant de se diviser par mitose
    Dans ce calcul le r�sultat sera arrondi au dixi�me
    afin de pouvoir utiliser apr�s la valeur
    ***************************************************/
    if (m_taille_init!=0)
    {
        /** calcul de la valeure r�elle de l'age de la cellule apr�s lequel elle va se diviser */
        float age_div_reel = v_taux*log(v_taille_max/m_taille_init);
       // cout << age_div_reel << endl;
       /** valeur finale arrondie au dixi�me pr�s */
        m_age_division = round(age_div_reel*10)/10;
    }
 }


 Cellule::Cellule(float v_taille_max, float v_taux, float v_taille_init_soeur)
 {
    /***************************************************
     1-------------------------------------------------
     Initialiser l'age de la cellule � z�ro
     ***************************************************/
     m_age = 0;


    /***************************************************
    2-------------------------------------------------
    Initialiser la taille de la cellule
    ***************************************************/
    m_taille_init = v_taille_max - v_taille_init_soeur;


    /***************************************************
    3-------------------------------------------------
    La taille actuelle de la cellule est �gale �
    la taille initiale au moment de cr�ation
    ***************************************************/
    m_taille_actu = m_taille_init; // au moment de cr�ation de la cellule la taille actuelle est �gale � la taille initiale

    /***************************************************
    4-------------------------------------------------
    Calculer l'age de division de la cellule
    En fonction de la taille initiale de la cellule
    Et tenant compte la taille maximum qu'une cellule
    peut atteindre avant de se diviser par mitose
    Dans ce calcul le r�sultat sera arrondi au dixi�me
    afin de pouvoir utiliser apr�s la valeur
    ***************************************************/
    if (m_taille_init!=0)
    {
        /** calcul de la valeure r�elle de l'age de la cellule apr�s lequel elle va se diviser */
        float age_div_reel = v_taux*log(v_taille_max/m_taille_init);
        //cout << age_div_reel << endl;
       /** valeur finale arrondie au dixi�me pr�s */
        m_age_division = round(age_div_reel*10)/10;
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
