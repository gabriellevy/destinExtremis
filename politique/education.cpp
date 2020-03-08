#include "education.h"
#include "../destinLib/abs/effet.h"
#include "../destinLib/abs/evt.h"
#include "../destinLib/gen/genevt.h"
#include "../destinLib/aleatoire.h"
#include "../destinLib/abs/selectionneurdenoeud.h"
#include "extremis.h"
#include "genviehumain.h"
#include "coteries/coterie.h"

Education::Education(int indexEvt):GenerateurNoeudsProbables (indexEvt)
{
    switch (indexEvt) {
    case 0 : {

    }break;
    }
}

std::shared_ptr<Evt> Education::GenererEvtEducationPolitique(GenHistoire* genHistoire)
{
    std::shared_ptr<Evt> evtEducationPol = genHistoire->AjouterEvt("evtEducationPol");

    // détermination des école de coterie que devra suivre le personnage :
    QVector<shared_ptr<Coterie>> m_Coteries = Coterie::GetNRandomCoteries(3);

    for ( auto cot: m_Coteries) {
        genHistoire->AjouterEffetNarration(cot->GetDescription(), cot->GetImage(), "id" + cot->GetNom());
    }

    return evtEducationPol;
}
