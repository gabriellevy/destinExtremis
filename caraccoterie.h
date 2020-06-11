#ifndef CARACCOTERIE_H
#define CARACCOTERIE_H

#include "../destinLib/abs/carac.h"
#include <memory>

class Coterie;

class CaracCoterie : public Carac
{
    std::shared_ptr<Coterie> m_Coterie;
public:
    CaracCoterie();

    virtual bool AfficherImage(bool dansBox = false);
    virtual QString GetCaracDescription();
};

#endif // CARACCOTERIE_H
