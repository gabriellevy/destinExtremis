#include "amour.h"
#include "../destinLib/abs/effet.h"
#include "../destinLib/abs/evt.h"
#include "../destinLib/gen/genevt.h"
#include "../destinLib/aleatoire.h"
#include "../destinLib/abs/selectionneurdenoeud.h"
#include "extremis.h"
#include "genviehumain.h"
#include "geographie/quartier.h"
#include <memory>
#include "humanite/pnj.h"
#include "humain.h"
#include <QtMath>

using std::make_shared;

// caracs liées :
QString Amour::PRE_AMOUREUSE1 = "Amoureuse_"; // pas forcément amoureuse, ça peut être juste le perso qui est amoureux d'elle
QString Amour::PRE_AMOUREUSE2 = "Amoureuse 2_"; // triangle moureux...
QString Amour::PRE_AMOUREUSE3 = "Amoureuse 3_"; // triangle moureux...
QString Amour::C_ETAT_MARITAL = "État marital";
QString Amour::C_ETAT_AMOUREUX_M = "Etat amoureux homme";
QString Amour::C_ETAT_AMOUREUX_F = "Etat amoureux homme";
// valeurs de C_ETAT_MARITAL
QString Amour::CELIBATAIRE = "Célibataire";
QString Amour::FIANCE = "Fiancé";//
QString Amour::MARIE = "Marié";
QString Amour::CONCUBIN = "Concubin";
QString Amour::REGULIERE = "Régulière";// relations sexuelle régulières sans engagement
// valeurs de C_ETAT_AMOUREUX
QString Amour::INDIFERENT = "Indifférent";
QString Amour::ENGAGE = "Engagé";
QString Amour::INTERESSE = "Intéressé";
QString Amour::AMOUREUX = "Amoureux";
QString Amour::MEPRIS = "Méprisant"; // et autres sentiments négatifs
QString Amour::AMOUREUX_OBSESSIONEL = "Obsessionnel";

