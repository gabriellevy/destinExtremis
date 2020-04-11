#ifndef Quartier_H
#define Quartier_H

#include <QString>
#include <QMap>
#include "generateurnoeudsprobables.h"

class GenEvt;
class GenHistoire;
class Effet;
class Evt;
class Condition;

struct Quartier {
    Quartier(QString nom, QString desc, QString img):m_Nom(nom), m_Description(desc), m_Image(img) {}

    QString m_Nom;
    QString m_Description;
    QString m_Image;


    static QMap<QString, std::shared_ptr<Quartier>> QUARTIERS;
    static void GenererQuartiersAdministratifs();
};

/**
 * @brief événements pouvant arriver dans les quartiers
 * emménagements, déménagements, problèmes localisés...
 */
class QuartierEffets : public GenerateurNoeudsProbables
{
public:
    QuartierEffets(int indexEvt);

    // caracs liées :
    static QString C_QUARTIER_HABITE;
    static QString C_QUARTIER_ACTUEL; // différent de l'habité lors des voyages etc

    static std::shared_ptr<Condition> AjouterCondHabiteCeQuartier(QString quartier);
    static std::shared_ptr<Condition> AjouterCondEstDansCeQuartier(QString quartier);

};

#endif // RELIGION_H
