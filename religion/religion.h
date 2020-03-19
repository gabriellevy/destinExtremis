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


class Religion : public GenerateurNoeudsProbables
{
public:
    Religion(int indexEvt);

    // caracs liées :
    static QString C_RELIGION; // représenté avec une image donc valeur de url
    static QString C_FOI; // niveau de foi dans sa religion (1 à 10)
    // valeurs de C_RELIGION "" = aucune
    static QString CHRETIEN;

    static std::shared_ptr<Condition> AjouterCondACetteReligion(QString religion);

};

#endif // RELIGION_H
