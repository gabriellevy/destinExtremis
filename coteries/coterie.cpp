#include "coterie.h"
#include "extremis.h"
#include "../destinLib/aleatoire.h"
#include "../destinLib/abs/condition.h"
#include "humain.h"

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


Coterie::Coterie()
{

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
    eff->m_Texte += "\nVous rejoignez la coterie : " + GetNom() + " et vous êtes nummé " + nom + ".";
    QString musique = GetMusique();
    if ( musique != "") {
        eff->m_Son = musique;
    }
}

void Coterie::Initialisation()
{
    GenererTraitCompatibles();
}

QVector<shared_ptr<Coterie>> Coterie::GetNRandomCoteries(int n)
{
    QVector<shared_ptr<Coterie>> m_Coteries = {};

    while (n > 0) {
        shared_ptr<Coterie> coterie = Extremis::COTERIES[Aleatoire::GetAl()->EntierInferieurA(Extremis::COTERIES.size())];

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
