#include <iostream>
#include <windows.h>

const int screenWidth = 80;
const int screenHeight = 25;

CHAR_INFO buffer1[screenWidth * screenHeight];
CHAR_INFO buffer2[screenWidth * screenHeight];

HANDLE consoleHandle;

void InitializeBuffers() {
    // Initialize buffer contents if needed
    for (int i = 0; i < screenWidth * screenHeight; ++i) {
        buffer1[i].Char.AsciiChar = '@';
        buffer1[i].Attributes = FOREGROUND_GREEN;  // Adjust attributes as needed

        buffer2[i].Char.AsciiChar = '1';
        buffer2[i].Attributes = FOREGROUND_RED;  // Adjust attributes as needed
    }
}

void UpdateBuffer(CHAR_INFO* buffer) {
    // Implement your game logic to update the buffer content
    // ...
}

void RenderBuffer(HANDLE bufferHandle, CHAR_INFO* buffer) {
    COORD bufferSize = { static_cast<SHORT>(screenWidth), static_cast<SHORT>(screenHeight) };
    COORD bufferCoord = { 0, 0 };
    SMALL_RECT writeRegion = { 0, 0, static_cast<SHORT>(screenWidth - 1), static_cast<SHORT>(screenHeight - 1) };

    // Write the content of the buffer to the active screen buffer
    WriteConsoleOutput(bufferHandle, buffer, bufferSize, bufferCoord, &writeRegion);
}

int main() {
    consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    // Create two console screen buffers
    HANDLE buffer1Handle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    HANDLE buffer2Handle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

    // Set the active buffer
    SetConsoleActiveScreenBuffer(buffer1Handle);

    // Set initial buffer handles
    HANDLE currentBufferHandle = buffer1Handle;
    HANDLE nextBufferHandle = buffer2Handle;

    InitializeBuffers();  // Initialize buffer contents
    bool bufferToggle = true;
    while (true) {
        // Update the content in the non-active buffer (background)
        //UpdateBuffer(buffer2);

        // Swap the buffer handles
        std::swap(currentBufferHandle, nextBufferHandle);

        // Set the active buffer
        SetConsoleActiveScreenBuffer(nextBufferHandle);

        // Render the content of the new active buffer
        if(bufferToggle == true) {
            RenderBuffer(nextBufferHandle, buffer1);
            bufferToggle = false;
        }
        else {
            RenderBuffer(nextBufferHandle, buffer2);
            bufferToggle = true;
        }
        //bufferToggle != bufferToggle;
        Sleep(5);
    }

    // Close the console screen buffers when done
    CloseHandle(buffer1Handle);
    CloseHandle(buffer2Handle);

    return 0;
}
