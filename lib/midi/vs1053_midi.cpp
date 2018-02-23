#include <vs1053_midi.h>
#include <Arduino.h>
//#include <Adafruit_VS1053.h>
#include <vs1053_registers.h>
#include <vs1053_instruments.h>

#define DEFAULT_VOLUME 127
#define DEFAULT_INSTRUMENT 25
#define DEFAULT_BANK VS1053_BANK_MELODY

void VS1053_MIDI_Channel::begin(uint32_t baud)
{
#if defined(__AVR__) && defined(USE_SW_SERIAL)
  if(gpsSwSerial) 
    gpsSwSerial->begin(baud);
  else 
#endif
    mSerialPort->begin(baud);

  delay(10);
}

VS1053_MIDI_Channel::VS1053_MIDI_Channel(uint8_t aChannel, HardwareSerial* aSerialPort)
{
  mChannel = aChannel;
  mSerialPort = aSerialPort;
  VS1053_MIDI_Channel::midiSetInstrument(DEFAULT_INSTRUMENT);
  VS1053_MIDI_Channel::midiSetChannelVolume(DEFAULT_VOLUME);
  VS1053_MIDI_Channel::midiSetChannelBank(DEFAULT_BANK);
}

VS1053_MIDI_Channel::VS1053_MIDI_Channel(uint8_t aChannel, uint8_t volume, uint8_t bank, HardwareSerial* aSerialPort)
{
  mChannel = aChannel;
  mSerialPort = aSerialPort;
  VS1053_MIDI_Channel::midiSetInstrument(DEFAULT_INSTRUMENT);
  VS1053_MIDI_Channel::midiSetChannelVolume(volume);
  VS1053_MIDI_Channel::midiSetChannelBank(bank);
}

VS1053_MIDI_Channel::VS1053_MIDI_Channel(uint8_t aChannel, uint8_t volume, uint8_t bank, uint8_t instrument, HardwareSerial* aSerialPort)
{
  mChannel = aChannel;
  mSerialPort = aSerialPort;
  VS1053_MIDI_Channel::midiSetInstrument(instrument);
  VS1053_MIDI_Channel::midiSetChannelVolume(volume);
  VS1053_MIDI_Channel::midiSetChannelBank(bank);
}

VS1053_MIDI_Channel::VS1053_MIDI_Channel(uint8_t aChannel, uint8_t volume, uint8_t bank, uint8_t instrument)
{
  mChannel = aChannel;
  // mSerialPort = aSerialPort;
  VS1053_MIDI_Channel::midiSetInstrument(instrument);
  VS1053_MIDI_Channel::midiSetChannelVolume(volume);
  VS1053_MIDI_Channel::midiSetChannelBank(bank);
}

void VS1053_MIDI_Channel::midiSetInstrument(uint8_t instrument)
{
  instrument--; // page 32 has instruments starting with 1 not 0 :(
  if (instrument > 127)
    return;

  mSerialPort->write(MIDI_CHAN_PROGRAM | mChannel);
  //delay(10);
  mSerialPort->write(instrument);
  //delay(10);
}

void VS1053_MIDI_Channel::midiSetChannelVolume(uint8_t volume)
{
  if (volume > 127)
    return;

  mSerialPort->write(MIDI_CHAN_MSG | mChannel);
  mSerialPort->write(MIDI_CHAN_VOLUME);
  mSerialPort->write(volume);
}

void VS1053_MIDI_Channel::midiSetChannelBank(uint8_t bank)
{
  if (bank > 127)
    return;

  mSerialPort->write(MIDI_CHAN_MSG | mChannel);
  mSerialPort->write((uint8_t)MIDI_CHAN_BANK);
  mSerialPort->write(bank);
}

void VS1053_MIDI_Channel::midiNoteOn(uint8_t note, uint8_t velocity)
{
  if (note > 127)
    return;
  if (velocity > 127)
    return;

  mSerialPort->write(MIDI_NOTE_ON | mChannel);
  mSerialPort->write(note);
  mSerialPort->write(velocity);
}

void VS1053_MIDI_Channel::midiNoteOff(uint8_t note, uint8_t velocity)
{
  if (note > 127)
    return;
  if (velocity > 127)
    return;

  mSerialPort->write(MIDI_NOTE_OFF | mChannel);
  mSerialPort->write(note);
  mSerialPort->write(velocity);
}
