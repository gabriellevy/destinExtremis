#include "elfes.h"
#include "genviehumain.h"
#include "socio_eco/metier.h"
#include "../destinLib/aleatoire.h"
#include "../destinLib/abs/condition.h"
#include "humanite/pbsante.h"
#include "geographie/quartier.h"
#include <QDebug>
#include "extremis.h"
#include "humanite/pnj.h"
#include "humain.h"
#include <QtMath>
#include "socio_eco/economieevt.h"
#include "famille/amour.h"

using std::make_shared;
using std::shared_ptr;

Elfes::Elfes()
{
    Initialisation();
}

shared_ptr<Quartier> Elfes::GenererQuartier()
{
    m_Quartier = make_shared<Quartier>("Saint Germain en Laye", "Quartier des Elfes", "", this);
    Extremis::QUARTIERS[m_Quartier->m_Nom] = m_Quartier;
    return m_Quartier;
}

QString Elfes::GetGentile(bool /*masculin*/)
{
    return "elfe";
}

void Elfes::GenererTraitCompatibles()
{
    m_TraitsCompatible = {
        make_shared<Condition>(Trait::GetNomTrait(eTrait::grand), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::beau), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::intelligent), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::sensible), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::habile), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::artiste), "1", Comparateur::c_Egal )
    };
    m_TraitsIncompatible = {
        make_shared<Condition>(Trait::GetNomTrait(eTrait::petit), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::laid), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::simple), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::franc), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::violent), "1", Comparateur::c_Egal ),
        make_shared<Condition>(PbSante::DEFIGURE, "1", Comparateur::c_Egal )
    };
    m_MetiersAssocies = {
        Metier::MUSICIEN,
        Metier::POETE,
        Metier::ALCHIMISTE
    };
}