Amour::Amour(int indexEvt):GenerateurNoeudsProbables (indexEvt)
{
    double tmpModificateur = 0.0;
    switch (indexEvt) {
    case 0 : {
        m_Nom = "Tombe amoureux d'une femme"; // mais pas elle de lui
        m_ConditionSelecteurProba = make_shared<Condition>(0.008 + tmpModificateur, p_Relative);
        m_ConditionSelecteurProba->AjouterModifProba(0.005,
            { make_shared<Condition>(Trait::GetNomTrait(jouisseur), "1", Comparateur::c_Egal) } );
        m_ConditionSelecteurProba->AjouterModifProba(0.002,
            { make_shared<Condition>(Trait::GetNomTrait(sensible), "1", Comparateur::c_Egal) } );
        m_ConditionSelecteurProba->AjouterModifProba(0.002,
            { make_shared<Condition>(Trait::GetNomTrait(pervers_sexuel), "1", Comparateur::c_Egal) } );
        m_ConditionSelecteurProba->AjouterModifProba(-0.002,
            { make_shared<Condition>(Trait::GetNomTrait(spirituel), "1", Comparateur::c_Egal) } );
        m_ConditionSelecteurProba->AjouterModifProba(0.005,
            { make_shared<Condition>(Trait::GetNomTrait(jouisseur), "1", Comparateur::c_Egal) } );
        m_ConditionSelecteurProba->AjouterModifProba(-0.005,
            { make_shared<Condition>(GenVieHumain::AGE, "40", Comparateur::c_Superieur) } );

        m_Description = "hop";
        m_CallbackDisplay = [] {
          Humain* hum = Humain::GetHumainJoue();
          shared_ptr<Effet> effet = ExecHistoire::GetEffetActuel();
          Amour::GenererTombeAmoureux(hum, effet);
        };
        // ne retombe pas amoureux si il l'est déjà (et limite dure à 3 amoureuses)
        m_Conditions.push_back( make_shared<Condition>(PRE_AMOUREUSE1 + C_ETAT_AMOUREUX_M, Amour::AMOUREUX, Comparateur::c_Different));
        m_Conditions.push_back( make_shared<Condition>(PRE_AMOUREUSE2 + C_ETAT_AMOUREUX_M, Amour::AMOUREUX, Comparateur::c_Different)        );
        m_Conditions.push_back( make_shared<Condition>(PRE_AMOUREUSE3 + C_ETAT_AMOUREUX_M, "", Comparateur::c_Egal)        );
        m_Conditions.push_back( make_shared<Condition>(PRE_AMOUREUSE3 + C_ETAT_AMOUREUX_F, "", Comparateur::c_Egal)        );
    }break;
    case 1 : {
        m_Nom = "Une femme tombe amoureuse de lui"; // mais pas lui d'elle
        m_ConditionSelecteurProba = make_shared<Condition>(0.008 + tmpModificateur, p_Relative);
        m_ConditionSelecteurProba->AjouterModifProba(0.005,
            { make_shared<Condition>(Trait::GetNomTrait(beau), "1", Comparateur::c_Egal) } );
        m_ConditionSelecteurProba->AjouterModifProba(0.002,
            { make_shared<Condition>(Trait::GetNomTrait(grand), "1", Comparateur::c_Egal) } );
        m_ConditionSelecteurProba->AjouterModifProba(0.002,
            { make_shared<Condition>(Trait::GetNomTrait(artiste), "1", Comparateur::c_Egal) } );
        m_ConditionSelecteurProba->AjouterModifProba(0.002,
            { make_shared<Condition>(Trait::GetNomTrait(fort), "1", Comparateur::c_Egal) } );
        m_ConditionSelecteurProba->AjouterModifProba(-0.002,
            { make_shared<Condition>(Trait::GetNomTrait(angoisse), "1", Comparateur::c_Egal) } );
        m_ConditionSelecteurProba->AjouterModifProba(-0.002,
            { make_shared<Condition>(Trait::GetNomTrait(faible), "1", Comparateur::c_Egal) } );
        m_ConditionSelecteurProba->AjouterModifProba(-0.003,
            { make_shared<Condition>(Trait::GetNomTrait(laid), "1", Comparateur::c_Egal) } );
        m_ConditionSelecteurProba->AjouterModifProba(-0.003,
            { make_shared<Condition>(Trait::GetNomTrait(chetif), "1", Comparateur::c_Egal) } );
        m_ConditionSelecteurProba->AjouterModifProba(-0.002,
            { make_shared<Condition>(Trait::GetNomTrait(bete), "1", Comparateur::c_Egal) } );
        m_ConditionSelecteurProba->AjouterModifProba(-0.002,
            { make_shared<Condition>(Trait::GetNomTrait(paresseux), "1", Comparateur::c_Egal) } );
        m_ConditionSelecteurProba->AjouterModifProba(0.005,
            { make_shared<Condition>(Trait::GetNomTrait(charmeur), "1", Comparateur::c_Egal) } );
        m_ConditionSelecteurProba->AjouterModifProba(-0.005,
            { make_shared<Condition>(GenVieHumain::AGE, "40", Comparateur::c_Superieur) } );

        m_Description = "hop";
        m_CallbackDisplay = [] {
          Humain* hum = Humain::GetHumainJoue();
          shared_ptr<Effet> effet = ExecHistoire::GetEffetActuel();
          Amour::GenererAmoureuse(hum, effet);
        };
    }break;
    case 2 : {
        m_Nom = "Coup de foudre";
        m_ConditionSelecteurProba = make_shared<Condition>(0.003 + tmpModificateur, p_Relative);
        m_ConditionSelecteurProba->AjouterModifProba(0.0005,
            { make_shared<Condition>(Trait::GetNomTrait(beau), "1", Comparateur::c_Egal) } );
        m_ConditionSelecteurProba->AjouterModifProba(0.0002,
            { make_shared<Condition>(Trait::GetNomTrait(grand), "1", Comparateur::c_Egal) } );
        m_ConditionSelecteurProba->AjouterModifProba(0.0002,
            { make_shared<Condition>(Trait::GetNomTrait(artiste), "1", Comparateur::c_Egal) } );
        m_ConditionSelecteurProba->AjouterModifProba(0.0002,
            { make_shared<Condition>(Trait::GetNomTrait(fort), "1", Comparateur::c_Egal) } );
        m_ConditionSelecteurProba->AjouterModifProba(-0.0002,
            { make_shared<Condition>(Trait::GetNomTrait(angoisse), "1", Comparateur::c_Egal) } );
        m_ConditionSelecteurProba->AjouterModifProba(-0.0002,
            { make_shared<Condition>(Trait::GetNomTrait(faible), "1", Comparateur::c_Egal) } );
        m_ConditionSelecteurProba->AjouterModifProba(-0.0003,
            { make_shared<Condition>(Trait::GetNomTrait(laid), "1", Comparateur::c_Egal) } );
        m_ConditionSelecteurProba->AjouterModifProba(-0.0003,
            { make_shared<Condition>(Trait::GetNomTrait(chetif), "1", Comparateur::c_Egal) } );
        m_ConditionSelecteurProba->AjouterModifProba(-0.0002,
            { make_shared<Condition>(Trait::GetNomTrait(bete), "1", Comparateur::c_Egal) } );
        m_ConditionSelecteurProba->AjouterModifProba(-0.0002,
            { make_shared<Condition>(Trait::GetNomTrait(paresseux), "1", Comparateur::c_Egal) } );
        m_ConditionSelecteurProba->AjouterModifProba(0.0005,
            { make_shared<Condition>(Trait::GetNomTrait(charmeur), "1", Comparateur::c_Egal) } );
        m_ConditionSelecteurProba->AjouterModifProba(-0.0005,
            { make_shared<Condition>(GenVieHumain::AGE, "40", Comparateur::c_Superieur) } );

        m_Description = "hop";
        m_CallbackDisplay = [] {
          Humain* hum = Humain::GetHumainJoue();
          shared_ptr<Effet> effet = ExecHistoire::GetEffetActuel();
          Amour::GenererRencontreAmoureuse(hum, effet);
        };
    }break;
    }
}


