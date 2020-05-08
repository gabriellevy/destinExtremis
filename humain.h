#ifndef HUMAIN_H
#define HUMAIN_H

#include "../destinLib/gestcarac.h"
#include <QVector>
#include <memory>
#include "humanite/trait.h"


class Effet;
class JourApresJour;
class Quartier;

class Humain : public DPerso
{
    static Humain* ME;
    JourApresJour* m_JourApresJour;
    int m_SeedPortrait = -1;
    int m_NombreImagesPrecedent = -1;

public:
    Humain(QString nom);

    static Humain* GetHumainJoue();

    int GetAge();

    virtual QString GetValeurCarac(QString id);
    virtual int GetValeurCaracAsInt(QString id);
    virtual void ExecutionPostChangeCarac();
    virtual void InitialiserPerso();
    bool EstLibre();
    bool ACeTrait(eTrait trait);
    bool GagneCeTrait(eTrait trait, std::shared_ptr<Effet> effet);
    bool PerdCeTrait(eTrait trait, std::shared_ptr<Effet> effet);
    std::shared_ptr<Quartier> GetQuartierCourant();

    /**
     * @brief met à jour le portrait du personnage sleon ses caracs actuelles
     * à Appeler quand il change  de carac mais avec un aléatoire "seed" fixe qui fait que l'image ne change aps à chaque actualisation amis seulement si une carac déterminante a changée
     */
    void ActualisationPortrait();
};

#endif // HUMAIN_H
