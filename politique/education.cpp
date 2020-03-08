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


    genHistoire->AjouterEffetNarration(
                "Pour parfaire votre éducation et devenir un homme vous allez être éduqué dans les universités de " +
                QString::number(NB_COTERIES_EDUCATION) + "coteries déterminées au hasard et y apprendre leurs philosophie et mode de vie pendant un mois pour chaque. " +
                "Après cette formalité vous serez libre d'en rejoindre une ou de partir vivre votre vie par vous même."
                , "", "choixUnivCoteries");

    // détermination des école de coterie que devra suivre le personnage :
    QVector<shared_ptr<Coterie>> m_Coteries = Coterie::GetNRandomCoteries(3);

    for ( auto cot: m_Coteries) {
        // ajouter X événements aléatoires pour chaque  coterie où le personnage va étudier
        genHistoire->AjouterEffetNarration(cot->GetDescription(), cot->GetImage(), "id" + cot->GetNom());

        for ( int i = 0; i < NB_EFFETS_EDUCATION; ++i) {
            cot->AjouterEffetUniversite(genHistoire);
        }
    }

    return evtEducationPol;
}
