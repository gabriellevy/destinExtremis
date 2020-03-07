#ifndef TRAIT_H
#define TRAIT_H

#include <QString>

/**
 * @brief ce qui a rapport aux traits descriptif d'un personnage
 * Tous ces traits sont binaires par souci d simplification et peuvent aussi bien être psychologiques que physiques
 */

enum eTrait : int {
    sens_du_groupe,
    sens_du_sacrifice,
    cupide,
    honneur,
    fort,
    spirituel,
    opportuniste,
    sournois,
    faible,
    nature,
    franc,
    industrieux,
    violent,
    resistant,
    pragmatique,
    simple,
    intellectuel,
    grand,
    beau,
    intelligent,
    artiste,
    sensible,
    habile,
    petit,
    laid,
    patriarcal,
    patriote,
    jouisseur,
    ambitieux,
    aventureux,
    altruiste,
    pacifiste,

    nb_Traits
};

class Trait
{
public:
    Trait(eTrait trait);

    QString GetNom();

    eTrait m_eTrait;
};

#endif // TRAIT_H
