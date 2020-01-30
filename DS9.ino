/*
 __    _  _____   ___      ___ _  _     __    _ ______ _    
/__|_|/ \(_  |     | |\|    | |_)|_||\|(_ |  |_| |  | / \|\|
\_|| |\_/__) |    _|_| |    | | \| || |__)|__| | | _|_\_/| |

https://ghostintranslation.bandcamp.com
https://www.instagram.com/ghostintranslation
https://github.com/ghostintranslation
*/

#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE(); // MIDI library init

#include <Audio.h>

#include "Kick.h"
#include "Snare.h"
#include "Hihat.h"


int ledPin = 13;
const int interval_time = 20;
elapsedMillis clock_count;

// The drums
Kick kick;
Snare snare;
Hihat hihat;

// The audio output
AudioOutputI2S  i2s2;
AudioMixer4     mixer;
AudioConnection patchCord1(*kick.getOutput(), 0, mixer, 0);
AudioConnection patchCord2(*snare.getOutput(), 0, mixer, 1);
AudioConnection patchCord3(*hihat.getOutput(), 0, mixer, 2);
AudioConnection patchCord4(mixer, 0, i2s2, 0);
AudioConnection patchCord5(mixer, 0, i2s2, 1);
AudioOutputUSB  usb1;
AudioConnection patchCord6(mixer, 0, usb1, 0);
AudioConnection patchCord7(mixer, 0, usb1, 1);

AudioControlSGTL5000 audioBoard;

void setup() {
  mixer.gain(0, 1);
  mixer.gain(1, 2);
  mixer.gain(2, 0.5);

  Serial.begin(115200);
  
  pinMode(ledPin, OUTPUT);
  
  MIDI.setHandleNoteOn(onNoteOn);
  usbMIDI.setHandleNoteOn(onNoteOn);

  AudioMemory(60);

  audioBoard.enable();
  audioBoard.volume(0.5);


  while (!Serial && millis() < 2500); // wait for serial monitor

  // Starting sequence
  Serial.println("Ready!");
  
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);

}

void loop() {
  MIDI.read();
  usbMIDI.read();
  
  // Leveraging the overload
  if (clock_count >= interval_time) {
    
    digitalWrite(ledPin, LOW);

    // Kick
    byte kickPitch = map(analogRead(A0), 0, 1023, 0, 255);
    if(kick.getPitch() != kickPitch){
      kick.setPitch(kickPitch);
    }
   
    byte kickTone = map(analogRead(A1), 0, 1023, 0, 255);
    if(kick.getTone() != kickTone){
      kick.setTone(kickTone);
    }
    
    byte kickDecay = map(analogRead(A2), 0, 1023, 0, 255);
    if(kick.getDecay() != kickDecay){
      kick.setDecay(kickDecay);
    }

    // Snare
    byte snarePitch = map(analogRead(A3), 0, 1023, 0, 255);
    if(snare.getPitch() != snarePitch){
      snare.setPitch(snarePitch);
    }
   
    byte snareTone = map(analogRead(A4), 0, 1023, 0, 255);
    if(snare.getTone() != snareTone){
      snare.setTone(snareTone);
    }
    
    byte snareDecay = map(analogRead(A5), 0, 1023, 0, 255);
    if(snare.getDecay() != snareDecay){
      snare.setDecay(snareDecay);
    }

    // Hihat
    byte hihatPitch = map(analogRead(A6), 0, 1023, 0, 255);
    if(hihat.getPitch() != hihatPitch){
      hihat.setPitch(hihatPitch);
    }
   
    byte hihatTone = map(analogRead(A7), 0, 1023, 0, 255);
    if(hihat.getTone() != hihatTone){
      hihat.setTone(hihatTone);
    }
    
    byte hihatDecay = map(analogRead(A8), 0, 1023, 0, 255);
    if(hihat.getDecay() != hihatDecay){
      hihat.setDecay(hihatDecay);
    }
    
    clock_count = 0;
  }
}

/**
 * Midi note on callback
 */
void onNoteOn(byte channel, byte note, byte velocity) {
  switch(note){
    case 36: 
      kick.noteOn();
      digitalWrite(ledPin, HIGH);
    break;
    case 38: 
      snare.noteOn();
    break;
    case 42: 
      hihat.noteOn();
    break;
  }
}