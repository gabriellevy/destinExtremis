#ifndef EDUCATION_H
#define EDUCATION_H

#include <QString>
#include <QMap>
#include "generateurnoeudsprobables.h"

class GenEvt;
class Effet;
class Condition;


class Education : public GenerateurNoeudsProbables
{
public:
    Education(int indexEvt);
};

#endif // EDUCATION_H
