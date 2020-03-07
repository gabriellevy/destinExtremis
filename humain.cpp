#include "humain.h"
#include "extremis.h"
#include "genviehumain.h"
#include "texte/jourapresjour.h"
#include "../destinLib/aleatoire.h"

Humain* Humain::ME = nullptr;

Humain::Humain(QString nom):DPerso(nom, nom, nom, "")
{
    Humain::ME = this;
    m_JourApresJour = new JourApresJour();
}

void Humain::InitialiserPerso()
{
    // génération des traits :
    int nb = 7 + Aleatoire::GetAl()->EntierInferieurA(12);
    while(nb-->0) {
        AjouterTrait(static_cast<eTrait>(Aleatoire::GetAl()->EntierInferieurA(eTrait::nb_Traits)));
    }
}

void Humain::AjouterTrait(eTrait etrait)
{
    shared_ptr<Trait> trait = make_shared<Trait>(etrait);
    this->SetValeurACaracId(trait->GetNom(), "1");
    m_Traits.push_back(trait);
}

Humain* Humain::GetHumainJoue()
{
    if ( Humain::ME == nullptr )
        Humain::ME = new Humain("inconnu ??");
    return ME;
}

int Humain::GetAge()
{
    return DPerso::GetValeurCaracAsInt(GenVieHumain::AGE);
}

QString Humain::GetValeurCarac(QString id)
{
    return DPerso::GetValeurCarac(id);
}

int Humain::GetValeurCaracAsInt(QString id)
{
    // cas particuliers où on ne rend aps directement la valeur associée :
    /*if ( id == Combat::C_FORCE_COMBAT) {
        int val = 1; //humain de base

        // ici on pourra ajouter ou retirer des points selon les caracs du perso (space marine = +2 par exemple
        // cf échelle des Combat.h

        return val;
    }*/

    return DPerso::GetValeurCaracAsInt(id);
}

void Humain::ExecutionPostChangeCarac()
{
    m_JourApresJour->RafraichirPhrases();
}

