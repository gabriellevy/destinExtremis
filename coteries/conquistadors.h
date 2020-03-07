#ifndef CONQUISTADORS_H
#define CONQUISTADORS_H

#include "coterie.h"

class Conquistadors : public Coterie
{
public:
    Conquistadors();

    void GenererTraitCompatibles();
    QString GetNom();
};

#endif // CONQUISTADORS_H
