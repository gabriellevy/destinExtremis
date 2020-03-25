#include "celte.h"
#include "genviehumain.h"
#include "socio_eco/metier.h"

using std::make_shared;
using std::shared_ptr;

Celte::Celte()
{
    Initialisation();
}

void Celte::GenererTraitCompatibles()
{
    m_TraitsCompatible = {
        make_shared<Trait>(eTrait::nature),
        make_shared<Trait>(eTrait::fort),
        make_shared<Trait>(eTrait::franc),
        make_shared<Trait>(eTrait::spirituel)
    };
    m_TraitsIncompatible = {
        make_shared<Trait>(eTrait::industrieux)
    };
}

QString Celte::GetDescription()
{
    return "Description des celtes";
}

QString Celte::GetNom()
{
    return "Celtes";
}

QString Celte::GetDescriptionUniversite()
{
    return "Les celtes";
}

QString Celte::GetImage()
{
    return ":/images/celtes/description.jpg";
}

float Celte::GetPoidsDemo()
{
    return 1.3;
}

QString Celte::GetId()
{
    return Coterie::CELTES;
}

std::shared_ptr<Effet> Celte::AjouterEffetUniversite(GenHistoire* genHist, shared_ptr<Evt> evt, QString go_to_effet_suivant )
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

    // effet devient Alchimiste
    {
        shared_ptr<Effet> effet = genHist->AjouterEffetNarration(
                    "La fabrication de potions, de filtres, de pommades est une composante essentielle de la science des druides celtes. "
                    "Leurs usages sont innombrables et vont de potions de soins aux champignons rendant les guerriers insensibles à la peur et la douleur. "
                    "Un druide détecte un certain potentiel chez vous et décide de vous apprendre les bases.",
                    ":/images/elfes/alchimiste.jpg",
                    "", evt);
        effet->m_GoToEffetId = go_to_effet_suivant;
        effet->AjouterAjouteurACarac(Metier::ALCHIMISTE, "1");
        Trait::AjouterConditionSiAPasCeTrait(effet, bete);

        shared_ptr<Condition> cond = make_shared<Condition>(0.7, TypeProba::p_Relative);
        shared_ptr<NoeudProbable> noeud = make_shared<NoeudProbable>(
                    effet,
                    cond);
        noeudsProbaEducation.push_back(noeud);
    }

    shared_ptr<Effet> effetSelecteur = genHist->m_GenerateurEvt->AjouterEffetSelecteurDEvt(
                noeudsProbaEducation);
    effetSelecteur->m_MsChrono = 1; // passé automatiquement

    return effetSelecteur;
}
