#include "elfes.h"
#include "genviehumain.h"
#include "socio_eco/metier.h"
#include "../destinLib/aleatoire.h"

using std::make_shared;
using std::shared_ptr;

Elfes::Elfes()
{
    Initialisation();
}

void Elfes::GenererTraitCompatibles()
{
    m_TraitsCompatible = {
        make_shared<Trait>(eTrait::grand),
        make_shared<Trait>(eTrait::beau),
        make_shared<Trait>(eTrait::intelligent),
        make_shared<Trait>(eTrait::sensible),
        make_shared<Trait>(eTrait::habile),
        make_shared<Trait>(eTrait::artiste)
    };
    m_TraitsIncompatible = {
        make_shared<Trait>(eTrait::petit),
        make_shared<Trait>(eTrait::laid),
        make_shared<Trait>(eTrait::simple)
    };
}

QString Elfes::GetNom()
{
    return "Elfes";
}

QString Elfes::GetDescription()
{
    return "Description des Elfes";
}

QString Elfes::GetDescriptionUniversite()
{
    return "Les Elfes";
}

QString Elfes::GetImage()
{
    return ":/images/elfes/400px-Elfe.jpg";
}

QString Elfes::GetId()
{
    return Coterie::ELFES;
}

float Elfes::GetPoidsDemo()
{
    return 0.4;
}

