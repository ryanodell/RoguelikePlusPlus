#ifndef RENDERMANAGER_H_INCLUDED
#define RENDERMANAGER_H_INCLUDED

struct RenderUnit {
public:
    int X, Y;
    char Character;
    unsigned char Color;
};

class RenderManager {
public:
    RenderManager(const RenderManager&) = delete;
    static RenderManager& Get();
    //static eInputAction GetInput() { return Get().IGetInput(); }

private:
    RenderManager() {}
    //eInputAction IGetInput();

private:
//eInputAction m_inputAction = NONE;
};

#endif // RENDERMANAGER_H_INCLUDED
