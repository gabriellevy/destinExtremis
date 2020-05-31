#include "humain.h"
#include "extremis.h"
#include "genviehumain.h"
#include "texte/jourapresjour.h"
#include "../destinLib/aleatoire.h"
#include "socio_eco/metier.h"
#include "geographie/quartier.h"
#include "humanite/pnj.h"
#include "socio_eco/classesociale.h"
#include "humanite/identite.h"

Humain* Humain::ME = nullptr;

Humain::Humain(QString nom):DPerso(nom, nom, nom, "")
{
    Humain::ME = this;
    m_JourApresJour = new JourApresJour();
}

void Humain::ActualisationPortrait()
{
    int age = this->GetValeurCaracAsInt(GenVieHumain::C_AGE)/12;
    QString metier = this->GetValeurCarac(Metier::C_METIER);
    QMap<QString, QString> map = GestCarac::GetGestionnaireCarac()->GetCaracsQHash();

    QString cheminImg = Identite::GenererPortraits(map, age);
    MajCheminImage(cheminImg);
}

bool Humain::EstLibre()
{
    return this->GetValeurCarac(GenVieHumain::C_LIBERTE) == "";
}

void Humain::InitialiserPerso()
{
}

bool Humain::ACeTrait(eTrait trait)
{
    return ( GetValeurCarac(Trait::GetNomTrait(trait)) == "1");
}

bool Humain::GagneCeTrait(eTrait trait, std::shared_ptr<Effet> effet)
{
    if ( !ACeTrait(trait)) {
        // perd le trait opposé :
        if ( Trait::GetTraitOppose(trait) != nb_Traits) {
            this->PerdCeTrait(Trait::GetTraitOppose(trait), effet);
        }
        QString nomTrait = Trait::GetNomTrait(trait);
        this->SetValeurACaracId(nomTrait, "1");
        effet->m_Texte += "\nVous gagnez " + nomTrait + ".";

        return true;
    }
    return false;
}

bool Humain::PerdCeTrait(eTrait trait, std::shared_ptr<Effet> effet)
{
    if ( ACeTrait(trait)) {
        QString nomTrait = Trait::GetNomTrait(trait);
        this->SetValeurACaracId(nomTrait, "1");
        effet->m_Texte += "\nVous perdez " + nomTrait + ".";

        return true;
    }
    return false;
}

Humain* Humain::GetHumainJoue()
{
    if ( Humain::ME == nullptr )
        Humain::ME = new Humain("inconnu ??");
    return ME;
}

int Humain::GetAge()
{
    return DPerso::GetValeurCaracAsInt(GenVieHumain::C_AGE);
}

QString Humain::GetValeurCarac(QString id)
{
    return DPerso::GetValeurCarac(id);
}


std::shared_ptr<Quartier> Humain::GetQuartierCourant()
{
    QString quartier = this->GetValeurCarac(QuartierEffets::C_QUARTIER_ACTUEL);
    if ( quartier == "") {
        quartier = this->GetValeurCarac(QuartierEffets::C_QUARTIER_HABITE);
        this->SetValeurACaracId(QuartierEffets::C_QUARTIER_ACTUEL, quartier);
    }
    return Extremis::QUARTIERS[quartier];
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
    ActualisationPortrait();
}

