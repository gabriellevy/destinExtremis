#include "caraccoterie.h"
#include "ui_carac.h"
#include "../destinLib/abs/univers.h"
#include "../destinLib/gestcarac.h"
#include "genviehumain.h"
#include "coteries/coterie.h"
#include "extremis.h"

CaracCoterie::CaracCoterie():Carac(Coterie::C_COTERIE, Coterie::C_COTERIE, "",
                                   "", "", MODE_AFFICHAGE::ma_Img,
                                   nullptr, "", "")
{
    m_EmplacementAffichage = ea_ImgPrimaire;
}

bool CaracCoterie::AfficherImage(bool dansBox)
{
    m_Coterie = Extremis::GetCoterie(this->m_DataCarac.GetValeur());
    QString chemin = m_Coterie->GetIcone();
    if ( chemin != "" ) {
        m_Img.load(chemin);
        return Carac::AfficherImage(false);
    }
    return false;
}

QString CaracCoterie::GetCaracDescription()
{
    return m_Coterie->GetNom();
}
