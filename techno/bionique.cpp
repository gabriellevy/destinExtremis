#include "bionique.h"
#include "../destinLib/abs/effet.h"
#include "../destinLib/aleatoire.h"
#include "../destinLib/abs/evt.h"
#include "../destinLib/gen/genevt.h"
#include "../destinLib/abs/selectionneurdenoeud.h"
#include "extremis.h"
#include "genviehumain.h"
#include "socio_eco/metier.h"
#include "../destinLib/aleatoire.h"
#include "socio_eco/classesociale.h"
#include "humanite/pbsante.h"
#include "humain.h"

QString Bionique::C_BIONIQUE_LONGEVITE = "Bionique longévité";

QString Bionique::C_FABRICATION_BIONIQUE = "Fabrication de bioniques";

// liste de bioniques existants (booléens essentiellement)
QString Bionique::C_OEIL_BIONIQUE = "Oeil bionique"; // infrarouge, zoom
QString Bionique::C_JAMBE_BIONIQUE = "Jambe bionique";
QString Bionique::C_BRAS_BIONIQUE = "Bras bionique";
QString Bionique::C_STIMULANT_REFLEXE = "Réflexes améliorés";
QString Bionique::C_OS_RENFORCES = "Os renforcés"; // os renforcés avec divers matériaux
QVector<QString> Bionique::TOUS_LES_BIONIQUES = {
    Bionique::C_OEIL_BIONIQUE,
    Bionique::C_JAMBE_BIONIQUE,
    Bionique::C_BRAS_BIONIQUE,
    Bionique::C_STIMULANT_REFLEXE,
    Bionique::C_OS_RENFORCES
};

Bionique::Bionique(int indexEvt):GenerateurNoeudsProbables (indexEvt)
{
    switch (indexEvt) {
    case 0 : {
        m_Nom = "ajout de " + Bionique::C_BIONIQUE_LONGEVITE;
        m_ConditionSelecteurProba = make_shared<Condition>(0.01, p_Relative);
        m_Description = "Vous remplacez un de vos organes défaillants pour allonger votre durée de vie.";
        m_IncrementeursCaracs[Bionique::C_BIONIQUE_LONGEVITE] = 1;
        m_Image = ":/images/techno/Biotic_Arm.jpg";
        // pour les vieux riches
        m_Conditions.push_back(ClasseSociale::AjouterConditionSiClasseSocialeSuperieureA(ClasseSociale::CLASSE_MOYENNE));
        m_Conditions.push_back(PbSante::AjouterConditionSiAgeSuperieurA(30));
        m_Conditions.push_back(Bionique::AjouterConditionSiBioniqueLongeviteInferieurA(10));

    }break;
    }
}

shared_ptr<Condition> Bionique::AjouterConditionSiBioniqueLongeviteSuperieureA(int nbBionique)
{
    shared_ptr<Condition> cond = make_shared<Condition>(Bionique::C_BIONIQUE_LONGEVITE, QString::number(nbBionique), Comparateur::c_Superieur);
    return cond;
}
shared_ptr<Condition> Bionique::AjouterConditionSiBioniqueLongeviteInferieurA(int nbBionique)
{
    shared_ptr<Condition> cond = make_shared<Condition>(Bionique::C_BIONIQUE_LONGEVITE, QString::number(nbBionique), Comparateur::c_Inferieur);
    return cond;
}

QString Bionique::AppliquerBionique(Humain* hum, QString id)
{
    if ( id=="")
        id = Bionique::TOUS_LES_BIONIQUES[Aleatoire::GetAl()->EntierInferieurA(Bionique::TOUS_LES_BIONIQUES.length())];

    hum->SetValeurACaracId(id, "1");

    // capacités bonus données par les bioniques
    if ( id == C_OS_RENFORCES ) {
        hum->SetValeurACaracId(Trait::GetNomTrait(resistant), "1");
    }else if ( id == C_BRAS_BIONIQUE ) {
        hum->SetValeurACaracId(Trait::GetNomTrait(fort), "1");
    }
    return id;
}
