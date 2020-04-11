#include "crime.h"
#include "../destinLib/abs/effet.h"
#include "../destinLib/abs/evt.h"
#include "../destinLib/gen/genevt.h"
#include "../destinLib/abs/selectionneurdenoeud.h"
#include "extremis.h"
#include "genviehumain.h"
#include "metier.h"
#include "../destinLib/exec/execeffet.h"
#include "../destinLib/aleatoire.h"
#include "classesociale.h"
#include "humanite/pbsante.h"
#include "socio_eco/economieevt.h"
#include "humain.h"

// caracs :
QString Crime::C_CRIMINEL = "Est criminel";
QString Crime::C_GANG = "Gang";
QString Crime::C_MOIS_PRISON = "Mois de prison restants";
//valeurs de criminel : ("" signifie innocent). Note : être jugé innocent même si n est coupable remet en ""
QString Crime::DELINQUANT = "Délinquant";
QString Crime::CRIMINEL = "Criminel";
// valeurs de GenVieHumain::C_LIBERTE :
QString Crime::CAPTURE_POLICE = "Capturé par la police";
QString Crime::PRISON = "En prison";

Crime::Crime(int indexEvt):GenerateurNoeudsProbables (indexEvt)
{
    double tmp_Modificateur = 1.0; //pour les tests (doit être à 0 en prod)
    switch (indexEvt) {
    case 0 : { // misérable qui devient voleur/délinquant
        m_Nom = "devient_voleur_" + ClasseSociale::PAUVRES;
        m_ConditionSelecteurProba = make_shared<Condition>(0.01 + tmp_Modificateur, p_Relative);
        Trait::AjouterModifProbaSiACeTrait(m_ConditionSelecteurProba.get(), 0.01, paresseux);
        Trait::AjouterModifProbaSiACeTrait(m_ConditionSelecteurProba.get(), 0.01, cupide);
        Trait::AjouterModifProbaSiACeTrait(m_ConditionSelecteurProba.get(), 0.01, opportuniste);
        Trait::AjouterModifProbaSiACeTrait(m_ConditionSelecteurProba.get(), 0.01, menteur);
        Trait::AjouterModifProbaSiACeTrait(m_ConditionSelecteurProba.get(), 0.01, sournois);
        Trait::AjouterModifProbaSiACeTrait(m_ConditionSelecteurProba.get(), -0.01, travailleur);
        Trait::AjouterModifProbaSiACeTrait(m_ConditionSelecteurProba.get(), -0.01, honorable);
        Trait::AjouterModifProbaSiACeTrait(m_ConditionSelecteurProba.get(), -0.01, franc);
        m_Description = "Vous vous mettez à voler à droite à gauche pour survivre";
        m_Conditions.push_back(Crime::AjouterConditionSiJamaisCriminel());
        m_Conditions.push_back(ClasseSociale::AjouterConditionSiCetteClasseSociale(ClasseSociale::MISERABLES));
        m_Conditions.push_back(Crime::AjouterConditionSiLibre());
        m_ModificateursCaracs[Crime::C_CRIMINEL] = Crime::DELINQUANT;

    }break;
    case 1 : {
        m_Nom = "devient_" + Crime::CRIMINEL + "_violeur";
        m_ConditionSelecteurProba = make_shared<Condition>(0.0001 + tmp_Modificateur, p_Relative);
        Trait::AjouterModifProbaSiACeTrait(m_ConditionSelecteurProba.get(), 0.01, cruel);
        Trait::AjouterModifProbaSiACeTrait(m_ConditionSelecteurProba.get(), 0.01, pervers_sexuel);
        Trait::AjouterModifProbaSiACeTrait(m_ConditionSelecteurProba.get(), 0.01, sournois);
        Trait::AjouterModifProbaSiACeTrait(m_ConditionSelecteurProba.get(), -0.01, honorable);
        Trait::AjouterModifProbaSiACeTrait(m_ConditionSelecteurProba.get(), -0.01, franc);
        m_Conditions.push_back(Crime::AjouterConditionSiLibre());
        m_Description = "Vos perversions vous poussent à devenir un violeur de plus en plus dépravé.";
        m_ModificateursCaracs[Crime::C_CRIMINEL] = Crime::CRIMINEL;

    }break;
    case 2 : {
        m_Nom = "devient_" + Crime::CRIMINEL + "_braqueur";
        m_ConditionSelecteurProba = make_shared<Condition>(0.0001 + tmp_Modificateur, p_Relative);
        Trait::AjouterModifProbaSiACeTrait(m_ConditionSelecteurProba.get(), 0.01, aventureux);
        Trait::AjouterModifProbaSiACeTrait(m_ConditionSelecteurProba.get(), 0.01, cupide);
        Trait::AjouterModifProbaSiACeTrait(m_ConditionSelecteurProba.get(), 0.01, opportuniste);
        Trait::AjouterModifProbaSiACeTrait(m_ConditionSelecteurProba.get(), 0.01, menteur);
        Trait::AjouterModifProbaSiACeTrait(m_ConditionSelecteurProba.get(), 0.01, sournois);
        Trait::AjouterModifProbaSiACeTrait(m_ConditionSelecteurProba.get(), -0.01, travailleur);
        Trait::AjouterModifProbaSiACeTrait(m_ConditionSelecteurProba.get(), -0.01, honorable);
        Trait::AjouterModifProbaSiACeTrait(m_ConditionSelecteurProba.get(), -0.01, franc);
        m_Description = "Votre soif de richesse fait de vous un criminel de plus en plus violent.";
        m_Conditions.push_back(Crime::AjouterConditionSiLibre());
        m_ModificateursCaracs[Crime::C_CRIMINEL] = Crime::CRIMINEL;

    }break;
    case 3 : {
        m_Nom = Crime::CAPTURE_POLICE;
        m_ConditionSelecteurProba = make_shared<Condition>(0.005 + tmp_Modificateur, p_Relative);
        m_Description = "Vous avez été capturé par la police pour vos méfaits.";
        m_Conditions.push_back(
                    make_shared<Condition>(Crime::C_CRIMINEL,
                                  "",
                                  Comparateur::c_Different));
        m_Conditions.push_back(Crime::AjouterConditionSiLibre());
        m_ModificateursCaracs[GenVieHumain::C_LIBERTE] = Crime::CAPTURE_POLICE;
        // perd son métier :
        m_ModificateursCaracs[Metier::C_METIER] = "";
        m_ModificateursCaracs[Metier::C_COMPETENCE_METIER] = "";

    }break;
    case 4 : { // si déjà criminel et au travail
        m_Nom = "Vendeur de drogue";
        m_ConditionSelecteurProba = make_shared<Condition>(0.01 + tmp_Modificateur, p_Relative);
        Trait::AjouterModifProbaSiACeTrait(m_ConditionSelecteurProba.get(), 0.01, cupide);
        Trait::AjouterModifProbaSiACeTrait(m_ConditionSelecteurProba.get(), 0.01, opportuniste);
        Trait::AjouterModifProbaSiACeTrait(m_ConditionSelecteurProba.get(), 0.01, menteur);
        Trait::AjouterModifProbaSiACeTrait(m_ConditionSelecteurProba.get(), 0.01, sournois);
        Trait::AjouterModifProbaSiACeTrait(m_ConditionSelecteurProba.get(), -0.01, honorable);
        Trait::AjouterModifProbaSiACeTrait(m_ConditionSelecteurProba.get(), -0.01, franc);
        m_Description = "Vous mettez en place un petit réseau de revente de drogue sur votre lieu "
                "de travail qui vous fait très bien voir de vos collègues.";
        m_Conditions.push_back(Crime::AjouterConditionSiLibre());
        m_Conditions.push_back(Metier::AjouterConditionSiAMetier());
        m_Conditions.push_back(Crime::AjouterConditionSiMalhonnete());
        m_ModificateursCaracs[Crime::C_CRIMINEL] = Crime::DELINQUANT;
        m_IncrementeursCaracs[EconomieEvt::C_NIVEAU_ECONOMIQUE] = 3;

    }break;
    case 5 : {
        m_Nom = "Jugement !";
        m_Description = "Le jour de votre procès est venu. \n";
        m_ConditionSelecteurProba = make_shared<Condition>(0.1 + tmp_Modificateur, p_Relative);
        m_Conditions.push_back(
             make_shared<Condition>(GenVieHumain::C_LIBERTE, Crime::CAPTURE_POLICE, Comparateur::c_Egal));
        m_CallbackDisplay = [] {
            Humain* humain = Humain::GetHumainJoue();
            ExecEffet* effet = ExecHistoire::GetExecEffetActuel();
            Crime::PrononcerLaSentence(humain, effet);
        };
    }break;
    case 6 : { // honnête devient petit délinquant par violence et désoeuvrement
        m_Nom = "devient_" + Crime::DELINQUANT + "_" + ClasseSociale::PAUVRES;
        m_ConditionSelecteurProba = make_shared<Condition>(0.002 + tmp_Modificateur, p_Relative);
        Trait::AjouterModifProbaSiACeTrait(m_ConditionSelecteurProba.get(), 0.01, violent);
        Trait::AjouterModifProbaSiACeTrait(m_ConditionSelecteurProba.get(), 0.01, rancunier);
        Trait::AjouterModifProbaSiACeTrait(m_ConditionSelecteurProba.get(), 0.01, cruel);
        Trait::AjouterModifProbaSiACeTrait(m_ConditionSelecteurProba.get(), 0.01, sournois);
        Trait::AjouterModifProbaSiACeTrait(m_ConditionSelecteurProba.get(), -0.01, altruiste);
        Trait::AjouterModifProbaSiACeTrait(m_ConditionSelecteurProba.get(), -0.01, pacifiste);
        Trait::AjouterModifProbaSiACeTrait(m_ConditionSelecteurProba.get(), -0.01, travailleur);
        Trait::AjouterModifProbaSiACeTrait(m_ConditionSelecteurProba.get(), -0.01, honorable);
        m_Description = "Vous prenez l'habitude de vous battre et de voler.";
        m_Conditions.push_back(
                    make_shared<Condition>(Crime::C_CRIMINEL,
                                  "",
                                  Comparateur::c_Egal));
        m_Conditions.push_back(
                    make_shared<Condition>(ClasseSociale::C_CLASSE_SOCIALE,
                                  ClasseSociale::PAUVRES,
                                  Comparateur::c_Egal));
        m_Conditions.push_back(Crime::AjouterConditionSiLibre());
        m_ModificateursCaracs[Crime::C_CRIMINEL] = Crime::DELINQUANT;

    }break;
    case 7 : {
        m_Nom = "joint_" + Crime::C_GANG;
        m_ConditionSelecteurProba = make_shared<Condition>(0.002 + tmp_Modificateur, p_Relative);
        QString gang = Crime::GenererNomGang();
        m_Description = "Vous rejoignez le gang " + gang + ".";
        m_Image = ":/images/crime/gang.PNG";
        m_Conditions.push_back(Crime::AjouterConditionSiDelinquant());
        m_Conditions.push_back(
                    make_shared<Condition>(Crime::C_GANG,
                                  "",
                                  Comparateur::c_Egal));
        m_ModificateursCaracs[Crime::C_GANG] = gang;

    }break;
    case 8 : {
        m_Nom = "Misérable qui devient pauvre par le crime";
        m_ConditionSelecteurProba = make_shared<Condition>(0.001 + tmp_Modificateur, p_Relative);
        Crime::AjouterModificateurDeProbaSiDelinquant(m_ConditionSelecteurProba, 0.01);
        Crime::AjouterModificateurDeProbaSiCriminel(m_ConditionSelecteurProba, 0.01);
        Trait::AjouterModifProbaSiACeTrait(m_ConditionSelecteurProba.get(), 0.01, opportuniste);
        Trait::AjouterModifProbaSiACeTrait(m_ConditionSelecteurProba.get(), -0.01, honorable);
        m_Description = "Par un crime très astucieux vous parvenez à vous enrichir considérablement.";
        m_Conditions.push_back(Crime::AjouterConditionSiLibre());
        m_Conditions.push_back(ClasseSociale::AjouterConditionSiCetteClasseSociale(ClasseSociale::MISERABLES));
        m_ModificateursCaracs[Crime::C_CRIMINEL] = Crime::CRIMINEL;
        m_ModificateursCaracs[ClasseSociale::C_CLASSE_SOCIALE] = ClasseSociale::PAUVRES;

    }break;
    case 9 : {
        m_Nom = "Pauvre qui devient classe moyenne par le crime";
        m_ConditionSelecteurProba = make_shared<Condition>(0.001 + tmp_Modificateur, p_Relative);
        Crime::AjouterModificateurDeProbaSiDelinquant(m_ConditionSelecteurProba, 0.01);
        Crime::AjouterModificateurDeProbaSiCriminel(m_ConditionSelecteurProba, 0.01);
        Trait::AjouterModifProbaSiACeTrait(m_ConditionSelecteurProba.get(), 0.01, opportuniste);
        Trait::AjouterModifProbaSiACeTrait(m_ConditionSelecteurProba.get(), -0.01, honorable);
        m_Description = "Par un crime très astucieux vous parvenez à vous enrichir considérablement.";
        m_Conditions.push_back(Crime::AjouterConditionSiLibre());
        m_Conditions.push_back(ClasseSociale::AjouterConditionSiCetteClasseSociale(ClasseSociale::PAUVRES));
        m_ModificateursCaracs[Crime::C_CRIMINEL] = Crime::CRIMINEL;
        m_ModificateursCaracs[ClasseSociale::C_CLASSE_SOCIALE] = ClasseSociale::CLASSE_MOYENNE;

    }break;

    }
}

