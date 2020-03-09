#ifndef COTERIE_H
#define COTERIE_H

#include <QVector>
#include "humanite/trait.h"
#include <memory>

class Effet;
class Evt;
class GenHistoire;

class Coterie
{
protected:
    QVector<std::shared_ptr<Trait>> m_TraitsCompatible = {};
    QVector<std::shared_ptr<Trait>> m_TraitsIncompatible = {};
public:
    Coterie();
    virtual ~Coterie() {}

    void Initialisation();

    virtual void GenererTraitCompatibles() = 0;
    virtual QString GetNom() = 0;
    virtual QString GetDescription() = 0;
    virtual QString GetImage() = 0;

    virtual std::shared_ptr<Effet> AjouterEffetUniversite(
            GenHistoire* genHist, std::shared_ptr<Evt> evt, QString go_to_effet_suivant) = 0;

    static QVector<std::shared_ptr<Coterie>>GetNRandomCoteries(int n);
};

#endif // COTERIE_H
