#include "conquistadors.h"
#include "genviehumain.h"
#include "religion/religion.h"
#include "violence/combat.h"
#include "socio_eco/metier.h"
#include "humanite/trait.h"
#include "../destinLib/aleatoire.h"
#include "../destinLib/abs/condition.h"
#include "geographie/quartier.h"
#include <QDebug>
#include "extremis.h"
#include "humain.h"
#include "../destinLib/abs/condition.h"
#include "socio_eco/economieevt.h"

using std::make_shared;
using std::shared_ptr;

Conquistadors::Conquistadors()
{
    Initialisation();
}

shared_ptr<Quartier> Conquistadors::GenererQuartier()
{
    m_Quartier = make_shared<Quartier>("Honfleur", "Quartier des Conquistadors", "", this);
    Extremis::QUARTIERS[m_Quartier->m_Nom] = m_Quartier;
    return m_Quartier;
}

QString Conquistadors::GetMusique()
{
    return "qrc:/sons/celtes/01-06-Lemminkainen_Suite_Op_22_IV_Lemminkainen-LLS.mp3";
}

void Conquistadors::GenererTraitCompatibles()
{
    m_TraitsCompatible = {
        make_shared<Condition>(Trait::GetNomTrait(eTrait::ambitieux), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::aventureux), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::opportuniste), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::cupide), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Religion::C_FOI, Religion::CHRETIEN, Comparateur::c_Egal )
    };
    m_TraitsIncompatible = {
        make_shared<Condition>(Trait::GetNomTrait(eTrait::altruiste), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::chetif), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::pacifiste), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::paresseux), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::angoisse), "1", Comparateur::c_Egal )
    };
    m_MetiersAssocies = {
        Metier::CARTOGRAPHE,
        Metier::FORGERON,
        Metier::MARCHAND
    };
}

QString Conquistadors::GetGentile(bool /*masculin*/)
{
    return "conquistador";
}

QString Conquistadors::GetNom()
{
    return "Conquistadors";
}

QString Conquistadors::GetDescription()
{
    return "Description des Conquistadors";
}

double Conquistadors::GetPoidsDemo()
{
    return 1.0;
}

QString Conquistadors::GetDescriptionUniversite()
{
    return "Les Conquistadors";
}

QString Conquistadors::GetImage()
{
    return ":/images/conquistadors/soldats.jpg";
}

std::shared_ptr<Effet> Conquistadors::AjouterEffetUniversite(GenHistoire* genHist, shared_ptr<Evt> evt, QString go_to_effet_suivant )
{
    QVector<shared_ptr<NoeudProbable>> noeudsProbaEducation;

    // formation religieuse
    {
        shared_ptr<Effet> effet1 = genHist->AjouterEffetNarration(
                    "Un conquistador se doit d'être un fervent catholique confiant dans le destin que Dieu trace devant lui et qui le mènera à la gloire et la richesse. "
                    "\nVous passez des jours entiers à prier dans la dévotion des images saintes à suivre les cours de catéchisme des prêtres catholiques.",
                    ":/images/conquistadors/priant.jpg",
                    "", evt);
        Religion::ModifierEffetEnEffetConversion(effet1, Religion::CHRETIEN);
        effet1->m_GoToEffetId = go_to_effet_suivant;
        shared_ptr<Condition> cond1 = make_shared<Condition>(0.6, TypeProba::p_Relative);// la religion n'est pas le plus important pour les conquistadors
        shared_ptr<NoeudProbable> noeud1 = make_shared<NoeudProbable>(
                    effet1,
                    cond1);
        noeudsProbaEducation.push_back(noeud1);
    }

    // effetCombat
    {
        shared_ptr<Effet> effetCombat = genHist->AjouterEffetNarration(
                    "Seuls les grands guerriers peuvent espérer devenir des conquistadors et affronter les horreurs des terres désolées. "
                    "Votre formation contient bien sûr un entrainement avec de célbres maîtres d'armes.",
                    ":/images/conquistadors/soldat.jpg",
                    "", evt);
        effetCombat->m_GoToEffetId = go_to_effet_suivant;
        effetCombat->AjouterAjouteurACarac(Combat::C_CAP_COMBAT, "1"); // meilleur combattant
        shared_ptr<Condition> condCombat = make_shared<Condition>(1.0, TypeProba::p_Relative);
        shared_ptr<NoeudProbable> noeudCombat = make_shared<NoeudProbable>(
                    effetCombat,
                    condCombat);
        noeudsProbaEducation.push_back(noeudCombat);
    }

    // effetForgeron
    {
        shared_ptr<Effet> effetForgeron = genHist->AjouterEffetNarration(
                    "Les conquistadors sont des experts de la forge, leurs armures sont les meilleures du monde. "
                    "De plus il est indispensable qu'en expédition ils soient capables de réparer et entretenir leur matériel donc même les aventuriers se doivent d'avoir des rudiments techniques."
                    "\nVous êtes donc formé par un maître forgeron pour connaître les bases du métier.",
                    ":/images/conquistadors/forgeron.jpg",
                    "", evt);
        effetForgeron->m_GoToEffetId = go_to_effet_suivant;
        effetForgeron->AjouterAjouteurACarac(Metier::FORGERON, "1"); // meilleur forgeron
        shared_ptr<Condition> condCombat = make_shared<Condition>(1.0, TypeProba::p_Relative);
        shared_ptr<NoeudProbable> noeudCombat = make_shared<NoeudProbable>(
                    effetForgeron,
                    condCombat);
        noeudsProbaEducation.push_back(noeudCombat);
    }

    // effet Musicien
    {
        shared_ptr<Effet> effet = genHist->AjouterEffetNarration(
                    "Les conquistadors ne sont pas seulement des aventuriers, ce sont aussi des baladins itinérants qui divertissent les hôtes qui veulent bien les accueillir dans leurs nombreuses aventures. "
                    "Ainsi ils peuvent chanter leurs exploits mais aussi ceux de leurs ancêtres et de leur clan.",
                    ":/images/conquistadors/guitariste2.jpg",
                    "", evt);
        effet->m_GoToEffetId = go_to_effet_suivant;
        effet->AjouterAjouteurACarac(Metier::MUSICIEN, "1");
        shared_ptr<Condition> cond = make_shared<Condition>(0.3, TypeProba::p_Relative);

        Trait::AjouterModifProbaSiACeTrait(cond.get(), 1.5, artiste);
        shared_ptr<NoeudProbable> noeudCombat = make_shared<NoeudProbable>(
                    effet,
                    cond);
        noeudsProbaEducation.push_back(noeudCombat);
    }

    // effet Cartographe
    {
        shared_ptr<Effet> effet = genHist->AjouterEffetNarration(
                    "Les conquistadors ont bâti le plus grand empire du monde et sont donc ceux qui le connaissent le mieux depuis la destructions amssives causées par la dernière guerre. "
                    "Cette connaissance est primordiale et c'est pourquoi comme toutes les jeunes recrues vous êtes formé à la cartographie pour contempler la plus grande gloire de la coterie.",
                    ":/images/conquistadors/carte.png",
                    "", evt);
        effet->m_GoToEffetId = go_to_effet_suivant;
        effet->AjouterAjouteurACarac(Metier::CARTOGRAPHE, "2");
        shared_ptr<Condition> cond = make_shared<Condition>(0.8, TypeProba::p_Relative);

        shared_ptr<NoeudProbable> noeudCombat = make_shared<NoeudProbable>(
                    effet,
                    cond);
        noeudsProbaEducation.push_back(noeudCombat);
    }

    // effet Marchand
    {
        shared_ptr<Effet> effet = genHist->AjouterEffetNarration(
                    "Par leur maîtrise des mers et de nombreuses contrées étrangères les conquistadors contrôlent une énorme partie du commerce mondiale. De plus par leurs pillages ils doivent savoir estimer rapidement la valeur des objets pour ne pas faire d'erreur. "
                    "\nJamais une expédition ne part sans au moins un marchand. Votre tuteur décide donc de vous y former pour estimer vos talents en la matière.",
                    "",
                    "", evt);
        effet->m_GoToEffetId = go_to_effet_suivant;
        effet->AjouterAjouteurACarac(Metier::MARCHAND, "1");
        shared_ptr<Condition> cond = make_shared<Condition>(1.0, TypeProba::p_Relative);

        shared_ptr<NoeudProbable> noeudCombat = make_shared<NoeudProbable>(
                    effet,
                    cond);
        noeudsProbaEducation.push_back(noeudCombat);
    }

    shared_ptr<Effet> effetSelecteur = genHist->m_GenerateurEvt->AjouterEffetSelecteurDEvt(
                noeudsProbaEducation);
    effetSelecteur->m_MsChrono = 1; // passé automatiquement

    return effetSelecteur;
}

