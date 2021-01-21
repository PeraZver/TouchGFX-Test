#include <gui/screen1_screen/Screen1View.hpp>
#include <math.h>

extern uint32_t adc_data[];

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
      float yMax = mojGraf.getGraphRangeYMaxAsFloat(); /* Scaling factor if necessary */
      // Insert data point
      for (int i = 0; i < 280; i++)
    	  mojGraf.addDataPoint((int)(10*(sinf(6.28*i/100) + 1) ) + rand() % (int)(yMax / 10.f)); /* <-- FOR SIMULATOR ONLY */
      	  //mojGraf.addDataPoint((float)adc_data[i]/4096.0f *100); /* Your data point here, either float or integer */
    }
}

void Screen1View::sliderValueChanged(int value)
{
    // Adjust the Y-axis max value according to the slider value
    mojGraf.setGraphRangeY(0, value);
    mojGraf.invalidate();

    // Adjust the interval of the labels/grid lines on the Y-axis
    // to match the new range.
    if (value > 199)
    {
    	mojGrafMajorYAxisLabel.setInterval(50);
    	mojGrafMajorYAxisGrid.setInterval(50);
    }
    else if (value > 100)
    {
    	mojGrafMajorYAxisLabel.setInterval(20);
    	mojGrafMajorYAxisGrid.setInterval(20);
    }
    else
    {
    	mojGrafMajorYAxisLabel.setInterval(10);
    	mojGrafMajorYAxisGrid.setInterval(10);
    }

    mojGrafMajorYAxisLabel.invalidate();
    mojGrafMajorYAxisGrid.invalidate();
}
