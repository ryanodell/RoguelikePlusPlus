#include "InputManager.h"

InputManager& InputManager::Get() {
    static InputManager instance;
    return instance;
}

eInputAction InputManager::IGetInput() {
    //char key = 0;
    //while (!_kbhit()) { }
    char key = getch();
    switch (key) {
       case 'w':
           m_inputAction = UP;
           break;
       case 'a':
           m_inputAction = LEFT;
           break;
       case 's':
           m_inputAction = DOWN;
           break;
       case 'd':
           m_inputAction = RIGHT;
           break;
       case 'k':
           m_inputAction = QUIT;
           break;
       default:
           m_inputAction = NONE;
           break;
    }
    return m_inputAction;
}
