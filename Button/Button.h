/*
  Button.h - Library for handling a button press.
  Created by Badreddine Bouzid, April 8, 2014.
  Released into the public domain.
*/

#ifndef Button_h
#define Button_h

#include "Arduino.h"

class Button {
	public:
		Button(int pin);
		void init ();
		void button_pressed (unsigned long gap);
		void button_released (unsigned long gap);
		void on_release (void (*)());
		void on_press (void (*)());
		void on_long_release (void (*)());
		void on_long_press (void (*)());
		void on_bounced_release (void (*)());
		void on_bounced_press (void (*)());
		unsigned long gap ();
		void enable_debug ();
		void disable_debug ();
		int get_minimum_gap();
		int get_maximum_gap();
		void set_minimum_gap(int gap);
		void set_maximum_gap(int gap);
	private:
		void _on_release (unsigned long gap);
		void _on_press (unsigned long gap);
		void _on_long_release (unsigned long gap);
		void _on_long_press (unsigned long gap);
		void _on_bounced_release (unsigned long gap);
		void _on_bounced_press (unsigned long gap);
		int _pin;
		int _button_state = HIGH;
		unsigned long _previous_LOW_millis = 0;
		unsigned long _previous_HIGH_millis = 0;
		unsigned long _gap = 0;
		unsigned long _milliseconds = 0;
		boolean _debug = false;
		int _minimum_gap = 35;
		int _maximum_gap = 1000;
		void (*__on_release)();
		void (*__on_press)();
		void (*__on_long_release)();
		void (*__on_long_press)();
		void (*__on_bounced_release)();
		void (*__on_bounced_press)();
};

#endif