#ifndef PNJ_H
#define PNJ_H

#include <memory>
#include <QString>

class Coterie;
class Humain;

enum Sexe {
    es_Masculin,
    es_Feminin,
    es_Aleatoire
};

/**
 * @brief Les PNJ sont des personnages liés au joueur qui ont plusieurs caractéristiques associées
 * Pour les stocker on crée une série de caractéristiques qui ont toutes un préfixe
 * Exemple pour stocker le père de joueur :
 * préfixe : Père_
 * caracs : Père_Age, Père_Nom, Père_Coterie...
 */
class PNJ
{
public:
    PNJ(QString prefixe):m_Prefixe(prefixe){}

    QString m_Prefixe; // = plus ou moins l'identifiant du perso. Recommandé de le terminer par '_'

    std::shared_ptr<Coterie> m_Coterie;
    QString m_Nom;
    bool m_SexeMasculin;

    // CARAC associées aux valeurs de pnj
    static QString C_NOM;
    static QString C_SEXE;
    static QString C_COTERIE;

    /**
     * @brief génère un perso aléatoire sauf pour les param fournis
     * @param sexeMasculin
     * @param coterie
     * @return
     */
    static std::shared_ptr<PNJ> GenererPersoAleatoire(
            QString prefixe, Sexe sexe = es_Aleatoire, std::shared_ptr<Coterie> coterie = nullptr);

    // enregistrer/charger des objets complexes est en fait charger de nombreuses caracs d'un coup
    // les caracs suivantes ont pour but de simplifier le code de ce type
    static std::shared_ptr<PNJ> ChargerPNJ(QString Prefixe, Humain* hum);
    void SauverPNJ(QString Prefixe, Humain* hum);
};

#endif // PNJ_H
