#ifndef PNJ_H
#define PNJ_H

#include <memory>
#include <QString>

class Coterie;

enum Sexe {
    es_Masculin,
    es_Feminin,
    es_Aleatoire
};

class PNJ
{
public:
    PNJ();

    std::shared_ptr<Coterie> m_Coterie;
    QString m_Nom;
    bool m_SexeMasculin;

    /**
     * @brief génère un perso aléatoire sauf pour les param fournis
     * @param sexeMasculin
     * @param coterie
     * @return
     */
    static std::shared_ptr<PNJ> GenererPersoAleatoire(
            Sexe sexe = es_Aleatoire, std::shared_ptr<Coterie> coterie = nullptr);
};

#endif // PNJ_H
