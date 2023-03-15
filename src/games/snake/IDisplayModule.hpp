/*
** EPITECH PROJECT, 2022
** poc
** File description:
** IGUI.hpp
*/

#ifndef IGUI_HPP
    #define IGUI_HPP
    #include <map>
    #include <vector>
    #include <string>
    #include <array>

    #define BINDINGs_NBR 4

namespace GUI
{
    class IDisplayModule {
        public:
            typedef enum bindingType_e {
                UP,
                DOWN,
                LEFT,
                RIGHT,
                MOUSE_CLICK,
                QUIT,
                KEYCODE,
            } bindingType_t;

            typedef enum color_e {
                BLACK,
                RED,
                GREEN,
                YELLOW,
                BLUE,
                MAGENTA,
                CYAN,
                WHITE,
            } color_t;

            /**
             * @brief Struct that represents a pixel on the screen.
             * Color is choosen from enum color_t. Repr is the char that will
             * be displayed on the screen or the code for the corresponding sprite.
             * x and y are the coordinates of the pixel in the graphical lib's
             * unit system.
             *
             */
            typedef struct pixel_s {
                unsigned char color = 0;
                unsigned char repr = ' ';
                unsigned int x = 0;
                unsigned int y = 0;
            } pixel_t;

            /**
             * @brief Struct that represents an Event.
             * Name is the type of the event, choosed from the enum bindingType_t.
             * The Event class has a std::vector of values that can be used if
             * the event has some values associated with it. (for exemple the coordinates
             * of the mouse when a mouse click event is triggered)
             * The Event class also has a timestamp that can be used to know when the event
             * happened and sort them by order in time if needed.
             *
             */
            typedef struct event_s {
                    bindingType_t _name = KEYCODE;

                    float timeStamp;
                    std::vector<double> _dvalues;
                    std::vector<int> _ivalues;
            } event_t;

            /**
             * @brief Set the relation between one in game unit and the number of
             * pixels on the screen.
             *
             */
            virtual void setUnits(const int &pxpu) = 0;
            virtual int getUnits() const = 0;

            /**
             * @brief Collects the events that happened since the last call to pollEvents.
             *
             * @return std::vector<event_t> the list of events that happened since the last call.
             */
            virtual std::vector<event_t> pollEvents() = 0;

            /**
             * @brief Play a sound. If the sound is already playing, it will be stopped and restarted.
             * If the sound is not already loaded, it will be loaded.
             * If the sound is not found, nothing will happen.
             *
             * @param id is the path to the sound to play in the filesystem.
             * @param loop is a boolean that indicates if the sound should be looped or not.
             *             Use it for your musics.
             */
            virtual void playSound(const std::string &id, bool loop = false) = 0;

            /**
             * @brief Stop a sound. If the sound is not playing, nothing will happen.
             *
             * @param id : the path to the sound to stop in the filesystem.
             */
            virtual void stopSound(const std::string &id) = 0;

            /**
             * @brief Set the volume of a sound.
             *
             * @param between_zero_and_100 where 0 is mute and 100 is the maximum volume.
             */
            virtual void setVolume(const int &between_zero_and_100) = 0;

            /**
             * @brief Set the pitch of a sound.
             *
             * @param multiplyer where 1 is the normal pitch and 2 is twice the normal pitch.
             */
            virtual void setPitch(const float &multiplier) = 0;

            /**
             * @brief Set the Window dimensions.
             *
             * @param w
             * @param h
             */
            virtual void setWindowSize(const int &w, const int &h) = 0;
            /**
             * @brief Opens the window for the graphical lib. Initializes the window.
             *
             * @param w width of the window, in the unit system of the graphical lib.
             * @param h height of the window, in the unit system of the graphical lib.
             */
            virtual void openWindow(const int &w, const int &h) = 0;

            /**
             * @brief Closes the window for the graphical lib. Destroys the window.
             *
             */
            virtual void closeWindow() = 0;

            /**
             * @brief Clears the screen. All the pixels will be set to black / transparent.
             *
             */
            virtual void clearScr() = 0;

            /**
             * @brief Draws the pixel map on the screen. The pixel map is
             * a 2D array of pixels stored internally by the library, with dimensions
             * set to w * h (the dimensions of the window).
             *
             */
            virtual void draw() = 0;

            /**
             * @brief Updates the pixel map with the new pixels.
             *
             * @param pixels a vector of pixel_t, each pixel_t representing a pixel to change on the map.
             * Pixels that are not explicitly set will not be changed.
             */
            virtual void updatePixels(std::vector<pixel_t> pixels) = 0;

            /**
             * @brief Draws a text on the screen. It will be drawn last, above the pixel map.
             *
             * @param text the text to draw.
             * @param x the x coordinate of the text, in the unit system of the graphical lib.
             * @param y the y coordinate of the text, in the unit system of the graphical lib.
             * @param color the color of the text, choosen from the enum color_t.
             */
            virtual void drawText(const std::string &text, int x, int y, const color_t &color = BLACK) = 0;
        private:
    };
} // namespace GUI

#endif // IGUI_HPP
