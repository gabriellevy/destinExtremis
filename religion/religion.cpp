#include "religion.h"
#include "../destinLib/abs/effet.h"
#include "../destinLib/abs/evt.h"
#include "../destinLib/gen/genevt.h"
#include "../destinLib/aleatoire.h"
#include "../destinLib/abs/selectionneurdenoeud.h"
#include "extremis.h"
#include "genviehumain.h"
#include "socio_eco/metier.h"
#include <memory>

using std::make_shared;

Religion::Religion(int indexEvt):GenerateurNoeudsProbables (indexEvt)
{
    double tmp_Modificateur = 0.0;
    switch (indexEvt) {
    case 0 : {
        m_Nom = "Nomination comme évèque";
        m_Description = "Pour vos fortes compétences et votre ancienneté, et pour votre foi bien sûr, vous êtes nommé évèque.";
        m_ConditionSelecteurProba = make_shared<Condition>(0.01 + tmp_Modificateur, p_Relative);
        m_Conditions.push_back(Religion::AjouterCondACetteReligion(Religion::CHRETIEN));
        m_Conditions.push_back(make_shared<Condition>(Metier::PRETRE, "5", Comparateur::c_Superieur));
        m_Conditions.push_back(make_shared<Condition>(Metier::C_TITRE, Religion::EVEQUE, Comparateur::c_Different));
        this->m_ModificateursCaracs[Metier::C_TITRE] = Religion::EVEQUE;
        m_Son = "qrc:/sons/croisade/sanctus.mp3";

    }break;
    }
}


// caracs liées :
QString Religion::C_RELIGION = "Religion";
QString Religion::C_FOI = "Foi"; // niveau de foi dans sa religion (1 à 10)
QString Religion::C_MIRACLE = "Miracles"; //capacité à créer des miracles (1 à 10)
// valeurs de C_RELIGION "" = aucune
QString Religion::CHRETIEN = ":/images/religion/Chretien.jpg";
QString Religion::ATHEE = ":/images/religion/athee.jpg"; // différent de "" car l'athée a développé une aversion à la religion, il sera dur à reconvertir
// valeurs de Metier::C_TITRE :
QString Religion::EVEQUE = "Évèque";



QString Religion::GetNomReligion(QString religion)
{
    if ( religion == Religion::CHRETIEN) return "chrétien";
    if ( religion == Religion::ATHEE) return "athée";
    return "????" + religion;
}

std::shared_ptr<Condition> Religion::AjouterCondACetteReligion(QString religion)
{
    return make_shared<Condition>(Religion::C_RELIGION, religion, Comparateur::c_Egal);
}

void Religion::ModifierEffetEnEffetConversion(std::shared_ptr<Effet> &effet, QString religion, int ajoutEnFoi, bool convertitAthees)
{
    effet->m_Conditions.push_back(make_shared<Condition>(Religion::C_RELIGION, religion, Comparateur::c_Different));//on ne s'auto convertit pas dans la même religion
    effet->AjouterChangeurDeCarac(Religion::C_RELIGION, religion);
    effet->AjouterAjouteurACarac(Religion::C_FOI, QString::number(ajoutEnFoi));
    if (!convertitAthees)
        effet->m_Conditions.push_back(make_shared<Condition>(Religion::C_RELIGION, Religion::ATHEE, Comparateur::c_Different)); // on part du principe que les athées purs et durs sont inconvertibles
    effet->m_Texte += "\n Vous devenez " + Religion::GetNomReligion(religion) + ".";
}
