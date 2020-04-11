#include "tyranides.h"
#include "genviehumain.h"
#include "../destinLib/aleatoire.h"
#include "../destinLib/abs/condition.h"
#include "socio_eco/metier.h"
#include "geographie/quartier.h"

using std::make_shared;
using std::shared_ptr;

Tyranides::Tyranides()
{
    Initialisation();
}

shared_ptr<Quartier> Tyranides::GenererQuartier()
{
    m_Quartier = make_shared<Quartier>("Saint Ouen", "Quartier des Tyranides", "", this);
    Quartier::QUARTIERS[m_Quartier->m_Nom] = m_Quartier;
    return m_Quartier;
}

void Tyranides::GenererTraitCompatibles()
{
    m_TraitsCompatible = {
        make_shared<Condition>(Trait::GetNomTrait(eTrait::sens_du_groupe), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::sournois), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::charmeur), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::spirituel), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::sens_du_sacrifice), "1", Comparateur::c_Egal )
    };
    m_TraitsIncompatible = {
        make_shared<Condition>(Trait::GetNomTrait(eTrait::honorable), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::franc), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::sensible), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::angoisse), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::artiste), "1", Comparateur::c_Egal )
    };
    m_MetiersAssocies = {
        Metier::MINEUR,
        Metier::OUVRIER,
        Metier::POLITIQUE
    };
}

QString Tyranides::GetNom()
{
    return "Tyranides";
}

double Tyranides::GetPoidsDemo()
{
    return 1.0;
}

QString Tyranides::GetDescription()
{
    return "Description des Tyranides";
}

QString Tyranides::GetDescriptionUniversite()
{
    return "Les Tyranides";
}

QString Tyranides::GetImage()
{
    return ":/images/tyranides/The_hive_fleets_descend.jpg";
}

QString Tyranides::GetId()
{
    return Coterie::TYRANIDES;
}

std::shared_ptr<Effet> Tyranides::AjouterEffetUniversite(GenHistoire* genHist, shared_ptr<Evt> evt, QString go_to_effet_suivant )
{
    QVector<shared_ptr<NoeudProbable>> noeudsProbaEducation;

    shared_ptr<Effet> effet2 = genHist->AjouterEffetNarration("youpi temp " + GetNom() + " 0.8", "", "", evt);
    effet2->m_GoToEffetId = go_to_effet_suivant;
    shared_ptr<Condition> cond = make_shared<Condition>(0.8, TypeProba::p_Relative);
    shared_ptr<NoeudProbable> noeud = make_shared<NoeudProbable>(
                effet2,
                cond);
    noeudsProbaEducation.push_back(noeud);

    shared_ptr<Effet> effetSelecteur = genHist->m_GenerateurEvt->AjouterEffetSelecteurDEvt(
                noeudsProbaEducation);
    effetSelecteur->m_MsChrono = 1; // passé automatiquement

    return effetSelecteur;
}

QString Tyranides::CreerPatronyme(bool masculin)
{
    return (masculin?
               Tyranides::NOMS_M[Aleatoire::GetAl()->EntierInferieurA(Tyranides::NOMS_M.size())]:
               Tyranides::NOMS_F[Aleatoire::GetAl()->EntierInferieurA(Tyranides::NOMS_M.size())]
            );
}

