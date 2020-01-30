#ifndef Snare_h
#define Snare_h

#include <Audio.h>


// GUItool: begin automatically generated code
//AudioSynthNoisePink      pink;          //xy=56.5,151
//AudioSynthWaveform       clapReverseSaw;      //xy=82.5,218
//AudioSynthSimpleDrum     snareDrum;           //xy=207,286
//AudioEffectEnvelope      snareEnvelope;       //xy=223,330
//AudioEffectMultiply      clapMultiply;      //xy=268,210
//AudioEffectEnvelope      clapEnvelope;      //xy=294,139
//AudioEffectFreeverb      clapVerb;      //xy=348,84
//AudioMixer4              mixer;         //xy=467,257
//AudioFilterBiquad        filter;        //xy=589,255
//AudioOutputI2S           i2s1;           //xy=717,236
//AudioOutputUSB           usb1;           //xy=718,278
//AudioConnection          patchCord1(pink, 0, clapMultiply, 0);
//AudioConnection          patchCord2(pink, snareEnvelope);
//AudioConnection          patchCord3(clapReverseSaw, 0, clapMultiply, 1);
//AudioConnection          patchCord4(snareDrum, 0, mixer, 2);
//AudioConnection          patchCord5(snareEnvelope, 0, mixer, 3);
//AudioConnection          patchCord6(clapMultiply, clapEnvelope);
//AudioConnection          patchCord7(clapEnvelope, 0, mixer, 1);
//AudioConnection          patchCord8(clapEnvelope, clapVerb);
//AudioConnection          patchCord9(clapVerb, 0, mixer, 0);
//AudioConnection          patchCord10(mixer, filter);
//AudioConnection          patchCord11(filter, 0, i2s1, 0);
//AudioConnection          patchCord12(filter, 0, i2s1, 1);
//AudioConnection          patchCord13(filter, 0, usb1, 0);
//AudioConnection          patchCord14(filter, 0, usb1, 1);
// GUItool: end automatically generated code

/*
 * Snare
 */
class Snare{
  private:
    byte pitch;
    byte tone;
    byte decay;
    AudioSynthNoisePink      *pink;
    AudioSynthWaveform       *clapReverseSaw;
    AudioEffectMultiply      *clapMultiply;
    AudioEffectEnvelope      *clapEnvelope;
    AudioEffectFreeverb      *clapVerb;
    AudioSynthSimpleDrum     *snareDrum;
    AudioEffectEnvelope      *snareEnvelope;
    AudioMixer4              *mixer;
    AudioFilterBiquad        *filter;
    AudioConnection* patchCords[12];
    AudioMixer4 *output;


