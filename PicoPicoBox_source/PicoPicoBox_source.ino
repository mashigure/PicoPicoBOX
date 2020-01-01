//------------------------------------------------------------
// PicoPico Box
//------------------------------------------------------------
#include <XBOXONE.h>

#define SOUND_OUT_PIN  (7)

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

//------------------------------------------------------------
// Buttons State
//------------------------------------------------------------
typedef struct{
    bool down;
    bool left;
    bool up;
    bool right;
    bool x;
    bool a;
    bool b;
    bool y;
} ButtonsState;

USB Usb;
XBOXONE Xbox(&Usb);

//------------------------------------------------------------
// sound freq. table
//------------------------------------------------------------
const int note[] = {
     8,    9,    9,   10,   10,   11,   12,   12,   13,   14,   15,   15, 
    16,   17,   18,   19,   21,   22,   23,   25,   26,   28,   29,   31, 
    33,   35,   37,   39,   41,   44,   46,   49,   52,   55,   58,   62,
    65,   69,   73,   78,   82,   87,   93,   98,  104,  110,  117,  123,
   131,  139,  147,  156,  165,  175,  185,  196,  208,  220,  233,  247,
   262,  277,  294,  311,  330,  349,  370,  392,  415,  440,  466,  494,
   523,  554,  587,  622,  659,  698,  740,  784,  831,  880,  932,  988,
  1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661, 1760, 1865, 1976,
  2093, 2217, 2349, 2489, 2637, 2794, 2960, 3136, 3322, 3520, 3729, 3951,
  4186, 4435, 4699, 4978, 5274, 5588, 5920, 6272, 6645, 7040, 7459, 7902, 
  8372, 8870, 9397, 9956,10548,11175,11840,12544
};

//------------------------------------------------------------
// Initialising
//------------------------------------------------------------
void setup()
{
    Serial.begin(31250); // USB MIDI

    if (Usb.Init() == -1)
    {
        while (1); //halt
    }
}

//------------------------------------------------------------
// Main Loop
//------------------------------------------------------------
void loop()
{
    Usb.Task();
    toneByGamepad();
    toneByUsbMidiIn();
    delay(1);
}

//------------------------------------------------------------
// play sound by using GamePad
//------------------------------------------------------------
void toneByGamepad()
{
    int shift      = 0;
    int analog_val = 0;
    int analog_l   = 0;
    int analog_r   = 0;
    ButtonsState curr_btn = {0};

    static byte key         = 0;
    static byte shifted_key = 255;
    static bool is_tone_on  = false;
    static int  last_analog = 0;
    static ButtonsState last_btn = {0};

    if (Xbox.XboxOneConnected)
    {
        curr_btn = getBtnSts();
        shift    = getShift();

        if (!last_btn.down & curr_btn.down)
        {
            if (is_tone_on) SendNoteOff(shifted_key);
            key = 60;
            shifted_key = key + shift;
            tone(SOUND_OUT_PIN, note[shifted_key]);
            SendNoteOn(shifted_key);
            is_tone_on = true;
        }
        else if (key == 60 && last_btn.down & !curr_btn.down)
        {
            noTone(SOUND_OUT_PIN);
            SendNoteOff(shifted_key);
            is_tone_on = false;
        }

        if (!last_btn.left & curr_btn.left)
        {
            if (is_tone_on) SendNoteOff(shifted_key);
            key = 62;
            shifted_key = key + shift;
            tone(SOUND_OUT_PIN, note[shifted_key]);
            SendNoteOn(shifted_key);
            is_tone_on = true;
        }
        else if (key == 62 && last_btn.left & !curr_btn.left)
        {
            noTone(SOUND_OUT_PIN);
            SendNoteOff(shifted_key);
            is_tone_on = false;
        }

        if (!last_btn.up & curr_btn.up)
        {
            if (is_tone_on) SendNoteOff(shifted_key);
            key = 64;
            shifted_key = key + shift;
            tone(SOUND_OUT_PIN, note[shifted_key]);
            SendNoteOn(shifted_key);
            is_tone_on = true;
        }
        else if (key == 64 && last_btn.up & !curr_btn.up)
        {
            noTone(SOUND_OUT_PIN);
            SendNoteOff(shifted_key);
            is_tone_on = false;
        }

        if (!last_btn.right & curr_btn.right)
        {
            if (is_tone_on) SendNoteOff(shifted_key);
            key = 65;
            shifted_key = key + shift;
            tone(SOUND_OUT_PIN, note[shifted_key]);
            SendNoteOn(shifted_key);
            is_tone_on = true;
        }
        else if (key == 65 && last_btn.right & !curr_btn.right)
        {
            noTone(SOUND_OUT_PIN);
            SendNoteOff(shifted_key);
            is_tone_on = false;
        }

        if (!last_btn.x & curr_btn.x)
        {
            if (is_tone_on) SendNoteOff(shifted_key);
            key = 67;
            shifted_key = key + shift;
            tone(SOUND_OUT_PIN, note[shifted_key]);
            SendNoteOn(shifted_key);
            is_tone_on = true;
        }
        else if (key == 67 && last_btn.x & !curr_btn.x)
        {
            noTone(SOUND_OUT_PIN);
            SendNoteOff(shifted_key);
            is_tone_on = false;
        }

        if (!last_btn.a & curr_btn.a)
        {
            if (is_tone_on) SendNoteOff(shifted_key);
            key = 69;
            shifted_key = key + shift;
            tone(SOUND_OUT_PIN, note[shifted_key]);
            SendNoteOn(shifted_key);
            is_tone_on = true;
        }
        else if (key == 69 && last_btn.a & !curr_btn.a)
        {
            noTone(SOUND_OUT_PIN);
            SendNoteOff(shifted_key);
            is_tone_on = false;
        }

        if (!last_btn.b & curr_btn.b)
        {
            if (is_tone_on) SendNoteOff(shifted_key);
            key = 71;
            shifted_key = key + shift;
            tone(SOUND_OUT_PIN, note[shifted_key]);
            SendNoteOn(shifted_key);
            is_tone_on = true;
        }
        else if (key == 71 && last_btn.b & !curr_btn.b)
        {
            noTone(SOUND_OUT_PIN);
            SendNoteOff(shifted_key);
            is_tone_on = false;
        }

        if (!last_btn.y & curr_btn.y)
        {
            if (is_tone_on) SendNoteOff(shifted_key);
            key = 72;
            shifted_key = key + shift;
            tone(SOUND_OUT_PIN, note[shifted_key]);
            SendNoteOn(shifted_key);
            is_tone_on = true;
        }
        else if (key == 72 && last_btn.y & !curr_btn.y)
        {
            noTone(SOUND_OUT_PIN);
            SendNoteOff(shifted_key);
            is_tone_on = false;
        }

        last_btn = curr_btn;


        /* Pitch bend */
        analog_l = Xbox.getAnalogHat(LeftHatY) /800;
        analog_r = Xbox.getAnalogHat(RightHatY)/800;
        if (abs(analog_r) < abs(analog_l))
        {
            analog_val = analog_l;
        }
        else
        {
            analog_val = analog_r;
        }

        if (analog_val != last_analog)
        {
            if (is_tone_on)
            {
                tone(SOUND_OUT_PIN, note[shifted_key] + 2 * analog_val);
            }
            SendPitchBend(100 * analog_val);
        }

        last_analog = analog_val;
    }
}

