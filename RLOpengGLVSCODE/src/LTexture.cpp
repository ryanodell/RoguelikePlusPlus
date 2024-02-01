#include "LTexture.h"
LTexture::LTexture() {
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture() {
    free();
}

bool LTexture::loadFromFile(const char *path) {

    return false;
}

void LTexture::render(int x, int y) {

}

void LTexture::free() {
}
