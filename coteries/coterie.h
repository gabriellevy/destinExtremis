#ifndef COTERIE_H
#define COTERIE_H

#include <QVector>
#include "humanite/trait.h"
#include <memory>

class Effet;
class Evt;
class GenHistoire;
class Condition;

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
    virtual QString GetId() = 0;
    virtual QString GetDescription() = 0;
    virtual QString GetDescriptionUniversite() = 0;
    virtual QString GetImage() = 0;
    virtual float GetPoidsDemo() = 0; // poids démographique. 1 = normal, 0.1 très très faible, 2 énorme

    virtual std::shared_ptr<Effet> AjouterEffetUniversite(
            GenHistoire* genHist, std::shared_ptr<Evt> evt, QString go_to_effet_suivant) = 0;

    static QVector<std::shared_ptr<Coterie>>GetNRandomCoteries(int n);

    static void AjouterModifProbaSiDeCetteCoterie(Condition* CondProba, double proba, QString nomCoterie);


    static QString C_COTERIE;
    // valeurs de C_COTERIE
    static QString CONQUISTADORS;
    static QString CATHARES;
    static QString CELTES;
    static QString CROISADE;
    static QString ELFES;
    static QString ORKS;
    static QString TYRANIDES;
};

#endif // COTERIE_H
