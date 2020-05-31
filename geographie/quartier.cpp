#include "quartier.h"
#include "../destinLib/abs/effet.h"
#include "../destinLib/abs/evt.h"
#include "../destinLib/gen/genevt.h"
#include "../destinLib/aleatoire.h"
#include "../destinLib/abs/selectionneurdenoeud.h"
#include "extremis.h"
#include "genviehumain.h"
#include <memory>
#include <QPair>

using std::shared_ptr;
using std::make_shared;



void Quartier::GenererQuartiersAdministratifs()
{
    /** TODO MATHIEU : à décommenter quand les quartiers administratifs seront assignés à des coteries
    shared_ptr<Quartier> tour = make_shared<Quartier>("Tour de la convention", "Centre du gouvernement mondial", "");
    Extremis::QUARTIERS[tour->m_Nom] = tour;

    shared_ptr<Quartier> quartierAdmin6 = make_shared<Quartier>("6eme Quartier administratif", "6eme Quartier administratif", "");
    Extremis::QUARTIERS[quartierAdmin6->m_Nom] = quartierAdmin6;

    shared_ptr<Quartier> quartierAdmin5 = make_shared<Quartier>("5eme Quartier administratif", "5eme Quartier administratif", "");
    Extremis::QUARTIERS[quartierAdmin5->m_Nom] = quartierAdmin5;

    shared_ptr<Quartier> quartierAdmin4 = make_shared<Quartier>("4eme Quartier administratif", "4eme Quartier administratif", "");
    Extremis::QUARTIERS[quartierAdmin4->m_Nom] = quartierAdmin4;

    shared_ptr<Quartier> quartierAdmin3 = make_shared<Quartier>("3eme Quartier administratif", "3eme Quartier administratif", "");
    Extremis::QUARTIERS[quartierAdmin3->m_Nom] = quartierAdmin3;

    shared_ptr<Quartier> quartierAdmin2 = make_shared<Quartier>("2eme Quartier administratif", "2eme Quartier administratif", "");
    Extremis::QUARTIERS[quartierAdmin2->m_Nom] = quartierAdmin2;

    shared_ptr<Quartier> quartierAdmin1 = make_shared<Quartier>("1er Quartier administratif", "1er Quartier administratif", "");
    Extremis::QUARTIERS[quartierAdmin1->m_Nom] = quartierAdmin1;
    */
}

double Quartier::GetPoidsDemo()
{
    if ( m_Coterie == nullptr) return 1.0;
    return m_Coterie->GetPoidsDemo();
}

shared_ptr<Quartier> Quartier::GetQuartierAleatoire(bool selonDemographie)
{
    if ( selonDemographie ) {
        double poidsDemoTotal = 0;
        for ( shared_ptr<Quartier> quart: Extremis::QUARTIERS) {
            poidsDemoTotal += quart->GetPoidsDemo();
        }

        double alPoidsDemo = Aleatoire::GetAl()->Entre0Et1() * poidsDemoTotal;

        for ( shared_ptr<Quartier> quart: Extremis::QUARTIERS) {
            alPoidsDemo -= quart->GetPoidsDemo();
            if ( alPoidsDemo <= 0)
                return quart;
        }

    }
    int val = Aleatoire::GetAl()->EntierInferieurA(Extremis::QUARTIERS.size());
    for ( shared_ptr<Quartier> quart: Extremis::QUARTIERS) {
        if ( val <= 0)
            return quart;
        val--;
    }
    return nullptr;
}

QuartierEffets::QuartierEffets(int indexEvt):GenerateurNoeudsProbables (indexEvt)
{
    switch (indexEvt) {
    case 0 : {

    }break;
    }
}

QString QuartierEffets::C_QUARTIER_HABITE = "Quartier habité";
QString QuartierEffets::C_QUARTIER_ACTUEL = "Quartier actuel"; // différent de l'habité lors des voyages etc

std::shared_ptr<Condition> QuartierEffets::AjouterCondHabiteCeQuartier(QString quartier)
{
    return make_shared<Condition>(QuartierEffets::C_QUARTIER_HABITE, quartier, Comparateur::c_Egal);
}

std::shared_ptr<Condition> QuartierEffets::AjouterCondEstDansCeQuartier(QString quartier)
{
    return make_shared<Condition>(QuartierEffets::C_QUARTIER_ACTUEL, quartier, Comparateur::c_Egal);
}

