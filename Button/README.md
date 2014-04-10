# Arduino Button library

## Introduction

The first issue I encountered when learning to use Arduino is the "bouncing phenomenon" inherent to buttons, indeed, when pressing a button, very often this press produces many "bounced" presses/releases of that button, which may make a program behave strangly!

## Proof of concept

To do ...

## Presentation

This is the Arduino `Button` library that handle buttons that has the ability of detecting:

* **Normal button press** - press that lasts less than 1000 milliseconds (this value can be changed)
* **Long button press** - press that lasts more than 1000 milliseconds (this value can be changed)
* **Bounced button press** - press that lasts less than 1000 milliseconds (this value can be changed)