#include "celte.h"
#include "genviehumain.h"

using std::make_shared;
using std::shared_ptr;

Celte::Celte()
{
    Initialisation();
}

void Celte::GenererTraitCompatibles()
{
    m_TraitsCompatible = {
        make_shared<Trait>(eTrait::nature),
        make_shared<Trait>(eTrait::fort),
        make_shared<Trait>(eTrait::franc),
        make_shared<Trait>(eTrait::spirituel)
    };
    m_TraitsIncompatible = {
        make_shared<Trait>(eTrait::industrieux)
    };
}

QString Celte::GetNom()
{
    return "Celtes";
}

QString Celte::GetDescription()
{
    return "Les celtes";
}

QString Celte::GetImage()
{
    return ":/images/celtes/description.jpg";
}

std::shared_ptr<Effet> Celte::AjouterEffetUniversite(GenHistoire* genHist)
{
    shared_ptr<Effet> effet = genHist->AjouterEffetNarration("youpi temp");

    return effet;
}
