#ifndef HUMAIN_H
#define HUMAIN_H

#include "../destinLib/gestionnairecarac.h"
#include "humanite/trait.h"
#include <QVector>
#include <memory>

class JourApresJour;

class Humain : public DPerso
{
    static Humain* ME;
    JourApresJour* m_JourApresJour;
    QVector<std::shared_ptr<Trait>> m_Traits = {};

public:
    Humain(QString nom);

    static Humain* GetHumainJoue();

    int GetAge();

    virtual QString GetValeurCarac(QString id);
    virtual int GetValeurCaracAsInt(QString id);
    virtual void ExecutionPostChangeCarac();
    virtual void InitialiserPerso();

    void AjouterTrait(eTrait trait);

};

#endif // HUMAIN_H
