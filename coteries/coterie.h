#ifndef COTERIE_H
#define COTERIE_H

#include <QVector>
#include "humanite/trait.h"
#include <memory>

class Effet;
class Evt;
class GenHistoire;
class Condition;
class Humain;
class Quartier;

class Coterie
{
protected:
    QVector<std::shared_ptr<Condition>> m_TraitsCompatible = {}; // si true pour le joueur alors il est compatible à la coterie
    QVector<std::shared_ptr<Condition>> m_TraitsIncompatible = {}; // si true pour le joueur alors il est incompatible à la coterie

public:
    Coterie();
    virtual ~Coterie() {}

    std::shared_ptr<Quartier> m_Quartier;

    void Initialisation();

    virtual void GenererTraitCompatibles() = 0;
    virtual QString GetNom() = 0;
    virtual QString CreerPatronyme(bool masculin = true) = 0;
    virtual QString GetId() = 0;
    virtual QString GetDescription() = 0;
    virtual QString GetDescriptionUniversite() = 0;
    virtual QString GetImage() = 0;
    virtual std::shared_ptr<Quartier> GenererQuartier();
    /**
     * @return id de la musique de cette faction. Aucune par défaut. Peut tout à fait contenir une liste de musique dont une aléatoire (ou déterminée par calcul) est renvoyée
     */
    virtual QString GetMusique();
    virtual double GetPoidsDemo() = 0; // poids démographique. 1 = normal, 0.1 très très faible, 2 énorme
    /**
     * @brief Calcul la compatibilité entre le joueur et cette coterie.
     * @param aleatoire résultat semi aléatoire  si true (pour 50% de al valeur grosso modo
     * @return < à 0 = ennemis ; < 0.5 = mauvais ; > 1 = excellente compatibilité
     */
    virtual double Compatibilite(Humain* hum, bool aleatoire = false);
    /**
     * @brief Fonction runtime exécutée quand un eprsonnage rejoint cette coetrie.
     * A surclasser dès que la coterie implique des effets particuliers quand on la rejoint (en appelant tout de même cette fonction super)
     */
    virtual void RejoindreCoterie(Humain* hum, std::shared_ptr<Effet> eff);

    virtual std::shared_ptr<Effet> AjouterEffetUniversite(
            GenHistoire* genHist, std::shared_ptr<Evt> evt, QString go_to_effet_suivant) = 0;

    static QVector<std::shared_ptr<Coterie>> GetNRandomCoteries(int nombre, bool selonPoidsDemographique = false);
    static std::shared_ptr<Coterie> GetCoterieAleatoire(bool selonPoidsDemographique = false);

    static void AjouterModifProbaSiDeCetteCoterie(Condition* CondProba, double proba, QString nomCoterie);

    QVector<QString> m_MetiersAssocies = {}; // métiers particulièrement prisés/contrôlés par la coterie.

    static QString C_COTERIE;
    // valeurs de C_COTERIE
    static QString CONQUISTADORS;
    static QString CATHARES;
    static QString CELTES;
    static QString CROISADE;
    static QString ELFES;
    static QString ORKS;
    static QString TYRANIDES;
};

#endif // COTERIE_H
