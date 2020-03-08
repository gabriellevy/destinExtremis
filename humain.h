#ifndef HUMAIN_H
#define HUMAIN_H

#include "../destinLib/gestionnairecarac.h"
#include <QVector>
#include <memory>

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

};

#endif // HUMAIN_H
