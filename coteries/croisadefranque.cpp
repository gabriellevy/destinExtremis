#include "croisadefranque.h"

using std::make_shared;

CroisadeFranque::CroisadeFranque()
{
    GenererTraitCompatibles();
}

void CroisadeFranque::GenererTraitCompatibles()
{
    m_TraitsCompatible = {
        make_shared<Trait>(eTrait::honneur),
        make_shared<Trait>(eTrait::fort),
        make_shared<Trait>(eTrait::sens_du_sacrifice),
        make_shared<Trait>(eTrait::spirituel)
    };
    m_TraitsIncompatible = {
        make_shared<Trait>(eTrait::opportuniste),
        make_shared<Trait>(eTrait::sournois),
        make_shared<Trait>(eTrait::faible)
    };
}

QString CroisadeFranque::GetNom()
{
    return "Croisade franque";
}

QString CroisadeFranque::GetDescription()
{
    return "Les croisés";
}

QString CroisadeFranque::GetImage()
{
    return ":/images/croisade_franque/Chevaliers_premières_croisades.jpg";
}