void Amour::GenererAmoureusePotentielle(QString prefixe, Humain* hum, std::shared_ptr<Effet> effetNarration)
{
    // génération des traits :
    int nb = 2 + Aleatoire::GetAl()->EntierInferieurA(4);
    QVector<eTrait> traits = {};
    while(nb-->0) {
        shared_ptr<Trait> trait = Trait::GetTrait(traits, false);
        traits.push_back(trait->m_eTrait);
    }
    shared_ptr<Coterie> saCoterie = Coterie::GetCoterieAleatoire(true);

    for (eTrait trait: traits) {
        hum->SetValeurACaracId(prefixe + Trait::GetNomTrait(trait), "1");
    }

    QString sonNom = saCoterie->CreerPatronyme(false);
    hum->SetValeurACaracId(prefixe + PNJ::C_NOM, sonNom);
    hum->SetValeurACaracId(prefixe + PNJ::C_SEXE, PNJ::FEMME);
    hum->SetValeurACaracId(prefixe + PNJ::C_COTERIE, saCoterie->GetId());

    // son age :
    int ageP = hum->GetValeurCaracAsInt(GenVieHumain::AGE);
    int decal = qMin(ageP/2 - Aleatoire::GetAl()->EntierInferieurA(ageP), ageP-15);
    int age = ageP + decal;
    hum->SetValeurACaracId(prefixe + GenVieHumain::AGE, age);

    // son statut marital
    double proba = Aleatoire::GetAl()->Entre0Et1();
    if ( proba <=0.5) {
        hum->SetValeurACaracId(prefixe + Amour::C_ETAT_MARITAL,Amour::CELIBATAIRE);
    } else if ( proba <=0.6) {
        hum->SetValeurACaracId(prefixe + Amour::C_ETAT_MARITAL,Amour::FIANCE);
    } else if ( proba <=0.9) {
        hum->SetValeurACaracId(prefixe + Amour::C_ETAT_MARITAL,Amour::MARIE);
    } else {
        hum->SetValeurACaracId(prefixe + Amour::C_ETAT_MARITAL,Amour::REGULIERE);
    }

    effetNarration->m_Texte = "Vous rencontrez " + sonNom + ".\n";
}

