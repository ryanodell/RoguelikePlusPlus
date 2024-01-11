#ifndef OVERWORLDSCREEN_H_INCLUDED
#define OVERWORLDSCREEN_H_INCLUDED
#include "ScreenBase.h"
#include <iostream>

class OverworldScreen : public ScreenBase {
    void OnLoad() const override;
    void Update(int frame) const override;
    void Draw(int frame) const override;
};


#endif // OVERWORLDSCREEN_H_INCLUDED
