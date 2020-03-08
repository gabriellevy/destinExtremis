#include "orks.h"

using std::make_shared;

Orks::Orks()
{
    Initialisation();
}

void Orks::GenererTraitCompatibles()
{
    m_TraitsCompatible = {
        make_shared<Trait>(eTrait::violent),
        make_shared<Trait>(eTrait::fort),
        make_shared<Trait>(eTrait::resistant),
        make_shared<Trait>(eTrait::pragmatique),
        make_shared<Trait>(eTrait::franc),
        make_shared<Trait>(eTrait::simple)
    };
    m_TraitsIncompatible = {
        make_shared<Trait>(eTrait::intellectuel),
        make_shared<Trait>(eTrait::faible)
    };
}

QString Orks::GetNom()
{
    return "Orks";
}

QString Orks::GetDescription()
{
    return "Les Orks";
}

QString Orks::GetImage()
{
    return ":/images/orks/mekano.PNG";
}
