#include "genviehumain.h"
#include "generateurnoeudsprobables.h"
#include "extremis.h"
#include "../destinLib/gestionnairecarac.h"
#include "../destinLib/aleatoire.h"
#include "../destinLib/abs/perso.h"
#include "../destinLib/exec/execeffet.h"
#include "../destinLib/abs/lancerde.h"
#include "../destinLib/abs/setcarac.h"
#include "../destinLib/abs/choix.h"
#include "humain.h"
#include "socio_eco/metier.h"
#include "humanite/pbsante.h"
#include "humanite/identite.h"
#include "socio_eco/classesociale.h"
#include "socio_eco/crime.h"
#include "socio_eco/economieevt.h"
#include "humanite/naissance.h"
#include "texte/jourapresjour.h"
#include "techno/vehicule.h"
#include "techno/bionique.h"
#include "age.h"
#include "famille/famille.h"
#include "humanite/trait.h"
#include "politique/education.h"
#include "politique/propagande.h"
#include "violence/combat.h"
#include "religion/religion.h"
#include "geographie/quartier.h"
#include "humanite/pnj.h"
#include "caracpnj.h"
#include "famille/amour.h"
#include "coteries/orks.h"
#include "coteries/croisadefranque.h"
#include "coteries/conquistadors.h"

using std::make_shared;
using std::shared_ptr;

QString GenVieHumain::AGE = "Age";
QString GenVieHumain::C_LIBERTE = "Liberté";

GenVieHumain::GenVieHumain():GenHistoire ("La vie sur Extremis") {}

GenVieHumain* GenVieHumain::GetGenVieHumain()
{
    return static_cast<GenVieHumain*>(ME);
}

shared_ptr<Hist> GenVieHumain::GenererHistoire()
{
    GenHistoire::GenererHistoire();
    GenererDataUnivers();
    GenererPersos();
    GenererEvtsAccueil();
    GenererCaracs();
    GenererPrincipalSelectionneurDEffet();

    m_HistoireGeneree->m_ModeDeroulement = ModeDeroulement::Automatique;
    m_HistoireGeneree->m_MsDureeDefilement = GenVieHumain::CHRONO;

    return m_HistoireGeneree;
}

void GenVieHumain::GenererDataUnivers()
{
    // pour les données d'univers dépendantes de l'histoire
    Quartier::GenererQuartiersAdministratifs();
}

void GenVieHumain::GenererPersos()
{
    QString nom = Identite::CreerPatronyme();
    shared_ptr<Humain> perso = make_shared<Humain>(nom);
    perso->InitialiserPerso();
    IPerso::AjouterPersoJouable(perso);
}

void GenVieHumain::GenererCaracs()
{
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCarac(new Age(180)); // début à 15 ans (180)
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracNombre(PbSante::C_MOIS_HOPITAL);
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracString(Metier::C_METIER);
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracNombre(Metier::C_COMPETENCE_METIER);
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracString(Coterie::C_COTERIE);
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCarac(new CaracPNJ(Amour::PRE_AMOUREUSE1, "Amoureuse"));
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCarac(new CaracPNJ(Amour::PRE_AMOUREUSE2, "Amoureuse"));
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCarac(new CaracPNJ(Amour::PRE_AMOUREUSE3, "Amoureuse"));
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCarac(new CaracPNJ(Famille::PRE_PERE, "Père"));
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCarac(new CaracPNJ(Famille::PRE_MERE, "Mère"));
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracString(ClasseSociale::C_CLASSE_SOCIALE);
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracImage(Religion::C_RELIGION);
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracStringIntitule(QuartierEffets::C_QUARTIER_HABITE);

    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracBinaire(PbSante::ALCOOLIQUE);
    // afficher tous les traits et blessures du personnage
    for (int i = 0; i < eTrait::nb_Traits; i++) {
        GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracBinaire((make_shared<Trait>(static_cast<eTrait>(i)))->GetNom());
    }
    for ( QString bless: PbSante::BLESSURES_LEGERES) {
        GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracBinaire(bless);
    }
    for ( QString bless: PbSante::BLESSURES_GRAVES) {
        GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracBinaire(bless);
    }

    // temp test :
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracString(GenVieHumain::C_LIBERTE);
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracString(Crime::C_CRIMINEL);
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracString(Crime::C_GANG);
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracNombre(EconomieEvt::C_NIVEAU_ECONOMIQUE);
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracString(PbSante::C_SANTE);
    GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracString(PbSante::C_CONSTITUTION);


    Carac* carac = GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracNombre(Crime::C_MOIS_PRISON);
    carac->m_ModeAffichage = MODE_AFFICHAGE::ma_NombreSupZero;
    Carac* caracBionique = GestionnaireCarac::GetGestionnaireCarac()->AjouterCaracNombre(Bionique::C_BIONIQUE_LONGEVITE);
    caracBionique->m_ModeAffichage = MODE_AFFICHAGE::ma_NombreSupZero;
}

