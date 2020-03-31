#ifndef HUMAIN_H
#define HUMAIN_H

#include "../destinLib/gestionnairecarac.h"
#include <QVector>
#include <memory>
#include "humanite/trait.h"

class JourApresJour;

class Humain : public DPerso
{
    static Humain* ME;
    JourApresJour* m_JourApresJour;

public:
    Humain(QString nom);

    static Humain* GetHumainJoue();

    int GetAge();

    virtual QString GetValeurCarac(QString id);
    virtual int GetValeurCaracAsInt(QString id);
    virtual void ExecutionPostChangeCarac();
    virtual void InitialiserPerso();
    bool ACeTrait(eTrait trait);

};

#endif // HUMAIN_H
