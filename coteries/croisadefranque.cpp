#include "croisadefranque.h"
#include "genviehumain.h"
#include "religion/religion.h"
#include "violence/combat.h"

using std::make_shared;
using std::shared_ptr;

CroisadeFranque::CroisadeFranque()
{
    GenererTraitCompatibles();
}

void CroisadeFranque::GenererTraitCompatibles()
{
    m_TraitsCompatible = {
        make_shared<Trait>(eTrait::honorable),
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

float CroisadeFranque::GetPoidsDemo()
{
    return 1.0;
}

QString CroisadeFranque::GetDescription()
{
    return "Description des Croisés";
}

QString CroisadeFranque::GetDescriptionUniversite()
{
    return "Les croisés";
}

QString CroisadeFranque::GetImage()
{
    return ":/images/croisade_franque/Chevaliers_premières_croisades.jpg";
}

std::shared_ptr<Effet> CroisadeFranque::AjouterEffetUniversite(GenHistoire* genHist, shared_ptr<Evt> evt, QString go_to_effet_suivant )
{
    QVector<shared_ptr<NoeudProbable>> noeudsProbaEducation;

    // formation religieuse
    {
        shared_ptr<Effet> effet1 = genHist->AjouterEffetNarration(
                    "Un croisé se doit d'être un fervent chrétien dévoué à la guerre sainte. "
                    "\nVous passez des jours entiers à prier dans la dévotion des images saintes à suivre les cours de catéchisme des franciscains.",
                    ":/images/croisade_franque/priant.jpg",
                    "", evt);
        Religion::ModifierEffetEnEffetConversion(effet1, Religion::CHRETIEN);
        effet1->m_GoToEffetId = go_to_effet_suivant;
        shared_ptr<Condition> cond1 = make_shared<Condition>(1.0, TypeProba::p_Relative);
        shared_ptr<NoeudProbable> noeud1 = make_shared<NoeudProbable>(
                    effet1,
                    cond1);
        noeudsProbaEducation.push_back(noeud1);
    }

    // effetCombat
    {
        shared_ptr<Effet> effet = genHist->AjouterEffetNarration(
                    "On ne peut devenir croisé qu'une fois qu'on maîtrise le système de combat ancestral du croisé franc. "
                    "De plus, comme l'essentiel des querelles sont réglés par un duel sous le jugement de Dieu il est indispensable de savoir se défendre pour se faire respecter dans les quartiers de la croisade."
                    "\nVotre formation contient bien sûr un entrainement avec de célbres maîtres d'armes.",
                    ":/images/croisade_franque/duel_chevalier.jpg",
                    "", evt);
        effet->m_GoToEffetId = go_to_effet_suivant;
        effet->AjouterAjouteurACarac(Combat::C_CAP_COMBAT, "1"); // meilleur combattant
        shared_ptr<Condition> condCombat = make_shared<Condition>(1.0, TypeProba::p_Relative);
        shared_ptr<NoeudProbable> noeudCombat = make_shared<NoeudProbable>(
                    effet,
                    condCombat);
        noeudsProbaEducation.push_back(noeudCombat);
    }

    shared_ptr<Effet> effetSelecteur = genHist->m_GenerateurEvt->AjouterEffetSelecteurDEvt(
                noeudsProbaEducation);
    effetSelecteur->m_MsChrono = 1; // passé automatiquement

    return effetSelecteur;
}

QString CroisadeFranque::GetId()
{
    return Coterie::CROISADE;
}
