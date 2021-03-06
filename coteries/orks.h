#ifndef ORKS_H
#define ORKS_H

#include "coterie.h"
#include "generateurnoeudsprobables.h"

class GenEvt;
class ExecEffet;
class Condition;
class Humain;
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
    virtual QString GetIcone(){ return ":/images/orks/icone.jpg";}
    virtual QString GetGentile(bool masculin = true);
    QString CreerPatronyme(bool masculin = true);
    void GenererPortraits(QMap<QString, QString> caracs, int ageAnnees, QVector<QString>&images);
    QString GetMusique();
    virtual std::shared_ptr<Quartier> GenererQuartier();
    virtual std::shared_ptr<Effet> AjouterEffetUniversite(
            GenHistoire* genHist, std::shared_ptr<Evt> evt, QString go_to_effet_suivant);
    virtual void RejoindreCoterie(Humain* hum, std::shared_ptr<Effet> eff);
    virtual double GetCoeffSeduction() {return 0.2;}

    static QVector<QString> NOMS_M;
    static QVector<QString> NOMS_F;
};

class EvtOrks : public GenerateurNoeudsProbables
{
private:

public:
    EvtOrks(int indexEvt);
};

#endif // ORKS_H
