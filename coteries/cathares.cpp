#include "cathares.h"
#include "genviehumain.h"
#include "religion/religion.h"

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
    return "L'université Cathares où vous êtes accueilli est très éloignée du centre de la ville. "
            "Elle se trouve dans un endroit peu industrialisé et entouré d'arbres. L'université elle-même est un majestueux monastère de "
            "pierre mais de toute évidence très peu équipé niveau confort.";
}

QString Cathares::GetImage()
{
    return ":/images/cathares/moine.jpg";
}

std::shared_ptr<Effet> Cathares::AjouterEffetUniversite(GenHistoire* genHist, shared_ptr<Evt> evt, QString go_to_effet_suivant )
{
    QVector<shared_ptr<NoeudProbable>> noeudsProbaEducation;

    // formation religieuse
    shared_ptr<Effet> effet1 = genHist->AjouterEffetNarration(
                "Rien n'est plus important pour un cathare que la formation religieuse. Vous apssez des semaines à écouter les leçons et à suivre les exemples des purs.",
                ":/images/cathares/apprend_lit.jpg",
                "", evt);
    effet1->AjouterChangeurDeCarac(Religion::C_RELIGION, Religion::CHRETIEN);
    effet1->AjouterAjouteurACarac(Religion::C_FOI, "1");
    effet1->m_GoToEffetId = go_to_effet_suivant;
    shared_ptr<Condition> cond1 = make_shared<Condition>(1.0, TypeProba::p_Relative);
    shared_ptr<NoeudProbable> noeud1 = make_shared<NoeudProbable>(
                effet1,
                cond1);
    noeudsProbaEducation.push_back(noeud1);
    shared_ptr<Effet> effetSelecteur = genHist->m_GenerateurEvt->AjouterEffetSelecteurDEvt(
                noeudsProbaEducation);
    effetSelecteur->m_MsChrono = 1; // passé automatiquement

    return effetSelecteur;
}
