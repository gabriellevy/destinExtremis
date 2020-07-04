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
QString Metier::C_TITRE = "Titre";
QString Metier::C_COMPETENCE_METIER = "Compétence métier";

QString Metier::INEMPLOYABLE = "Inemployable";
QString Metier::PAYSAN = "Paysan";
QString Metier::MUSICIEN = "Musicien";
QString Metier::CARTOGRAPHE = "Cartographe";
QString Metier::MARCHAND = "Marchand";
QString Metier::POETE = "Poète";
QString Metier::MINEUR = "Mineur";
QString Metier::PRETRE = "Prêtre";
QString Metier::OUVRIER = "Ouvrier";
QString Metier::POLITIQUE = "Politique";
QString Metier::FORGERON = "Forgeron";
QString Metier::ALCHIMISTE = "Alchimiste";
QString Metier::MEDECIN = "Médecin";
QString Metier::TUEUR_DE_MONSTRE = "Tueur de monstres";
QString Metier::ARCHITECTE = "Architecte";
QString Metier::PARASITE = "Parasite";
QString Metier::GUERRIER = "Guerrier";
QString Metier::CONDUCTEUR = "Conducteur";
QString Metier::PILOTE = "Pilote";
QString Metier::INFORMATICIEN = "Informaticien";
QString Metier::CYBERNETICIEN = "Cybernéticien";
QString Metier::GENETICIEN = "Généticien";
QString Metier::COMMERCIAL = "Commercial";
QString Metier::POLICIER = "Policier";
QString Metier::VIGILE = "Vigile";
QString Metier::BANQUIER = "Banquier";
QString Metier::GARDE_DU_CORPS = "Garde du corps";

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
        m_ConditionSelecteurProba = make_shared<Condition>(0.0005 - tmpFavoriseur, p_Relative);
        Trait::AjouterModifProbaSiACeTrait(m_ConditionSelecteurProba.get(), 0.3, artiste);
        Coterie::AjouterModifProbaSiDeCetteCoterie(m_ConditionSelecteurProba.get(), 0.05, Coterie::CONQUISTADORS);
        Coterie::AjouterModifProbaSiDeCetteCoterie(m_ConditionSelecteurProba.get(), 0.03, Coterie::ELFES);
    }break;
    case 2 : {
        m_Nom = Metier::POETE;
        m_ConditionSelecteurProba = make_shared<Condition>(0.0005 - tmpFavoriseur, p_Relative);
        Trait::AjouterModifProbaSiACeTrait(m_ConditionSelecteurProba.get(), 0.3, artiste);
        Coterie::AjouterModifProbaSiDeCetteCoterie(m_ConditionSelecteurProba.get(), 0.03, Coterie::ELFES);
    }break;
    case 3 : {
        m_Nom = Metier::ALCHIMISTE;
        m_ConditionSelecteurProba = make_shared<Condition>(0.0001 - tmpFavoriseur, p_Relative);
        Coterie::AjouterModifProbaSiDeCetteCoterie(m_ConditionSelecteurProba.get(), 0.03, Coterie::ELFES);
        Coterie::AjouterModifProbaSiDeCetteCoterie(m_ConditionSelecteurProba.get(), 0.03, Coterie::CELTES);
    }break;
    case 4 : {
        m_Nom = Metier::MEDECIN;
        m_ConditionSelecteurProba = make_shared<Condition>(0.0001 - tmpFavoriseur, p_Relative);
    }break;
    case 5 : {
        m_Nom = Metier::CARTOGRAPHE;
        m_ConditionSelecteurProba = make_shared<Condition>(0.0001 - tmpFavoriseur, p_Relative);
    }break;
    case 6 : {
        m_Nom = Metier::MARCHAND;
        m_ConditionSelecteurProba = make_shared<Condition>(0.01 - tmpFavoriseur, p_Relative);
    }break;
    case 7 : {
        m_Nom = Metier::ARCHITECTE;
        m_ConditionSelecteurProba = make_shared<Condition>(0.001 - tmpFavoriseur, p_Relative);
    }break;
    case 8 : {
        m_Nom = Metier::TUEUR_DE_MONSTRE;
        m_ConditionSelecteurProba = make_shared<Condition>(0.0 - tmpFavoriseur, p_Relative);
    }break;
    case 9 : {
        m_Nom = Metier::PARASITE;
        m_ConditionSelecteurProba = make_shared<Condition>(0.01 - tmpFavoriseur, p_Relative);
        Trait::AjouterModifProbaSiACeTrait(m_ConditionSelecteurProba.get(), 0.01, paresseux);
        Trait::AjouterModifProbaSiACeTrait(m_ConditionSelecteurProba.get(), 0.03, sournois);
        Trait::AjouterModifProbaSiACeTrait(m_ConditionSelecteurProba.get(), 0.01, beau);
        Trait::AjouterModifProbaSiACeTrait(m_ConditionSelecteurProba.get(), 0.02, charmeur);
    }break;
    case 10 : {
        m_Nom = Metier::OUVRIER;
        m_ConditionSelecteurProba = make_shared<Condition>(0.1 - tmpFavoriseur, p_Relative);
    }break;
    case 11 : {
        m_Nom = Metier::PRETRE;
        m_ConditionSelecteurProba = make_shared<Condition>(0.001 - tmpFavoriseur, p_Relative);
    }break;
    case 12 : {
        m_Nom = Metier::MINEUR;
        m_ConditionSelecteurProba = make_shared<Condition>(0.005 - tmpFavoriseur, p_Relative);
    }break;
    case 13 : {
        m_Nom = Metier::FORGERON;
        m_ConditionSelecteurProba = make_shared<Condition>(0.0005 - tmpFavoriseur, p_Relative);
    }break;
    case 14 : {
        m_Nom = Metier::GUERRIER;
        m_ConditionSelecteurProba = make_shared<Condition>(0.005 - tmpFavoriseur, p_Relative);
    }break;
    case 15 : {
        m_Nom = Metier::CONDUCTEUR;
        m_ConditionSelecteurProba = make_shared<Condition>(0.01 - tmpFavoriseur, p_Relative);
    }break;
    case 16 : {
        m_Nom = Metier::POLITIQUE;
        m_ConditionSelecteurProba = make_shared<Condition>(0.002 - tmpFavoriseur, p_Relative);
    }break;
    case 17 : {
        m_Nom = Metier::PILOTE;
        m_ConditionSelecteurProba = make_shared<Condition>(0.0 - tmpFavoriseur, p_Relative);
    }break;
    case 18 : {
        m_Nom = Metier::INFORMATICIEN;
        m_ConditionSelecteurProba = make_shared<Condition>(0.0 - tmpFavoriseur, p_Relative);
    }break;
    case 19 : {
        m_Nom = Metier::CYBERNETICIEN;
        m_ConditionSelecteurProba = make_shared<Condition>(0.0 - tmpFavoriseur, p_Relative);
    }break;
    case 20 : {
        m_Nom = Metier::GENETICIEN;
        m_ConditionSelecteurProba = make_shared<Condition>(0.0 - tmpFavoriseur, p_Relative);
    }break;
    case 21 : {
        m_Nom = Metier::COMMERCIAL;
        m_ConditionSelecteurProba = make_shared<Condition>(0.005 - tmpFavoriseur, p_Relative);
    }break;
    case 22 : {
        m_Nom = Metier::POLICIER;
        m_ConditionSelecteurProba = make_shared<Condition>(0.01 - tmpFavoriseur, p_Relative);
    }break;
    case 23 : {
        m_Nom = Metier::GARDE_DU_CORPS;
        m_ConditionSelecteurProba = make_shared<Condition>(0.0 - tmpFavoriseur, p_Relative);
        Trait::AjouterModifProbaSiACeTrait(m_ConditionSelecteurProba.get(), 0.005, observateur);
        Trait::AjouterModifProbaSiACeTrait(m_ConditionSelecteurProba.get(), 0.005, resistant);
        Trait::AjouterModifProbaSiACeTrait(m_ConditionSelecteurProba.get(), 0.005, fort);
        Trait::AjouterModifProbaSiACeTrait(m_ConditionSelecteurProba.get(), 0.005, grand);
    }break;
    case 24 : {
        m_Nom = Metier::VIGILE;
        m_ConditionSelecteurProba = make_shared<Condition>(0.01 - tmpFavoriseur, p_Relative);
    }break;
    case 25 : {
        m_Nom = Metier::BANQUIER;
        m_ConditionSelecteurProba = make_shared<Condition>(0.01 - tmpFavoriseur, p_Relative);
    }break;
    }
    m_Id = "" + m_Nom;

    if ( m_Description == "" ) {
        m_Description = "Vous êtes maintenant " +
                        m_Nom;
        m_Description += ".";
    }
    m_ModificateursCaracs[C_METIER] = m_Nom;

    // la compétence métier du personnage devient celle de son nouveau métier
    QString nom = m_Nom;
    m_CallbackDisplay = [nom] {
        Humain* hum = Humain::GetHumainJoue();
        hum->SetValeurACaracId(C_COMPETENCE_METIER,
                               hum->GetValeurCaracAsInt(nom));
    };

    m_Conditions.push_back(Metier::AjouterConditionSiAPasMetier());
    Extremis::AjouterConditionSiActif(m_Conditions);

    if ( m_ConditionSelecteurProba!= nullptr) {
        // si on a moins de 15 ans la proba de s'en voir affecter un est très faible :
        // mais affectation de métier plus rapide sur monde féodal :
        m_ConditionSelecteurProba->AjouterModifProba(-2.3, {make_shared<Condition>(GenVieHumain::C_AGE, "120", Comparateur::c_Inferieur)});

        // plus de chances de choisir un métier si on a des compétences de ce métier :
        m_ConditionSelecteurProba->AjouterModifProba(0.2, {make_shared<Condition>(m_Nom, "1", Comparateur::c_SuperieurEgal)});
        m_ConditionSelecteurProba->AjouterModifProba(0.2, {make_shared<Condition>(m_Nom, "2", Comparateur::c_SuperieurEgal)});
        m_ConditionSelecteurProba->AjouterModifProba(0.2, {make_shared<Condition>(m_Nom, "3", Comparateur::c_SuperieurEgal)});
        m_ConditionSelecteurProba->AjouterModifProba(0.1, {make_shared<Condition>(m_Nom, "4", Comparateur::c_SuperieurEgal)});
        m_ConditionSelecteurProba->AjouterModifProba(0.1, {make_shared<Condition>(m_Nom, "5", Comparateur::c_SuperieurEgal)});
        m_ConditionSelecteurProba->AjouterModifProba(0.1, {make_shared<Condition>(m_Nom, "6", Comparateur::c_SuperieurEgal)});
        m_ConditionSelecteurProba->AjouterModifProba(0.1, {make_shared<Condition>(m_Nom, "7", Comparateur::c_SuperieurEgal)});
        m_ConditionSelecteurProba->AjouterModifProba(0.1, {make_shared<Condition>(m_Nom, "8", Comparateur::c_SuperieurEgal)});
        m_ConditionSelecteurProba->AjouterModifProba(0.1, {make_shared<Condition>(m_Nom, "9", Comparateur::c_SuperieurEgal)});
        m_ConditionSelecteurProba->AjouterModifProba(0.1, {make_shared<Condition>(m_Nom, "10", Comparateur::c_SuperieurEgal)});
    }

    // plus de chances d'avoir les métiers liés à notre coterie
    for ( shared_ptr<Coterie> cot: Extremis::COTERIES) {
        for ( QString nomMetier: cot->m_MetiersAssocies) {
            if ( nomMetier == m_Nom) {
                m_ConditionSelecteurProba->AjouterModifProba(
                            0.2,
                            {make_shared<Condition>(Coterie::C_COTERIE, cot->GetNom(), Comparateur::c_Egal)}
                            );
            }
        }
    }

    METIERS[m_Nom] = this;

    // affichage :
    //m_Nom = ("Devenir " + m_Nom);
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
