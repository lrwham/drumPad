#ifndef VS1053_INSTRUMENTS_H
#define VS1053_INSTRUMENTS_H

#include <Arduino.h>

#define NUM_MELODIC_INSTRUMENTS 99
#define NUM_PERCUSSION_INSTRUMENTS 61
#define INDEX_START_PERCUSSION 27

#define VS1053_HIGH_Q 27
#define VS1053_SLAP 28
#define VS1053_SCRATCH_PUSH 29 // EXC7
#define VS1053_SCRATCH_PULL 30 // EXC7
#define VS1053_STICKS 31
#define VS1053_SQUARE_CLICK 32
#define VS1053_METRONOME_CLICK 33
#define VS1053_METRONOME_BELL 34
#define VS1053_ACOUSTIC_BASS_DRUM 35
#define VS1053_BASS_DRUM_1 36
#define VS1053_SIDE_STICK 37
#define VS1053_ACOUSTIC_SNARE 38
#define VS1053_HAND_CLAP 39
#define VS1053_ELECTRIC_SNARE 40
#define VS1053_LOW_FLOOR_TOM 41
#define VS1053_CLOSED_HI_HAT 42 // EXC1
#define VS1053_HIGH_FLOOR_TOM 43
#define VS1053_PEDAL_HI_HAT 44 // EXC1
#define VS1053_LOW_TOM 45
#define VS1053_OPEN_HI_HAT 46 // EXC1
#define VS1053_LOW_MID_TOM 47
#define VS1053_HIGH_MID_TOM 48
#define VS1053_CRASH_CYMBAL_1 49
#define VS1053_HIGH_TOM 50
#define VS1053_RIDE_CYMBAL_1 51
#define VS1053_CHINESE_CYMBAL 52
#define VS1053_RIDE_BELL 53
#define VS1053_TAMBOURINE 54
#define VS1053_SPLASH_CYMBAL 55
#define VS1053_COWBELL 56
#define VS1053_CRASH_CYMBAL_2 57
#define VS1053_VIBRA_SLAP 58
#define VS1053_RIDE_CYMBAL_2 59
#define VS1053_HIGH_BONGO 60
#define VS1053_LOW_BONGO 61
#define VS1053_MUTE_HI_CONGA 62
#define VS1053_OPEN_HI_CONGA 63
#define VS1053_LOW_CONGA 64
#define VS1053_HIGH_TIMBALE 65
#define VS1053_LOW_TIMBALE 66
#define VS1053_HIGH_AGOGO 67
#define VS1053_LOW_AGOGO 68
#define VS1053_CABASA 69
#define VS1053_MARACAS 70
#define VS1053_SHORT_WHISTLE 71  //EXC2
#define VS1053_LONG_WHISTLE 2 72 // EXC2
#define VS1053_SHORT_GUIRO 73    // EXC3
#define VS1053_LONG_GUIRO 74     // EXC3
#define VS1053_CLAVES 75
#define VS1053_HI_WOOD_BLOCK 76
#define VS1053_LOW_WOOD_BLOCK 77
#define VS1053_MUTE_CUICA 78    // EXC4
#define VS1053_OPEN_CUICA 79    // EXC4
#define VS1053_MUTE_TRIANGLE 80 // EXC5
#define VS1053_OPEN_TRIANGLE 81 // EXC5
#define VS1053_SHAKER 82
#define VS1053_JINGLE_BELL 83
#define VS1053_BELL_TREE 84
#define VS1053_CASTANETS 85
#define VS1053_MUTE_SURDO 86 // EXC6
#define VS1053_OPEN_SURDO 87 // EXC6

using namespace std;

struct InstrumentVS1053
{
    int id;
    String prettyName;
};

struct InstrumentVS1053 percussionInstruments[NUM_PERCUSSION_INSTRUMENTS] = {
    {VS1053_HIGH_Q, "High Q"},
    {VS1053_SLAP, "Slap"},
    {VS1053_SCRATCH_PUSH, "Scratch Push EXC7"},
    {VS1053_SCRATCH_PULL, "Scratch Pull EXC7"},
    {VS1053_STICKS, "Sticks"},
    {VS1053_SQUARE_CLICK, "Square Cick"},
    {VS1053_METRONOME_CLICK, "Metronome Click"},
    {VS1053_METRONOME_BELL, "Metronome Bell"},
    {VS1053_ACOUSTIC_BASS_DRUM, "Acoustic Bass Drum"},
    {VS1053_BASS_DRUM_1, "Bass Drum 1"},
    {VS1053_SIDE_STICK, "Side Stick"},
    {VS1053_ACOUSTIC_SNARE, "Acoustic Snare Drum"},
    {VS1053_HAND_CLAP, "Hand Clap"},
    {VS1053_ELECTRIC_SNARE, "Electric Snare Drum"},
    {VS1053_LOW_FLOOR_TOM, "Low Floor Tom"},
    {VS1053_CLOSED_HI_HAT, "Closed Hi Hat"},
    {VS1053_HIGH_FLOOR_TOM, "High Floor Tom"},
    {VS1053_PEDAL_HI_HAT, "Pedal Hi Hat"}, // EXC1
    {VS1053_LOW_TOM, "Low Tom"},
    {VS1053_OPEN_HI_HAT, "Open Hi Hat"}, // EXC1
    {VS1053_LOW_MID_TOM, "Low Mid Tom"},
    {VS1053_HIGH_MID_TOM, "High Mid Tom"},
    {VS1053_CRASH_CYMBAL_1, "Crash Cymbal 1"}

};

#endif //VS1053_INSTRUMENTS_H
