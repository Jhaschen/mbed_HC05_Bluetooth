#ifndef BUTTON_H
#define BUTTON_H

#include "mbed.h"
#include <string>
#include "TS_DISCO_F469NI.h"
#include "LCD_DISCO_F469NI.h"

  class Button
    {
    public:
        // Constructor
        Button(LCD_DISCO_F469NI &lcd, TS_DISCO_F469NI &ts,
               uint16_t x, uint16_t y, uint16_t width, uint16_t height,
               uint32_t color, uint32_t backColor,
               const string str = "", sFONT &fonts = Font12,
               uint32_t textColor = LCD_COLOR_WHITE)
              : lcd_(lcd), ts_(ts), X_(x), Y_(y), W_(width), H_(height),
                ORIGINAL_COLOR_(color), BACK_COLOR_(backColor),
                STR_(str), FONTS_(&fonts), FONT_WIDTH_(fonts.Width),
                FONT_HEIGHT_(fonts.Height)
        {   Draw(color, textColor); }

        // Draw button
        void Draw(uint32_t color, uint32_t textColor = LCD_COLOR_WHITE);

        // Redraw button with original color
        void Redraw(uint32_t textColor = LCD_COLOR_WHITE)
        {   Draw(ORIGINAL_COLOR_, textColor);   }

        // Erase button
        void Erase()
        {   Draw(BACK_COLOR_, BACK_COLOR_);   }

        // Check touch detected
        bool Touched();

        // Check touch detected and redraw button
        bool Touched(uint32_t color, uint32_t textColor = LCD_COLOR_WHITE);

        // Get original color 
        uint32_t GetOriginalColor() { return ORIGINAL_COLOR_; }
        
        bool PanelTouched();
        bool IsOnButton();
        
        // Get previously got state
        static TS_StateTypeDef GottenState()
        {   return state_; }

        // Set or reset multi-touch
        static void SetMultiTouch(bool tf) { multiTouch = tf; }

    private:
        LCD_DISCO_F469NI &lcd_;
        TS_DISCO_F469NI &ts_;
        
        const uint16_t X_, Y_, W_, H_;
        const uint32_t ORIGINAL_COLOR_; // original color
        const uint32_t BACK_COLOR_;     // back color of screen
        const string STR_;
        sFONT *const FONTS_;
        const uint16_t FONT_WIDTH_;
        const uint16_t FONT_HEIGHT_;

        static TS_StateTypeDef state_;
        static bool multiTouch;

        // disallow copy constructor and assignment operator
        Button(const Button&);
        Button& operator=(const Button&);
    };

#endif  //BUTTON_H