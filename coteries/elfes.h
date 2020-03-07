#ifndef ELFES_H
#define ELFES_H

#include "coterie.h"


class Elfes : public Coterie
{
public:
    Elfes();

    void GenererTraitCompatibles();
    QString GetNom();
};

#endif // ELFES_H
