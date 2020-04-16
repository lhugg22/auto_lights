This project is to create an automated light for my apartment
it will use a HC-SR04 to get the hand wave gesture in front of the sensor
the sensor is also connnected to a arduino nano for control
the arduino is used to control the lights of a WS2812


Issues:
	currently I am running into issues because the sensor and lights won't work together
		I believe that the timing of the sensor is messing with the PWM of the lights


0.3 Working Distance Sensor:
	got the HC-SR04 to work with as small as a 50ms delay, I think I could go down to 10ms but haven't tested it yet
	created a bool called lights_on for controlling lights. 
	Plan: if lights_on is on do a colorWipe from the other .h file to wipe the colors.
		-I think I will turn off the serial for this. it will be obvious if its working right
		-if it isn't working, I will add the serial back for trouble shooting

1.0 Working w/ Lights!
	I got the sensor to work at a scan rate of 50ms. I may go back and change this later but ITS WORKING!
	This will work to show all of the colors Red (which isn't folling the (R, G, B) format that I thought it should
		(this might be in an English format of (G, R, B)? will do some testing)

1.1 changed color
	I changed the color and cleaned up the code a bit to get rid of the serial prints and extra code that wasn't needed
	I currently have left the color projection as blue. this can be changed easily by adjusting the color code of the GRB (green, red, blue)
	I am working on a function for changing the color just to make the code more streamlined
	very excited to mount this. next step is to start working on my wifi weight scale!
