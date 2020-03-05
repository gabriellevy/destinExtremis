#include "economieevt.h"
#include "../destinLib/abs/effet.h"
#include "../destinLib/abs/evt.h"
#include "../destinLib/gen/genevt.h"
#include "../destinLib/abs/selectionneurdenoeud.h"
#include "extremis.h"
#include "genviehumain.h"
#include "metier.h"
#include "../destinLib/aleatoire.h"

QString EconomieEvt::C_NIVEAU_ECONOMIQUE = "Niveau économique";

EconomieEvt::EconomieEvt(int indexEvt):GenerateurNoeudsProbables (indexEvt)
{
    switch (indexEvt) {
    case 0 : {
        m_Nom = "bon travail";
        m_ConditionSelecteurProba = make_shared<Condition>(0.03, p_Relative);
        m_Description = "Votre excellent travail est apprécié de tous.";
        m_IncrementeursCaracs[EconomieEvt::C_NIVEAU_ECONOMIQUE] = 1;
        m_Conditions.push_back(Metier::AjouterConditionSiAMetier());

    }break;
    case 1 : {
        m_Nom = "mauvais travail";
        m_ConditionSelecteurProba = make_shared<Condition>(0.02, p_Relative);
        m_Description = "Vos nombreuses gaffes au travail mettent votre carrière en danger.";
        m_IncrementeursCaracs[EconomieEvt::C_NIVEAU_ECONOMIQUE] = -1;
        m_Conditions.push_back(Metier::AjouterConditionSiAMetier());

    }break;
    }
}

shared_ptr<Condition> EconomieEvt::AjouterConditionSiNiveauEconomiqueSuperieurA(int niv)
{
    return make_shared<Condition>(EconomieEvt::C_NIVEAU_ECONOMIQUE, QString::number(niv), Comparateur::c_Superieur);
}
