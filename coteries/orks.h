#ifndef ORKS_H
#define ORKS_H

#include "coterie.h"


class Orks : public Coterie
{
public:
    Orks();

    void GenererTraitCompatibles();
    QString GetNom();

    QString GetDescription();
    QString GetImage();
    virtual std::shared_ptr<Effet> AjouterEffetUniversite(GenHistoire* genHist);
};

#endif // ORKS_H
