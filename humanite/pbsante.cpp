#include "pbsante.h"
#include "../destinLib/abs/effet.h"
#include "../destinLib/abs/evt.h"
#include "../destinLib/gen/genevt.h"
#include "../destinLib/aleatoire.h"
#include "../destinLib/abs/selectionneurdenoeud.h"
#include "extremis.h"
#include "genviehumain.h"
#include "socio_eco/classesociale.h"
#include "techno/bionique.h"
#include "humain.h"
#include "geographie/quartier.h"

QString PbSante::PESTE = "Peste";
QString PbSante::C_SANTE = "Sante";
QString PbSante::C_MOIS_HOPITAL = "Mois d'hopital";
QString PbSante::C_CONSTITUTION = "Constitution";
// valeurs de C_CONSTITUTION normal = ""
QString PbSante::RESISTANT = "Résistant";
QString PbSante::FRELE = "Frêle";
QString PbSante::MORT = "Mort";
QString PbSante::FOLIE = "Folie";

QString PbSante::ALCOOLIQUE = "Alcoolique";

QString PbSante::BORGNE = "Borgne";
QString PbSante::BOITEUX = "Boiteux";
QString PbSante::CICATRICE_AU_VISAGE = "Cicatrice au visage";
QString PbSante::DOIGT_COUPE = "Doigt coupé";
QString PbSante::DEFIGURE = "Défiguré";

QString PbSante::JAMBE_AMPUTEE = "Jambe amputée";
QString PbSante::BRAS_AMPUTEE = "Bras amputé";
QString PbSante::TRAUMATISME_CRANIEN = "Traumatisme cranien";
QString PbSante::HEMORAGIE_INTERNE = "Hémoragie interne";
QString PbSante::OREILLE_COUPEE = "Oreille coupée";

QVector<QString> PbSante::BLESSURES_LEGERES = { // appliquer aussi PbSante::DEFIGURE éventuellement
    PbSante::BORGNE,
    PbSante::BOITEUX,
    PbSante::CICATRICE_AU_VISAGE,
    PbSante::DOIGT_COUPE,
    PbSante::OREILLE_COUPEE
};
QVector<QString> PbSante::BLESSURES_GRAVES = {
    PbSante::JAMBE_AMPUTEE,
    PbSante::BRAS_AMPUTEE,
    PbSante::TRAUMATISME_CRANIEN,
    PbSante::HEMORAGIE_INTERNE,
    PbSante::OREILLE_COUPEE
};

QString PbSante::GetBlessureLegereAleatoire()
{
    return BLESSURES_LEGERES[Aleatoire::GetAl()->EntierInferieurA(BLESSURES_LEGERES.size())];
}

