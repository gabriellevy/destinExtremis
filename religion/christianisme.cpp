#include "christianisme.h"
#include "../destinLib/abs/effet.h"
#include "../destinLib/abs/evt.h"
#include "../destinLib/gen/genevt.h"
#include "../destinLib/aleatoire.h"
#include "../destinLib/abs/selectionneurdenoeud.h"
#include "religion/religion.h"
#include "extremis.h"
#include "genviehumain.h"
#include "socio_eco/metier.h"
#include "socio_eco/economieevt.h"
#include <memory>

using std::make_shared;

// valeurs de Metier::C_TITRE :
QString Christianisme::EVEQUE = "Évèque";

Christianisme::Christianisme(int indexEvt):GenerateurNoeudsProbables (indexEvt)
{
    double tmp_Modificateur = 0.0;
    switch (indexEvt) {
    case 0 : {
        m_Nom = "Nomination comme évèque";
        m_Description = "Pour vos fortes compétences et votre ancienneté, et pour votre foi bien sûr, vous êtes nommé évèque.";
        m_ConditionSelecteurProba = make_shared<Condition>(0.01 + tmp_Modificateur, p_Relative);
        m_Conditions.push_back(Religion::AjouterCondACetteReligion(Religion::CHRETIEN));
        m_Conditions.push_back(make_shared<Condition>(Metier::PRETRE, "5", Comparateur::c_Superieur));
        m_Conditions.push_back(make_shared<Condition>(Metier::C_TITRE, Christianisme::EVEQUE, Comparateur::c_Different));
        this->m_ModificateursCaracs[Metier::C_TITRE] = Christianisme::EVEQUE;
        m_Son = "qrc:/sons/croisade/sanctus.mp3";

    }break;
    case 1 : {
        m_Nom = "Don aux pauvres";
        m_Description = "Vous donnez une grande partie de votre argent pour soutenir les pauvres.";
        m_ConditionSelecteurProba = make_shared<Condition>(0.003 + tmp_Modificateur, p_Relative);
        m_ConditionSelecteurProba->AjouterModifProba(0.02, {Trait::GenConditionSiACeTrait(altruiste)});
        m_ConditionSelecteurProba->AjouterModifProba(-0.002, {Trait::GenConditionSiACeTrait(egoiste)});
        m_Conditions.push_back(Religion::AjouterCondACetteReligion(Religion::CHRETIEN));
        m_IncrementeursCaracs[EconomieEvt::C_NIVEAU_ECONOMIQUE] = -1;
        m_Son = "qrc:/sons/croisade/turexgloriae.mp3";
    }break;
    }
}
