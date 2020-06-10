#include "trait.h"
#include "../destinLib/aleatoire.h"
#include "../destinLib/abs/condition.h"
#include "../destinLib/abs/effet.h"
#include "../destinLib/abs/evt.h"
#include "../destinLib/gen/genevt.h"
#include "../destinLib/abs/selectionneurdenoeud.h"
#include "extremis.h"
#include "genviehumain.h"
#include "humain.h"

using std::make_shared;
using std::shared_ptr;

Trait::Trait(eTrait trait):m_eTrait(trait)
{}

QString Trait::GetNom()
{
    switch (m_eTrait) {
    case sens_du_groupe:    return "Sens du groupe";
    case pervers_sexuel:    return "Pervers sexuel";
    case sens_du_sacrifice: return "Sens du sacrifice";
    case cupide:            return "Cupide";
    case honorable:         return "Honorable";
    case menteur:           return "Menteur";
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
    case maigre:         return "Maigre";
    case gros:         return "Gros";
    case rancunier:        return "Rancunier";
    case observateur:        return "Observateur";
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
    case cruel: return "Cruel";
    case pacifiste: return "Pacifiste";
    case angoisse: return "Angoissé";
    case empathique: return "Empathique";
    case egoiste: return "Égoïste";
    case paresseux: return "Paresseux";
    case travailleur: return "Travailleur";
    case charmeur: return "Charmeur";
    case nb_Traits: return "??????????";
    }

     return "Trait au nom non ajouté";
}


void Trait::AjouterGagneTraitSelonProba(Humain* hum, std::shared_ptr<Effet> effet, eTrait trait, double proba)
{
    double res = Aleatoire::GetAl()->Entre0Et1();
    if ( res <= proba) {
        effet->m_Texte += "\nVous devenez " + Trait::GetNomTrait(trait) + ".";
        hum->SetValeurACaracId(Trait::GetNomTrait(trait), "1");
        hum->SetValeurACaracId(Trait::GetNomTrait(Trait::GetTraitOppose(trait)), "");
    }
}

void Trait::AjouterGagneTraitSelonProba(std::shared_ptr<Effet> effet, eTrait trait, double proba)
{
    double res = Aleatoire::GetAl()->Entre0Et1();
    if ( res <= proba) {
        effet->m_Texte += "\nVous devenez " + Trait::GetNomTrait(trait) + ".";
        effet->AjouterChangeurDeCarac(Trait::GetNomTrait(trait), "1");
        effet->AjouterChangeurDeCarac(Trait::GetNomTrait(Trait::GetTraitOppose(trait)), "");
    }
}

void Trait::AjouterPerdTraitSelonProba(std::shared_ptr<Effet> effet, eTrait trait, double proba)
{
    double res = Aleatoire::GetAl()->Entre0Et1();
    if ( res <= proba) {
        effet->m_Texte += "\nVous perdez '" + Trait::GetNomTrait(trait) + "'.";
        effet->AjouterChangeurDeCarac(Trait::GetNomTrait(trait), "");
    }
}

void Trait::AjouterPerdTraitSelonProba(Humain* hum, std::shared_ptr<Effet> effet, eTrait trait, double proba)
{
    if ( hum->ACeTrait(trait)) {
        double res = Aleatoire::GetAl()->Entre0Et1();
        if ( res <= proba) {
            effet->m_Texte += "\nVous perdez '" + Trait::GetNomTrait(trait) + "'.";
            hum->SetValeurACaracId(Trait::GetNomTrait(trait), "");
        }
    }
}


QMap<eTrait, shared_ptr<Trait>> Trait::TOUS_LES_TRAITS;


shared_ptr<Trait> Trait::GetTrait(eTrait etrait)
{
    if ( !Trait::TOUS_LES_TRAITS.contains(etrait))
        Trait::TOUS_LES_TRAITS.insert(etrait, make_shared<Trait>(etrait));
    return Trait::TOUS_LES_TRAITS[etrait];
}

QString Trait::GetNomTrait(eTrait etrait)
{
    return Trait::GetTrait(etrait)->GetNom();
}

shared_ptr<Condition> Trait::GenConditionSiACeTrait(eTrait trait)
{
    return make_shared<Condition>(Trait::GetNomTrait(trait), "1", Comparateur::c_Egal );
}

shared_ptr<Condition> Trait::GenConditionSiAPasCeTrait(eTrait trait)
{
    return make_shared<Condition>(Trait::GetNomTrait(trait), "1", Comparateur::c_Different );
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
    case pervers_sexuel: break;
    case sens_du_sacrifice: break;
    case cupide: break;
    case honorable: return menteur;
    case menteur: return honorable;
    case fort: return faible;
    case spirituel: break;
    case opportuniste: break;
    case sournois: return franc;
    case faible: return fort;
    case nature: break;
    case franc: return sournois;
    case industrieux: break;
    case maigre:       return gros;
    case gros:       return maigre;
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
    case altruiste: return egoiste;
    case cruel: return empathique;
    case egoiste: return altruiste;
    case empathique: return cruel;
    case angoisse: break;
    case charmeur: break;
    case observateur: break;
    case rancunier: break;
    case pacifiste: return violent;
    case paresseux: return travailleur;
    case travailleur: return paresseux;
    case nb_Traits: break;
    }

    return nb_Traits;// utilisé comme "retour invalide"
}


bool Trait::PeutEtrePrisALaNaissance()
{
    switch (m_eTrait) {
    case pervers_sexuel :
    case sens_du_groupe :
    case sens_du_sacrifice:
    case patriarcal:
    case patriote:
    case pacifiste:
        return false;
    default:
        return true;
    }
}

std::shared_ptr<Trait> Trait::GetTrait(QVector<eTrait> &m_TraitsDejaPossedes, bool traitDeNaissance)
{
    bool trouve = false;
    eTrait enumTrait;
    shared_ptr<Trait> trait;
    while (!trouve) {
        enumTrait = static_cast<eTrait>(Aleatoire::GetAl()->EntierInferieurA(eTrait::nb_Traits));
        trouve = ( m_TraitsDejaPossedes.indexOf(enumTrait) == -1);// pas deux fois le même
        if ( trouve)
        {
            trouve = ( m_TraitsDejaPossedes.indexOf(GetTraitOppose(enumTrait)) == -1);// pas un trait opposé à un déjà tiré
        }
        trait = Trait::GetTrait(enumTrait);
        if ( traitDeNaissance && !trait->PeutEtrePrisALaNaissance()) {
            trouve = false;
        }
    }
    return trait;
}

TraitEffets::TraitEffets(int indexEvt):GenerateurNoeudsProbables (indexEvt)
{
    double modificateur = 0.0;
    switch (indexEvt) {
    case 0 : {
        m_Nom = "jouisseur grossit";
        m_ConditionSelecteurProba = make_shared<Condition>(0.03 + modificateur, p_Relative);
        m_Description = "Vos excès en tout genre vous font grossir.";
        m_ModificateursCaracs[Trait::GetNomTrait(gros)] = "1";
        m_ModificateursCaracs[Trait::GetNomTrait(maigre)] = "";
        m_Conditions.push_back(Trait::GenConditionSiACeTrait(jouisseur));
    }break;
    }
}
