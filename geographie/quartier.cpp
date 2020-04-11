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


QMap<QString, shared_ptr<Quartier>> Quartier::QUARTIERS = {};

void Quartier::GenererQuartiersAdministratifs()
{
    shared_ptr<Quartier> tour = make_shared<Quartier>("Tour de la convention", "Centre du gouvernement mondial", "");
    Quartier::QUARTIERS[tour->m_Nom] = tour;

    shared_ptr<Quartier> quartierAdmin6 = make_shared<Quartier>("6eme Quartier administratif", "6eme Quartier administratif", "");
    Quartier::QUARTIERS[quartierAdmin6->m_Nom] = quartierAdmin6;

    shared_ptr<Quartier> quartierAdmin5 = make_shared<Quartier>("5eme Quartier administratif", "5eme Quartier administratif", "");
    Quartier::QUARTIERS[quartierAdmin5->m_Nom] = quartierAdmin5;

    shared_ptr<Quartier> quartierAdmin4 = make_shared<Quartier>("4eme Quartier administratif", "4eme Quartier administratif", "");
    Quartier::QUARTIERS[quartierAdmin4->m_Nom] = quartierAdmin4;

    shared_ptr<Quartier> quartierAdmin3 = make_shared<Quartier>("3eme Quartier administratif", "3eme Quartier administratif", "");
    Quartier::QUARTIERS[quartierAdmin3->m_Nom] = quartierAdmin3;

    shared_ptr<Quartier> quartierAdmin2 = make_shared<Quartier>("2eme Quartier administratif", "2eme Quartier administratif", "");
    Quartier::QUARTIERS[quartierAdmin2->m_Nom] = quartierAdmin2;

    shared_ptr<Quartier> quartierAdmin1 = make_shared<Quartier>("1er Quartier administratif", "1er Quartier administratif", "");
    Quartier::QUARTIERS[quartierAdmin1->m_Nom] = quartierAdmin1;
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

