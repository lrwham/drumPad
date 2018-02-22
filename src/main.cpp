#include <Adafruit_VS1053.h>
#include <vs1053_instruments.h>
#include <vs1053_registers.h>
//#include <midi.h>


#define SERIAL_DEBUG_BAUD 9600
#define MIDI_BAUD 31250

#define DRUMPAD_ANALOG_THRESHOLD 200
#define MIDI_START_STOP_DELAY 5
#define PAD1_PIN 14
#define PAD2_PIN 15
#define PAD3_PIN 16
#define PAD4_PIN 17

#if defined(__AVR_ATmega32U4__) || defined(ARDUINO_SAMD_FEATHER_M0) || defined(TEENSYDUINO) || defined(ARDUINO_STM32_FEATHER)
#define VS1053_MIDI Serial1
#elif defined(ESP32)
HardwareSerial Serial1(2);
#define VS1053_MIDI Serial1
#elif defined(ESP8266)
#define VS1053_MIDI Serial
#endif

volatile bool padOneOn = 0;
volatile bool padTwoOn = 0;
volatile bool padThreeOn = 0;
volatile bool padFourOn = 0;

void midiSetInstrument(uint8_t chan, uint8_t inst)
{
  if (chan > 15)
    return;
  inst--; // page 32 has instruments starting with 1 not 0 :(
  if (inst > 127)
    return;

  VS1053_MIDI.write(MIDI_CHAN_PROGRAM | chan);
  //delay(10);
  VS1053_MIDI.write(inst);
  //delay(10);
}

void midiSetChannelVolume(uint8_t chan, uint8_t vol)
{
  if (chan > 15)
    return;
  if (vol > 127)
    return;

  VS1053_MIDI.write(MIDI_CHAN_MSG | chan);
  VS1053_MIDI.write(MIDI_CHAN_VOLUME);
  VS1053_MIDI.write(vol);
}

void midiSetChannelBank(uint8_t chan, uint8_t bank)
{
  if (chan > 15)
    return;
  if (bank > 127)
    return;

  VS1053_MIDI.write(MIDI_CHAN_MSG | chan);
  VS1053_MIDI.write((uint8_t)MIDI_CHAN_BANK);
  VS1053_MIDI.write(bank);
}

void midiNoteOn(uint8_t chan, uint8_t n, uint8_t vel)
{
  if (chan > 15)
    return;
  if (n > 127)
    return;
  if (vel > 127)
    return;

  VS1053_MIDI.write(MIDI_NOTE_ON | chan);
  VS1053_MIDI.write(n);
  VS1053_MIDI.write(vel);
}

void midiNoteOff(uint8_t chan, uint8_t n, uint8_t vel)
{
  if (chan > 15)
    return;
  if (n > 127)
    return;
  if (vel > 127)
    return;

  VS1053_MIDI.write(MIDI_NOTE_OFF | chan);
  VS1053_MIDI.write(n);
  VS1053_MIDI.write(vel);
}

void padOneISR()
{
  padOneOn = 1;
}
void padTwoISR()
{
  padTwoOn = 1;
}
void padThreeISR()
{
  padThreeOn = 1;
}
void padFourISR()
{
  padFourOn = 1;
}

void setup()
{
  delay(1000);

  Serial.begin(SERIAL_DEBUG_BAUD);

  Serial.println("VS1053 MIDI test");

  VS1053_MIDI.begin(MIDI_BAUD); // MIDI uses a 'strange baud rate'

  midiSetChannelBank(0, VS1053_BANK_DRUMS2);

  midiSetChannelVolume(0, 127);

  midiSetInstrument(0, VS1053_GM1_SNARE);

  attachInterrupt(digitalPinToInterrupt(PAD1_PIN), padOneISR, RISING);
  attachInterrupt(digitalPinToInterrupt(PAD2_PIN), padTwoISR, RISING);
  attachInterrupt(digitalPinToInterrupt(PAD3_PIN), padThreeISR, RISING);
  attachInterrupt(digitalPinToInterrupt(PAD4_PIN), padFourISR, RISING);
}

void loop()
{
  if (padOneOn)
  {
    midiNoteOn(0, VS1053_ACOUSTIC_BASS_DRUM, 127);
    Serial.print("Percussion: ");
    Serial.println(percussionInstruments[VS1053_ACOUSTIC_BASS_DRUM - INDEX_START_PERCUSSION].prettyName);
    padOneOn = 0;
  }
  if (padTwoOn)
  {
    midiNoteOn(0, VS1053_ACOUSTIC_SNARE, 127);
    Serial.print("Percussion: ");
    Serial.println(percussionInstruments[VS1053_ACOUSTIC_SNARE - INDEX_START_PERCUSSION].prettyName);
    padTwoOn = 0;
  }
  if (padThreeOn)
  {
    midiNoteOn(0, VS1053_CLOSED_HI_HAT, 127);
    Serial.print("Percussion: ");
    Serial.println(percussionInstruments[VS1053_CLOSED_HI_HAT - INDEX_START_PERCUSSION].prettyName);
    padThreeOn = 0;
  }
  if (padFourOn)
  {
    midiNoteOn(0, VS1053_CRASH_CYMBAL_1, 127);
    Serial.print("Percussion: ");
    Serial.println(percussionInstruments[VS1053_CRASH_CYMBAL_1 - INDEX_START_PERCUSSION].prettyName);
    padFourOn = 0;
  }

  delay(10);

  //midiNoteOff(0, VS1053_ACOUSTIC_BASS_DRUM, 127);
  // midiNoteOff(0, VS1053_ACOUSTIC_SNARE, 127);
  // midiNoteOff(0, VS1053_CLOSED_HI_HAT, 127);
  // midiNoteOff(0, VS1053_CRASH_CYMBAL_1, 127);

  // delay(250);
  /*
    for (uint8_t i = 27; i < 88; i++)
  {
    midiNoteOn(0, i, 127);
    delay(400);
    midiNoteOff(0, i, 127);
  }
  */
  //delay(10);
}