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

std::shared_ptr<Effet> Conquistadors::AjouterEffetUniversite(GenHistoire* genHist, shared_ptr<Evt> evt, QString go_to_effet_suivant )
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