PbSante::PbSante(int indexEvt):GenerateurNoeudsProbables (indexEvt)
{
    switch (indexEvt) {
    case 0 : {
        m_Nom = "mort de vieillesse";
        m_ConditionSelecteurProba = make_shared<Condition>(0.0, p_Pure);
        m_Description = "Vous êtes mort de vieillesse.";
        // déclenchable quand on vieillit (et de plus en plus probable au fur et à mesure)
        m_ConditionSelecteurProba->AjouterModifProba(0.0001,
            {make_shared<Condition>(GenVieHumain::AGE, "480", Comparateur::c_Superieur)}); // 40 ans
        m_ConditionSelecteurProba->AjouterModifProba(0.0005,
            {make_shared<Condition>(GenVieHumain::AGE, "600", Comparateur::c_Superieur)}); // 50 ans
        m_ConditionSelecteurProba->AjouterModifProba(0.001,
            {make_shared<Condition>(GenVieHumain::AGE, "720", Comparateur::c_Superieur)}); // 60 ans
        m_ConditionSelecteurProba->AjouterModifProba(0.005,
            {make_shared<Condition>(GenVieHumain::AGE, "840", Comparateur::c_Superieur)}); // 70 ans
        m_ConditionSelecteurProba->AjouterModifProba(0.01,
            {make_shared<Condition>(GenVieHumain::AGE, "1020", Comparateur::c_Superieur)}); // 85 ans
        m_ConditionSelecteurProba->AjouterModifProba(0.05,
            {make_shared<Condition>(GenVieHumain::AGE, "1200", Comparateur::c_Superieur)}); // 100 ans
        m_ConditionSelecteurProba->AjouterModifProba(0.1,
            {make_shared<Condition>(GenVieHumain::AGE, "2400", Comparateur::c_Superieur)}); // 200 ans

        // espérance de vie différente selon la classe sociale... :
        m_ConditionSelecteurProba->AjouterModifProba(-0.001,
            {make_shared<Condition>(ClasseSociale::C_CLASSE_SOCIALE, ClasseSociale::PAUVRES, Comparateur::c_Egal)});
        m_ConditionSelecteurProba->AjouterModifProba(-0.004,
            {make_shared<Condition>(ClasseSociale::C_CLASSE_SOCIALE, ClasseSociale::INFLUENTS, Comparateur::c_Egal)});
        m_ConditionSelecteurProba->AjouterModifProba(-0.01,
            {make_shared<Condition>(ClasseSociale::C_CLASSE_SOCIALE, ClasseSociale::MAITRES, Comparateur::c_Egal)});
        // différence selon constitution
        m_ConditionSelecteurProba->AjouterModifProba(0.0001,
            {make_shared<Condition>(PbSante::C_CONSTITUTION, PbSante::FRELE, Comparateur::c_Egal)});
        m_ConditionSelecteurProba->AjouterModifProba(-0.005,
            {make_shared<Condition>(PbSante::C_CONSTITUTION, PbSante::RESISTANT, Comparateur::c_Egal)});
        // différence selon le nombre d'implants de longévité :
        m_ConditionSelecteurProba->AjouterModifProba(-0.004,
            {Bionique::AjouterConditionSiBioniqueLongeviteSuperieureA(0)});
        m_ConditionSelecteurProba->AjouterModifProba(-0.004,
            {Bionique::AjouterConditionSiBioniqueLongeviteSuperieureA(1)});
        m_ConditionSelecteurProba->AjouterModifProba(-0.004,
            {Bionique::AjouterConditionSiBioniqueLongeviteSuperieureA(2)});
        m_ConditionSelecteurProba->AjouterModifProba(-0.004,
            {Bionique::AjouterConditionSiBioniqueLongeviteSuperieureA(3)});
        m_ConditionSelecteurProba->AjouterModifProba(-0.004,
            {Bionique::AjouterConditionSiBioniqueLongeviteSuperieureA(4)});
        m_ConditionSelecteurProba->AjouterModifProba(-0.004,
            {Bionique::AjouterConditionSiBioniqueLongeviteSuperieureA(5)});
        m_ConditionSelecteurProba->AjouterModifProba(-0.004,
            {Bionique::AjouterConditionSiBioniqueLongeviteSuperieureA(6)});
        m_ConditionSelecteurProba->AjouterModifProba(-0.004,
            {Bionique::AjouterConditionSiBioniqueLongeviteSuperieureA(7)});
        m_ConditionSelecteurProba->AjouterModifProba(-0.004,
            {Bionique::AjouterConditionSiBioniqueLongeviteSuperieureA(8)});
        m_ConditionSelecteurProba->AjouterModifProba(-0.004,
            {Bionique::AjouterConditionSiBioniqueLongeviteSuperieureA(9)});

        m_ModificateursCaracs[PbSante::C_SANTE] = PbSante::MORT;
        m_Conditions.push_back(PbSante::AjouterConditionSiVivant());

    }break;
    case 1 : {
        m_Nom = "attraper la peste noire";
        m_ConditionSelecteurProba = make_shared<Condition>(0.001, p_Relative);
        m_Description = "Vous avez contracté la peste noire.";
        m_ModificateursCaracs[PbSante::PESTE] = "1";

    }break;
    case 2 : {
        m_Nom = "mort de la peste";
        m_ConditionSelecteurProba = make_shared<Condition>(0.01, p_Relative);
        m_Description = "Vous mourez des suites de la peste.";
        m_ModificateursCaracs[PbSante::C_SANTE] = PbSante::MORT;
        m_Conditions.push_back(make_shared<Condition>(PbSante::PESTE, "1", Comparateur::c_Egal));

    }break;
    }
}


void PbSante::AllerAHopital(Humain* hum, std::shared_ptr<Effet> effet, int& nbMoisHopital)
{
    hum->SetValeurACaracId(PbSante::C_MOIS_HOPITAL, nbMoisHopital);
    shared_ptr<Quartier> quartier = hum->GetQuartierCourant();
    effet->m_Texte += "\nVous devez rester " + QString::number(nbMoisHopital) +
            " mois à l'hopital. C'est un hopital " + quartier->m_Coterie->GetGentile() +
            " du quartier " + quartier->m_Nom + ".";

}

void PbSante::BlessureLegere(Humain* hum, std::shared_ptr<Effet> effet, int& nbMoisHopital)
{
    QString blessure = GetBlessureLegereAleatoire();
    effet->m_Texte += "\nVous êtes maintenant : " + blessure + ".";
    hum->SetValeurACaracId(blessure, "1");
    nbMoisHopital += 2;
}

void PbSante::BlessureGrave(Humain* hum, shared_ptr<Effet> effet, int& nbMoisHopital)
{
    QString blessure = BLESSURES_GRAVES[Aleatoire::GetAl()->EntierInferieurA(BLESSURES_GRAVES.size())];
    effet->m_Texte += "\nVous êtes maintenant : " + blessure + ".";
    // TODO effet des diverses blessures...
    hum->SetValeurACaracId(blessure, "1");
    nbMoisHopital += 10;
}

std::shared_ptr<Condition> PbSante::AjouterConditionSiAgeSuperieurA(int ageAnnees)
{
    std::shared_ptr<Condition> cond = make_shared<Condition>(GenVieHumain::AGE, QString::number(ageAnnees*12), Comparateur::c_Superieur);
    return cond;
}

std::shared_ptr<Condition> PbSante::AjouterConditionSiVivant()
{
    return make_shared<Condition>(PbSante::C_SANTE, PbSante::MORT, Comparateur::c_Different);
}

std::shared_ptr<Condition> PbSante::AjouterModifProbaSiMort(std::shared_ptr<Condition> cond, double poidsProba)
{
    cond->AjouterModifProba(poidsProba,
        {make_shared<Condition>(PbSante::C_SANTE, PbSante::MORT, Comparateur::c_Egal)});
    return cond;
}
