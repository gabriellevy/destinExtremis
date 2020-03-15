#include "cathares.h"
#include "genviehumain.h"

using std::make_shared;
using std::shared_ptr;

Cathares::Cathares()
{
    GenererTraitCompatibles();
}

void Cathares::GenererTraitCompatibles()
{
    m_TraitsCompatible = {
        make_shared<Trait>(eTrait::altruiste),
        make_shared<Trait>(eTrait::sens_du_sacrifice),
        make_shared<Trait>(eTrait::sens_du_groupe),
        make_shared<Trait>(eTrait::pacifiste),
        make_shared<Trait>(eTrait::faible)
    };
    m_TraitsIncompatible = {
        make_shared<Trait>(eTrait::cupide),
        make_shared<Trait>(eTrait::industrieux),
        make_shared<Trait>(eTrait::ambitieux),
        make_shared<Trait>(eTrait::jouisseur)
    };
}

QString Cathares::GetNom()
{
    return "Cathares";
}

QString Cathares::GetDescription()
{
    return "L'es'université Cathares où vous êtes accueilli est très éloignée du centre de la ville. "
            "Elle se trouve dans un endroit peu industrialisé et entouré d'arbres. L'université elle-même est un monastére de "
            "pierre majestueux amis de toute évidence très peu équipé niveau confort.";
}

QString Cathares::GetImage()
{
    return ":/images/cathares/moine.jpg";
}

std::shared_ptr<Effet> Cathares::AjouterEffetUniversite(GenHistoire* genHist, shared_ptr<Evt> evt, QString go_to_effet_suivant )
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
