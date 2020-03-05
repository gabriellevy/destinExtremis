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
    // valeurs de métiers :
    static QString INEMPLOYABLE; // quand le eprso n'est plus bon à rien (maladie extrêmement grave par ex)
    static QString PAYSAN;
    static QString MINEUR;
    static QString CHASSEUR_CUEILLEUR_NOMADE;
    static QString OUVRIER;
};

#endif // METIER_H
