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
class Coterie;

struct Quartier {
    Quartier(QString nom, QString desc, QString img, Coterie* cot = nullptr)
        :m_Nom(nom), m_Description(desc), m_Image(img), m_Coterie(cot) {
    }

    QString m_Nom;
    QString m_Description;
    QString m_Image;
    Coterie* m_Coterie; // pointeur simple sans responsabilité de le détruire
    double GetPoidsDemo();// 1.0 par défaut (poids normal de population)

    static QMap<QString, std::shared_ptr<Quartier>> QUARTIERS;
    static std::shared_ptr<Quartier> GetQuartierAleatoire(bool selonDemographie = false);
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