  public:
    Snare();
    
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
inline Snare::Snare(){
  this->pink = new AudioSynthNoisePink();
  this->pink->amplitude(1);

  this->clapReverseSaw = new AudioSynthWaveform();
  this->clapReverseSaw->begin(1,50,WAVEFORM_SAWTOOTH_REVERSE);
  this->clapReverseSaw->offset(1);

  this->clapMultiply = new AudioEffectMultiply();

  this->clapEnvelope = new AudioEffectEnvelope();
  this->clapEnvelope->attack(4);
  this->clapEnvelope->sustain(0);
  this->clapEnvelope->release(1);
  this->clapEnvelope->decay(90);

  this->clapVerb = new AudioEffectFreeverb();
  this->clapVerb->roomsize(0.2);
  this->clapVerb->damping(0.5);
  
  this->snareDrum = new AudioSynthSimpleDrum();
  this->snareDrum->pitchMod(0.52);
  this->snareDrum->frequency(180);
  this->snareDrum->length(150);
  
  this->snareEnvelope = new AudioEffectEnvelope();
  this->snareEnvelope->attack(4);
  this->snareEnvelope->sustain(0);
  this->snareEnvelope->release(1);
  this->snareEnvelope->decay(300);

  this->mixer = new AudioMixer4();
  this->mixer->gain(0, 0.3);
  this->mixer->gain(1, 0.5);
  this->mixer->gain(2, 1.2);
  this->mixer->gain(3, 0.3);
  
  this->filter = new AudioFilterBiquad();
  filter->setBandpass(0, 6000);
  
  this->output = new AudioMixer4();
  this->output->gain(0, 1);

  this->patchCords[0] = new AudioConnection(*this->pink, 0, *this->clapMultiply, 0);
  this->patchCords[1] = new AudioConnection(*this->pink, 0, *this->snareEnvelope, 0);
  this->patchCords[2] = new AudioConnection(*this->clapReverseSaw, 0, *this->clapMultiply, 1);
  this->patchCords[3] = new AudioConnection(*this->snareDrum, 0, *this->mixer, 2);
  this->patchCords[4] = new AudioConnection(*this->snareEnvelope, 0, *this->mixer, 3);
  this->patchCords[5] = new AudioConnection(*this->clapMultiply, 0, *this->clapEnvelope, 0);
  this->patchCords[6] = new AudioConnection(*this->clapEnvelope, 0, *this->mixer, 1);
  this->patchCords[7] = new AudioConnection(*this->clapEnvelope, 0, *this->clapVerb, 0);
  this->patchCords[8] = new AudioConnection(*this->clapVerb, 0, *this->mixer, 0);
  this->patchCords[9] = new AudioConnection(*this->mixer, 0, *this->filter, 0);
  this->patchCords[10] = new AudioConnection(*this->filter, 0, *this->output, 0);
}

/**
 * Return the audio output
 */
inline AudioMixer4 * Snare::getOutput(){
  return this->output;
}

/**
 * Note on
 */
inline void Snare::noteOn() {
  this->snareDrum->noteOn();
  this->snareEnvelope->noteOn();
  this->clapEnvelope->noteOn();
}

/**
 * Set the pitch
 * @param[byte] pitch The pitch
 */
inline void Snare::setPitch(byte pitch){
  this->pitch = pitch;
  unsigned int mappedFrequency = map(pitch, 0, 255, 100, 500);
  this->snareDrum->frequency(mappedFrequency);
}

/**
 * Set the decay
 * @param[byte] decay The decay
 */
inline void Snare::setDecay(byte decay){
  this->decay = decay;
  byte mappedSnareDecay = map(decay, 0, 255, 100, 160);
  unsigned int mappedSnareNoiseDecay = map(decay, 0, 255, 0, 400);
  byte mappedClapDecay = map(decay, 0, 255, 10, 100);

  this->snareDrum->length(mappedSnareDecay);
  this->snareEnvelope->decay(mappedSnareNoiseDecay);
  this->clapEnvelope->decay(mappedClapDecay);
}

/**
 * Set the tone
 * @param tone The tone
 */
inline void Snare::setTone(byte tone){
  this->tone = tone;
//  unsigned int mappedTone = map(tone, 0, 255, 500, 6000);
  //this->filter->setLowpass(0, mappedTone);

  float mappedTone = (float)map((float)tone, (float)0, (float)255, (float)0.0, (float)1.0);
  float mappedReverseTone = (float)map((float)tone, (float)0, (float)255, (float)1.0, (float)0.0);

  this->mixer->gain(0, 0.3*mappedTone);
  this->mixer->gain(1, 0.5*mappedTone);
  this->mixer->gain(2, 1.2*mappedReverseTone);
  this->mixer->gain(3, 0.3*mappedReverseTone);
}


/**
 * Get the pitch
 * @returns The pitch
 */
inline byte Snare::getPitch(){
  return this->pitch;
}

/**
 * Get the tone
 * @returns The tone
 */
inline byte Snare::getTone(){
  return this->tone;
}

/**
 * Get the decay
 * @returns The decay
 */
inline byte Snare::getDecay(){
  return this->decay;
}
#endif