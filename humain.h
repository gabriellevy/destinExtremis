#ifndef HUMAIN_H
#define HUMAIN_H

#include "../destinLib/gestionnairecarac.h"
#include <QVector>
#include <memory>
#include "humanite/trait.h"


class Effet;
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
    bool GagneCeTrait(eTrait trait, std::shared_ptr<Effet> effet);
    bool PerdCeTrait(eTrait trait, std::shared_ptr<Effet> effet);

};

#endif // HUMAIN_H