QString Conquistadors::GetId()
{
    return Coterie::CONQUISTADORS;
}

void Conquistadors::GenererPortraits(Humain* hum, int ageAnnees, QString metier, QVector<QString>&images)
{
    if ( ageAnnees > 15 ) {
        if ( ageAnnees < 40 ) {
            images.push_back(":/images/conquistadors/portrait_15-40.jpg");
            images.push_back(":/images/conquistadors/portrait_15-40_b.jpg");
            images.push_back(":/images/conquistadors/portrait_15-40_c.jpg");
            if ( ageAnnees > 20 ) {
                images.push_back(":/images/conquistadors/portrait_20-40.jpg");
            }
        } else {
            images.push_back(":/images/conquistadors/portrait_40+.jpg");
        }
    }
    if ( ageAnnees > 20 ) {
        if ( ageAnnees < 50 ) {
            if ( metier == Metier::MARCHAND) {
                images.push_back(":/images/conquistadors/portrait_marchand_15-50.jpg");
            }
            images.push_back(":/images/conquistadors/portrait_20-50.jpg");
            images.push_back(":/images/conquistadors/portrait_20-50_b.jpg");
            images.push_back(":/images/conquistadors/portrait_20-50_c.jpg");
            images.push_back(":/images/conquistadors/portrait_20-50_d.jpg");
            images.push_back(":/images/conquistadors/portrait_20-50_e.jpg");
        } else {
            // > 50
            if ( metier == Metier::MARCHAND) {
                images.push_back(":/images/conquistadors/portrait_marchand_50+.jpg");
            }
        }
    }
}

QString Conquistadors::CreerPatronyme(bool masculin)
{
    return (masculin?
               PRENOMS_M[Aleatoire::GetAl()->EntierInferieurA(PRENOMS_M.size())] + " " +
                         NOMS[Aleatoire::GetAl()->EntierInferieurA(NOMS.size())]:
               PRENOMS_F[Aleatoire::GetAl()->EntierInferieurA(PRENOMS_F.size())] + " " +
                       NOMS[Aleatoire::GetAl()->EntierInferieurA(NOMS.size())]
            );
}

