#include "cathares.h"
#include "genviehumain.h"
#include "religion/religion.h"
#include "humain.h"
#include "../destinLib/aleatoire.h"
#include "../destinLib/abs/univers.h"
#include "../destinLib/abs/condition.h"
#include "socio_eco/metier.h"
#include "geographie/quartier.h"
#include <QDebug>

using std::make_shared;
using std::shared_ptr;

Cathares::Cathares()
{
    Initialisation();
}

shared_ptr<Quartier> Cathares::GenererQuartier()
{
    m_Quartier = make_shared<Quartier>("Saint Maur des fossés", "Quartier des cathares", "", this);
    Quartier::QUARTIERS[m_Quartier->m_Nom] = m_Quartier;
    return m_Quartier;
}

QString Cathares::GetGentile(bool masculin)
{
    return "cathare";
}

void Cathares::GenererTraitCompatibles()
{
    m_TraitsCompatible = {
        make_shared<Condition>(Trait::GetNomTrait(eTrait::altruiste), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::sens_du_sacrifice), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::sens_du_groupe), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::pacifiste), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::spirituel), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::faible), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Religion::C_FOI, Religion::CHRETIEN, Comparateur::c_Egal )
    };
    m_TraitsIncompatible = {
        make_shared<Condition>(Trait::GetNomTrait(eTrait::cupide), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::industrieux), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::ambitieux), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::violent), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::jouisseur), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::sournois), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::cruel), "1", Comparateur::c_Egal )
    };
    m_MetiersAssocies = {
        Metier::INEMPLOYABLE,
        Metier::PAYSAN,
        Metier::PRETRE
    };
}

QString Cathares::GetMusique()
{
    return "qrc:/sons/cathares/01-21-Symphony_No_9_In_D_Minor_Adagio_Langsam_-LLS.mp3";
}

QString Cathares::GetNom()
{
    return "Cathares";
}

QString Cathares::GetDescription()
{
    return "Description des Cathares";
}

double Cathares::GetPoidsDemo()
{
    return 1.0;
}

QString Cathares::GetDescriptionUniversite()
{
    return "L'université Cathares où vous êtes accueilli est très éloignée du centre de la ville. "
            "Elle se trouve dans un endroit peu industrialisé et entouré d'arbres. L'université elle-même est un majestueux monastère de "
            "pierre mais de toute évidence très peu équipé niveau confort.";
}

QString Cathares::GetImage()
{
    return ":/images/cathares/moine.jpg";
}

std::shared_ptr<Effet> Cathares::AjouterEffetUniversite(GenHistoire* genHist, shared_ptr<Evt> evt, QString go_to_effet_suivant )
{
    QVector<shared_ptr<NoeudProbable>> noeudsProbaEducation;

    // formation religieuse
    {
        shared_ptr<Effet> effet1 = genHist->AjouterEffetNarration(
                    "Rien n'est plus important pour un cathare que la formation religieuse. Vous passez des semaines à écouter les leçons et à suivre les exemples des parfaits.",
                    ":/images/cathares/apprend_lit.jpg",
                    "", evt);
        Religion::ModifierEffetEnEffetConversion(effet1, Religion::CHRETIEN);
        effet1->m_GoToEffetId = go_to_effet_suivant;
        shared_ptr<Condition> cond1 = make_shared<Condition>(1.0, TypeProba::p_Relative);
        shared_ptr<NoeudProbable> noeud1 = make_shared<NoeudProbable>(
                    effet1,
                    cond1);
        noeudsProbaEducation.push_back(noeud1);
    }

    // enfermé en cellule
    {
        shared_ptr<Effet> effetEnferme = genHist->AjouterEffetNarration(
                    "Votre maître estime qu'un mois de privations et de pénitence sera excellent pour renforcer et sauver votre âme. "
                    "Vous êtes enfermé dans une celleule sombre au pain et à l'eau. "
                    "Cette dureté vous affecte cruellement.",
                    ":/images/cathares/apprend_lit.jpg",
                    "", evt);
        Religion::ModifierEffetEnEffetConversion(effetEnferme, Religion::CHRETIEN);
        effetEnferme->m_GoToEffetId = go_to_effet_suivant;
        effetEnferme->m_CallbackDisplay = [] {
            Humain* humain = Humain::GetHumainJoue();
            shared_ptr<Effet> effet = ExecHistoire::GetEffetActuel();
            if ( humain->GetValeurCarac(Trait::GetNomTrait(eTrait::rancunier)) != "" ) {
                effet->m_Texte += "\nCe traitement injuste vous rend furieux. Vous abjurez toute religion.";
                effet->AjouterChangeurDeCarac(Religion::C_RELIGION, Religion::ATHEE);
                effet->AjouterAjouteurACarac(Religion::C_FOI, "0");
            }
            else {
                // 50% de chance de perdre "jouisseur"
                if ( humain->GetValeurCarac(Trait::GetNomTrait(eTrait::jouisseur)) != "" && Aleatoire::GetAl()->Entre0Et1() > 0.5) {
                    humain->SetValeurACaracId(Trait::GetNomTrait(eTrait::jouisseur), "");
                    effet->m_Texte += "\nCe traitement rude est une révélation. Vous renoncez à la concupiscence et perdez la caractéristique 'jouisseur'.";
                }
                // 50% de chance de gagner "resistant"
                if ( humain->GetValeurCarac(Trait::GetNomTrait(eTrait::resistant)) == "" && Aleatoire::GetAl()->Entre0Et1() > 0.5) {
                    humain->SetValeurACaracId(Trait::GetNomTrait(eTrait::resistant), "1");
                    effet->m_Texte += "\nA votre grande surprise votre corps résiste particulièrement bien aux privations. Peut-être que la pureté nouvelle de votre âme vous renforce ? Vous gagnez 'résistant.";
                }
            }
        };
        shared_ptr<Condition> condEnferme = make_shared<Condition>(1.0, TypeProba::p_Relative);
        shared_ptr<NoeudProbable> noeudEnferme = make_shared<NoeudProbable>(
                    effetEnferme,
                    condEnferme);
        noeudsProbaEducation.push_back(noeudEnferme);
    }

    shared_ptr<Effet> effetSelecteur = genHist->m_GenerateurEvt->AjouterEffetSelecteurDEvt(
                noeudsProbaEducation);
    effetSelecteur->m_MsChrono = 1; // passé automatiquement

    return effetSelecteur;
}


QString Cathares::GetId()
{
    return Coterie::CATHARES;
}

QString Cathares::CreerPatronyme(bool masculin)
{
    qDebug()<<"Cathares::CreerPatronyme"<<endl;
    return (masculin?
               Cathares::PRENOMS_M[Aleatoire::GetAl()->EntierInferieurA(PRENOMS_M.size())] +
                        " " + NOMS[Aleatoire::GetAl()->EntierInferieurA(NOMS.size())]:
               Cathares::PRENOMS_F[Aleatoire::GetAl()->EntierInferieurA(PRENOMS_F.size())] +
                       " " + NOMS[Aleatoire::GetAl()->EntierInferieurA(NOMS.size())]
            );
}

QVector<QString> Cathares::PRENOMS_M = {
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

QVector<QString> Cathares::PRENOMS_F = {
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

QVector<QString> Cathares::NOMS = {
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
