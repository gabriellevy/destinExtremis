#ifndef VEHICULE_H
#define VEHICULE_H

#include <QString>
#include <QMap>
#include "generateurnoeudsprobables.h"

class GenEvt;
class Effet;
class Condition;


class Vehicule : public GenerateurNoeudsProbables
{
public:
    Vehicule(int indexEvt);

    static QString C_CONDUITE_ROUTE; // capacité à conduire des voitures, motos.. (1 à 10)
    static QString C_CONDUITE_AVION; // capacité à conduire tout ce qui vole (1 à 10)

};

#endif // VEHICULE_H
