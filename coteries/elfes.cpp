#include "elfes.h"
#include "genviehumain.h"
#include "socio_eco/metier.h"

using std::make_shared;
using std::shared_ptr;

Elfes::Elfes()
{
    Initialisation();
}

void Elfes::GenererTraitCompatibles()
{
    m_TraitsCompatible = {
        make_shared<Trait>(eTrait::grand),
        make_shared<Trait>(eTrait::beau),
        make_shared<Trait>(eTrait::intelligent),
        make_shared<Trait>(eTrait::sensible),
        make_shared<Trait>(eTrait::habile),
        make_shared<Trait>(eTrait::artiste)
    };
    m_TraitsIncompatible = {
        make_shared<Trait>(eTrait::petit),
        make_shared<Trait>(eTrait::laid),
        make_shared<Trait>(eTrait::simple)
    };
}

QString Elfes::GetNom()
{
    return "Elfes";
}

QString Elfes::GetDescription()
{
    return "Description des Elfes";
}

QString Elfes::GetDescriptionUniversite()
{
    return "Les Elfes";
}

QString Elfes::GetImage()
{
    return ":/images/elfes/400px-Elfe.jpg";
}

QString Elfes::GetId()
{
    return Coterie::ELFES;
}

std::shared_ptr<Effet> Elfes::AjouterEffetUniversite(GenHistoire* genHist, shared_ptr<Evt> evt, QString go_to_effet_suivant )
{
    QVector<shared_ptr<NoeudProbable>> noeudsProbaEducation;

    {
        shared_ptr<Effet> effet2 = genHist->AjouterEffetNarration("youpi temp " + GetNom() + " 0.8", "", "", evt);
        effet2->m_GoToEffetId = go_to_effet_suivant;
        shared_ptr<Condition> cond = make_shared<Condition>(0.8, TypeProba::p_Relative);
        shared_ptr<NoeudProbable> noeud = make_shared<NoeudProbable>(
                    effet2,
                    cond);
        noeudsProbaEducation.push_back(noeud);
    }

    // effet devient artiste
    {
        shared_ptr<Effet> effet = genHist->AjouterEffetNarration(
                    "Tous les elfes doivent être artistes, sinon ils redeviennent lentement de simples humains. "
                    "L'université se doit de consacrer un grand nombre d'heures à rendre votre esprit ouvert à l'art et à la beauté.",
                    ":/images/elfes/musique_automne.jpg",
                    "", evt);
        effet->m_GoToEffetId = go_to_effet_suivant;
        effet->AjouterAjouteurACarac(Trait::GetNomTrait(artiste), "1");
        Trait::AjouterConditionSiAPasCeTrait(effet, artiste);

        shared_ptr<Condition> cond = make_shared<Condition>(0.3, TypeProba::p_Relative);// difficile d'ajouter une carac à un eprso (artiste à partir de rien...)
        shared_ptr<NoeudProbable> noeudCombat = make_shared<NoeudProbable>(
                    effet,
                    cond);
        noeudsProbaEducation.push_back(noeudCombat);
    }

    // effet devient Musicien
    {
        shared_ptr<Effet> effet = genHist->AjouterEffetNarration(
                    "Vu votre poentiel d'artiste les elfes trouvent indispensable de vous former à la musique, le plus noble de tous les arts.",
                    ":/images/elfes/elfe_musicien.jpg",
                    "", evt);
        effet->m_GoToEffetId = go_to_effet_suivant;
        effet->AjouterAjouteurACarac(Metier::MUSICIEN, "1");
        Trait::AjouterConditionSiACeTrait(effet, artiste);

        shared_ptr<Condition> cond = make_shared<Condition>(1.0, TypeProba::p_Relative);
        shared_ptr<NoeudProbable> noeudCombat = make_shared<NoeudProbable>(
                    effet,
                    cond);
        noeudsProbaEducation.push_back(noeudCombat);
    }


    shared_ptr<Effet> effetSelecteur = genHist->m_GenerateurEvt->AjouterEffetSelecteurDEvt(
                noeudsProbaEducation);
    effetSelecteur->m_MsChrono = 1; // passé automatiquement

    return effetSelecteur;
}
