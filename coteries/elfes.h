#ifndef ELFES_H
#define ELFES_H

#include "coterie.h"


class Elfes : public Coterie
{
public:
    Elfes();

    void GenererTraitCompatibles();
    QString GetNom();
    QString GetId();
    double GetPoidsDemo();

    QString GetDescription();
    QString GetDescriptionUniversite();
    QString GetImage();
    virtual QString GetGentile(bool masculin = true);
    QString GetMusique();
    virtual std::shared_ptr<Quartier> GenererQuartier();
    virtual void GenererPortraits(Humain* hum, int ageAnnees, QString metier, QVector<QString>&images);
    QString CreerPatronyme(bool masculin = true);

    virtual std::shared_ptr<Effet> AjouterEffetUniversite(
            GenHistoire* genHist, std::shared_ptr<Evt> evt, QString go_to_effet_suivant );

    static QVector<QString> NOMS_M1;
    static QVector<QString> NOMS_M2;
    static QVector<QString> NOMS_M3;
    static QVector<QString> NOMS_F1;
    static QVector<QString> NOMS_F2;
    static QVector<QString> NOMS_F3;
};

#endif // ELFES_H
