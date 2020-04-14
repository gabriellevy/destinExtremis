#ifndef AMOUR_H
#define AMOUR_H

#include <QString>
#include <QMap>
#include "generateurnoeudsprobables.h"

class GenEvt;
class GenHistoire;
class Effet;
class Evt;
class Condition;
class Humain;

class Amour : public GenerateurNoeudsProbables
{
public:
    Amour(int indexEvt);

    // caracs liées :
    // pas forcément amoureuse, ça peut être juste le perso qui est amoureux d'elle
    // la mariée ou fiancée est forcément la première
    static QString PRE_AMOUREUSE1;
    static QString PRE_AMOUREUSE2; // triangles amoureux...
    static QString PRE_AMOUREUSE3; // triangles amoureux...
    static QString C_ETAT_AMOUREUX;
    static QString C_ETAT_MARITAL;
    // valeurs de C_ETAT_MARITAL
    static QString CELIBATAIRE;
    static QString FIANCE;//
    static QString MARIE;
    static QString CONCUBIN;
    static QString REGULIERE;// relations sexuelle régulières sans engagement
    // valeurs de C_ETAT_AMOUREUX
    static QString LUI_AMOUREUX; // et pas elle
    static QString ELLE_AMOUREUX; // et pas lui
    static QString AMOUREUX; // les deux

    static void GenererRencontreAmoureuse(Humain* hum, std::shared_ptr<Effet> effetNarrationVide);
};

#endif // AMOUR_H
