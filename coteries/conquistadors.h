#ifndef CONQUISTADORS_H
#define CONQUISTADORS_H

#include "coterie.h"

class Conquistadors : public Coterie
{
public:
    Conquistadors();

    void GenererTraitCompatibles();
    QString GetNom();
    QString GetId();

    QString GetDescription();
    QString GetImage();

    virtual std::shared_ptr<Effet> AjouterEffetUniversite(
            GenHistoire* genHist, std::shared_ptr<Evt> evt, QString go_to_effet_suivant );
};

#endif // CONQUISTADORS_H
