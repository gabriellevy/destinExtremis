#include "croisadefranque.h"
#include "genviehumain.h"

using std::make_shared;
using std::shared_ptr;

CroisadeFranque::CroisadeFranque()
{
    GenererTraitCompatibles();
}

void CroisadeFranque::GenererTraitCompatibles()
{
    m_TraitsCompatible = {
        make_shared<Trait>(eTrait::honneur),
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
