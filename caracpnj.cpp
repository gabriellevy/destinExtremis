#include "caracpnj.h"
#include "ui_carac.h"
#include "../destinLib/abs/univers.h"
#include <QDebug>
#include "../destinLib/gestionnairecarac.h"
#include "genviehumain.h"
#include "humain.h"
#include "coteries/coterie.h"
#include "humanite/pnj.h"

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
    }
    else
    {
        qDebug()<<"Tentative d'afficher une carac dénuée d'intitulé"<<endl;
        return false;
    }
}

bool CaracPNJ::AfficherValeur()
{
    if ( m_Pnj == nullptr) // comment détecter quand il change de valeur ?
        m_Pnj = PNJ::ChargerPNJ(GetPrefixe(), Humain::GetHumainJoue());

    if ( m_Pnj!= nullptr && m_Pnj->m_Nom != "")
    {
        ui->labelValeur->show();
        ui->labelValeur->setFont( *Univers::BASE_FONT);

        QString txt = m_Pnj->m_Nom +
                "\n" + m_Pnj->m_Coterie->GetGentile();

        if ( m_Pnj->m_Age != -1) {
            int ageMois = m_Pnj->m_Age;
            int ageAnnee = ageMois/12;
            ageMois = (ageMois % 12);
            QString ageStr = QString::number(ageAnnee) + " ans " +
                    (ageMois> 0 ? (QString::number(ageMois) + " mois"):"");

            txt += "\n" + ageStr;
        }

        if ( m_Pnj->m_EtatMarital != "") {
            txt += "\n" + m_Pnj->m_EtatMarital;
        }

        ui->labelValeurDansBox->setText(txt);
        QString desc = this->GetCaracDescription();
        ui->labelValeur->setToolTip(desc);
        return true;
    }
    return false;
}
