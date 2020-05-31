#ifndef IDENTITE_H
#define IDENTITE_H

#include <QString>
#include <QVector>
#include <QMap>

/**
 * @brief ce qui concerne les bases de l'identité du personnage à la naissance
 */
class Identite
{
public:
    static QVector<QString> PRENOMS;
    static QVector<QString> PRENOMS_FEMININS;
    static QVector<QString> NOMS;

    static QString CreerPatronyme(bool male = true);
    static QString GenererPortraits(QMap<QString, QString> /*caracs*/, int /*ageAnnees*/);
};

#endif // IDENTITE_H