QVector<QString> Tyranides::NOMS_M = {
    "Aadam","Aadeynag","Aali","Aalmaas","Adham","Allayaar","Armaan","Baahout","Baalaach","Baaraan","Baarag","Bahraam","Bandag","Bashshaam","Behrouz",
    "Behzaad","Bibagr","Bohaador","Bouheyr","Braanz","Chaakar","Chaarshambeh","Cheraag","Delaawar","Deleyr","Dellshaad","Didag","Doudaa","Dousteyn",
    "Gaazi","Gamshaad","Gazzi","Gishshar","Gwahraam","Haameyn","Hammal","Hammbal","Hayaat","Haybat","Horsond","Jaafar","Jalab","Jehaangir","Jiyand",
    "Joma","Kamaal","Kambar","Mallouk","Mayaar","Mirdoust","Mirzaad","Omeyd","Oumaan","Rahmat","Rayhaan","Roushen","Rozhn","Sabzal","Sayaad","Sekandar",
    "Shaadaan","Shaadmaan","Shahdoust","Shahmir","Shakkal","Shamsheyr","Shanbeh","Sharif","Sheyrdel","Soubaan","Zangi","Aadeyna","Aadeynag","Aazaat",
    "Aaskaan","Aaskalok","Aashoor","Aala","Aali","Aaherdad","Aahorran","Aawar","Aachaar","Armaan","Ashkaan","Allok","Almaas","Allayaar","Amaan",
    "Ahltaaz","Oustan","Oumaan","Omytaan","Omyt","Omyt","Omyd","Baaeiyaan","Baboo","Baabul","Baaraan","Baaro","Baarak","Baazo","Baalaach","Baamei",
    "Baahar","Baahot'","Baahar'","Braanz","Braahumdaq","Brahundag","Braaho","Braahym","Barkat","Bashir","Bejjaar","Balbaas","Baloch","Bandig",
    "Bandeig","Bahaadurr","Bahaar","Bahtyaar","Bahraam","Botaar","Borjaan","Bolaan","Bouheyr","Bashshaam","Bashshaan","Bat'Yhan","Bandag","Bangul",
    "Bangol","Bat'Y","Bullei","Bullo","Beibarg","Bibagr","Byr","Beizan","Beiwarq","Byr'Aahaan","Bygal","Taajoo","Jaanuo","Jaar'O","Jaar'Yn","Jalluo",
    "Jalaal","Jalaaii","Jangeyaan","Jehanzyb","Jwaansaal","Jopaak","Jalab","Jawhar","Juma","Jehel","Jeeyaa","Daadshaah","Daaduo","Daadul","Daadyn",
    "Darbysh","Dramshok","Durgosh","Delaawar","Delbod","Deljaan","Dellshaad","Delmraad","Delwashsh","Delpull","Deleyr","Doudaa","Dorrukk","Dostuk",
    "Dousteyn","Durraa","Doshok","Delok","Dinaar","Raajo","Raamyn","Raahi","Razaa","Razok","Rahchaar","Rodyn","Rodi","Rostom","Roshen","Rohaan","Raz",
    "Rashid","Ramagi","Ramok","Rami","Ragaam","Rago","Rayhaan","Rozhn","Reihaan","Rekhi","Rynko","Rynki","Rynk","Zabardast","Zamaan","Zangi","Zahro",
    "Zahri","Zahmi","Zirrok","Sawluk","Saalaar","Saalmei","Saaluk","Saahi","Sabzal","Sardaar","Sarmachaar","Samandar","Sammo","Sobaan","Sohaw","Sopuk",
    "Sawl","Saparhaan","Sapar","Sanjaraan","Sanjar","Sangat","Sahaak","Sohbathaan","Sumaal","Suhraab","Suhrag","Suhyl","Spaahi","Sakandar","Sagaar",
    "Syaaho","Syaahar'","Syaahuk","Syahpad","Shabaan","Shaadaan","Shaadmaan","Shaashaan","Shaahdost","Shaahed","Shaahal","Shaahnor","Shaaho","Shaahuk",
    "Shaahija","Shaahi","Shaahjhaan","Sharbat","Shawkat","Shakkal","Shambeh","Shams","Shamsheyr","Shanbeh","Shandok","Shandi","Shahbaaz","Shahzaanz",
    "Shahbik","Shahjhaan","Shahdaad","Shahdoust","Shahdorr","Shahdok","Shahzor","Shahsawaar","Shahmoraad","Shahmir","Shahnoor","Shahgol","Shoro",
    "Shohaaz","Shambo","Shapi","Shakar","Shyraan","Shyraan","Shyrjaan","Shyrjaan","Sheyrdel","Shyrshaad","Shyrshekaar","Shyro","Shyr","Shayhaan",
    "Shyhak","Shywaar","Lashaar","Laalbashk","Laalbaksh","Laalbyk","Laalhan","Laagar","Laagaruk","Labaab","Lashkarhan","Lashkari","Lashkar","Lalla",
    "Lahdaat","Lahdaad","Lawaar","Mubaarak","Meraad","Murid","Mazaaraan","Mazaari","Mazaar","Mesaaper","Meskaan","Madat","Mur'Aa","Mandost","Mando",
    "Mehraab","Mehrdel","Muhim","Majolei","Malang","Malek","Mandalei","Maymich","Meiyaahaan","Meiyaa","Mayaar","Meiraaji","Meiraan","Meirbaal","Meirdel",
    "Meirzaad","Meirzaa","Meiral","Meiro","Meirkaa","Miryn","Mingal","Naader","Naaro","Nalo","Naande","Naakaam","Naagumaan","Nato","Nande","Nehaalaan",
    "Nawbat","Nawbathaan","Nodbandag","Noraan","Noraa","Norbaksh","Norjaan","Nawroz","Nori","Nosharwaan","Noshar","Nohaan","Negbaht","Neyaaz","Neyaazhaan",
    "Haalaa","Haamyn","Haandaad","Hudaabashk","Hudaabaksh","Hudaadaad","Hudaayaar","Hazaarhaan","Hasto","Huzhyaar","Hambal","Hamdard","Hamdam","Hammal",
    "Hot","Hoshaam","Halil","Hawza","Hayaat","Haybataan","Haybat","Hayrbaksh","Hayrbeyaar","Hayrbyr","Hayfo","Waaja","Waahund","Warnaa","Warrod","Wazir",
    "Washdel","Washnaam","Wazbat","Wazhdel","Wazhnaam","Pahrei","Pahlawaan","Polaat","Pasund","Pordel","Chaarshambeh","Chaaruog","Chaarok","Chaawosh",
    "Chaakar","Cheraag","Challei","Chamrok","Chamal","Chegerd","Kaado","Kaari","Kaat'Aar","Kaar'Uk","Kajir","Karaa","Karych","Kasuor","Karam","Kalmat",
    "Kalyrei","Kalyr","Kambar","Kanbar","Kachkol","Kazhzhok","Kolmeir","Kulei","Kunari","Kunar","Kamaal","Kungur","Kahuor","Kaheiri","Kotuwaal",
    "Kont'Or","Konar'","Kohi","Kohprosh","Kot'Uwaal","Kot'Or","Kehraa","Keiyaa","Kynagi","Kihaa","Ezzat","Kihar","Gaajeyaan","Gaalei","Gurgyj","Garri",
    "Gazaabyk","Gazzo","Gazyn","Gazi","Gamdaad","Gami","Gurki","Gurk","Gulaam","Gulzaat","Gulhaan","Gamshaad","Ganguzaar","Ganguo","Gorshaan","Gorich",
    "Gosho","Gwahraam","Gyhal","Geishshtari","Geishshar","Yaarjaan","Yalyn","Yakshamby",
    "Äðhäm","Äğlämetdin","Äkhmät","Äkrämetdin","Ämir","Ämirkhan","Änüär","Änwär","Äxkäm","Äxmät","Äxmätzäki","Ğäbiz̦Ulla","Ğäli","Ğälim","Ğälimyän",
    "Ğäziz","Ğöbäyðulla","Ğöbäyz̦Ulla","Ğümär","Ğaysa","Ğilemdar","Şähit","Şärif","Ağiðel","Afzaletdin","Airat","Almas","Altynbay","Anuar","Aryşlan",
    "Ayðar","Aybulat","Aydar","Aygiz","Ayrat","Azamat","Bäğiz","Büre","Bariy","Bayğötdin","Bikbulat","Borxan","Bulat","Dawït","Dawit","Dayan","Dim",
    "Dinislam","Färit","Fäyzulla","Fazulla","Gäwhär","Gotbetdin","Haz̦Iy","Husayn","Ibrahim","Ilyas","Irändek","Irek","Iskändär","Islamğäli","Islambäk",
    "Islametdin","Iz̦El","Kamaletdin","Khamza","Khasan","Mäjit","Mäxmüt","Möxämätğäbdelxäy","Möxämmätša","Möxämmät","Marvan","Minhažetdin","Mintimer",
    "Mirgayaz","Mirxäyz̦Är","Mortaz̦A","Muşarif","Muhammad","Mullayän","Musa","Näžip","Nögöş","Nagim","Niğmät","Niğmättulla","Niğmätulla","Nil","Räşit",
    "Rämil","Räsül","Räwef","Röstäm","Ramaz̦An","Rišat","Rif","Rifqät","Rinat","Ruslan","Säğit","Sälimä","Sälim","Säyet","Sïñğïð","Söläymän","Sabir",
    "Sabit","Salawat","Sayed","Shäyxislam","Shaikhzada","Siñğiz̦","Tälğät","Tölkö","Tagir","Talğat","Talxa","Tashtemir","Tayfur","Taymaç","Tufan",
    "Tulqyn","Ural","Uyïldan","Uyildan","Växit","Vener","Vildan","Xäbibulla","Xäbir","Xämzä","Xäsän","Xäydär","Xösäyen","Xoz̦Aybirgän","Yähüz̦Ä",
    "Yämil","Yäwðät","Yäwz̦Ät","Yahya","Yakhya","Yaqup","Yaxya","Yomabay","Yosop","Yulay","Yusuf","Zäki","Zäkiryän","Zäynulla","Zöfär","Zagir","Zahir"
};