QVector<QString> Conquistadors::PRENOMS_M = {
    "Rodigo", 	"Adis",	"Albertino",	"Alcidès",
    "Ãšrbez","AgostÃ­n","Aimadeio","Aimadeo","Aimau","Aimor","Albaro","Aleixandro","Aleixo","Alexandro","Alexo","Alfons","Alfred","Alifonso","Alixandre",
    "Alodio","Alois","AltabÃ¡s","Alvaro","Alziz","Amancio","Amanzio","Amat","Anchel","Andreu","Anizeto","AntÃ³n","Antoni","Aparizio","Arbert","Archentino",
    "Archimiro","Armenchol","Arnau","Artal","Ato","Augusto","AusiÃ¡s","BalandÃ­n","BalantÃ­n","BaldobÃ­n","BaldovÃ­n","Baleriano","Balero","Bartomeu","BascuÃ©s",
    "BastiÃ¡n","Bauzis","Belasco","BeliÃ¡n","Benanzio","BenchamÃ­n","Benet","Benino","Bentura","Beremundo","Berenguer","Berenice","Bernal","Bernat",
    "BertolomÃ©","BertrÃ¡n","Bertran","BeturiÃ¡n","Beturio","BibiÃ¡n","Bisorio","Bital","Bitelio","Bitor","BizÃ©n","Blasco","Boecio","Boezio","Borrell",
    "Borxa","Bras","Bruis","Buil","Burnau","Calisto","Calixto","Calvet","Cancio","Canzio","Carapas","Carles","CeferÃ­n","Celdoni","CelestÃ­n","Celidonio",
    "Celipe","Cerilo","Cesar","Chabier","Chacinto","Chacobo","Chaime","Chavier","Chazinto","Chenaro","ChentÃ­l","Cherardo","Cherbasio","CheremÃ­as","CheriÃ³n",
    "ChermÃ¡n","Cheromo","Cheronimo","Chervasio","ChesÃºs","Chil","ChimÃ©n","ChinÃ©s","Chodofrodo","Choel","ChonÃ¡s","ChonatÃ¡n","Chorche","Chuan","ChuaquÃ­n",
    "Chubenal","Chudes","ChuliÃ¡n","Chulio","ChusÃ©","ChustÃ­n","Chustino","Chusto","Chuvenal","CicerÃ³n","Cilipo","ClimÃ©n","Climent","ColÃ¡s","CristiÃ¡n",
    "Cristofo","DabÃ­","Dachoberto","Dacil","Dalmacio","Dalmau","Dalmazio","DavÃ­","Dazil","Dimetrio","Diochenes","Diochens","Dolcet","DomÃ¨nech","Domingo",
    "Donisio","Ebardo","ElÃ­","Elicio","Eliodoro","Elizio","Emerenziano","ErÃ³n","Ercules","Eriberto","Ermelando","Ermeneixildo","Ermenexildo","Ermengol",
    "Ermes","Esteve","Etelbino","EtelvÃ­n","Euchenio","Euloxio","Eunizie","Euridize","Eustazio","Fabricio","Fabrizio","Feli","Felip","FerrÃ¡n","Ferran",
    "Ferrando","FertÃºs","Filipo","Flabio","Flavio","Florencio","Florenzio","FloriÃ¡n","FrancÃ­","Francesc","Francho","Frederic","GabÃ­n","Gabriel","GalÃ©n",
    "Galceran","Galindo","Garapasio","Garcia","Gausfred","GenÃ­s","Gibert","Gil","Gilabert","Gombal","Gombau","Grabiel","GraciÃ¡n","GraciliÃ¡n","Grapas",
    "Graziliano","Guerau","Guergorio","GuifrÃ©","GuillÃ©n","Guillem","Guillen","Guislabert","Gustabo","Gustau","Honorato","Honorio","Hug","Iago","IbÃ¡n",
    "IbÃ³n","Ilario","Inacio","Indalecio","Indalezio","Inico","Inocencio","Inozencio","Ipol","Iram","Istebe","IvÃ¡n","Ixinio","Iziar","Izurbe","Jaume",
    "Jeroni","Joan","Jordi","Josep","Ladislau","Laude","Lauriano","Leobixildo","Leovixildo","LiÃ³n","Libio","Licer","Licinio","Lixandro","Lizer","Lizinio",
    "LlorenÃ§","LluÃ­s","LoÃ­s","Locadio","Lodosis","Loncio","Loren","Lorent","Lorente","LoriÃ©n","Lorient","Lucer","Luciano","Lucio","Lupercio","Luperzio",
    "Luterio","Luzer","Luziano","Luzio","MachÃ­n","MaiximiliÃ¡n","Maiximo","Manel","Marc","MarcelÃ­n","Marcelo","MarciÃ¡n","MartÃ­","Marzal","Marzelino",
    "Marzelo","Marziano","Masimiliano","Masimo","MatalÃ³n","Mateu","Mauricio","Maurizio","Medardo","Menancio","Mencio","Meneixildo","Menzio","Merenciano",
    "Meterio","Miguel","Milbio","Milio","Milvio","Minerbo","Minervo","Miquel","Mir","MiranÃ³n","Miterio","Moisen","NarcÃ­s","Narciso","Narziso","NazarÃ©",
    "Nazaret","Nazario","Niceto","Nicolau","Nunildo","Octavio","Olechario","Oleguer","Oliba","Olivar","Omero","Onorato","Onorio","Oracio","Orazio",
    "Osbaldo","Osvaldo","Ot","Otabio","Otger","PÃ­o","PÃ³liz","Pancracio","Pancrazio","Paricio","Patrizio","Patrozinio","Paulo","Pedro","Peirod","Pelayo",
    "Penya","Pere","Pero","PetrÃºs","Pietro","Pifanio","Placido","Plazido","Polito","Polonio","PonÃ§","Poncio","Ponzio","Pricio","Primitibo","Primitivo","Prizio","Prudencio","Prudenzio","Pueyo","Pulinario","Puy","Puyal","Rafael","Rafel","Raimundo","Rais","Ramiro","Ramon","Reimundo","Remiro","Remund","Ricart","Rochelio","Roger","RolÃ¡n","RoldÃ¡n","RomÃ¡n","Romeral","Romeu","Ruixero","Ruxer","Salas","Salbador","Salbiano","Salbino","SalvÃ­n","Salvador","SalviÃ¡n","Salvino","SanÃ§","Sancho","SatornÃ­l","Satornil","Saturiano","Seberino","Sechio","Seguinus","Serbando","Servando","Severino","Siervo","Silbestre","Silvestre","SimÃ³","SimÃ³n","Simon","Sisto","Sixto","Solpicio","Solpizio","Sunyer","Superio","Taciano","Tarsicio","Tarsizio","Taziano","Terencio","Terenzio","Tito","TomÃ¡s","TornÃ­l","Ualdo","Uc","Uchenio","Ufemio","Ufrasio","Ugo","Uloixio","Uloxio","Umberto","UrruÃ©s","Usebio","Ustacio","ValantÃ­n","ValeriÃ¡n","Valero","Venancio","Ventura","Veremundo","VeturiÃ¡n","Veturino","Veturio","VibiÃ¡n","VicenÃ§","Vicent","Vidal","Violant","Vital","Vitelio","Vitor","Wenceslao","Wenceslau","XimÃ©n","Ximeno","Yacma","Yacme","Zeferino","Zelestino","Zequiel","Zerilo","Zesar","Zirilo",
    "Alioth",	"Alirio",	"Alterio",	"Anyelo",
    "Arcadio",	"Arcangel",	"Arles",	"Alfie",
    "Agapito",  	"Ari",	"Aureliano",  	"Amancio",
    "Ambrosio",  	"Américo",  	"Adolfito",  	"Alejo",
    "Amado",  	"Apolinar",  	"Asdrubal",  	"Alonso",
    "Arsenio",  	"Audie",	"Anibal",	"Arnold",
    "Albano",	"Agustin", 	"Andréas",	"Andrès",
    "Alexis",	"Alejandro",	"Alex",	"Adam",
    "Adan",	"Alvaro",	"Adriel",	"Aristides",
    "Angel",	"Absalon",	"Axel",
    "Adonis",	"Abelardo", "Bélisario",	"Blumaro",	"Borris",
    "Baldomero",	"Bolívar",  	"Baudelio",
    "Bautista",	"Bartolomé",  	"Blas",	"Buenaventura",
    "Bernardo",	"Baltasar",	"Baltazar",	"Bernabe", "Clotario",	"Crissolorio",	"Curro",  	"Carlito",
    "Carlitos",  	"Chuy",  	"Chimo",  	"Chester",
    "Che",  	"Candelario",  	"Custodio",
    "Calixto",	"Chucho",  	"Cayetano",	"Clímaco",
    "Conrado",	"Cebrián",  	"Ceferino",	"Ciríaco",
    "Celestino",  	"Cecilio",  	"Casimiro",  	"Cruz",
    "Constantino",	"Cornelio",	"Carol",	"Carlos",
    "Camilo",	"Cristian",	"Cristobal",	"Christoph",
    "Cipriano",	"Cirilo",	"César", "Dago",	"Dagoberto",	"Dalmacio",	"Dalmiro",
    "Donaldo",	"Desi",	"Didacus",
    "Diogenes",	"Dimas",	"Delfin",
    "Diogène",	"Daniel",	"Damian",	"Dennis",
    "Dérek",	"Dan",	"Donovan",	"Domingo",
    "Duncan", "Edagar",	"Edelberto",	"Edin",	"Eras",	"Euclido",	"Ever",
    "Epifanio",  	"Eleuterio",  	"Eustaquio",  	"Ezequiel",
    "Edelmiro",  	"Emigdio",  	"Efrain",	"Eutimio",
    "Eutropio",  	"Eberardo",	"Espiridión", 	"Estavan",
    "Esteban",	"Ezéchiel",	"Emanuel",	"Eduardo",	"Eduard",
    "Ewen",	"Edgar",	"Eléazar",	"Elias",
    "Eli",	"Elian",	"Enrique",	"Enzo",
    "Elviro",	"Eric",	"Elmer",	"Eladio",
    "Edmundo", "Fernan",	"Facundo",	"Fantino",	"Fito",
    "Felipe",	"Florentino",  	"Fulgencio",  	"Fabricio",
    "Fermin",	"Fabian",	"Florencio",	"Félix",
    "Faustin",	"Faustino",	"Fidel",	"Francisco",
    "Faride", "Galeno",	"Genaro",	"Gerson",	"Giano",
    "Gildardo",	"Gilmer",	"Goar",	"Gaspare",	"Gasparo",	"Gervasio",
    "Godofredo",	"Graciano",	"Goyo",  	"Gabino",
    "Galo",  	"Gualterio",	"Gaston",	"German",
    "Gabriel",	"Gaspard",	"Gaspar",	"Georges",
    "Gérard",	"Gerhard",	"Geraldo",	"Gonzalo",
    "Guillermo",	"Gideon",	"Gadiel", "Honorato",	"Harlin",	"Haroldo",	"Homero",	"Honorio",	"Horaz",
    "Huberto",	"Heber",	"Horacio",	"Hiram",
    "Hernan",	"Hermenegildo",	"Herberto",  	"Heraclio",
    "Hazel",	"Herminio",	"Hector",	"Hernando",
    "Hermès",	"Hipolito",	"Héliodoro",	"Hubert",
    "Humberto",	"Hugo",	"Heriberto",	"Horace", "Iberico",	"Idelfonso",	"Iskandar",
    "Inocencio",  	"Ildefonso",  	"Isidro",	"Ismaël",	"Imanol",	"Isaï",	"Isaias",
    "Isidoro",	"Ignace",	"Ignacio",
    "Iñigo",	"Ilian",	"Israël",	"Isaac", "Jairo",	"Janoc",	"Jorvic",	"Justo",
    "Juanito",  	"Jair",	"Jenaro",	"Jafet",
    "Joaquin",	"Jimeno",  	"Jojo",	"Julio",	"Joshua",	"Josue",
    "José",	"José-Luis",	"Jeremias",	"Juan", "Juan-Cruz",	"Juan-José",	"Juan-Manuel",	"Juan-Carlos",
    "Juan-Pablo",	"Juan-Domingo",	"Jésus",	"Jasper",
    "Jorge",	"Javier",	"Jéronimo",	"Jacinto",
    "Jason",	"Justino",	"Jacob",
    "Jacques",	"Jakob",	"Jacobo", 	"Kaspar", "Lautaro",	"Leal",	"Lenin",	"Leobardo",
    "Liberato",	"Lonhard",	"Lucero",	"Lorencio",
    "Lalo",  	"Lincoln",	"Ladislao",	"Leocadio",
    "Leoncio",  	"Lope",  	"Lisandro",	"Lennard",
    "Loreto",	"Lancelot",	"Laurent", "Lazaro",	"Léonard", "Luis",	 "Lino",	"Léo",	"Léonel",	"Léonidas",
    "Léonidès",	"Luc",	"Lucas",	"Lilian",
    "Lillian",	"Lévi", "Macedonio",	"Magno",	"Malaquias",	"Marconio",
    "Marquesio",	"Mesias",	"Milciades",	"Misael",
    "Miguelito",  	"Marcelino",  	"Marcelo",	"Maximiano",
    "Maximino",  	"Moïses",	"Manolo",  	"Melchor",
    "Macario",  	"Marian",	"Marcel",	"Martin",
    "Marcos",	"Marco-Antonio",	"Marcial",	"Manuel",
    "Malcom",	"Mateo",	"Matias",	"Maximiliano",
    "Maximo",	"Michel",	"Miguel",	"Milton",
    "Melchior",	"Mauricio", "Neftali",	"Neptali",	"Néron",	"Nacho",
    "Nicanor",	"Nahum",	"Nahuel",	"Nando",
    "Nacio",  	"Natanael",  	"Nicolao",  	"Nelson", "Nataniel",	"Noël",	"Natalio",
    "Néréo",	"Napoléon",	"Nazareno",	"Nicolas",
    "Nestor", "Oderico",	"Onan",	"Orangel",	"Origenes",
    "Obed",	"Olegario",	"Ona",	"Oswaldo",
    "Octavio",	"Ovidio",	"Otto",	"Oliverio", "Pancracio",	"Patrocinio",	"Pompeyo",	"Pantaleon",
    "Pastor",  	"Pancho",	"Pepe",  	"Pepito",
    "Pánfilo",  	"Pacifico",	"Paris",	"Paco",
    "Paquito",	"Patricio",	"Pascual",	"Pablo",
    "Paulino",	"Paulo",	"Pedro", "Quique",  	"Quintin", "Radames",	"Rainiero",	"Randolfo",	"Recaredo", "Rigoberto", "Rico",
    "Raimundo",	"Raymundo",  	"Régulo",  	"Rodolfito",
    "Rosendo",  	"Rainerio",  	"Roldán",  	"Ruperto",
    "Remedios",	"Rocio",	"Robin",	"Renzo",
    "Rafaël",	"Ramiro",	"Roger",	"Rogelio", "Ramsès",	"Ricardo",	"Richard",
    "Reynaldo",	"Ramon",	"Raymond",	"Remigio",
    "René",	"Roque", "Sigfrido",	"Solimar",	"Saulo",	"Saveiro",
    "Segismundo",	"Segundo",	"Shaqueel",	"Silvino", "Santino",	"Santos",	"Sans",
    "Seve",  	"Sandalio",  	"Sofronio",  	"Sosimo",
    "Saturnino",  	"Sabas",  	"Saul", "Sandro",	"Santiago",	"Sévero",	"Silvestre",
    "Sanson",	"Salomon",	"Simon",	"Sébastian",
    "Sancho",	"Socrates",	"Salvador",	"Sol",
    "Samuel", "Transito",	"Tomeo",	"Torcuato",	"Troilo",
    "Telemaco",	"Tulio",	"Tercero",  	"Tiago",
    "Tiburcio",  	"Toño",  	"Tancredo",  	"Teódulo",
    "Tadeo",	"Téo",	"Tobias",	"Téodoro",
    "Tyrone",	"Toni",	"Tomas",	"Tirso",
    "Téobaldo",	"Telmo",	"Téofilo",	"Toribio", "Ubaldino",	"Urso",	"Uzziel",	"Ulises", "Valdo",	"Venancio",	"Venceslao",	"Velasco",
    "Valdemar",	"Victorino",  	"Vidal", "Venceslas",	"Vilmar",	"Vicente",	"Valentin", "Victor", "Wenceslao",	"Waldo", "Wilfredo", "Waldemar", "Ximeno",  	"Xaver",	"Xavier",
    "Ysmaël",	"Yamil",	"Yago",	"Yaël",
    "Yuli", "Zafiro",	"Zacarias", "Zoilo"
};

