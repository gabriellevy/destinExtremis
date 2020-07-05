#include "classesociale.h"
#include "../destinLib/abs/effet.h"
#include "../destinLib/abs/evt.h"
#include "../destinLib/gen/genevt.h"
#include "../destinLib/abs/selectionneurdenoeud.h"
#include "extremis.h"
#include "genviehumain.h"
#include "metier.h"
#include "../destinLib/aleatoire.h"
#include "economieevt.h"
#include "humanite/pbsante.h"


QString ClasseSociale::MISERABLES = "Misérable";//"Misérable";
QString ClasseSociale::PAUVRES = "Pauvre";//"Pauvre";
QString ClasseSociale::CLASSE_MOYENNE = "Classe moyenne";//"Classe moyenne";
QString ClasseSociale::INFLUENTS = "Classe dominante";//"Classe dominante";
QString ClasseSociale::MAITRES = "Classe dirigeante";//"Classe dirigeante";

QVector<QString> ClasseSociale::CLASSES_SOCIALES = {
    MISERABLES,
    PAUVRES,
    CLASSE_MOYENNE,
    INFLUENTS,
    MAITRES
};

ClasseSociale::ClasseSociale(int indexEvt):GenerateurNoeudsProbables (indexEvt)
{
    double modificateur = 0.0;
    switch (indexEvt) {
    case 0 : {
        m_Nom = "promotion classe sociale des misérables vers pauvres";
        m_ConditionSelecteurProba = make_shared<Condition>(0.02 + modificateur, p_Relative);
        m_Description = "Vous n'êtes pas riche mais vous êtes moins misérables, vous vivez moins au jour le jour.";
        m_ModificateursCaracs[EconomieEvt::C_NIVEAU_ECONOMIQUE] = "0";
        m_ModificateursCaracs[ClasseSociale::C_CLASSE_SOCIALE] = ClasseSociale::PAUVRES;
        m_Conditions.push_back(make_shared<Condition>(EconomieEvt::C_NIVEAU_ECONOMIQUE, "10", Comparateur::c_SuperieurEgal));
        m_Conditions.push_back(ClasseSociale::GenConditionSiDeCetteClasseSociale(ClasseSociale::MISERABLES));

    }break;
    case 1 : {
        m_Nom = "promotion classe sociale des pauvres vers moyenne";
        m_ConditionSelecteurProba = make_shared<Condition>(0.02 + modificateur, p_Relative);
        m_Description = "Vous avez amassé une telle fortune que vous parvenez à vous hisser dans la classe moyenne.";
        m_ModificateursCaracs[EconomieEvt::C_NIVEAU_ECONOMIQUE] = "0";
        m_ModificateursCaracs[ClasseSociale::C_CLASSE_SOCIALE] = ClasseSociale::CLASSE_MOYENNE;
        m_Conditions.push_back(make_shared<Condition>(EconomieEvt::C_NIVEAU_ECONOMIQUE, "10", Comparateur::c_SuperieurEgal));
        m_Conditions.push_back(ClasseSociale::GenConditionSiDeCetteClasseSociale(ClasseSociale::PAUVRES));

    }break;
    case 2 : {
        m_Nom = "promotion classe sociale des moyens vers influents";
        m_ConditionSelecteurProba = make_shared<Condition>(0.02 + modificateur, p_Relative);
        m_Description = "Vous avez amassé une telle fortune et noué tellement de contacts avec les classes dirigeants "
                "que vous parvenez à vous hisser parmi les dominants de la société.";
        m_ModificateursCaracs[EconomieEvt::C_NIVEAU_ECONOMIQUE] = "0";
        m_ModificateursCaracs[ClasseSociale::C_CLASSE_SOCIALE] = ClasseSociale::INFLUENTS;
        m_Conditions.push_back(make_shared<Condition>(EconomieEvt::C_NIVEAU_ECONOMIQUE, "10", Comparateur::c_SuperieurEgal));
        m_Conditions.push_back(ClasseSociale::GenConditionSiDeCetteClasseSociale(ClasseSociale::CLASSE_MOYENNE));

    }break;
    case 3 : {
        m_Nom = "promotion classe sociale des influents vers dominants";
        m_ConditionSelecteurProba = make_shared<Condition>(0.02 + modificateur, p_Relative);
        m_Description = "Vous avez amassé une telle fortune que vous atteignez le petit nombre des ultra riches. ";
        m_ModificateursCaracs[EconomieEvt::C_NIVEAU_ECONOMIQUE] = "0";
        m_ModificateursCaracs[ClasseSociale::C_CLASSE_SOCIALE] = ClasseSociale::MAITRES;
        m_Conditions.push_back(make_shared<Condition>(EconomieEvt::C_NIVEAU_ECONOMIQUE, "10", Comparateur::c_SuperieurEgal));
        m_Conditions.push_back(ClasseSociale::GenConditionSiDeCetteClasseSociale(ClasseSociale::INFLUENTS));

    }break;
    case 4 : {
        m_Nom = "descente classe sociale des pauvres vers misérables";
        m_ConditionSelecteurProba = make_shared<Condition>(0.02 + modificateur, p_Relative);
        m_Description = "Vous avez accumulé tant d'échecs que vous vous retrouvez dans la misère la plus totale.";
        m_ModificateursCaracs[EconomieEvt::C_NIVEAU_ECONOMIQUE] = "0";
        m_ModificateursCaracs[ClasseSociale::C_CLASSE_SOCIALE] = ClasseSociale::MISERABLES;
        m_Conditions.push_back(make_shared<Condition>(EconomieEvt::C_NIVEAU_ECONOMIQUE, "-10", Comparateur::c_InferieurEgal));
        m_Conditions.push_back(ClasseSociale::GenConditionSiDeCetteClasseSociale(ClasseSociale::PAUVRES));

    }break;
    case 5 : {
        m_Nom = "descente classe sociale des moyens vers pauvres";
        m_ConditionSelecteurProba = make_shared<Condition>(0.02 + modificateur, p_Relative);
        m_Description = "Vous avez accumulé tant d'échecs que vous vous retrouvez dans la pauvreté.";
        m_ModificateursCaracs[EconomieEvt::C_NIVEAU_ECONOMIQUE] = "0";
        m_ModificateursCaracs[ClasseSociale::C_CLASSE_SOCIALE] = ClasseSociale::PAUVRES;
        m_Conditions.push_back(make_shared<Condition>(EconomieEvt::C_NIVEAU_ECONOMIQUE, "-10", Comparateur::c_InferieurEgal));
        m_Conditions.push_back(ClasseSociale::GenConditionSiDeCetteClasseSociale(ClasseSociale::CLASSE_MOYENNE));

    }break;
    case 6 : {
        m_Nom = "descente classe sociale des influents vers moyens";
        m_ConditionSelecteurProba = make_shared<Condition>(0.02 + modificateur, p_Relative);
        m_Description = "Vous avez accumulé tant d'échecs que vous vous retrouvez expulsé de votre maison noble et déshonoré. "
                "Vous allez devoir maintenant survivre parmi les classes inférieures.";
        m_ModificateursCaracs[EconomieEvt::C_NIVEAU_ECONOMIQUE] = "0";
        m_ModificateursCaracs[ClasseSociale::C_CLASSE_SOCIALE] = ClasseSociale::CLASSE_MOYENNE;
        m_Conditions.push_back(make_shared<Condition>(EconomieEvt::C_NIVEAU_ECONOMIQUE, "-10", Comparateur::c_InferieurEgal));
        m_Conditions.push_back(ClasseSociale::GenConditionSiDeCetteClasseSociale(ClasseSociale::INFLUENTS));

    }break;
    case 7 : {
        m_Nom = "descente classe sociale des maîtres vers influents";
        m_ConditionSelecteurProba = make_shared<Condition>(0.02 + modificateur, p_Relative);
        m_Description = "Jadis parmi les êtres les plus puissants du monde vous êtes rejeté du cercle des 1% par vos échecs et redevenez un homme encore riche mais secondaire.";
        m_ModificateursCaracs[EconomieEvt::C_NIVEAU_ECONOMIQUE] = "0";
        m_ModificateursCaracs[ClasseSociale::C_CLASSE_SOCIALE] = ClasseSociale::INFLUENTS;
        m_Conditions.push_back(make_shared<Condition>(EconomieEvt::C_NIVEAU_ECONOMIQUE, "-10", Comparateur::c_InferieurEgal));
        m_Conditions.push_back(ClasseSociale::GenConditionSiDeCetteClasseSociale(ClasseSociale::MAITRES));

    }break;
    case 8 : {
        m_Nom = "mort de pauvre misérable";
        m_ConditionSelecteurProba = make_shared<Condition>(0.1 + modificateur, p_Relative);
        m_Description = "Plus possible de supporter l'horrible vie que vous menez. La volonté vous quitte, vous mourrez de froid et de faim.";
        m_ModificateursCaracs[PbSante::C_SANTE] = PbSante::MORT;
        m_Conditions.push_back(make_shared<Condition>(EconomieEvt::C_NIVEAU_ECONOMIQUE, "-10", Comparateur::c_InferieurEgal));
        m_Conditions.push_back(ClasseSociale::GenConditionSiDeCetteClasseSociale(ClasseSociale::MISERABLES));
    }break;
    case 9 : {
        m_Nom = "misérable perd gros";
        m_ConditionSelecteurProba = make_shared<Condition>(0.1 + modificateur, p_Relative);
        m_Description = "Les privations que vous subissez vous font maigrir.";
        m_ModificateursCaracs[Trait::GetNomTrait(gros)] = "";
        m_Conditions.push_back(ClasseSociale::GenConditionSiDeCetteClasseSociale(ClasseSociale::MISERABLES));
        m_Conditions.push_back(Trait::GenConditionSiACeTrait(gros));
    }break;
    case 10 : {
        m_Nom = "misérable gagne maigre";
        m_ConditionSelecteurProba = make_shared<Condition>(0.1 + modificateur, p_Relative);
        m_Description = "Les privations que vous subissez vous font maigrir.";
        m_ModificateursCaracs[Trait::GetNomTrait(maigre)] = "1";
        m_Conditions.push_back(ClasseSociale::GenConditionSiDeCetteClasseSociale(ClasseSociale::MISERABLES));
        m_Conditions.push_back(Trait::GenConditionSiAPasCeTrait(maigre));
    }break;
    }
}

