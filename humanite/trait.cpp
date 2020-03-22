#include "trait.h"
#include "../destinLib/aleatoire.h"
#include "../destinLib/abs/condition.h"
#include "../destinLib/abs/effet.h"

using std::make_shared;
using std::shared_ptr;

Trait::Trait(eTrait trait):m_eTrait(trait)
{}

QString Trait::GetNom()
{
    switch (m_eTrait) {
    case sens_du_groupe:    return "Sens du groupe";
    case sens_du_sacrifice: return "Sens du sacrifice";
    case cupide:            return "Cupide";
    case honorable:         return "Honorable";
    case fort:              return "Fort";
    case spirituel:         return "Spirituel";
    case opportuniste:      return "Opportuniste";
    case sournois:          return "Sournois";
    case faible:            return "Faible";
    case nature:            return "Nature";
    case franc:             return "Franc";
    case chetif:            return "Chétif";
    case maladroit:         return "Maladroit";
    case industrieux:       return "Industrieux";
    case bete:              return "Bête";
    case violent:           return "Violent";
    case resistant:         return "Résistant";
    case rancunnier:        return "Rancunier";
    case pragmatique:       return "Pragmatique";
    case simple:            return "Simple";
    case intellectuel: return "Intellectuel";
    case grand: return "Grand";
    case beau: return "Beau";
    case intelligent: return "Intelligent";
    case artiste: return "Artiste";
    case sensible: return "Sensible";
    case habile: return "Habile";
    case petit: return "Petit";
    case laid: return "Laid";
    case patriarcal: return "Patriarcal";
    case patriote: return "Patriote";
    case jouisseur: return "Jouisseur";
    case ambitieux: return "Ambitieux";
    case aventureux: return "Aventureux";
    case altruiste: return "Altruiste";
    case pacifiste: return "Pacifiste";
    case angoisse: return "Angoissé";
    case paresseux: return "Paresseux";
    case travailleur: return "Travailleur";
    case nb_Traits: return "??????????";
    }

     return "Trait au nom non ajouté";
}

QString Trait::GetNomTrait(eTrait etrait)
{
    return (make_shared<Trait>(etrait))->GetNom();
}

void Trait::AjouterConditionSiACeTrait(shared_ptr<Effet> effet, eTrait trait)
{
    effet->AjouterCondition(Trait::GetNomTrait(trait), Comparateur::c_Egal, "1");
}

void Trait::AjouterConditionSiAPasCeTrait(shared_ptr<Effet> effet, eTrait trait)
{
    effet->AjouterCondition(Trait::GetNomTrait(trait), Comparateur::c_Egal, "");
}

void Trait::AjouterModifProbaSiACeTrait(Condition* CondProba, double proba, eTrait trait)
{
    CondProba->AjouterModifProba(proba, {
                                make_shared<Condition>(Trait::GetNomTrait(trait), "1", Comparateur::c_Egal)
                            });
}

eTrait Trait::GetTraitOppose(eTrait etrait)
{
    switch (etrait) {
    case sens_du_groupe: break;
    case sens_du_sacrifice: break;
    case cupide: break;
    case honorable: break;
    case fort: return faible;
    case spirituel: break;
    case opportuniste: break;
    case sournois: return franc;
    case faible: return fort;
    case nature: break;
    case franc: return sournois;
    case industrieux: break;
    case violent:       return pacifiste;
    case resistant:     return chetif;
    case chetif:        return resistant;
    case pragmatique: break;
    case simple: return intellectuel;
    case intellectuel: return simple;
    case grand: return petit;
    case beau: return laid;
    case intelligent:   return bete;
    case bete:          return intelligent;
    case artiste: break;
    case sensible: break;
    case habile:        return maladroit;
    case maladroit:     return habile;
    case petit: return grand;
    case laid: return beau;
    case patriarcal: break;
    case patriote: break;
    case jouisseur: break;
    case ambitieux: break;
    case aventureux: break;
    case altruiste: break;
    case angoisse: break;
    case rancunnier: break;
    case pacifiste: return violent;
    case paresseux: return travailleur;
    case travailleur: return paresseux;
    case nb_Traits: break;
    }

    return nb_Traits;// utilisé comme "retour invalide"
}

std::shared_ptr<Trait> Trait::GetTrait(QVector<eTrait> &m_TraitsDejaPossedes)
{
    bool trouve = false;
    eTrait enumTrait;
    while (!trouve) {
        enumTrait = static_cast<eTrait>(Aleatoire::GetAl()->EntierInferieurA(eTrait::nb_Traits));
        trouve = ( m_TraitsDejaPossedes.indexOf(enumTrait) == -1);// pas deux fois le même
        if ( trouve)
        {
            trouve = ( m_TraitsDejaPossedes.indexOf(GetTraitOppose(enumTrait)) == -1);// pas un trait opposé à un déjà tiré
        }
    }
    shared_ptr<Trait> trait = make_shared<Trait>(enumTrait);
    return trait;
}
