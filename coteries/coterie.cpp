#include "coterie.h"
#include "extremis.h"
#include "../destinLib/aleatoire.h"

using std::shared_ptr;

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