void GenVieHumain::GenererEvtsAccueil()
{
    this->AjouterEvt("Debut", "Génération du perso par les choix");
    shared_ptr<Effet> effet1 = AjouterEffetNarration("", "");
    Naissance::GenererEffetNaissance(effet1);

    std::shared_ptr<Evt> evtEducationPol = Education::GenererEvtEducationPolitique(this);

    AjouterEffetGoToEvt(GenVieHumain::EVT_SELECTEUR_ID, "finNaissance");
}


void GenVieHumain::GenererEvtsDeBase(QVector<shared_ptr<NoeudProbable>> &noeuds)
{
    shared_ptr<Evt> evtRien = AjouterEvt("evtRien");
    shared_ptr<Effet> effetRien = AjouterEffetNarration("Il ne se passe rien. => à régénérer");
    effetRien = TransformerEffetEnEffetMoisDeVie(effetRien);
    effetRien->m_CallbackDisplay = [] {
        Phrase phrase = JourApresJour::ExtrairePhrase();
        ExecHistoire::GetEffetActuel()->m_Texte = phrase.m_Texte;
        ExecHistoire::GetEffetActuel()->m_ImgPath = phrase.m_CheminImg;
        ExecHistoire::GetExecEffetActuel()->ChargerImage(phrase.m_CheminImg);
    };
    shared_ptr<NoeudProbable> noeudEvtRien = make_shared<NoeudProbable>(
                evtRien,
                make_shared<Condition>(1, p_Relative));
    noeuds.push_back(noeudEvtRien);

    GenererNoeuds<Metier>(m_GenerateurEvt, noeuds);
    GenererNoeuds<PbSante>(m_GenerateurEvt, noeuds);
    GenererNoeuds<ClasseSociale>(m_GenerateurEvt, noeuds);
    GenererNoeuds<Crime>(m_GenerateurEvt, noeuds);
    GenererNoeuds<EconomieEvt>(m_GenerateurEvt, noeuds);
    GenererNoeuds<Education>(m_GenerateurEvt, noeuds);
    GenererNoeuds<Propagande>(m_GenerateurEvt, noeuds);
    GenererNoeuds<Combat>(m_GenerateurEvt, noeuds);
    GenererNoeuds<Religion>(m_GenerateurEvt, noeuds);
    GenererNoeuds<Vehicule>(m_GenerateurEvt, noeuds);
    GenererNoeuds<Famille>(m_GenerateurEvt, noeuds);
    GenererNoeuds<Amour>(m_GenerateurEvt, noeuds);
    GenererNoeuds<EvtOrks>(m_GenerateurEvt, noeuds);
    GenererNoeuds<EvtCroisadeFranque>(m_GenerateurEvt, noeuds);
    GenererNoeuds<EvtConquistadors>(m_GenerateurEvt, noeuds);
}

