#include "orks.h"
#include "genviehumain.h"
#include "../destinLib/aleatoire.h"
#include "humanite/pbsante.h"
#include "violence/combat.h"
#include "techno/ingenieur.h"
#include "techno/vehicule.h"
#include "techno/bionique.h"
#include "socio_eco/metier.h"
#include "../destinLib/exec/exechistoire.h"
#include "humain.h"
#include "../destinLib/abs/condition.h"
#include "geographie/quartier.h"
#include <QDebug>

using std::make_shared;
using std::shared_ptr;

Orks::Orks()
{
    Initialisation();
}

shared_ptr<Quartier> Orks::GenererQuartier()
{
    m_Quartier = make_shared<Quartier>("Poissy", "Quartier des Orks", ":/images/orks/quartier.jpg", this);
    Quartier::QUARTIERS[m_Quartier->m_Nom] = m_Quartier;
    return m_Quartier;
}

QString Orks::GetGentile(bool masculin)
{
    return "ork";
}

void Orks::GenererTraitCompatibles()
{
    m_TraitsCompatible = {
        make_shared<Condition>(Trait::GetNomTrait(eTrait::violent), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::pragmatique), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::franc), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::paresseux), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::faible), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::simple), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::angoisse), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::fort), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::resistant), "1", Comparateur::c_Egal ),
        make_shared<Condition>(PbSante::DEFIGURE, "1", Comparateur::c_Egal )
    };
    m_TraitsIncompatible = {
        make_shared<Condition>(Trait::GetNomTrait(eTrait::ambitieux), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::intellectuel), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::industrieux), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::sensible), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::altruiste), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::sens_du_sacrifice), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::pacifiste), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::charmeur), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::spirituel), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::artiste), "1", Comparateur::c_Egal )
    };
    m_MetiersAssocies = {
        Metier::PARASITE,
        Metier::GUERRIER,
        Metier::CONDUCTEUR
    };
}

double Orks::GetPoidsDemo()
{
    return 1.1;
}

QString Orks::GetNom()
{
    return "Orks";
}

QString Orks::GetDescription()
{
    return "Description des Orks";
}

QString Orks::GetMusique()
{
    return "qrc:/sons/orks/Skyrim.mp3";
}

QString Orks::GetDescriptionUniversite()
{
    return "Les orks sont des mutants qui embrassent avant tout une vie simple et brutale sans prise de tête.";
}

QString Orks::GetId()
{
    return Coterie::ORKS;
}

QString Orks::GetImage()
{
    return ":/images/orks/mekano.PNG";
}

QString Orks::CreerPatronyme(bool masculin)
{
    return (masculin?
               NOMS_M[Aleatoire::GetAl()->EntierInferieurA(NOMS_M.size())]:
               NOMS_F[Aleatoire::GetAl()->EntierInferieurA(NOMS_F.size())]
            );
}

void Orks::RejoindreCoterie(Humain* hum, shared_ptr<Effet> eff)
{
    // fonction de base
    Coterie::RejoindreCoterie(hum, eff);

    // transformation en ork
    eff->m_Texte += "\nVous prenez enfin le redouté sérum d'orkission qui fera de vous un véritable ork.";
    double scoreTransformation = Aleatoire::GetAl()->Entre0Et1();
    if ( hum->ACeTrait(franc)) scoreTransformation += 0.01;
    if ( hum->ACeTrait(fort)) scoreTransformation += 0.05;
    if ( hum->ACeTrait(resistant)) scoreTransformation += 0.05;
    if ( hum->ACeTrait(violent)) scoreTransformation += 0.05;
    if ( hum->ACeTrait(industrieux)) scoreTransformation -= 0.02;
    if ( hum->ACeTrait(intelligent)) scoreTransformation -= 0.02;
    if ( hum->ACeTrait(angoisse)) scoreTransformation -= 0.02;
    if ( hum->ACeTrait(faible)) scoreTransformation -= 0.03;
    if ( hum->ACeTrait(chetif)) scoreTransformation -= 0.03;
    if ( hum->ACeTrait(intellectuel)) scoreTransformation -= 0.02;
    if ( scoreTransformation < 0) {
        eff->m_Texte += "Malheureusement le résultat est catastrophique. Votre faible volonté ou juste la malchance font de vous un simple gretchin. Esclave pitoyable des ork que vous rêviez d'être.";
        hum->GagneCeTrait(petit, eff);
        hum->GagneCeTrait(chetif, eff);
        hum->GagneCeTrait(faible, eff);
    } else  if ( scoreTransformation > 1 ) {
        eff->m_Texte += "Le résultat dépasse toutes vos espérances. Vous devenez un gros et errible nob. Un chef né tout en muscle à la mesure des orks.";
        hum->GagneCeTrait(fort, eff);
        hum->GagneCeTrait(resistant, eff);
        hum->GagneCeTrait(grand, eff);
    } else  {
        eff->m_Texte += "Cela marche à merveille. Vous sentez votre corps se renforcer, votre esprit se libérer. Vous êtes maintenant un ork !";
        hum->GagneCeTrait(resistant, eff);
    }
    hum->PerdCeTrait(angoisse, eff);
    hum->PerdCeTrait(pacifiste, eff);
    hum->GagneCeTrait(laid, eff);

    // guérison des blessures :
    for ( QString blessure: PbSante::BLESSURES_LEGERES) {
        if ( hum->GetValeurCarac(blessure) == "1") {
            scoreTransformation = Aleatoire::GetAl()->Entre0Et1();
            if ( scoreTransformation >= 0.2) {
                eff->m_Texte +="\nL'incroyable pouvoir de régénération du sérum ork fait que vous n'êtes plus " + blessure + ".";
                hum->SetValeurACaracId(blessure, "");
            }
        }
    }
}

