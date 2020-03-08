#ifndef CATHARES_H
#define CATHARES_H

#include "coterie.h"


class Cathares : public Coterie
{
public:
    Cathares();

    void GenererTraitCompatibles();
    QString GetNom();

    QString GetDescription();
    QString GetImage();
    virtual std::shared_ptr<Effet> AjouterEffetUniversite(GenHistoire* genHist);
};

#endif // CATHARES_H