void Crime::PrononcerLaSentence(Humain* humain, ExecEffet* execEffet)
{
    QString texte = execEffet->GetEffet()->m_Texte;
    QString imgPath = "";

    int graviteCrime = Aleatoire::GetAl()->EntierInferieurA(7);
    // < 5  = petit délinquant
    // > 10 crime capital

    if ( humain->GetValeurCarac(Crime::C_CRIMINEL) == Crime::CRIMINEL)
        graviteCrime += 4;
    if ( humain->GetValeurCarac(Crime::C_GANG) != "")
        graviteCrime += 2;


    if ( graviteCrime < 5 ) {
        // relaché
        humain->SetValeurACaracId(GenVieHumain::C_LIBERTE, "");
        humain->SetValeurACaracId(Crime::C_GANG, "");
        humain->SetValeurACaracId(Crime::C_CRIMINEL, "");
        texte = "Miracle ! Loué soit l'empereur ! Vous êtes jugé innocent et relâché.";
    }
    else if ( graviteCrime < 10 ) {
        // prison
        int nbAnneePrison = Aleatoire::GetAl()->EntierEntreAEtB(1, 40);
        humain->SetValeurACaracId(GenVieHumain::C_LIBERTE, Crime::PRISON );
        humain->SetValeurACaracId(Crime::C_GANG, "");
        humain->SetValeurACaracId(Crime::C_CRIMINEL, "");
        humain->SetValeurACaracId(Crime::C_MOIS_PRISON, QString::number(nbAnneePrison * 12));
        texte = "Vous êtes condamné à " + QString::number(nbAnneePrison) + " années de prison.";

    }
    else {
        QList<QString> punitions = {
            "exécution",
            "serviteur",
            "arcoflagellation"
        };
        int indexPunition = Aleatoire::GetAl()->EntierInferieurA(punitions.length());

        switch (indexPunition) {
        case 1 : {
            // exécution
            texte = "Vous êtes jugé et condamné à mort pour vos crimes. La sentence est exécutée le mois suivant.";
            humain->SetValeurACaracId(PbSante::C_SANTE, PbSante::MORT);

        }break;
        case 2 : {
            // transformé en serviteur
            texte = "Vous êtes jugé et condamné à être transformé en serviteur décérébré jusqu'à la fin de vos jours. Vous êtes lobotomisé le mois suivant...";
            imgPath = ":/images/metier/serviteur.jpg";
            humain->SetValeurACaracId(PbSante::C_SANTE, PbSante::MORT);
        }break;
        case 3 : {
            // arco flagellation
            texte = "Vous êtes jugé et condamné à l'arcoflagellation. Vous êtes lobotomisé et transformé en machine à tuer décérébrée au service de l'inquisition.";
            imgPath = ":/images/guerre/Arcoflagellant.jpg";
            humain->SetValeurACaracId(PbSante::C_SANTE, PbSante::MORT);
        }break;
        }
    }

    execEffet->GetEffet()->m_Texte = texte;
    if ( imgPath != "" )
        execEffet->ChargerImage(imgPath);
}

