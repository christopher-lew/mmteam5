# README

This repository contains the source code that will be used to run UCSD's IEEE Team 1 Micromouse for the 2016-2017 year. Currently in the early stages of development.

This repo is meant to be compatible with mbed's library using the [NUCLEO-F401RE platform](https://developer.mbed.org/platforms/ST-Nucleo-F411RE/) and designed to be run on the "Falcon v2" Micromouse.

[How to export mbed c/C++ SDK to use with offline toolchains](https://developer.mbed.org/handbook/Exporting-to-offline-toolchains)

## Current Implementation Objectives:
* ~~Determine C vs C++ pros/cons and choose a language~~ (Develop classes in C++)

* Determine language limitations
    + dynamic memory
	+ usable libraries
	    1. MBed's libraries *(.dll's)*
		2. Project Futura ST Libraries *(stm32f4xx_foo.c's)*
	+ etc
	
* Develop __Classes__ for:
	1. Main
	2. Maze __(later implement nested cell class with inline function calls)__
    3. Motor
	4. Encoder _(maybe nest in motor)_
	5. IR Controller __(with nested IRPair class with inline function calls)__
	6. Gyro
	
* Develop __Headers__ *(Sets of Functions)* for:
	1. Pin Assignments Header _(determine if this legacy feature is useful)_
	2. Drive Controls
	2. Set of I/O Print _Debug_ functions through Bluetooth USART
	
	
* * *
*Default information below*
### What is this repository for?

* Quick summary
* Version
* [Learn Markdown](https://bitbucket.org/tutorials/markdowndemo)

### How do I get set up?

* Summary of set up
* Configuration
* Dependencies
* Database configuration
* How to run tests
* Deployment instructions

### Contribution guidelines

* Writing tests
* Code review
* Other guidelines

### Who do I talk to?

* Repo owner or admin
* Other community or team contact