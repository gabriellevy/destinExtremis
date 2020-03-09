#ifndef ORKS_H
#define ORKS_H

#include "coterie.h"

class Evt;

class Orks : public Coterie
{
public:
    Orks();

    void GenererTraitCompatibles();
    QString GetNom();

    QString GetDescription();
    QString GetImage();
    virtual std::shared_ptr<Effet> AjouterEffetUniversite(
            GenHistoire* genHist, std::shared_ptr<Evt> evt, QString go_to_effet_suivant);
};

#endif // ORKS_H
