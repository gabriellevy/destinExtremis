#include "famille.h"
#include "../destinLib/abs/effet.h"
#include "../destinLib/abs/evt.h"
#include "../destinLib/gen/genevt.h"
#include "../destinLib/aleatoire.h"
#include "../destinLib/abs/selectionneurdenoeud.h"
#include "extremis.h"
#include "genviehumain.h"
#include "geographie/quartier.h"
#include <memory>
#include "humanite/pnj.h"

using std::make_shared;

Famille::Famille(int indexEvt):GenerateurNoeudsProbables (indexEvt)
{
    switch (indexEvt) {
    case 0 : {

    }break;
    }
}

// préfixes liés (à associer aux caracs persos de la class PNJ)
QString Famille::PRE_PERE = "Père_";
QString Famille::PRE_MERE = "Mère_";


void Famille::GenererParents(std::shared_ptr<Effet> effetNarrationVide)
{
    // coterie des parents :
    shared_ptr<PNJ> pere = PNJ::GenererPersoAleatoire(es_Masculin);
    shared_ptr<Coterie> cotMere  = Coterie::GetCoterieAleatoire(true);
    double proba = Aleatoire::GetAl()->Entre0Et1();
    if ( proba <= 0.6) {// bonnes chances que père et mère aient la même coterie
        cotMere = pere->m_Coterie;
    }
    shared_ptr<PNJ> mere = PNJ::GenererPersoAleatoire(es_Feminin, cotMere);

    shared_ptr<Quartier> quartierNaissance = pere->m_Coterie->m_Quartier;
    proba = Aleatoire::GetAl()->Entre0Et1();
    if ( proba <= 0.2 ) {
        quartierNaissance = Quartier::GetQuartierAleatoire(true);
    } else if ( proba <= 0.6) {
        quartierNaissance = cotMere->m_Quartier;
    }
    effetNarrationVide->m_Texte += "Vous êtes né à " + quartierNaissance->m_Nom + ". " +
            quartierNaissance->m_Description + ".";

    effetNarrationVide->m_Texte += "\nVotre père s'appelle " + pere->m_Nom +
            ". C'est un " + pere->m_Coterie->GetNom();
    effetNarrationVide->m_Texte += "\nVotre mère s'appelle " + mere->m_Nom +
            ". C'est une " + mere->m_Coterie->GetNom();


}