//------------------------------------------------------------
// play sound by USB MIDI INPUT
//------------------------------------------------------------
void toneByUsbMidiIn()
{
    static byte data[3];
    static int  dat_no = 0;
    static byte key    = 0;

    if (0 < Serial.available())
    {
        data[dat_no] = Serial.read();

        if ((data[dat_no]&0x80) == 0x80)
        {
            data[0] = data[dat_no];
            dat_no = 0;
        }

        if ((data[0]&0x80) == 0x80)
        {
            dat_no++;
        }

        if (dat_no == 3)
        {
            /* Note ON */
            if(((data[0]&0xf0) == 0x90) && 0 < data[2])
            {
                key = data[1];
                tone(SOUND_OUT_PIN, note[key]);
            }

            /* Note OFF */
            else if (((data[0]&0xf0) == 0x80) || (((data[0]&0xf0) == 0x90) && data[2] == 0))
            {
                if (data[1] == key)
                {
                    noTone(SOUND_OUT_PIN);
                }
            }

            dat_no = 0;
        }
    }
}

//------------------------------------------------------------
// get buttons Status (Press or not)
//------------------------------------------------------------
ButtonsState getBtnSts(void)
{
    ButtonsState btn = {0};

    if (Xbox.getButtonPress(DOWN) ) btn.down  = true;
    if (Xbox.getButtonPress(UP)   ) btn.up    = true;
    if (Xbox.getButtonPress(LEFT) ) btn.left  = true;
    if (Xbox.getButtonPress(RIGHT)) btn.right = true;
    if (Xbox.getButtonPress(X)    ) btn.x = true;
    if (Xbox.getButtonPress(A)    ) btn.a = true;
    if (Xbox.getButtonPress(B)    ) btn.b = true;
    if (Xbox.getButtonPress(Y)    ) btn.y = true;

    return btn;
}

//------------------------------------------------------------
// get R/L Buttons State to shift key
//------------------------------------------------------------
int getShift(void)
{
    int shift = 0;

    if (Xbox.getButtonPress(L1)) shift =   1;
    if (Xbox.getButtonPress(R1)) shift += 12;
    if (511 < Xbox.getButtonPress(L2)) shift +=  -1;
    if (511 < Xbox.getButtonPress(R2)) shift += -12;

    return shift;
}

//------------------------------------------------------------
// Note ON
//------------------------------------------------------------
void SendNoteOn(byte key)
{
    Serial.write(0x90);
    Serial.write(key);
    Serial.write(0x64);
}

//------------------------------------------------------------
// Note OFF
//------------------------------------------------------------
void SendNoteOff(byte key)
{
    Serial.write(0x80);
    Serial.write(key);
    Serial.write(0x00);
}

//------------------------------------------------------------
// Pitch bend
//------------------------------------------------------------
void SendPitchBend(int value)
{
    value += 8192;

    const unsigned msb = ((value >> 7) & 0x7f);
    const unsigned lsb = (value & 0x7f);

    Serial.write(0xE0);
    Serial.write(lsb);
    Serial.write(msb);
}

