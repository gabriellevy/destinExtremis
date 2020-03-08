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
};

#endif // CATHARES_H
