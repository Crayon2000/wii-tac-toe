#include <string.h>
#include <gccore.h>
#include "../gfx/button_on.h"
#include "../gfx/button_off.h"
//#include "../fonts/button_text.h"
#include "../fonts/GRRLIB_font1.h"
#include "button.h"

/**
 * Constructor for the Button class.
 */
Button::Button() : Object()
{
	Selected = false;
	Left = 0;
	Top = 0;
	Width = 400;
	Height = 64;

	TextColor = 0xFF000000;

	button_font = GRRLIB_LoadTexture(GRRLIB_font1);
	TextHeight = 8;
	TextWidth = 1024 / 128;

	ButtonImgOn = GRRLIB_LoadTexture(button_on);
	ButtonImgOff = GRRLIB_LoadTexture(button_off);
}

/**
 * Destructor for the Button class.
 */
Button::~Button()
{
	free(button_font);
	free(ButtonImgOn);
	free(ButtonImgOff);
}

/**
 * Draw the button to screen.
 */
void Button::Paint()
{
	GRRLIB_DrawImg(Left, Top, Width, Height, ButtonImgOff, 0, 1, 1, 255);
	GRRLIB_Printf(TextLeft, TextTop, button_font, TextColor, 1, Caption);
	if(Selected)
	{
		GRRLIB_DrawImg(Left, Top, Width, Height, ButtonImgOn, 0, 1, 1, 255);
	}
}

/**
 * Set caption on the button.
 * @param[in] Caption Text to put on the button.
 */
void Button::SetCaption(const char *Caption)
{
	strncpy(this->Caption, Caption, 50);
	TextWidth *= strlen(this->Caption);
	TextTop = Top + (Height / 2) - (TextHeight / 2);
	TextLeft = Left + (Width / 2) - (TextWidth / 2);
}

/**
 * Set the button state, selected or not.
 * @param[in] Selected Set to true to select the button, false otherwise.
 */
void Button::SetSelected(bool Selected)
{
	this->Selected = Selected;
}

/**
 * Set the text color on the button.
 * @param[in] TextColor Color of the text when the button is not selected.
 */
void Button::SetTextColor(u32 TextColor)
{
	this->TextColor = TextColor;
}
