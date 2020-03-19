#include "religion.h"
#include "../destinLib/abs/effet.h"
#include "../destinLib/abs/evt.h"
#include "../destinLib/gen/genevt.h"
#include "../destinLib/aleatoire.h"
#include "../destinLib/abs/selectionneurdenoeud.h"
#include "extremis.h"
#include "genviehumain.h"

Religion::Religion(int indexEvt):GenerateurNoeudsProbables (indexEvt)
{
    switch (indexEvt) {
    case 0 : {

    }break;
    }
}


// caracs liées :
QString Religion::C_RELIGION = "Religion";
QString Religion::C_FOI = "Foi"; // niveau de foi dans sa religion (1 à 10)
// valeurs de C_RELIGION "" = aucune
QString Religion::CHRETIEN = ":/images/religion/Chretien.jpg";

std::shared_ptr<Condition> Religion::AjouterCondACetteReligion(QString religion)
{
    return make_shared<Condition>(Religion::C_RELIGION, religion, Comparateur::c_Egal);
}
