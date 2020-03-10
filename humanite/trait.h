#ifndef TRAIT_H
#define TRAIT_H

#include <QString>
#include <memory>

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
    simple, // pas forcément idiot mais a peu tendace à utiliser son intelligence de manière abstraite : plutôt terre à terre
    intellectuel, // intelligent à priori mais a surtout tendance à intellectualiser tout, à conceptualiser, à aimer l'abstrait et la discussion
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

    /**
     * @brief GetTrait
     * @param m_TraitsDejaPossedes listes de traits que le personnage possède déjà : permet d'éviter qu'il se retrouve avec des traits opposés entre eux comme 'Petit' et 'Grand'
     * @return
     */
    static std::shared_ptr<Trait> GetTrait(QVector<eTrait>& m_TraitsDejaPossedes);

    static eTrait GetTraitOppose(eTrait etrait);

    static QString GetNomTrait(eTrait etrait); // est aussi l'identifiant de la carac associée
};

#endif // TRAIT_H
