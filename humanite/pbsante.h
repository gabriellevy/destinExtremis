#ifndef SANTE_H
#define SANTE_H

#include <QString>
#include <QMap>
#include "generateurnoeudsprobables.h"

class GenEvt;
class Effet;
class Condition;
class Humain;


/**
 * @brief Tout ce qui concerne la santé y compris la mort par vieillesse et les maladies
 */
class PbSante : public GenerateurNoeudsProbables
{
public:
    PbSante(int indexEvt);

    // caracs liées :
    static QString C_SANTE;
    static QString C_MOIS_HOPITAL;
    static QString C_CONSTITUTION; // influe sur espérance de vie
    // valeurs de C_CONSTITUTION "" = normal
    static QString RESISTANT;
    static QString FRELE;
    // valeurs de C_SANTE
    static QString MORT;
    static QString FOLIE;
    static QString PESTE;

    // diverses blessures légères recevables (booléens)
    static QString BORGNE;
    static QString BOITEUX;
    static QString CICATRICE_AU_VISAGE;
    static QString DOIGT_COUPE;
    static QString DEFIGURE; // a une blessure quelconque au visage
    // blessures graves
    static QString JAMBE_AMPUTEE;
    static QString BRAS_AMPUTEE;
    static QString TRAUMATISME_CRANIEN;
    static QString HEMORAGIE_INTERNE;
    static QString OREILLE_COUPEE;
    static QVector<QString> BLESSURES_LEGERES;
    static QVector<QString> BLESSURES_GRAVES;
    static QString GetBlessureLegereAleatoire();
    // maladies diverses semi graves
    static QString ALCOOLIQUE;

    static void BlessureLegere(Humain* hum, std::shared_ptr<Effet> effet, int& nbMoisHopital);
    static void BlessureGrave(Humain* hum, std::shared_ptr<Effet> effet, int& nbMoisHopital);

    static std::shared_ptr<Condition> AjouterModifProbaSiMort(std::shared_ptr<Condition> cond, double poidsProba);
    static std::shared_ptr<Condition> AjouterConditionSiVivant();
    static std::shared_ptr<Condition> AjouterConditionSiAgeSuperieurA(int ageAnnees);
};

#endif // SANTE_H
