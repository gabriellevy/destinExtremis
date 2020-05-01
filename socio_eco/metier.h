#ifndef METIER_H
#define METIER_H

#include <QString>
#include <QMap>
#include "generateurnoeudsprobables.h"

class GenEvt;
class Effet;
class Condition;

class Metier : public GenerateurNoeudsProbables
{
public:
    Metier(int indexEvt);

    static QMap<QString, Metier*> METIERS;

    static std::shared_ptr<Condition> AjouterConditionSiAMetier();
    static std::shared_ptr<Condition> AjouterConditionSiACeMetier(QString metier);
    static std::shared_ptr<Condition> AjouterConditionSiAPasMetier();
    static QList<QString> METIERS_INTEGRES; //  métiers où la criminalité est extrêmement faible

    static QString C_METIER;
    // valeurs de C_METIER :
    // ATTENTION : les noms de métier snt à la fois la valeur de la carac C_METIER pour indiquer le métier du perso
    // PLUS un nom de carac en soi qui indique le niveau (1 à 10) du personnage dans ce métier
    static QString INEMPLOYABLE; // quand le eprso n'est plus bon à rien (maladie extrêmement grave par ex)
    static QString PAYSAN;
    static QString MINEUR;
    static QString PRETRE;
    static QString OUVRIER;
    static QString POLITIQUE;
    static QString FORGERON;
    static QString MUSICIEN;
    static QString CARTOGRAPHE;
    static QString MARCHAND;
    static QString POETE;
    static QString ALCHIMISTE;
    static QString MEDECIN;
    static QString GUERRIER;
    static QString CONDUCTEUR; // pilote / chauffeur
    static QString PILOTE; // pilote d'aéronef
    static QString TUEUR_DE_MONSTRE; //  au sens large adapté selon la coterie et sa définition de monstre
    static QString ARCHITECTE;
    static QString INFORMATICIEN;
    static QString CYBERNETICIEN;
    static QString GENETICIEN;
    static QString COMMERCIAL;
    static QString PARASITE; // type qui ne bosse jaamis mais est très doué pour vivre aux dépens des autres

    // correspond au niveau de la carac du métier du personnage
    // un personnage qui a PAYSAN en C_METIER et 4 en carac PAYSAN doit avoir 4 en carac C_COMPETENCE_METIER
    static QString C_COMPETENCE_METIER;

};

#endif // METIER_H
