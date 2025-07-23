# M5Carputer-Offline-Dictionary-EN-to-CZ-

A simple, fast, and completely offline English-to-Czech dictionary application for the M5Carputer.

This project uses a pre-processed dictionary file and a custom font for a stable and complete user experience.

Features

    Offline Operation: No Wi-Fi required. The entire dictionary is stored on the SD card.

    Large Dictionary Support: Handles large dictionary files (tested with over 88,000 words).

    Full Accent Support: Uses a pre-generated custom font to perfectly display all Czech characters.

    Clean User Interface: A simple, readable interface for typing and viewing translations.

    Word Wrapping: Long translations automatically wrap to the next line.

Requirements

Hardware

    M5Carputer

    A MicroSD Card (formatted as FAT32)

Software & Files

    Arduino IDE

    M5Stack Board Support Package

    Project Files (To Download):

        dico_final.csv (the dictionary data)

        Police_with_accents.h (the custom font)

        The main .ino sketch file.

Installation

The installation is a simple two-step process.

Step 1: Arrange the Project Files

    Create a new sketch folder in your Arduino projects directory.

    Download the main .ino sketch file and the Police_with_accents.h font file from this repository. Place both files inside this new sketch folder.

    Download the dico_final.csv file from this repository. Copy it to the root of your MicroSD card.

Step 2: Configure IDE and Upload

    In the Arduino IDE, open the .ino sketch file.

    Go to Tools > Board and select M5Stack-Core-ESP32.

    Go to Tools > M5Stack-Core-ESP32 > Board and select M5Cardputer.

    Ensure Tools > PSRAM is set to Enable.

    Upload the sketch to your M5Carputer.

Usage

Once the application is running, simply start typing an English word. The text will appear in the input box. Press the Enter key to see the Czech translation. Use the Delete key to correct your input.
