#include "vehicule.h"
#include "../destinLib/abs/effet.h"
#include "../destinLib/abs/evt.h"
#include "../destinLib/gen/genevt.h"
#include "../destinLib/abs/selectionneurdenoeud.h"
#include "extremis.h"
#include "genviehumain.h"
#include "humain.h"
#include "humanite/pbsante.h"
#include "../destinLib/aleatoire.h"

QString Vehicule::C_CONDUITE_ROUTE = "Conduite";
QString Vehicule::C_CONDUITE_AVION = "Pilotage avion";

Vehicule::Vehicule(int indexEvt):GenerateurNoeudsProbables (indexEvt)
{
    double tmpModif = 0.0;
    switch (indexEvt) {
    case 0 : {
        m_Nom = "accident de circulation";
        m_ConditionSelecteurProba = make_shared<Condition>(0.005 + tmpModif, p_Relative);
        m_Description = "????";
        m_CallbackDisplay = [] {
            Humain* hum = Humain::GetHumainJoue();
            shared_ptr<Effet> effet = ExecHistoire::GetEffetActuel();
            effet->m_Texte = "Vous êtes heurté par une voiture.";
            int nbMoisHopital = 0;
            // mort ?
            double proba = Aleatoire::GetAl()->Entre0Et1();
            if ( proba > 0.99) {
                effet->m_Texte += "\nVous êtes tué dans l'accident.";
                PbSante::BlessureLegere(hum, effet, nbMoisHopital);
                hum->SetValeurACaracId(PbSante::C_SANTE, PbSante::MORT);
                return;
            }

            // blessure légère ?
            proba = Aleatoire::GetAl()->Entre0Et1();
            if ( proba > 0.6) {
                PbSante::BlessureLegere(hum, effet, nbMoisHopital);
            }
            // blessure grave ?
            proba = Aleatoire::GetAl()->Entre0Et1();
            if ( proba > 0.8) {
                PbSante::BlessureGrave(hum, effet, nbMoisHopital);
            }

            nbMoisHopital += Aleatoire::GetAl()->EntierEntreAEtB(1,6);
            hum->SetValeurACaracId(PbSante::C_MOIS_HOPITAL, nbMoisHopital);
            effet->m_Texte += "\nVous devez rester " + QString::number(nbMoisHopital) + " mois à l'hopital.";
        };

    }break;
    }
}
