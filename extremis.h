#ifndef EXTREMIS_H
#define EXTREMIS_H

#include "../destinLib/abs/univers.h"
#include <QVector>
#include "coteries/coterie.h"
#include <memory>

struct Quartier;
class Condition;

class Extremis : public Univers
{
    Q_OBJECT

public:
    explicit Extremis(ModeAffichage modeAffichage = ModeAffichage::ema_Jeu,
             QWidget *parent = nullptr);
    void GenererCoteries();
    // un perso est actif si il n'est aps en prison ni à l'hopial, qu'il est libre de ses mouvements
    static void AjouterConditionSiActif(QList<std::shared_ptr<Condition>>& conditions);

    // noms d'aventures
    static QString VIE_HUMAIN;

    static QVector<std::shared_ptr<Coterie>> COTERIES;
    static QMap<QString, std::shared_ptr<Quartier>> QUARTIERS;
    static std::shared_ptr<Coterie> GetCoterie(QString id);
};

#endif // EXTREMIS_H
