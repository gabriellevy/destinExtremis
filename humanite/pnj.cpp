#include "pnj.h"
#include "coteries/coterie.h"
#include "../destinLib/aleatoire.h"

using std::make_shared;
using std::shared_ptr;

PNJ::PNJ()
{

}

std::shared_ptr<PNJ> PNJ::GenererPersoAleatoire( Sexe sexe, std::shared_ptr<Coterie> coterie)
{
    shared_ptr<PNJ> pnj = make_shared<PNJ>();

    if ( coterie == nullptr ) {
        pnj->m_Coterie  = Coterie::GetCoterieAleatoire(true);
    } else {
        pnj->m_Coterie = coterie;
    }

    switch (sexe) {
    case es_Masculin : pnj->m_SexeMasculin = true; break;
    case es_Feminin : pnj->m_SexeMasculin = false; break;
    case es_Aleatoire : pnj->m_SexeMasculin = Aleatoire::GetAl()->GetBool(); break;
    }

    pnj->m_Nom = pnj->m_Coterie->CreerPatronyme(sexe);

    return pnj;
}
