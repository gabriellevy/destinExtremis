#ifndef TYRANIDES_H
#define TYRANIDES_H

#include "coterie.h"

class Tyranides : public Coterie
{
public:
    Tyranides();

    void GenererTraitCompatibles();
    QString GetNom();

    QString GetDescription();
    QString GetImage();
};

#endif // TYRANIDES_H
