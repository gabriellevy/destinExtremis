#include "conquistadors.h"
#include "genviehumain.h"

using std::make_shared;
using std::shared_ptr;

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
    return "Conquistadors";
}

QString Conquistadors::GetDescription()
{
    return "Les Conquistadors";
}

QString Conquistadors::GetImage()
{
    return ":/images/conquistadors/soldats.jpg";
}

std::shared_ptr<Effet> Conquistadors::AjouterEffetUniversite(GenHistoire* genHist)
{
    shared_ptr<Effet> effet = genHist->AjouterEffetNarration("youpi temp");

    return effet;
}

