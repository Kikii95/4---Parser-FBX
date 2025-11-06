#include <iostream>
#include <fstream>
#include <SFML/Graphics.hpp>

struct __attribute__((__packed__)) BMPFileHeader {
    unsigned char fileMarker[2];
    unsigned int size;
    uint16_t unused1;
    uint16_t unused2;
    unsigned int imageDataOffset;
};

struct __attribute__((__packed__)) BMPInfoHeader {
    unsigned int size;
    int width;
    int height;
    uint16_t planes;
    uint16_t bitByPixel;
    unsigned int bitCompression;
    unsigned int bitSizeImage;
    int bitPerMeterX;
    int bitPerMeterY;
    unsigned int colorUsed;
    unsigned int colorImportant;
};

struct __attribute__((__packed__)) BMPPixel {
    unsigned char b;
    unsigned char g;
    unsigned char r;
};

struct __attribute__((__packed__)) BMPHeaders {
    BMPFileHeader file;
    BMPInfoHeader info;
};

struct __attribute__((__packed__)) SFMLPixel {
    unsigned char b;
    unsigned char g;
    unsigned char r;
    unsigned char a;
};

int main() {
    sf::RenderWindow win(sf::VideoMode({800, 600}), "BMP");

    std::ifstream fs;
    fs.open("assets/chat.bmp", std::ios::binary | std::ios::in);

    BMPHeaders bh;
    fs.read(reinterpret_cast<char *>(&bh), sizeof(BMPHeaders));

    if (bh.info.bitByPixel != 24) {
        std::cout << "BMP: only handle 24bit color." << std::endl;
        exit(1);
    }

    BMPPixel pixels[bh.info.width * bh.info.height];

    fs.seekg(bh.file.imageDataOffset);
    fs.read(reinterpret_cast<char *>(pixels), sizeof(pixels));

    SFMLPixel texturePixel[bh.info.width * bh.info.height];

    for (int i = 0; i < bh.info.width * bh.info.height; ++i) {
        texturePixel[bh.info.width * bh.info.height-i-1] = {pixels[i].r, pixels[i].g, pixels[i].b, 255};
    }

    sf::Texture tex(sf::Vector2u{(u_int32_t)bh.info.width, (u_int32_t)bh.info.height});
    tex.update(reinterpret_cast<uint8_t*>(texturePixel));
    sf::Sprite s(tex);

    while (win.isOpen()) {
        while (const std::optional event = win.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                win.close();
        }

        win.clear(sf::Color::Black);
        win.draw(s);
        win.display();
    }

    return 0;
}
