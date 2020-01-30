#ifndef Hihat_h
#define Hihat_h

#include <Audio.h>

// GUItool: begin automatically generated code
//AudioSynthWaveformSine   modulator;          //xy=55,223
//AudioSynthNoiseWhite     noise;         //xy=57,173
//AudioSynthWaveformSineModulated sine;       //xy=173,259
//AudioFilterBiquad        noiseFilter;        //xy=179,186
//AudioMixer4              mixer;         //xy=309,267
//AudioEffectEnvelope      envelope;      //xy=447,267
//AudioFilterBiquad        filter;        //xy=581,264
//AudioOutputI2S           i2s1;           //xy=733,264
//AudioConnection          patchCord1(modulator, sine);
//AudioConnection          patchCord2(noise, noiseFilter);
//AudioConnection          patchCord3(sine, 0, mixer, 1);
//AudioConnection          patchCord4(noiseFilter, 0, mixer, 0);
//AudioConnection          patchCord5(mixer, envelope);
//AudioConnection          patchCord6(envelope, filter);
//AudioConnection          patchCord7(filter, 0, i2s1, 0);
//AudioConnection          patchCord8(filter, 0, i2s1, 1);
// GUItool: end automatically generated code



/*
 * Hihat
 */
class Hihat{
  private:
    byte pitch;
    byte tone;
    byte decay;
    AudioSynthWaveformSine     *modulator;
    AudioSynthWaveformSineModulated *sine;
    AudioSynthNoiseWhite       *noise;
    AudioFilterBiquad          *noiseFilter;
    AudioEffectEnvelope        *envelope;
    AudioFilterBiquad          *filter;
    AudioMixer4                *mixer;
    AudioConnection* patchCords[7];
    AudioMixer4 *output;


  public:
    Hihat();
    
    AudioMixer4 * getOutput();
    void noteOn();
    void setPitch(byte pitch);
    void setTone(byte tone);
    void setDecay(byte decay);
    byte getPitch();
    byte getTone();
    byte getDecay();
};

/**
 * Constructor
 */
inline Hihat::Hihat(){
  this->modulator = new AudioSynthWaveformSine();
  this->modulator->amplitude(1);
  this->sine = new AudioSynthWaveformSineModulated();
  this->sine->frequency(5000);
  this->sine->amplitude(1);
  this->noise = new AudioSynthNoiseWhite();
  this->noise->amplitude(0.5);
  this->noiseFilter = new AudioFilterBiquad();
  this->noiseFilter->setHighpass(0, 4000);
  this->noiseFilter->setHighpass(1, 3000);
  this->noiseFilter->setHighpass(2, 2000);
  this->envelope = new AudioEffectEnvelope();
  this->envelope->attack(4);
  this->envelope->sustain(0);
  this->envelope->release(1);
  this->filter = new AudioFilterBiquad();
  this->mixer = new AudioMixer4();
  this->mixer->gain(0, 1);
  this->mixer->gain(1, 0.3);
  
  this->output = new AudioMixer4();
  this->output->gain(0, 1);

  this->patchCords[0] = new AudioConnection(*this->noise, 0, *this->noiseFilter, 0);
  this->patchCords[1] = new AudioConnection(*this->noiseFilter, 0, *this->mixer, 0);
  this->patchCords[2] = new AudioConnection(*this->modulator, 0, *this->sine, 0);
  this->patchCords[3] = new AudioConnection(*this->sine, 0, *this->mixer, 1);
  this->patchCords[4] = new AudioConnection(*this->mixer, 0, *this->envelope, 0);
  this->patchCords[5] = new AudioConnection(*this->envelope, 0, *this->filter, 0);
  this->patchCords[6] = new AudioConnection(*this->filter, 0, *this->output, 0);
}

/**
 * Return the audio output
 */
inline AudioMixer4 * Hihat::getOutput(){
  return this->output;
}

/**
 * Note on
 */
inline void Hihat::noteOn() {
  this->envelope->noteOn();
}

/**
 * Set the pitch
 * @param[byte] pitch The pitch
 */
inline void Hihat::setPitch(byte pitch){
  this->pitch = pitch;
  unsigned int mappedFrequency = map(pitch, 0, 255, 1100, 2500);
  
  this->modulator->frequency(mappedFrequency);
}

/**
 * Set the decay
 * @param[byte] decay The decay
 */
inline void Hihat::setDecay(byte decay){
  this->decay = decay;
  unsigned int mappedDecay = map(decay, 0, 255, 10, 1000);
  
  this->envelope->decay(mappedDecay);
}

/**
 * Set the tone
 * @param tone The tone
 */
inline void Hihat::setTone(byte tone){
  this->tone = tone;
  unsigned int mappedTone = map(tone, 0, 255, 1000, 16000);

  this->filter->setHighpass(0, mappedTone);
}


/**
 * Get the pitch
 * @returns The pitch
 */
inline byte Hihat::getPitch(){
  return this->pitch;
}

/**
 * Get the tone
 * @returns The tone
 */
inline byte Hihat::getTone(){
  return this->tone;
}

/**
 * Get the decay
 * @returns The decay
 */
inline byte Hihat::getDecay(){
  return this->decay;
}
#endif