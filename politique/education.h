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
};

#endif // EDUCATION_H
