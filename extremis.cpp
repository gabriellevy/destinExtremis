#include "extremis.h"
#include "ui_univers.h"
#include "genviehumain.h"
#include "coteries/tyranides.h"
#include "coteries/templiers.h"
#include "coteries/celte.h"
#include "coteries/orks.h"
#include "coteries/transhumanistes.h"
#include "coteries/elfes.h"
#include "coteries/conquistadors.h"
#include "coteries/cathares.h"
#include <QVector>
#include "humanite/pbsante.h"

QString Extremis::VIE_HUMAIN = "Vie d'un humain";

QVector<std::shared_ptr<Coterie>> Extremis::COTERIES = {};
QMap<QString, shared_ptr<Quartier>> Extremis::QUARTIERS = {};

using std::shared_ptr;

Extremis::Extremis(ModeAffichage modeAffichage,
                   QWidget *parent)
    : Univers(parent, modeAffichage)
{
    //this->AppliquerTheme(QColor(54, 46, 43));
    this->AppliquerTheme(QColor(100, 90, 80));

    GenererCoteries();
    m_GensHistoire[Extremis::VIE_HUMAIN] = make_shared<GenVieHumain>();
}

void Extremis::GenererCoteries()
{
    Extremis::COTERIES = {
        make_shared<Elfes>(),
        make_shared<Orks>(),
        make_shared<Conquistadors>(),
        make_shared<Templiers>(),
        make_shared<Transhumanistes>()
        //make_shared<Tyranides>(),
        //make_shared<Celte>(),
        //make_shared<Cathares>(),
    };
}

std::shared_ptr<Coterie> Extremis::GetCoterie(QString id)
{
    for ( auto cot: COTERIES) {
        if ( id == cot->GetId())
            return cot;
    }
    return nullptr;
}


void Extremis::AjouterConditionSiActif(QList<shared_ptr<Condition>>& conditions)
{
    conditions.push_back( make_shared<Condition>(GenVieHumain::C_LIBERTE, "", Comparateur::c_Egal));
    conditions.push_back( make_shared<Condition>(PbSante::C_MOIS_HOPITAL, "0", Comparateur::c_InferieurEgal));
}

