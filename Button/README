Arduino Button library
======================

Introduction
------------

The first issue we encounter when learning to use Arduino is the "bouncing phenomenon" inherent to buttons, indeed, when pressing a button, very often this press produces many "bounced" successive presses/releases of that button, which may affect the normal behaviour of our program!

Proof of concept
----------------

If you write a simple code that switches a led state between HIGH and LOW using a button like this:

const int buttonPin = 2;
const int ledPin = 4;
int button_state = HIGH;
unsigned long int previous_time = 0;

void switch_led_state() {
	if(digitalRead(ledPin) == LOW) digitalWrite(ledPin, HIGH);
	else digitalWrite(ledPin, LOW);
	Serial.print(String("Switching after ") + (millis() - previous_time) + String(" milliseconds\n"));
	previous_time = millis();
}

void setup() {
	Serial.begin(9600);
	pinMode(buttonPin, INPUT_PULLUP);
	pinMode(ledPin, OUTPUT);
	digitalWrite(ledPin, LOW);
}

void loop() {
	if(digitalRead(buttonPin) == LOW) {
		if(button_state != LOW) switch_led_state();
		button_state = LOW;
	} else button_state = HIGH;
}

This code will turn the led on (if it's off) or off (if it's on). If you try it, you will notice that some presses will switch the led state two times (even many times), this is due to the "bouncing effect", it means that the button bounces two or three times when pressed, the same phenomenon occures when releasing the button. You can see in the serial monitor the difference of time between two different bounced presses (or releases) and check that it is very short.

Features
--------

This is the Arduino `Button` library solution for the "bouncing effect", it handles buttons and has the ability of detecting:

* **A normal button press NBP** An (ending by a release) press that lasts less than 1000<sup>(*)</sup> milliseconds and that is not a bounced press
* **A long button press LBP** - An (ending by a release) press that lasts more than 1000<sup>(*)</sup> milliseconds
* **A bounced button press BBP** - An (ending by a release) press that lasts less than 35<sup>(*)</sup> milliseconds

In addition, this library can handle button presses without requiring releasing the button, it has the ability of detecting:

* **A normal button (strict) press NBsP** - A press occuring after less than 1000(*) milliseconds of the previous release and that is not a bounced press
* **Long button (strict) press LBsP** - A press occuring after more than 1000(*) milliseconds of the previous release
* **Bounced button (strict) press BBsP** - A press occuring after less than 35(*) milliseconds of the previous release

> (*) These values can be modified by user to fit particular situations where buttons bounce with periods greater than 35 ms, or to considere long press duration more or less than 1000 milliseconds.

Under normal circumstances, BBP and BBsP detection features will be useless, in the same way, a normal user will not need to differentiate between a NBsP ans a LBsP, this is why affecting actions to NBsP will by default affect the same action to LBsP unless the user affects another action to NBsP. The same thing happens when affecting an action to NBP which will be considered as the default action for LBP unless the user reaffects another action to LBP (though the user will very likely need to differentiate between NBP's and LBP's).

Installation
------------

Simply put the `Button/` folder to the Arduino library folder(**) then include the `Button` library to your project:

#include "Button.h"

(**)  This should be:
`~/Arduino/libraries/` on Linux
`My Documents\Arduino\libraries\` on Windows
`Documents/Arduino/libraries/` on Mac

Usage
-----

Here is a simple example that show you how to use the `Button` library:

#include "Button.h"

Button button(2);	// the button will be on pin 2

// fcuntions that will be called whenever one of the XB(s)P's event occurs

void on_release() {
	Serial.print(String("button released immediately: ") + button.gap() + String(" milliseconds\n"));
}
void on_press() {
	Serial.print(String("button pressed immediately: ") + button.gap() + String(" milliseconds\n"));
}
void on_long_release() {
	Serial.print(String("button released after long time: ") + button.gap() + String(" milliseconds\n"));
}
void on_long_press() {
	Serial.print(String("button pressed after long time: ") + button.gap() + String(" milliseconds\n"));
}
void on_bounced_release() {
	Serial.print(String("button released after a bounce: ") + button.gap() + String(" milliseconds\n"));
}
void on_bounced_press() {
	Serial.print(String("button pressed after a bounce: ") + button.gap() + String(" milliseconds\n"));
}

void setup() {
	Serial.begin(9600);
	button.on_release(on_release);						// on NBP (if not set nothing will be done)
	button.on_press(on_press);							// on NBsP (if not set nothing will be done)
	button.on_long_press(on_long_press);				// on LBsP (if not set, on_press will be used for on_long_press events)
	button.on_long_release(on_long_release);			// on LBP (if not set, on_release will be used for on_long_release events)
	button.on_bounced_release(on_bounced_release);		// on BBP (junk, if not set nothing will be done)
	button.on_bounced_press(on_bounced_press);			// on BBsP (junk, if not set nothing will be done)
}

void loop() {
	button.init();
}

Options
-------

You can change the default time for wich a press is considered as bounced as well as that for which a press is considered long with the methods:

button.set_minimum_gap(<time in milliseconds>);
button.set_maximum_gap(<time in milliseconds>);

You can also get these values with:

button.get_minimum_gap(<time in milliseconds>);
button.get_maximum_gap(<time in milliseconds>);

The gap between a release and a press (or vice versa) can be accessed with:

button.gap(<time in milliseconds>);

Finally debug mode can be enable or disabled with (it is disabled by default):

button.enable_debug();
button.disable_debug();

Find it horribly heavy for a microcontroller?
--------------------------------------------

Criticisms are welcome! Or just fork it ;-)

Contact
-------

Please contact me at https://twitter.com/ubugnu
