#include <pad.h>
#include <Arduino.h>

pad::pad(int interuptPin, int MIDIchannel, int note){
     attachInterrupt(digitalPinToInterrupt(interuptPin), padOne, RISING);
}
