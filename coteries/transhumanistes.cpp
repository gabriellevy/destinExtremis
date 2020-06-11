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
#include "socio_eco/economieevt.h"
#include "religion/religion.h"
#include "socio_eco/classesociale.h"
#include "humanite/pnj.h"

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

void Transhumanistes::GenererPortraits(QMap<QString, QString> caracs, int ageAnnees, QVector<QString>&images)
{
    bool femme = caracs[PNJ::C_SEXE] == PNJ::FEMME;
    if ( femme ) {

    }
    else {
        if ( ageAnnees >= 10 ) {
            if ( ageAnnees <= 20 ) {
                images.push_back(":/images/transhumanistes/portrait10-20.jpg");
            }
        }
        if ( ageAnnees >= 35 ) {
            images.push_back(":/images/transhumanistes/portrait35+.jpg");
            images.push_back(":/images/transhumanistes/portrait35+_2.jpg");
            images.push_back(":/images/transhumanistes/portrait35+_3.jpg");
        }
        if ( ageAnnees >= 40 ) {
            images.push_back(":/images/transhumanistes/portrait40+.jpg");
        }
        if ( ageAnnees >= 50 ) {
            images.push_back(":/images/transhumanistes/portrait50+.jpg");
        }
        if ( ageAnnees >= 60 ) {
            images.push_back(":/images/transhumanistes/portrait60+.jpg");
            images.push_back(":/images/transhumanistes/portrait60+_2.jpg");
        }
        if ( ageAnnees >= 70 ) {
            images.push_back(":/images/transhumanistes/portrait70+.jpg");
        }
        if ( ageAnnees >= 30 ) {
            if ( ageAnnees <= 50 ) {
                images.push_back(":/images/transhumanistes/portrait30-50.jpg");
                images.push_back(":/images/transhumanistes/portrait30-50_2.jpg");
                images.push_back(":/images/transhumanistes/portrait30-50_3.jpg");
                images.push_back(":/images/transhumanistes/portrait30-50_2.png");
            }
        }
        if ( ageAnnees >= 20 ) {
            if ( ageAnnees <= 50 ) {
                images.push_back(":/images/transhumanistes/portrait20-40.jpg");
                images.push_back(":/images/transhumanistes/portrait20-50.jpg");
                images.push_back(":/images/transhumanistes/portrait20-50_2.jpg");
                images.push_back(":/images/transhumanistes/portrait20-50_3.jpg");
                images.push_back(":/images/transhumanistes/portrait20-50.png");
            }
        }
        if ( ageAnnees >= 15 ) {
            if ( ageAnnees <= 30 ) {
                images.push_back(":/images/transhumanistes/portrait15-30.jpg");
                images.push_back(":/images/transhumanistes/portrait15-30_2.jpg");
                images.push_back(":/images/transhumanistes/portrait15-30_3.jpg");
            }
        }
    }

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
        make_shared<Condition>(Trait::GetNomTrait(eTrait::travailleur), "1", Comparateur::c_Egal ),
        make_shared<Condition>(ClasseSociale::C_CLASSE_SOCIALE, ClasseSociale::INFLUENTS, Comparateur::c_Egal ), // la richesse est déjà un signe d'ascension et d'homme supérieur chez les transhumanistes
        make_shared<Condition>(ClasseSociale::C_CLASSE_SOCIALE, ClasseSociale::MAITRES, Comparateur::c_Egal )
    };
    m_TraitsIncompatible = {
        make_shared<Condition>(Trait::GetNomTrait(eTrait::franc), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::altruiste), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::sens_du_groupe), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::sens_du_sacrifice), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::patriote), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::spirituel), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::nature), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::artiste), "1", Comparateur::c_Egal ),
        make_shared<Condition>(ClasseSociale::C_CLASSE_SOCIALE, ClasseSociale::PAUVRES, Comparateur::c_Egal ), // les pauvres sont plutôt mal vus par les transhumanistes
        make_shared<Condition>(ClasseSociale::C_CLASSE_SOCIALE, ClasseSociale::MISERABLES, Comparateur::c_Egal )
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
    return "Les transhumanistes sont la coterie qui embrasse le plus la technologie moderne surtout dans tout ce qui s'applique à la transformation de l'humain. "
            "Ils s'obsèdent en particulier pour la cybernétique et les modifications génétiques et ils sont très loin en avance sur toutes les autres coteries à ce sujet.";
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

    // cours scientifique
    {
        shared_ptr<Effet> effet = genHist->AjouterEffetNarration(
                    "La génétique et la cybernétique sont les base du transhumanisme. Une initiation à ces sciences est indispensable dans cette université. ",
                    ":/images/transhumanistes/labo.jpg",
                    "", evt);
        GenVieHumain::TransformerEffetEnEffetMoisDeVie(effet, false);
        effet->AjouterAjouteurACarac(Metier::GENETICIEN, "1");
        effet->AjouterAjouteurACarac(Metier::CYBERNETICIEN, "1");
        effet->AjouterAjouteurACarac(EconomieEvt::C_NIVEAU_ECONOMIQUE, "-1");
        effet->m_GoToEffetId = go_to_effet_suivant;
        shared_ptr<Condition> cond1 = make_shared<Condition>(0.7, TypeProba::p_Relative);
        Trait::AjouterModifProbaSiACeTrait(cond1.get(), 0.5, intelligent);
        Trait::AjouterModifProbaSiACeTrait(cond1.get(), -0.5, bete);
        shared_ptr<NoeudProbable> noeud1 = make_shared<NoeudProbable>(
                    effet,
                    cond1);
        noeudsProbaEducation.push_back(noeud1);
    }
    // cours informatique
    {
        shared_ptr<Effet> effet = genHist->AjouterEffetNarration(
                    "L'informatique est indispensable pour garder en fonctionnement les nombreuses organisations techniquement avancées des transhumanistes. "
                    "L'université comprend bien sûr des cours variés dans cette discipline.",
                    ":/images/transhumanistes/poste de controle.jpg",
                    "", evt);
        effet->AjouterAjouteurACarac(Metier::INFORMATICIEN, "1");
        effet->AjouterAjouteurACarac(EconomieEvt::C_NIVEAU_ECONOMIQUE, "-1");
        GenVieHumain::TransformerEffetEnEffetMoisDeVie(effet, false);
        effet->m_GoToEffetId = go_to_effet_suivant;
        shared_ptr<Condition> cond1 = make_shared<Condition>(1.0, TypeProba::p_Relative);
        shared_ptr<NoeudProbable> noeud1 = make_shared<NoeudProbable>(
                    effet,
                    cond1);
        noeudsProbaEducation.push_back(noeud1);
    }
    // cours de commerce
    {
        shared_ptr<Effet> effet = genHist->AjouterEffetNarration(
                    "La base de la philosophie libérale transhumaniste est que tout se vend. Les produits et les améliorations cybernétique bien sûr. Mais un politique se vend aussi à son électorat comme un gendre à sa belle famille."
                    "Que vous fassiez carrière dans le commerce ou pas ces cours de commerce et de manipulation seront utiles.",
                    ":/images/transhumanistes/commercial.jpg",
                    "", evt);
        effet->AjouterAjouteurACarac(Metier::COMMERCIAL, "1");
        effet->AjouterAjouteurACarac(EconomieEvt::C_NIVEAU_ECONOMIQUE, "-1");
        GenVieHumain::TransformerEffetEnEffetMoisDeVie(effet, false);
        double proba = Aleatoire::GetAl()->Entre0Et1();
        if ( proba <= 0.5) {
            effet->m_Texte += "\nVous devenez 'cupide'.";
            effet->AjouterChangeurDeCarac(Trait::GetNomTrait(cupide), "1");
        }
        if ( proba <= 0.5) {
            effet->m_Texte += "\nVous devenez 'charmeur'.";
            effet->AjouterChangeurDeCarac(Trait::GetNomTrait(charmeur), "1");
        }
        effet->m_GoToEffetId = go_to_effet_suivant;
        shared_ptr<Condition> cond1 = make_shared<Condition>(1.0, TypeProba::p_Relative);
        shared_ptr<NoeudProbable> noeud1 = make_shared<NoeudProbable>(
                    effet,
                    cond1);
        noeudsProbaEducation.push_back(noeud1);
    }

    // cours de philosophie libérale transhumaniste
    {
        shared_ptr<Effet> effet = genHist->AjouterEffetNarration(
                    "Toute coterie a une forme de philosophie et celle des transhumanistes est une des plus développée. Tout vous est expliqué sur plusieurs mois. Du matérialisme au libéralisme. "
                    "Le progrès est central et l'amélioration de l'humain en tant qu'individu complet est le but final de toute la coterie. Vous en ressortez transformé.",
                    ":/images/transhumanistes/ingenieur.jpg",
                    "", evt);
        Trait::AjouterGagneTraitSelonProba(effet, egoiste, 0.5);
        Trait::AjouterGagneTraitSelonProba(effet, ambitieux, 0.5);
        Trait::AjouterGagneTraitSelonProba(effet, cupide, 0.5);
        Trait::AjouterGagneTraitSelonProba(effet, opportuniste, 0.5);
        Trait::AjouterPerdTraitSelonProba(effet, sens_du_groupe, 0.5);
        Trait::AjouterPerdTraitSelonProba(effet, sens_du_sacrifice, 0.5);
        GenVieHumain::TransformerEffetEnEffetMoisDeVie(effet, false);
        effet->AjouterAjouteurACarac(EconomieEvt::C_NIVEAU_ECONOMIQUE, "-1");
        double proba = Aleatoire::GetAl()->Entre0Et1();
        if ( proba <= 0.5) {
            Religion::ModifierEffetEnEffetConversion(effet, Religion::ATHEE);
        }

        effet->m_GoToEffetId = go_to_effet_suivant;
        shared_ptr<Condition> cond1 = make_shared<Condition>(1.0, TypeProba::p_Relative);
        shared_ptr<NoeudProbable> noeud1 = make_shared<NoeudProbable>(
                    effet,
                    cond1);
        noeudsProbaEducation.push_back(noeud1);
    }

    // petits boulots
    {
        shared_ptr<Effet> effet = genHist->AjouterEffetNarration(
                    "L'université transhumaniste est hors de prix. Vous êtes obligé de prendre des petits boulots à côté pour vous en sortir. L'université voit cela d'un bon oeil car ça donne de la main d'oeuvre pas cher à son conglomérat et forme les étudiants au monde du travail.",
                    "",
                    "", evt);
        Trait::AjouterGagneTraitSelonProba(effet, travailleur, 0.5);
        Trait::AjouterGagneTraitSelonProba(effet, angoisse, 0.5);
        effet->AjouterAjouteurACarac(EconomieEvt::C_NIVEAU_ECONOMIQUE, "2");
        GenVieHumain::TransformerEffetEnEffetMoisDeVie(effet, false);

        effet->m_GoToEffetId = go_to_effet_suivant;
        shared_ptr<Condition> cond1 = make_shared<Condition>(1.0, TypeProba::p_Relative);
        shared_ptr<NoeudProbable> noeud1 = make_shared<NoeudProbable>(
                    effet,
                    cond1);
        noeudsProbaEducation.push_back(noeud1);
    }

    // faire la fête
    {
        shared_ptr<Effet> effet = genHist->AjouterEffetNarration(
                    "L'université transhumaniste n'est aps juste un lieu d'apprentissage univeraitaire, c'est aussi un lieu de vie et de consommation unique dans tout Extremis. "
                    "Impossible de passer à côté des fêtes innombrables, toutes plus surprenantes et chères les unes que les autres.",
                    ":/images/transhumanistes/boite_de_nuit.jpg",
                    "", evt);
        Trait::AjouterGagneTraitSelonProba(effet, jouisseur, 0.5);
        effet->AjouterAjouteurACarac(EconomieEvt::C_NIVEAU_ECONOMIQUE, "-2");
        GenVieHumain::TransformerEffetEnEffetMoisDeVie(effet, false);

        effet->m_GoToEffetId = go_to_effet_suivant;
        shared_ptr<Condition> cond1 = make_shared<Condition>(1.0, TypeProba::p_Relative);
        shared_ptr<NoeudProbable> noeud1 = make_shared<NoeudProbable>(
                    effet,
                    cond1);
        noeudsProbaEducation.push_back(noeud1);
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
        m_Nom = "hôpital transhumaniste";
        m_Description = "???";
        m_ConditionSelecteurProba = make_shared<Condition>(0.9 + tmp_Modificateur, p_Relative);
        this->m_IncrementeursCaracs[EconomieEvt::C_NIVEAU_ECONOMIQUE] =-2;
        m_Conditions.push_back(
             make_shared<Condition>(PbSante::C_MOIS_HOPITAL, "0", Comparateur::c_Superieur));
        m_Conditions.push_back(
             make_shared<Condition>(QuartierEffets::C_QUARTIER_ACTUEL, cot->m_Quartier->m_Nom, Comparateur::c_Egal));
        m_CallbackDisplay = [] {
            Humain* hum = Humain::GetHumainJoue();
            shared_ptr<Effet> eff = ExecHistoire::GetEffetActuel();
            eff->m_Texte = "L'hopital transhumaniste où vous vous trouvez est hors de prix mais d'une qualité exceptionnelle.";

            // guérison d'une blessure
            for ( QString blessure: PbSante::BLESSURES_LEGERES) {
                if ( hum->GetValeurCarac(blessure) == "1") {
                    eff->m_Texte +="\nVous n'êtes plus " + blessure + ".";
                    hum->SetValeurACaracId(blessure, "");
                    return;
                }
            }
            for ( QString blessure: PbSante::BLESSURES_GRAVES) {
                if ( hum->GetValeurCarac(blessure) == "1") {
                    eff->m_Texte +="\nVous n'êtes plus " + blessure + ".";
                    hum->SetValeurACaracId(blessure, "");
                    return;
                }
            }
        };
    }break;
    }
}
