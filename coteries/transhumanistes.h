#ifndef TRANSHUMANISTES_H
#define TRANSHUMANISTES_H

#include "coterie.h"
#include "generateurnoeudsprobables.h"

class GenEvt;
class ExecEffet;
class Condition;
class Humain;
class Evt;


class Transhumanistes : public Coterie
{
public:
    Transhumanistes();

    void GenererTraitCompatibles();
    QString GetNom();
    QString GetId();
    double GetPoidsDemo();

    QString GetDescription();
    QString GetDescriptionUniversite();
    QString GetImage();
    virtual QString GetGentile(bool masculin = true);
    QString CreerPatronyme(bool masculin = true);
    void GenererPortraits(QMap<QString, QString> caracs, int ageAnnees, QVector<QString>&images);
    virtual std::shared_ptr<Quartier> GenererQuartier();
    virtual std::shared_ptr<Effet> AjouterEffetUniversite(
            GenHistoire* genHist, std::shared_ptr<Evt> evt, QString go_to_effet_suivant);
};

class EvtTranshumanistes : public GenerateurNoeudsProbables
{
private:

public:
    EvtTranshumanistes(int indexEvt);
};

#endif // TRANSHUMANISTES_H
