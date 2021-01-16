#include <gui/screen1_screen/Screen1View.hpp>

extern int adc_data;

Screen1View::Screen1View()
{

    tickCounter = 0;
}

void Screen1View::setupScreen()
{
    Screen1ViewBase::setupScreen();
}

void Screen1View::tearDownScreen()
{
    Screen1ViewBase::tearDownScreen();
}

void Screen1View::handleTickEvent()
{
    tickCounter++;

    // Insert each second tick
    if (tickCounter % 2 == 0)
    {
      // Insert data point
      mojGraf.addDataPoint((float)adc_data/4096*100); /* Your data point here, either float or integer */
    }
}
