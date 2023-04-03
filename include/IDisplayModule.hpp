/*
** EPITECH PROJECT, 2022
** poc
** File description:
** IGUI.hpp
*/

#pragma once

#include <map>
#include <vector>
#include <string>
#include <array>

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
                BACKSPACE,
                ENTER,
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
             * @brief Represents the delta RGB values of a pixel for all channels,
             * relative to the base color of the pixel specified in the pixel_t
             * structure.
             *
             */
            typedef struct deltaRGB_s {
                int r = 0;
                int g = 0;
                int b = 0;
            } deltaRGB_t;
            /**
             * @brief Struct that represents the specs of the map.
             * posx and posy are the coordinates of the top left corner of the map
             * in the graphical lib's unit system.
             * pixw and pixh are the width and height of the map in pixels.
             *
             */
            typedef struct mapSpecs_s {
                int posx;
                int posy;
                int pixw;
                int pixh;
            } mapSpecs_t;

            /**
             * @brief Struct that represents a pixel on the screen.
             * Color is choosen from enum color_t. Repr is the char that will
             * be displayed on the screen or the label code for the corresponding sprite.
             * x and y are the coordinates of the pixel in the graphical lib's
             * unit system.
             * rotation is the rotation of the sprite in mutliple of 90°.
             */
            typedef struct pixel_s {
                color_t color = BLACK;
                deltaRGB_t deltaRGB;
                unsigned char repr = ' ';
                int x = 0;
                int y = 0;
                std::string spritePath = "";
                int rotation;
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
             * @brief Struct that represents a text.
             *
             * str is the string to display.
             * x and y are the coordinates of the text in the graphical lib's unit system.
             * scale is the scale of the text.
             * color is the color of the text, choosen from the enum color_t.
            */
            typedef struct text_s {
                std::string str;
                int x = 0;
                int y = 0;
                double scale = 1;
                color_t color = WHITE;
            } text_t;

            /**
             * @brief Set the relation between one in game unit and the number of
             * pixels on the screen.
             *
             */
            virtual void setUnits(const int &pxpu) = 0;
            virtual int getUnits() const = 0;

            /*
            * @brief Set the specs of the map.
            * @param mapspecs
            */
            virtual void setMapSpecs(mapSpecs_t mapspecs) = 0;
            /**
             * @brief Collects the events that happened since the last call to pollEvents.
             *
             * @return std::vector<event_t> the list of events that happened since the last call.
             */
            virtual std::vector<event_t> pollEvents() = 0;

            /**
             * @brief Load all the sounds from a directory.
             *
             * @param dir The directory where sounds are.
             */
            virtual void loadSound(const std::string &label, const std::string &path) = 0;

            /**
             * @brief Play a sound.
             *
             * @param sound : the struct of the sound to play.
             * @param loop is a boolean that indicates if the sound should be looped or not.
             *             Use it for your musics.
             */
            virtual void playSound(const std::string &label, const bool &loop = false) = 0;

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
             * @brief If text label does not exist create a new text, else update the existing one.
             * @param label the label of the text to update.
             * @param text the new struct of the text to draw. It contain all the parameters of the text.
             */
            virtual void setText(std::string label, text_t text) = 0;

            /**
             * @brief If sprite label does not exist create a new sprite, else update the existing one.
             * @param label the label of the sprite to update this label should be the character contained in the pixel.
             * @param path the path to the sprite.
             */
            virtual void setSprite(char label, std::string path) = 0;
        private:
    };
} // namespace GUI
