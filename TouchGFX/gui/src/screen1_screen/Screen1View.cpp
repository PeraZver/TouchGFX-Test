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
      float yMax = mojGraf.getGraphRangeYMaxAsFloat();
      // Insert data point
      mojGraf.addDataPoint((float)adc_data/4096.0f *yMax); /* Your data point here, either float or integer */
      //mojGraf.addDataPoint(1*yMax); /* <-- FOR SIMULATOR ONLY */
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
