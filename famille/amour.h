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
    // la mariée ou fiancée est forcément la première, les eprsonnages peuvent être transférées de l'une à l'autre dans les événements
    static QString PRE_COUPLE; // à utiliser quand les deux sont amoureux ou qu'ils sont au moins encore en couple
    static QString PRE_MAITRESSE; // triangles amoureux...
    static QString PRE_ELLE_AMOUREUSE; // triangles amoureux...
    static QString PRE_LUI_AMOUREUX; // triangles amoureux...
    static QString C_ETAT_AMOUREUX_M; // état amoureux de l'homme
    static QString C_ETAT_AMOUREUX_F; // .. de la femme
    static QString C_ETAT_MARITAL;
    static QString C_FAIT_LA_COUR; // "1" si fait la cour
    // valeurs de C_ETAT_MARITAL
    static QString CELIBATAIRE;
    static QString FIANCE;//
    static QString MARIE;
    static QString CONCUBIN;
    static QString REGULIERE;// relations sexuelle régulières sans engagement
    // valeurs de C_ETAT_AMOUREUX
    static QString INDIFERENT;
    static QString INTERESSE;
    static QString AMOUREUX;
    static QString ENGAGE; // engagé ensemble => pas plus d'un à la fois !!
    static QString MEPRIS; // et autres sentiments négatifs
    static QString AMOUREUX_OBSESSIONEL;

    void AjouterModifProbaSeduisant();

    static void GenererAmoureusePotentielle(QString prefixe, Humain* hum, std::shared_ptr<Effet> effetNarrationVide);
    static void GenererTombeAmoureux(Humain* hum, std::shared_ptr<Effet> effetNarrationVide);
    static void GenererAmoureuse(Humain* hum, std::shared_ptr<Effet> effetNarrationVide);
    static void GenererRencontreAmoureuse(Humain* hum, std::shared_ptr<Effet> effetNarrationVide); // mutuelle
};

#endif // AMOUR_H
