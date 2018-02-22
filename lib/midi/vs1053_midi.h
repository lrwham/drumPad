#ifndef MIDI_H
#define MIDI_H

#include <Arduino.h>

void midiSetInstrument(uint8_t chan, uint8_t inst, Uart SerialPort);

void midiSetChannelVolume(uint8_t chan, uint8_t vol, Uart SerialPort);

void midiSetChannelBank(uint8_t chan, uint8_t bank, Uart SerialPort);

void midiNoteOn(uint8_t chan, uint8_t n, uint8_t vel, Uart SerialPort);

void midiNoteOff(uint8_t chan, uint8_t n, uint8_t vel, Uart SerialPort);

#endif //MIDI_H