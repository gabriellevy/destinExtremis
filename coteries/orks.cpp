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

std::shared_ptr<Effet> Orks::AjouterEffetUniversite(GenHistoire* genHist, shared_ptr<Evt> evt, QString go_to_effet_suivant )
{
    QVector<shared_ptr<NoeudProbable>> noeudsProbaEducation;

    shared_ptr<Effet> effet1 = genHist->AjouterEffetNarration("youpi temp " + GetNom() + " 15", "", "", evt);
    effet1->m_GoToEffetId = go_to_effet_suivant;
    shared_ptr<Condition> cond1 = make_shared<Condition>(15, TypeProba::p_Relative);
    shared_ptr<NoeudProbable> noeud1 = make_shared<NoeudProbable>(
                effet1,
                cond1);
    noeudsProbaEducation.push_back(noeud1);

    shared_ptr<Effet> effet2 = genHist->AjouterEffetNarration("youpi temp " + GetNom() + " 0.8", "", "", evt);
    effet2->m_GoToEffetId = go_to_effet_suivant;
    shared_ptr<Condition> cond = make_shared<Condition>(0.8, TypeProba::p_Relative);
    shared_ptr<NoeudProbable> noeud = make_shared<NoeudProbable>(
                effet2,
                cond);
    noeudsProbaEducation.push_back(noeud);

    shared_ptr<Effet> effetSelecteur = genHist->m_GenerateurEvt->AjouterEffetSelecteurDEvt(
                noeudsProbaEducation);
    effetSelecteur->m_MsChrono = 1; // passé automatiquement

    return effetSelecteur;
}
