#include "orks.h"
#include "genviehumain.h"
#include "../destinLib/aleatoire.h"
#include "humanite/pbsante.h"
#include "violence/combat.h"
#include "techno/ingenieur.h"

using std::make_shared;
using std::shared_ptr;

Orks::Orks()
{
    Initialisation();
}

void Orks::GenererTraitCompatibles()
{
    m_TraitsCompatible = {
        make_shared<Trait>(eTrait::violent),
        make_shared<Trait>(eTrait::fort),
        make_shared<Trait>(eTrait::resistant),
        make_shared<Trait>(eTrait::pragmatique),
        make_shared<Trait>(eTrait::franc),
        make_shared<Trait>(eTrait::angoisse),
        make_shared<Trait>(eTrait::paresseux),
        make_shared<Trait>(eTrait::faible),
        make_shared<Trait>(eTrait::simple)
    };
    m_TraitsIncompatible = {
        make_shared<Trait>(eTrait::ambitieux),
        make_shared<Trait>(eTrait::intellectuel)
    };
}

QString Orks::GetNom()
{
    return "Orks";
}

QString Orks::GetDescription()
{
    return "Description des Orks";
}

QString Orks::GetDescriptionUniversite()
{
    return "Les orks sont des mutants qui embrassent avant tout une vie simple et brutale sans prise de tête.";
}

QString Orks::GetId()
{
    return Coterie::ORKS;
}

QString Orks::GetImage()
{
    return ":/images/orks/mekano.PNG";
}

std::shared_ptr<Effet> Orks::AjouterEffetUniversite(GenHistoire* genHist, shared_ptr<Evt> evt, QString go_to_effet_suivant )
{
    QVector<shared_ptr<NoeudProbable>> noeudsProbaEducation;

    // blessure dans la fosse
    QString blessure = PbSante::GetBlessureLegereAleatoire();
    shared_ptr<Effet> effet1 = genHist->AjouterEffetNarration(
                "Au cours d'un entrainement au combat dans les fosses vous recevez une blessure : " + blessure +
                "\nLes orks en rigolent un bon coup et vous tappent dans le dos joyeusement. \"Tu verras quand tu s'ras un vrai ork ça r'poussera\"",
                ":/images/orks/gros_cosatud_jugeant.jpg",
                "", evt);
    effet1->AjouterChangeurDeCarac(blessure, "1");
    effet1->AjouterAjouteurACarac(Combat::C_CAP_COMBAT, "1"); // meilleur combattant
    effet1->AjouterChangeurDeCarac((make_shared<Trait>(eTrait::beau))->GetNom(), ""); // le joueur perd son éventuelle beauté...
    effet1->m_GoToEffetId = go_to_effet_suivant;
    shared_ptr<Condition> cond1 = make_shared<Condition>(1.0, TypeProba::p_Relative);
    shared_ptr<NoeudProbable> noeud1 = make_shared<NoeudProbable>(
                effet1,
                cond1);
    noeudsProbaEducation.push_back(noeud1);

    // formation mékano
    shared_ptr<Effet> effetMekano = genHist->AjouterEffetNarration(
                "Un mékano a remarqué vos capacités et vous a formé aux bases de la réparation de moteurs. "
                "\nBien que sa technique semble rudimentaire à première vue il est véritablement doué et très entousisaste comm enseignant."
                "\nIl vous prometq ue quand vous serez un vrai ork il vous apprendra à fabriquer des armes, ce qui est encore plus rigolo.",
                ":/images/orks/mekano.PNG",
                "", evt);
    effetMekano->m_GoToEffetId = go_to_effet_suivant;
    effetMekano->m_Conditions = {
        make_shared<Condition>(Trait::GetNomTrait(eTrait::intelligent), "1", Comparateur::c_SuperieurEgal)
    };
    effetMekano->AjouterAjouteurACarac(Ingenieur::C_MECANIQUE, "1"); // meilleur Mékano
    shared_ptr<Condition> cond = make_shared<Condition>(1.0, TypeProba::p_Relative);
    shared_ptr<NoeudProbable> noeudMekano = make_shared<NoeudProbable>(
                effetMekano,
                cond);
    noeudsProbaEducation.push_back(noeudMekano);

    shared_ptr<Effet> effetSelecteur = genHist->m_GenerateurEvt->AjouterEffetSelecteurDEvt(
                noeudsProbaEducation);
    effetSelecteur->m_MsChrono = 1; // passé automatiquement

    return effetSelecteur;
}
