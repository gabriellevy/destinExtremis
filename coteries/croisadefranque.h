#ifndef CROISADEFRANQUE_H
#define CROISADEFRANQUE_H

#include "coterie.h"

class CroisadeFranque : public Coterie
{
public:
    CroisadeFranque();

    void GenererTraitCompatibles();
    QString GetNom();

    QString GetDescription();
    QString GetImage();
    virtual std::shared_ptr<Effet> AjouterEffetUniversite(GenHistoire* genHist);
};

#endif // CROISADEFRANQUE_H
