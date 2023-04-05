/*
** EPITECH PROJECT, 2022
** sdl
** File description:
** DisplaySDL2.hpp
*/

#ifndef AAE0EF63_1E8B_400B_B5FF_667C035B734D
#define AAE0EF63_1E8B_400B_B5FF_667C035B734D

#include <SDL2/SDL.h>
#include <ctime>
#include <iostream>
#include <map>
#include <vector>
#include "IDisplayModule.hpp"
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

namespace GUI
{
    class DisplaySDL2 : public IDisplayModule {
      private:
        int _pxpu;
        SDL_Window *_window;
        SDL_Renderer *_renderer;
        SDL_Event _event;
        mapSpecs_t _mapspecs;
        std::map<std::string, text_t> _texts;
        std::map<std::string, Mix_Music *> _sounds;
        time_t _lastTime;
        TTF_Font *_font;
        std::vector<pixel_t> _pixels;

      public:
        DisplaySDL2();
        ~DisplaySDL2();
        void setUnits(const int &pxpu) override;
        /**
         * @brief Get the Units object
         * @return int
        */
        int getUnits() const override;
        /**
         * @brief Set the Map Specs object
         * @param mapspecs specs of the map
        */
        void setMapSpecs(mapSpecs_t mapspecs) override;
        std::vector<event_t> pollEvents() override;
        void loadSound(
            const std::string &label, const std::string &path) override;
        void playSound(
            const std::string &label, const bool &loop = false) override;
        void setWindowSize(const int &w, const int &h) override;
        void openWindow(const int &w, const int &h) override;
        void closeWindow() override;
        void clearScr() override;
        void draw() override;
        void updatePixels(std::vector<pixel_t> pixels) override;
        void setText(std::string label, text_t text) override;
        void setSprite(char label, std::string path) override;
        SDL_Color getColor(const color_t &color) const;
    };
} // namespace GUI

#endif /* AAE0EF63_1E8B_400B_B5FF_667C035B734D */
