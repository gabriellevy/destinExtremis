#include "cathares.h"

using std::make_shared;

Cathares::Cathares()
{
    GenererTraitCompatibles();
}

void Cathares::GenererTraitCompatibles()
{
    m_TraitsCompatible = {
        make_shared<Trait>(eTrait::altruiste),
        make_shared<Trait>(eTrait::sens_du_sacrifice),
        make_shared<Trait>(eTrait::sens_du_groupe),
        make_shared<Trait>(eTrait::pacifiste),
        make_shared<Trait>(eTrait::faible)
    };
    m_TraitsIncompatible = {
        make_shared<Trait>(eTrait::cupide),
        make_shared<Trait>(eTrait::industrieux),
        make_shared<Trait>(eTrait::ambitieux),
        make_shared<Trait>(eTrait::jouisseur)
    };
}

QString Cathares::GetNom()
{
    return "Cathares";
}