QVector<QString> Tyranides::NOMS_F = {
    "Aarezou","Ambar","Bahtaawar","Darmaan","Dorbibi","Dorhaatun","Dornaaz","Dranna","Emaan","Eymen","Aask","Kimat","Kygad","Ezzat","Aahoog","Washrang",
    "Raaji","Razaan","Namer","Washshek","Pollyn","Panyr","Washpull","Geraanaaz","Chaahik","Chaahi","Raazyn","Nodi","Noraatuon","Naago","Ganji","Gawhar",
    "Chandan","Naazaatuon","Naazbaano","Gulderr","Guldym","Gul","Gulaauon","Kaawak","Naazbaanuk","Naazbo","Gulbaano","Gulpari","Guli","Gulbo","Nourjhaan",
    "Gwaar'Ag","Ganjaatuon","Noras","Kalampor","Kunnal","Gesed","Normalek","Naazul","Katuor","Kapot","Nykaatuon","Waahag","Haatuon","Haatyn","Haanul",
    "Haangul","Haani","Ngaar","Kezmat","Naazuk","Naazpari","Hazaari","Hazzaam","Hawraan","Hawrei","Henaar","Hangour","Naazgul","Naazyn","Naazei","Hayri",
    "Rozaatoon","Laal","Laalyn","Raabya","Aasmei","Ganjhaatun","Lakki","Bahtei","Bezerg","Muraadi","Shaarei","Sharrang","Maahaatuon","Maahaan","Maahtos",
    "Maahdost","Muluok","Maahrang","Maahal","Maduok","Maduk","Murwaared","Mahrang","Maahpari","Morti","Mawri","Mahlunj","Mahnaaz","Mulkaan","Mitaap","Mulki",
    "Mehri","Mahnaa","Madyr","Mayruk","Malok","Mahnuor","Mahpari","Mahger","Mahgul","Mahganj","Mahgend","Mahgonag","Maahkaan","Maahgul","Mahbaano","Mahtaab",
    "Mahtaap","Mahtos","Mahdost","Mahdym","Maahyn","Maaheig","Maahi","Maapari","Sharhaatun","Shali","Shaazyn","Beibo","Shemshok","Shaahpari","Beibok",
    "Shamsaatoon","Shamsi","Shahbaanuk","Armaan","Gawhar","Blor","Golandaam","Jaangul","Jaani","Jato","Shahpari","Zaamoraan","Sharbano","Zaamor","Zaaporaan",
    "Shahnaaz","Zebaad","Jaar'Uk","Zaraatoon","Zarbaano","Saara","Saarag","Shaatul","Shaato","Zinat","Zarbaanuk","Zarbaht","Zomorrod","Zohra","Zybuk","Samyn",
    "Sahto","Sawli","Sahtei","Sanji","Zaytoun","Sammi","Sabzi","Sadap","Sapora","Saddo","Sadganj","Sadok","Zirrag","Zarjaan","Zarmalek","Zarnaaz","Zarhaatoon",
    "Zarpoll","Zarok","Zargul","Zari","Golbaanu","Tajatoon","Taajei","Jawri","Jaanol","Golhaatun","Ambar","Amoll","Golmalek","Golpari","Graannaaz","Haani",
    "Daanichk","Durbaano","Durbibi","Haatun","Durmalek","Durnaaz","Delbar","Deldost","Delband","Dranna","Durhaatuon","Durdap","Dorrchamm","Durrdn","Naani",
    "Jannat","Durras","Durraatuon","Maahaan","Maahaatun","Maahekaan","Ezbotk","Ezgend","Eyman","Eymen","Maaheyn","Mahbaanu","Mahbibi","Mahganj","Baanalei",
    "Baanal","Baanul","Baanuk","Berenjaask","Mahgol","Mahjabin","Mahnaaz","Bahtbibi","Mahnur","Mahrang","Mahtaab","Bahtaawar","Bahtgul","Mehlab","Morwaared",
    "Naazbibi","Naazhaatun","Naazmalek","Parigol","Parinaaz","Sadaaf","Sadaf","Sanji","Sharhaatun","Shemshok","Waahag","Zaaferaan","Zarhaatun","Zaytun","Zinat","Zomorred",
    "Älfiä","Äliä","Äminä","Änisä","Äyšä","Ümmöxäbibä","Ğäyšä","Šäwrä","Aigöl","Albinä","Almabikä","Asiä","Asiya","Aybikä","Aygöl","Bäkirä","Bäz̦Är","Banıŵ",
    "Banat","Baniw","Bayrambikä","Bibi","Elvirä","Emeşbikä","Fänünä","Färiz̦Ä","Fatima","Firüzä","Flyura","Gäwhär","Gölbanïw","Gölsinä","Güzäl","Güzäliä","Hädiä",
    "Jamila","Läysän","Laysan","Liliä","Mäðinä","Mädinä","Märyäm","Mäymünä","Menäwrä","Miläwşä","Miläwšä","Muyylbikä","Näžibä","Närkäs","Rämilä","Rämzilä",
    "Räyxana","Reyhane","Rezeda","Rezida","Säüdä","Säbilä","Säkinä","Sälimä","Säriä","Säyäbikä","Sabira","Saniya","Sara","Shäwrä","Sulpan","Tañhïlïw","Tañhiliw",
    "Xäz̦Isä","Xafasa","Yämilä","Yüväyriä","Yomabikä","Zäbirä","Zäynäb","Zäynäp","Zäytünä","Zöhrä","Zöläykha","Zöläyxä","Zöläyxa","Zölfiä","Zölxizä","Zamira",
    "Zemfíra","Zemfira","Zeyneb","Zifa","Ziliä","Zulaikha","Zulfiya"
};


