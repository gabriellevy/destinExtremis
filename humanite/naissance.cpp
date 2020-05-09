#include "naissance.h"
#include "../destinLib/aleatoire.h"
#include "socio_eco/classesociale.h"
#include "genviehumain.h"
#include "socio_eco/metier.h"
#include "trait.h"
#include "coteries/coterie.h"
#include "geographie/quartier.h"
#include "famille/famille.h"

using std::make_shared;
using std::shared_ptr;

std::shared_ptr<Effet> Naissance::GenererEffetNaissance(std::shared_ptr<Effet> effetNarrationVide)
{
    effetNarrationVide->m_Texte = "";
    Famille::GenererParents(effetNarrationVide);

    // génération des traits :
    int nb = 3 + Aleatoire::GetAl()->EntierInferieurA(6);
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

    // génération classe sociale :
    QString clas = ClasseSociale::GetClasseSocialeAleatoire();
    effetNarrationVide->AjouterChangeurDeCarac(ClasseSociale::C_CLASSE_SOCIALE, clas);
    effetNarrationVide->m_Texte += "\nVous êtes de la classe sociale des " + clas + ".";

    return effetNarrationVide;
}
