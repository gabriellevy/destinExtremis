#include "croisadefranque.h"
#include "genviehumain.h"
#include "religion/religion.h"
#include "violence/combat.h"
#include "../destinLib/aleatoire.h"
#include "socio_eco/metier.h"
#include "../destinLib/exec/exechistoire.h"
#include "humain.h"
#include "../destinLib/abs/condition.h"
#include "geographie/quartier.h"
#include <QDebug>
#include "genviehumain.h"
#include "socio_eco/crime.h"
#include "extremis.h"
#include "socio_eco/economieevt.h"

using std::make_shared;
using std::shared_ptr;

CroisadeFranque::CroisadeFranque()
{
    Initialisation();
}

shared_ptr<Quartier> CroisadeFranque::GenererQuartier()
{
    m_Quartier = make_shared<Quartier>("Saint Denis", "Quartier des Croisés", ":/images/croisade_franque/logement.jpg", this);
    Extremis::QUARTIERS[m_Quartier->m_Nom] = m_Quartier;
    return m_Quartier;
}

QString CroisadeFranque::GetMusique()
{
    return "qrc:/sons/croisade/rejoindre.mp3";
}


QString CroisadeFranque::GetGentile(bool masculin)
{
    return masculin?"croisé":"croisée";
}

void CroisadeFranque::GenererTraitCompatibles()
{
    m_TraitsCompatible = {
        make_shared<Condition>(Trait::GetNomTrait(eTrait::honorable), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Religion::C_FOI, Religion::CHRETIEN, Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::sens_du_sacrifice), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::franc), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::spirituel), "1", Comparateur::c_Egal )
    };
    m_TraitsIncompatible = {
        make_shared<Condition>(Trait::GetNomTrait(eTrait::opportuniste), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::sournois), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::faible), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::chetif), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::cupide), "1", Comparateur::c_Egal )
    };
    m_MetiersAssocies = {
        Metier::ARCHITECTE,
        Metier::PAYSAN,
        Metier::POLICIER,
        Metier::VIGILE,
        Metier::GARDE_DU_CORPS,
        Metier::FORGERON
    };
}

QString CroisadeFranque::GetNom()
{
    return "Croisade franque";
}

double CroisadeFranque::GetPoidsDemo()
{
    return 1.0;
}

QString CroisadeFranque::GetDescription()
{
    return "Description des Croisés";
}

QString CroisadeFranque::GetDescriptionUniversite()
{
    return "Les croisés";
}

QString CroisadeFranque::GetImage()
{
    return ":/images/croisade_franque/Chevaliers_premières_croisades.jpg";
}

