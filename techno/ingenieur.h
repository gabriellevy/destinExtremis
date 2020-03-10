#ifndef INGENIEUR_H
#define INGENIEUR_H

#include <QString>
#include <QMap>
#include "generateurnoeudsprobables.h"

class GenEvt;
class Effet;
class Condition;


class Ingenieur : public GenerateurNoeudsProbables
{
public:
    Ingenieur(int indexEvt);

    // caracs liées :
    static QString C_MECANIQUE; // niveau en mécanique. 5 étant un bon mécanien, 10 un génie
};

#endif // INGENIEUR_H
