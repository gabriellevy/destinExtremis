#ifndef PROPAGANDE_H
#define PROPAGANDE_H

#include <QString>
#include <QMap>
#include "generateurnoeudsprobables.h"

class GenEvt;
class Effet;
class Condition;


class Propagande : public GenerateurNoeudsProbables
{
public:
    Propagande(int indexEvt);
};

#endif // PROPAGANDE_H
