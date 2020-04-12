#ifndef CARACPNJ_H
#define CARACPNJ_H

#include "../destinLib/abs/carac.h"
#include <memory>

class PNJ;

class CaracPNJ : public Carac
{
public:
    CaracPNJ(QString prefixe, QString intitule);

    std::shared_ptr<PNJ> m_Pnj;

    virtual bool bAffichable();
    QString GetPrefixe();
    virtual bool AfficherValeur();
    virtual bool AfficherIntitule();
};

#endif // CARACPNJ_H