void Amour::GenererTombeAmoureux(Humain* hum, std::shared_ptr<Effet> effetNarration)
{
    // 1ère, 2ème ou 3ème ?
    QString prefixe = Amour::DeterminerNumeroAmoureuse(hum);

    Amour::GenererAmoureusePotentielle(prefixe, hum, effetNarration);

    effetNarration->m_Texte += "Vous tombez amoureux d'elle.";
    hum->SetValeurACaracId(prefixe + C_ETAT_AMOUREUX_M, AMOUREUX);
}

QString Amour::DeterminerNumeroAmoureuse(Humain* hum)
{
    QString prefixe = "";
    if (hum->GetValeurCarac(PRE_AMOUREUSE1 + C_ETAT_AMOUREUX_M) == "" &&
            hum->GetValeurCarac(PRE_AMOUREUSE1 + C_ETAT_AMOUREUX_F) == "")
        prefixe = PRE_AMOUREUSE1;
    else if (hum->GetValeurCarac(PRE_AMOUREUSE2 + C_ETAT_AMOUREUX_M) == "" &&
             hum->GetValeurCarac(PRE_AMOUREUSE2 + C_ETAT_AMOUREUX_F) == "")
        prefixe = PRE_AMOUREUSE2;
    else if (hum->GetValeurCarac(PRE_AMOUREUSE3 + C_ETAT_AMOUREUX_M) == "" &&
             hum->GetValeurCarac(PRE_AMOUREUSE3 + C_ETAT_AMOUREUX_F) == "")
        prefixe = PRE_AMOUREUSE3;
    else {
        // déjà trop d'amoureuses : il en perd une de vue
        // on liquide les histoires où seule la femme est amoureuse :
        if (hum->GetValeurCarac(PRE_AMOUREUSE1 + C_ETAT_AMOUREUX_M) == "" )
            prefixe = PRE_AMOUREUSE1;
        else if (hum->GetValeurCarac(PRE_AMOUREUSE2 + C_ETAT_AMOUREUX_M) == "" )
            prefixe = PRE_AMOUREUSE2;
        else if (hum->GetValeurCarac(PRE_AMOUREUSE3 + C_ETAT_AMOUREUX_M) == "" )
            prefixe = PRE_AMOUREUSE3;
        else {
            // on liquide les histore juste "intéressées"
            if (hum->GetValeurCarac(PRE_AMOUREUSE1 + C_ETAT_AMOUREUX_M) == Amour::INTERESSE )
                prefixe = PRE_AMOUREUSE1;
            else if (hum->GetValeurCarac(PRE_AMOUREUSE2 + C_ETAT_AMOUREUX_M) == Amour::INTERESSE )
                prefixe = PRE_AMOUREUSE2;
            else if (hum->GetValeurCarac(PRE_AMOUREUSE3 + C_ETAT_AMOUREUX_M) == Amour::INTERESSE )
                prefixe = PRE_AMOUREUSE3;
            else {
                // on liquide ce qui n'est pas mariage ou concubin
                if (hum->GetValeurCarac(PRE_AMOUREUSE1 + C_ETAT_AMOUREUX_M) != Amour::ENGAGE )
                    prefixe = PRE_AMOUREUSE1;
                else
                    prefixe = PRE_AMOUREUSE2;
            }
        }
    }


    return prefixe;
}

void Amour::GenererRencontreAmoureuse(Humain* hum, std::shared_ptr<Effet> effetNarration)
{
    // 1ère, 2ème ou 3ème ?
    QString prefixe = Amour::DeterminerNumeroAmoureuse(hum);

    Amour::GenererAmoureusePotentielle(prefixe, hum, effetNarration);

    effetNarration->m_Texte += "C'est le coup de foudre.";
    hum->SetValeurACaracId(prefixe + C_ETAT_AMOUREUX_F, AMOUREUX);
    hum->SetValeurACaracId(prefixe + C_ETAT_AMOUREUX_M, AMOUREUX);
}

void Amour::GenererAmoureuse(Humain* hum, std::shared_ptr<Effet> effetNarration)
{
    // 1ère, 2ème ou 3ème ?
    QString prefixe = Amour::DeterminerNumeroAmoureuse(hum);

    Amour::GenererAmoureusePotentielle(prefixe, hum, effetNarration);

    effetNarration->m_Texte += "Elle tombe amoureuse de vous.";
    hum->SetValeurACaracId(prefixe + C_ETAT_AMOUREUX_F, AMOUREUX);
}
