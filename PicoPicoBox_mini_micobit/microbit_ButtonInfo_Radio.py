# Pushing button information is sent via Radio
import radio
from microbit import *

# Connect to PC
#uart.init(115200)

# Connect using GPIO
uart.init(baudrate=19200, bits=8, parity=None, stop=1, tx=pin1, rx=pin0)

radio.config(group=0x03)
radio.on()

while True:

    if uart.any():
        recv = uart.read(1)
        data = str(recv, 'UTF-8')

        if data == 'D' or data == 'Y':
            radio.send('Yellow')

        elif data == 'L':
            radio.send('Purple')

        elif data == 'U':
            radio.send('Cyan')

        elif data == 'R':
            radio.send('Orange')

        elif data == 'X':
            radio.send('Blue')

        elif data == 'A':
            radio.send('Green')

        elif data == 'B':
            radio.send('Red')

        elif data == 'N':
            radio.send('Reset')
