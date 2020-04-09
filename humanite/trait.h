#ifndef TRAIT_H
#define TRAIT_H

#include <QString>
#include <memory>

class Condition;
class Effet;

/**
 * @brief ce qui a rapport aux traits descriptif d'un personnage
 * Tous ces traits sont binaires par souci d simplification et peuvent aussi bien être psychologiques que physiques
 * ces traits doivent pouvoir être acquis très jeune et de préférence dès la petite enfance.
 * On écarte de préférence ceux qui sont des acquisistion tardives
 */

enum eTrait : int {
    // psychologique
    cupide,
    honorable, // prends très au sérieux sa réputation, ne ment jamais, respecte ses pairs et sa famille...
    opportuniste,
    menteur,
    sournois,
    franc,
    industrieux,
    violent,
    pragmatique,
    simple, // pas forcément idiot mais a peu tendace à utiliser son intelligence de manière abstraite : plutôt terre à terre
    intellectuel, // intelligent à priori mais a surtout tendance à intellectualiser tout, à conceptualiser, à aimer l'abstrait et la discussion
    intelligent,
    bete,
    sensible,
    jouisseur,
    ambitieux,
    aventureux,
    travailleur,
    paresseux,
    altruiste,
    cruel,
    rancunier,
    angoisse, // angoissé, stressé, pas bien dans sa peau

    // psychologique acquis plus idéologique => PeutEtrePrisALaNaissance renvoie false
    pervers_sexuel,
    sens_du_groupe,
    sens_du_sacrifice,
    patriarcal,
    patriote,
    pacifiste,

    // capacités physiques
    fort,
    faible,
    resistant,
    chetif,
    grand,
    beau,
    habile,
    maladroit,
    petit,
    laid,
    observateur,
    charmeur, // bon abord, bonne voie, charisme

    // tendances de l'âme
    spirituel,
    nature, // lié à la nature, aux animaux
    artiste,

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
    static std::shared_ptr<Trait> GetTrait(QVector<eTrait>& m_TraitsDejaPossedes, bool traitDeNaissance);

    static eTrait GetTraitOppose(eTrait etrait);

    static QString GetNomTrait(eTrait etrait); // est aussi l'identifiant de la carac associée
    static void AjouterModifProbaSiACeTrait(Condition* CondProba, double proba, eTrait trait);
    static void AjouterConditionSiACeTrait(std::shared_ptr<Effet> effet, eTrait trait);
    static void AjouterConditionSiAPasCeTrait(std::shared_ptr<Effet> effet, eTrait trait);

    bool PeutEtrePrisALaNaissance(); // renvoit faux si ce trait peut seulement être acquis plutôt tard dans la vie
};

#endif // TRAIT_H
