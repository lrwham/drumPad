#ifndef VS1053_MIDI_H
#define VS1053_MIDI_H

#include <Arduino.h>

class VS1053_MIDI_Channel
{
  public:
    VS1053_MIDI_Channel(uint8_t chan, Uart* aSerialPort);

    VS1053_MIDI_Channel(uint8_t chan, uint8_t volume, uint8_t bank, Uart* aSerialPort);

    VS1053_MIDI_Channel(uint8_t chan, uint8_t volume, uint8_t bank, uint8_t instrument, Uart* aSerialPort);

    void midiSetInstrument(uint8_t instrument);

    void midiSetChannelVolume(uint8_t volume);

    void midiSetChannelBank(uint8_t bank);

    void midiNoteOn(uint8_t note, uint8_t velocity);

    void midiNoteOff(uint8_t note, uint8_t velocity);

  private:
    uint8_t mChannel;
    Uart* mSerialPort;
};

#endif // VS1053_MIDI_H