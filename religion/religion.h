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
    static QString C_MIRACLE; // capacité à créer des miracles (1 à 10)
    // valeurs de C_RELIGION "" = aucune
    static QString CHRETIEN;
    static QString ATHEE; // différent de "" car l'athée a développé une aversion à la religion, il sera dur à reconvertir

    static QString GetNomReligion(QString religion);
    static std::shared_ptr<Condition> AjouterCondACetteReligion(QString religion);

    static void ModifierEffetEnEffetConversion(std::shared_ptr<Effet> &effet, QString religion, int ajoutEnFoi = 1, bool convertitAthees = false);

};

#endif // RELIGION_H
