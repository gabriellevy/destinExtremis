#include "coterie.h"
#include "extremis.h"
#include "../destinLib/aleatoire.h"
#include "../destinLib/abs/condition.h"
#include "humain.h"
#include "geographie/quartier.h"
#include "socio_eco/economieevt.h"

using std::shared_ptr;
using std::make_shared;


QString Coterie::C_COTERIE = "Coterie";
// valeurs de C_COTERIE
QString Coterie::CONQUISTADORS = "Conquistadors";
QString Coterie::CATHARES = "Cathares";
QString Coterie::CELTES = "Celtes";
QString Coterie::CROISADE = "Croisade franque";
QString Coterie::ELFES = "Elfes";
QString Coterie::ORKS = "Orks";
QString Coterie::TYRANIDES = "Tyranides";

double Coterie::SEUIL_CONVERSION = 0.9;

Coterie::Coterie()
{}

shared_ptr<Quartier> Coterie::GenererQuartier()
{
    return m_Quartier;
}

double Coterie::Compatibilite(Humain* hum, bool aleatoire)
{
    double proba = 0.5;
    if ( aleatoire)
        proba = Aleatoire::GetAl()->Entre0Et1();

    for ( shared_ptr<Condition> cond : this->m_TraitsCompatible) {
        if ( cond->Tester()) {
            proba += 0.2;
        }
    }
    for ( shared_ptr<Condition> cond : this->m_TraitsIncompatible) {
        if ( cond->Tester()) {
            proba -= 0.2;
        }
    }
    for (QString idMetier: this->m_MetiersAssocies) {
        if ( hum->GetValeurCarac(Coterie::C_COTERIE) == idMetier) {
            proba += 0.3;
        }
    }

    return proba;
}

QString Coterie::GetMusique()
{
    return "";
}

void Coterie::RejoindreCoterie(Humain* hum, shared_ptr<Effet> eff)
{
    hum->SetValeurACaracId(Coterie::C_COTERIE, GetId());
    QString nom = this->CreerPatronyme();
    hum->MajNom(nom);
    eff->m_Texte += "\nVous rejoignez la coterie : " + GetNom() + ". Vous vous appelez maintenant " + nom + ".";
    QString musique = GetMusique();
    if ( musique != "") {
        eff->m_Son = musique;
    }
    // déménagement dans le quartier de la coterie ?
    double proba = Aleatoire::GetAl()->Entre0Et1();
    if ( proba >= 0.3) {
        eff->m_Texte += "\nVous décidez de déménager dans " + m_Quartier->m_Nom + ", le quartier de votre nouvelle coterie.";
        hum->SetValeurACaracId(QuartierEffets::C_QUARTIER_HABITE,
                                                   m_Quartier->m_Nom);
        hum->SetValeurACaracId(QuartierEffets::C_QUARTIER_ACTUEL,
                                                   m_Quartier->m_Nom);
        hum->SetValeurACaracId(EconomieEvt::C_NIVEAU_ECONOMIQUE,
             hum->GetValeurCaracAsInt(EconomieEvt::C_NIVEAU_ECONOMIQUE) - 1);
    }
}

void Coterie::Initialisation()
{
    GenererTraitCompatibles();
    m_Quartier = this->GenererQuartier();
}


std::shared_ptr<Coterie>Coterie:: GetCoterieAleatoire(bool selonPoidsDemographique )
{
    if ( selonPoidsDemographique ) {
        double poidsDemoTotal = 0;
        for ( shared_ptr<Coterie> cot: Extremis::COTERIES) {
            poidsDemoTotal += cot->GetPoidsDemo();
        }

        double alPoidsDemo = Aleatoire::GetAl()->Entre0Et1() * poidsDemoTotal;

        for ( shared_ptr<Coterie> cot: Extremis::COTERIES) {
            alPoidsDemo -= cot->GetPoidsDemo();
            if ( alPoidsDemo <= 0)
                return cot;
        }

    }
    return Extremis::COTERIES[Aleatoire::GetAl()->EntierInferieurA(Extremis::COTERIES.size())];
}

QVector<shared_ptr<Coterie>> Coterie::GetNRandomCoteries(int n, bool selonPoidsDemographique)
{
    QVector<shared_ptr<Coterie>> m_Coteries = {};

    while (n > 0) {
        shared_ptr<Coterie> coterie = GetCoterieAleatoire(selonPoidsDemographique);

        if ( m_Coteries.indexOf(coterie) == -1) {
            m_Coteries.push_back(coterie);
            n--;
        }
    }

    return m_Coteries;
}

void Coterie::AjouterModifProbaSiDeCetteCoterie(Condition* CondProba, double proba, QString nomCoterie)
{
    CondProba->AjouterModifProba(proba,
        {make_shared<Condition>(Coterie::C_COTERIE, nomCoterie, Comparateur::c_Egal)});
}
