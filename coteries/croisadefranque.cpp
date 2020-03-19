#include "croisadefranque.h"
#include "genviehumain.h"
#include "religion/religion.h"

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

QString CroisadeFranque::GetDescription()
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
    shared_ptr<Effet> effet1 = genHist->AjouterEffetNarration(
                "Un croisé se doit d'être un fervent chértien dévoué à la guerre sainte. "
                "\nVous passez des jours entiers à prier dans la dévotion des images saintes à suivre les cours de catéchisme des franciscains.",
                ":/images/croisade_franque/priant.jpg",
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
