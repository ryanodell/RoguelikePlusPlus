#ifndef SCREENBASE_H_INCLUDED
#define SCREENBASE_H_INCLUDED
#include "../Managers/RenderManager.h"

class ScreenBase {
public:
    virtual void OnLoad() const;
    virtual void Update(int frame) const;
    virtual void Draw(int frame) const;
};

#endif // SCREENBASE_H_INCLUDED
