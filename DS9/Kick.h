#ifndef Kick_h
#define Kick_h

#include <Audio.h>

/*
// GUItool: begin automatically generated code
AudioSynthSimpleDrum     kick;          //xy=228,217
AudioSynthSimpleDrum     click;          //xy=229,165
AudioMixer4              mixer1;         //xy=422,193
AudioOutputI2S           i2s1;           //xy=598,199
AudioConnection          patchCord1(kick, 0, mixer1, 1);
AudioConnection          patchCord2(click, 0, mixer1, 0);
AudioConnection          patchCord3(mixer1, 0, i2s1, 0);
AudioConnection          patchCord4(mixer1, 0, i2s1, 1);
// GUItool: end automatically generated code
*/

/*
 * Kick
 */
class Kick{
  private:
    byte pitch;
    byte tone;
    byte decay;
    byte clickFrequency;
    byte clickExtraFrequency;
    AudioSynthSimpleDrum     *kick;
    AudioSynthSimpleDrum     *click;
    AudioConnection* patchCords[18];
    AudioMixer4 *output;


  public:
    Kick();
    
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
inline Kick::Kick(){
  this->click = new AudioSynthSimpleDrum();
  this->kick = new AudioSynthSimpleDrum();
  this->kick->pitchMod(0.5);

  this->output = new AudioMixer4();
  this->output->gain(0, 0.8);
  this->output->gain(1, 1);

  this->patchCords[0] = new AudioConnection(*this->click, 0, *this->output, 0);
  this->patchCords[1] = new AudioConnection(*this->kick, 0, *this->output, 1);
}

/**
 * Return the audio output
 */
inline AudioMixer4 * Kick::getOutput(){
  return this->output;
}

/**
 * Note on
 */
inline void Kick::noteOn() {
  this->click->noteOn();
  this->kick->noteOn();
}

/**
 * Set the pitch
 * @param[byte] pitch The pitch
 */
inline void Kick::setPitch(byte pitch){
  this->pitch = pitch;
  byte mappedFrequency = map(pitch, 0, 255, 20, 150);
  this->clickFrequency = mappedFrequency;
  
  this->kick->frequency(mappedFrequency);
  this->click->frequency(this->clickFrequency + this->clickExtraFrequency);
}

/**
 * Set the decay
 * @param[byte] decay The decay
 */
inline void Kick::setDecay(byte decay){
  this->decay = decay;
  unsigned int mappedDecay = map(decay, 0, 255, 10, 1000);
  byte mappedClickDecay = map(decay, 0, 255, 10, 110);
  
  this->kick->length(mappedDecay);
  this->click->length(mappedClickDecay);
}

/**
 * Set the tone
 * @param tone The tone
 */
inline void Kick::setTone(byte tone){
  this->tone = tone;
  float mappedTone = (float)map((float)tone, (float)0, (float)255, (float)0.5, (float)1);
  this->clickExtraFrequency = map(tone, 0, 255, 0, 15);
  
  this->click->pitchMod(mappedTone);
  this->click->frequency(this->clickFrequency + this->clickExtraFrequency);
}


/**
 * Get the pitch
 * @returns The pitch
 */
inline byte Kick::getPitch(){
  return this->pitch;
}

/**
 * Get the tone
 * @returns The tone
 */
inline byte Kick::getTone(){
  return this->tone;
}

/**
 * Get the decay
 * @returns The decay
 */
inline byte Kick::getDecay(){
  return this->decay;
}
#endif
