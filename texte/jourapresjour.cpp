#include "jourapresjour.h"
#include "../destinLib/aleatoire.h"
#include "humain.h"
#include "socio_eco/classesociale.h"
#include "socio_eco/metier.h"
#include "genviehumain.h"
#include "coteries/coterie.h"

QVector<Phrase> JourApresJour::PHRASES = {};

JourApresJour::JourApresJour()
{
    RafraichirPhrases();
}

void JourApresJour::RafraichirPhrasesSelonMetier(QString /*classeSociale*/, QString metier)
{
    Humain* humain = Humain::GetHumainJoue();
    if (metier == Metier::PAYSAN)
    {
        JourApresJour::PHRASES.push_back(Phrase("Encore une journée de récolte de blé."));
        JourApresJour::PHRASES.push_back(Phrase("Encore une journée de récolte de patates."));
        JourApresJour::PHRASES.push_back(Phrase("Encore une journée de récolte de riz."));
        JourApresJour::PHRASES.push_back(Phrase("Encore une journée de récolte de céréales."));
        JourApresJour::PHRASES.push_back(Phrase("Encore une journée de récolte de légumes."));
        JourApresJour::PHRASES.push_back(Phrase("Vous avez essentiellement abattu des têtes de bétail ces jours-ci."));
        JourApresJour::PHRASES.push_back(Phrase("Les Grox se tiennent à carreau et se nourrissent normalement."));
        JourApresJour::PHRASES.push_back(Phrase("La ponte d'oeufs géants a été bonne."));
        JourApresJour::PHRASES.push_back(Phrase("Vous avez récolté des champignons géants comestibles."));
        JourApresJour::PHRASES.push_back(Phrase("Vous avez chargé des milliers de tonnes d'eau potable pour les mondes ruches."));
        JourApresJour::PHRASES.push_back(Phrase("La pêche devrait suffire à remplir vos quotas du mois."));
        JourApresJour::PHRASES.push_back(Phrase("La récolte d'algues nutritive est satisfaisante."));
    } else if ( metier == Metier::PARASITE) {
        if (humain->ACeTrait(beau) || humain->ACeTrait(charmeur)) {
            JourApresJour::PHRASES.push_back(Phrase("Vous emballez la grande clémence avec un sourire et des belles paroles. "
                                                    "Elle n'est pas très jolie mais elle a de l'argent. En la jouant fine vous êtes à l'abri du besoin pour un moment."));
        }
        JourApresJour::PHRASES.push_back(Phrase("Vous avez réussi à vous mettre en bonne relation avec tout le quartier. "
                                      "En faisant tourner les voisins vous arrivez à vous faire inviter à manger presque tous les jours !"));
    }
}

void JourApresJour::RafraichirPhrasesSelonCoterie(QString coterie)
{
    if ( coterie ==  Coterie::CATHARES ||
         coterie == Coterie::CONQUISTADORS) {
        // christianisme post moyen-âge
        JourApresJour::PHRASES.push_back(
                    Phrase("Pensée de Pascal du jour : "
                           "\nIl est dangereux de trop faire croire à l'homme combien il est égal aux bêtes, sans lui montrer sa grandeur."
                           "Il est encore dangereux de lui trop faire voir sa grandeur sans sa bassesse."
                           "Il est encore plus dangereux de lui laisser ignorer l'un et l'autre, mais il est très avantageux de lui représenter l'un et l'autre."
                           "\n\nIl ne faut pas que l'homme croie qu'il est égal aux bêtes, ni aux anges, ni qu'il ignore l'un et l'autre, mais qu'il sache l'une t l'autre.")
                    );
    }
}

void JourApresJour::RafraichirPhrases()
{
    JourApresJour::PHRASES.clear();

    Humain* humain = Humain::GetHumainJoue();
    // extraire les critères qui influent sur les textes/événements possibles :
    QString classeSociale = humain->GetValeurCarac(ClasseSociale::C_CLASSE_SOCIALE);
    QString metier = humain->GetValeurCarac(Metier::C_METIER);
    QString liberte = humain->GetValeurCarac(GenVieHumain::C_LIBERTE);
    QString coterie = humain->GetValeurCarac(Coterie::C_COTERIE);

    RafraichirPhrasesSelonCoterie(coterie);

    if ( liberte == "" ) // si libre
    {
        // pas d'actions de métier si on est enfermé
        RafraichirPhrasesSelonMetier(classeSociale, metier);

        JourApresJour::PHRASES.push_back(
                    Phrase("Vous mettez la main sur une bouteille d'Aasec de bonne qualité."));
        JourApresJour::PHRASES.push_back(
                    Phrase("Vous buvez un verre de Dammassine au bon goût d'herbe et d'amande."));
        JourApresJour::PHRASES.push_back(
                    Phrase("Une famille d'amis vous invite à boire un petit Recaf avec des biscuits Nafar."));
        JourApresJour::PHRASES.push_back(
                    Phrase("Vous mangez un bon rôti de Grox."));
    }


    if ( classeSociale == ClasseSociale::MISERABLES ) {
        JourApresJour::PHRASES.push_back(
                    Phrase("Encore une bonne bouillie de déchets organiques recyclés comme repas", ""));
        JourApresJour::PHRASES.push_back(
                    Phrase("La fatigue et la déprime est telle après cette journée épuisante que vous vous laissez aller à boire de l'immonde Torboyo. "
                           "Espérons que vous ne serez pas aveugle demain.",
                           ""));

    } else
    {
        // les non misérables :
        JourApresJour::PHRASES.push_back(
                    Phrase("Plaisir rare dans votre vie harassante : vous partagez une bonne bouteille de Whiskar avec vos amis. "
                           "Le serpent mort qui s'y trouve prouve que c'est de la qualité",
                           ""));

    }
    if ( classeSociale == ClasseSociale::PAUVRES) {
        JourApresJour::PHRASES.push_back(
                    Phrase("Encore une bonne bouillie de déchets organiques recyclés comme repas", ""));
        JourApresJour::PHRASES.push_back(
                    Phrase("La fatigue et la déprime est telle après cette journée épuisante que vous vous laissez aller à boire de l'immonde Torboyo. "
                           "Espérons que vous ne serez pas aveugle demain.",
                           ""));

    } else if ( classeSociale == ClasseSociale::CLASSE_MOYENNE ) {
        JourApresJour::PHRASES.push_back(
                    Phrase("Encore une bonne bouillie de déchets organiques recyclés comme repas"));

    } else if ( classeSociale == ClasseSociale::INFLUENTS ) {

    } else if ( classeSociale == ClasseSociale::MAITRES ) {
        JourApresJour::PHRASES.push_back(
                    Phrase(
                        "Encore une délicieuse journée sur le satelitte privé de divertissement de votre famille, à chevaucher les nuages boréals multicolores.",
                        ":/images/socio_eco/FemmeNobleApparat.jpg"));
        JourApresJour::PHRASES.push_back(
                    Phrase(
                        "Vous avez goûté un vin délicieux. Si délicieux que vous avez décidé de réduire le village qui le produit en esclavage.",
                        ":/images/socio_eco/GrosNoble.png"));
    }

    if ( PHRASES.length() == 0 )
        JourApresJour::PHRASES.push_back(
                    Phrase("Il ne se passe rien."));
}

Phrase JourApresJour::ExtrairePhrase()
{
    return JourApresJour::PHRASES[Aleatoire::GetAl()->EntierInferieurA(PHRASES.length())];
}
