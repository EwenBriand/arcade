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
        Ncurse(unsigned int x, unsigned int y);
        ~Ncurse();
        virtual void setUnits(const int &pxpu) override;
        virtual int getUnits() const override;
        virtual std::vector<event_t> pollEvents() override;
        virtual void playSound(
            const std::string &id, bool loop = false) override;
        virtual void stopSound(const std::string &id) override;
        virtual void setVolume(const int &between_zero_and_100) override;
        virtual void setPitch(const float &multiplyer) override;
        virtual void setWindowSize(const int &w, const int &h) override;
        virtual void openWindow(const int &w, const int &h) override;
        virtual void closeWindow() override;
        virtual void clearScr() override;
        virtual void draw(const int x, const int y) override;
        virtual void updatePixels(std::vector<pixel_t> pixels) override;
        virtual void drawText(const std::string &text, int x, int y,
            const color_t &color = BLACK) override;

      private:
        int _units;
        std::map<int, std::map<int, pixel_t>> _map;
    };
} // namespace GUI

#endif /* FA028B0A_04A6_49C1_AA05_E6F559D8DDC2 */
