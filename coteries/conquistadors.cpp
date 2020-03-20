#include "conquistadors.h"
#include "genviehumain.h"
#include "religion/religion.h"

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

    // formation religieuse
    shared_ptr<Effet> effet1 = genHist->AjouterEffetNarration(
                "Un conquistador se doit d'être un fervent catholique confiant dans le destin que Dieu trace devant lui et qui le mènera à la gloire et la richesse. "
                "\nVous passez des jours entiers à prier dans la dévotion des images saintes à suivre les cours de catéchisme des prêtres catholiques.",
                ":/images/conquistadors/priant.jpg",
                "", evt);
    Religion::ModifierEffetEnEffetConversion(effet1, Religion::CHRETIEN);
    effet1->m_GoToEffetId = go_to_effet_suivant;
    shared_ptr<Condition> cond1 = make_shared<Condition>(0.6, TypeProba::p_Relative);// la religion n'est pas le plus important pour les conquistadors
    shared_ptr<NoeudProbable> noeud1 = make_shared<NoeudProbable>(
                effet1,
                cond1);
    noeudsProbaEducation.push_back(noeud1);

    // effetVide
    shared_ptr<Effet> effetVide = genHist->AjouterEffetNarration(
                "effetVide temp conqui.",
                ":/images/conquistadors/priant.jpg",
                "", evt);
    effet1->m_GoToEffetId = go_to_effet_suivant;
    shared_ptr<Condition> condVide = make_shared<Condition>(1.0, TypeProba::p_Relative);
    shared_ptr<NoeudProbable> noeudVide = make_shared<NoeudProbable>(
                effetVide,
                condVide);
    noeudsProbaEducation.push_back(noeudVide);

    shared_ptr<Effet> effetSelecteur = genHist->m_GenerateurEvt->AjouterEffetSelecteurDEvt(
                noeudsProbaEducation);
    effetSelecteur->m_MsChrono = 1; // passé automatiquement

    return effetSelecteur;
}

