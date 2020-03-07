#include "tyranides.h"

using std::make_shared;

Tyranides::Tyranides()
{
    Initialisation();
}

void Tyranides::GenererTraitCompatibles()
{
    m_TraitsCompatible = {
        make_shared<Trait>(eTrait::sens_du_groupe),
        make_shared<Trait>(eTrait::sournois),
        make_shared<Trait>(eTrait::sens_du_sacrifice)
    };
    m_TraitsIncompatible = {
        make_shared<Trait>(eTrait::franc),
        make_shared<Trait>(eTrait::cupide)
    };
}

QString Tyranides::GetNom()
{
    return "Tyranides";
}