shared_ptr<Condition> Crime::AjouterModificateurDeProbaSiDelinquant(shared_ptr<Condition> cond, double poidsProba)
{
    cond->AjouterModifProba(poidsProba,
        {         make_shared<Condition>(Crime::C_CRIMINEL, Crime::DELINQUANT, Comparateur::c_Egal)        });
    return cond;
}

shared_ptr<Condition> Crime::AjouterModificateurDeProbaSiCriminel(shared_ptr<Condition> cond, double poidsProba)
{
    cond->AjouterModifProba(poidsProba,
        {         make_shared<Condition>(Crime::C_CRIMINEL, Crime::CRIMINEL, Comparateur::c_Egal)        });
    return cond;
}

QList<QString> Crime::NOMS_GANGS = {
    "Mara Salvatrucha", "Hell's Angels", "Camorra", "Los Zetas", "Yakuzas", "The Crips", "The Bloods", "Mongrel Mob",
    "Bahala Na", "Big Circle", "Born To Kill", "Bing Kong Tong", "Hip Sing Tong", "Ying On Tong", "Satanas", "Tiny Rascal Gang",
    "Wah Ching", "Triades", "Chung Ching Yee", "Chung Ching Yee", "Chung Ching Yee", "Breed Street", "Venice 13", "Culver City Boyz",
    "Maravilla", "avenidas", "Onterio Varrio Sur", "Tortilla Flats", "Rockwood", "Hazard", "Harpys 13", "Varrio Pico Nuevo", "Inglewood 13",
    "Rivas", "Whittier", "La Eme", "El Monte Flores", "norwalk los one ways gang", "White Fence", "Ñetas", "NFOD", "Hessians",
    "Milieu", "Les Apaches", "Les Loups de la Butte", "Cœurs d’Acier", "Gars d'Charonne", "Milieu", "Mitan",
};

QString Crime::GenererNomGang()
{
    return Crime::NOMS_GANGS[Aleatoire::GetAl()->EntierInferieurA(Crime::NOMS_GANGS.length())];
}

shared_ptr<Condition> Crime::AjouterConditionSiLibre()
{    return make_shared<Condition>(GenVieHumain::C_LIBERTE, "", Comparateur::c_Egal);}

shared_ptr<Condition> Crime::AjouterConditionSiDelinquant()
{    return make_shared<Condition>(Crime::C_CRIMINEL, Crime::DELINQUANT, Comparateur::c_Egal);}

shared_ptr<Condition> Crime::AjouterConditionSiNonLibre()
{    return make_shared<Condition>(GenVieHumain::C_LIBERTE, "", Comparateur::c_Different);}

shared_ptr<Condition> Crime::AjouterConditionSiJamaisCriminel()
{    return make_shared<Condition>(Crime::C_CRIMINEL, "", Comparateur::c_Egal);}

shared_ptr<Condition> Crime::AjouterConditionSiMalhonnete()
{    return make_shared<Condition>(Crime::C_CRIMINEL, "", Comparateur::c_Different);}

