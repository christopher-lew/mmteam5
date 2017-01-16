# README

This repository contains the source code that will be used to run UCSD's IEEE Team 1 Micromouse for the 2016-2017 year. Currently in the early stages of development.

This repo is meant to be compatible with mbed's library using the [NUCLEO-F401RE platform](https://developer.mbed.org/platforms/ST-Nucleo-F411RE/) and designed to be run on the "Falcon v2" Micromouse.

* [How to export mbed C/C++ SDK to use with offline toolchains](https://developer.mbed.org/handbook/Exporting-to-offline-toolchains)

* [Learn Markdown](https://bitbucket.org/tutorials/markdowndemo)

* * *
## Current Implementation Objectives:
* ~~Determine C vs C++ pros/cons and choose a language~~ (Develop classes in C++)

* ~~Determine language limitations~~
    + no dynamic memory
	+ will use mbed's libraries
	
* Learn to use FPU on STM32F446RE
	
* Develop __Classes__ for:
	1. Main
	2. Maze *(later implement nested cell class with inline function calls)*
    3. Motor
	4. Encoder
	5. ~~IR Sensor Pair~~
	6. Gyro
	7. ~~Buzzer~~
	
* Develop __Headers__ *(Sets of Functions)* for:
	1. ~~Initialize Sensors~~
		+ Instatiates objects from sensor classes and objects from mbed libraries *(battery, ledRed, etc.)*
	2. ~~Debugging IO Print Functions~~
		+ Can be printed through Bluetooth USART or SWD cable?
	3. Drive Control Logic
	