shared_ptr<Condition> ClasseSociale::GenConditionSiDeCetteClasseSociale(QString classeSociale)
{
    shared_ptr<Condition> cond = make_shared<Condition>(ClasseSociale::C_CLASSE_SOCIALE, classeSociale, Comparateur::c_Egal);
    return cond;
}

QString ClasseSociale::C_CLASSE_SOCIALE = "Classe sociale";

shared_ptr<Condition> ClasseSociale::AjouterConditionSiClasseSocialeSuperieureA(int classeSociale)
{
    shared_ptr<Condition> cond = make_shared<Condition>(ClasseSociale::C_CLASSE_SOCIALE, QString::number(classeSociale), Comparateur::c_Superieur);
    return cond;
}

shared_ptr<Condition> ClasseSociale::AjouterConditionSiClasseSocialeSuperieureA(QString classeSociale)
{
    shared_ptr<Condition> cond = make_shared<Condition>(ClasseSociale::C_CLASSE_SOCIALE, classeSociale, Comparateur::c_Superieur);
    return cond;
}

QString ClasseSociale::GetClasseSocialeAleatoire()
{
    double proba = Aleatoire::GetAl()->Entre0Et1();
    if ( proba < 0.01)
        return ClasseSociale::MISERABLES;
    else if (proba < 0.6)
        return ClasseSociale::PAUVRES;
    else if ( proba < 0.98)
        return ClasseSociale::CLASSE_MOYENNE;
    else if ( proba < 0.999)
        return ClasseSociale::INFLUENTS;
    else {
        return ClasseSociale::MAITRES;
    }
}

