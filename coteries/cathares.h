#ifndef CATHARES_H
#define CATHARES_H

#include "coterie.h"


class Cathares : public Coterie
{
public:
    Cathares();

    void GenererTraitCompatibles();
    QString GetNom();
};

#endif // CATHARES_H
