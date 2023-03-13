/*
** EPITECH PROJECT, 2022
** interface
** File description:
** IGameModule.hpp
*/

#ifndef FC1CAAB3_70C1_4100_A955_F4F1F994421B
    #define FC1CAAB3_70C1_4100_A955_F4F1F994421B
    #include "IDisplayModule.hpp"

namespace Game
{
    class IGameModule {
        public:
            virtual ~IGameModule() = default;
            /**
             * @brief Initialize the game and starts its main loop.
             *
             * @param gui The graphical library that will be used to display the game.
             * @param stopGame The game will stop if this variable is externally set to false during runtime.
             * @return true If the game was successfully initialized and ran
             * without errors.
             * @return false If the game failed to initialize.
             */
            virtual bool run(GUI::IDisplayModule &gui, bool &stopGame) = 0;
    };
}

#endif /* FC1CAAB3_70C1_4100_A955_F4F1F994421B */
