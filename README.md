# DS9

DS9 is a 3 channels drum synthesizer, based on eurorack physical format it has however no patch cables in the front but has rather midi and audio jacks in the back.

It is based on [Motherboard9](https://github.com/ghostintranslation/motherboard9).

NOTE: This is a work in progress.

## Features

* 3 Voices: Kick, Snare, HiHat
* Pitch, Tone, Decay controls on each voice
* MIDI over USB
* MIDI over mini jack
* Audio jack output

## Dimensions

Height: 3U / 128.5mm

Width: 12HP / 60mm

## Getting Started
## Getting Started

### Prerequisites

What things you need to make it work:

```
1 Teensy 4.0
1 Teensy audio board
1 MOTHERBOARD9A pcb
1 MOTHERBOARD9B pcb
1 PSYC03 front panel pcb
9 vertical linear 10k potentiometers
3 14 pins male header
5 14 pins female header
6 CD4051 multiplexers
6 DIP16 IC sockets (optionak)
2 3.5mm jack connectors
1 resistor ~ 22ohm
3 LED
1 4 positions dipswitch (optional)
```

I personally get these parts from multiple stores: digikey.com, thonk.co.uk, modularaddict.com

In order to run any sketch on the Teensy you have to install the Teensyduino add-on to Arduino.
Follow the instructions from the official page:
https://www.pjrc.com/teensy/teensyduino.html

Then open the sketch located in the Synth folder of this repo.

In the Tools -> USB Type menu, choose "Serial + midi".

Then you are ready to compile and upload the sketch.

## How to use

Here is a description of the 6 inputs and what they do:

```
1. Kick tune
2. Clap tune
3. Hihat tune
4. Kick color
5. Clap color 
6. Hihat color
7. Kick decay
8. Clap decay
9. Hihat decay

```

The 3 MIDI notes to trigger the drums are 36, 38 and 42.

## MIDI

The MIDI input and output jacks are directly connected to the Teensy serial input and output. That means there is not protection against voltage or current. It is primarily ment to connect 2 of these modules, or 2 Teensy together. If you want to connect something else to it make sure to provide a maximum of 3.3v and 250 mA.

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

# About me
You can find me on Bandcamp and Instagram:

https://ghostintranslation.bandcamp.com/

https://www.instagram.com/ghostintranslation/

https://www.youtube.com/channel/UCcyUTGTM-hGLIz4194Inxyw

https://www.ghostintranslation.com/