std::shared_ptr<Effet> Orks::AjouterEffetUniversite(GenHistoire* genHist, shared_ptr<Evt> evt, QString go_to_effet_suivant )
{
    QVector<shared_ptr<NoeudProbable>> noeudsProbaEducation;

    // blessure dans la fosse
    {
        QString blessure = PbSante::GetBlessureLegereAleatoire();
        shared_ptr<Effet> effet1 = genHist->AjouterEffetNarration(
                    "Au cours d'un entrainement au combat dans les fosses vous recevez une blessure : " + blessure +
                    "\nLes orks en rigolent un bon coup et vous tappent dans le dos joyeusement. \"Tu verras quand tu s'ras un vrai ork ça r'poussera\"",
                    ":/images/orks/Combat_fosse.jpg",
                    "", evt);
        effet1->AjouterChangeurDeCarac(blessure, "1");
        effet1->AjouterChangeurDeCarac(PbSante::DEFIGURE, "1");
        effet1->AjouterAjouteurACarac(Combat::C_CAP_COMBAT, "1"); // meilleur combattant
        effet1->AjouterChangeurDeCarac((make_shared<Trait>(eTrait::beau))->GetNom(), ""); // le joueur perd son éventuelle beauté...
        effet1->m_GoToEffetId = go_to_effet_suivant;
        shared_ptr<Condition> cond1 = make_shared<Condition>(1.3, TypeProba::p_Relative);
        shared_ptr<NoeudProbable> noeud1 = make_shared<NoeudProbable>(
                    effet1,
                    cond1);
        noeudsProbaEducation.push_back(noeud1);
    }

    // fou de la vitesse
    {
        shared_ptr<Effet> effet1 = genHist->AjouterEffetNarration(
                    "Tout ork se doit de savoir piloter les bolides et aimer la vitesse. Vos instructeurs font en sorte que vous fassiez un bon paquet de tours de pistes sans faire vot' mauviet'.",
                    ":/images/orks/chariot.jpg",
                    "", evt);
        double proba = Aleatoire::GetAl()->Entre0Et1();
        if ( proba >= 0.4) {
            QString blessure = PbSante::GetBlessureLegereAleatoire();
            effet1->AjouterChangeurDeCarac(blessure, "1");
            effet1->m_Texte += "\nMalheureusement vous faites quelques chutes violentes sous les moqueries de votre instructeur."
                    "Vous avez mainteannt la blessure : " + blessure;
        }
        effet1->AjouterAjouteurACarac(Vehicule::C_CONDUITE_ROUTE, "2");
        effet1->AjouterAjouteurACarac(Metier::CONDUCTEUR, "2");

        effet1->m_GoToEffetId = go_to_effet_suivant;
        shared_ptr<Condition> cond1 = make_shared<Condition>(1.0, TypeProba::p_Relative);
        shared_ptr<NoeudProbable> noeud1 = make_shared<NoeudProbable>(
                    effet1,
                    cond1);
        noeudsProbaEducation.push_back(noeud1);
    }

    // pilote d'avion
    {
        shared_ptr<Effet> effet1 = genHist->AjouterEffetNarration(
                    "Les autres coteries se moquent de l'aspect rudimentaire de la technologie ork et pourtant ils sont une des rares à être capable de produire et faire tourner des avions grâces à leurs techniques très économiques en énergie."
                    "\nVotre instructeur vous offre l'insigne honneur de voler vec lui et vous montre les bases du pilotage.",
                    ":/images/orks/avion.jpg",
                    "", evt);
        effet1->AjouterAjouteurACarac(Vehicule::C_CONDUITE_AVION, "1");
        effet1->AjouterAjouteurACarac(Metier::PILOTE, "1");

        effet1->m_GoToEffetId = go_to_effet_suivant;
        shared_ptr<Condition> cond1 = make_shared<Condition>(0.6, TypeProba::p_Relative);
        shared_ptr<NoeudProbable> noeud1 = make_shared<NoeudProbable>(
                    effet1,
                    cond1);
        noeudsProbaEducation.push_back(noeud1);
    }

    // soulé à la bière
    {
        shared_ptr<Effet> effet1 = genHist->AjouterEffetNarration(
                    "Personne ne respecte un ork qui ne tient pas la bière aux champignons."
                    "Votre instructeur fait en sorte que vous goûtiez de tous les alcools ork. Et en grande quantité."
                    "\nAucun humain ayant subi une telle épreuve n'en ressort indemne.",
                    "",
                    "", evt);
        double proba = Aleatoire::GetAl()->Entre0Et1();
        if ( proba <= 0.3) {
            effet1->m_Texte += "\nVotre organisme est durement affecté. Vous devenez 'faible'.";
            effet1->AjouterChangeurDeCarac(Trait::GetNomTrait(faible), "1");
        }
        else if (proba > 0.7 )
        {
            effet1->m_Texte += "\nVous gagnez 'résistant'.";
            effet1->AjouterChangeurDeCarac(Trait::GetNomTrait(resistant), "1");
        }
        proba = Aleatoire::GetAl()->Entre0Et1();
        if ( proba <= 0.4 ) {
            effet1->m_Texte += "\nToutes vos angoisses profondes fondent définitivement.";
            effet1->AjouterChangeurDeCarac(Trait::GetNomTrait(angoisse), "");
        }
        proba = Aleatoire::GetAl()->Entre0Et1();
        if ( proba <= 0.5 ) {
            effet1->m_Texte += "\nDurablement affecté par la boisson vous devenez alcoolique.";
            effet1->AjouterChangeurDeCarac(PbSante::ALCOOLIQUE, "1");
        }
        proba = Aleatoire::GetAl()->Entre0Et1();
        if ( proba <= 0.2 ) {
            effet1->m_Texte += "\nL'alcool vous a salement endommagé le cerveau. Vous devenez 'simple'";
            effet1->AjouterChangeurDeCarac(Trait::GetNomTrait(simple), "1");
            effet1->AjouterChangeurDeCarac(Trait::GetNomTrait(intelligent), "");
            effet1->AjouterChangeurDeCarac(Trait::GetNomTrait(intellectuel), "");
        }
        proba = Aleatoire::GetAl()->Entre0Et1();
        if ( proba <= 0.2 ) {
            effet1->m_Texte += "\nL'alcool est tellement persistant qu'il vous fait sauter vos inhibitions et votre prudence sur le coup mais aussi à long terme. Vous devenez 'franc'.";
            effet1->AjouterChangeurDeCarac(Trait::GetNomTrait(franc), "1");
        }

        effet1->m_GoToEffetId = go_to_effet_suivant;
        shared_ptr<Condition> cond1 = make_shared<Condition>(1.0, TypeProba::p_Relative);
        shared_ptr<NoeudProbable> noeud1 = make_shared<NoeudProbable>(
                    effet1,
                    cond1);
        noeudsProbaEducation.push_back(noeud1);
    }

    // formation mékano
    {
        shared_ptr<Effet> effetMekano = genHist->AjouterEffetNarration(
                    "Un mékano a remarqué vos capacités et vous a formé aux bases de la réparation de moteurs. "
                    "\nBien que sa technique semble rudimentaire à première vue il est véritablement doué et très entousiaste comm enseignant."
                    "\nIl vous promet que quand vous serez un vrai ork il vous apprendra à fabriquer des armes, ce qui est encore plus rigolo.",
                    ":/images/orks/mekano.PNG",
                    "", evt);
        effetMekano->m_GoToEffetId = go_to_effet_suivant;
        effetMekano->m_Conditions = {
            make_shared<Condition>(Trait::GetNomTrait(eTrait::intelligent), "1", Comparateur::c_SuperieurEgal)
        };
        effetMekano->AjouterAjouteurACarac(Ingenieur::C_MECANIQUE, "1"); // meilleur Mékano
        shared_ptr<Condition> cond = make_shared<Condition>(1.0, TypeProba::p_Relative);
        shared_ptr<NoeudProbable> noeudMekano = make_shared<NoeudProbable>(
                    effetMekano,
                    cond);
        noeudsProbaEducation.push_back(noeudMekano);
    }

    // formation médiko
    {
        shared_ptr<Effet> effet = genHist->AjouterEffetNarration(
                    "Un médiko a remarqué vos capacités et vous a formé aux bases de la rudimentaire médecine ork. "
                    "Leur vrai point fort est leur obsession des améliorations bioniques combinée à la capacité des patients orques à accepter à peu près toutes les greffes. ",
                    ":/images/orks/ork_mediko0.jpg",
                    "", evt);
        effet->m_GoToEffetId = go_to_effet_suivant;
        effet->AjouterAjouteurACarac(Bionique::C_FABRICATION_BIONIQUE, "1"); // meilleur médiko
        effet->AjouterAjouteurACarac(Metier::MEDECIN, "1"); // meilleur médiko
        shared_ptr<Condition> cond = make_shared<Condition>(0.5, TypeProba::p_Relative);
        effet->m_CallbackDisplay = [] {
            double proba = Aleatoire::GetAl()->Entre0Et1();
            if ( proba <= 0.8) {
                shared_ptr<Effet> effet = ExecHistoire::GetEffetActuel();
                Humain* humain = Humain::GetHumainJoue();
                QString blessure = PbSante::GetBlessureLegereAleatoire();
                effet->m_Texte += "\nMalheureusement il en profite pour faire des expériences amusantes sur vous après vous avoir assomé avec un maillet.";
                effet->m_Texte += "\nVous êtes maintenant : " + blessure;
                humain->SetValeurACaracId(blessure, "1");
                humain->SetValeurACaracId(PbSante::DEFIGURE, "1");
                QString bionique = Bionique::AppliquerBionique(humain);
                effet->m_Texte += "\nEt vous avez le bionique : " + bionique;
            }
        };

        shared_ptr<NoeudProbable> noeudMekano = make_shared<NoeudProbable>(
                    effet,
                    cond);
        noeudsProbaEducation.push_back(noeudMekano);
    }

    shared_ptr<Effet> effetSelecteur = genHist->m_GenerateurEvt->AjouterEffetSelecteurDEvt(
                noeudsProbaEducation);
    effetSelecteur->m_MsChrono = 1; // passé automatiquement

    return effetSelecteur;
}

