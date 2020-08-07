#include "graphics.h"

Graphics::Graphics(std::string title, Uint32 fullscreenFlag, std::string fontPath,
                   unsigned int screenWidth, unsigned int screenHeight, 
                   unsigned int numRows, unsigned int numCols) 
    : title{title}, fullscreen{fullscreenFlag}, 
    screenWidth{screenWidth}, screenHeight{screenHeight}, 
    numRows{numRows}, numCols{numCols} {

    window = nullptr;
    renderer = nullptr;
    font = nullptr;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
    } else {
        window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
        SDL_SetWindowFullscreen(window, fullscreen);
        if (window == nullptr) {
            std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        } else {
            renderer = SDL_CreateRenderer(window, -1, 0);
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            if (TTF_Init() == -1) {
                std::cerr << "TTF initialization failed: " << TTF_GetError() << std::endl;
            } else {
                font = TTF_OpenFont(fontPath.c_str(), 36);
                if (font == nullptr) {
                    std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
                }
            }
        }
    }

    preBuffer = std::vector<std::vector<Buffer>>(numRows);
    for (int i = 0; i < numRows; ++i) {
        preBuffer[i] = std::vector<Buffer>(numCols);
        for (int j = 0; j < numCols; ++j) {
            preBuffer[i][j] = {' ', 255, 255, 255, 255, 0, 0, 0, 255};
        }
    }

    textDisplay = std::vector<std::vector<std::shared_ptr<Texture>>>(numRows);
    for (int i = 0; i < numRows; ++i) {
        textDisplay[i] = std::vector<std::shared_ptr<Texture>>(numCols);
        for (int j = 0; j < numCols; ++j) {
            textDisplay[i][j] = std::make_shared<Texture>(screenWidth/numCols, screenHeight/numRows);
            textDisplay[i][j]->loadFromText(renderer, std::string(1, preBuffer[i][j].ch), font);
            textDisplay[i][j]->setBlendMode(SDL_BLENDMODE_BLEND);
            textDisplay[i][j]->setPosition(j*(screenWidth/numCols), i*(screenHeight/numRows));
        }
    }
}

void Graphics::setCh(char ch, unsigned int x, unsigned int y) {
    if (x < numCols && y < numRows) {
        preBuffer[y][x].ch = ch;
    }
}

void Graphics::setForeColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a, int x, int y) {
    if (x < numCols && y < numRows) {
        preBuffer[y][x].r = r;
        preBuffer[y][x].g = g;
        preBuffer[y][x].b = b;
        preBuffer[y][x].a = a;
    }
}

void Graphics::setBackColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a, int x, int y) {
    if (x < numCols && y < numRows) {
        preBuffer[y][x].br = r;
        preBuffer[y][x].bg = g;
        preBuffer[y][x].bb = b;
        preBuffer[y][x].ba = a;
    }
}

void Graphics::importTxt(std::string filename, bool transparent) {
    std::string line;
    std::ifstream infile {filename};
    if (infile.is_open()) {
        int row = 0;
        while (std::getline(infile, line)) {
            int len = line.length();
            if (row < numRows) {
                for (int i = 0; i < len && i < numCols; ++i) {
                    if (!transparent || (transparent && line[i] != ' ')) {
                        preBuffer[row][i] = {
                            line[i],
                            255, 255, 255, 255,
                            0, 0, 0, 255};
                    }
                }
                ++row;
            }
            
        }
    } else {
        std::cerr << "Could not open file " << filename << std::endl;
    }
}

void Graphics::write(std::string content, int x, int y) {
    if (x >= numCols || y >= numRows) {
        return;
    }
    int len = content.length();
    for (int i = 0; i < len && x + i < numCols; ++i) {
        preBuffer[y][x + i] = {content[i], 255, 255, 255, 255, 0, 0, 0, 255};
    }
}

void Graphics::write(std::string content, int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    if (x >= numCols || y >= numRows) {
        return;
    }
    int len = content.length();
    for (int i = 0; i < len && x + i < numCols; ++i) {
        preBuffer[y][x + i] = {content[i], r, g, b, a, 0, 0, 0, 255};
    }
}

void Graphics::writeln(std::string content, int x, int y, int width) {
    if (x >= numCols || y >= numRows) {
        return;
    }
    int len = content.length();
    int j = 0;
    for (int i = 0; i < len; ++i) {
        preBuffer[y][x + j] = {content[i], 255, 255, 255, 255, 0, 0, 0, 255};
        ++j;
        if (j == numCols || j == width) {
            ++y;
            j = 0;
        }
    }
}

void Graphics::writeln(std::string content, int x, int y, int width, Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
    if (x >= numCols || y >= numRows) {
        return;
    }
    int len = content.length();
    int j = 0;
    for (int i = 0; i < len; ++i) {
        preBuffer[y][x + j] = {content[i], r, g, b, a, 0, 0, 0, 255};
        ++j;
        if (j == numCols || j == width) {
            ++y;
            j = 0;
        }
    }
}

unsigned int Graphics::getScreenWidth() const { return screenWidth; }

unsigned int Graphics::getScreenHeight() const { return screenHeight; }

unsigned int Graphics::getScreenRows() const { return numRows; }

unsigned int Graphics::getScreenCols() const { return numCols; }

Graphics::~Graphics() {
    TTF_CloseFont(font);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

void Graphics::clear() {
    SDL_RenderClear(renderer);
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            preBuffer[i][j] = {' ', 255, 255, 255, 255, 0, 0, 0, 255};
        }
    }
}

void Graphics::render() {
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            textDisplay[i][j]->setBackColor(preBuffer[i][j].br, preBuffer[i][j].bg, preBuffer[i][j].bb, preBuffer[i][j].ba);
            textDisplay[i][j]->setForeColor(preBuffer[i][j].r, preBuffer[i][j].g, preBuffer[i][j].b, preBuffer[i][j].a);
            textDisplay[i][j]->loadFromText(renderer, std::string(1, preBuffer[i][j].ch), font);
            textDisplay[i][j]->setBlendMode(SDL_BLENDMODE_BLEND);
            textDisplay[i][j]->render(renderer);
        }
    }
    SDL_RenderPresent(renderer);
}