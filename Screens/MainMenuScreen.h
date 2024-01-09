#ifndef MAINMENUSCREEN_H_INCLUDED
#define MAINMENUSCREEN_H_INCLUDED
#include "ScreenBase.h"

class MainMenuScreen : public ScreenBase {
public:
    void OnLoad() const override;
    void Update(int frame) const override;
    void Draw(int frame) const override;
};

#endif // MAINMENUSCREEN_H_INCLUDED
