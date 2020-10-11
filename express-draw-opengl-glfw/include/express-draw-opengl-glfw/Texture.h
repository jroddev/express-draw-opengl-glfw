
#ifndef INC_2D_PLATFORM_GAME_TEST_TEXTURE_H
#define INC_2D_PLATFORM_GAME_TEST_TEXTURE_H

#include <string>

class Texture {
public:
    Texture(std::string textureFileName);

    int width, height, colorChannels;
    unsigned int textureId; // opengl resource id
    void bind() const;
};


#endif //INC_2D_PLATFORM_GAME_TEST_TEXTURE_H
