#ifndef RELIGION_H
#define RELIGION_H

#include <QString>
#include <QMap>
#include "generateurnoeudsprobables.h"

class GenEvt;
class GenHistoire;
class Effet;
class Evt;
class Condition;


class Famille : public GenerateurNoeudsProbables
{
public:
    Famille(int indexEvt);

    // préfixes liés (à associer aux caracs persos de la class PNJ)
    static QString PRE_PERE;
    static QString PRE_MERE;
    // TODO frère/soeurs, femme, enfants...

    // caracs liées :


    static void GenererParents(std::shared_ptr<Effet> effetNarrationVide);

};

#endif // RELIGION_H
