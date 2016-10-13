#ifndef CASINOGAMESWIDGETDELEGATEQML_H
#define CASINOGAMESWIDGETDELEGATEQML_H

#include <string>

class CNativeButtonQml;
class CCasinoGamesWidgetDelegateQML
{
public:
    CCasinoGamesWidgetDelegateQML();
    virtual void onSomeButtonClicked(CNativeButtonQml *pWidget, const std::string &sParam) = 0;
};

#endif // CASINOGAMESWIDGETDELEGATEQML_H
