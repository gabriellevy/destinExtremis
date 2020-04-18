#ifndef CROISADEFRANQUE_H
#define CROISADEFRANQUE_H

#include "coterie.h"
#include <QString>
#include <QMap>
#include "generateurnoeudsprobables.h"

class GenEvt;
class ExecEffet;
class Condition;
class Humain;

class CroisadeFranque : public Coterie
{
public:
    CroisadeFranque();

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
            GenHistoire* genHist, std::shared_ptr<Evt> evt, QString go_to_effet_suivant);

    static QVector<QString> PRENOMS_M;
    static QVector<QString> PRENOMS_F;
    static QVector<QString> NOMS;
};

class EvtCroisadeFranque : public GenerateurNoeudsProbables
{
private:

public:
    EvtCroisadeFranque(int indexEvt);
};

#endif // CROISADEFRANQUE_H
