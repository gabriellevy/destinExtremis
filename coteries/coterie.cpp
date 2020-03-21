#include "coterie.h"
#include "extremis.h"
#include "../destinLib/aleatoire.h"
#include "../destinLib/abs/condition.h"

using std::shared_ptr;
using std::make_shared;


QString Coterie::C_COTERIE = "Coterie";
// valeurs de C_COTERIE
QString Coterie::CONQUISTADORS = "Conquistadors";
QString Coterie::CATHARES = "Cathares";
QString Coterie::CELTES = "Celtes";
QString Coterie::CROISADE = "Croisade";
QString Coterie::ELFES = "Elfes";
QString Coterie::ORKS = "Orks";
QString Coterie::TYRANIDES = "Tyranides";


Coterie::Coterie()
{

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
