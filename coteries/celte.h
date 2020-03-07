#ifndef CELTE_H
#define CELTE_H

#include "coterie.h"


class Celte : public Coterie
{
public:
    Celte();

    void GenererTraitCompatibles();
    QString GetNom();
};

#endif // CELTE_H
