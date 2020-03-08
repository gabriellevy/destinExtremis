#include "orks.h"
#include "genviehumain.h"
#include "../destinLib/aleatoire.h"

using std::make_shared;
using std::shared_ptr;

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
    return "Les orks sont des mutants qui embrassent avant tout une vie simple et brutale sans prise de tête.";
}

QString Orks::GetImage()
{
    return ":/images/orks/mekano.PNG";
}

std::shared_ptr<Effet> Orks::AjouterEffetUniversite(GenHistoire* genHist)
{
    shared_ptr<Effet> effet;
    int nb = Aleatoire::GetAl()->EntierInferieurA(5);

    switch (nb) {
    case 0 : {
        effet = genHist->AjouterEffetNarration("youpi temp Orks " + QString::number(nb));
        //effet->AjouterChangeurDeCarac() // bonne blessure (cicatrice) suite aux exercices à l'ork // attention mauvaise carac pour être elfe
    } break;
    case 1 : effet = genHist->AjouterEffetNarration("youpi temp Orks " + QString::number(nb)); break;
    case 2 : effet = genHist->AjouterEffetNarration("youpi temp Orks " + QString::number(nb)); break;
    case 3 : effet = genHist->AjouterEffetNarration("youpi temp Orks " + QString::number(nb)); break;
    case 4 : effet = genHist->AjouterEffetNarration("youpi temp Orks " + QString::number(nb)); break;
    }

    return effet;
}
