#include "humain.h"
#include "extremis.h"
#include "genviehumain.h"
#include "texte/jourapresjour.h"
#include "../destinLib/aleatoire.h"
#include "socio_eco/metier.h"
#include "geographie/quartier.h"

Humain* Humain::ME = nullptr;

Humain::Humain(QString nom):DPerso(nom, nom, nom, "")
{
    Humain::ME = this;
    m_JourApresJour = new JourApresJour();
}

void Humain::ActualisationPortrait()
{
    QVector<QString> images = {};

    int age = this->GetValeurCaracAsInt(GenVieHumain::AGE)/12;
    QString metier = this->GetValeurCarac(Metier::C_METIER);
    QString strCoterie = this->GetValeurCarac(Coterie::C_COTERIE);
    if ( strCoterie != "" ) {
        shared_ptr<Coterie> coterie = Extremis::GetCoterie(strCoterie);

        coterie->GenererPortraits(this, age, metier, images);
    }

    if ( images.size() == 0 ) {
        if ( age > 15 ) {
            if ( age < 40 ) {
                images.push_back(":/images/portraits/portrait_15-40.jpg");
                images.push_back(":/images/portraits/portrait_15-40_b.jpg");
            }
        }

        if ( age > 20 ) {
            if ( age < 60 ) {
                images.push_back(":/images/portraits/portrait_bucheron_20-60.jpg");
                if ( age < 50 ) {
                    images.push_back(":/images/portraits/portrait_20-50.jpg");
                }
            }
        }
    }

    if ( images.size() == 0 )
        return;

    if ( m_SeedPortrait == -1 || m_SeedPortrait >= images.size() ||
         images.size() != m_NombreImagesPrecedent)
        m_SeedPortrait = Aleatoire::GetAl()->EntierInferieurA(images.size());

    m_NombreImagesPrecedent = images.size();
    MajCheminImage(images[m_SeedPortrait]);
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
        effet->m_Texte += "\nVous gagnez " + nomTrait;

        return true;
    }
    return false;
}

bool Humain::PerdCeTrait(eTrait trait, std::shared_ptr<Effet> effet)
{
    if ( ACeTrait(trait)) {
        QString nomTrait = Trait::GetNomTrait(trait);
        this->SetValeurACaracId(nomTrait, "1");
        effet->m_Texte += "\nVous perdez " + nomTrait;

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
    return DPerso::GetValeurCaracAsInt(GenVieHumain::AGE);
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

