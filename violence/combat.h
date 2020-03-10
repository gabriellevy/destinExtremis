#ifndef COMBAT_H
#define COMBAT_H

#include <QString>
#include <QMap>
#include "generateurnoeudsprobables.h"

class GenEvt;
class Effet;
class Condition;


class Combat : public GenerateurNoeudsProbables
{
public:
    Combat(int indexEvt);

    // caracs liées :
    static QString C_CAP_COMBAT;
};

#endif // COMBAT_H
