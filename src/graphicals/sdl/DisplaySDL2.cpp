/*
** EPITECH PROJECT, 2022
** sdl
** File description:
** DisplaySDL2.cpp
*/

#include "DisplaySDL2.hpp"

extern "C"
{
    GUI::IDisplayModule *entry_point()
    {
        return new GUI::DisplaySDL2();
    };
}


GUI::DisplaySDL2::DisplaySDL2()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS);
    TTF_Init();
    _font = TTF_OpenFont("assets/fonts/Montserrat-Regular.ttf", 20);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    _mapspecs = {0, 0, 0, 0};
    _pxpu = 5;
}

GUI::DisplaySDL2::~DisplaySDL2()
{
    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    TTF_CloseFont(_font);
    closeWindow();
    TTF_Quit();
    Mix_CloseAudio();
    SDL_Quit();
}

void GUI::DisplaySDL2::setUnits(const int &pxpu)
{
    _pxpu = pxpu;
}

int GUI::DisplaySDL2::getUnits() const
{
    return _pxpu;
}

void GUI::DisplaySDL2::setMapSpecs(mapSpecs_t mapspecs)
{
    _mapspecs = mapspecs;
}

void GUI::DisplaySDL2::playSound(const std::string &label, const bool &loop)
{
    if (loop)
        Mix_PlayMusic(_sounds[label], -1);
    else
        Mix_PlayMusic(_sounds[label], 1);
}

void GUI::DisplaySDL2::loadSound(const std::string &label, const std::string &path)
{
    _sounds[label] = Mix_LoadMUS(path.c_str());
}

void GUI::DisplaySDL2::setWindowSize(const int &w, const int &h)
{
    SDL_SetWindowSize(_window, w * _pxpu, h * _pxpu);
}

void GUI::DisplaySDL2::openWindow(const int &w, const int &h)
{
    _window = SDL_CreateWindow("Arcade", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w * _pxpu, h * _pxpu, SDL_WINDOW_SHOWN);
    _renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
}

void GUI::DisplaySDL2::closeWindow()
{
    SDL_DestroyWindow(_window);
}

void GUI::DisplaySDL2::clearScr()
{
    SDL_RenderClear(_renderer);
}

SDL_Color GUI::DisplaySDL2::getColor(const color_t &color) const
{
    switch (color)
    {
    case GUI::IDisplayModule::BLACK:
        return {0, 0, 0, 255};
    case GUI::IDisplayModule::WHITE:
        return {255, 255, 255, 255};
    case GUI::IDisplayModule::RED:
        return {255, 0, 0, 255};
    case GUI::IDisplayModule::GREEN:
        return {0, 255, 0, 255};
    case GUI::IDisplayModule::BLUE:
        return {0, 0, 255, 255};
    case GUI::IDisplayModule::YELLOW:
        return {255, 255, 0, 255};
    case GUI::IDisplayModule::MAGENTA:
        return {255, 0, 255, 255};
    case GUI::IDisplayModule::CYAN:
        return {0, 255, 255, 255};
    default:
        return {0, 0, 0, 255};
    }
}

void GUI::DisplaySDL2::draw()
{
    for (auto texts : _texts) {
        SDL_Surface *surface = TTF_RenderText_Blended(_font, texts.second.str.c_str(), getColor(texts.second.color));
        SDL_Texture *texture = SDL_CreateTextureFromSurface(_renderer, surface);
        SDL_Rect rect = {texts.second.x * _pxpu, texts.second.y * _pxpu, surface->w, surface->h};
        SDL_RenderCopy(_renderer, texture, NULL, &rect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }
    for (auto pixels : _pixels) {
        SDL_Rect rect = {pixels.x * _pxpu, pixels.y * _pxpu, _pxpu, _pxpu};
        SDL_SetRenderDrawColor(_renderer, pixels.deltaRGB.r, pixels.deltaRGB.g, pixels.deltaRGB.b, 0);
        SDL_RenderFillRect(_renderer, &rect);
    }
    SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
    SDL_RenderPresent(_renderer);
}

void GUI::DisplaySDL2::updatePixels(std::vector<pixel_t> pixels)
{
    _pixels = pixels;
}

std::vector<GUI::IDisplayModule::event_t> GUI::DisplaySDL2::pollEvents()
{
    time_t now = time(nullptr);
    std::vector<GUI::IDisplayModule::event_t> events;
    while (SDL_PollEvent(&_event)) {
        switch (_event.type) {
            case SDL_QUIT:
                events.push_back({GUI::IDisplayModule::QUIT, (float)difftime(_lastTime, now), {}, {}});
                std::cout << "Closing window..." << std::endl;
                break;
            case SDL_MOUSEBUTTONDOWN:
                events.push_back({GUI::IDisplayModule::MOUSE_CLICK, (float)difftime(_lastTime, now), {static_cast<float>(_event.button.x), static_cast<float>(_event.button.y)}, {}});
                break;
            case SDL_KEYDOWN:
                switch (_event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        events.push_back({GUI::IDisplayModule::QUIT, (float)difftime(_lastTime, now), {}, {}});
                        break;
                    case SDLK_UP:
                        events.push_back({GUI::IDisplayModule::UP, (float)difftime(_lastTime, now), {}, {}});
                        break;
                    case SDLK_DOWN:
                        events.push_back({GUI::IDisplayModule::DOWN, (float)difftime(_lastTime, now), {}, {}});
                        break;
                    case SDLK_LEFT:
                        events.push_back({GUI::IDisplayModule::LEFT, (float)difftime(_lastTime, now), {}, {}});
                        break;
                    case SDLK_RIGHT:
                        events.push_back({GUI::IDisplayModule::RIGHT, (float)difftime(_lastTime, now), {}, {}});
                        break;
                    case SDLK_BACKSPACE:
                        events.push_back({GUI::IDisplayModule::BACKSPACE, (float)difftime(_lastTime, now), {}, {}});
                        break;
                    default:
                        events.push_back({GUI::IDisplayModule::KEYCODE, (float)difftime(_lastTime, now), {}, {}});
                }
                break;
            default:
                break;
        }
    }
    return events;
}

void GUI::DisplaySDL2::setText(std::string label, text_t text)
{
    _texts[label] = text;
}