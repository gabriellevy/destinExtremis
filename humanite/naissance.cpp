#include "naissance.h"
#include "../destinLib/aleatoire.h"
#include "socio_eco/classesociale.h"
#include "genviehumain.h"
#include "socio_eco/metier.h"
#include "trait.h"
#include "coteries/coterie.h"
#include "geographie/quartier.h"

using std::make_shared;
using std::shared_ptr;

std::shared_ptr<Effet> Naissance::GenererEffetNaissance(std::shared_ptr<Effet> effetNarrationVide)
{
    // coterie des parents :
    shared_ptr<Coterie> cotPere  = Coterie::GetCoterieAleatoire(true);
    shared_ptr<Coterie> cotMere  = Coterie::GetCoterieAleatoire(true);
    double proba = Aleatoire::GetAl()->Entre0Et1();
    if ( proba <= 0.6) {// bonnes chances que père et mère aient la même coterie
        cotMere = cotPere;
    }

    shared_ptr<Quartier> quartierNaissance = cotPere->m_Quartier;
    proba = Aleatoire::GetAl()->Entre0Et1();
    if ( proba <= 0.2 ) {
        quartierNaissance = Quartier::GetQuartierAleatoire(true);
    } else if ( proba <= 0.6) {
        quartierNaissance = cotMere->m_Quartier;
    }
    effetNarrationVide->m_Texte = "Vous êtes né à " + quartierNaissance->m_Nom + ". " +
            quartierNaissance->m_Description + ".";

    effetNarrationVide->m_Texte += "\nVotre père est " + cotPere->GetNom();
    effetNarrationVide->m_Texte += "\nVotre mère est " + cotMere->GetNom();

    // génération des traits :
    int nb = 4 + Aleatoire::GetAl()->EntierInferieurA(10);
    effetNarrationVide->m_Texte += "\n\nVos traits principaux : ";
    QVector<eTrait> m_Traits = {};
    while(nb-->0) {
        shared_ptr<Trait> trait = Trait::GetTrait(m_Traits, true);
        m_Traits.push_back(trait->m_eTrait);
        effetNarrationVide->AjouterChangeurDeCarac(trait->GetNom(), "1");
        effetNarrationVide->m_Texte += trait->GetNom();
        if ( nb != 0)
            effetNarrationVide->m_Texte += ", ";
        else {
            effetNarrationVide->m_Texte += ".";
        }

    }

    return effetNarrationVide;
}
