#ifndef ELFES_H
#define ELFES_H

#include "coterie.h"


class Elfes : public Coterie
{
public:
    Elfes();

    void GenererTraitCompatibles();
    QString GetNom();
    QString GetId();

    QString GetDescription();
    QString GetImage();

    virtual std::shared_ptr<Effet> AjouterEffetUniversite(
            GenHistoire* genHist, std::shared_ptr<Evt> evt, QString go_to_effet_suivant );
};

#endif // ELFES_H
