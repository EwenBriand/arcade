/*
** EPITECH PROJECT, 2023
** B-OOP-400-BAR-4-1-arcade-thomas.laprie
** File description:
** Ncurs
*/

#include "IDisplayModule.hpp"

#ifndef FA028B0A_04A6_49C1_AA05_E6F559D8DDC2
    #define FA028B0A_04A6_49C1_AA05_E6F559D8DDC2

namespace GUI
{
    class Ncurse : public IDisplayModule {
      public:
        Ncurse();
        ~Ncurse();
        virtual void setUnits(const int &pxpu) override;
        /**
         * @brief Get the Units object
         *
         * @return int
         */
        virtual int getUnits() const override;
        /**
         * @brief Set the Map Specs object
         *
         * @param mapspecs specs of the map
         */
        virtual void setMapSpecs(mapSpecs_t mapspecs) override;
        virtual std::vector<event_t> pollEvents() override;
        virtual void loadSound(
            const std::string &label, const std::string &path) override;
        virtual void playSound(
            const std::string &label, const bool &loop = false) override;
        virtual void setWindowSize(const int &w, const int &h) override;
        virtual void openWindow(const int &w, const int &h) override;
        virtual void closeWindow() override;
        virtual void clearScr() override;
        virtual void draw() override;
        virtual void updatePixels(std::vector<pixel_t> pixels) override;
        virtual void setText(std::string label, text_t text) override;
        virtual void setSprite(char label, std::string path) override;

      private:
        int _units;
        std::map<int, std::map<int, pixel_t>> _map;
        std::map<std::string, text_t> _texts;
        mapSpecs_t _mapspecs;
    };
} // namespace GUI

#endif /* FA028B0A_04A6_49C1_AA05_E6F559D8DDC2 */
