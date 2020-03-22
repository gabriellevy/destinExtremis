#ifndef CROISADEFRANQUE_H
#define CROISADEFRANQUE_H

#include "coterie.h"

class CroisadeFranque : public Coterie
{
public:
    CroisadeFranque();

    void GenererTraitCompatibles();
    QString GetNom();
    QString GetId();

    QString GetDescription();
    QString GetDescriptionUniversite();
    QString GetImage();

    virtual std::shared_ptr<Effet> AjouterEffetUniversite(
            GenHistoire* genHist, std::shared_ptr<Evt> evt, QString go_to_effet_suivant);
};

#endif // CROISADEFRANQUE_H
