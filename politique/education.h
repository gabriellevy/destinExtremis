#ifndef EDUCATION_H
#define EDUCATION_H

#include <QString>
#include <QMap>
#include "generateurnoeudsprobables.h"

class GenEvt;
class GenHistoire;
class Effet;
class Evt;
class Condition;


class Education : public GenerateurNoeudsProbables
{
public:
    Education(int indexEvt);

    static std::shared_ptr<Evt> GenererEvtEducationPolitique(GenHistoire* genHistoire);

    // nombre de coteries par elsquelles doit passer le personnage pour son éducation
    const static int NB_COTERIES_EDUCATION = 3;
    const static int NB_EFFETS_EDUCATION = 3; // par université de coterie
};

#endif // EDUCATION_H
