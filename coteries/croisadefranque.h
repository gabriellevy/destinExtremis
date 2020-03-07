#ifndef CROISADEFRANQUE_H
#define CROISADEFRANQUE_H

#include "coterie.h"

class CroisadeFranque : public Coterie
{
public:
    CroisadeFranque();

    void GenererTraitCompatibles();
    QString GetNom();
};

#endif // CROISADEFRANQUE_H
