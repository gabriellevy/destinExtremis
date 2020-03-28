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
    float GetPoidsDemo();

    QString GetDescription();
    QString GetDescriptionUniversite();
    QString GetImage();
    QString CreerPatronyme(bool masculin = true);

    virtual std::shared_ptr<Effet> AjouterEffetUniversite(
            GenHistoire* genHist, std::shared_ptr<Evt> evt, QString go_to_effet_suivant );

    static QVector<QString> NOMS_M;
    static QVector<QString> NOMS_F;
};

#endif // TYRANIDES_H
