#ifndef ORKS_H
#define ORKS_H

#include "coterie.h"


class Orks : public Coterie
{
public:
    Orks();

    void GenererTraitCompatibles();
    QString GetNom();
};

#endif // ORKS_H
