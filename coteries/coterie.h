#ifndef COTERIE_H
#define COTERIE_H

#include <QVector>
#include "humanite/trait.h"
#include <memory>

class Coterie
{
protected:
    QVector<std::shared_ptr<Trait>> m_TraitsCompatible = {};
    QVector<std::shared_ptr<Trait>> m_TraitsIncompatible = {};
public:
    Coterie();
    virtual ~Coterie() {}

    void Initialisation();

    virtual void GenererTraitCompatibles() = 0;
    virtual QString GetNom() = 0;
};

#endif // COTERIE_H
