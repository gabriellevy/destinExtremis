#include "naissance.h"
#include "../destinLib/aleatoire.h"
#include "socio_eco/classesociale.h"
#include "genviehumain.h"
#include "socio_eco/metier.h"
#include "trait.h"

using std::make_shared;
using std::shared_ptr;

std::shared_ptr<Effet> Naissance::GenererEffetNaissance(std::shared_ptr<Effet> effetNarrationVide)
{
    // génération des traits :
    int nb = 4 + Aleatoire::GetAl()->EntierInferieurA(10);
    effetNarrationVide->m_Texte = "Vos traits principaux : ";
    QVector<eTrait> m_Traits = {};
    while(nb-->0) {
        shared_ptr<Trait> trait = Trait::GetTrait(m_Traits);
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