QVector<QString> Orks::NOMS_M = {
    "Ghazat","Abghat","Adgulg","Aghed","Agugh","Aguk","Almthu","Alog","Ambilge","Apaugh","Argha","Argigoth","Argug",
    "Arpigig","Auhgan","Azhug","Bagdud","Baghig","Bahgigoth","Bandagh","Barfu","Bargulg","Baugh","Bidgug","Bildud","Bilge","Bog","Boghat","Bogugh","Borgan",
    "Borug","Braugh","Brougha","Brugagh","Bruigig","Buadagh","Buggug","Builge","Buimghig","Bulgan","Bumhug","Buomaugh",
    "Buordud","Burghed","Buugug","Cabugbu","Cagan","Carguk","Carthurg","Clog","Corgak","Crothu","Cubub","Cukgilug",
    "Curbag","Dabub","Dakgorim","Dakgu","Dalthu","Darfu","Deakgu","Dergu","Derthag","Digdug","Diggu","Dilug","Ditgurat",
    "Dorgarag","Dregu","Dretkag","Drigka","Drikdarok","Drutha","Dudagog","Dugarod","Dugorim","Duiltag","Durbag","Eagungad","Eggha","Eggugat","Egharod","Eghuglat",
    "Eichelberbog","Ekganit","Epkagut","Ergoth","Ertguth","Ewkbanok","Fagdud","Faghig","Fandagh","Farfu","Farghed","Fargigoth","Farod","Faugh","Feldgulg","Fidgug",
    "Filge","Fodagog","Fogugh","Fozhug","Frikug","Frug","Frukag","Fubdagog","Fudhagh","Fupgugh","Furbog","Futgarek","Gaakt","Garekk","Gelub","Gholug","Gilaktug",
    "Ginug","Gnabadug","Gnadug","Gnalurg","Gnarg","Gnarlug","Gnorl","Gnorth","Gnoth","Gnurl","Golag","Golub","Gomatug","Gomoku","Gorgu","Gorlag","Grikug","Grug",
    "Grukag","Grukk","Grung","Gruul","Guag","Gubdagog","Gudhagh","Gug","Gujarek","Gujek","Gujjab","Gulm","Gulrn","Gunaakt","Gunag","Gunug","Gurukk","Guthakug","Guthug",
    "Gutjja","Hagob","Hagu","Hagub","Haguk","Hebub","Hegug","Hibub","Hig","Hogug","Hoknath","Hoknuk","Hokulk","Holkurg","Horknuth","Hrolkug","Hugagug","Hugmug","Hugolm",
    "Ig","Igmut","Ignatz","Ignorg","Igubat","Igug","Igurg","Ikgnath","Ikkath","Inkathu","Inkathurg","Isagubat","Jogug","Jokgagu","Jolagh","Jorgagu","Jregh","Jreghug",
    "Jugag","Jughog","Jughragh","Jukha","Jukkhag","Julakgh","Kabugbu","Kagan","Kaghed","Kahigig","Karfu","Karguk","Karrghed","Karrhig","Karthurg","Kebub","Kegigoth",
    "Kegth","Kerghug","Kertug","Kilug","Klapdud","Klog","Klughig","Knagh","Knaraugh","Knodagh","Knorgh","Knuguk","Knurigig","Kodagog","Kog","Kogan","Komarod",
    "Korgak","Korgulg","Koughat","Kraugug","Krilge","Krothu","Krouthu","Krugbu","Krugorim","Kubub","Kugbu","Kukgilug","Kulgha","Kupgugh","Kurbag","Kurmbag","Laghed",
    "Lamgugh","Mabub","Magdud","Malthu","Marfu","Margulg","Mazhug","Meakgu","Mergigoth","Milug","Mudagog","Mugarod","Mughragh","Mugorim","Murbag","Naghat","Naghig",
    "Naguk","Nahgigoth","Nakgu","Narfu","Nargulg","Narhbub","Narod","Neghed","Nehrakgu","Nildud","Nodagog","Nofhug","Nogugh","Nomgulg","Noogugh","Nugbu","Nughilug",
    "Nulgha","Numhug","Nurbag","Nurghed","Oagungad","Oakgu","Obghat","Oggha","Oggugat","Ogharod","Oghuglat","Oguk","Ohomdud","Ohulhug","Oilug","Okganit","Olaghig",
    "Olaugh","Olmthu","Olodagh","Olog","Omaghed","Ombilge","Omegugh","Omogulg","Omugug","Onog","Onubub","Onugug","Oodagh","Oogorim","Oogugbu","Oomigig","Opathu",
    "Opaugh","Opeghat","Opilge","Opkagut","Opoguk","Oquagan","Orgha","Orgoth","Orgug","Orpigig","Ortguth","Otugbu","Ougha","Ougigoth","Ouhgan","Owkbanok","Paghorim",
    "Pahgigoth","Pahgorim","Pakgu","Parfu","Pargu","Parhbub","Parod","Peghed","Pehrakgu","Pergu","Perthag","Pigdug","Piggu","Pitgurat","Podagog","Pofhug","Pomgulg",
    "Poogugh","Porgarag","Pregu","Pretkag","Prigka","Prikdarok","Prutha","Pughilug","Puiltag","Purbag","Qog","Quadagh","Quilge","Quimghig","Quomaugh","Quordud","Quugug",
    "Raghat","Raguk","Rakgu","Rarfu","Rebub","Rilug","Rodagog","Rogan","Romarod","Routhu","Rugbu","Rugorim","Rurbag","Rurigig","Sabub","Saghig","Sahgigoth","Sahgorim",
    "Sakgu","Salthu","Saraugug","Sarfu","Sargulg","Sarhbub","Sarod","Sbghat","Seakgu","Sguk","Shomdud","Shulhug","Sildud","Silge","Silug","Sinsbog","Slaghig","Slapdud",
    "Slaugh","Slodagh","Slog","Slughig","Smaghed","Smegugh","Smogulg","Snog","Snubub","Snugug","Sodagh","Sog","Sogorim","Sogugbu","Sogugh","Sombilge","Somigig","Sonagh",
    "Sorgulg","Sornaraugh","Soughat","Spathu","Speghat","Spilge","Spoguk","Squagan","Stugbu","Sudagog","Sugarod","Sugbu","Sugha","Sugigoth","Sugorim","Suhgan","Sulgha",
    "Sulmthu","Sumhug","Sunodagh","Sunuguk","Supaugh","Supgugh","Surbag","Surgha","Surghed","Surgug","Surpigig","Tagdud","Taghig","Tandagh","Tarfu","Targhed","Targigoth",
    "Tarod","Taugh","Teldgulg","Tidgug","Tilge","Todagog","Tog","Toghat","Togugh","Torgan","Torug","Tozhug","Traugh","Trilug","Trougha","Trugagh","Truigig","Tuggug",
    "Tulgan","Turbag","Turge","Ug","Ugghra","Uggug","Ughat","Ulgan","Ulmragha","Ulmrougha","Umhra","Umragig","Umruigig","Ungagh","Unrugagh","Urag","Uraugh","Urg",
    "Urgan","Urghat","Urgran","Urlgan","Urmug","Urug","Urulg","Vabugbu","Vagan","Vagrungad","Vagungad","Vakgar","Vakgu","Vakmu","Valthurg","Vambag","Vamugbu","Varbu",
    "Varbuk","Varfu","Vargan","Varguk","Varkgorim","Varthurg","Vegum","Vergu","Verlgu","Verthag","Verthurg","Vetorkag","Vidarok","Vigdolg","Vigdug","Viggu","Viggulm",
    "Viguka","Vitgurat","Vitgut","Vlog","Vlorg","Vorgak","Vorgarag","Vothug","Vregu","Vretkag","Vrigka","Vrikdarok","Vrogak","Vrograg","Vrothu","Vruhag","Vrutha",
    "Vubub","Vugub","Vuiltag","Vukgilug","Vultog","Vulug","Vurbag","Wakgut","Wanug","Wapkagut","Waruk","Wauktug","Wegub","Welub","Wholug","Wilaktug","Wingloug",
    "Winug","Woabadug","Woggha","Woggugat","Wogharod","Woghuglat","Woglug","Wokganit","Womkug","Womrikug","Wonabadug","Worthag","Wraog","Wrug","Wrukag","Wrukaog",
    "Wubdagog","Wudgh","Wudhagh","Wudugog","Wuglat","Wumanok","Wumkbanok","Wurgoth","Wurmha","Wurtguth","Wurthu","Wutgarek","Xaakt","Xago","Xagok","Xagu","Xaguk",
    "Xarlug","Xarpug","Xegug","Xepug","Xig","Xnath","Xnaurl","Xnurl","Xoknath","Xokuk","Xolag","Xolkug","Xomath","Xomkug","Xomoku","Xonoth","Xorag","Xorakk",
    "Xoroku","Xoruk","Xothkug","Xruul","Xuag","Xug","Xugaa","Xugag","Xugagug","Xugar","Xugarf","Xugha","Xugor","Xugug","Xujarek","Xuk","Xulgag","Xunaakt","Xunag",
    "Xunug","Xurek","Xurl","Xurug","Xurukk","Xutag","Xuthakug","Xutjja","Yaghed","Yagnar","Yagnatz","Yahg","Yahigig","Yakgnath","Yakha","Yalakgh","Yargug","Yegigoth",
    "Yegoth","Yerghug","Yerug","Ymafubag","Yokgagu","Yokgu","Yolmar","Yonkathu","Yregh","Yroh","Ysagubar","Yughragh","Yugug","Yukgnath","Yukha","Yulakgh","Yunkathu",
    "Zabghat","Zabub","Zaghig","Zahgigoth","Zahgorim","Zalthu","Zaraugug","Zarfu","Zargulg","Zarhbub","Zarod","Zeakgu","Zguk","Zildud","Zilge","Zilug","Zinsbog",
    "Zlapdud","Zlog","Zlughig","Zodagh","Zog","Zogugbu","Zogugh","Zombilge","Zonagh","Zorfu","Zorgulg","Zorhgigoth","Zornaraugh","Zoughat","Zudagog","Zugarod",
    "Zugbu","Zugorim","Zuhgan","Zulgha","Zulmthu","Zumhug","Zunodagh","Zunuguk","Zupaugh","Zupgugh","Zurbag","Zurgha","Zurghed","Zurgug","Zurpigig","Atulg",
    "Azuk","Bagamul","Bakh","Baronk","Bashag","Bazgulub","Bogakh","Borug","Both","Bugdul","Bugharz","Bugrash","Bugrol","Bumbub","Burul","Dul","Dular","Duluk",
    "Duma","Dumbuk","Dumburz","Dur","Durbul","Durgash","Durz","Durzol","Durzub","Durzum","Garothmuk","Garzonk","Gashna","Ghamborz","Ghamonk","Ghoragdush",
    "Ghorlorz","Glush","Grat","Guarg","Gurak","Khadba","Khagra","Khargol","Koffutto","Largakh","Lorbumol","Lorzub","Lugdum","Lugrub","Lurog","Mash","Matuk",
    "Mauhul","Mazorn","Mol","Morbash","Mug","Mugdul","Muk","Murag","Murkub","Murzol","Muzgonk","Nag","Nar","Nash","Ogrul","Ogrumbu","Olfin","Olumba","Orakh",
    "Rogdul","Shakh","Shamar","Shamob","Shargam","Sharkub","Shat","Shulong","Shura","Shurkul","Shuzug","Snaglak","Snakha","Snat","Ugdumph","Ughash","Ulam",
    "Umug","Uram","Urim","Urul","Urzog","Ushamph","Yadba","Yagak","Yak","Yam","Yambagorn","Yambul","Yargol","Yashnarz","Yatur","Agronak","Bat","Bazur",
    "Brugo","Bogrum","Brag","Brokil","Bugak","Buramog","Burz","Dubok","Dul","Dulfish","Dumag","Dulphumph","Gaturn","Gogron","Gorgo","Graklak","Graman",
    "Grommok","Gul","Hanz","Krognak","Kurdan","Kurz","Rugdumph","Lum","Lumdum","Luronk","Magra","Magub","Maknok","Mug","Orok","Shagol","Shagrol","Shobob",
    "Shum","Ulmug","Urbul","Urul","Ushnar","Uzul","Arob","Balogog","Borkul","Burguk","Dushnamub","Gat","Ghamorz","Ghorbash","Gradba","Grogmar","Grushnag",
    "Gularzob","Kharag","Larek","Lob","Lurbuk","Mahk","Makhel","Abbas","Mauhulakh","Moth","Mul","Mulush","Nagrub","Oglub","Ogol","Olur","Ulag","Umurn",
    "Urag","Yamarz","Yar"};

QVector<QString> Orks::NOMS_F = {
    "Agrob","Badbog","Bashuk","Bogdub","Bugdurash","Bula","Bulak","Bulfim","Bum","Burzob","Burub","Dura","Durgat","Durz","Gashnakh","Ghob","Glasha",
    "Glob","Gluronk","Gonk","Grat","Grazob","Gulfim","Kharzug","Lagakh","Lambug","Lazgar","Mogak","Morn","Murob","Murzush","Nargol","Rolfish","Orbul",
    "Ragash","Rulfim","Shadbak","Shagar","Shagdub","Sharn","Sharog","Shazgob","Shelur","Uloth","Ulumpha","Urzoth","Urzul","Ushat","Ushug","Yazgash",
    "Batul","Borba","Bumph","Homraz","Rogbut","Mazoga","Mog","Mor","Oghash","Rogmesh","Snak","Ugak","Umog","Arob","Atub","Bagrak","Bolar","Bor",
    "Borgakh","Dulug","Garakh","Ghak","Gharol","Ghorza","Gul","Lash","Murbol","Sharamph","Shel","Shufharz","Ugor","Urog","Yotul"
};
