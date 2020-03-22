#ifndef CATHARES_H
#define CATHARES_H

#include "coterie.h"


class Cathares : public Coterie
{
public:
    Cathares();

    void GenererTraitCompatibles();
    QString GetNom();
    QString GetId();

    QString GetDescription();
    QString GetDescriptionUniversite();
    QString GetImage();
    virtual std::shared_ptr<Effet> AjouterEffetUniversite(
            GenHistoire* genHist, std::shared_ptr<Evt> evt, QString go_to_effet_suivant );
};

#endif // CATHARES_H
