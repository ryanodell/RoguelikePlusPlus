#ifndef INPUTMANAGER_H_INCLUDED
#define INPUTMANAGER_H_INCLUDED
#include "../Enums.h"
#include <iostream>
#include <windows.h>
#include <conio.h>

class InputManager {
public:
    InputManager(const InputManager&) = delete;
    static InputManager& Get();
    static eInputAction GetInput() { return Get().IGetInput(); }

private:
    InputManager() {}
    eInputAction IGetInput();

private:
    eInputAction m_inputAction = NONE;
};
#endif // INPUTMANAGER_H_INCLUDED
