#include "trait.h"

Trait::Trait(eTrait trait):m_eTrait(trait)
{

}

QString Trait::GetNom()
{
    switch (m_eTrait) {
    case sens_du_groupe: return "Sens du groupe";
    case sens_du_sacrifice: return "Sens du sacrifice";
    case cupide: return "Cupide";
    case honneur: return "Honneur";
    case fort: return "Fort";
    case spirituel: return "Spirituel";
    case opportuniste: return "Opportuniste";
    case sournois: return "Sournois";
    case faible: return "Faible";
    case nature: return "Nature";
    case franc: return "France";
    case industrieux: return "Industrieux";
    case violent: return "Violent";
    case resistant: return "Résistant";
    case pragmatique: return "Pragmatique";
    case simple: return "Simple";
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
    case nb_Traits: return "??????????";
    }

     return "Trait au nom non ajouté";
}
