#ifndef CHRISTIANISME_H
#define CHRISTIANISME_H

#include <QString>
#include <QMap>
#include "generateurnoeudsprobables.h"

class GenEvt;
class GenHistoire;
class Effet;
class Evt;
class Condition;

class Christianisme : public GenerateurNoeudsProbables
{
public:
    Christianisme(int indexEvt);

    // valeurs de Metier::C_TITRE :
        static QString EVEQUE;
};

#endif // CHRISTIANISME_H
