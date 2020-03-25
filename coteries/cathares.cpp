#include "cathares.h"
#include "genviehumain.h"
#include "religion/religion.h"
#include "humain.h"
#include "../destinLib/aleatoire.h"
#include "../destinLib/abs/univers.h"

using std::make_shared;
using std::shared_ptr;

Cathares::Cathares()
{
    GenererTraitCompatibles();
}

void Cathares::GenererTraitCompatibles()
{
    m_TraitsCompatible = {
        make_shared<Trait>(eTrait::altruiste),
        make_shared<Trait>(eTrait::sens_du_sacrifice),
        make_shared<Trait>(eTrait::sens_du_groupe),
        make_shared<Trait>(eTrait::pacifiste),
        make_shared<Trait>(eTrait::faible)
    };
    m_TraitsIncompatible = {
        make_shared<Trait>(eTrait::cupide),
        make_shared<Trait>(eTrait::industrieux),
        make_shared<Trait>(eTrait::ambitieux),
        make_shared<Trait>(eTrait::jouisseur)
    };
}

QString Cathares::GetNom()
{
    return "Cathares";
}

QString Cathares::GetDescription()
{
    return "Description des Cathares";
}

float Cathares::GetPoidsDemo()
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

    // enfermé en cellule
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
        if ( humain->GetValeurCarac(Trait::GetNomTrait(eTrait::rancunnier)) != "" ) {
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

    // effetVide
    shared_ptr<Effet> effetVide = genHist->AjouterEffetNarration(
                "effetVide temp.",
                ":/images/cathares/apprend_lit.jpg",
                "", evt);
    effet1->m_GoToEffetId = go_to_effet_suivant;
    shared_ptr<Condition> condVide = make_shared<Condition>(1.0, TypeProba::p_Relative);
    shared_ptr<NoeudProbable> noeudVide = make_shared<NoeudProbable>(
                effetVide,
                condVide);
    noeudsProbaEducation.push_back(noeudVide);

    shared_ptr<Effet> effetSelecteur = genHist->m_GenerateurEvt->AjouterEffetSelecteurDEvt(
                noeudsProbaEducation);
    effetSelecteur->m_MsChrono = 1; // passé automatiquement

    return effetSelecteur;
}


QString Cathares::GetId()
{
    return Coterie::CATHARES;
}
