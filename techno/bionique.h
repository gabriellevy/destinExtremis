#ifndef BIONIQUE_H
#define BIONIQUE_H

#include <QString>
#include <QMap>
#include "generateurnoeudsprobables.h"

class GenEvt;
class Effet;
class Condition;
class Humain;


class Bionique : public GenerateurNoeudsProbables
{
public:
    Bionique(int indexEvt);

    static std::shared_ptr<Condition> AjouterConditionSiBioniqueLongeviteSuperieureA(int nbBionique);
    static std::shared_ptr<Condition> AjouterConditionSiBioniqueLongeviteInferieurA(int nbBionique);

    static QString C_BIONIQUE_LONGEVITE; // nombre de bioniques ajouté au corps pour augmenter la longévité
    static QString C_FABRICATION_BIONIQUE; // niveau en conception et fabrication de bionique (entre ingénieur et médecin)

    static QString AppliquerBionique(Humain* hum, QString id = ""); // fonction runtime

    // liste de bioniques existants (booléens essentiellement)
    static QString C_OEIL_BIONIQUE; // infrarouge, zoom
    static QString C_JAMBE_BIONIQUE;
    static QString C_BRAS_BIONIQUE;
    static QString C_STIMULANT_REFLEXE;
    static QString C_OS_RENFORCES; // os renforcés avec divers matériaux
    static QVector<QString> TOUS_LES_BIONIQUES;
};

#endif // BIONIQUE_H
