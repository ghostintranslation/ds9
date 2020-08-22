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
    // Snare
    Snare *snare;
    // Hihat
    Hihat *hihat;
    
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

    // Callbacks
    static void onTuneChange(byte inputIndex, unsigned int value, int diffToPrevious);
    static void onColorChange(byte inputIndex, unsigned int value, int diffToPrevious);
    static void onDecayChange(byte inputIndex, unsigned int value, int diffToPrevious);
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

  // Device callbacks
  this->device->setHandlePotentiometerChange(0, onTuneChange);
  this->device->setHandlePotentiometerChange(1, onTuneChange);
  this->device->setHandlePotentiometerChange(2, onTuneChange);
  this->device->setHandlePotentiometerChange(3, onColorChange);
  this->device->setHandlePotentiometerChange(4, onColorChange);
  this->device->setHandlePotentiometerChange(5, onColorChange);
  this->device->setHandlePotentiometerChange(6, onDecayChange);
  this->device->setHandlePotentiometerChange(7, onDecayChange);
  this->device->setHandlePotentiometerChange(8, onDecayChange);
}

/**
 * Update
 */
inline void DS9::update(){
  this->device->update();
  
  MIDI.read();
  usbMIDI.read();
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

/**
 * On Tune Change
 */
inline void DS9::onTuneChange(byte inputIndex, unsigned int value, int diffToPrevious){
  byte tune = map(
    value, 
    getInstance()->device->getAnalogMinValue(), 
    getInstance()->device->getAnalogMaxValue(),
    0,
    255
  );
    
  switch(inputIndex){
    case 0:
      // Kick
      getInstance()->kick->setPitch(tune);
    break;
    
    case 1:
      // Clap
      getInstance()->snare->setPitch(tune);
    break;

    case 2:
      // Hihat
      getInstance()->hihat->setPitch(tune);
    break;

    default:
    break;
  }
}

/**
 * On Color Change
 */
inline void DS9::onColorChange(byte inputIndex, unsigned int value, int diffToPrevious){
  byte color = map(
    value, 
    getInstance()->device->getAnalogMinValue(), 
    getInstance()->device->getAnalogMaxValue(),
    0,
    255
  );

  switch(inputIndex){
    case 3:
      // Kick
      getInstance()->kick->setTone(color);
    break;
    
    case 4:
      // Clap
      getInstance()->snare->setTone(color);
    break;

    case 5:
      // Hihat
      getInstance()->hihat->setTone(color);
    break;

    default:
    break;
  }
}

/**
 * On Decay Change
 */
inline void DS9::onDecayChange(byte inputIndex, unsigned int value, int diffToPrevious){
  byte decay = map(
    value, 
    getInstance()->device->getAnalogMinValue(), 
    getInstance()->device->getAnalogMaxValue(),
    0,
    255
  );

  switch(inputIndex){
    case 6:
      // Kick
      getInstance()->kick->setDecay(decay);
    break;
    
    case 7:
      // Clap
      getInstance()->snare->setDecay(decay);
    break;

    case 8:
      // Hihat
      getInstance()->hihat->setDecay(decay);
    break;

    default:
    break;
  }
}
#endif
