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

class Templiers : public Coterie
{
public:
    Templiers();

    void GenererTraitCompatibles();
    QString GetNom();
    QString GetId();
    double GetPoidsDemo();

    QString GetDescription();
    QString GetDescriptionUniversite();
    virtual QString GetIcone(){ return ":/images/croisade_franque/icone.png";}
    QString GetImage();
    QString GetMusique();
    virtual QString GetGentile(bool masculin = true);
    virtual std::shared_ptr<Quartier> GenererQuartier();
    void GenererPortraits(QMap<QString, QString> caracs, int ageAnnees, QVector<QString>&images);
    QString CreerPatronyme(bool masculin = true);

    virtual std::shared_ptr<Effet> AjouterEffetUniversite(
            GenHistoire* genHist, std::shared_ptr<Evt> evt, QString go_to_effet_suivant);

    static QVector<QString> PRENOMS_M;
    static QVector<QString> PRENOMS_F;
    static QVector<QString> NOMS;
};

class EvtTempliers : public GenerateurNoeudsProbables
{
private:

public:
    EvtTempliers(int indexEvt);
};

#endif // CROISADEFRANQUE_H
