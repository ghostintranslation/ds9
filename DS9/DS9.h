#ifndef DS9_h
#define DS9_h

#include <Audio.h>
#include <MIDI.h>
MIDI_CREATE_DEFAULT_INSTANCE(); // MIDI library init

#include "Motherboard9.h"
#include "Kick.h"
#include "Snare.h"
#include "Hihat.h"

/*
 * DS9
 */
class DS9{
  private:
    static DS9 *instance;
    DS9();
   
    // Motherboard
    Motherboard9 *device;
    
    // Kick
    Kick *kick;
    byte kickTuneInputIndex = 0;
    byte kickColorInputIndex = 3;
    byte kickDecayInputIndex = 6;
    int kickTune = 0;
    int kickColor = 0;
    int kickDecay = 0;
    // Snare
    Snare *snare;
    byte snareTuneInputIndex = 1;
    byte snareColorInputIndex = 4;
    byte snareDecayInputIndex = 7;
    int snareTune = 0;
    int snareColor = 0;
    int snareDecay = 0;
    // Hihat
    Hihat *hihat;
    byte hihatTuneInputIndex = 2;
    byte hihatColorInputIndex = 5;
    byte hihatDecayInputIndex = 8;
    int hihatTune = 0;
    int hihatColor = 0;
    int hihatDecay = 0;
    
    // Output
    AudioMixer4 *output;
    AudioConnection* patchCords[3];

    // Clock
    byte updateMillis = 10;
    elapsedMillis clockUpdate;

    
  public:
    static DS9 *getInstance();
    void init();
    void update();
    static void noteOn(byte channel, byte note, byte velocity);
    AudioMixer4 * getOutput();
};

// Singleton pre init
DS9 * DS9::instance = nullptr;

/**
 * Constructor
 */
inline DS9::DS9(){
  this->kick = new Kick();
  this->hihat = new Hihat();
  this->snare = new Snare();
  
  this->device = Motherboard9::getInstance();
  
  this->output = new AudioMixer4();
  this->output->gain(0, 1 );
  this->output->gain(1, 1 );
  this->output->gain(2, 1 );

  this->patchCords[0] = new AudioConnection(*this->kick->getOutput(),  0, *this->output, 0);
  this->patchCords[1] = new AudioConnection(*this->hihat->getOutput(), 0, *this->output, 1);
  this->patchCords[2] = new AudioConnection(*this->snare->getOutput(), 0, *this->output, 2);
}

/**
 * Singleton instance
 */
inline DS9 *DS9::getInstance()    {
  if (!instance)
     instance = new DS9;
  return instance;
}

/**
 * Init
 */
inline void DS9::init(){
  // 0 = empty, 1 = button, 2 = potentiometer, 3 = encoder
  byte controls[9] = {2,2,2, 2,2,2, 2,2,2};
  this->device->init(controls);

  MIDI.setHandleNoteOn(noteOn);
  MIDI.begin(MIDI_CHANNEL_OMNI);
  usbMIDI.setHandleNoteOn(noteOn);
}

/**
 * Update
 */
inline void DS9::update(){
  this->device->update();
  
  MIDI.read();
  usbMIDI.read();
  
  if(this->clockUpdate > this->updateMillis){
    // Kick Tune
    byte kickTune = map(
      this->device->getInput(
      this->kickTuneInputIndex), 
      this->device->getAnalogMinValue(), 
      this->device->getAnalogMaxValue(),
      0,
      255
    );

    if(this->kickTune != kickTune){
      this->kickTune = kickTune;
      this->kick->setPitch(kickTune);
    }
    
    // Kick Color
    byte kickColor = map(
      this->device->getInput(
      this->kickColorInputIndex), 
      this->device->getAnalogMinValue(), 
      this->device->getAnalogMaxValue(),
      0,
      255
    );

    if(this->kickColor != kickColor){
      this->kickColor = kickColor;
      this->kick->setTone(kickColor);
    } 

    // Kick Decay
    byte kickDecay = map(
      this->device->getInput(
      this->kickDecayInputIndex), 
      this->device->getAnalogMinValue(), 
      this->device->getAnalogMaxValue(),
      0,
      255
    );

    if(this->kickDecay != kickDecay){
      this->kickDecay = kickDecay;
      this->kick->setDecay(kickDecay);
    }

    // Hihat Tune
    byte hihatTune = map(
      this->device->getInput(
      this->hihatTuneInputIndex), 
      this->device->getAnalogMinValue(), 
      this->device->getAnalogMaxValue(),
      0,
      255
    );

    if(this->hihatTune != hihatTune){
      this->hihatTune = hihatTune;
      this->hihat->setPitch(hihatTune);
    }
    
    // Hihat Color
    byte hihatColor = map(
      this->device->getInput(
      this->hihatColorInputIndex), 
      this->device->getAnalogMinValue(), 
      this->device->getAnalogMaxValue(),
      0,
      255
    );

    if(this->hihatColor != hihatColor){
      this->hihatColor = hihatColor;
      this->hihat->setTone(hihatColor);
    } 

    // Hihat Decay
    byte hihatDecay = map(
      this->device->getInput(
      this->hihatDecayInputIndex), 
      this->device->getAnalogMinValue(), 
      this->device->getAnalogMaxValue(),
      0,
      255
    );

    if(this->hihatDecay != hihatDecay){
      this->hihatDecay = hihatDecay;
      this->hihat->setDecay(hihatDecay);
    }

    // Snare Tune
    byte snareTune = map(
      this->device->getInput(
      this->snareTuneInputIndex), 
      this->device->getAnalogMinValue(), 
      this->device->getAnalogMaxValue(),
      0,
      255
    );

    if(this->snareTune != snareTune){
      this->snareTune = snareTune;
      this->snare->setPitch(snareTune);
    }
    
    // Snare Color
    byte snareColor = map(
      this->device->getInput(
      this->snareColorInputIndex), 
      this->device->getAnalogMinValue(), 
      this->device->getAnalogMaxValue(),
      0,
      255
    );

    if(this->snareColor != snareColor){
      this->snareColor = snareColor;
      this->snare->setTone(snareColor);
    } 

    // Snare Decay
    byte snareDecay = map(
      this->device->getInput(
      this->snareDecayInputIndex), 
      this->device->getAnalogMinValue(), 
      this->device->getAnalogMaxValue(),
      0,
      255
    );

    if(this->snareDecay != snareDecay){
      this->snareDecay = snareDecay;
      this->snare->setDecay(snareDecay);
    }
    
    this->clockUpdate = 0;
  }
}

/**
 * Note on
 */
inline void DS9::noteOn(byte channel, byte note, byte velocity){
  switch(note){
    case 36:
      getInstance()->kick->noteOn();
      getInstance()->device->setLED(0, 4);
    break;
    case 39:
      getInstance()->snare->noteOn();
      getInstance()->device->setLED(1, 4);
    break;
    case 42:
      getInstance()->hihat->noteOn();
      getInstance()->device->setLED(2, 4);
    break;
  }
}

/**
 * Return the audio output
 */
inline AudioMixer4 * DS9::getOutput(){
  return this->output;
}
#endif
