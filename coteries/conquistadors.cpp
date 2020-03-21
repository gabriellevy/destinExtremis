#include "conquistadors.h"
#include "genviehumain.h"
#include "religion/religion.h"
#include "violence/combat.h"
#include "socio_eco/metier.h"
#include "humanite/trait.h"

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
    {
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
    }

    // effetCombat
    {
        shared_ptr<Effet> effetCombat = genHist->AjouterEffetNarration(
                    "Seuls les grands guerriers peuvent espérer devenir des conquistadors et affronter les horreurs des terres désolées. "
                    "Votre formation contient bien sûr un entrainement avec de célbres maîtres d'armes.",
                    ":/images/conquistadors/soldat.jpg",
                    "", evt);
        effetCombat->m_GoToEffetId = go_to_effet_suivant;
        effetCombat->AjouterAjouteurACarac(Combat::C_CAP_COMBAT, "1"); // meilleur combattant
        shared_ptr<Condition> condCombat = make_shared<Condition>(1.0, TypeProba::p_Relative);
        shared_ptr<NoeudProbable> noeudCombat = make_shared<NoeudProbable>(
                    effetCombat,
                    condCombat);
        noeudsProbaEducation.push_back(noeudCombat);
    }

    // effetForgeron
    {
        shared_ptr<Effet> effetForgeron = genHist->AjouterEffetNarration(
                    "Les conquistadors sont des experts de la forge, leurs armures sont les meilleures du monde. "
                    "De plus il est indispensable qu'en expédition ils soient capables de réparer et entretenir leur matériel donc même les aventuriers se doivent d'avoir des rudiments techniques."
                    "\nVous êtes donc formé par un maître forgeron pour connaître les bases du métier.",
                    ":/images/conquistadors/forgeron.jpg",
                    "", evt);
        effetForgeron->m_GoToEffetId = go_to_effet_suivant;
        effetForgeron->AjouterAjouteurACarac(Metier::FORGERON, "1"); // meilleur forgeron
        shared_ptr<Condition> condCombat = make_shared<Condition>(1.0, TypeProba::p_Relative);
        shared_ptr<NoeudProbable> noeudCombat = make_shared<NoeudProbable>(
                    effetForgeron,
                    condCombat);
        noeudsProbaEducation.push_back(noeudCombat);
    }

    // effet Musicien
    {
        shared_ptr<Effet> effet = genHist->AjouterEffetNarration(
                    "Les conquistadors ne sont pas seulement des aventuriers, ce sont aussi des baladins itinérants qui divertissent les hôtes qui veulent bien les accueillir dans leurs nombreuses aventures. "
                    "Ainsi ils peuvent chanter leurs exploits mais aussi ceux de leurs ancêtres et de leur clan.",
                    ":/images/conquistadors/guitariste2.jpg",
                    "", evt);
        effet->m_GoToEffetId = go_to_effet_suivant;
        effet->AjouterAjouteurACarac(Metier::MUSICIEN, "1");
        shared_ptr<Condition> cond = make_shared<Condition>(0.3, TypeProba::p_Relative);

        Trait::AjouterModifProbaSiACeTrait(cond.get(), 1.5, artiste);
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

QString Conquistadors::GetId()
{
    return Coterie::CONQUISTADORS;
}

