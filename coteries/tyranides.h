#ifndef TYRANIDES_H
#define TYRANIDES_H

#include "coterie.h"

class Tyranides : public Coterie
{
public:
    Tyranides();

    void GenererTraitCompatibles();
    QString GetNom();
    QString GetId();
    double GetPoidsDemo();

    QString GetDescription();
    QString GetDescriptionUniversite();
    QString GetImage();
    virtual QString GetIcone(){ return ":/images/tyranides/icone.jpg";}
    virtual QString GetGentile(bool masculin = true);
    virtual std::shared_ptr<Quartier> GenererQuartier();
    QString CreerPatronyme(bool masculin = true);

    virtual std::shared_ptr<Effet> AjouterEffetUniversite(
            GenHistoire* genHist, std::shared_ptr<Evt> evt, QString go_to_effet_suivant );

    static QVector<QString> NOMS_M;
    static QVector<QString> NOMS_F;
};

#endif // TYRANIDES_H
