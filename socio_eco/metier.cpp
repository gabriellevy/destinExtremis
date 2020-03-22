#include "metier.h"
#include "../destinLib/abs/effet.h"
#include "../destinLib/abs/evt.h"
#include "../destinLib/gen/genevt.h"
#include "../destinLib/abs/selectionneurdenoeud.h"
#include "extremis.h"
#include "genviehumain.h"
#include "socio_eco/crime.h"
#include "humain.h"

QString Metier::C_METIER = "Métier";

QString Metier::INEMPLOYABLE = "Inemployable";
QString Metier::PAYSAN = "Paysan";
QString Metier::MUSICIEN = "Musicien";
QString Metier::POETE = "Poète";
QString Metier::MINEUR = "Mineur";
QString Metier::CHASSEUR_CUEILLEUR_NOMADE = "Chasseur cueilleur nomade";
QString Metier::OUVRIER = "Ouvrier";
QString Metier::FORGERON = "Forgeron";

QMap<QString, Metier*> Metier::METIERS;

Metier::Metier(int indexEvt):GenerateurNoeudsProbables (indexEvt)
{
    double tmpFavoriseur = 0.0; // valeur servant à tester => à mettre à 0 pour un test final
    switch (indexEvt) {
    case 0 : {
        m_Nom = Metier::PAYSAN;
        m_ConditionSelecteurProba = make_shared<Condition>(0.1 - tmpFavoriseur, p_Relative);
        // plus de chances d'êtres paysans sur les mondes agricoles et médiévaux
    }break;
    case 1 : {
        m_Nom = Metier::MUSICIEN;
        m_ConditionSelecteurProba = make_shared<Condition>(0.00005 - tmpFavoriseur, p_Relative);
        Trait::AjouterModifProbaSiACeTrait(m_ConditionSelecteurProba.get(), 0.3, artiste);
        Coterie::AjouterModifProbaSiDeCetteCoterie(m_ConditionSelecteurProba.get(), 0.05, Coterie::CONQUISTADORS);
        Coterie::AjouterModifProbaSiDeCetteCoterie(m_ConditionSelecteurProba.get(), 0.03, Coterie::ELFES);
    }break;
    case 2 : {
        m_Nom = Metier::POETE;
        m_ConditionSelecteurProba = make_shared<Condition>(0.00005 - tmpFavoriseur, p_Relative);
        Trait::AjouterModifProbaSiACeTrait(m_ConditionSelecteurProba.get(), 0.3, artiste);
        Coterie::AjouterModifProbaSiDeCetteCoterie(m_ConditionSelecteurProba.get(), 0.03, Coterie::ELFES);
    }break;
    case 10 : {
        m_Nom = Metier::OUVRIER;
        m_ConditionSelecteurProba = make_shared<Condition>(0.1 - tmpFavoriseur, p_Relative);
        // plus de chances d'êtres ouvrier sur les mondes ruches et forges
    }break;
    case 11 : {
        m_Nom = Metier::CHASSEUR_CUEILLEUR_NOMADE;
        m_ConditionSelecteurProba = make_shared<Condition>(0.5 - tmpFavoriseur, p_Relative);
        // uniquement sur les mondes férals
    }break;
    case 12 : {
        m_Nom = Metier::MINEUR;
        m_ConditionSelecteurProba = make_shared<Condition>(0.005 - tmpFavoriseur, p_Relative);
    }break;
    case 13 : {
        m_Nom = Metier::FORGERON;
        m_ConditionSelecteurProba = make_shared<Condition>(0.0005 - tmpFavoriseur, p_Relative);
        Coterie::AjouterModifProbaSiDeCetteCoterie(m_ConditionSelecteurProba.get(), 0.05, Coterie::CONQUISTADORS);
    }break;
}

    if ( m_Description == "" ) {
        m_Description = "Vous êtes maintenant " +
                        m_Nom;
        m_Description += ".";
    }
    m_ModificateursCaracs[C_METIER] = m_Nom;

    m_Conditions.push_back(Metier::AjouterConditionSiAPasMetier());
    m_Conditions.push_back(Crime::AjouterConditionSiLibre());

    if ( m_ConditionSelecteurProba!= nullptr) {
        // si on a moins de 15 ans la proba de s'en voir affecter un est très faible :
        // mais affectation de métier plus rapide sur monde féodal :
        m_ConditionSelecteurProba->AjouterModifProba(-2.3, {make_shared<Condition>(GenVieHumain::AGE, "120", Comparateur::c_Inferieur)});
    }

    METIERS[m_Nom] = this;
}



shared_ptr<Condition> Metier::AjouterConditionSiACeMetier(QString metier)
{
    shared_ptr<Condition> cond = make_shared<Condition>(Metier::C_METIER, metier, Comparateur::c_Egal);
    return cond;
}

shared_ptr<Condition> Metier::AjouterConditionSiAMetier()
{
    shared_ptr<Condition> cond = make_shared<Condition>(Metier::C_METIER, "", Comparateur::c_Different);
    return cond;
}

shared_ptr<Condition> Metier::AjouterConditionSiAPasMetier()
{
    shared_ptr<Condition> cond = make_shared<Condition>(Metier::C_METIER, "", Comparateur::c_Egal);
    return cond;
}