std::shared_ptr<Effet> CroisadeFranque::AjouterEffetUniversite(GenHistoire* genHist, shared_ptr<Evt> evt, QString go_to_effet_suivant )
{
    QVector<shared_ptr<NoeudProbable>> noeudsProbaEducation;

    // formation religieuse
    {
        shared_ptr<Effet> effet1 = genHist->AjouterEffetNarration(
                    "Un croisé se doit d'être un fervent chrétien dévoué à la guerre sainte. "
                    "\nVous passez des jours entiers à prier dans la dévotion des images saintes à suivre les cours de catéchisme des franciscains.",
                    ":/images/croisade_franque/priant.jpg",
                    "", evt);
        Religion::ModifierEffetEnEffetConversion(effet1, Religion::CHRETIEN);
        effet1->m_GoToEffetId = go_to_effet_suivant;
        shared_ptr<Condition> cond1 = make_shared<Condition>(1.0, TypeProba::p_Relative);
        shared_ptr<NoeudProbable> noeud1 = make_shared<NoeudProbable>(
                    effet1,
                    cond1);
        noeudsProbaEducation.push_back(noeud1);
    }

    // effetCombat
    {
        shared_ptr<Effet> effet = genHist->AjouterEffetNarration(
                    "On ne peut devenir croisé qu'une fois qu'on maîtrise le système de combat ancestral du croisé franc. "
                    "De plus, comme l'essentiel des querelles sont réglés par un duel sous le jugement de Dieu il est indispensable de savoir se défendre pour se faire respecter dans les quartiers de la croisade."
                    "\nVotre formation contient bien sûr un entrainement avec de célbres maîtres d'armes.",
                    ":/images/croisade_franque/duel_chevalier.jpg",
                    "", evt);
        effet->m_GoToEffetId = go_to_effet_suivant;
        effet->AjouterAjouteurACarac(Combat::C_CAP_COMBAT, "1"); // meilleur combattant
        shared_ptr<Condition> condCombat = make_shared<Condition>(1.0, TypeProba::p_Relative);
        shared_ptr<NoeudProbable> noeudCombat = make_shared<NoeudProbable>(
                    effet,
                    condCombat);
        noeudsProbaEducation.push_back(noeudCombat);
    }

    // effet Cavalerie
    {
        shared_ptr<Effet> effet = genHist->AjouterEffetNarration(
                    "Savoir s'occuper d'un cheval est indispensable chez les croisés. Que ce soit pour être chevalier ou simple paysan."
                    "Votre formateur vous apprends les bases de l'équitation et de tout ce qui tourne autour de l'entretien des chevaux.",
                    ":/images/croisade_franque/cheval.jpg",
                    "", evt);
        effet->m_GoToEffetId = go_to_effet_suivant;
        effet->AjouterAjouteurACarac(Combat::C_EQUITATION, "2");
        effet->AjouterAjouteurACarac(Metier::PAYSAN, "1");
        shared_ptr<Condition> condCombat = make_shared<Condition>(1.0, TypeProba::p_Relative);
        shared_ptr<NoeudProbable> noeudCombat = make_shared<NoeudProbable>(
                    effet,
                    condCombat);
        noeudsProbaEducation.push_back(noeudCombat);
    }

    // effet architecte
    {
        shared_ptr<Effet> effet = genHist->AjouterEffetNarration(
                    "La construction de châteaux imprenables est la spécialité des croisés. Avec l'interdiction des guerres les châteaux sont peu importants. Les compétences en architecture des croisés restent bien utiles et votre tuteur vous en fait profiter",
                    ":/images/croisade_franque/chateau.jpg",
                    "", evt);
        effet->m_GoToEffetId = go_to_effet_suivant;
        effet->AjouterAjouteurACarac(Metier::ARCHITECTE, "2");
        shared_ptr<Condition> condCombat = make_shared<Condition>(1.0, TypeProba::p_Relative);
        shared_ptr<NoeudProbable> noeudCombat = make_shared<NoeudProbable>(
                    effet,
                    condCombat);
        noeudsProbaEducation.push_back(noeudCombat);
    }

    // hospitaliers
    {
        shared_ptr<Effet> effet = genHist->AjouterEffetNarration(
                    "Les hospitaliers sont des croisés qui ont juré de protéger et soigner les faibles quelle que soit leur race, religion ou coterie et ce gratuitement de manière complètement désintéressée."
                    "\nVous êtes amenés à travailler durement dans un de leurs hospices à soigner les vieux, les malades et les femmes enceintes.",
                    ":/images/croisade_franque/hospice.jpg",
                    "", evt);
        effet->m_GoToEffetId = go_to_effet_suivant;
        effet->AjouterAjouteurACarac(Metier::MEDECIN, "1"); // meilleur médecin
        effet->m_CallbackDisplay = [] {
            shared_ptr<Effet> effet = ExecHistoire::GetEffetActuel();
            Humain* humain = Humain::GetHumainJoue();
            double proba = Aleatoire::GetAl()->Entre0Et1();
            if ( proba <= 0.4 && !humain->ACeTrait(sens_du_sacrifice)) {
                effet->m_Texte += "\nVous vous portez volontaires pour nettoyer les lépreux tant vous êtes prêt à prendre tous les risques pour les malades. Vous gagnez 'sens du sacrifice'.";
                humain->SetValeurACaracId(Trait::GetNomTrait(sens_du_sacrifice), "1");
            }
            proba = Aleatoire::GetAl()->Entre0Et1();
            if ( proba <= 0.4 && !humain->ACeTrait(altruiste)) {
                effet->m_Texte += "\nVous vous sentez vraiment à votre place parmi les malades. En quelques jours seulement vous faites passer leurs problèmes avant les votres. Vous gagnez 'Altruiste'.";
                humain->SetValeurACaracId(Trait::GetNomTrait(altruiste), "1");
            }
            proba = Aleatoire::GetAl()->Entre0Et1();
            if ( proba <= 0.4 && !humain->ACeTrait(angoisse)) {
                effet->m_Texte += "\nLe spectacle de toute cette misère vous affecte durement. Vous gagnez 'Angoissé'.";
                humain->SetValeurACaracId(Trait::GetNomTrait(angoisse), "1");
            }
        };
        shared_ptr<Condition> condCombat = make_shared<Condition>(1.0, TypeProba::p_Relative);
        shared_ptr<NoeudProbable> noeudCombat = make_shared<NoeudProbable>(
                    effet,
                    condCombat);
        noeudsProbaEducation.push_back(noeudCombat);
    }

    // chasseur de sorciers
    {
        shared_ptr<Effet> effet = genHist->AjouterEffetNarration(
                    "Les croisés méprisent la magie égoïste et imprévisible qui vient des hommes car c'est le diable qui la leur inspire. Ils vous forment donc dans la compréhension de ce qu'est la magie maléfique et de la différence avec les miracles divins."
                    "\nIls vous montrent aussi comment repérer les monstres et les démons qui complotent toujours dans l'ombre des hommes.",
                    ":/images/croisade_franque/priant_guerre.jpg",
                    "", evt);
        effet->m_GoToEffetId = go_to_effet_suivant;
        effet->AjouterAjouteurACarac(Metier::TUEUR_DE_MONSTRE, "1");
        effet->m_CallbackDisplay = [] {
            shared_ptr<Effet> effet = ExecHistoire::GetEffetActuel();
            Humain* humain = Humain::GetHumainJoue();
            double proba = Aleatoire::GetAl()->Entre0Et1();
            if ( proba <= 0.6 && !humain->ACeTrait(observateur)) {
                effet->m_Texte += "\nVous devenez redoutable dans la détection des détails. Vous gagnez 'observateur'.";
                humain->SetValeurACaracId(Trait::GetNomTrait(observateur), "1");
            }
        };
        shared_ptr<Condition> condCombat = make_shared<Condition>(1.0, TypeProba::p_Relative);
        shared_ptr<NoeudProbable> noeudCombat = make_shared<NoeudProbable>(
                    effet,
                    condCombat);
        noeudsProbaEducation.push_back(noeudCombat);
    }

    // honneur et traditions
    {
        shared_ptr<Effet> effet = genHist->AjouterEffetNarration(
                    "Un croisé digne de ce nom doit avoir un honneur sans faille ce qui passe avant tout par le respect de la parole donné et la fidélité au seigneur."
                    "\nEst requis aussi un grand courage dans la guerre comme dans la protection de la veuve et de l'orphelin."
                    "\nVous devenez 'honorable'.",
                    ":/images/croisade_franque/priant_guerre.jpg",
                    "", evt);
        effet->m_GoToEffetId = go_to_effet_suivant;
        effet->m_CallbackDisplay = [] {
            shared_ptr<Effet> effet = ExecHistoire::GetEffetActuel();
            Humain* humain = Humain::GetHumainJoue();
            humain->SetValeurACaracId(Trait::GetNomTrait(honorable), "1");
            double proba = Aleatoire::GetAl()->Entre0Et1();
            if ( proba <= 0.6 && !humain->ACeTrait(sens_du_sacrifice)) {
                effet->m_Texte += " Ainsi que 'sens du sacrifice'.";
                humain->SetValeurACaracId(Trait::GetNomTrait(sens_du_sacrifice), "1");
            }
        };
        shared_ptr<Condition> cond = make_shared<Condition>(1.0, TypeProba::p_Relative);
        shared_ptr<NoeudProbable> noeud = make_shared<NoeudProbable>(
                    effet,
                    cond);
        noeudsProbaEducation.push_back(noeud);
    }

    // techniques policiers/vigiles/garde du corps
    {
        shared_ptr<Effet> effet = genHist->AjouterEffetNarration(
                    "Les croisés combinent deux ensembles de qualités précieuses : des capacités martiales redoutables avec armes et à main nues. Et surtout une éthique sans faille."
                    " Ces qualités en font les meilleurs policiers du monde mais aussi de remarquables vigiles et garde du corps. Vous êtes formé aux bases de tous ces métiers.",
                    ":/images/croisade_franque/priant_guerre.jpg",
                    "", evt);
        effet->m_GoToEffetId = go_to_effet_suivant;
        effet->AjouterAjouteurACarac(Metier::POLICIER, 1);
        effet->AjouterAjouteurACarac(Metier::VIGILE, 1);
        effet->AjouterAjouteurACarac(Metier::GARDE_DU_CORPS, 1);
        shared_ptr<Condition> cond = make_shared<Condition>(1.0, TypeProba::p_Relative);
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

QString CroisadeFranque::GetId()
{
    return Coterie::CROISADE;
}

QString CroisadeFranque::CreerPatronyme(bool masculin)
{
    return (masculin?
               PRENOMS_M[Aleatoire::GetAl()->EntierInferieurA(PRENOMS_M.size())] + " " +
                            NOMS[Aleatoire::GetAl()->EntierInferieurA(NOMS.size())]:
               PRENOMS_F[Aleatoire::GetAl()->EntierInferieurA(PRENOMS_F.size())] + " " +
                       NOMS[Aleatoire::GetAl()->EntierInferieurA(NOMS.size())]
            );
}

QVector<QString> CroisadeFranque::NOMS = {
    "d'Aiglemont", "d'Aiguemorte", "d'Aiguevive", "d'Aspremont", "de Beaulieu", "de Beaupré", "de Belleforest",
    "de Bellegarde", "de Bénévent", "de Blancmoustier", "de Boisjoli", "de Boutefeu", "de Clairefontaine",
    "de Clairval", "de Clochemerle", "de la Combe-aux-Cerfs", "de la Combe-aux-Loups", "de Courtelande",
    "de Courtepaille", "d'Engoulevent", "de Fiercastel", "de Gardefeu", "de Hauterive", "de Hauteroche",
    "de Hautfort", "de Hurlevent", "du Lac de Maisonfort", "de Mondragon", "de Montaigu", "de Montalembert",
    "de Montardent", "de Montbard", "de Montfaucon", "de Montfleury", "deMontjoye", "de Montmirail",
    "de Montorgueil", "de Morneplaine", "de Mortelande", "de Mortelune", "de Neuville", "de Noirmoustier",
    "de Sautemouton", "de Sauveterre", "de Sombretour", "de Sombreval", "de Songecreux", "de Valvert",
    "le Bel", "le Bon", "le Brave", "le Fier", "le Franc", "le Hardi", "le Jeune", "le Matois", "le Preux", "le Sagace",
    "le Sage", "le Taciturne", "Barberousse", "Brisefer", "Coeur-de-Lion", "Dent-de-Loup", "Sang-de-Boeuf", "Taillefer",
    "Tuemouches", "Langlois", "Duchesne", "Marchand", "Boulanger", "le Chauve", "Courtois", "Ageorges", "Aubernard", "Alamartine",
    "Fromentin", "Rabier", "Coulomb", "Cabrera", "Poudevigne", "Messonnier", "Métivier", "Pelletier", "Larsonneur",
    "Castagnier", "Nouet", "Lebreton", "Manceau", "Legros", "Lenain", "Sarrazin", "Chauvin", "Roux",
    "Abarnou", "Abattu", "Abbadie", "Abéjean", "Abellan", "Abeloos", "Abijou", "Abillard", "Abisseror", "Abrassart",
    "Abravanel", "Abrazard", "Abribat", "Abric", "Abrigeon", "Abriol", "Absalon", "Acharles", "Acheriteguy", "Achotte",
    "Achouline", "Adélaïde", "Adelmard"
};

QVector<QString> CroisadeFranque::PRENOMS_M = {
    "Abbo","Abrahil","Abram","Adalard","Adalbert","Adalbertus","Adaldag","Adalgrimus","Adalhaid","Adalhard","Adalolf","Adelard","Aega","Ageric","Agilbert","Agilfride","Agiulf","Agobard","Aigulf","Alberic","Aldedramnus","Aldgisl","Allowin","Amalricus","Amand","Amator","Andica","Angegisis","Angilbart","Angilbert","Anno","Ansegisel","Anskar","Ansovald","Arbitio","Arbogast","Arbogastes","Arculf","Aregisel","Arnegisel","Arnold","Arnoul","Arnulf","Artaud","Asselin","Atacinus","Audoen","Audomar","Audoneus","Audovald","Audramnus","Austregisel","Avremarus","Badegisel","Balderic","Baldrick","Baudry","Baugulf","Bauto","Bavo","Benild","Berchar","Berengar","Berenger","Bernard","Bernardus","Bernhard","Berno","Bero","Bertelis","Berthaire","Berthefried","Bertin","Bertlinus","Bertram","Bertramnus","Bertulf","Besso","Birinus","Blutmund","Boso","Bovo","Brice","Britius","Brocard","Bruno","Burchard","Butilin","Carloman","Cassyon","Ceslinus","Ceufroy","Chararic","Charibert","Charles","Cheldric","Childebert","Childebrand","Childeric","Chilperic","Chlodion","Chlodmer","Chlodomer","Chlodowig","Chlodwig","Chlotar","Chramnesind","Chrodegang","Clodio","Clodomir","Clotaire","Clothair","Cloud","Clovis","Conrad","Corbinian","Corbus","Creatus","Cyr","Cyricus","Dado","Dagaric","Dagobert","Dalfin","Dietrich","Dodo","Dreux","Drogo","Drogon","Dudon","Durand","Ebbo","Eberhard","Eberulf","Ebregisel","Ebroin","Ebrulf","Egide","Einhard","Electeus","Electus","Emme","Emmeran","Emmon","Engelbert","Engilbert","Enguerrand","Enurchus","Eracle","Erard","Erchinoald","Erenfried","Eudes","Euric","Evrard","Evroul","Evroult","Farabert","Fardulf","Faro","Faroardus","Faroinus","Feremundus","Feroardus","Flodoard","Floribert","Folcard","Folmar","Foroenus","Fredegar","Fridolin","Fridugis","Frobertus","Frothardus","Frotlaicus","Fulbert","Fulcaire","Fulk","Fulrad","Gararic","Garivald","Gaudulfus","Gaujoinus","Gausbertus","Gausboldus","Gautmarus","Gedalbertus","Gedalcaus","Gerbert","Gereon","Gerold","Gifemund","Gilbert","Giselbert","Giseler","Gislevertus","Giso","Godalbertus","Godobald","Godomar","Godun","Goisfrid","Gondulph","Goscelin","Gouzlim","Gozbert","Gozolon","Griffon","Grifo","Grimald","Grimbald","Grimoald","Guadulfus","Guido","Gundobad","Gundovald","Gunthar","Guntram","Guntramn","Hagen","Haldemarus","Halinard","Hartgard","Hartmut","Hartnid","Helinand","Helisachar","Heribert","Hildebald","Hildebold","Hildeboldus","Hildegaudus","Hildeprand","Hildevoldus","Hildoinus","Hilduin","Hincmar","Hlodver","Hrodbert","Hubert","Huebald","Humbert","Hunald","Imbert","Imnachar","Imninon","Ingalbertus","Ingelram","Ingomer","Ingund","Jocelin","Karlmann","Lambert","Lanfranc","Lantbertus","Laudus","Lebuin","Ledger","Leger","Leodegar","Letard","Leudast","Leufred","Leufroy","Leutfrid","Leuthard","Leuthere","Liudger","Liudhard","Liudolf","Lo","Lothar","Ludger","Lul","Lull","Magnachar","Magneric","Maiuel","Maixent","Majorian","Malaric","Mallobaudes","Mansuetus","Marachar","Maraulf","Marcomir","Marcoul","Marellus","Martinus","Matfrid","Mauger","Maurifius","Medard","Meginhard","Merobaudes","Merovech","Monulph","Munderic","Nevelung","Nibelung","Nithard","Norbert","Nordbert","Notger","Notker","Odger","Odilo","Odilon","Odo","Odulf","Omer","Orderic","Otbert","Otker","Otto","Otton","Ouen","Ouus","Pacatian","Pair","Pancras","Panteleon","Paschal","Pepin","Philibert","Piligrim","Pippin","Poppo","Priarios","Puvis","Radbod","Radigis","Ragenard","Ragenardus","Ragenaus","Ragnachar","Ragnfred","Ragno","Ramnulf","Rathar","Rathier","Ratold","Razo","Reginald","Reginar","Reginard","Remacle","Remi","Reolus","Ricbodo","Ricchar","Ricfried","Richer","Richomer","Richomeres","Rigunth","Riquier","Rothad","Samo","Samson","Sergius","Sichar","Sicho","Siclandus","Sicleardus","Siclevoldus","Siegfried","Sigebert","Sigefroy","Sigeric","Sigibert","Sigismund","Sinopus","Suger","Suidbert","Suidger","Sunnegisil","Sunno","Syagrius","Tassilo","Taurin","Tescelin","Thankmar","Thegan","Theodard","Theodebert","Theodemir","Theodon","Theodore","Theodoric","Theodulf","Theodulph","Theodwin","Theoto","Theudebald","Theudebert","Theuderic","Theutgaud","Thierry","Thietmar","Trutgaudus","Turpin","Unroch","Vedast","Vicelin","Vigor","Vulmar","Waiofar","Wala","Walaric","Walcaud","Waldolanus","Waleran","Waltgaud","Wandregisel","Wandregisilus","Wandrille","Warmann","Wazo","Welf","Werinbert","Wibert","Wichmann","Wido","Willehad","Willibald","Willibrord","Willichar","Wolbodo","Wulfhard","Wulfram","Zwentibold",
    "ALPHONSE", "AMEDEE", "AMINA", "ARNAUD", "ARTHUR", "AUDOIN", "BAUDOIN",
    "Aalongue", "Abbaud", "Abbon", "Abelène", "Abran", "Abzal", "Acelin", "Achaire",
    "Achard", "Acheric", "Adalard", "Adalbaud", "Adalbéron", "Adalbert", "Adalelme",
    "Adalgaire", "Adalgise", "Adalicaire", "Adalman", "Adalric", "Adebran", "Adélard",
    "Adelbert", "Adelin", "Adenet", "Adhémar", "Adier", "Adinot", "Adolbert", "Adon",
    "Adoul", "Adrier", "Adson", "Agambert", "Aganon", "Agebert", "Agelmar", "Agelric",
    "Agenulf", "Agerad", "Ageran", "Agilbert", "Agilmar", "Aglebert", "Agmer", "Agnebert", "Agrestin", "Agrève",
    "Aibert", "Aicard", "Aimbaud", "Aimin", "Aimoin", "Airard", "Airy", "Alard", "Albalde", "Albaud", "Albéron",
    "Alboin", "Albuson", "Alchaire", "Alchas", "Alcuin", "Alleaume", "Amanieu", "Amat", "Amblard", "Anaclet",
    "Ansbert", "Anselin", "Ansoald", "Archambaud", "Arembert", "Arnat", "Artaud", "Aubry", "Authaire", "Avold",
    "Ayoul", "Barnoin", "Barral", "Baudri", "Bérard", "Bérenger", "Bernon", "Bettolin", "Betton", "Brunon",
    "Burchard", "Caribert", "Centule", "Childebert", "Chilpéric", "Cillien", "Clodomir", "Clotaire", "Cloud",
    "Colomban", "Conan", "Conrad", "Cybard", "Dacien", "Dadon", "Dalmace", "Dambert", "Dioclétien", "Doat",
    "Drogon", "Durand", "Eadwin", "Ebbon", "Ebehard", "Eddo", "Edwin", "Egfroi", "Égilon", "Eilbert", "Einold",
    "Éon", "Ermenfred", "Ermengaud", "Ernée", "Ernold", "Ernoul", "Eumène", "Eunuce", "Euric", "Eustaise", "Euverte",
    "Evroult", "Fleuret", "Flocel", "Flodoard", "Flouard", "Flour", "Floxel", "Folquet", "Fortunat", "Foulque",
    "Frajou", "Frambault", "Frambourg", "Frameric", "Francaire", "Fulbert", "Gailhart", "Gaillon", "Garréjade",
    "Gaubert", "Gerbert", "Giboin", "Gildric", "Gislebert", "Godomer", "Gossuin", "Guéthenoc", "Guibin", "Guiscard",
    "Hatton", "Haynhard", "Héribert", "Herlebald", "Herlebauld", "Herlemond", "Hildebald", "Hildebrand",
    "Hilduin", "Hoel", "Honfroi", "Hugon", "Humbaud", "Isembert", "Ithier", "Jacquemin", "Jacut", "Lagier", "Lambert",
    "Lancelin", "Léothéric", "Lidoire", "Lisiard", "Lothaire", "Lubin", "Maïeul", "Malulf", "Marcuard", "Maric",
    "Materne", "Matfrid", "Matifas", "Maur", "Mauront", "Mesmin", "Milon", "Odo", "Oldaric", "Orderic", "Oricle",
    "Premon", "Rachio", "Radoald", "Radulf", "Raginard", "Raimbaut", "Raimbert", "Rainier", "Rainon", "Ramnulf",
    "Ranulfe", "Rataud", "Rodron", "Romary", "Roscelin", "Rostang", "Salvin", "Savaric", "Savary", "Sébaste",
    "Senoc", "Sicard", "Siegebert", "Sifard", "Sigebert", "Taillefer", "Taurin", "Théodebert", "Théodemar",
    "Theoderich", "Théodran", "Thérouanne", "Thiégaud", "Ursicin", "Ursion", "Vantelme", "Volusien", "Warin",
    "Wigeric", "Willibert", "Wulfoald", "Wulgrin",
    "Acelin", "Amaury", "Anselme", "Anthiaume", "Arthaud", "Aubert", "Audibert", "Aymeric", "Aymon", "Barthélémi",
    "Benoît", "Bérard", "Bernier", "Bertrand", "Bohémond", "Edmond", "Enguerrand", "Ernaut", "Eudes", "Galaad",
    "Garin", "Garnier", "Gauthier", "Gauvain", "Gibouin", "Gilemer", "Girart", "Godefroy", "Gontran",
    "Gonzagues", "Grégoire", "Guerri", "Guilhem", "Hardouin", "Herbert", "Herchambaut", "Hubert", "Hugues",
    "Huon", "Jehan", "Lancelot", "Merlin", "Perceval", "Philibert", "Raoul", "Raymond", "Renaud", "Robert",
    "Roland", "Savari", "Sigismond", "Tancrède", "Thibaut", "Tristan", "Urbain", "Ybert", "Yvain", "Abélard"
};

QVector<QString> CroisadeFranque::PRENOMS_F = {
    "Ada","Adala","Adalberta","Adalind","Adalindis","Adallind","Adallinda","Adalmut","Adalrada","Adaltrude","Adaltrutis","Adaluuidis","Adalwif","Adda","Addela","Adela","Adelaidis","Adele","Adelhaid","Adelheid","Adeltrudis","Adhela","Adwala","Aebbe","Agatha","Agentrudis","Agglethrudis","Albelenda","Albofleda","Albruga","Alburch","Alburg","Aldguda","Aldgudana","Aldruth","Alfgarda","Alfild","Alflent","Alpaida","Alpaide","Alpais","Amabilia","Amalberga","Amalbirga","Amoltrud","Amulberga","Anselda","Ansgard","Anstruda","Aregund","Athalia","Athela","Atula","Aua","Auacyn","Aubirge","Aude","Audofleda","Audovera","Auekin","Auin","Auina","Auriana","Austrechild","Ava","Avacyn","Avekin","Avin","Baldechildis","Baltelda","Balthechildis","Balthildis","Basina","Bauin","Bava","Bavacin","Bave","Bavin","Begga","Belegardis","Benedicta","Berchildis","Berehta","Berenga","Beretrude","Bergard","Bergundis","Berhta","Beriungis","Berna","Bernewief","Bernewif","Berta","Bertaida","Bertha","Berthe","Berthefled","Berthefried","Berthegund","Berthildis","Berthlenda","Bertildis","Bertliana","Bertoane","Bertrada","Bertruda","Bertswinda","Bettin","Bilichildis","Blesinde","Blitekin","Boltiarda","Bova","Boviardis","Brunhild","Brunhilda","Burgundefara","Childebertana","Chlodeswinthe","Chlodosind","Chlothsinda","Chrodechildis","Chrodtrude","Chunsina","Cilia","Clodauuiua","Clothild","Clotild","Clotilde","Clotrada","Conegont","Conegundis","Conegunt","Crapahildis","Cunegonde","Cunegund ","Cunegundis","Dadin","Dagarada","Danburga","Deuteria","Doda","Dodda","Duda","Eadgithu","Ealswid","Ebertana","Edeberga","Edeborg","Ega","Egecin","Egeluuara","Egesburga","Egesloga","Ehgelhild","Ehgeluuara","Ellinrat","Emecin","Emma","Engelberga","Engelberge","Engelgard","Engelsuit","Engeltrude","Engeluuara","Engelwara","Enna","Erchembrog","Eremburgis","Ereprad","Erkembrog","Erkenbrog","Erkenburoc","Erkenrad","Ermecin","Ermegardis","Ermenberga","Ermengard","Ermengarda","Ermengarde","Ermengardis","Ermentrudis","Ermeswindis","Ermina","Erpsuid","Errictruda","Ethelchif","Ethelgard","Ethelgarda","Euerloga","Everelda","Evereldis","Faileuba","Fara","Fastrada","Flouerana","Folclind","Folclinda","Folcrada","Folcuuara","Folgarda","Folsuindis","Folsuuendis","Fordola","Fortlifh","Foy","Frauuara","Fredeburgis","Fredegunde","Frederada","Fredeuuara","Frethegard","Frethesuinda","Frethesuindis","Fridesuenda","Fridewiga","Frisburgis","Frithelinda","Frouuin","Frouuina","Galswinth","Geila","Gelduuara","Geneva","Genofeva","Gerberga","Geretrudis","Gerlent","Gerlinda","Gersenda","Gersuenda","Gersuinda","Gersvinda","Gertruda","Geruuara","Geua","Geva","Gisela","Gisla","Glismodis","Godalinda","Godeca","Godecin","Godelda","Godelinda","Godildis","Goduuara","Goiswinth","Gomatrudis","Gothuuera","Grimuuara","Gudula","Gudule","Gundrada","Gundrade","Gundradis","Guntheuc","Gunza","Guodhelda","Guodlia","Hadaken","Hamesindis","Harwara","Hatilde","Hazeca","Heilewif","Heilswinda","Heldeburga","Heletradana","Heleuuidis","Helinda","Heltrada","Hengelsenda","Herden","Herdin","Herenborg","Herenfrida","Herleva","Herlinda","Hermengarda","Hildberta","Hildborg","Hildcardis","Hildeberga","Hildeburg","Hildegard","Hildegarde","Hildegardis","Hildegund","Hildelana","Hildemunda","Hildeswindis","Hildeuuara","Hildeuuif","Hildewara","Hildewif","Hildrada","Hildwara","Hiltrude","Himiltrud","Hirmenlind","Hodierna","Hostaruuara","Hruodgarda","Hruotberta","Hruothraud","Ida","Idasgarda","Ideslef","Idesuuif","Ideswif","Idisiardis","Imicina","Imma","Ingela","Ingelburga","Ingelswindis","Ingeltrud","Ingeltrude","Ingeltrudis","Ingeluuara","Ingelwara","Ingitrude","Ingoberg","Ingunde","Iodberta","Iolitha","Irmengard","Irmenhild","Irmenlind","Irmgard","Irmingard","Isa","Isburch","Itta","Joveta","Kunegund","Landburuga","Landgarda","Landrada","Lanthechilde","Lanthildis","Lantuuara","Lebdrudis","Leddinga","Leubast","Leubovera","Leuekin","Leuuich","Liaueld","Lidiardis","Liedrada","Liefhun","Lieftet","Lietgarda","Lietgardis","Lietuuif","Lieuuara","Lifgarda","Liobsynde","Liodburga","Liodgard","Liodrada","Litburh","Litgardis","Litiardis","Liutgarde","Luitgarde","Machtildis","Madelgarda","Madelgarde","Madelrada","Madhalberta","Magnatrude","Magthildis","Magtildis","Marcatrude","Marcovefa","Markuuara","Mathildis","Mauriana","Mechtild","Megenberta","Megendrod","Megenhelda","Megenlind","Megenlioba","Megensind","Megensinda","Megenuuara","Meinburg","Meinnelda","Meinsent","Meinswindis","Menborch","Merofled","Merwig","Methdin","Moschia","Murina","Nantechildis","Nidlebis","Nordrada","Oda","Odburga","Odela","Odgiva","Odguda","Odgudana","Odlenda","Odriana","Ogiva","Olburgis","Olga","Osgarda","Osgiua","Otberta","Otgiua","Otgiva","Oydela","Pharahildis","Plectrudis","Radborg","Radburg","Radburgis","Radegund","Radeken","Radgert","Radlia","Radogund","Radsuinda","Ragnachilde","Rainilda","Rainildis","Ramburga","Regana","Regenburuga","Regenelda","Regenlind","Regenset","Reginsuint","Regintrude","Regnetrudis","Regneuuig","Reinewif","Reingard","Reingardis","Reingart","Reingaud","Reingod","Reinsuent","Renburgis","Rennewief","Riberta","Richelda","Richildis","Riclindis","Ricsuinda","Rigunth","Rikildis","Rinelt","Rinilda","Rodburga","Rodgarda","Rodgardae","Rofsind","Rosamund","Rotburga","Rothaide","Rothin","Rotlenda","Rotrud","Rotrude","Rotrudis","Ruodhaid","Ruothild","Ruothilde","Seburg","Seburga","Siborch","Siburg","Sigarda","Sigberta","Sigeberta","Sigeburgis","Sigethrod","Sigiburgis","Snelburch","Stenburch","Stilleuuara","Strilleburg","Suitburgis","Susanna","Swanahilde","Syardis","Teudsindis","Teutberga","Thancuuara","Theaduuara","Thedela","Theodelinda","Theoderada","Theodrada","Theodrade","Theudechild","Theudelinde","Theutberga","Thidela","Thieda","Thietgarda","Thietuuich","Thietwara","Thiodsind","Thiodsuinda","Thiutuuara","Thrasborg","Thrudberga","Ticekin","Tietlenda","Tietza","Trhutborgana","Trudlinde","Trutilda","UUaldburg","UUaldethruda","UUeremund","UUerenburoc","UUiburgis","UUindborog","UUinebarga","UUireda","UUlgarda","Uda","Ultrogotha","Uoldolberta","Veneranda","Vrowecin","Vualdberta","Vualdedruda","Vualdetruda","Vuifken","Vuinetberta","Vuiuechin","Vuldretrada","Vulfegundis","Waldrada","Wavin","Wiburgis","Wihted","Wilberga","Wilgeva","Willelda","Willesuindis","Wisigard","Wivecin","Wivin","Wlbergis","Wlbgis","Wlfildis","Wlgert",
    "ADELAIDE", "AGNES", "ALIENOR", "ANASTASE", "ANASTASIE", "ASTRID", "AUDE", "AURE",
    "Aalis", "Ada", "Adalarde", "Adalasinde", "Adalburge", "Adalinde", "Adalsende", "Adalsinde", "Ade",
    "Adélaïde", "Adelberge", "Adèle", "Adelheit", "Adeline", "Adelsinde", "Adnette", "Adrehilde", "Advise", "Aélais",
    "Aelidis", "Aelis", "Aélith", "Aénor", "Agarde", "Agathe", "Agelberte", "Ageruchia", "Agnoflède", "Aiga", "Aïn",
    "Alaine", "Alaison", "Alaiseta", "Alaizie", "Alarèse", "Alayde", "Alazaïs", "Albérade", "Albereda", "Albérée",
    "Alberte", "Albine", "Alboflède", "Alchima", "Alcima", "Aldeberge", "Aléide", "Aliénor", "Aliète", "Aliote",
    "Alix", "Almodis", "Ameline", "Aneglie", "Ansgarde", "Arambour", "Aremburge", "Arlette", "Asceline",
    "Assalid", "Attala", "Audeburge", "Audefledis", "Audovère", "Aubrée", "Auge", "Austreberthe", "Azelaïs",
    "Barbe", "Balde", "Bathilde", "Bayonne", "Béatrix", "Bénigne", "Berthe", "Betton", "Boussarde", "Brunehaut",
    "Brunissende", "Carensa", "Carétène", "Clervie", "Clotsende", "Clotsinde", "Dangerosa", "Déda", "Dies",
    "Elbore", "Eliette", "Elvide", "Emillane", "Emma", "Erembourg", "Ermelne", "Ermengarde", "Ermenjart",
    "Ermentrude", "Ermesinde", "Etiennette", "Eudoxie", "Eusébie", "Fleur", "Floberte", "Flodoberte",
    "Flor", "Flore", "Foi", "Framehilde", "Franchilde", "Gabrielle", "Gausle", "Gebétrude", "Gerberge",
    "Gerberte", "Gerloc", "Gersinde", "Gillete", "Gillote", "Gisla", "Glossinde", "Gontrade", "Guen",
    "Guillemette", "Guiraude", "Hélits", "Hermine", "Hersent", "Hildegarde", "Huguette", "Hugonette",
    "Hylde", "Ide", "Inde", "Ingonde", "Jutta", "Lampagia", "Léceline", "Leudeberte", "Liutgarde", "Mahaud",
    "Mahaut", "Malorsie", "Marguerite", "Mathe", "Mathie", "Mathilde", "Mechtilde", "Mélie", "Métronie", "Mode",
    "Nantechilde", "Ode", "Odete", "Odile", "Odonette", "Opportune", "Ostrogotho", "Pétronille", "Phébalde",
    "Placidina", "Plectrude", "Poppa", "Praetoria", "Pulcelle", "Ragnachilde", "Régina", "Renaude", "Richilde",
    "Rictrude", "Rixende", "Robresse", "Rodheid", "Rosemonde", "Rothaïde", "Rotrude", "Sanche", "Sancie", "Sara",
    "Sédeleude", "Sénégonde", "Sichède", "Souveraine", "Thelchilde", "Théodechilde", "Théodora", "Théodrade",
    "Théophanie", "Waldrade", "Yolande", "Yselda", "Ysoir",
    "Aalais", "Aliénor", "Alix", "Anthéa", "Aremburge", "Artémise", "Astride", "Aude", "Barbe", "Barberine", "Béatrix",
    "Berthe", "Blanche", "Blancheflor", "Bradamante", "Brunehaut", "Cathau", "Diane", "Ermessende", "Gallendis",
    "Geneviève", "Grisélidis", "Gudule", "Guenièvre", "Hélix", "Héloïse", "Hermeline", "Hersende", "Hildegarde",
    "Iseult", "Léonor", "Letgarde", "Mahaut", "Mélissande", "Mélusine", "Milesende", "Morgane", "Ursule", "Viviane"
};

void CroisadeFranque::GenererPortraits(Humain* /*hum*/, int ageAnnees, QString /*metier*/, QVector<QString>&images)
{
    if ( ageAnnees >= 20 ) {
        if ( ageAnnees <= 40 ) {
            images.push_back(":/images/croisade_franque/portrait_20-40.jpg");
        }
        if ( ageAnnees >= 30 ) {
            images.push_back(":/images/croisade_franque/portrait_30+.jpg");
            if ( ageAnnees >= 50 ) {
                images.push_back(":/images/croisade_franque/portrait_50+.jpg");
                images.push_back(":/images/croisade_franque/portrait_50+_b.jpg");
            }
        }
    }
}

EvtCroisadeFranque::EvtCroisadeFranque(int indexEvt):GenerateurNoeudsProbables (indexEvt)
{
    double tmp_Modificateur = 0.0; //pour les tests (doit être à 0 en prod)
    switch (indexEvt) {
    case 0 : {
        m_Nom = "Conversion en prison";
        m_Description = "???";
        m_ConditionSelecteurProba = make_shared<Condition>(0.1 + tmp_Modificateur, p_Relative);
        m_Conditions.push_back(
             make_shared<Condition>(Crime::C_MOIS_PRISON, "0", Comparateur::c_Superieur));
        m_Conditions.push_back(
             make_shared<Condition>(Coterie::C_COTERIE, Coterie::CROISADE, Comparateur::c_Different));
        m_CallbackDisplay = [] {
            Humain* humain = Humain::GetHumainJoue();
            shared_ptr<Effet> effet = ExecHistoire::GetEffetActuel();

            effet->m_Texte = "Un prêcheur de la croisade franque rend une visite dans votre prison."
                    "\nIl entame de longs discours sur l'honneur, le devoir la force et le sens de la vie et vous appelle à la rédemption en rejoignant les croisés qui s'engagent à vous aider à votre sortie de prison si vous preêtez serment.";

            double proba = Aleatoire::GetAl()->Entre0Et1();
            if ( proba < 0.3 ) {
                humain->GagneCeTrait(honorable, effet);
            }
            proba = Aleatoire::GetAl()->Entre0Et1();
            if ( proba < 0.3 ) {
                humain->PerdCeTrait(sournois, effet);
            }
            proba = Aleatoire::GetAl()->Entre0Et1();
            if ( proba < 0.3 ) {
                Religion::ModifierEffetEnEffetConversion(effet,
                          Religion::CHRETIEN);
            }

            // devient croisé ??
            shared_ptr<Coterie> croisade = Extremis::GetCoterie(Coterie::CROISADE);
            proba = croisade->Compatibilite(humain);
            if ( proba >= Coterie::SEUIL_CONVERSION) {
                croisade->RejoindreCoterie(humain, effet);
            } else
            {
                effet->m_Texte += "\nSes arguments ne vous convainquent pas de le rejoindre.";
            }
        };
    }break;
    case 1 : {
        m_Nom = "Grande cérémonie";
        m_Description = "Vous assistez aux offices de pâques. La cérémonie est si parfaite que vous en êtes très affecté, comme si vous étiez purifié de vos péchés.";
        m_ConditionSelecteurProba = make_shared<Condition>(0.01 + tmp_Modificateur, p_Relative);
        m_Conditions.push_back(Religion::AjouterCondACetteReligion(Religion::CHRETIEN));
        m_CallbackDisplay = [] {
            Humain* hum = Humain::GetHumainJoue();
            shared_ptr<Effet> effet = ExecHistoire::GetEffetActuel();

            effet->m_Son = "qrc:/sons/croisade/hornsofhattinandaftermath.mp3";
            Trait::AjouterGagneTraitSelonProba(hum, effet, altruiste, 0.2);
            Trait::AjouterPerdTraitSelonProba(hum, effet, sournois, 0.2);
            Trait::AjouterPerdTraitSelonProba(hum, effet, jouisseur, 0.2);
            Trait::AjouterPerdTraitSelonProba(hum, effet, cupide, 0.2);
            Trait::AjouterPerdTraitSelonProba(hum, effet, menteur, 0.2);
            Trait::AjouterPerdTraitSelonProba(hum, effet, pervers_sexuel, 0.2);

        };
    }break;
    case 2 : {
        m_Nom = "Don aux pauvres";
        m_Description = "Vous donnez une grande partie de votre argent pour soutenir les pauvres.";
        m_ConditionSelecteurProba = make_shared<Condition>(0.01 + tmp_Modificateur, p_Relative);
        m_Conditions.push_back(Religion::AjouterCondACetteReligion(Religion::CHRETIEN));
        m_Conditions.push_back(Trait::GenConditionSiACeTrait(altruiste));
        m_IncrementeursCaracs[EconomieEvt::C_NIVEAU_ECONOMIQUE] = -2;
        m_Son = "qrc:/sons/croisade/turexgloriae.mp3";
    }break;

    }
}
