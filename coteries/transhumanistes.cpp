#include "transhumanistes.h"
#include "genviehumain.h"
#include "../destinLib/aleatoire.h"
#include "humanite/pbsante.h"
#include "violence/combat.h"
#include "techno/ingenieur.h"
#include "techno/vehicule.h"
#include "techno/bionique.h"
#include "socio_eco/metier.h"
#include "../destinLib/exec/exechistoire.h"
#include "humain.h"
#include "../destinLib/abs/condition.h"
#include "geographie/quartier.h"
#include <QDebug>
#include "extremis.h"
#include "geographie/quartier.h"
#include "humanite/identite.h"

using std::make_shared;
using std::shared_ptr;

Transhumanistes::Transhumanistes()
{
    Initialisation();
}

shared_ptr<Quartier> Transhumanistes::GenererQuartier()
{
    m_Quartier = make_shared<Quartier>("La défense",
                                       "Quartier des Transhumanistes",
                                       ":/images/transhumanistes/quartier.jpg", this);
    Extremis::QUARTIERS[m_Quartier->m_Nom] = m_Quartier;
    return m_Quartier;
}

QString Transhumanistes::GetGentile(bool /*masculin*/)
{
    return "transhumaniste";
}

void Transhumanistes::GenererPortraits(Humain* hum, int ageAnnees, QString metier, QVector<QString>&images)
{

}

void Transhumanistes::GenererTraitCompatibles()
{
    m_TraitsCompatible = {
        make_shared<Condition>(Trait::GetNomTrait(eTrait::cupide), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::opportuniste), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::industrieux), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::pragmatique), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::jouisseur), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::ambitieux), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::angoisse), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::travailleur), "1", Comparateur::c_Egal )
    };
    m_TraitsIncompatible = {
        make_shared<Condition>(Trait::GetNomTrait(eTrait::franc), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::altruiste), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::sens_du_groupe), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::sens_du_sacrifice), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::patriote), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::spirituel), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::nature), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::artiste), "1", Comparateur::c_Egal )
    };
    m_MetiersAssocies = {
        Metier::INFORMATICIEN,
        Metier::CYBERNETICIEN,
        Metier::COMMERCIAL,
        Metier::GENETICIEN
    };
}

double Transhumanistes::GetPoidsDemo()
{
    return 1.0;
}

QString Transhumanistes::GetNom()
{
    return "Transhumanistes";
}

QString Transhumanistes::GetDescription()
{
    return "Description des Orks";
}

QString Transhumanistes::GetDescriptionUniversite()
{
    return "L'université transhumanistes est un magnifique gratte-ciel d'acier et de verre qui contient tout un campus : "
            "les salles de cours, les dortoirs, et une quantité incroyable de bars et de distractions hors de pris.";
}

QString Transhumanistes::GetId()
{
    return Coterie::TRANSHUMANISTES;
}

QString Transhumanistes::GetImage()
{
    return ":/images/transhumanistes/quartier.jpg";
}

QString Transhumanistes::CreerPatronyme(bool masculin)
{
    return Identite::CreerPatronyme(masculin);
}

std::shared_ptr<Effet> Transhumanistes::AjouterEffetUniversite(GenHistoire* genHist, shared_ptr<Evt> evt, QString go_to_effet_suivant )
{
    QVector<shared_ptr<NoeudProbable>> noeudsProbaEducation;

    // blessure dans la fosse
    {
       /* QString blessure = PbSante::GetBlessureLegereAleatoire();
        shared_ptr<Effet> effet1 = genHist->AjouterEffetNarration(
                    "Au cours d'un entrainement au combat dans les fosses vous recevez une blessure : " + blessure +
                    "\nLes orks en rigolent un bon coup et vous tappent dans le dos joyeusement. \"Tu verras quand tu s'ras un vrai ork ça r'poussera\"",
                    ":/images/orks/Combat_fosse.jpg",
                    "", evt);
        effet1->AjouterChangeurDeCarac(blessure, "1");
        effet1->AjouterChangeurDeCarac(PbSante::DEFIGURE, "1");
        effet1->AjouterAjouteurACarac(Combat::C_CAP_COMBAT, "1"); // meilleur combattant
        effet1->AjouterChangeurDeCarac((make_shared<Trait>(eTrait::beau))->GetNom(), ""); // le joueur perd son éventuelle beauté...
        effet1->m_GoToEffetId = go_to_effet_suivant;
        shared_ptr<Condition> cond1 = make_shared<Condition>(1.0, TypeProba::p_Relative);
        shared_ptr<NoeudProbable> noeud1 = make_shared<NoeudProbable>(
                    effet1,
                    cond1);
        noeudsProbaEducation.push_back(noeud1);*/
    }

    shared_ptr<Effet> effetSelecteur = genHist->m_GenerateurEvt->AjouterEffetSelecteurDEvt(
                noeudsProbaEducation);
    effetSelecteur->m_MsChrono = 1; // passé automatiquement

    return effetSelecteur;
}

EvtTranshumanistes::EvtTranshumanistes(int indexEvt):GenerateurNoeudsProbables (indexEvt)
{
    shared_ptr<Coterie> cot = Extremis::GetCoterie(Coterie::TRANSHUMANISTES);

    double tmp_Modificateur = 0.0; //pour les tests (doit être à 0 en prod)
    switch (indexEvt) {
    case 0 : {
        /*m_Nom = "Conversion à l'hôpital";
        m_Description = "???";
        m_ConditionSelecteurProba = make_shared<Condition>(0.1 + tmp_Modificateur, p_Relative);
        m_Conditions.push_back(
             make_shared<Condition>(PbSante::C_MOIS_HOPITAL, "0", Comparateur::c_Superieur));
        m_Conditions.push_back(
             make_shared<Condition>(Coterie::C_COTERIE, Coterie::ORKS, Comparateur::c_Different));
        m_CallbackDisplay = [] {
            Humain* humain = Humain::GetHumainJoue();
            shared_ptr<Effet> effet = ExecHistoire::GetEffetActuel();
            effet->m_Texte = "Un médiko ork vient rendre des visites à l'hopital et s'attarde dans votre chambre."
                             "\nD'ordinaire les médikos sont plutôt des être terrifiants vu leurs habitudes de faire des expériences sur leurs patients mais cette fois et vu votre état ses arguments attirent votre attention. En particulier quand il parle du miracle du sérum orkoïde qui quand on le boît guérit presque toutes les blessures."
                             "\nCa a l'air fou mais vous avez entendu beaucoup de témoignages sur la résistance surnaturelle des orks.";

            // devient ork ??
            shared_ptr<Coterie> orks = Extremis::GetCoterie(Coterie::ORKS);
            double proba = orks->Compatibilite(humain);
            if ( proba >= Coterie::SEUIL_CONVERSION) {
                orks->RejoindreCoterie(humain, effet);
            } else {
                effet->m_Texte += "Ca ne suffit néanmoins pas à vous convaincre de devenir un ork.";
            }
        };*/
    }break;
    }
}
