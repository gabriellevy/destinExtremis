#include "elfes.h"
#include "genviehumain.h"

using std::make_shared;
using std::shared_ptr;

Elfes::Elfes()
{
    Initialisation();
}

void Elfes::GenererTraitCompatibles()
{
    m_TraitsCompatible = {
        make_shared<Trait>(eTrait::grand),
        make_shared<Trait>(eTrait::beau),
        make_shared<Trait>(eTrait::intelligent),
        make_shared<Trait>(eTrait::sensible),
        make_shared<Trait>(eTrait::habile),
        make_shared<Trait>(eTrait::artiste)
    };
    m_TraitsIncompatible = {
        make_shared<Trait>(eTrait::petit),
        make_shared<Trait>(eTrait::laid),
        make_shared<Trait>(eTrait::simple)
    };
}

QString Elfes::GetNom()
{
    return "Elfes";
}

QString Elfes::GetDescription()
{
    return "Les Elfes";
}

QString Elfes::GetImage()
{
    return ":/images/elfes/400px-Elfe.jpg";
}

std::shared_ptr<Effet> Elfes::AjouterEffetUniversite(GenHistoire* genHist)
{
    shared_ptr<Effet> effet = genHist->AjouterEffetNarration("youpi temp");

    return effet;
}
