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
    return "Description des Tyranides";
}

QString Tyranides::GetDescriptionUniversite()
{
    return "Les Tyranides";
}

QString Tyranides::GetImage()
{
    return ":/images/tyranides/The_hive_fleets_descend.jpg";
}

QString Tyranides::GetId()
{
    return Coterie::TYRANIDES;
}

std::shared_ptr<Effet> Tyranides::AjouterEffetUniversite(GenHistoire* genHist, shared_ptr<Evt> evt, QString go_to_effet_suivant )
{
    QVector<shared_ptr<NoeudProbable>> noeudsProbaEducation;

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
