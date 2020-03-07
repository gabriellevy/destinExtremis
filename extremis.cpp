#include "extremis.h"
#include "ui_univers.h"
#include "genviehumain.h"
#include "coteries/tyranides.h"
#include "coteries/croisadefranque.h"
#include "coteries/celte.h"
#include "coteries/orks.h"
#include "coteries/elfes.h"
#include "coteries/conquistadors.h"
#include "coteries/cathares.h"

QString Extremis::VIE_HUMAIN = "Vie d'un humain";

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
    m_Coteries = {
        make_shared<Tyranides>(),
        make_shared<Celte>(),
        make_shared<Elfes>(),
        make_shared<Orks>(),
        make_shared<Cathares>(),
        make_shared<Conquistadors>(),
        make_shared<CroisadeFranque>()
    };
}
