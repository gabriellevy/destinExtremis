#ifndef EXTREMIS_H
#define EXTREMIS_H

#include "../destinLib/abs/univers.h"
#include <QVector>
#include "coteries/coterie.h"
#include <memory>

class Extremis : public Univers
{
    Q_OBJECT

public:
    explicit Extremis(ModeAffichage modeAffichage = ModeAffichage::ema_Jeu,
             QWidget *parent = nullptr);
    void GenererCoteries();

    // noms d'aventures
    static QString VIE_HUMAIN;

    static QVector<std::shared_ptr<Coterie>> COTERIES;
    static std::shared_ptr<Coterie> GetCoterie(QString id);
};

#endif // EXTREMIS_H
