#include "celte.h"
#include "genviehumain.h"
#include "socio_eco/metier.h"
#include "../destinLib/aleatoire.h"
#include "../destinLib/abs/condition.h"
#include "geographie/quartier.h"

using std::make_shared;
using std::shared_ptr;

Celte::Celte()
{
    Initialisation();
}

shared_ptr<Quartier> Celte::GenererQuartier()
{
    m_Quartier = make_shared<Quartier>("Fontainebleau", "Quartier des Celtes", "", this);
    Quartier::QUARTIERS[m_Quartier->m_Nom] = m_Quartier;
    return m_Quartier;
}

QString Celte::GetGentile(bool masculin)
{
    return "celte";
}

void Celte::GenererTraitCompatibles()
{
    m_TraitsCompatible = {
        make_shared<Condition>(Trait::GetNomTrait(eTrait::nature), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::honorable), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::franc), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::spirituel), "1", Comparateur::c_Egal )
    };
    m_TraitsIncompatible = {
        make_shared<Condition>(Trait::GetNomTrait(eTrait::industrieux), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::intellectuel), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::pacifiste), "1", Comparateur::c_Egal ),
        make_shared<Condition>(Trait::GetNomTrait(eTrait::maladroit), "1", Comparateur::c_Egal )
    };
    m_MetiersAssocies = {
        Metier::ALCHIMISTE,
        Metier::PAYSAN,
        Metier::PRETRE
    };
}

QString Celte::GetMusique()
{
    return "qrc:/sons/celtes/01-06-Lemminkainen_Suite_Op_22_IV_Lemminkainen-LLS.mp3";
}

QString Celte::GetDescription()
{
    return "Description des celtes";
}

QString Celte::GetNom()
{
    return "Celtes";
}

QString Celte::GetDescriptionUniversite()
{
    return "Les celtes";
}

QString Celte::GetImage()
{
    return ":/images/celtes/description.jpg";
}

double Celte::GetPoidsDemo()
{
    return 1.3f;
}

QString Celte::GetId()
{
    return Coterie::CELTES;
}