QString Elfes::GetMusique()
{
    return "qrc:/sons/elfes/5eme.1Sibelius.mp3";
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

double Elfes::GetPoidsDemo()
{
    return 0.4;
}

void Elfes::GenererPortraits(Humain* /*hum*/, int ageAnnees, QString /*metier*/, QVector<QString>&images)
{
    if ( ageAnnees >= 15 ) {
        if ( ageAnnees <= 40 ) {
            images.push_back(":/images/elfes/portrait_15-40_b.jpg");
            images.push_back(":/images/elfes/portrait_15-40_c.jpg");
            images.push_back(":/images/elfes/portrait_15-40_d.jpg");
            if ( ageAnnees < 30 ) {
                images.push_back(":/images/elfes/portrait_15-30.jpg");
            }
        }
        if ( ageAnnees >= 30 ) {
            images.push_back(":/images/elfes/portrait_30+.jpg");
            if ( ageAnnees >= 50 ) {
                images.push_back(":/images/elfes/portrait_50+.jpg");
            }
        }
    }
}

std::shared_ptr<Effet> Elfes::AjouterEffetUniversite(GenHistoire* genHist, shared_ptr<Evt> evt, QString go_to_effet_suivant )
{
    QVector<shared_ptr<NoeudProbable>> noeudsProbaEducation;


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
                    "La beauté est primordiale pour les elfes et ils font en sorte que votre médiocrité ne soit pas un frein pour vous intégrer et vous sentir l'un des leurs. "
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

QString Elfes::CreerPatronyme(bool masculin)
{
    return (masculin?
               Elfes::NOMS_M1[Aleatoire::GetAl()->EntierInferieurA(Elfes::NOMS_M1.size())] +
            Elfes::NOMS_M2[Aleatoire::GetAl()->EntierInferieurA(Elfes::NOMS_M2.size())] +
            Elfes::NOMS_M3[Aleatoire::GetAl()->EntierInferieurA(Elfes::NOMS_M3.size())]:
               Elfes::NOMS_F1[Aleatoire::GetAl()->EntierInferieurA(Elfes::NOMS_F1.size())] +
               Elfes::NOMS_F2[Aleatoire::GetAl()->EntierInferieurA(Elfes::NOMS_F2.size())]
            );
}

QVector<QString> Elfes::NOMS_M1 = {
    "Aba","Ada","Adan","Ado","Adr","Aeg","Ael","Aer","Aes","Afa","Aga","Agi","Aia","Aid","Aie","Ail","Aim","Air","Ait","Aiw","Akk","Ala","Alb",
    "Ald","Ale","Ali","All","Alm","Alo","Alr","Alt","Alw","Am","Amr","And","Anf","Anl","Aol","Aqu","Ara","Aran","Arb","Ard","Arl","Aru","Asc",
    "Ath","Aub","Aum","Avo","Aya","Ayd","Aye","Ayl","Aym","Ayr","Ayw","Bara","Bel","Beleg","Bia","Bra","Cai","Cam","Cas","Celeb","Cha","Che",
    "Clu","Coh","Con","Cor","Curu","Dag","Dai","Dak","Dal","Dar","Del","Dev","Dra","Dru","Dur","Dyf","Edw","Edy","Ehl","Ehr","Eil","Ele","El",
    "Ela","Elb","Eld","Ele","Eli","Elk","Ell","Elm","Elo","Elp","Elr","Elt","Elw","Ely","Emm","Ent","Ere","Erg","Eri","Erl","Ero","Esc","Est",
    "Eth","Ett","Evi","Eyr","Fae","Fal","Fel","Fela","Fen","Fha","Fil","Fin","Fla","Fli","Fol","Fox","Fyl","Gae","Gal","Gan","Gar","Gil","Giu",
    "Gla","Glo","Gol","Gor","Gra","Hae","Hag","Hal","Ham","Har","Has","Hat","Hoc","Hor","Hub","Ief","Iev","Ilb","Ili","Ill","Ilp","Ilr","Ilt",
    "Inc","Ing","Ini","Inj","Int","Iol","Ith","Ivo","Ivl","Ivr","Iym","Iyr","Jan","Jao","Jas","Jha","Jon","Jor","Jos","Jup","Kai","Kat","Kel",
    "Ken","Ker","Kes","Kha","Khi","Khu","Khy","Kie","Kii","Kin","Kiv","Kiy","Kla","Kol","Kuo","Kus","Kym","Kyr","Lae","Laf","Lam","Lao","Lar",
    "Las","Lat","Leo","Lho","Lia","Lin","Lla","Lle","Llo","Lor","Lui","Lut","Luv","Lya","Lyk","Lys","Mae","Mai","Mal","Mar","Mel","Mer","Met",
    "Mha","Mi'","Mih","Mii","Mir","Mla","Mol","Mon","Mor","Myr","Myt","Nae","Nar","Nas","Nav","Nel","Nes","Nev","Nha","Nie","Nin","Nlo","Nop",
    "Nre","Nuv","Nyl","Nym","Nyv","Oac","Oen","Ohm","Ola","Ona","Onc","Onv","Ori","Orl","Orn","Orr","Ory","Osl","Ota","Oth","Pae","Pel","Pen",
    "Pha","Phr","Pir","Ple","Pur","Pyr","Pyw","Qil","Quy","Rae","Rai","Ral","Rat","Rau","Rel","Ren","Rep","Res","Rha","Rhi","Rho","Rhy","Ril",
    "Rol","Rot","Rua","Rue","Rui","Ruv","Ryc","Ryf","Ryo","Ryu","Sae","Sal","Sam","San","Sei","Sel","Sha","Shi","Shy","Sii","Sil","Sim","Sin",
    "Ska","Son","Sor","Sud","Sun","Syl","Sym","Syt","Taa","Tae","Tal","Tam","Tan","Tar","Tas","Tat","Teh","Tei","Tha","The","Thu","Thurin","Tia",
    "Tla","Tol","Tor","Tra","Tri","Ual","Uev","Ul","Uld","Urd","Usu","Uth","Vaa","Vae","Vam","Van","Var","Vel","Ven","Ves","Vir","Vol","Vor","Vud",
    "Vul","Wis","Wyl","Wyn","Wyr","Xal","Xan","Xha","Yal","Yes","Yhe","Yly","Zab","Zal","Zan","Zao","Zel","Zen","Zho","Ab","Ad","Ae","Af","Ag","Ai",
    "Ak","Al","Am","An","Ao","Aq","Ar","As","At","Au","Av","Ay","Be","Bi","Br","Ca","Ch","Cl","Co","Da","De","Dr","Du","Dy","Ed","Eh","Ei","El","Em",
    "En","Er","Es","Et","Ev","Ey","Fa","Fe","Fh","Fi","Fl","Fo","Fy","Ga","Gi","Gl","Go","Gr","Ha","Ho","Hu","Ie","Il","In","Io","It","Iv","Iy","Ja",
    "Jh","Jo","Ju","Ka","Ke","Kh","Ki","Kl","Ko","Ku","Ky","La","Le","Lh","Li","Ll","Lo","Lu","Ly","Ma","Me","Mh","Mi","Ml","Mo","My","Na","Ne","Nh",
    "Ni","Nl","No","Nr","Nu","Ny","Oa","Oe","Oh","Ol","On","Or","Os","Ot","Pa","Pe","Ph","Pi","Pl","Pu","Py","Qi","Qu","Ra","Re","Rh","Ri","Ro","Ru",
    "Ry","Sa","Se","Sh","Si","Sk","So","Su","Sy","Ta","Te","Th","Ti","Tl","To","Tr","Ua","Ue","Ul","Ur","Us","Ut","Va","Ve","Vi","Vo","Vu","Wi","Wy",
    "Xa","Xh","Ya","Ye","Yh","Yl","Za","Ze","Zh"
};

QVector<QString> Elfes::NOMS_M2 = {
    "a","e","o","i","",""
};

QVector<QString> Elfes::NOMS_M3 = {
    "aan","acvar","adan","adavar","ael","aen","aerae","aern","aernth","aeron","aeryn","afarin","aht","air","al","alen","ali","all","aln","alos","am",
    "amar","amede","an","anas","anath","andal","andrach","andrar","ane","angyl","anlar","anor","anthir","aor","ar","arallin","aran","arelar","areth",
    "arion","ark","arre","artael","arth","as","ath","athan","athanil","ather","athiel","authin","auver","bas","beth","blar","bor","born","bryl","bryn",
    "byr","byran","car","cassan","chant","chyr","dacil","damar","dan","dar","ddin","deiym","del","dell","der","devv","dir","dor","drach","dreithen",
    "dro","drol","droth","dual","duin","dusk","dynnar","dyr","e","ed","edd","efehon","eh","ehryn","eisin","el","elar","ele","eliorn","elladon","ellien",
    "en","enal","endar","endil","endyl","enic","enth","er","ern","eron","eros","esin","essin","etheryl","ethuil","evar","fildor","fin","fire","flar",
    "fros","fyndar","gan","gath","gauth","gen","had","haeryn","hai","hais","hal","hallus","haln","hanthar","har","haral","has","hazel","hel","hell",
    "hidon","hild","hilion","hlaeril","hlin","hon","hul","hurach","huryn","ian","ianaro","idiah","iil","ik","ikanthae","ikoth","il","ilan","ilarro",
    "ildyn","im","imar","in","indar","ion","ir","iral","is","isar","itar","ith","ithil","ithor","itran","jym","k","kalr","kyn","l","ladar","laer",
    "lam","lan","lando","lanil","lanis","lar","lareo","las","leas","leath","lethil","levaur","lh","lin","lith","llan","llio","lmar","lor","lseith",
    "lth","lu","luin","lyf","lyn","lyun","m","mar","mashal","mbaerth","mer","mir","mitar","mon","moth","mrail","muth","myn","n","naar","naeril","naeuth",
    "naith","nak","nal","nalor","nar","naran","naril","ndal","ndar","ndaur","ndorn","ndorr","ndriel","nduil","ngyl","nivh","nn","nnatar","nnor","nor",
    "nos","nthorn","nyll","nyn","nyth","o","odar","odas","odemar","oden","odluin","odmer","odmon","odre","odred","oduin","odwin","on","ondiel","ongar",
    "onym","or","orim","orion","orlas","ornik","os","oss","ostroi","othil","otter","par","pen","perr","ph","phal","phant","phar","phon","phor","r",
    "raddyth","rak","ral","rald","ran","randal","randir","randuil","ranthur","ras","rat","rath","rathath","rauth","ravym","rdan","rdh","rdryn","re",
    "red","reiyn","rel","rellan","reth","ri","rian","rik","ril","rin","rindel","rion","ris","rist","rlan","rlion","rm","rmn","rnos","rntym","rod","rom",
    "ron","rond","ros","roth","rphys","rrik","rshin","rshus","rtho","rtlar","ruil","rydal","ryl","ryll","rym","ryn","ryndam","s","saar","sala","san",
    "saran","sarion","shor","sin","son","srin","ssae","st","stan","stel","sx","taar","tagor","tan","tar","tari","tarish","terin","th","thal","thalas",
    "thalion","thalor","tham","thanglas","the","thgor","thil","thir","thomir","thoridan","thorn","tien","tos","uaneth","uar","ueth","ueve","ufan","uigh",
    "uil","uin","umal","undyl","une","unia","urae","uraun","urel","us","uvethel","var","varan","vel","velore","ven","vendor","verel","veril","vhan","vyr",
    "we","wellenar","win","yk","yl","ym","yn","ynn","ynnhv","ynnon","yor","yr","yrd","yrth","yth"
};

QVector<QString> Elfes::NOMS_F2 = {
    "a","adh","adyl","ae","ael","aela","aera","aerae","aestra","aethra","aevar","afain","ah","ahala","ahava","ain","ainn","ais","al","ala","alar","aleth",
    "alla","alue","alurie","alya","alyn","ana","anae","anda","andi","andra","ani","ania","anna","anor","anthae","anthe","ar","ara","arda","aril","arla",
    "arrel","aru","arzah","as","asha","ashta","asta","at","ath","atha","athla","athria","auntha","aya","biyra","ca","cca","cia","dal","dalar","dha","dia",
    "dis","dra","drelle","due","dya","dyl","e","eae","edha","ee","eene","ei","eia","eira","el","ela","ele","elyth","ema","en","ena","endra","ene","enee",
    "enoel","er","era","erae","erele","erina","erla","ern","eru","esca","esra","essa","esse","estri","eth","ethae","fain","farrel","gan","gara","ggan",
    "gil","h","ha","hala","handra","hara","hee","heira","hen","hia","hie","hion","hleene","hn","hnee","honel","hra","hrel","hswana","hyl","hynna","hyrra",
    "i","ia","iah","ian","ianna","iar","ica","ie","iel","ihn","ii","iisa","il","ilue","imnda","in","indra","inn","inne","io","ion","ira","is","isa","issa",
    "italia","itia","ka","l","la","laevar","lahava","lanae","lara","laya","lda","le","lee","leene","lei","leia","lesca","leth","lia","limnda","litia","ll",
    "lla","llee","llyss","lo","los","lossa","lsraa","lue","lurie","lya","lyn","lyntra","lyss","lyth","ma","mara","mbiyra","mna","mrithe","n","na","naestra",
    "nas","nashta","nath","nda","ndi","ndra","ndue","ne","nee","nesra","nestri","ngara","ni","nia","nii","nilue","nna","nne","nnia","noel","nor","ntha",
    "nthae","nthe","nthi","nyn","o","oel","ola","on","ona","onel","onyn","or","ora","orna","oru","ossa","owmoon","r","ra","radh","rae","raen","raethra",
    "ralla","re","reae","rel","rele","relle","ren","reth","ria","rian","riel","rien","ril","rin","rina","rindra","rine","rio","ris","rissa","rithe","rl",
    "rla","rlda","rn","rna","roel","ronel","rra","rria","rtala","rtha","ru","rue","ruil","ryl","ryllia","s","sa","sarda","sha","shnee","sia","sola","sra",
    "sraa","ss","ssa","sse","ssra","sta","star","strae","stria","swana","synora","tala","talia","tarzah","ter","th","tha","thae","thara","thi","thiia","thla",
    "thra","thria","thyl","thynna","ti","tora","trae","tria","trine","ua","ue","uil","uilas","uilos","untha","urel","uria","ustar","uthiia","vel","vren","wais",
    "wen","wing","wmoon","ya","yat","ye","yl","ylla","yllia","ymna","yn","yna","ynor","ynora","yntra","yrl","yrra","yrria","ys","zee"
};

QVector<QString> Elfes::NOMS_F1 = {
    "Adan","Ae","Ael","Aer","Ah","Ahr","Ahs","Ai","Ail","Al","Ala","Ale","All","Alm","Alv","Aly","Am","Ama","Ame","Amk","Aml","Amn","Amr","An","Ana","And",
    "Ane","Anh","Ann","Ar","Ara","Arc","Ari","Arl","Arn","Arr","Art","As","Ash","Au","Aul","Aur","Av","Ava","Ax","Axi","Ay","Ayd","Az","Aza","Be","Bel","Bem",
    "Bl","Bly","Bo","Bon","Br","Bra","Breg","Bu","Bur","Ca","Cae","Cal","Ce","Cel","Celeb","Ch","Cha","Cho","Ci","Cil","Ciy","Cl","Cla","Cr","Cre","Cy","Cyi",
    "Da","Dar","Das","Dat","De","Del","Deu","Dol","Du","Dui","Dur","Ea","Eal","Ec","Eca","Ed","Ede","Edhel","Edr","Ei","Eir","El","Ela","Ele","Eli","Ell","Elm",
    "Elo","Ely","En","Ena","Es","Esh","Ess","Est","Esy","Fa","Fal","Fan","Far","Fau","Fay","Fh","Fha","Fi","Fie","Fil","Find","Ga","Gae","Galadh","Gay","Ge",
    "Gem","Gh","Ghi","Gil","Gl","Gly","Gw","Gwe","Gwy","Gy","Gyl","Ha","Hac","Hal","Ham","Har","He","Hel","Hir","Ho","Hol","Hu","Huq","Hy","Hyc","Ia","Ial",
    "Ik","Ike","Il","Ild","Ilm","Ils","Ily","Im","Imi","Imm","Imr","Io","Ioe","Ior","Ir","Irh","Is","Isi","It","Iti","Ity","Iy","Iyt","Ja","Jas","Je","Jea",
    "Jh","Jha","Jhi","Ka","Kas","Kav","Kay","Ke","Kee","Kei","Ket","Key","Ky","Kyt","La","Laa","Lae","Lal","Laz","Le","Lei","Len","Let","Li","Lie","Lil","Lix",
    "Ll","Lla","Lo","Lor","Lu","Lur","Lus","Ly","Lye","Lyi","Lym","Lyn","Ma","Mae","Mak","Mal","Mar","May","Me","Mei","Mel","Mer","Mi","Mic","Ml","Mla","Mn",
    "Mnu","Mo","Mor","Mu","Mue","My","Myl","Myr","Na","Nab","Nae","Nak","Nam","Nan","Nau","Ne","Nei","Nep","Nex","Ni","Nim","Nit","Nl","Nla","Nu","Nua","Nue",
    "Nuo","Nus","Ny","Nyl","Nyn","Oc","Och","Om","Omy","Os","Oso","Pe","Pen","Ph","Pha","Phe","Phu","Phy","Pyr","Qu","Qua","Ra","Rad","Rae","Ran","Rat","Re",
    "Ren","Ri","Rin","Ro","Rod","Ros","Ru","Rub","Ry","Ryl","SaÃ©","Sa","Sae","Sael","Sai","Sak","San","Sar","Se","Sei","Sel","Sh","Sha","She","Shi","Shy","Si",
    "Sin","So","Sol","Soo","Sor","Sp","Sph","Su","Sum","Sus","Sy","Syl","Sym","Syn","Syv","Ta","Tae","Tai","Tal","Tan","Tar","Te","Teh","Ter","Tet","Th","Tha",
    "Ti","Tia","Tin","Tinu","Tir","Tis","Ts","Tsa","Ui","Uia","Ul","Ule","Um","Umr","Ur","Urm","Us","Usc","Va","Val","Vas","Ve","Vel","Ver","Ves","Vi","Via",
    "Wy","Wyn","Ya","Yae","Yal","Yat","Yg","Ygr","Yn","Yns","Yr","Yrl","Yrn","Yrt","Ys","Ysm","Yu","Yul","Yun","Zo","Zoa"
};

EvtElfes::EvtElfes(int indexEvt):GenerateurNoeudsProbables (indexEvt)
{
    double tmp_Modificateur = 0.0; //pour les tests (doit être à 0 en prod)
    switch (indexEvt) {
    case 0 : {
        m_Nom = "Conversion des malheureux en amour";
        m_Description = "????";
        m_ConditionSelecteurProba = make_shared<Condition>(0.1 + tmp_Modificateur, p_Relative);
        // il est amoureux (malheureux) et en séduction
        m_Conditions.push_back( make_shared<Condition>(
                                    Amour::PRE_LUI_AMOUREUX + Amour::C_ETAT_AMOUREUX_M, Amour::AMOUREUX, Comparateur::c_Egal));
        m_Conditions.push_back( make_shared<Condition>(
                                    Amour::PRE_LUI_AMOUREUX + Amour::C_FAIT_LA_COUR, "1", Comparateur::c_Egal));
        // et pas elfe
        m_Conditions.push_back(
             make_shared<Condition>(Coterie::C_COTERIE, Coterie::ELFES, Comparateur::c_Different));
        m_CallbackDisplay = [] {
            Humain* humain = Humain::GetHumainJoue();
            shared_ptr<Effet> effet = ExecHistoire::GetEffetActuel();
            effet->m_Texte = "Plus le temps passe dans vos échecs en séduction plus vous vous dites que ce serait quand même bien plus simple si vous étiez un elfe beau, grand et poète.";
            // devient elfe ??
            shared_ptr<Coterie> cot = Extremis::GetCoterie(Coterie::ELFES);

            double proba = Aleatoire::GetAl()->Entre0Et1();
            if ( proba < 0.3 ) {
                humain->GagneCeTrait(angoisse, effet);
            }
            proba = Aleatoire::GetAl()->Entre0Et1();
            if ( proba < 0.3 ) {
                humain->GagneCeTrait(rancunier, effet);
            }

            proba = cot->Compatibilite(humain);
            if ( proba >= Coterie::SEUIL_CONVERSION) {
                cot->RejoindreCoterie(humain, effet);
            } else {
                proba = Aleatoire::GetAl()->Entre0Et1();
                if ( proba < 0.3 ) {
                    humain->GagneCeTrait(opportuniste, effet);
                }
            }
        };
    }break;
    }
}
