#include "pnj.h"
#include "coteries/coterie.h"
#include "../destinLib/aleatoire.h"
#include "humain.h"
#include "extremis.h"

using std::make_shared;
using std::shared_ptr;


std::shared_ptr<PNJ> PNJ::GenererPersoAleatoire( QString prefixe, Sexe sexe, std::shared_ptr<Coterie> coterie)
{
    shared_ptr<PNJ> pnj = make_shared<PNJ>(prefixe);

    if ( coterie == nullptr ) {
        pnj->m_Coterie  = Coterie::GetCoterieAleatoire(true);
    } else {
        pnj->m_Coterie = coterie;
    }

    switch (sexe) {
    case es_Masculin : pnj->m_SexeMasculin = true; break;
    case es_Feminin : pnj->m_SexeMasculin = false; break;
    case es_Aleatoire : pnj->m_SexeMasculin = Aleatoire::GetAl()->GetBool(); break;
    }

    pnj->m_Nom = pnj->m_Coterie->CreerPatronyme(sexe);

    return pnj;
}

QString PNJ::C_NOM = "Nom";
QString PNJ::C_SEXE = "Sexe";
QString PNJ::C_COTERIE = "Coterie";

void PNJ::SauverPNJ(QString prefixe, Humain* hum)
{
    hum->SetValeurACaracId(prefixe + PNJ::C_NOM, this->m_Nom);
    hum->SetValeurACaracId(prefixe + PNJ::C_SEXE, this->m_SexeMasculin?"Homme":"Femme");
    hum->SetValeurACaracId(prefixe + PNJ::C_COTERIE, this->m_Coterie->GetId());
}

shared_ptr<PNJ> PNJ::ChargerPNJ(QString prefixe, Humain* hum)
{
    shared_ptr<PNJ> pnj = make_shared<PNJ>(prefixe);
    pnj->m_Coterie = Extremis::GetCoterie( hum->GetValeurCarac(prefixe + PNJ::C_COTERIE));
    pnj->m_Nom = hum->GetValeurCarac(prefixe + PNJ::C_NOM);
    pnj->m_SexeMasculin = hum->GetValeurCarac(prefixe + PNJ::C_SEXE) == "Homme";
    return pnj;
}