template<class T>
void GenVieHumain::GenererNoeuds(shared_ptr<GenEvt> genEvt, QVector<shared_ptr<NoeudProbable>> &noeuds)
{
    int indexEvt = 0;
    GenerateurNoeudsProbables* evt = new T(indexEvt++);
    while ( evt->m_Nom != "") {

        shared_ptr<Effet> effet = evt->GenererEffet(genEvt);

        shared_ptr<Condition> cond = evt->m_ConditionSelecteurProba;

        shared_ptr<NoeudProbable> noeud = make_shared<NoeudProbable>(
                    effet,
                    cond);

        noeuds.push_back(noeud);

        evt = new T(indexEvt++);
    }
}

shared_ptr<Effet> GenVieHumain::TransformerEffetEnEffetMoisDeVie(shared_ptr<Effet> effet)
{
    // ne se déclenche que si le personnage est encore en vie :
    effet->AjouterCondition(PbSante::C_SANTE, Comparateur::c_Different, PbSante::MORT);
    effet->m_MsChrono = GenVieHumain::CHRONO;
    effet->m_GoToEvtId = "PrincipalSelecteur";
    effet->AjouterAjouteurACarac(GenVieHumain::AGE, 1);
    effet->AjouterAjouteurACarac(Amour::PRE_AMOUREUSE1 + GenVieHumain::AGE, 1);
    effet->AjouterAjouteurACarac(Crime::C_MOIS_PRISON, -1);
    effet->AjouterAjouteurACarac(PbSante::C_MOIS_HOPITAL, -1);
    return effet;
}

QString GenVieHumain::EFFET_SELECTEUR_ID = "effetSelecteur";
QString GenVieHumain::EVT_SELECTEUR_ID = "PrincipalSelecteur";
shared_ptr<Evt> GenVieHumain::EVT_SELECTEUR = nullptr;

void GenVieHumain::GenererPrincipalSelectionneurDEffet()
{
    GenVieHumain::EVT_SELECTEUR = this->AjouterEvt(GenVieHumain::EVT_SELECTEUR_ID, "Principal sélecteur");
    /*Effet* effetDebut = */AjouterEffetGoToEffet(GenVieHumain::EFFET_SELECTEUR_ID, "effet_go_to_" + GenVieHumain::EFFET_SELECTEUR_ID);
    // ce vector doit contenir tous les noeuds de base déclenchant des effets et événements à partir du cours normal de la vie
    // en dehors de lui les sélections de noeuds ne sont qu'à la création du personnage et quand un événement particulier est en cours d'exécution
    // à sa fin on doit avoir un goto qui ramène à cet événement/effet "sélecteur"
    QVector<shared_ptr<NoeudProbable>> tousLesNoeudsDeBase;
    GenererEvtsDeBase(tousLesNoeudsDeBase);

    shared_ptr<Effet> effetTestMort = m_GenerateurEvt->AjouterEffetVide(GenVieHumain::EVT_SELECTEUR, GenVieHumain::EFFET_SELECTEUR_ID);
    effetTestMort->m_GoToEffetId = "effetFinVie";
    effetTestMort->AjouterCondition(PbSante::C_SANTE, Comparateur::c_Egal, PbSante::MORT);

    shared_ptr<Effet> effetSelecteur = m_GenerateurEvt->AjouterEffetSelecteurDEvt(
                tousLesNoeudsDeBase, GenVieHumain::EFFET_SELECTEUR_ID + "_selecteur", "", GenVieHumain::EVT_SELECTEUR);
    effetSelecteur->m_MsChrono = 1; // passé automatiquement

    shared_ptr<Effet> effetFinVie = AjouterEffetNarration("Cette vie est terminée...", "", "effetFinVie", GenVieHumain::EVT_SELECTEUR);
    effetFinVie->m_ChangeurPhaseDeroulement = PhaseDeroulement::epd_Fini;
}