std::shared_ptr<Effet> Celte::AjouterEffetUniversite(GenHistoire* genHist, shared_ptr<Evt> evt, QString go_to_effet_suivant )
{
    QVector<shared_ptr<NoeudProbable>> noeudsProbaEducation;

    {
        shared_ptr<Effet> effet2 = genHist->AjouterEffetNarration("youpi temp " + GetNom() + " 0.8", "", "", evt);
        effet2->m_GoToEffetId = go_to_effet_suivant;
        shared_ptr<Condition> cond = make_shared<Condition>(0.8, TypeProba::p_Relative);
        shared_ptr<NoeudProbable> noeud = make_shared<NoeudProbable>(
                    effet2,
                    cond);
        noeudsProbaEducation.push_back(noeud);
    }

    // effet devient Alchimiste
    {
        shared_ptr<Effet> effet = genHist->AjouterEffetNarration(
                    "La fabrication de potions, de filtres, de pommades est une composante essentielle de la science des druides celtes. "
                    "Leurs usages sont innombrables et vont de potions de soins aux champignons rendant les guerriers insensibles à la peur et la douleur. "
                    "Un druide détecte un certain potentiel chez vous et décide de vous apprendre les bases.",
                    ":/images/elfes/alchimiste.jpg",
                    "", evt);
        effet->m_GoToEffetId = go_to_effet_suivant;
        effet->AjouterAjouteurACarac(Metier::ALCHIMISTE, "1");
        Trait::AjouterConditionSiAPasCeTrait(effet, bete);

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


QString Celte::CreerPatronyme(bool masculin)
{
    return (masculin?
               Celte::PRENOMS_M[Aleatoire::GetAl()->EntierInferieurA(Celte::PRENOMS_M.size())] + " " + Celte::NOMS_M[Aleatoire::GetAl()->EntierInferieurA(Celte::NOMS_M.size())]:
               Celte::PRENOMS_F[Aleatoire::GetAl()->EntierInferieurA(Celte::PRENOMS_F.size())] + " " + Celte::NOMS_F[Aleatoire::GetAl()->EntierInferieurA(Celte::NOMS_F.size())]
            );
}

QVector<QString> Celte::PRENOMS_F = {
    "Áilís","Áilísh","Áine","Álmath","Éabha","Éadaoin","Éibhleann","Éile","Éimhear","Émer","Érne","Étaín","Étain","Órfhlaith","Órla","Órlaith","Órnait","Órnat","Úna","Aíbell",
    "Aíbhinn","Abaigeal","Abhlach","Achall","Affraic","Agata","Aghna","Aibhilín","Aifric","Aigneis","Ailbhe","Ailionóra","Ailis","Ailish","Ailleann","Ainfean","Ainnir","Aislin",
    "Aisling","Aislinn","Aithche","Alistriona","Almha","Ana","Annábla","Aobhnait","Aodhamair","Aodhnait","Aoibhe","Aoibheann","Aoibhgreine","Aoibhin","Aoibhinn","Aoife",
    "Athracht","Báine","Bébhinn","Béibhinn","Bóinn","Baillgheal","Bairbre","Bairrionn","Banbha","Banbhnait","Barrdhubh","Bearrach","Bethaill","Bigseach","Blánaid","Bláth",
    "Bláthnaid","Bláthnat","Blaine","Blinne","Brídín","Bríd","Brígh","Brónach","Briana","Brighdín","Brighid","Brigit","Briuinseach","Buadhnait","Buanait","Buanann","Céibhionn",
    "Cúach","Cúachnait","Caíreach","Cacht","Cainnear","Cainnech","Cainnleach","Caireann","Cairrean","Caitlín","Caitlin","Caitrín","Caitríona","Caitriona","Caoilfhionn",
    "Caoilinn","Caoimhe","Caoimhinn","Caoimseach","Caointiarn","Caomhnait","Caomhog","Cathach","Catríona","Catraoine","Ceallach","Ceallsach","Ceara","Ciamhnait","Ciannait",
    "Ciar","Ciara","Ciarnait","Clídna","Clíona","Cliodhna","Clodagh","Clothra","Cobhfhlaith","Cobhlaith","Cochrann","Comnait","Corcair","Créd","Crínóc","Cróchnait","Crón",
    "Crónsech","Cranait","Craobhnait","Cristin","Cristiona","Cruimseach","Curchach","Dáire","Dáireen","Dáirine","Dúinseach","Dúnlaith","Daghain","Dairile","Dairinn",
    "Damhnait","Daróma","Darearca","Dealla","Dearbháil","Dearbhfhorgaill","Dearbhfhorghaill","Dearbhla","Dearbhorgaill","Dearlú","Deidre","Deirbhile","Deirdre","Derbail",
    "Dianaimh","Doireann","Draigen","Dubhóg","Dubhchobhlaigh","Duibheasa","Duibhleamhna","Dunla","Dymphna","Eórann","Eachna","Eachra","Eachtach","Ealga","Earcnait","Earnait",
    "Eavan","Eavnat","Eeada","Eibhlín","Eibhlin","Eilín","Eilís","Eilísh","Eilis","Eilise","Eilish","Eimear","Eimer","Eimhear","Eimile","Eirnín","Eistir","Eithne","Elan",
    "Escrach","Etaoin","Ethna","Féthnaid","Féthnat","Fíneamhain","Fínola","Fínscoth","Fíona","Faílenn","Faife","Fainche","Fainnear","Faoileann","Faoiltighearna","Feamair",
    "Feidhelm","Feme","Fennore","Fiadhnait","Fial","Fianait","Finnabair","Finncháem","Finnchnes","Finneacht","Finnech","Finnseach","Fiona","Fionnghuala","Fionnuala",
    "Fionnuir","Fithir","Flann","Flannait","Flidais","Fodhla","Fodla","Forbhlaith","Forlaith","Geiléis","Gelace","Gobnait","Gormfhlaith","Gormlaith","Gráinne","Grania",
    "Grian","Ida","Ierne","Ina","Iodhnait","Ionait","Isibéal","Iuchra","Láimhseach","Líadan","Líoch","Lúgach","Laithche","Lann","Laoiseach","Lasairíona","Lasair",
    "Lasairfhíona","Lavarcham","Leenane","Loimseach","Loughlin","Luíseach","Luighseach","Lysagh","Máen","Máiréad","Máirín","Máire","Míde","Míonait","Móirín","Móirne",
    "Mór","Macha","Maeve","Maille","Mailse","Mailte","Mairéad","Mairghréad","Mairin","Mairona","Mairsil","Maiti","Maleia","Mallaidh","Maol","Meabh","Meadhbh","Meaghan",
    "Mealla","Meibhín","Meidhbhín","Miodhnait","Moina","Moira","Moirin","Monat","Moncha","Monghnd","Morrin","Muadhnait","Mugain","Mughain","Muirín","Muireacht","Muireann",
    "Muirgel","Muirgheal","Muirinn","Muirne","Nárbhla","Nóirín","Nóra","Neacht","Neamhain","Niamh","Niav","Noirin","Nuala","Odharnait","Onóra","Oonagh","Osnait","Pádraigin",
    "Peigín","Peig","Peigi","Proinnseas","Ráichéal","Ríofach","Ríoghnach","Ríona","Ríonach","Róinseach","Róisín","Róis","Róise","Rónait","Rós","Rúadhnait","Raghnailt",
    "Rathnait","Riona","Sárnait","Séadach","Séanait","Síle","Síne","Síthmaith","Síve","Sadb","Sadhbh","Samhaoir","Samthann","Saoirse","Saorfhlaith","Saorla","Saorlaith",
    "Saraid","Scáthach","Sciath","Scoth","Searc","Searlait","Seosaimhin","Sibéal","Sinéad","Siobhán","Sláine","Sláne","Slany","Sorcha","Souhaun","Suaibhseach","Suanach",
    "Téide","Taillte","Teafa","Teamhair","Tiarnan","Tierney","Tuathflaith","Tuathla","Tuathlaith","Tuileach","Tuilelaith","Uaine","Uallach","Uasal"
};
QVector<QString> Celte::NOMS_F = {
    "Mhic Ámoinn","Mhic Éanraic","Mhic Íomhair","Mhic Adaim","Mhic Ailin","Mhic Airt","Mhic Alasdair","Mhic Amhlaidh","Mhic Amhlaoibh","Mhic Aodha","Mhic Aodhagáin",
    "Mhic Aoidh","Mhic Aonghuis","Mhic Aonghusa","Mhic Ardghail","Mhic Artair","Mhic Asgaill","Mhic Ausaláin","Mhic Bhiadhtaigh","Mhic Bhloscaidh","Mhic Braoin",
    "Mhic Braonáin","Mhic Cába","Mhic Cárthaigh","Mhic Céile","Mhic Céileachair","Mhic Céin","Mhic Céirín","Mhic Céitinn","Mhic Cómhaltáin","Mhic Cú Uladh","Mhic Cúg",
    "Mhic Cadhla","Mhic Cahan","Mhic Cailin","Mhic Cairbre","Mhic Cairealláin","Mhic Caiside","Mhic Canáin","Mhic Cana","Mhic Canannáin","Mhic Canann","Mhic Caocháin",
    "Mhic Caoimh","Mhic Caoindealbháin","Mhic Caoinnigh","Mhic Caollaidhe","Mhic Caomháin","Mhic Carra","Mhic Carrghamhna","Mhic Cartaine","Mhic Catháin","Mhic Cathail",
    "Mhic Cathaláin","Mhic Cathal","Mhic Cathasaigh","Mhic Cathmhaoil","Mhic Ceallacháin","Mhic Ceallaigh","Mhic Ceanndubháin","Mhic Cearáin","Mhic Cearbhaigh",
    "Mhic Cearbhaill","Mhic Cearbhalláin","Mhic Cearnacháin","Mhic Cearnaigh","Mhic Cearncháin","Mhic Cianáin","Mhic Cianaigh","Mhic Ciaráin","Mhic Ciaragáin",
    "Mhic Ciardha","Mhic Cillín","Mhic Cinnéide","Mhic Cinnseallaigh","Mhic Cionaodha","Mhic Cionnaith","Mhic Cionnfhaolaidh","Mhic Ciosáin","Mhic Cléirigh",
    "Mhic Cluanaigh","Mhic Cluasaigh","Mhic Cnáimhsí","Mhic Cnaimhín","Mhic Cobhthaigh","Mhic Cogadháin","Mhic Coigligh","Mhic Coilín","Mhic Coileáin",
    "Mhic Coinnich","Mhic Coinnigh","Mhic Coitir","Mhic Colgáin","Mhic Colla","Mhic Coluim","Mhic Comhraidhe","Mhic Con Coille","Mhic Con Fhiacla","Mhic Con Mhaighe",
    "Mhic Con Uladh","Mhic Conaill","Mhic Conaing","Mhic Conaire","Mhic Conalláin","Mhic Conaráin","Mhic Conbhuide","Mhic Conchúir","Mhic Conchobhair","Mhic Conduibh",
    "Mhic Conghaile","Mhic Conmara","Mhic Conmidhe","Mhic Connacháin","Mhic Connagáin","Mhic Connmhaigh","Mhic Conradh","Mhic Conraoi","Mhic Consaidín","Mhic Conshámha",
    "Mhic Corbáin","Mhic Corcáin","Mhic Cormaic","Mhic Cornghaile","Mhic Corráin","Mhic Corra","Mhic Corragáin","Mhic Corraidh","Mhic Cosgair","Mhic Críodáin",
    "Mhic Crabháin","Mhic Craith","Mhic Craobhaigh","Mhic Creacháin","Mhic Creachmhaoil","Mhic Croidheáin","Mhic Croidheagan","Mhic Crotaigh","Mhic Cruadhlaoich",
    "Mhic Cuairt","Mhic Cuanáin","Mhic Cuana","Mhic Cuanaigh","Mhic Cuarta","Mhic Cuilinn","Mhic Cuimín","Mhic Cuindlis","Mhic Cuineáin","Mhic Cuinn","Mhic Cuinneacháin",
    "Mhic Cuinneagáin","Mhic Cuirc","Mhic Cuirnín","Mhic Cullieagáin","Mhic Cumhaighe","Mhic Cumhaill","Mhic Daibhéid","Mhic Dhabhóg","Mhic Dhomhnuill","Mhic Dhonnchaidh",
    "Mhic Dhuarcáin","Mhic Dhubháin","Mhic Dhuibh","Mhic Dhuibhshíthe","Mhic Dhurcáin","Mhic Diarmada","Mhic Donnchadha","Mhic Dubhdara","Mhic Dubhghaill","Mhic Duibh",
    "Mhic Duibhir","Mhic Duibhshíthe","Mhic Duinnshléibhe","Mhic Eacháin","Mhic Eachaidh","Mhic Eanruig","Mhic Eathain","Mhic Eochagáin","Mhic Eoghain","Mhic Eoin",
    "Mhic Fheargail","Mhic Fhearghaile","Mhic Fhearghaill","Mhic Fhearraigh","Mhic Fhiachra","Mhic Fhinghin","Mhic Fhiodhbhuidhe","Mhic Fhirbhisigh","Mhic Fhlannchaidh",
    "Mhic Fionnlaigh","Mhic Gábháin","Mhic Gáibhín","Mhic Gáibhtheacháin","Mhic Géibheannaigh","Mhic Géidigh","Mhic Gabhann","Mhic Gadhra","Mhic Gafraidh","Mhic Gairbhshíth",
    "Mhic Gallchóir","Mhic Gallchobhair","Mhic Garmhaic","Mhic Gealbháin","Mhic Gearailt","Mhic Geargáin","Mhic Geibheannaigh","Mhic Geigheannaigh","Mhic Gibealáin",
    "Mhic Gille","Mhic Gille Íosa","Mhic Gille Chomhghaill","Mhic Gille Comhghain","Mhic Gille Dheòradha","Mhic Gille Eathain","Mhic Gille Fhaoláin","Mhic Gille Fhaolain",
    "Mhic Gille Fhinneain","Mhic Gille Fhionndaig","Mhic Gille Fhionntain","Mhic Gille Onchon","Mhic Gille Uidhir","Mhic Giolláin","Mhic Giolla","Mhic Giolla Íosa",
    "Mhic Giolla Bhríde","Mhic Giolla Chúda","Mhic Giolla Chúille","Mhic Giolla Chaillín","Mhic Giolla Chathair","Mhic Giolla Chlaoin","Mhic Giolla Choille",
    "Mhic Giolla Choinnigh","Mhic Giolla Chomhghaill","Mhic Giolla Coileáin","Mhic Giolla Comhghaill","Mhic Giolla Cuilinn","Mhic Giolla Deacair","Mhic Giolla Dheóradha",
    "Mhic Giolla Dhomhnaigh","Mhic Giolla Dhomnaigh","Mhic Giolla Duibh","Mhic Giolla Eóin","Mhic Giolla Easpuig","Mhic Giolla Fhaoláin","Mhic Giolla Fhionntáin",
    "Mhic Giolla Fhionntóg","Mhic Giolla Ghuala","Mhic Giolla Léigh","Mhic Giolla Leith","Mhic Giolla Mhártain","Mhic Giolla Mhaoil","Mhic Giolla Mhuire","Mhic Giolla Phádraig",
    "Mhic Giolla Phóil","Mhic Giolla Riabhaigh","Mhic Giolla Rua","Mhic Giolla Uidhir","Mhic Giolla na Naomh","Mhic Giolla t-Seanáin","Mhic Giolla-Gheimhridh","Mhic Giollagáin",
    "Mhic Glaisne","Mhic Glasáin","Mhic Gobhann","Mhic Gofraidh","Mhic Gormáin","Mhic Gráda","Mhic Gríofa","Mhic Grúgáin","Mhic Gribín","Mhic Gruagáin","Mhic Grudaire",
    "Mhic Iain","Mhic Iomaire","Mhic Labhradha","Mhic Labhrainn","Mhic Laibheartaigh","Mhic Leòid","Mhic Leanacháin","Mhic Liam","Mhic Lochlainn","Mhic Loinsigh",
    "Mhic Loughlin","Mhic Lughaidh","Mhic Máirtín","Mhic Maghnus","Mhic Maoláin","Mhic Mathúna","Mhic Mathghamhna","Mhic Mhuircheartaigh","Mhic Mhuirich","Mhic Muircheartaigh",
    "Mhic Muireadhaigh","Mhic Muiris","Mhic Murchadha","Mhic Murchaidh","Mhic Naois","Mhic Neachtain","Mhic Niadh","Mhic Niallais","Mhic Niocaill","Mhic Oilibhéir",
    "Mhic Oisdealbhaigh","Mhic Oistigín","Mhic Phádraig","Mhic Pháidín","Mhic Phóil","Mhic Phaidin","Mhic Pharthaláin","Mhic Phearais","Mhic Philbín","Mhic Philib",
    "Mhic Piarais","Mhic Pilib","Mhic Réamoinn","Mhic Rúaidh","Mhic Raghnaill","Mhic Reachtain","Mhic Reannacháin","Mhic Riabhaigh","Mhic Riada","Mhic Ruaidhrí","Mhic Ruidhrí",
    "Mhic Séaghdha","Mhic Síomóin","Mhic Síthigh","Mhic Saoghair","Mhic Scalaidhe","Mhic Seáin","Mhic Seanlaoich","Mhic Shitrig","Mhic Shuibhne","Mhic Somhairle",
    "Mhic Taidhg","Mhic Thámhais","Mhic Thóm","Mhic Thaidhg","Mhic Thighearnáin","Mhic Thomáis","Mhic Thréinfhir","Mhic Uáid","Mhic Uighlilin","Mhic Uisdein",
    "Mhic Uistein","Ní Ailín","Ní Báire","Ní Béara","Ní Bairr","Ní Banáin","Ní Baoighill","Ní Baoill","Ní Beólláin","Ní Bearáin","Ní Beirgin","Ní Bolguidhir",
    "Ní Brádaigh","Ní Brógáin","Ní Bradáin","Ní Branagáin","Ní Braoin","Ní Braonáin","Ní Breislin","Ní Briain","Ní Briosáin","Ní Broin","Ní Broithe","Ní Brolcháin",
    "Ní Brosnacháin","Ní Bruacháin","Ní Bruadair","Ní Buachalla","Ní Cnáimhsí","Ní Cnaimhín","Ní Crabháin","Ní Dálaigh","Ní Déaghain","Ní Díomasaigh","Ní Dónaill",
    "Ní Dúnadhaigh","Ní Daimhín","Ní Daire","Ní Dathlaoich","Ní Deághaidh","Ní Deargáin","Ní Deoradháin","Ní Dhonnaile","Ní Dhuiling","Ní Diarmada","Ní Diomain",
    "Ní Dobhailein","Ní Dochartaigh","Ní Doghair","Ní Doibhilin","Ní Doiridh","Ní Doirinne","Ní Doirnín","Ní Domhnalláin","Ní Donnabháin","Ní Donnagáin","Ní Donncadha",
    "Ní Donnchú","Ní Donnghaile","Ní Dorcháin","Ní Dorchaidhe","Ní Dornáin","Ní Dreaghneáin","Ní Duarcáin","Ní Dubháin","Ní Dubhagáin","Ní Dubhartaigh","Ní Dubhchonna",
    "Ní Dubhdáleithe","Ní Dubhda","Ní Dubhlaoich","Ní Dubhshláine","Ní Dubhthaigh","Ní Dubhuir","Ní Duibh","Ní Duibheamhna","Ní Duibheannaigh","Ní Duibhgeannain",
    "Ní Duibhginn","Ní Duibhidhir","Ní Duibhlin","Ní Duilleáin","Ní Duillearga","Ní Duineachdha","Ní Duinnín","Ní Duinn","Ní Duinnchinn","Ní Duirnín","Ní Dulchaointigh",
    "Ní Durcáin","Ní Fágáin","Ní Fáilbhe","Ní Fógartaigh","Ní Fallamhain","Ní Faodhagáin","Ní Faoláin","Ní Faracháin","Ní Farannáin","Ní Fathaigh","Ní Fearadhaigh",
    "Ní Fearghail","Ní Fearghaile","Ní Fearghasa","Ní Fearghuis","Ní Fearraigh","Ní Feichín","Ní Fhraoigh","Ní Fiacháin","Ní Fiaich","Ní Fiannachta","Ní Fiannaidhe",
    "Ní Finn","Ní Finnthighearn","Ní Fionnáin","Ní Fionnachta","Ní Fionnagáin","Ní Fionnghail","Ní Fionnghaile","Ní Fionnghalaigh","Ní Fithcheallaigh","Ní Flaithbertaigh",
    "Ní Flaithbheartaigh","Ní Flaithfhileadh","Ní Flaitile","Ní Flannabhra","Ní Flannagáin","Ní Flannail","Ní Flannghaile","Ní Floinn","Ní Foghladha","Ní Forannáin",
    "Ní Fuaráin","Ní Gormáin","Ní Hainbheáin","Ní Labhradha","Ní Laighin","Ní Laochdha","Ní Laoghaire","Ní Lapain","Ní Leannacháin","Ní Leocháin","Ní Liatháin",
    "Ní Lideadha","Ní Lochlainn","Ní Loideáin","Ní Loingsigh","Ní Lonagáin","Ní Longáin","Ní Lorcáin","Ní Luain","Ní Luasaigh","Ní Luinigh","Ní Máille","Ní Máinle",
    "Ní Méalóid","Ní Móráin","Ní Macdha","Ní Macháin","Ní Madáin","Ní Madagáin","Ní Mainchín","Ní Manacháin","Ní Manannáin","Ní Maoilíosa","Ní Maoil Mhichíl",
    "Ní Maoilbhríde","Ní Maoilbhrighde","Ní Maoileanaigh","Ní Maoileoin","Ní Maoilmheana","Ní Maoilmhiadhaigh","Ní Maoilriáin","Ní Maoilsheachlainn","Ní Maoilsheachnaill",
    "Ní Maoláin","Ní Maol Aodha","Ní Maol Chonaire","Ní Maol Dhomhnaigh","Ní Maol Máirthín","Ní Maol Mhaodhóg","Ní Maol Ruanaidh","Ní Maol Tuile","Ní Maolacháin",
    "Ní Maolagáin","Ní Maolalaidh","Ní Maolaodhóg","Ní Maolcatha","Ní Maolcholuim","Ní Maolchraoibhe","Ní Maolconaire","Ní Maoldúin","Ní Maoldomhnaigh","Ní Maolfhoghmhair",
    "Ní Maolmhóna","Ní Maolmhaghna","Ní Maolmhochóir","Ní Maolmhoicheirghe","Ní Maolmhuaidh","Ní Maolmhuire","Ní Maolmocheirghe","Ní Maolruanaidh","Ní Maonaigh",
    "Ní Maonghaile","Ní Maotháin","Ní Marcaigh","Ní Mathúna","Ní Mathghamhna","Ní Meára","Ní Meachair","Ní Meadhra","Ní Mealláin","Ní Mearlaigh","Ní Meidhir",
    "Ní Meirgin","Ní Mháirtín","Ní Miadhacháin","Ní Midhir","Ní Mocháin","Ní Mordha","Ní Mothlacháin","Ní Muimhneacháin","Ní Muineacháin","Ní Muineaog",
    "Ní Muireadhaigh","Ní Muireagáin","Ní Muireartaigh","Ní Muireasa","Ní Muiris","Ní Muraíle","Ní Murchú","Ní Murchadha","Ní Murghaile","Ní Murnáin",
    "Ní Murthuile","Ní Néill","Ní Neachtain","Ní Niadh","Ní Nialláin","Ní Niallagáin","Ní Nuadháin","Ní Nualláin","Ní Peatáin","Ní Pléimeann","Ní Ráighne",
    "Ní Ríagaín","Ní Rínn","Ní Ríordáin","Ní Rónáin","Ní Raghailligh","Ní Rathaille","Ní Riáin","Ní Roideacháin","Ní Ruadháin","Ní Ruadhagáin","Ní Ruairc",
    "Ní Ruanaidh","Ní Sé","Ní Síocháin","Ní Síoghraidh","Ní Síoráin","Ní Síthigh","Ní Súilleabháin","Ní Sabháin","Ní Saoraidhe","Ní Scalaidhe","Ní Scannail",
    "Ní Scoireadh","Ní Scolaidhe","Ní Scurra","Ní Seachnasaigh","Ní Seanáin","Ní Seireadáin","Ní Siadhail","Ní Siail","Ní Siochfhradha","Ní Sionúir",
    "Ní Sirideáin","Ní Slatara","Ní Slatiascaigh","Ní Sluagháin","Ní Sluaghadhaigh","Ní Somacháin","Ní Spaelain","Ní Suaird","Ní Suairt","Ní Tíghearnáin",
    "Ní Tíghearnaigh","Ní Taithligh","Ní Tanaidheain","Ní Teamhnainn","Ní Toghda","Ní Tonnaigh","Ní Tuachair","Ní Tuairisc","Ní Tuama","Ní Tuathaigh",
    "Ní Tuathail","Ní Tuathaláin","Ní hÁdhmaill","Ní hÁgáin","Ní hÁileagáin","Ní hÁilgheanáin","Ní hÁirt","Ní hÉamhthaigh","Ní hÉigceartaigh","Ní hÓgáin",
    "Ní hÓisín","Ní hÓsáin","Ní hÚbáin","Ní h-Ailghiusa","Ní hAiligheasa","Ní hAiliosa","Ní hAilmhic","Ní hAimheirgin","Ní hAinbhith","Ní hAinbhthín",
    "Ní hAinifín","Ní hAinle","Ní hAirmheadhaigh","Ní hAllmhuráin","Ní hAlluráin","Ní hAmhsaigh","Ní hAngluinn","Ní hAnnagáin","Ní hAnnaigh","Ní hAnnlúinn",
    "Ní hAnnracháin","Ní hAnrachtaigh","Ní hAnradháin","Ní hAodha","Ní hAodhagáin","Ní hAoileáin","Ní hAonghusa","Ní hAragáin","Ní hArgáin","Ní hArgadáin",
    "Ní hArrachtáin","Ní hArragáin","Ní hArtagáin","Ní hAthairne","Ní hEachach","Ní hEachaidh","Ní hEachthairn","Ní hEadeáin","Ní hEadhra","Ní hEaghráin",
    "Ní hEaghra","Ní hEalaighthe","Ní hEanraig","Ní hEaráin","Ní hEarcáin","Ní hEarchadha","Ní hEarchaidh","Ní hEarghaile","Ní hEidhin","Ní hEidhneacháin",
    "Ní hEidirsceoil","Ní hEimhín","Ní hEireamhóin","Ní hEodhusa","Ní hEoghanáin","Ní hIarfhlatha","Ní hIcí","Ní hIceadh","Ní hIfearnáin","Ní hInreachtaigh",
    "Ní hIonmhaineáin","Ní hIonnghaile","Ní hIorua","Ní hIoruaidh","Ní hOistín","Ní hUainín","Ní hUallacháin","Ní hUiginn","Ní hUrmholtaigh","Ní hUrthuile",
    "Nic Ámoinn","Nic Éanraic","Nic Íomhair","Nic Adaim","Nic Ailin","Nic Airt","Nic Alasdair","Nic Amhlaidh","Nic Amhlaoibh","Nic Aodha","Nic Aodhagáin",
    "Nic Aoidh","Nic Aonghuis","Nic Aonghusa","Nic Ardghail","Nic Artair","Nic Asgaill","Nic Ausaláin","Nic Bhiadhtaigh","Nic Bhloscaidh","Nic Braoin",
    "Nic Braonáin","Nic Cába","Nic Cárthaigh","Nic Céile","Nic Céileachair","Nic Céin","Nic Céirín","Nic Céitinn","Nic Cómhaltáin","Nic Cú Uladh","Nic Cúg",
    "Nic Cadhla","Nic Cahan","Nic Cailin","Nic Cairbre","Nic Cairealláin","Nic Caiside","Nic Canáin","Nic Cana","Nic Canannáin","Nic Canann","Nic Caocháin",
    "Nic Caoimh","Nic Caoindealbháin","Nic Caoinnigh","Nic Caollaidhe","Nic Caomháin","Nic Carra","Nic Carrghamhna","Nic Cartaine","Nic Catháin","Nic Cathail",
    "Nic Cathaláin","Nic Cathal","Nic Cathasaigh","Nic Cathmhaoil","Nic Ceallacháin","Nic Ceallaigh","Nic Ceanndubháin","Nic Cearáin","Nic Cearbhaigh",
    "Nic Cearbhaill","Nic Cearbhalláin","Nic Cearnacháin","Nic Cearnaigh","Nic Cearncháin","Nic Cianáin","Nic Cianaigh","Nic Ciaráin","Nic Ciaragáin",
    "Nic Ciardha","Nic Cillín","Nic Cinnéide","Nic Cinnseallaigh","Nic Cionaodha","Nic Cionnaith","Nic Cionnfhaolaidh","Nic Ciosáin","Nic Cléirigh",
    "Nic Cluanaigh","Nic Cluasaigh","Nic Cnáimhsí","Nic Cnaimhín","Nic Cobhthaigh","Nic Cogadháin","Nic Coigligh","Nic Coilín","Nic Coileáin","Nic Coinnich",
    "Nic Coinnigh","Nic Coitir","Nic Colgáin","Nic Colla","Nic Coluim","Nic Comhraidhe","Nic Con Coille","Nic Con Fhiacla","Nic Con Mhaighe","Nic Con Uladh",
    "Nic Conaill","Nic Conaing","Nic Conaire","Nic Conalláin","Nic Conaráin","Nic Conbhuide","Nic Conchúir","Nic Conchobhair","Nic Conduibh","Nic Conghaile",
    "Nic Conmara","Nic Conmidhe","Nic Connacháin","Nic Connagáin","Nic Connmhaigh","Nic Conradh","Nic Conraoi","Nic Consaidín","Nic Conshámha","Nic Corbáin",
    "Nic Corcáin","Nic Cormaic","Nic Cornghaile","Nic Corráin","Nic Corra","Nic Corragáin","Nic Corraidh","Nic Cosgair","Nic Críodáin","Nic Crabháin","Nic Craith",
    "Nic Craobhaigh","Nic Creacháin","Nic Creachmhaoil","Nic Croidheáin","Nic Croidheagan","Nic Crotaigh","Nic Cruadhlaoich","Nic Cuairt","Nic Cuanáin","Nic Cuana",
    "Nic Cuanaigh","Nic Cuarta","Nic Cuilinn","Nic Cuimín","Nic Cuindlis","Nic Cuineáin","Nic Cuinn","Nic Cuinneacháin","Nic Cuinneagáin","Nic Cuirc","Nic Cuirnín",
    "Nic Cullieagáin","Nic Cumhaighe","Nic Cumhaill","Nic Daibhéid","Nic Dhabhóg","Nic Dhomhnuill","Nic Dhonnchaidh","Nic Dhuarcáin","Nic Dhubháin","Nic Dhuibh",
    "Nic Dhuibhshíthe","Nic Dhurcáin","Nic Diarmada","Nic Donnchadha","Nic Dubhdara","Nic Dubhghaill","Nic Duibh","Nic Duibhir","Nic Duibhshíthe","Nic Duinnshléibhe",
    "Nic Eacháin","Nic Eachaidh","Nic Eanruig","Nic Eathain","Nic Eochagáin","Nic Eoghain","Nic Eoin","Nic Fheargail","Nic Fhearghaile","Nic Fhearghaill","Nic Fhearraigh",
    "Nic Fhiachra","Nic Fhinghin","Nic Fhiodhbhuidhe","Nic Fhirbhisigh","Nic Fhlannchaidh","Nic Fionnlaigh","Nic Gábháin","Nic Gáibhín","Nic Gáibhtheacháin",
    "Nic Géibheannaigh","Nic Géidigh","Nic Gabhann","Nic Gadhra","Nic Gafraidh","Nic Gairbhshíth","Nic Gallchóir","Nic Gallchobhair","Nic Garmhaic","Nic Gealbháin",
    "Nic Gearailt","Nic Geargáin","Nic Geibheannaigh","Nic Geigheannaigh","Nic Gibealáin","Nic Gille","Nic Gille Íosa","Nic Gille Chomhghaill","Nic Gille Comhghain",
    "Nic Gille Dheòradha","Nic Gille Eathain","Nic Gille Fhaoláin","Nic Gille Fhaolain","Nic Gille Fhinneain","Nic Gille Fhionndaig","Nic Gille Fhionntain",
    "Nic Gille Onchon","Nic Gille Uidhir","Nic Giolláin","Nic Giolla","Nic Giolla Íosa","Nic Giolla Bhríde","Nic Giolla Chúda","Nic Giolla Chúille","Nic Giolla Chaillín",
    "Nic Giolla Chathair","Nic Giolla Chlaoin","Nic Giolla Choille","Nic Giolla Choinnigh","Nic Giolla Chomhghaill","Nic Giolla Coileáin","Nic Giolla Comhghaill",
    "Nic Giolla Cuilinn","Nic Giolla Deacair","Nic Giolla Dheóradha","Nic Giolla Dhomhnaigh","Nic Giolla Dhomnaigh","Nic Giolla Duibh","Nic Giolla Eóin",
    "Nic Giolla Easpuig","Nic Giolla Fhaoláin","Nic Giolla Fhionntáin","Nic Giolla Fhionntóg","Nic Giolla Ghuala","Nic Giolla Léigh","Nic Giolla Leith",
    "Nic Giolla Mhártain","Nic Giolla Mhaoil","Nic Giolla Mhuire","Nic Giolla Phádraig","Nic Giolla Phóil","Nic Giolla Riabhaigh","Nic Giolla Rua","Nic Giolla Uidhir",
    "Nic Giolla na Naomh","Nic Giolla t-Seanáin","Nic Giolla-Gheimhridh","Nic Giollagáin","Nic Glaisne","Nic Glasáin","Nic Gobhann","Nic Gofraidh","Nic Gormáin",
    "Nic Gráda","Nic Gríofa","Nic Grúgáin","Nic Gribín","Nic Gruagáin","Nic Grudaire","Nic Iain","Nic Iomaire","Nic Labhradha","Nic Labhrainn","Nic Laibheartaigh",
    "Nic Leòid","Nic Leanacháin","Nic Liam","Nic Lochlainn","Nic Loinsigh","Nic Loughlin","Nic Lughaidh","Nic Máirtín","Nic Maghnus","Nic Maoláin","Nic Mathúna",
    "Nic Mathghamhna","Nic Mhuircheartaigh","Nic Mhuirich","Nic Muircheartaigh","Nic Muireadhaigh","Nic Muiris","Nic Murchadha","Nic Murchaidh","Nic Naois",
    "Nic Neachtain","Nic Niadh","Nic Niallais","Nic Niocaill","Nic Oilibhéir","Nic Oisdealbhaigh","Nic Oistigín","Nic Phádraig","Nic Pháidín","Nic Phóil","Nic Phaidin",
    "Nic Pharthaláin","Nic Phearais","Nic Philbín","Nic Philib","Nic Piarais","Nic Pilib","Nic Réamoinn","Nic Rúaidh","Nic Raghnaill","Nic Reachtain","Nic Reannacháin",
    "Nic Riabhaigh","Nic Riada","Nic Ruaidhrí","Nic Ruidhrí","Nic Séaghdha","Nic Síomóin","Nic Síthigh","Nic Saoghair","Nic Scalaidhe","Nic Seáin","Nic Seanlaoich",
    "Nic Shitrig","Nic Shuibhne","Nic Somhairle","Nic Taidhg","Nic Thámhais","Nic Thóm","Nic Thaidhg","Nic Thighearnáin","Nic Thomáis","Nic Thréinfhir","Nic Uáid",
    "Nic Uighlilin","Nic Uisdein","Nic Uistein","Uí Ailín","Uí Báire","Uí Béara","Uí Bairr","Uí Banáin","Uí Baoighill","Uí Baoill","Uí Beólláin","Uí Bearáin",
    "Uí Beirgin","Uí Bolguidhir","Uí Brádaigh","Uí Brógáin","Uí Bradáin","Uí Branagáin","Uí Braoin","Uí Braonáin","Uí Breislin","Uí Briain","Uí Briosáin","Uí Broin",
    "Uí Broithe","Uí Brolcháin","Uí Brosnacháin","Uí Bruacháin","Uí Bruadair","Uí Buachalla","Uí Cnáimhsí","Uí Cnaimhín","Uí Crabháin","Uí Dálaigh","Uí Déaghain",
    "Uí Díomasaigh","Uí Dónaill","Uí Dúnadhaigh","Uí Daimhín","Uí Daire","Uí Dathlaoich","Uí Deághaidh","Uí Deargáin","Uí Deoradháin","Uí Dhonnaile","Uí Dhuiling",
    "Uí Diarmada","Uí Diomain","Uí Dobhailein","Uí Dochartaigh","Uí Doghair","Uí Doibhilin","Uí Doiridh","Uí Doirinne","Uí Doirnín","Uí Domhnalláin","Uí Donnabháin",
    "Uí Donnagáin","Uí Donncadha","Uí Donnchú","Uí Donnghaile","Uí Dorcháin","Uí Dorchaidhe","Uí Dornáin","Uí Dreaghneáin","Uí Duarcáin","Uí Dubháin","Uí Dubhagáin",
    "Uí Dubhartaigh","Uí Dubhchonna","Uí Dubhdáleithe","Uí Dubhda","Uí Dubhlaoich","Uí Dubhshláine","Uí Dubhthaigh","Uí Dubhuir","Uí Duibh","Uí Duibheamhna",
    "Uí Duibheannaigh","Uí Duibhgeannain","Uí Duibhginn","Uí Duibhidhir","Uí Duibhlin","Uí Duilleáin","Uí Duillearga","Uí Duineachdha","Uí Duinnín","Uí Duinn",
    "Uí Duinnchinn","Uí Duirnín","Uí Dulchaointigh","Uí Durcáin","Uí Fágáin","Uí Fáilbhe","Uí Fógartaigh","Uí Fallamhain","Uí Faodhagáin","Uí Faoláin","Uí Faracháin",
    "Uí Farannáin","Uí Fathaigh","Uí Fearadhaigh","Uí Fearghail","Uí Fearghaile","Uí Fearghasa","Uí Fearghuis","Uí Fearraigh","Uí Feichín","Uí Fhraoigh","Uí Fiacháin",
    "Uí Fiaich","Uí Fiannachta","Uí Fiannaidhe","Uí Finn","Uí Finnthighearn","Uí Fionnáin","Uí Fionnachta","Uí Fionnagáin","Uí Fionnghail","Uí Fionnghaile",
    "Uí Fionnghalaigh","Uí Fithcheallaigh","Uí Flaithbertaigh","Uí Flaithbheartaigh","Uí Flaithfhileadh","Uí Flaitile","Uí Flannabhra","Uí Flannagáin","Uí Flannail",
    "Uí Flannghaile","Uí Floinn","Uí Foghladha","Uí Forannáin","Uí Fuaráin","Uí Gormáin","Uí Hainbheáin","Uí Labhradha","Uí Laighin","Uí Laochdha","Uí Laoghaire",
    "Uí Lapain","Uí Leannacháin","Uí Leocháin","Uí Liatháin","Uí Lideadha","Uí Lochlainn","Uí Loideáin","Uí Loingsigh","Uí Lonagáin","Uí Longáin","Uí Lorcáin",
    "Uí Luain","Uí Luasaigh","Uí Luinigh","Uí Máille","Uí Máinle","Uí Méalóid","Uí Móráin","Uí Macdha","Uí Macháin","Uí Madáin","Uí Madagáin","Uí Mainchín",
    "Uí Manacháin","Uí Manannáin","Uí Maoilíosa","Uí Maoil Mhichíl","Uí Maoilbhríde","Uí Maoilbhrighde","Uí Maoileanaigh","Uí Maoileoin","Uí Maoilmheana",
    "Uí Maoilmhiadhaigh","Uí Maoilriáin","Uí Maoilsheachlainn","Uí Maoilsheachnaill","Uí Maoláin","Uí Maol Aodha","Uí Maol Chonaire","Uí Maol Dhomhnaigh",
    "Uí Maol Máirthín","Uí Maol Mhaodhóg","Uí Maol Ruanaidh","Uí Maol Tuile","Uí Maolacháin","Uí Maolagáin","Uí Maolalaidh","Uí Maolaodhóg","Uí Maolcatha",
    "Uí Maolcholuim","Uí Maolchraoibhe","Uí Maolconaire","Uí Maoldúin","Uí Maoldomhnaigh","Uí Maolfhoghmhair","Uí Maolmhóna","Uí Maolmhaghna","Uí Maolmhochóir",
    "Uí Maolmhoicheirghe","Uí Maolmhuaidh","Uí Maolmhuire","Uí Maolmocheirghe","Uí Maolruanaidh","Uí Maonaigh","Uí Maonghaile","Uí Maotháin","Uí Marcaigh",
    "Uí Mathúna","Uí Mathghamhna","Uí Meára","Uí Meachair","Uí Meadhra","Uí Mealláin","Uí Mearlaigh","Uí Meidhir","Uí Meirgin","Uí Mháirtín","Uí Miadhacháin",
    "Uí Midhir","Uí Mocháin","Uí Mordha","Uí Mothlacháin","Uí Muimhneacháin","Uí Muineacháin","Uí Muineaog","Uí Muireadhaigh","Uí Muireagáin","Uí Muireartaigh",
    "Uí Muireasa","Uí Muiris","Uí Muraíle","Uí Murchú","Uí Murchadha","Uí Murghaile","Uí Murnáin","Uí Murthuile","Uí Néill","Uí Neachtain","Uí Niadh","Uí Nialláin",
    "Uí Niallagáin","Uí Nuadháin","Uí Nualláin","Uí Peatáin","Uí Pléimeann","Uí Ráighne","Uí Ríagaín","Uí Rínn","Uí Ríordáin","Uí Rónáin","Uí Raghailligh",
    "Uí Rathaille","Uí Riáin","Uí Roideacháin","Uí Ruadháin","Uí Ruadhagáin","Uí Ruairc","Uí Ruanaidh","Uí Sé","Uí Síocháin","Uí Síoghraidh","Uí Síoráin",
    "Uí Síthigh","Uí Súilleabháin","Uí Sabháin","Uí Saoraidhe","Uí Scalaidhe","Uí Scannail","Uí Scoireadh","Uí Scolaidhe","Uí Scurra","Uí Seachnasaigh",
    "Uí Seanáin","Uí Seireadáin","Uí Siadhail","Uí Siail","Uí Siochfhradha","Uí Sionúir","Uí Sirideáin","Uí Slatara","Uí Slatiascaigh","Uí Sluagháin",
    "Uí Sluaghadhaigh","Uí Somacháin","Uí Spaelain","Uí Suaird","Uí Suairt","Uí Tíghearnáin","Uí Tíghearnaigh","Uí Taithligh","Uí Tanaidheain","Uí Teamhnainn",
    "Uí Toghda","Uí Tonnaigh","Uí Tuachair","Uí Tuairisc","Uí Tuama","Uí Tuathaigh","Uí Tuathail","Uí Tuathaláin","Uí hÁdhmaill","Uí hÁgáin","Uí hÁileagáin",
    "Uí hÁilgheanáin","Uí hÁirt","Uí hÉamhthaigh","Uí hÉigceartaigh","Uí hÓgáin","Uí hÓisín","Uí hÓsáin","Uí hÚbáin","Uí h-Ailghiusa","Uí hAiligheasa",
    "Uí hAiliosa","Uí hAilmhic","Uí hAimheirgin","Uí hAinbhith","Uí hAinbhthín","Uí hAinifín","Uí hAinle","Uí hAirmheadhaigh","Uí hAllmhuráin","Uí hAlluráin",
    "Uí hAmhsaigh","Uí hAngluinn","Uí hAnnagáin","Uí hAnnaigh","Uí hAnnlúinn","Uí hAnnracháin","Uí hAnrachtaigh","Uí hAnradháin","Uí hAodha","Uí hAodhagáin",
    "Uí hAoileáin","Uí hAonghusa","Uí hAragáin","Uí hArgáin","Uí hArgadáin","Uí hArrachtáin","Uí hArragáin","Uí hArtagáin","Uí hAthairne","Uí hEachach",
    "Uí hEachaidh","Uí hEachthairn","Uí hEadeáin","Uí hEadhra","Uí hEaghráin","Uí hEaghra","Uí hEalaighthe","Uí hEanraig","Uí hEaráin","Uí hEarcáin",
    "Uí hEarchadha","Uí hEarchaidh","Uí hEarghaile","Uí hEidhin","Uí hEidhneacháin","Uí hEidirsceoil","Uí hEimhín","Uí hEireamhóin","Uí hEodhusa",
    "Uí hEoghanáin","Uí hIarfhlatha","Uí hIcí","Uí hIceadh","Uí hIfearnáin","Uí hInreachtaigh","Uí hIonmhaineáin","Uí hIonnghaile","Uí hIorua","Uí hIoruaidh",
    "Uí hOistín","Uí hUainín","Uí hUallacháin","Uí hUiginn","Uí hUrmholtaigh","Uí hUrthuile"
};
QVector<QString> Celte::PRENOMS_M = {
"Ábharrach","Ádhamh","Áengus","Ágastas","Áinle","Áinnle","Áirdin","Árón","Árdghal","Éadbhárd","Éamon","Éamonn","Éanán","Éanna","Éibhear","Éignach","Éigneachán","Éimhín","Éinde","Éireamhón","Émer",
    "Íobhar","Íomhar","Íon","Íor","Óengus","Úaithne","Úghaire","Abbán","Acobhrán","Adomnán","Agaistín","Aibhne","Aicher","Aichlinn","Ailín","Ailbhe","Ailill","Ailin","Ailithir","Ainéislis",
    "Aindréas","Aindriú","Ainmire","Ainníleas","Airdgal","Amalgith","Ambrós","Amhalgaidh","Amhlaoibh","Amhra","Anamcha","Anfudán","Anluan","Anmchadh","Anraoi","Antóin","Antóine","Aodhán",
    "Aodh","Aodhagán","Aodhgán","Aogán","Aoidhghean","Aolú","Aona","Aonghus","Ardghal","Ardghar","Artúr","Art","Artgal","Augholy","Ayamonn","Búadach","Bairre","Bairrionn","Banbhán","Baodán",
    "Baoithin","Baolach","Baothghalach","Barhan","Barra","Beacán","Beanon","Bearach","Bearchán","Bearnárd","Beccán","Beircheart","Benedict","Beolagh","Berach","Blámhac","Bláthmac",
    "Bréanainn","Bran","Brandubh","Braon","Breandán","Breanndán","Breas","Breasal","Breccán","Brecc","Brión","Brian","Bricín","Brine","Brochadh","Buadhach","Cáel","Cárthach","Céadach",
    "Cúchonnacht","Cúmhaí","Cúmhaighe","Cúmheá","Cúmheadha","Cadhan","Cadhla","Cailean","Caillin","Cailte","Caimin","Cainneach","Cairbre","Caireall","Cairneach","Calbhach","Canice",
    "Caoimhín","Caoimhghín","Caoinleán","Caolán","Caolbhadh","Caomhán","Carhal","Carraig","Carthach","Casey","Cassair","Cathán","Cathair","Cathal","Cathaoir","Cathbharr","Ceallachán",
    "Ceallach","Cearúl","Cearbhall","Ceat","Cellach","Cethern","Cianán","Cian","Ciarán","Cillín","Cillian","Cináed","Cinnéide","Cinnéididh","Cinnéidigh","Cinnsealach","Cionaodh",
    "Cionnaola","Ciothruadh","Clothach","Cofach","Coilín","Coileán","Coilean","Coinneach","Coireall","Colla","Colmán","Colm","Colmcille","Colum","Columbcille","Comán","Comhghall",
    "Comhghan","Conán","Conaire","Conall","Conchúr","Conchobhar","Conchubhar","Congal","Conghalach","Conlao","Conmhac","Conn","Connla","Connlaodh","Connor","Conor","Conuil","Cormac",
    "Cosnamhach","Críonán","Críostóir","Cróchán","Crónán","Criodan","Criofan","Criomthann","Cruimín","Cruinn","Cuán","Cuan","Cuana","Cuchulainn","Cuileán","Cuimín","Cumhal","Dáire",
    "Dáithí","Déaglán","Dícuill","Dímma","Díochú","Díomán","Dónall","Dúnchadh","Dúnlang","Dabhóg","Dabhag","Dagda","Daghán","Daibhead","Daibhi","Daigh","Daighre","Daimhín","Dainéal",
    "Daire","Daithi","Dalbhach","Damháin","Damhán","Dara","Darragh","Deaglán","Deamán","Deasmhumhnach","Declán","Declan","Dianach","Diarmaid","Diarmait","Dineartach","Doctor",
    "Domhnall","Domnall","Donagh","Donnán","Donn","Donnchadh","Donnchadha","Donncuan","Donovan","Dualtach","Duarcán","Dubhán","Dubhaltach","Dubhda","Dubhghall","Dubhghlas","Dufach",
    "Eóin","Eachaidh","Eachann","Eachdhonn","Eachthighearn","Eamon","Eamonn","Eanna","Earcán","Earc","Earnán","Earnan","Echlin","Echmhílidh","Eibhir","Eignach","Eigneachán","Eiltín",
    "Eireamhán","Eireamhón","Eirnín","Eoan","Eochaid","Eochaidh","Eogan","Eoghainín","Eoghanán","Eoghan","Eoin","Eolann","Fáelán","Fáilbhe","Féilim","Féthchú","Féthmac","Fínán",
    "Fínín","Fínneachta","Fíthel","Fachtna","Failghe","Faircheallach","Faithleann","Faoiltiarn","Faolán","Faolan","Faolchu","Fearachach","Fearadhach","Fearchar","Feardomhnach",
    "Fearganainm","Fearghal","Fearghus","Feargus","Fedelmid","Feichín","Feidhlim","Felimid","Feradach","Fergus","Fiacc","Fiach","Fiacha","Fiachna","Fiachra","Finbar","Finghin",
    "Finguine","Finnán","Finn","Finnbar","Finnchán","Finnchú","Finnchad","Finnian","Finnlug","Fionghuine","Fionn","Fionnbharr","Fionntán","Fitheal","Flaithrí","Flannán","Flann",
    "Fortchern","Fothad","Fraech","Fraochan","Frassach","Froinsias","Garbhán","Gearóid","Gilla","Gilleece","Glaisne","Glasán","Glas","Glassán","Gobán","Gréagóir","Greagoir","Greallán",
    "Guásacht","Guaire","Iósaf","Iúdás","Iarfhlaith","Iarlaith","Iarlugh","Imchad","Irial","Lúarán","Lúi","Lúithiarn","Labhrás","Labhraidh","Lachtín","Lachtna","Laidhgeann","Laighneach",
    "Laisrén","Laobhán","Laoghaire","Laoighseach","Laoiseach","Lasairian","Laserian","Laughlin","Leanan","Leenane","Liadhnán","Liam","Liber","Lithgen","Loch","Lochan","Lochlainn",
    "Lochlann","Lomán","Lonán","Lorcán","Loughlin","Lubhrás","Luchaidh","Lugaid","Lughán","Lugh","Lughaidh","Lughna","Máedóc","Máelechlainn","Máirtín","Mícheál","Maelíosa",
    "Maeleachlainn","Maelsheachlainn","Mainchín","Maine","Mairtin","Maithi","Maitiú","Maitiu","Malachi","Malachy","Manchán","Maodhóg","Maodhog","Maoilín","Maoilir","Maolóráin",
    "Maol","Maolcholm","Maolcholuim","Maolmórdha","Maolmhuire","Maolruadháin","Maolruanaí","Maonach","Matha","Mathghamhain","Meallán","Miach","Michan","Mochaomhóg","Mocholla",
    "Mochonna","Mochta","Mochua","Mochuda","Mochuma","Molaisse","Molua","Muadhán","Muiríoch","Muiríos","Muircheartach","Muireach","Muireadhach","Muirgheas","Muirin","Muiris",
    "Murchú","Murchadh","Néamh","Nóe","Nóise","Naisi","Naithí","Nannid","Naoise","Naomhán","Naos","Neachtan","Neasán","Nechtan","Niadh","Niallán","Niall","Nioclás","Nuadha",
    "Nuadu","Odhrán","Oilibhéar","Oilleóg","Oireachtach","Oisín","Onchú","Oscar","Pádhraic","Pádraig","Páidí","Páidín","Páid","Páraic","Póil","Pól","Padhra","Paití","Peadar",
    "Piaras","Pilib","Proinnsias","Proinsias","Réamann","Réamonn","Rónán","Rúadhán","Raghnall","Raibhilín","Riaghail","Riain","Rian","Riocard","Riordán","Ristéard","Risteárd",
    "Rohan","Roibéard","Roibeárd","Roibeard","Roibhilín","Ros","Ruadhán","Ruaidhri","Ruaidri","Ruairí","Ruairi","Ruarí","Ruari","Ruaridh","Ruibhilín","Ruisín","Rumann","Séadna",
    "Séafra","Séamas","Séamus","Séan","Séaonin","Séighín","Síoda","Síomón","Saerbhreathach","Scoithín","Seán","Seárlas","Seachnasach","Seanán","Seanchen","Seathan","Senán","Senan",
    "Seoirse","Seosamh","Seumas","Siadhal","Siaghal","Sioda","Siollán","Sléibhín","Solamh","Stíofán","Stiofan","Suibhne","Suibne","Tárlacll","Téodóir","Tadgh","Tadhg","Taichleach",
    "Tassach","Teigue","Teimhnín","Tiarnach","Tiarnan","Tiernán","Tierney","Tighearnán","Tighernach","Tiobóid","Toimilin","Toirdhealbhach","Toirleach","Tomás","Tomaltach","Torna",
    "Treabhair","Tuama","Tuathal","Uaitéar","Uaithne","Ualgharg","Uilleag","Uilliam","Uinseann","Ultán"
};

QVector<QString> Celte::NOMS_M =
        {
    "Ó Ailín","Ó Báire","Ó Béara","Ó Bairr","Ó Banáin","Ó Baoighill","Ó Baoill","Ó Beólláin","Ó Bearáin","Ó Beirgin","Ó Bolguidhir","Ó Brádaigh","Ó Brógáin","Ó Bradáin",
    "Ó Branagáin","Ó Braoin","Ó Braonáin","Ó Breislin","Ó Briain","Ó Briosáin","Ó Broin","Ó Broithe","Ó Brolcháin","Ó Brosnacháin","Ó Bruacháin","Ó Bruadair","Ó Buachalla",
    "Ó Céileachair","Ó Céin","Ó Céirín","Ó Céitinn","Ó Cómhaltáin","Ó Cadhla","Ó Cahan","Ó Cairbre","Ó Cairealláin","Ó Caiside","Ó Canáin","Ó Canannáin","Ó Canann","Ó Caoimh",
    "Ó Caoindealbháin","Ó Caoinnigh","Ó Caollaidhe","Ó Caomháin","Ó Carra","Ó Catháin","Ó Cathaláin","Ó Cathal","Ó Cathasaigh","Ó Ceallacháin","Ó Ceallaigh","Ó Ceanndubháin",
    "Ó Cearbhaill","Ó Cearbhalláin","Ó Cearnacháin","Ó Cearnaigh","Ó Cearncháin","Ó Cianáin","Ó Cianaigh","Ó Ciaragáin","Ó Ciardha","Ó Cillín","Ó Cinnéide","Ó Cinnseallaigh",
    "Ó Cionaodha","Ó Cionnaith","Ó Cionnfhaolaidh","Ó Ciosáin","Ó Cléirigh","Ó Cluanaigh","Ó Cobhthaigh","Ó Coigligh","Ó Coileáin","Ó Coinnigh","Ó Comhraidhe","Ó Con Fhiacla",
    "Ó Conaill","Ó Conaing","Ó Conaire","Ó Conalláin","Ó Conaráin","Ó Conbhuide","Ó Conchúir","Ó Conchobhair","Ó Conghaile","Ó Connacháin","Ó Connagáin","Ó Connmhaigh",
    "Ó Conradh","Ó Conraoi","Ó Corbáin","Ó Corcáin","Ó Cornghaile","Ó Corráin","Ó Corra","Ó Corragáin","Ó Críodáin","Ó Craobhaigh","Ó Creacháin","Ó Creachmhaoil","Ó Croidheáin",
    "Ó Croidheagan","Ó Crotaigh","Ó Cruadhlaoich","Ó Cuanáin","Ó Cuana","Ó Cuanaigh","Ó Cuilinn","Ó Cuimín","Ó Cuineáin","Ó Cuinn","Ó Cuinneacháin","Ó Cuinneagáin","Ó Cuirc",
    "Ó Cuirnín","Ó Cullieagáin","Ó Dálaigh","Ó Déaghain","Ó Díomasaigh","Ó Dónaill","Ó Dúnadhaigh","Ó Daimhín","Ó Daire","Ó Dathlaoich","Ó Deághaidh","Ó Deargáin","Ó Deoradháin",
    "Ó Dhonnaile","Ó Dhuiling","Ó Diarmada","Ó Diomain","Ó Dobhailein","Ó Dochartaigh","Ó Doghair","Ó Doibhilin","Ó Doiridh","Ó Doirinne","Ó Doirnín","Ó Domhnalláin","Ó Donnabháin",
    "Ó Donnagáin","Ó Donncadha","Ó Donnchú","Ó Donnghaile","Ó Dorcháin","Ó Dorchaidhe","Ó Dornáin","Ó Dreaghneáin","Ó Duarcáin","Ó Dubháin","Ó Dubhagáin","Ó Dubhartaigh","Ó Dubhchonna","Ó Dubhdáleithe","Ó Dubhda","Ó Dubhlaoich","Ó Dubhshláine","Ó Dubhthaigh","Ó Dubhuir","Ó Duibh","Ó Duibheamhna","Ó Duibheannaigh","Ó Duibhgeannain","Ó Duibhginn","Ó Duibhidhir","Ó Duibhlin","Ó Duilleáin","Ó Duillearga","Ó Duineachdha","Ó Duinnín","Ó Duinn","Ó Duinnchinn","Ó Duirnín","Ó Dulchaointigh","Ó Durcáin","Ó Fágáin","Ó Fáilbhe","Ó Fógartaigh","Ó Fallamhain","Ó Faodhagáin","Ó Faoláin","Ó Faracháin","Ó Farannáin","Ó Fathaigh","Ó Fearadhaigh","Ó Fearghail","Ó Fearghaile","Ó Fearghasa","Ó Fearghuis","Ó Fearraigh","Ó Feichín","Ó Fhraoigh","Ó Fiacháin","Ó Fiaich","Ó Fiannachta","Ó Fiannaidhe","Ó Finn","Ó Finnthighearn","Ó Fionnáin","Ó Fionnachta","Ó Fionnagáin","Ó Fionnghail","Ó Fionnghaile","Ó Fionnghalaigh","Ó Fithcheallaigh","Ó Flaithbertaigh","Ó Flaithbheartaigh","Ó Flaithfhileadh","Ó Flaitile","Ó Flannabhra","Ó Flannagáin","Ó Flannail","Ó Flannghaile","Ó Floinn","Ó Foghladha","Ó Forannáin","Ó Fuaráin","Ó Gábháin","Ó Gáibhín","Ó Gáibhtheacháin","Ó Gadhra","Ó Gairbhshíth","Ó Gallchóir","Ó Gallchobhair","Ó Garmhaic","Ó Gealbháin","Ó Geargáin","Ó Geibheannaigh","Ó Geigheannaigh","Ó Gibealáin","Ó Giolláin","Ó Glaisne","Ó Glasáin","Ó Gráda","Ó Gríofa","Ó Grúgáin","Ó Gribín","Ó Gruagáin","Ó Hainbheáin","Ó Labhradha","Ó Laighin","Ó Laochdha","Ó Laoghaire","Ó Lapain","Ó Leannacháin","Ó Leocháin","Ó Liatháin","Ó Lideadha","Ó Lochlainn","Ó Loideáin","Ó Loingsigh","Ó Lonagáin","Ó Longáin","Ó Lorcáin","Ó Luain","Ó Luasaigh","Ó Luinigh","Ó Máille","Ó Máinle","Ó Méalóid","Ó Móráin","Ó Maolmhochóir","Ó Macdha","Ó Macháin","Ó Madáin","Ó Madagáin","Ó Mainchín","Ó Manacháin","Ó Manannáin","Ó Maoilíosa","Ó Maoil Mhichíl","Ó Maoilbhríde","Ó Maoilbhrighde","Ó Maoileanaigh","Ó Maoileoin","Ó Maoilmheana","Ó Maoilmhiadhaigh","Ó Maoilriáin","Ó Maoilsheachlainn","Ó Maoilsheachnaill","Ó Maoláin","Ó Maol Aodha","Ó Maol Chonaire","Ó Maol Dhomhnaigh","Ó Maol Máirthín","Ó Maol Mhaodhóg","Ó Maol Ruanaidh","Ó Maol Tuile","Ó Maolacháin","Ó Maolagáin","Ó Maolalaidh","Ó Maolaodhóg","Ó Maolcatha","Ó Maolcholuim","Ó Maolchraoibhe","Ó Maolconaire","Ó Maoldúin","Ó Maoldomhnaigh","Ó Maolfhoghmhair","Ó Maolmhóna","Ó Maolmhaghna","Ó Maolmhoicheirghe","Ó Maolmhuaidh","Ó Maolmhuire","Ó Maolmocheirghe","Ó Maolruanaidh","Ó Maonaigh","Ó Maonghaile","Ó Maotháin","Ó Marcaigh","Ó Mathúna","Ó Mathghamhna","Ó Meára","Ó Meachair","Ó Meadhra","Ó Mealláin","Ó Mearlaigh","Ó Meidhir","Ó Meirgin","Ó Mháirtín","Ó Miadhacháin","Ó Midhir","Ó Mocháin","Ó Mordha","Ó Mothlacháin","Ó Muimhneacháin","Ó Muineacháin","Ó Muineaog","Ó Muireadhaigh","Ó Muireagáin","Ó Muireartaigh","Ó Muireasa","Ó Muiris","Ó Muraíle","Ó Murchú","Ó Murchadha","Ó Murghaile","Ó Murnáin","Ó Murthuile","Ó Néill","Ó Neachtain","Ó Niadh","Ó Nialláin","Ó Niallagáin","Ó Nuadháin","Ó Nualláin","Ó Peatáin","Ó Pléimeann",
    "Ó Ráighne","Ó Ríagaín","Ó Rínn","Ó Ríordáin","Ó Rónáin","Ó Raghailligh","Ó Rathaille","Ó Riáin","Ó Roideacháin","Ó Ruadháin","Ó Ruadhagáin","Ó Ruairc","Ó Ruanaidh","Ó Sé","Ó Síocháin","Ó Síoghraidh","Ó Síoráin","Ó Síthigh","Ó Súilleabháin","Ó Sabháin","Ó Saoraidhe","Ó Scalaidhe","Ó Scannail","Ó Scoireadh","Ó Scolaidhe","Ó Scurra","Ó Seachnasaigh","Ó Seanáin","Ó Seireadáin","Ó Siadhail","Ó Siail","Ó Siochfhradha","Ó Sionúir","Ó Sirideáin","Ó Slatara","Ó Slatiascaigh","Ó Sluagháin","Ó Sluaghadhaigh","Ó Somacháin","Ó Spaelain","Ó Suaird","Ó Suairt","Ó Tíghearnáin","Ó Tíghearnaigh","Ó Taithligh","Ó Tanaidheain","Ó Teamhnainn","Ó Toghda","Ó Tonnaigh","Ó Tuachair","Ó Tuairisc","Ó Tuama","Ó Tuathaigh","Ó Tuathail","Ó Tuathaláin","Ó hÁdhmaill","Ó hÁgáin","Ó hÁileagáin","Ó hÁilgheanáin","Ó hÁirt","Ó hÉamhthaigh","Ó hÉigceartaigh","Ó hÓgáin","Ó hÓisín","Ó hÓsáin","Ó hÚbáin","Ó hAiligheasa","Ó hAiliosa","Ó h-Ailghiusa","Ó hAilmhic","Ó hAimheirgin","Ó hAinbhith","Ó hAinbhthín","Ó hAinifín","Ó hAinle","Ó hAirmheadhaigh","Ó hAllmhuráin","Ó hAlluráin","Ó hAmhsaigh","Ó hAngluinn","Ó hAnnagáin","Ó hAnnaigh","Ó hAnnlúinn","Ó hAnnracháin","Ó hAnrachtaigh","Ó hAnradháin","Ó hAodha","Ó hAodhagáin","Ó hAoileáin","Ó hAonghusa","Ó hAragáin","Ó hArgáin","Ó hArgadáin","Ó hArrachtáin","Ó hArragáin","Ó hArtagáin","Ó hAthairne","Ó hEachach","Ó hEachaidh","Ó hEachthairn","Ó hEadeáin","Ó hEadhra","Ó hEaghráin","Ó hEaghra","Ó hEalaighthe","Ó hEanraig","Ó hEaráin","Ó hEarcáin","Ó hEarchadha","Ó hEarchaidh","Ó hEarghaile","Ó hEidhin","Ó hEidhneacháin","Ó hEidirsceoil","Ó hEimhín","Ó hEireamhóin","Ó hEodhusa","Ó hEoghanáin","Ó hIarfhlatha","Ó hIcí","Ó hIceadh","Ó hIfearnáin","Ó hInreachtaigh","Ó hIonmhaineáin","Ó hIonnghaile","Ó hIorua","Ó hIoruaidh","Ó hOistín","Ó hUainín","Ó hUallacháin","Ó hUiginn","Ó hUrmholtaigh","Ó hUrthuile","Mac Cnáimhsí","Mac Cnaimhín","Mac Crabháin","Mac Gormáin","Ó Cnáimhsí","Ó Cnaimhín","Ó Crabháin","Ó Gormáin","Mac Ámoinn","Mac Éanraic","Mac Íomhair","Mac Adaim","Mac Ailin","Mac Airt","Mac Alasdair","Mac Amhlaidh","Mac Amhlaoibh","Mac Aodha","Mac Aodhagáin","Mac Aoidh","Mac Aonghuis","Mac Aonghusa","Mac Ardghail","Mac Artair","Mac Asgaill","Mac Ausaláin","Mac Bhiadhtaigh","Mac Bhloscaidh","Mac Braoin","Mac Braonáin","Mac Cába","Mac Cárthaigh","Mac Céile","Mac Cú Uladh","Mac Cúg","Mac Cailin","Mac Cairbre","Mac Cana","Mac Canann","Mac Caocháin","Mac Carrghamhna","Mac Cartaine","Mac Cathail","Mac Cathmhaoil","Mac Cearáin","Mac Cearbhaigh","Mac Cearbhaill","Mac Ciaráin","Mac Cinnéide","Mac Cionaodha","Mac Cionnaith","Mac Cluasaigh","Mac Cogadháin","Mac Coilín","Mac Coinnich","Mac Coitir","Mac Colgáin","Mac Colla","Mac Coluim","Mac Con Coille","Mac Con Mhaighe",
    "Mac Con Uladh","Mac Conduibh","Mac Conghaile","Mac Conmara","Mac Conmidhe","Mac Connmhaigh","Mac Consaidín","Mac Conshámha","Mac Cormaic","Mac Corraidh","Mac Cosgair","Mac Críodáin","Mac Craith","Mac Cuairt","Mac Cuarta","Mac Cuilinn","Mac Cuimín","Mac Cuindlis","Mac Cumhaighe","Mac Cumhaill","Mac Daibhéid","Mac Dhabhóg","Mac Dhomhnuill","Mac Dhonnchaidh","Mac Dhuarcáin","Mac Dhubháin","Mac Dhuibh","Mac Dhuibhshíthe","Mac Dhurcáin","Mac Diarmada","Mac Donnchadha","Mac Dubhdara","Mac Dubhghaill","Mac Duibh","Mac Duibhir","Mac Duibhshíthe","Mac Duinnshléibhe","Mac Eacháin","Mac Eachaidh","Mac Eanruig","Mac Eathain","Mac Eochagáin","Mac Eoghain","Mac Eoin","Mac Fheargail","Mac Fhearghaile","Mac Fhearghaill","Mac Fhearraigh","Mac Fhiachra","Mac Fhinghin","Mac Fhiodhbhuidhe","Mac Fhirbhisigh","Mac Fhlannchaidh","Mac Fionnlaigh","Mac Gáibhtheacháin","Mac Géibheannaigh","Mac Géidigh","Mac Gabhann","Mac Gafraidh","Mac Gearailt","Mac Geargáin","Mac Gille","Mac Gille Íosa","Mac Gille Chomhghaill","Mac Gille Comhghain","Mac Gille Dheòradha","Mac Gille Eathain","Mac Gille Fhaoláin","Mac Gille Fhaolain","Mac Gille Fhinneain","Mac Gille Fhionndaig","Mac Gille Fhionntain","Mac Gille Onchon","Mac Gille Uidhir","Mac Giolla","Mac Giolla Íosa","Mac Giolla Bhríde","Mac Giolla Chúda","Mac Giolla Chúille","Mac Giolla Chaillín","Mac Giolla Chathair","Mac Giolla Chlaoin","Mac Giolla Choille","Mac Giolla Choinnigh","Mac Giolla Chomhghaill","Mac Giolla Coileáin","Mac Giolla Comhghaill","Mac Giolla Cuilinn","Mac Giolla Deacair","Mac Giolla Dheóradha","Mac Giolla Dhomhnaigh","Mac Giolla Dhomnaigh","Mac Giolla Duibh","Mac Giolla Eóin","Mac Giolla Easpuig","Mac Giolla Fhaoláin","Mac Giolla Fhionntáin","Mac Giolla Fhionntóg","Mac Giolla Ghuala","Mac Giolla Léigh","Mac Giolla Leith","Mac Giolla Mhártain","Mac Giolla Mhaoil","Mac Giolla Mhuire","Mac Giolla Phádraig","Mac Giolla Phóil","Mac Giolla Riabhaigh","Mac Giolla Rua","Mac Giolla Uidhir","Mac Giolla na Naomh","Mac Giolla t-Seanáin","Mac Giolla-Gheimhridh","Mac Giollagáin","Mac Gobhann","Mac Gofraidh","Mac Gruagáin","Mac Grudaire","Mac Iain","Mac Iomaire","Mac Labhradha","Mac Labhrainn","Mac Laibheartaigh","Mac Leòid","Mac Leanacháin","Mac Liam","Mac Lochlainn","Mac Loinsigh","Mac Loughlin","Mac Lughaidh","Mac Máirtín","Mac Muiris","Mac Maghnus","Mac Maoláin","Mac Mathúna","Mac Mathghamhna","Mac Mhuircheartaigh","Mac Mhuirich","Mac Muircheartaigh","Mac Muireadhaigh","Mac Murchadha","Mac Murchaidh","Mac Naois","Mac Neachtain","Mac Niadh","Mac Niallais","Mac Niocaill","Mac Oilibhéir","Mac Oisdealbhaigh","Mac Oistigín","Mac Phádraig","Mac Pháidín","Mac Phóil","Mac Phaidin","Mac Pharthaláin","Mac Phearais","Mac Philbín","Mac Philib","Mac Piarais","Mac Pilib","Mac Réamoinn","Mac Rúaidh","Mac Raghnaill","Mac Reachtain",
    "Mac Reannacháin","Mac Riabhaigh","Mac Riada","Mac Ruaidhrí","Mac Ruidhrí","Mac Séaghdha","Mac Síomóin","Mac Síthigh","Mac Saoghair","Mac Scalaidhe","Mac Seáin","Mac Seanlaoich","Mac Shitrig","Mac Shuibhne","Mac Somhairle","Mac Taidhg","Mac Thámhais","Mac Thóm","Mac Thaidhg","Mac Thighearnáin","Mac Thomáis","Mac Thréinfhir","Mac Uáid","Mac Uighlilin","Mac Uisdein","Mac Uistein"
};
