"""
Created on 05/22/2017
Python 3.5.3

@author: Javier Urquizu

This script zips all the directories and files needed to flash onto the mouse.
Used for zipping up files and easily uploading them to mbed's online compiler.
"""

import os
import zipfile


zipFilename = "falconProject.zip"
zipdirs = ["config/", "devices/", "drivers/", "src/"]
validFiles = ["main.cpp"]
ignoreFiles = ["desktop.ini"]


if __name__ == '__main__':
    # Check that all needed zip directories are present
    for _dir in zipdirs:
        assert (os.path.exists(_dir)), "'{}' folder not found!".format(_dir) 

    # Get a list of all valid files inside these directories (i.e. remove all desktop.ini files Google Drive generates)
    for _dir in zipdirs:
        files = os.listdir(_dir)
        for f in files:
            if f not in ignoreFiles:
                validFiles.append(_dir +f)
    
    # Write files to zipfile's file handler
    with zipfile.ZipFile(zipFilename, 'w') as zipf:
        for f in validFiles:
            zipf.write(f)