#include "conquistadors.h"

using std::make_shared;

Conquistadors::Conquistadors()
{
    Initialisation();
}

void Conquistadors::GenererTraitCompatibles()
{
    m_TraitsCompatible = {
    make_shared<Trait>(eTrait::ambitieux),
    make_shared<Trait>(eTrait::aventureux),
    make_shared<Trait>(eTrait::fort),
    make_shared<Trait>(eTrait::spirituel),
    make_shared<Trait>(eTrait::opportuniste),
    make_shared<Trait>(eTrait::cupide)
    };
    m_TraitsIncompatible = {
    make_shared<Trait>(eTrait::altruiste),
    make_shared<Trait>(eTrait::faible),
    make_shared<Trait>(eTrait::pacifiste)
    };
}

QString Conquistadors::GetNom()
{
    return "Croisade franque";
}

