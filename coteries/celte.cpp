#include "celte.h"

using std::make_shared;

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
