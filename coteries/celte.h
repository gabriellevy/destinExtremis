#ifndef CELTE_H
#define CELTE_H

#include "coterie.h"


class Celte : public Coterie
{
public:
    Celte();

    void GenererTraitCompatibles();
    QString GetNom();
    QString GetId();
    float GetPoidsDemo();

    QString GetDescription();
    QString GetDescriptionUniversite();
    QString GetImage();
    QString GetMusique();
    virtual std::shared_ptr<Quartier> GenererQuartier();
    QString CreerPatronyme(bool masculin = true);
    virtual std::shared_ptr<Effet> AjouterEffetUniversite(
            GenHistoire* genHist, std::shared_ptr<Evt> evt, QString go_to_effet_suivant );


    static QVector<QString> PRENOMS_M;
    static QVector<QString> PRENOMS_F;
    static QVector<QString> NOMS_M;
    static QVector<QString> NOMS_F;
};

#endif // CELTE_H
