#ifndef ELFES_H
#define ELFES_H

#include "coterie.h"


class Elfes : public Coterie
{
public:
    Elfes();

    void GenererTraitCompatibles();
    QString GetNom();

    QString GetDescription();
    QString GetImage();
    virtual std::shared_ptr<Effet> AjouterEffetUniversite(GenHistoire* genHist);
};

#endif // ELFES_H
