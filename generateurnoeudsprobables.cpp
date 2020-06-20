#include "generateurnoeudsprobables.h"
#include "../destinLib/abs/effet.h"
#include "../destinLib/abs/evt.h"
#include "../destinLib/gen/genevt.h"
#include "extremis.h"
#include <memory>
#include "genviehumain.h"

using std::shared_ptr;

GenerateurNoeudsProbables::GenerateurNoeudsProbables(int /*indexEvt*/){}


shared_ptr<Effet> GenerateurNoeudsProbables::GenererEffet(shared_ptr<GenEvt> genEvt)
{
    shared_ptr<Effet> effet = nullptr;

    if ( m_Id == "")
        m_Id = m_Nom;

    // système de création d'effets de base :
    effet = genEvt->AjouterEffetNarration(
        m_Description,
        m_Image,
        "evt_" + m_Id,
        GenVieHumain::EVT_SELECTEUR);
    effet->SetNom(m_Nom);
    effet->m_GoToEffetId = GenVieHumain::EFFET_TEST_MORT_ID;
    effet = GenVieHumain::TransformerEffetEnEffetMoisDeVie(effet);
    effet->m_Conditions = m_Conditions;
    effet->m_CallbackDisplay = m_CallbackDisplay;

    // modificateurs de carac :
    QMapIterator<QString, QString> it(m_ModificateursCaracs);
    while ( it.hasNext()) {
        it.next();
        effet->AjouterChangeurDeCarac(it.key(), it.value());
    }
    QMapIterator<QString, int> itInc(m_IncrementeursCaracs);
    while ( itInc.hasNext()) {
        itInc.next();
        effet->AjouterAjouteurACarac(itInc.key(), itInc.value());
    }

    if ( m_Son != "" )
        effet->m_Son = m_Son;

    return effet;
}

