#ifndef BIONIQUE_H
#define BIONIQUE_H

#include <QString>
#include <QMap>
#include "generateurnoeudsprobables.h"

class GenEvt;
class Effet;
class Condition;


class Bionique : public GenerateurNoeudsProbables
{
public:
    Bionique(int indexEvt);

    static std::shared_ptr<Condition> AjouterConditionSiBioniqueLongeviteSuperieureA(int nbBionique);
    static std::shared_ptr<Condition> AjouterConditionSiBioniqueLongeviteInferieurA(int nbBionique);

    static QString C_BIONIQUE_LONGEVITE; // nombre de bioniques ajouté au corps pour augmenter la longévité
    static QString C_FABRICATION_BIONIQUE; // niveau en conception et fabrication de bionique (entre ingénieur et médecin)
};

#endif // BIONIQUE_H
