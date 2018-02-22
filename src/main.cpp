#include <Adafruit_VS1053.h>
#include <vs1053_instruments.h>

#define SERIAL_DEBUG_BAUD 9600

// Solder closed jumper on bottom!

#define DRUMPAD_ANALOG_THRESHOLD 200
#define MIDI_START_STOP_DELAY 5
#define PAD1 14
#define PAD2 15
#define PAD3 16
#define PAD4 17

// See http://www.vlsi.fi/fileadmin/datasheets/vs1053.pdf Pg 31
#define VS1053_BANK_DEFAULT 0x00
#define VS1053_BANK_DRUMS1 0x78
#define VS1053_BANK_DRUMS2 0x7F
#define VS1053_BANK_MELODY 0x79

// See http://www.vlsi.fi/fileadmin/datasheets/vs1053.pdf Pg 32 for more!
#define VS1053_GM1_OCARINA 80
#define VS1053_GM1_PIANO 1

#define VS1053_GM1_SNARE 38

#define MIDI_NOTE_ON 0x90
#define MIDI_NOTE_OFF 0x80
#define MIDI_CHAN_MSG 0xB0
#define MIDI_CHAN_BANK 0x00
#define MIDI_CHAN_VOLUME 0x07
#define MIDI_CHAN_PROGRAM 0xC0

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

void padOne()
{
  padOneOn = 1;
}
void padTwo()
{
  padTwoOn = 1;
}
void padThree()
{
  padThreeOn = 1;
}
void padFour()
{
  padFourOn = 1;
}

void setup()
{
  delay(1000);

  Serial.begin(SERIAL_DEBUG_BAUD);

  Serial.println("VS1053 MIDI test");

  VS1053_MIDI.begin(31250); // MIDI uses a 'strange baud rate'

  midiSetChannelBank(0, VS1053_BANK_DRUMS2);

  midiSetChannelVolume(0, 127);

  midiSetInstrument(0, VS1053_GM1_SNARE);

  attachInterrupt(digitalPinToInterrupt(PAD1), padOne, RISING);
  attachInterrupt(digitalPinToInterrupt(PAD2), padTwo, RISING);
  attachInterrupt(digitalPinToInterrupt(PAD3), padThree, RISING);
  attachInterrupt(digitalPinToInterrupt(PAD4), padFour, RISING);
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