QVector<QString> Conquistadors::PRENOMS_F = {
    "Gabriella", "Adalia",	"Abi",	"Abril",	"Adamaris",
    "Abelina","Adela","AgnÃ¨s","Agostina","Aimor","Alba","Aledis","Aleixandra","Alexandra","Alicia","Alizia","Almodis","Alodia","AltabÃ¡s","Alvira","Alziz","Anchela","Ancheles","Anchels","Andreya","Anna","Antona","AnunciaciÃ³n","AnunziaziÃ³n","Araceli","Arazeli","Arraro","AscensiÃ³n","Asenoma","Asperanza","AsunciÃ³n","AsunziÃ³n","AszensiÃ³n","AusiÃ¡s","Avelina","Azucena","Azuzena","Balandina","Baldesca","Baleria","Baleriana","Balma","Banesa","BascuÃ©s","Baucis","Beatriu","Begonia","Benchamina","Bera","Berenguela","Berenice","Berenize","Beronica","Berta","Bilma","Biolante","Bioleta","Birchinia","Biridiana","Birila","Birilia","Birtudes","Bitoria","Bizena","Blanca","Blanga","Brichida","Brixida","Bruis","Buil","Carmeta","Casbas","Celena","Celia","Celidonia","Celipa","Chacinta","Chanira","Chazinta","ChazmÃ­n","Chenobeba","Chenoveba","ChentÃ­l","Chesusa","ChinÃ©s","Chinebra","Chorcha","Chuana","Chuaquina","Chulia","Chuliana","Chulieta","Chusefa","Chusta","Cilia","Cillas","Cintia","Cirenia","Clara","Colasa","ConcepciÃ³n","ConstanÃ§a","ConzeziÃ³n","Crestina","Cristeta","Delia","Dimetria","DolÃ§a","Dolors","Dominga","Donata","Donisia","DulcÃ­a","Dulza","Dulze","Dulzis","Ebanchelina","Ebelina","ElÃ­","Elbira","Elionor","Elisabet","Emma","EncarnaciÃ³n","EncarnaziÃ³n","Engracia","Engrazia","Enriqueta","Erenia","Ermessenda","Erminia","Ersilia","EsaltaziÃ³n","Esperia","Estela","EulÃ lia","Evanchelina","Evelina","ExaltaciÃ³n","FelÃ­cia","Feli","Felicidat","Felicitas","Felisa","FelizidÃ¡","Felizitas","Ferranda","Fonfrida","Francesca","Francha","Francina","Franzina","Gala","Gisela","Gorba","Grabiela","Graciela","Graziela","GuayÃ©n","Guergoria","Guillema","Guillena","Guisla","Iciar","IdalÃ­","Idoia","IguÃ¡cel","IguÃ¡zel","Ilda","Iliena","Illarz","Iracena","Iram","Irazena","Isabel","Isabela","Isperia","Ixeia","Ixeya","Ixinia","Izarbe","Izurbe","Jara","Joana","LÃºzia","Laude","Lauriana","Lena","Leticia","Letizia","LibertÃ¡","Libertat","Liena","LiliÃ¡n","LluÃ¯sa","Loisa","Loreto","LucÃ­a","Lucila","Lutecia","Lutezia","LuzÃ­a","Luzila","Madalena","Magdalena","Malba","Malbina","Malva","Malvina","MarÃ­a","Mara","Marcela","Margarida","Maria","Mariona","Marta","Martina","Marzela","Masima","Maxima","Mercet","Merenciana","Milia","Minerva","Miraglos","Monlora","NatibidÃ¡","Natividat","Nieus","Nunila","Nuria","NuvÃ­lia","Obarra","Odulia","Olaria","Olibia","Oliva","Olivia","OrdÃ¡s","Orosia","Ortensia","Patricia","Patrizia","Patrocinio","PeÃ±a","Penya","Peronella","PiedÃ¡","Piedat","Piera","Pifania","Pilar","Pilara","Pineta","Pirineye","Polita","Polonia","PonÃ§a","Porzia","Priscila","Priszila","Pueyo","Puy","Puyeta","Rafela","Raimunda","Raina","Rais","Reixina","ResurreciÃ³n","Rexina","Romeral","Rosabel","Rosenda","RoxÃ­o","RozÃ­o","Rut","SalÃº","Salas","Salut","Salz","SanÃ§a","SescÃºn","Silbia","Silvia","Sis","SoledÃ¡","Soledat","Telba","Telva","Teresa","Tremedal","Tresa","Tricia","TrinidÃ¡","Trinidat","Trizia","Ufemia","Unicie","Uridice","UrruÃ©s","Usebia","Valandina","Valantina","Valeria","Valeriana","Vanesa","Vera","Veronica","Vicena","Violant","Violeta","Virchinia","Viridiana","Virilia","Virtutz","Vitoria","Xara","Ysabel","Zelena","Zelia","Zilia","Zillas","Zintia","Zirenia","Zoya",
    "Adelma",	"Agostina",	"Agueda",	"Aidée",
    "Ailen",	"Alcira",	"Aldana",	"Alejandra",
    "Alfonsina",	"Almudena",	"Alondra",	"Ambar",
    "America",	"Amparo",	"Anaeli",	"Analia",
    "Analis",	"Angeles",	"Antonieta",	"Araceli",
    "Arantza",	"Aranza",	"Arcelia",	"Arellys",
    "Ariadna",	"Ariana",	"Arianne",	"Aroa",
    "Ayelen",	"Aylen",	"Azucena",	"Azul",
    "Asunción",  	"Asun",  	"Ascensión",  	"Amarilis",
    "Amaranta",  	"Adoración",  	"Aracelis",  	"Aracely",
    "Anunciación",  	"Angelita",  	"Amada",  	"Alita",
    "Adora",  	"Adelita",  	"Azeneth",  	"Amaya",
    "Amy",	"Amadéa",	"Alanis",	"Aïsha",
    "Agnès",	"Agustina",	"Andréa",	"Adelaïda",
    "Alicia",	"Alison",	"Alexa",	"Alexandra",
    "Alexia",	"Aglaé",	"Aura",	"Arantxa",
    "Ana",	"Anabel",	"Anabella",
    "Ana-Maria",	"Ana-Laura",	"Ana-Clara",	"Ana-Luisa",
    "Ambrosia",	"Ariel",	"Angalina",
    "Adela",	"Adelina",	"Aline",	"Amaranthe",
    "Ainhoa",	"Afra",	"Avelina", "Benilda",	"Betiana",	"Betina",	"Betsabe",
    "Briseyda",	"Benigna",  	"Bernardita",
    "Bethania",  	"Bienvenida",  	"Brunilda",  	"Brunella",	"Benita",	"Bertha",	"Blanca",
    "Blanca-Estèla",	"Bella",	"Beatriz",	"Begoña",
    "Brenda",	"Belen", "Candela",	"Candelaria",	"Caridad",	"Carlina",
    "Carlota",	"Catalia",	"Celene",	"Charo",
    "Chita",	"Concepcion",	"Conception",	"Conchita",
    "Cintia",	"Circe",	"Citlalli",	"Claudina",
    "Calixta",  	"Cande",  	"Candelas",  	"Carmelita",
    "Celestina",  	"Chelo",  	"Chus",  	"Concha",
    "Consuela",	"Crescencia",  	"Cruzita",  	"Custodia",
    "Célia",	"Carmina",	"Coral",	"Constanza",
    "Carolin",	"Clarisa",	"Chiara-Maria",
    "Corina",	"Cloé",	"Célina",
    "Carina",	"Catalina",	"Catherine",	"Casandra", "Dalma",	"Damaris",	"Darlyne",	"Deidamia",
    "Delicia",	"Denisse",	"Dilcia",
    "Dilean",	"Dinora",	"Dominga",	"Domitila",
    "Dina",	"Danaé",	"Désirée",	"Dana",
    "Dania",	"Dulce",	"Delta",	"Doïna",
    "Dominica",	"Dominico",	"Daina", 	"Edelmira",	"Edilma",	"Eduina",
    "Elba",	"Elcira",	"Elenor",	"Elida",
    "Elinathan",	"Eloisa",	"Elva",
    "Emilce",	"Encarnacion",	"Enriqueta",	"Ercilia",
    "Erlinda",	"Esneda",	"Etelvina",	"Evangelina",
    "Evelia",	"Elodia",  	"Emelina",  	"Emigdia",
    "Emperatriz",  	"Encarna",  	"Encarnita",  	"Eléonor",
    "Estefania",	"Emanuella",	"Elena-Ofelia",
    "Esther",	"Estèla",	"Estrella",	"Ethel",
    "Elvia",	"Erika",	"Eda",	"Enid",
    "Ernestina",	"Esperanza",	"Ermanda",	"Emilia",
    "Edna",	"Ema",    "Eve",	"Evita", "Felicidad",	"Farina",	"Felicitas",	"Felipa",
    "Felisa",	"Fiama",	"Filis",	"Fina",
    "Florentina",	"Francisca",	"Feliciana",  	"Fran",
    "Fernanda",	"Fiona",	"Florencia",	"Félicia",
    "Fidelia",	"Fidelina",	"Fidela",	"Fania", "Genovea",	"Geraldina",	"Gimena",	"Ginna",
    "Gintare",	"Glorymar",	"Goretti",	"Graciela",
    "Grecia",	"Grisel",	"Griselda",	"Guadalupe",
    "Guillermina",	"Garsea",  	"Graciana",  	"Gala",
    "Gina",	"Giulianna",	"Galia",	"Gilberta",
    "Gil",	"Giselle",	"Gisel",	"Gisela",
    "Giselda",	"Gisell",	"Gabriela",	"Grace",
    "Gracia",	"Georgina",	"Gertrudis", "Gretel",	"Gladys",	"Glenda", "Hebe",	"Herendiara",	"Herminia",
    "Higinia",	"Hilda",	"Helena",	"Hannah",	"Hortensia",	"Helga",	"Heidi",	"Hedda", "Idalia",	"Iracema",	"Irupe",	"Iselda",
    "Isolda",	"Itati",	"Izana",	"Idoya",
    "Inmaculada",  	"Isabela",  	"Ivette",  	"Iliana",
    "Isolde",	"Iona",	"Itzel",	"Inma",
    "Isabel",	"Isadora",	"Ignacia",	"Isaura",
    "Isis",	"Ina",	"Irina", "Jacinta",	"Javiera",	"Janeth",	"Jannette",
    "Jazmin",	"Jerie",	"Jimena", "Jocabed",	"Jorgelina",	"Julieta",
    "Justiniana",	"Jesenia",  	"Jessenia",  	"Jesusa",
    "Joaquina",  	"Jordana",  	"Jovita",  "Julia",	"Julieta",	"Juliana",
    "Jade",	"Josépha",	"Joséfina",	"Jane",
    "Janet",	"Jeanne",	"Joanna",	"Johanna",
    "Juanita",	"Jeanette",	"Jenna",	"Joana",
    "Juana",	"Jo-Ann",	"Jocelin",	"Jésabel", "Katja",	"Kristine",	"Karyme",	"Katsya",
    "Keisi",	"Kobra",	"Kyra",	"Kiara","Karla",	"Karina", 	"Laisha",	"Larisa",
    "Laurentina",	"Léonela",	"Libertad",	"Libia",
    "Ligia",	"Lihuen",	"Liliam",	"Lilyane",
    "Lisaida",	"Lisseth",	"Lissette",	"Lizzeth",
    "Llisaida",	"Lorelis",	"Loyda",	"Lucrecia",
    "Luisiana",	"Luisina",	"Lupina",	"Lupita",
    "Luz",	"Laurita",  	"Loida",  	"Ludmila",
    "Léticia",	"Lynda",	"Léonor",	"Laurence", "Loren",	"Lorna",	"Laureana",
    "Lida",	"Lis",	"Lola",	"Lolita",
    "Lupe",	"Leslie",	"Lucila",	"Lucina",
    "Lucinda",	"Lilia", "Lila",	"Lourdes",	"Lidia-Cira", "Maca",	"Macarena",	"Maida",	"Malenca",
    "Marcela",	"Margoth",	"Marianela",	"Mariangela",
    "Mariangeles",	"Maricel",	"Maricela",	"Marilina",
    "Marilu",	"Marlena",	"Marzela",	"Marzul",
    "Mayra",	"Merlina",	"Micaela", "Miguelina",	"Milénia",	"Millie",
    "Mireya",	"Mora",	"Morela",	"Macaria",
    "Manola",  	"Manuelita",  	"Marianita",  	"Maricruz",
    "Marisela",  	"Maristela",  	"Martirio",  	"Martita",
    "Máxima",  	"Mayte",  	"Merche",  	"Miguela",
    "Modesta",  	"Mélina",	"Mélinda",	"Mélisa",
    "Mabel",	"Magnolia",	"Marita",	"Maïtena",
    "Maria-Auxiliadora",	"Maria-Emilce",	"Maria-Socorro",	"Mariel",
    "Mariela",	"Mariella",	"Marietta",	"Marisol",	"Marissa",	"Mia",
    "Myrna",	"Maria-Eugénia",	"Maria-Del-Carmen",	"Maria-Inès",
    "Maria-Fernanda",	"Maria-José",	"Maria-Del-Jésus",	"Maria-Hélèna",
    "Maria-Eléna",	"Maïté",	"Maria-Clara",	"Maria-Paz",
    "Maria-Lourdes",	"Maritza",	"Maria-Emilia",	"Mariana",
    "Maribel",	"Maribella",	"Martha",	"Marta-Lucia",
    "Martha-Sonia",	"Marcelina",	"Marcia",	"Manel",
    "Manuela",	"Manuella",	"Madeleine",	"Madeline",
    "Maddelline",	"Madelyn",	"Magdalena",	"Malena",
    "Milagros",	"Monserrath",	"Montserrat",	"Mélanie",
    "Magali",	"Margaret",	"Margot",	"Marjorie",
    "Margarita",	"Maya", "Nicolasa",  	"Nohemi",  	"Nieve",  	"Narcisa",
    "Nayeli",	"Nelda",	"Nelida",	"Nellida",
    "Nereida",	"Nicolasia",	"Nidia",	"Nilda",
    "Niriel",	"Nube",	"Nubia", "Naomi", "Nadina", "Nuria", "Nina",	"Natacha",
    "Natasha",	"Nathalie",	"Natali",	"Noélia",	"Nieves",	"Nerea",
    "Natividad",	"Nazarena",	"Nicole", "Olalla",  	"Odalys",  	"Obdulia",	"Odalis",
    "Odili",	"Olenca",	"Onelia",	"Orfilia",
    "Orieta",	"Oliva",	"Olivera", "Perpetua",  	"Paca",  	"Pastora",  	"Pepita",
    "Pascuala",  	"Pacífica",  	"Pandora",	"Priscila",
    "Paloma",	"Paquita",	"Paz",	"Patricia",
    "Petra",	"Paula",	"Paulina",	"Piedad",
    "Pia", "Rosenda",  	"Reyes",  	"Ricarda",  	"Ruperta",
    "Rosalva",  	"Rafa",	"Rosita",	"Rebeca",
    "Reyna",	"Rudecinda",	"Roxana",	"Raquel", "Rafaëla",	"Reina",	"Romane",
    "Rosalba",	"Roselia",	"Rosella",	"Rosinda", "Sancha",  	"Sanchia",  	"Sens",  	"Sence",
    "Salud",  	"Susanita", "Socorro",
    "Stela", "Surama",	"Sahara",
    "Salena",	"Silvina",	"Siomara",	"Sylma",
    "Samanta",	"Samara",	"Sandra",	"Sasha",
    "Stella-Maris",	"Savannah",	"Sélina",	"Susana",
    "Salomé",	"Shakira",	"Saraï",
    "Selenia",	"Soledad", "Teresita",  	"Teófila",  	"Tomasa",  	"Tere",
    "Taalia",	"Taua",	"Trinidad",	"Talia",
    "Trini",	"Thaïs",	"Thelma",	"Telma", "Uma",	"Uriel", "Valencia",  	"Visitación",  	"Varinia",	"Vicenta",
    "Vasti",	"Venecia",	"Ventura",	"Verenice",
    "Violeta",	"Valeska",	"Vanina",	"Vanesa",
    "Vilma",	"Victoria",	"Verena", "Xochilt",  	"Ximena",	"Xiomara",	"Xochitl",
    "Xénia", "Yesenia",  	"Ysabel",  	"Yanet",	"Yannel",
    "Yadira",	"Yanina",	"Yazmin",	"Yaima",
    "Yamila",	"Yamile",	"Yaneth",	"Yanira",
    "Yara",	"Yareni",	"Yasna",	"Yennifer",
    "Yesmine",	"Yessena",	"Yhoalibeth",	"Yilda",
    "Yuana",	"Yolanda",	"Yasmina",	"Yasmin",
    "Yvonne", "Zarela",	"Ziva",	"Zenaïda",	"Zaïda",
    "Zulema",	"Zulma",	"Zunilda",	"Zurine",
    "Zoraïda",	"Zoila"
};

