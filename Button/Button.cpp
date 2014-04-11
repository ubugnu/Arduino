/*
  Button.cpp - Library for handling a button press.
  Created by Badreddine Bouzid, April 8, 2014.
  Released into the public domain.
*/

#include "Arduino.h"
#include "Button.h"

void do_nothing() {
	return;
}

Button::Button(int pin) {
	pinMode(pin, INPUT_PULLUP);
	_pin = pin;
	if(this->_debug) Serial.begin(9600);
	this->on_release(do_nothing);
	this->on_press(do_nothing);
	this->on_bounced_release(do_nothing);
	this->on_bounced_press(do_nothing);
}

void Button::_on_release(unsigned long gap) {
	this->__on_release();
	if(this->_debug) Serial.print(String("Button has been released after ") + gap + String(" milliseconds\n"));
}
void Button::_on_press(unsigned long gap) {
	this->__on_press();
	if(this->_debug) Serial.print(String("Button has been pressed after ") + gap + String(" milliseconds\n"));
}
void Button::_on_long_release(unsigned long gap) {
	this->__on_long_release();
	if(this->_debug) Serial.print(String("Button has been released after ") + gap + String(" milliseconds\n"));
}
void Button::_on_long_press(unsigned long gap) {
	this->__on_long_press();
	if(this->_debug) Serial.print(String("Button has been pressed after ") + gap + String(" milliseconds\n"));
}
void Button::_on_bounced_release(unsigned long gap) {
	this->__on_bounced_release();
	if(this->_debug) Serial.print(String("(I've detected a bounce at release! gap = ") + gap + String(")\n"));
}
void Button::_on_bounced_press(unsigned long gap) {
	this->__on_bounced_press();
	if(this->_debug) Serial.print(String("(I've detected a bounce at pressure! gap = ") + gap + String(")\n"));
}

void Button::init () {
	if(digitalRead(_pin) == LOW) {
		if(_button_state != LOW) {
			_milliseconds = millis();
			_gap = _milliseconds - _previous_HIGH_millis;
			_previous_LOW_millis = _milliseconds;
			this->button_pressed(_gap);
		}
		_button_state = LOW;
	}

	if(digitalRead(_pin) == HIGH) {
		if(_button_state != HIGH) {
			_milliseconds = millis();
			_gap = _milliseconds - _previous_LOW_millis;
			_previous_HIGH_millis = _milliseconds;
			this->button_released(_gap);
		}
		_button_state = HIGH;
	}
}

void Button::button_pressed (unsigned long gap) {
	if(gap > _minimum_gap && gap < _maximum_gap) this->_on_press(gap);
	else if(gap > _minimum_gap) this->_on_long_press(gap);
	else this->_on_bounced_press(gap);
}

void Button::button_released (unsigned long gap) {
	if(gap > _minimum_gap && gap < _maximum_gap) this->_on_release(gap);
	else if(gap > _minimum_gap) this->_on_long_release(gap);
	else this->_on_bounced_release(gap);
}

void Button::on_release(void(*on_release)()) {
	this->__on_release = on_release;
	this->__on_long_release = on_release;
}
void Button::on_press(void(*on_press)()) {
	this->__on_press = on_press;
	this->__on_long_press = on_press;
}
void Button::on_long_release(void(*on_long_release)()) {
	this->__on_long_release = on_long_release;
}
void Button::on_long_press(void(*on_long_press)()) {
	this->__on_long_press = on_long_press;
}
void Button::on_bounced_release(void(*on_bounced_release)()) {
	this->__on_bounced_release = on_bounced_release;
}
void Button::on_bounced_press(void(*on_bounced_press)()) {
	this->__on_bounced_press = on_bounced_press;
}

unsigned long Button::gap() {
	return this->_gap;
}

int Button::get_minimum_gap() {
	return this->_minimum_gap;
} 

int Button::get_maximum_gap() {
	return this->_maximum_gap;
}
void Button::set_minimum_gap(int gap) {
	this->_minimum_gap = gap;
}
void Button::set_maximum_gap(int gap) {
	this->_maximum_gap = gap;
}

void Button::enable_debug() {
	this->_debug = true;
}
void Button::disable_debug() {
	this->_debug = false;
}