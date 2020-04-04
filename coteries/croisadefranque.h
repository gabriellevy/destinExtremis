#ifndef CROISADEFRANQUE_H
#define CROISADEFRANQUE_H

#include "coterie.h"

class CroisadeFranque : public Coterie
{
public:
    CroisadeFranque();

    void GenererTraitCompatibles();
    QString GetNom();
    QString GetId();
    float GetPoidsDemo();

    QString GetDescription();
    QString GetDescriptionUniversite();
    QString GetImage();
    QString GetMusique();
    QString CreerPatronyme(bool masculin = true);

    virtual std::shared_ptr<Effet> AjouterEffetUniversite(
            GenHistoire* genHist, std::shared_ptr<Evt> evt, QString go_to_effet_suivant);

    static QVector<QString> PRENOMS_M;
    static QVector<QString> PRENOMS_F;
    static QVector<QString> NOMS;
};

#endif // CROISADEFRANQUE_H
