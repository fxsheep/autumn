# autumn
Baremetal shell for Renesas UPD814400-Q11-A/Canon QK1-8798

## Build
```
make CROSS_COMPILE=arm-none-eabi-
make
```

## Flash
**Make sure to backup the original firmware.** 

Use your favorite 25-series flash programmer with a in-system-programming clip, program `build/firmware.bin` to 0x0 of the flash.   

You may need to lower the supply voltage to prevent the SoC booting and interfere with flash access.  

In case you use glasgow, you can use `flash.sh`.  

Note that programming in-system is generally a bad idea. If you do care, desolder the chip, program it and solder it back.

## Usage
Solder TX/RX/GND to the unpopulated SH-1.0 connector pads, or, better, solder a SH-1.0 socket. The exact location and pinout of this connector varies between printer models.

Then use your favorite UART-to-USB cable and software to connect to it:
```
picocom -b 19200 /dev/ttyUSB0
```
Note that the SoC boots immediately after giving power to the printer. The "power button" on the panel isn't actually a power button but a sleep button. The SoC never fully powers down.

## References
 - This project is based on [fernly](https://github.com/xobs/fernly)