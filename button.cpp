#include "button.h"


    // Draw button
    void Button::Draw(uint32_t color, uint32_t textColor)
    {
        lcd_.SetTextColor(color);
        lcd_.FillRect(X_, Y_, W_, H_);

        if (STR_.length() != 0)
        {
            lcd_.SetFont(FONTS_);
            lcd_.SetBackColor(color);
            lcd_.SetTextColor(textColor);

            uint16_t x0 = X_ + (W_ - FONT_WIDTH_*(STR_.length()))/2;
            uint16_t y0 = Y_ + (H_ - FONT_HEIGHT_)/2 + 1;
            lcd_.DisplayStringAt(x0, y0, (uint8_t *)STR_.c_str(),
                                 LEFT_MODE);
            lcd_.SetBackColor(BACK_COLOR_); // recover back color
        }            
    }
        
    // Check touch detected
    bool Button::Touched()
    {
        ts_.GetState(&state_);
        if (!state_.touchDetected) return false;
        return IsOnButton();
    }
        
    // Check touch detected and redraw button
    bool Button::Touched(uint32_t color, uint32_t textColor)
    {
        bool rtn = Touched();
        if (rtn) Draw(color, textColor);
        return rtn;
    }
    
    // If panel touched, return true
    bool Button::PanelTouched()
    {
        ts_.GetState(&state_);
        return (bool)(state_.touchDetected);
    }
    
    // If touched position is on the button, return true
    bool Button::IsOnButton()
    {
        int nTouch = multiTouch ? state_.touchDetected : 1;
        for (int n=0; n<nTouch; n++)
        {
            uint16_t x = state_.touchX[n];
            uint16_t y = state_.touchY[n];

            if ( (X_ <= x) && (x <= X_+W_) &&
                 (Y_ <= y) && (y <= Y_+H_) ) return true;
        }
        return false;
    }

    TS_StateTypeDef Button::state_;
    bool Button::multiTouch = true;
