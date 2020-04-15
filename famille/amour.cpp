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
#include <QDebug>
#include <QtMath>

using std::make_shared;

// caracs liées :
QString Amour::PRE_AMOUREUSE1 = "Amoureuse_"; // pas forcément amoureuse, ça peut être juste le perso qui est amoureux d'elle
QString Amour::PRE_AMOUREUSE2 = "Amoureuse 2_"; // triangle moureux...
QString Amour::PRE_AMOUREUSE3 = "Amoureuse 3_"; // triangle moureux...
QString Amour::C_ETAT_MARITAL = "État marital";
QString Amour::C_ETAT_AMOUREUX = "Etat amoureux";
// valeurs de C_ETAT_MARITAL
QString Amour::CELIBATAIRE = "Célibataire";
QString Amour::FIANCE = "Fiancé";//
QString Amour::MARIE = "Marié";
QString Amour::CONCUBIN = "Concubin";
QString Amour::REGULIERE = "Régulière";// relations sexuelle régulières sans engagement
// valeurs de C_ETAT_AMOUREUX
QString Amour::LUI_AMOUREUX = "lui amoureux"; // et pas elle
QString Amour::ELLE_AMOUREUX = "elle amoureuse"; // et pas lui
QString Amour::AMOUREUX = "amoureux"; // les deux

Amour::Amour(int indexEvt):GenerateurNoeudsProbables (indexEvt)
{
    qDebug()<<" ---- Amour début"<<endl;
    double tmpModificateur = 0.0;
    switch (indexEvt) {
    case 0 : {
        qDebug()<<" ---- Amour 1"<<endl;
        m_Nom = "Rencontre amoureuse";
        m_ConditionSelecteurProba = make_shared<Condition>(0.01 + tmpModificateur, p_Relative);
        m_ConditionSelecteurProba->AjouterModifProba(-0.004,
            {make_shared<Condition>(PRE_AMOUREUSE1 + C_ETAT_AMOUREUX, "", Comparateur::c_Different)}
        );
        m_ConditionSelecteurProba->AjouterModifProba(-0.004,
            {make_shared<Condition>(PRE_AMOUREUSE2 + C_ETAT_AMOUREUX, "", Comparateur::c_Different)}
        );
        m_Description = "hop";
        qDebug()<<" ---- Amour 2"<<endl;
        m_CallbackDisplay = [] {
            qDebug()<<" ---- m_CallbackDisplay début"<<endl;
          Humain* hum = Humain::GetHumainJoue();
          shared_ptr<Effet> effet = ExecHistoire::GetEffetActuel();
          Amour::GenererRencontreAmoureuse(hum, effet);
          qDebug()<<" ---- m_CallbackDisplay fin"<<endl;
        };
        m_Conditions.push_back(
            make_shared<Condition>(PRE_AMOUREUSE3 + C_ETAT_AMOUREUX, "", Comparateur::c_Egal)
        );
        qDebug()<<" ---- Amour 3"<<endl;
    }break;
    }
    qDebug()<<" ---- Amour fin"<<endl;
}


