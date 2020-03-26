#include "orks.h"
#include "genviehumain.h"
#include "../destinLib/aleatoire.h"
#include "humanite/pbsante.h"
#include "violence/combat.h"
#include "techno/ingenieur.h"
#include "techno/vehicule.h"
#include "techno/bionique.h"
#include "socio_eco/metier.h"

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

float Orks::GetPoidsDemo()
{
    return 1.1;
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
    {
        QString blessure = PbSante::GetBlessureLegereAleatoire();
        shared_ptr<Effet> effet1 = genHist->AjouterEffetNarration(
                    "Au cours d'un entrainement au combat dans les fosses vous recevez une blessure : " + blessure +
                    "\nLes orks en rigolent un bon coup et vous tappent dans le dos joyeusement. \"Tu verras quand tu s'ras un vrai ork ça r'poussera\"",
                    ":/images/orks/Combat_fosse.jpg",
                    "", evt);
        effet1->AjouterChangeurDeCarac(blessure, "1");
        effet1->AjouterAjouteurACarac(Combat::C_CAP_COMBAT, "1"); // meilleur combattant
        effet1->AjouterChangeurDeCarac((make_shared<Trait>(eTrait::beau))->GetNom(), ""); // le joueur perd son éventuelle beauté...
        effet1->m_GoToEffetId = go_to_effet_suivant;
        shared_ptr<Condition> cond1 = make_shared<Condition>(1.3, TypeProba::p_Relative);
        shared_ptr<NoeudProbable> noeud1 = make_shared<NoeudProbable>(
                    effet1,
                    cond1);
        noeudsProbaEducation.push_back(noeud1);
    }

    // fou de la vitesse
    {
        shared_ptr<Effet> effet1 = genHist->AjouterEffetNarration(
                    "Tout ork se doit de savoir piloter les bolides et aimer la vitesse. Vos instructeurs font en sorte que vous fassiez un bon paquet de tours de pistes sans faire vot' mauviet'.",
                    ":/images/orks/chariot.jpg",
                    "", evt);
        double proba = Aleatoire::GetAl()->Entre0Et1();
        if ( proba >= 0.4) {
            QString blessure = PbSante::GetBlessureLegereAleatoire();
            effet1->AjouterChangeurDeCarac(blessure, "1");
            effet1->m_Texte += "\nMalheureusement vous faites quelques chutes violentes sous les moqueries de votre instructeur."
                    "Vous avez mainteannt la blessure : " + blessure;
        }
        effet1->AjouterAjouteurACarac(Vehicule::C_CONDUITE_ROUTE, "2");

        effet1->m_GoToEffetId = go_to_effet_suivant;
        shared_ptr<Condition> cond1 = make_shared<Condition>(1.0, TypeProba::p_Relative);
        shared_ptr<NoeudProbable> noeud1 = make_shared<NoeudProbable>(
                    effet1,
                    cond1);
        noeudsProbaEducation.push_back(noeud1);
    }

    // soulé à la bière
    {
        shared_ptr<Effet> effet1 = genHist->AjouterEffetNarration(
                    "Personne ne respecte un ork qui ne tient pas la bière aux champignons."
                    "Votre instructeur fait en sorte que vous goûtiez de tous les alcools ork. Et en grande quantité."
                    "\nAucun humain ayant subi une telle épreuve n'en ressort indemne.",
                    "",
                    "", evt);
        double proba = Aleatoire::GetAl()->Entre0Et1();
        if ( proba <= 0.3) {
            effet1->m_Texte += "\nVotre organisme est durement affecté. Vous devenez 'faible'.";
            effet1->AjouterChangeurDeCarac(Trait::GetNomTrait(faible), "1");
        }
        else if (proba > 0.7 )
        {
            effet1->m_Texte += "\nVous gagnez 'résistant'.";
            effet1->AjouterChangeurDeCarac(Trait::GetNomTrait(resistant), "1");
        }
        proba = Aleatoire::GetAl()->Entre0Et1();
        if ( proba <= 0.4 ) {
            effet1->m_Texte += "\nToutes vos angoisses profondes fondent définitivement.";
            effet1->AjouterChangeurDeCarac(Trait::GetNomTrait(angoisse), "");
        }
        proba = Aleatoire::GetAl()->Entre0Et1();
        if ( proba <= 0.5 ) {
            effet1->m_Texte += "\nDurablement affecté par la boisson vous devenez alcoolique.";
            effet1->AjouterChangeurDeCarac(PbSante::ALCOOLIQUE, "1");
        }
        proba = Aleatoire::GetAl()->Entre0Et1();
        if ( proba <= 0.2 ) {
            effet1->m_Texte += "\nL'alcool vous a salement endommagé le cerveau. Vous devenez 'simple'";
            effet1->AjouterChangeurDeCarac(Trait::GetNomTrait(simple), "1");
        }
        proba = Aleatoire::GetAl()->Entre0Et1();
        if ( proba <= 0.2 ) {
            effet1->m_Texte += "\nL'alcool est tellement persistant qu'il vous fait sauter vos inhibitions et votre prudence sur le coup mais aussi à long terme. Vous devenez 'franc'.";
            effet1->AjouterChangeurDeCarac(Trait::GetNomTrait(franc), "1");
        }

        effet1->m_GoToEffetId = go_to_effet_suivant;
        shared_ptr<Condition> cond1 = make_shared<Condition>(1.0, TypeProba::p_Relative);
        shared_ptr<NoeudProbable> noeud1 = make_shared<NoeudProbable>(
                    effet1,
                    cond1);
        noeudsProbaEducation.push_back(noeud1);
    }

    // formation mékano
    {
        shared_ptr<Effet> effetMekano = genHist->AjouterEffetNarration(
                    "Un mékano a remarqué vos capacités et vous a formé aux bases de la réparation de moteurs. "
                    "\nBien que sa technique semble rudimentaire à première vue il est véritablement doué et très entousiaste comm enseignant."
                    "\nIl vous promet que quand vous serez un vrai ork il vous apprendra à fabriquer des armes, ce qui est encore plus rigolo.",
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
    }

    // formation médiko
    {
        shared_ptr<Effet> effet = genHist->AjouterEffetNarration(
                    "Un médiko a remarqué vos capacités et vous a formé aux bases de la rudimentaire médecine ork. "
                    "Leur vrai point fort est leur obsession des améliorations bioniques combinée à la capacité des patients orques à accepter à peu près toutes les greffes. ",
                    ":/images/orks/ork_mediko0.jpg",
                    "", evt);
        effet->m_GoToEffetId = go_to_effet_suivant;
        effet->AjouterAjouteurACarac(Bionique::C_FABRICATION_BIONIQUE, "1"); // meilleur médiko
        effet->AjouterAjouteurACarac(Metier::MEDECIN, "1"); // meilleur médiko
        shared_ptr<Condition> cond = make_shared<Condition>(0.5, TypeProba::p_Relative);
        double proba = Aleatoire::GetAl()->Entre0Et1();
        if ( proba <= 0.3) {
            QString blessure = PbSante::GetBlessureLegereAleatoire();
            effet->m_Texte += "\nMalheureusement il en profite pour faire des expériences amusantes sur vous après vous avoir assomé avec un maillet.";
            effet->m_Texte += "\nVous êtes maintenant : " + blessure;
            effet->AjouterChangeurDeCarac(blessure, "1");
            // TODO MATHIEU : ajouter ici un bionique aléatoire
        }
        shared_ptr<NoeudProbable> noeudMekano = make_shared<NoeudProbable>(
                    effet,
                    cond);
        noeudsProbaEducation.push_back(noeudMekano);
    }

    shared_ptr<Effet> effetSelecteur = genHist->m_GenerateurEvt->AjouterEffetSelecteurDEvt(
                noeudsProbaEducation);
    effetSelecteur->m_MsChrono = 1; // passé automatiquement

    return effetSelecteur;
}