QVector<QString> Conquistadors::NOMS = {
    "Acosta", "Acuña", "Adalbéron",     "Abril",
    "AbadÃ­a","Abarca","AbellÃ¡n","Abiego","Acorella","AdriÃ¡n","Agea","Ager","Agramunt","AgustÃ­n","AlbarracÃ­n",
    "AlberÃ³","AlcalÃ¡","Alcolea","Alfaro","Alicante","Almunia","Alos","Amalric","AragonÃ©s","Arcas","Aymerich",
    "Aznar","Balaguer","Baldovinos","BandrÃ©s","Baptista","Barrachina","Batista","Bautista","Bermund","Boix",
    "Bonfill","Borrell","Bruguer","Burguera","Burrell","CaballerÃ­a","Caballero","Cabra","Cacho","Cajal","Calasanz",
    "CalderÃ³n","Canyelles","Castellblanc","CebriÃ¡n","Centelles","CerdÃ¡n","Ceret","Cirera","Claver","Clemente",
    "Desclot","Donat","Egea","Ena","Entenza","Ermengol","Escolano","EstÃ©banez","Estanyol","Feliu","Ferrer",
    "Font","FortiÃ ","Garcia","Gironella","Grau","Gualba","Guitarra","Jofre","Lagos","Latorre","March","Marquet",
    "Martell","Martorell","Mas","Massa","Massot","MirÃ³","Morer","Muntaner","Murillo","Navarro","Noguera","Notario",
    "Oms","Penyafort","Planas","Ponts","Prat","Puig","Rami­rez","Ramon","Riba","Riera","Roca","Roig","Roldaño","Romero","Rosellao","Rovira","Sacristaño","Sagarra","Samper","Sanz","Segarra","Texidor","Torquelles","VallÃ¨s","Vilagrassa","Vilaregut","de Arcas","de la CaballerÃ­a"
    "Aguilar",
    "Aguilera",
    "Aguirre",
    "Alcaraz",
    "Almodóvar",
    "Alvar",
    "Álvarez",
    "Álvaro",
    "Arocena",
    "Arregui",
    "Arteaga",
    "Arteta",
    "Aznar",
    "Baeza",
    "Bahamonte",
    "Balaguer",
    "Bañuelos",
    "Barberá",
    "Bárcenas",
    "Bello",
    "Berdugo",
    "Berenguer",
    "Biraben",
    "Blasco",
    "Bolívar",
    "Cabestany",
    "Cadalso",
    "Campos",
    "Campuzano",
    "Canuto",
    "Caperochipi",
    "Carvallo",
    "Casal",
    "Castro",
    "Catalán",
    "Cebrián",
    "Cedeño",
    "Cervantes",
    "Cervera",
    "Cisneros",
    "Colón",
    "Cortés",
    "Domínguez",
    "Echeberría",
    "Echepare",
    "Encinas",
    "Escobar",
    "Feijoó",
    "Fernández",
    "Ferrando",
    "Fraga",
    "Francés",
    "Franco",
    "Gabaldón",
    "Gacía",
    "Gacías",
    "Gació",
    "Garcés",
    "Garsés",
    "Garzia",
    "Garzón",
    "Gaztea",
    "Pérez",
    "Gaciot",
    "Garcea",
    "Garceller",
    "Gárcez",
    "Garci",
    "García",
    "Garcías",
    "Garibay",
    "Garsea",
    "Gartzea",
    "Gartzes",
    "Gartzia",
    "Garzea",
    "Gasía",
    "Gassía",
    "Gassías",
    "Giménez",
    "Gomez",
    "Gómez",
    "Góngora",
    "González",
    "Gorrochategui",
    "Goya",
    "Gutiérrez",
    "Heredia",
    "Hernández",
    "Herrera",
    "Herrero",
    "Hortelano",
    "Ibáñez",
    "Irigoyen",
    "Jiménez",
    "Láñez",
    "Llorente",
    "López",
    "Machado",
    "Machain",
    "Machinandiarena",
    "maestre",
    "Marichalar",
    "Martínez",
    "Matilla",
    "Melo",
    "Mendoza",
    "Molina",
    "Monardes",
    "Montoya",
    "Morales",
    "Moreno",
    "Morestin",
    "Múgica",
    "Muñoz",
    "Murillo",
    "Núñez",
    "Ordoqui",
    "Ortiz",
    "Pacheco",
    "Pastor",
    "Pinilla",
    "Puértolas",
    "Quesada",
    "Quílez",
    "Ramírez",
    "Ribera",
    "Robledo",
    "Rodas",
    "Rodríguez",
    "Rumi",
    "Sanches",
    "Sánchez",
    "Sancho",
    "Santana",
    "Santín",
    "Sedeño",
    "Segura",
    "Sepúlveda",
    "Somoza",
    "Soriano",
    "Suárez",
    "Tarín",
    "Torres",
    "Trujillo",
    "Ubeda",
    "Ubieto",
    "Unamuno",
    "Urcelay",
    "Valenciano",
    "Vargas",
    "Velasco",
    "Velasques",
    "Velásquez",
    "Velázquez",
    "Vera",
    "Verdugo",
    "Vicente",
    "Vidal",
    "Villalobos",
    "Villanueva",
    "Villar",
    "Ximenes",
    "Ximénez",
    "Zamora",
    "Zapatero",
    "Zaplana"
};

