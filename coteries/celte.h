#ifndef CELTE_H
#define CELTE_H

#include "coterie.h"


class Celte : public Coterie
{
public:
    Celte();

    void GenererTraitCompatibles();
    QString GetNom();

    QString GetDescription();
    QString GetImage();
    virtual std::shared_ptr<Effet> AjouterEffetUniversite(
            GenHistoire* genHist, std::shared_ptr<Evt> evt, QString go_to_effet_suivant );
};

#endif // CELTE_H
