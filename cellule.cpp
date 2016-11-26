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
     Initialiser l'age de la cellule à zéro
     ***************************************************/
     m_age = 0;

    /***************************************************
    2-------------------------------------------------
    Initialiser la taille de la cellule : valeure aléatoire
    ***************************************************/
    SimpleRNG var1 = SimpleRNG();
    int ecart_type = time(NULL) % 10; // l'écart type reçoit une valeur semi-aléatoire en fonction du temps du système entre 0 et 99
    int moyenne = 50; // la moyenne qui va être utlisée dans la loi normale
    float var_normal = round(var1.GetNormal(moyenne,ecart_type));

    while ((var_normal < 1) && (var_normal >99))
    {
        var_normal = round(var1.GetNormal(moyenne,ecart_type)); // générer un nombre aléatoire selon la loi normale de moyenne 50 et d'écart type égal à une valeur aléatoire entre 1 et 10
    }
    m_taille_init = var_normal * 0.0000001; // La taille initiale de la cellule est une valeur aléatoire entre 1.10^(-6) et 99.10^(-6) en mètre


    /***************************************************
    3-------------------------------------------------
    La taille actuelle de la cellule est égale à
    la taille initiale au moment de création
    ***************************************************/
    m_taille_actu = m_taille_init; //

    /***************************************************
    4-------------------------------------------------
    Calculer l'age de division de la cellule
    En fonction de la taille initiale de la cellule
    Et tenant compte la taille maximum qu'une cellule
    peut atteindre avant de se diviser par mitose
    Dans ce calcul le résultat sera arrondi au dixième
    afin de pouvoir utiliser après la valeur
    ***************************************************/
    if (m_taille_init!=0)
    {
        /** calcul de la valeure réelle de l'age de la cellule après lequel elle va se diviser */
        float age_div_reel = v_taux*log(v_taille_max/m_taille_init);
       // cout << age_div_reel << endl;
       /** valeur finale arrondie au dixième près */
        m_age_division = round(age_div_reel*10)/10;
    }
 }


 Cellule::Cellule(float v_taille_max, float v_taux, float v_taille_init_soeur)
 {
    /***************************************************
     1-------------------------------------------------
     Initialiser l'age de la cellule à zéro
     ***************************************************/
     m_age = 0;


    /***************************************************
    2-------------------------------------------------
    Initialiser la taille de la cellule
    ***************************************************/
    m_taille_init = v_taille_max - v_taille_init_soeur;


    /***************************************************
    3-------------------------------------------------
    La taille actuelle de la cellule est égale à
    la taille initiale au moment de création
    ***************************************************/
    m_taille_actu = m_taille_init; // au moment de création de la cellule la taille actuelle est égale à la taille initiale

    /***************************************************
    4-------------------------------------------------
    Calculer l'age de division de la cellule
    En fonction de la taille initiale de la cellule
    Et tenant compte la taille maximum qu'une cellule
    peut atteindre avant de se diviser par mitose
    Dans ce calcul le résultat sera arrondi au dixième
    afin de pouvoir utiliser après la valeur
    ***************************************************/
    if (m_taille_init!=0)
    {
        /** calcul de la valeure réelle de l'age de la cellule après lequel elle va se diviser */
        float age_div_reel = v_taux*log(v_taille_max/m_taille_init);
        //cout << age_div_reel << endl;
       /** valeur finale arrondie au dixième près */
        m_age_division = round(age_div_reel*10)/10;
    }
 }


 Cellule::~Cellule()
{
    /* Rien à mettre ici car on ne fait pas d'allocation dynamique
    dans la classe Personnage. Le destructeur est donc inutile mais
    je le mets pour montrer à quoi cela ressemble.
    En temps normal, un destructeur fait souvent des delete et quelques
    autres vérifications si nécessaire avant la destruction de l'objet. */
}
