/*
** EPITECH PROJECT, 2022
** interface
** File description:
** IGameModule.hpp
*/

#pragma once

#include "IDisplayModule.hpp"

namespace Game
{
    class IGameModule {
        public:
            virtual ~IGameModule() = default;
            /**
            @brief Process one frame of the game based on the events received.
            @param events The events received from the graphical lib.
            @return True if the game is still running, False if the game is over.
            */
            virtual bool processFrame(std::vector<GUI::IDisplayModule::event_t>) = 0;
            /**
            @brief Get the specs of the map.
            */
            virtual GUI::IDisplayModule::mapSpecs_t getMapSpecs() = 0;
            /**
            @brief Get the pixels to display on the screen.
            */
            virtual std::vector<GUI::IDisplayModule::pixel_t> getPixels() = 0;
            /**
            @brief Get the texts to display on the screen.
            */
            virtual std::vector<GUI::IDisplayModule::text_t> getTexts() = 0;
            /**
            @brief Get the sounds to play.
            */
            virtual std::vector<std::string> getSounds() = 0;
    };
}