EvtConquistadors::EvtConquistadors(int indexEvt):GenerateurNoeudsProbables (indexEvt)
{
    double tmp_Modificateur = 1.0; //pour les tests (doit être à 0 en prod)
    switch (indexEvt) {
    case 0 : {
        m_Nom = "Conversion des pauvres";
        m_Description = "????";
        m_ConditionSelecteurProba = make_shared<Condition>(0.1 + tmp_Modificateur, p_Relative);
        m_Conditions.push_back(
             make_shared<Condition>(EconomieEvt::C_NIVEAU_ECONOMIQUE, "-4", Comparateur::c_InferieurEgal));
        m_Conditions.push_back(
             make_shared<Condition>(Coterie::C_COTERIE, Coterie::CONQUISTADORS, Comparateur::c_Different));
        m_CallbackDisplay = [] {
            Humain* humain = Humain::GetHumainJoue();
            shared_ptr<Effet> effet = ExecHistoire::GetEffetActuel();
            effet->m_Texte = "Alors que vous êtes au plus bas à déprimer dans un bar vous êtes abordé par un conquistador en armure jovial."
                            "Il vous vante la vie aventureuse aux confins du monde où vous pourrez avoir une vie aventureuse pleine de combats et de pillages. "
                            "Là où la fortune se fait au mérite loin des magouilles politiciennes.";

            // devient conquistador ??
            shared_ptr<Coterie> conqui = Extremis::GetCoterie(Coterie::CONQUISTADORS);

            double proba = Aleatoire::GetAl()->Entre0Et1();
            if ( proba < 0.3 ) {
                humain->GagneCeTrait(aventureux, effet);
            }
            proba = Aleatoire::GetAl()->Entre0Et1();
            if ( proba < 0.3 ) {
                humain->GagneCeTrait(cupide, effet);
            }
            proba = Aleatoire::GetAl()->Entre0Et1();
            if ( proba < 0.3 ) {
                humain->GagneCeTrait(opportuniste, effet);
            }

            proba = conqui->Compatibilite(humain);
            if ( proba >= Coterie::SEUIL_CONVERSION) {
                conqui->RejoindreCoterie(humain, effet);
            } else {
                effet->m_Texte += "Ca ne suffit néanmoins pas à vous convaincre de devenir un conquistador.";
            }
        };
    }break;
    }
}
