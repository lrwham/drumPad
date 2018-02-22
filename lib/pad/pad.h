#ifndef PAD_H
#define PAD_H

class pad
{

  public:
    pad(int interuptPin, int MIDIchannel, int note);

  private:
    bool wasPressed;
};

#endif // ndef PAD_H