void Amour::GenererRencontreAmoureuse(Humain* hum, std::shared_ptr<Effet> effetNarration)
{
    qDebug()<<"--- GenererRencontreAmoureuse début"<<endl;
    // génération des traits :
    int nb = 2 + Aleatoire::GetAl()->EntierInferieurA(4);
    QVector<eTrait> traits = {};
    while(nb-->0) {
        shared_ptr<Trait> trait = Trait::GetTrait(traits, false);
        traits.push_back(trait->m_eTrait);
    }
    shared_ptr<Coterie> saCoterie = Coterie::GetCoterieAleatoire(true);

    double probaElleTombeAmoureuse = Aleatoire::GetAl()->Entre0Et1();
    if ( hum->ACeTrait(beau) ) probaElleTombeAmoureuse += 0.05;
    if ( hum->ACeTrait(charmeur) ) probaElleTombeAmoureuse += 0.05;
    if ( hum->ACeTrait(grand) ) probaElleTombeAmoureuse += 0.03;
    if ( hum->ACeTrait(artiste) ) probaElleTombeAmoureuse += 0.02;
    if ( hum->ACeTrait(fort) ) probaElleTombeAmoureuse += 0.02;
    if ( hum->ACeTrait(angoisse) ) probaElleTombeAmoureuse -= 0.02;
    if ( hum->ACeTrait(faible) ) probaElleTombeAmoureuse -= 0.02;
    if ( hum->ACeTrait(laid) ) probaElleTombeAmoureuse -= 0.03;
    if ( hum->ACeTrait(bete) ) probaElleTombeAmoureuse -= 0.03;
    if ( hum->ACeTrait(chetif) ) probaElleTombeAmoureuse -= 0.03;
    if ( hum->ACeTrait(paresseux) ) probaElleTombeAmoureuse -= 0.02;
    bool elleAmoureuse = probaElleTombeAmoureuse>=0.5;
    qDebug()<<"GenererRencontreAmoureuse 1"<<endl;


    double probaIlTombeAmoureuse = Aleatoire::GetAl()->Entre0Et1();
    if ( hum->ACeTrait(jouisseur) ) probaIlTombeAmoureuse += 0.05;
    if ( hum->ACeTrait(sensible) ) probaIlTombeAmoureuse += 0.02;
    if ( hum->ACeTrait(pervers_sexuel) ) probaIlTombeAmoureuse += 0.02;
    if ( traits.indexOf(beau) != -1 ) probaIlTombeAmoureuse += 0.1;
    if ( hum->ACeTrait(angoisse) ) probaIlTombeAmoureuse -= 0.04;
    if ( hum->ACeTrait(spirituel) ) probaIlTombeAmoureuse -= 0.04;
    if ( traits.indexOf(laid) != -1 ) probaIlTombeAmoureuse -= 0.6;
    if ( traits.indexOf(cruel) != -1 ) probaIlTombeAmoureuse -= 0.3;
    bool ilAmoureux = probaIlTombeAmoureuse >= 0.5;

    // forcément un des deux tombe amoureux quoiqu'il arrive :
    if ( !ilAmoureux && !elleAmoureuse) {
        if ( probaElleTombeAmoureuse > probaIlTombeAmoureuse)
            elleAmoureuse = true;
        else ilAmoureux = true;
    }
    qDebug()<<"GenererRencontreAmoureuse 2"<<endl;

    // si un des deux amoureux alors on modifie les caracs :
    if ( elleAmoureuse || ilAmoureux) {
        // 1ère, 2ème ou 3ème ?
        QString prefixe = "";
        if (hum->GetValeurCarac(PRE_AMOUREUSE1 + C_ETAT_AMOUREUX) == "")
            prefixe = PRE_AMOUREUSE1;
        else if (hum->GetValeurCarac(PRE_AMOUREUSE2 + C_ETAT_AMOUREUX) == "")
            prefixe = PRE_AMOUREUSE2;
        else if (hum->GetValeurCarac(PRE_AMOUREUSE3 + C_ETAT_AMOUREUX) == "")
            prefixe = PRE_AMOUREUSE3;
        else {
            // déjà trop d'amoureuses : il perd de vue
        }
        qDebug()<<"GenererRencontreAmoureuse 3"<<endl;


        for (eTrait trait: traits) {
            hum->SetValeurACaracId(prefixe + C_ETAT_AMOUREUX, Trait::GetNomTrait(trait));
        }
        qDebug()<<"GenererRencontreAmoureuse 4"<<endl;

        QString sonNom = saCoterie->CreerPatronyme(false);

        qDebug()<<"GenererRencontreAmoureuse 4b"<<endl;

        effetNarration->m_Texte = "Vous rencontrez " + sonNom + "\n";
        qDebug()<<"GenererRencontreAmoureuse 4c"<<endl;
        if ( elleAmoureuse && !ilAmoureux) {
            effetNarration->m_Texte += "Elle tombe amoureuse de vous.";
            hum->SetValeurACaracId(prefixe + C_ETAT_AMOUREUX, ELLE_AMOUREUX);
        }
        else if ( elleAmoureuse && ilAmoureux) {
            effetNarration->m_Texte += "Vous tombez amoureux l'un de l'autre.";
            hum->SetValeurACaracId(prefixe + C_ETAT_AMOUREUX, AMOUREUX);
        }
        else if ( !elleAmoureuse && ilAmoureux) {
            effetNarration->m_Texte += "Vous tombez amoureux d'elle.";
            hum->SetValeurACaracId(prefixe + C_ETAT_AMOUREUX, LUI_AMOUREUX);
        }
        qDebug()<<"GenererRencontreAmoureuse 5"<<endl;

        hum->SetValeurACaracId(prefixe + PNJ::C_NOM, sonNom);
        hum->SetValeurACaracId(prefixe + PNJ::C_SEXE, PNJ::FEMME);
        hum->SetValeurACaracId(prefixe + PNJ::C_COTERIE, saCoterie->GetId());
        // son age :
        int ageP = hum->GetValeurCaracAsInt(GenVieHumain::AGE);
        int decal = qMin(ageP/2 - Aleatoire::GetAl()->EntierInferieurA(ageP), ageP-15);
        int age = ageP + decal;
        hum->SetValeurACaracId(prefixe + GenVieHumain::AGE, age);
        qDebug()<<"GenererRencontreAmoureuse 6"<<endl;

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

    }
    qDebug()<<" ---- GenererRencontreAmoureuse fin"<<endl;




}
