#include "economieevt.h"
#include "../destinLib/abs/effet.h"
#include "../destinLib/abs/evt.h"
#include "../destinLib/gen/genevt.h"
#include "../destinLib/abs/selectionneurdenoeud.h"
#include "extremis.h"
#include "genviehumain.h"
#include "metier.h"
#include "../destinLib/aleatoire.h"
#include "humain.h"
#include "socio_eco/crime.h"

QString EconomieEvt::C_NIVEAU_ECONOMIQUE = "Niveau économique";

using std::make_shared;

EconomieEvt::EconomieEvt(int indexEvt):GenerateurNoeudsProbables (indexEvt)
{
    double tmp_Modificateur = 0.0;
    switch (indexEvt) {
    case 0 : {
        m_Nom = "bon travail";
        m_ConditionSelecteurProba = make_shared<Condition>(0.03 + tmp_Modificateur, p_Relative);
        Trait::AjouterModifProbaSiACeTrait(m_ConditionSelecteurProba.get(), 0.01, ambitieux);
        Trait::AjouterModifProbaSiACeTrait(m_ConditionSelecteurProba.get(), 0.01, travailleur);
        // plus la compétence est haute plus il  a de chances de réussir
        m_ConditionSelecteurProba->AjouterModifProba(0.01,
            { make_shared<Condition>(Metier::C_COMPETENCE_METIER, "5", Comparateur::c_SuperieurEgal)}
        );
        m_ConditionSelecteurProba->AjouterModifProba(0.01,
            { make_shared<Condition>(Metier::C_COMPETENCE_METIER, "6", Comparateur::c_SuperieurEgal)}
        );
        m_ConditionSelecteurProba->AjouterModifProba(0.01,
            { make_shared<Condition>(Metier::C_COMPETENCE_METIER, "7", Comparateur::c_SuperieurEgal)}
        );
        m_ConditionSelecteurProba->AjouterModifProba(0.01,
            { make_shared<Condition>(Metier::C_COMPETENCE_METIER, "8", Comparateur::c_SuperieurEgal)}
        );
        m_ConditionSelecteurProba->AjouterModifProba(0.01,
            { make_shared<Condition>(Metier::C_COMPETENCE_METIER, "9", Comparateur::c_SuperieurEgal)}
        );
        m_ConditionSelecteurProba->AjouterModifProba(0.01,
            { make_shared<Condition>(Metier::C_COMPETENCE_METIER, "10", Comparateur::c_SuperieurEgal)}
        );
        m_Description = "Votre excellent travail est apprécié de tous.";
        m_IncrementeursCaracs[EconomieEvt::C_NIVEAU_ECONOMIQUE] = 1;
        m_Conditions.push_back(Metier::AjouterConditionSiAMetier());
        Extremis::AjouterConditionSiActif(m_Conditions);

    }break;
    case 1 : {
        m_Nom = "mauvais travail";
        m_ConditionSelecteurProba = make_shared<Condition>(0.02 - tmp_Modificateur, p_Relative);
        Trait::AjouterModifProbaSiACeTrait(m_ConditionSelecteurProba.get(), 0.005, maladroit);
        Trait::AjouterModifProbaSiACeTrait(m_ConditionSelecteurProba.get(), 0.005, paresseux);
        // plus la compétence est basse plus il  a de chances de se planter
        m_ConditionSelecteurProba->AjouterModifProba(0.005,
            { make_shared<Condition>(Metier::C_COMPETENCE_METIER, "4", Comparateur::c_InferieurEgal)}
        );
        m_ConditionSelecteurProba->AjouterModifProba(0.005,
            { make_shared<Condition>(Metier::C_COMPETENCE_METIER, "3", Comparateur::c_InferieurEgal)}
        );
        m_ConditionSelecteurProba->AjouterModifProba(0.005,
            { make_shared<Condition>(Metier::C_COMPETENCE_METIER, "2", Comparateur::c_InferieurEgal)}
        );
        m_ConditionSelecteurProba->AjouterModifProba(0.005,
            { make_shared<Condition>(Metier::C_COMPETENCE_METIER, "1", Comparateur::c_InferieurEgal)}
        );
        m_Description = "Vos nombreuses gaffes au travail mettent votre carrière en danger.";
        m_IncrementeursCaracs[EconomieEvt::C_NIVEAU_ECONOMIQUE] = -1;
        m_Conditions.push_back(Metier::AjouterConditionSiAMetier());
        Extremis::AjouterConditionSiActif(m_Conditions);

    }break;
    case 2 : {
        m_Nom = "montée en compétence";
        m_ConditionSelecteurProba = make_shared<Condition>(0.01, p_Relative);
        m_Description = "L'expérience aidant vous êtes de plus en plus compétent dans votre métier.";
        m_IncrementeursCaracs[Metier::C_COMPETENCE_METIER] = 1;
        m_CallbackDisplay = [] {
            Humain* hum = Humain::GetHumainJoue();
            QString metier = hum->GetValeurCarac(Metier::C_METIER);
            int nivMetier = hum->GetValeurCaracAsInt(metier) + 1;
            hum->SetValeurACaracId(Metier::C_COMPETENCE_METIER, nivMetier);
            hum->SetValeurACaracId(metier, nivMetier);
        };
        m_Conditions.push_back(Metier::AjouterConditionSiAMetier());
        Extremis::AjouterConditionSiActif(m_Conditions);
    }
    }
}

shared_ptr<Condition> EconomieEvt::AjouterConditionSiNiveauEconomiqueSuperieurA(int niv)
{
    return make_shared<Condition>(EconomieEvt::C_NIVEAU_ECONOMIQUE, QString::number(niv), Comparateur::c_Superieur);
}
