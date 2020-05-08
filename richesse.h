#ifndef RICHESSE_H
#define RICHESSE_H

#include "../destinLib/abs/carac.h"


class Richesse : public Carac
{
public:
    Richesse();

    virtual bool AfficherValeur();

    static QString RICHESSE;
};

#endif // RICHESSE_H
