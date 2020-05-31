#include "caracpnj.h"
#include "ui_carac.h"
#include "../destinLib/abs/univers.h"
#include <QDebug>
#include "../destinLib/gestcarac.h"
#include "genviehumain.h"
#include "humain.h"
#include "coteries/coterie.h"
#include "humanite/pnj.h"
#include "socio_eco/metier.h"
#include "humanite/identite.h"

CaracPNJ::CaracPNJ(QString prefixe, QString intitule)
    :Carac(prefixe, intitule, "",
           "", intitule, MODE_AFFICHAGE::ma_Texte_intitule,
           nullptr, "", ""), m_Pnj(nullptr)
{}

QString CaracPNJ::GetPrefixe()
{
    return this->m_DataCarac.m_Id;
}

bool CaracPNJ::bAffichable()
{
    if ( m_Pnj == nullptr)
        m_Pnj = PNJ::ChargerPNJ(GetPrefixe(), Humain::GetHumainJoue());
    return ( m_Pnj!= nullptr && m_Pnj->m_Nom != "");
}

bool CaracPNJ::AfficherIntitule()
{
    if ( m_DataCarac.m_Intitule != "")
    {
        ui->caracBox->show();
        ui->caracBox->setFont( *Univers::BASE_FONT);
        ui->caracBox->setTitle(m_DataCarac.m_Intitule);
        ui->caracBox->setToolTip(this->GetCaracDescription());
        return true;
    }
    else
    {
        qDebug()<<"Tentative d'afficher une carac dénuée d'intitulé"<<endl;
    }
    return false;
}

void CaracPNJ::Afficher()
{
    AfficherIntitule();

    this->setStyleSheet("QWidget#Fond { background-color: rgba(" +
                             QString::number(Univers::COULEUR_FOND.red()) +
                             "," + QString::number(Univers::COULEUR_FOND.green()) +
                             "," + QString::number(Univers::COULEUR_FOND.blue()) +
                             "," + QString::number(Univers::COULEUR_FOND.alpha()) +
                             ") }");

    ui->labelValeur->hide();
    ui->imageDansBox->hide();
    ui->imageCarac->hide();
    ui->jaugeCarac->hide();

    //if ( m_Pnj == nullptr) // lourd de charger à chaque fois... comment détecter quand il change de valeur ?
        m_Pnj = PNJ::ChargerPNJ(GetPrefixe(), Humain::GetHumainJoue());

    if ( m_Pnj!= nullptr && m_Pnj->m_Nom != "")
    {
        ui->labelValeurDansBox->show();
        ui->labelValeurDansBox->setFont( *Univers::BASE_FONT);

        QString txt = m_Pnj->m_Nom +
                "\n" + m_Pnj->m_Coterie->GetGentile();

        /* afficher age ?
         * if ( m_Pnj->m_Age != -1) {
            int ageMois = m_Pnj->m_Age;
            int ageAnnee = ageMois/12;
            ageMois = (ageMois % 12);
            QString ageStr = QString::number(ageAnnee) + " ans " +
                    (ageMois> 0 ? (QString::number(ageMois) + " mois"):"");

            txt += "\n" + ageStr;
        }*/

        if ( m_Pnj->m_EtatMarital != "") {
            txt += "\n" + m_Pnj->m_EtatMarital;
        }

        ui->labelValeurDansBox->setText(txt);
        QString desc = this->GetCaracDescription();
        ui->labelValeurDansBox->setToolTip(desc);

        QMap<QString, QString> caracs;
        caracs[PNJ::C_SEXE] = m_Pnj->m_SexeMasculin?PNJ::HOMME:PNJ::FEMME;
        caracs[Coterie::C_COTERIE] = m_Pnj->m_Coterie->GetId();

        QString CheminImg = Identite::GenererPortraits(caracs, m_Pnj->m_Age/12);
        if ( CheminImg != "" ) {
            m_Img.load(CheminImg);
            AfficherImage(true);
        }
    }
}
