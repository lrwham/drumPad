#include <vs1053_midi.h>
#include <Arduino.h>
//#include <Adafruit_VS1053.h>
#include <vs1053_registers.h>


void midiSetInstrument(uint8_t chan, uint8_t inst, Uart SerialPort)
{
  if (chan > 15)
    return;
  inst--; // page 32 has instruments starting with 1 not 0 :(
  if (inst > 127)
    return;

  SerialPort.write(MIDI_CHAN_PROGRAM | chan);
  //delay(10);
  SerialPort.write(inst);
  //delay(10);
}

void midiSetChannelVolume(uint8_t chan, uint8_t vol, Uart SerialPort)
{
  if (chan > 15)
    return;
  if (vol > 127)
    return;

  SerialPort.write(MIDI_CHAN_MSG | chan);
  SerialPort.write(MIDI_CHAN_VOLUME);
  SerialPort.write(vol);
}

void midiSetChannelBank(uint8_t chan, uint8_t bank, Uart SerialPort)
{
  if (chan > 15)
    return;
  if (bank > 127)
    return;

  SerialPort.write(MIDI_CHAN_MSG | chan);
  SerialPort.write((uint8_t)MIDI_CHAN_BANK);
  SerialPort.write(bank);
}

void midiNoteOn(uint8_t chan, uint8_t n, uint8_t vel, Uart SerialPort)
{
  if (chan > 15)
    return;
  if (n > 127)
    return;
  if (vel > 127)
    return;

  SerialPort.write(MIDI_NOTE_ON | chan);
  SerialPort.write(n);
  SerialPort.write(vel);
}

void midiNoteOff(uint8_t chan, uint8_t n, uint8_t vel, Uart SerialPort)
{
  if (chan > 15)
    return;
  if (n > 127)
    return;
  if (vel > 127)
    return;

  SerialPort.write(MIDI_NOTE_OFF | chan);
  SerialPort.write(n);
  SerialPort.write(vel);
}
