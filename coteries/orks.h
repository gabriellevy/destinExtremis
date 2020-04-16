#ifndef ORKS_H
#define ORKS_H

#include "coterie.h"

class Evt;

class Orks : public Coterie
{
public:
    Orks();

    void GenererTraitCompatibles();
    QString GetNom();
    QString GetId();
    double GetPoidsDemo();

    QString GetDescription();
    QString GetDescriptionUniversite();
    QString GetImage();
    virtual QString GetGentile(bool masculin = true);
    QString CreerPatronyme(bool masculin = true);
    QString GetMusique();
    virtual std::shared_ptr<Quartier> GenererQuartier();
    virtual std::shared_ptr<Effet> AjouterEffetUniversite(
            GenHistoire* genHist, std::shared_ptr<Evt> evt, QString go_to_effet_suivant);
    virtual void RejoindreCoterie(Humain* hum, std::shared_ptr<Effet> eff);

    static QVector<QString> NOMS_M;
    static QVector<QString> NOMS_F;
};

#endif // ORKS_H