std::shared_ptr<Effet> Elfes::AjouterEffetUniversite(GenHistoire* genHist, shared_ptr<Evt> evt, QString go_to_effet_suivant )
{
    QVector<shared_ptr<NoeudProbable>> noeudsProbaEducation;

    {
        shared_ptr<Effet> effet2 = genHist->AjouterEffetNarration("youpi temp " + GetNom() + " 0.8", "", "", evt);
        effet2->m_GoToEffetId = go_to_effet_suivant;
        shared_ptr<Condition> cond = make_shared<Condition>(0.8, TypeProba::p_Relative);
        shared_ptr<NoeudProbable> noeud = make_shared<NoeudProbable>(
                    effet2,
                    cond);
        noeudsProbaEducation.push_back(noeud);
    }

    // effet perd laid
    {
        shared_ptr<Effet> effet = genHist->AjouterEffetNarration(
                    "Votre laideur offense tellement vos maître qu'ils font une priorité de vous rendre présentable."
                    "Pour cela ils utilisent une myriades d'outils et d'objets merveilleux. Des pommades, des bains, des amulettes et même des potions enchantées."
                    "Le résultat est stupéfiant. "
                    "\nVous perdez la compétence 'laid'.",
                    ":/images/elfes/elfe_habille.jpg",
                    "", evt);
        effet->m_GoToEffetId = go_to_effet_suivant;
        effet->AjouterChangeurDeCarac(Trait::GetNomTrait(laid), "");
        Trait::AjouterConditionSiACeTrait(effet, laid);

        shared_ptr<Condition> cond = make_shared<Condition>(2.0, TypeProba::p_Relative);
        shared_ptr<NoeudProbable> noeud = make_shared<NoeudProbable>(
                    effet,
                    cond);
        noeudsProbaEducation.push_back(noeud);
    }

    // effet gagne beau
    {
        shared_ptr<Effet> effet = genHist->AjouterEffetNarration(
                    "La beauté est primorduiale pour els elfes et ils font en sorte que votre médiocrité ne soit aps un frein pour vous intégrer et vous sentir l'un des leurs. "
                    "Pour cela ils utilisent une myriades d'outils et d'objets merveilleux. Des pommades, des bains, des amulettes et même des potions enchantées."
                    "Le résultat est stupéfiant. "
                    "\nVous gagnez la compétence 'beau'.",
                    ":/images/elfes/elfe_royale.jpg",
                    "", evt);
        effet->m_GoToEffetId = go_to_effet_suivant;
        effet->AjouterChangeurDeCarac(Trait::GetNomTrait(beau), "1");
        Trait::AjouterConditionSiAPasCeTrait(effet, beau);

        shared_ptr<Condition> cond = make_shared<Condition>(1.0, TypeProba::p_Relative);
        shared_ptr<NoeudProbable> noeud = make_shared<NoeudProbable>(
                    effet,
                    cond);
        noeudsProbaEducation.push_back(noeud);
    }

    // effet devient artiste
    {
        shared_ptr<Effet> effet = genHist->AjouterEffetNarration(
                    "Tous les elfes doivent être artistes, sinon ils redeviennent lentement de simples humains. "
                    "L'université se doit de consacrer un grand nombre d'heures à rendre votre esprit ouvert à l'art et à la beauté.",
                    ":/images/elfes/musique_automne.jpg",
                    "", evt);
        effet->m_GoToEffetId = go_to_effet_suivant;
        effet->AjouterChangeurDeCarac(Trait::GetNomTrait(artiste), "1");
        Trait::AjouterConditionSiAPasCeTrait(effet, artiste);

        shared_ptr<Condition> cond = make_shared<Condition>(0.3, TypeProba::p_Relative);// difficile d'ajouter une carac à un eprso (artiste à partir de rien...)
        shared_ptr<NoeudProbable> noeud = make_shared<NoeudProbable>(
                    effet,
                    cond);
        noeudsProbaEducation.push_back(noeud);
    }

    // effet frustration sexuelle
    {
        shared_ptr<Effet> effet = genHist->AjouterEffetNarration(
                    "Vous êtes fasciné et tout émoustillé par la quantité incroyable de jeunes beautés que vous rencontrez à l'université elfique. "
                    "Malheureusement elles n'ont que mérpis et moquerie pour vous et votre physique médiocre.",
                    ":/images/elfes/jeune_elfe.jpg",
                    "", evt);
        effet->m_GoToEffetId = go_to_effet_suivant;
        double proba = Aleatoire::GetAl()->Entre0Et1();
        if ( proba < 0.6) {
            effet->AjouterChangeurDeCarac(Trait::GetNomTrait(angoisse), "1");
            effet->m_Texte += "\nVous en intériosez une forte angoisse sur votre propre valeur.";
        } else if (proba < 0.75) {
            effet->AjouterChangeurDeCarac(Trait::GetNomTrait(violent), "1");
            effet->m_Texte += "\nVous trouvez ça injuste et vous sentez profondément énervé contre elles et contre la société en général.";
        } else {
            effet->AjouterChangeurDeCarac(Trait::GetNomTrait(ambitieux), "1");
            effet->m_Texte += "\nVous décidez de vous concentrer sur votre propre amélioration et enrichissement pour un jour avoir votre chance avec une femme aussi belle";

        }
        Trait::AjouterConditionSiAPasCeTrait(effet, beau);

        shared_ptr<Condition> cond = make_shared<Condition>(0.5, TypeProba::p_Relative);// difficile d'ajouter une carac à un eprso (artiste à partir de rien...)
        shared_ptr<NoeudProbable> noeud = make_shared<NoeudProbable>(
                    effet,
                    cond);
        noeudsProbaEducation.push_back(noeud);
    }

    // effet devient Musicien
    {
        shared_ptr<Effet> effet = genHist->AjouterEffetNarration(
                    "Vu votre poentiel d'artiste les elfes trouvent indispensable de vous former à la musique, le plus noble de tous les arts.",
                    ":/images/elfes/elfe_musicien.jpg",
                    "", evt);
        effet->m_GoToEffetId = go_to_effet_suivant;
        effet->AjouterAjouteurACarac(Metier::MUSICIEN, "1");
        Trait::AjouterConditionSiACeTrait(effet, artiste);

        shared_ptr<Condition> cond = make_shared<Condition>(0.7, TypeProba::p_Relative);
        shared_ptr<NoeudProbable> noeud = make_shared<NoeudProbable>(
                    effet,
                    cond);
        noeudsProbaEducation.push_back(noeud);
    }

    // effet devient Poète
    {
        shared_ptr<Effet> effet = genHist->AjouterEffetNarration(
                    "Vu votre poentiel d'artiste les elfes trouvent indispensable de vous former à la poésie, la pierre angulaire de la sensibilité elfique.",
                    ":/images/elfes/poete.jpg",
                    "", evt);
        effet->m_GoToEffetId = go_to_effet_suivant;
        effet->AjouterAjouteurACarac(Metier::POETE, "1");
        Trait::AjouterConditionSiACeTrait(effet, artiste);

        shared_ptr<Condition> cond = make_shared<Condition>(0.7, TypeProba::p_Relative);
        shared_ptr<NoeudProbable> noeud = make_shared<NoeudProbable>(
                    effet,
                    cond);
        noeudsProbaEducation.push_back(noeud);
    }

    // effet devient Alchimiste
    {
        shared_ptr<Effet> effet = genHist->AjouterEffetNarration(
                    "La fabrication de potions, de filtres, de pommades est une composante essentielle de l'art elfique. "
                    "Leurs usages sont innombrables et vont de potions de soins aux meilleurs produits de beauté du monde. "
                    "Un maître herboriste détecte un certain potentiel chez vous et décide de vous apprendre les bases.",
                    ":/images/elfes/alchimiste.jpg",
                    "", evt);
        effet->m_GoToEffetId = go_to_effet_suivant;
        effet->AjouterAjouteurACarac(Metier::ALCHIMISTE, "1");

        shared_ptr<Condition> cond = make_shared<Condition>(0.7, TypeProba::p_Relative);
        shared_ptr<NoeudProbable> noeud = make_shared<NoeudProbable>(
                    effet,
                    cond);
        noeudsProbaEducation.push_back(noeud);
    }


    shared_ptr<Effet> effetSelecteur = genHist->m_GenerateurEvt->AjouterEffetSelecteurDEvt(
                noeudsProbaEducation);
    effetSelecteur->m_MsChrono = 1; // passé automatiquement

    return effetSelecteur;
}
