#include "richesse.h"
#include "ui_carac.h"
#include "../destinLib/abs/univers.h"
#include "../destinLib/gestcarac.h"
#include "genviehumain.h"
#include "humain.h"
#include "socio_eco/economieevt.h"
#include "socio_eco/classesociale.h"
#include <QtMath>

QString Richesse::RICHESSE = "Richesse";

Richesse::Richesse():Carac(Richesse::RICHESSE, Richesse::RICHESSE, "1",
                           "", "", MODE_AFFICHAGE::ma_Texte_intitule,
                           nullptr, "", "")
{
    m_EmplacementAffichage = ea_Primaire;
}

bool Richesse::AfficherValeur()
{
    Humain* hum = Humain::GetHumainJoue();

    int nivEco = hum->GetValeurCaracAsInt(EconomieEvt::C_NIVEAU_ECONOMIQUE);
    QString classSociale = hum->GetValeurCarac(ClasseSociale::C_CLASSE_SOCIALE);
    if ( classSociale != "" )
    {
        int nivClassSociale = ClasseSociale::CLASSES_SOCIALES.indexOf(classSociale);
        int valFinale = static_cast<int>(qPow((nivClassSociale+1), 2 )) * (20 + nivEco);
        QString intitule = "Misérable";
        if ( valFinale > 70)
            intitule = "Très pauvre";
        if ( valFinale > 120)
            intitule = "Pauvre";
        if ( valFinale > 210)
            intitule = "En difficulé";
        if ( valFinale > 320)
            intitule = "Moyen";
        if ( valFinale > 400)
            intitule = "Aisé";
        if ( valFinale > 480)
            intitule = "Riche";
        if ( valFinale > 550)
            intitule = "Très riche";
        if ( valFinale > 650)
            intitule = "Richissime";
        ui->labelValeurDansBox->show();
        ui->labelValeurDansBox->setFont( *Univers::BASE_FONT);
        ui->labelValeurDansBox->setText(intitule);
        ui->labelValeurDansBox->setToolTip(this->GetCaracDescription());
        return true;
    }
    return false;
}
