#ifndef CELLULE_H_INCLUDED
#define CELLULE_H_INCLUDED

class Cellule
{
    // Tout ce qui suit est public (accessible depuis l'extérieur)
    public:

    // Constructeur
    Cellule(float v_taille_max, float v_taux);

    // Constructeur
    Cellule(float v_taille_max, float v_taux, float v_taille_init);

    // Destructeur
    ~Cellule();

    // méthode permettant de retrouver la taille initiale de la cellule
    float getTailleInitCellule();

    // méthode permettant de retrouver la taille actuelle de la cellule
    float getTailleActuCellule();

    // Agradir la cellule
    void agrradirCellule(float v_taux , float v_time);

    // méthode permettat de retrouver l'age actuel de la cellule
    float getAge();

    float getAgeDiv();

    // Tout ce qui suit est privé (inaccessible depuis l'extérieur)
    private:

    float m_age; // Age de la cellule en seconde
    float m_taille_init; // taille initiale de la cellule en métre (la taille moyenne d'une cellule varie entre 10^(-4) et 10^(-2) mètres)
    float m_taille_actu; // taille de la cellule à l'instant m_age
    float m_age_division; // Age après lequel la cellule se divise pour donner deux cellules filles
};

#endif // CELLULE_H_INCLUDED
