#ifndef CONQUISTADORS_H
#define CONQUISTADORS_H

#include "coterie.h"

class Conquistadors : public Coterie
{
public:
    Conquistadors();

    void GenererTraitCompatibles();
    QString GetNom();

    QString GetDescription();
    QString GetImage();
    virtual std::shared_ptr<Effet> AjouterEffetUniversite(GenHistoire* genHist);
};

#endif // CONQUISTADORS_H
