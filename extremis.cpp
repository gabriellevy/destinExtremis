#include "extremis.h"
#include "ui_univers.h"
#include "genviehumain.h"

QString Extremis::VIE_HUMAIN = "Vie d'un humain";

Extremis::Extremis(ModeAffichage modeAffichage,
                   QWidget *parent)
    : Univers(parent, modeAffichage)
{
    //this->AppliquerTheme(QColor(54, 46, 43));
    this->AppliquerTheme(QColor(100, 90, 80));

    m_GensHistoire[Extremis::VIE_HUMAIN] = make_shared<GenVieHumain>();
}
