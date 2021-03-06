#ifndef CLASSESOCIALE_H
#define CLASSESOCIALE_H

#include <QString>
#include <QMap>
#include "generateurnoeudsprobables.h"

class GenEvt;
class Effet;
class Condition;

/**
 * @brief événements liés à la classe sociale des personnages
 */
class ClasseSociale : public GenerateurNoeudsProbables
{
public:
    ClasseSociale(int indexEvt);

    static std::shared_ptr<Condition> GenConditionSiDeCetteClasseSociale(QString classeSociale);
    static std::shared_ptr<Condition> AjouterConditionSiClasseSocialeSuperieureA(int classeSociale);
    static std::shared_ptr<Condition> AjouterConditionSiClasseSocialeSuperieureA(QString classeSociale);

    static QString GetClasseSocialeAleatoire();

    // caracs :
    static QString C_CLASSE_SOCIALE; // noté de 0(misérable) à 4 (seigneurs de coteries)
    // valeurs de caracs :
    static QString MISERABLES; // dépourvus de logement et de métier, mendiants...
    static QString PAUVRES; // travaillerrs non qualifiés
    static QString CLASSE_MOYENNE;// travailleurs qualifiés
    static QString INFLUENTS; // commerçants, financiers, trafiqueurs d'inflence
    static QString MAITRES; // gouverneurs impériaux, maîtres de la ruche, planète etc..
    static QVector<QString> CLASSES_SOCIALES;

};

#endif // CLASSESOCIALE_H
