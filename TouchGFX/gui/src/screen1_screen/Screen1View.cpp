#include <gui/screen1_screen/Screen1View.hpp>

Screen1View::Screen1View()
{

}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

void Screen1View::buttonUpClicked()
{
  touchgfx_printf("buttonUpClicked\n");
    counter++;
  	Unicode::snprintf(textCounterBuffer, TEXTCOUNTER_SIZE, "%d", counter);
  	// Invalidate text area, which will result in it being redrawn in next tick.
 	 textCounter.invalidate();
}

void Screen1View::buttonDownClicked()
{
  	touchgfx_printf("buttonDownClicked\n");
   	counter--;
  	Unicode::snprintf(textCounterBuffer, TEXTCOUNTER_SIZE, "%d", counter);
  	// Invalidate text area, which will result in it being redrawn in next tick.
  	textCounter.invalidate();
}