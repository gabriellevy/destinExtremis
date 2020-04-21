#ifndef CONQUISTADORS_H
#define CONQUISTADORS_H

#include "coterie.h"
#include "generateurnoeudsprobables.h"

class Conquistadors : public Coterie
{
public:
    Conquistadors();

    void GenererTraitCompatibles();
    QString GetNom();
    QString GetId();
    double GetPoidsDemo();

    QString GetDescription();
    QString GetDescriptionUniversite();
    QString GetImage();
    QString GetMusique();
    virtual QString GetGentile(bool masculin = true);
    virtual std::shared_ptr<Quartier> GenererQuartier();
    virtual void GenererPortraits(Humain* hum, int ageAnnees, QString metier, QVector<QString>&images);
    QString CreerPatronyme(bool masculin = true);

    virtual std::shared_ptr<Effet> AjouterEffetUniversite(
            GenHistoire* genHist, std::shared_ptr<Evt> evt, QString go_to_effet_suivant );

    static QVector<QString> PRENOMS_M;
    static QVector<QString> PRENOMS_F;
    static QVector<QString> NOMS;
};

class EvtConquistadors : public GenerateurNoeudsProbables
{
private:

public:
    EvtConquistadors(int indexEvt);
};

#endif // CONQUISTADORS_H
