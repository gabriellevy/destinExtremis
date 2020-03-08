#include "tyranides.h"
#include "genviehumain.h"

using std::make_shared;
using std::shared_ptr;

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

QString Tyranides::GetDescription()
{
    return "Les Tyranides";
}

QString Tyranides::GetImage()
{
    return ":/images/tyranides/The_hive_fleets_descend.jpg";
}

std::shared_ptr<Effet> Tyranides::AjouterEffetUniversite(GenHistoire* genHist)
{
    shared_ptr<Effet> effet = genHist->AjouterEffetNarration("youpi temp");

    return effet;
}
