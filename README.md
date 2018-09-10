#Linux Keyboard&Mouse Key Input Remapper#
-----
## Background
My *Lenovo laptop*'s both CTRL key is broken and hard to fix.
So I brought one 'Logitech M590' mouse with programmble keys.

In Windows is okay to redefine keycode, but linux
does not. After much work I found it's impossible to do it without coding,
so I write this.

## Feature

 - remap key by conf file
 - specific remap device, won't affect other input device
 - generic, no need to compile kernel module
 - work background at startup,  even in console!
 - high performance,  written in C

## Quick Start
change work directory to the util. 
```
    cmake .
    make
    make install
```
open the conf file (usually in /usr/local/etc/mkr.conf) and make appropriate change.
here is an example with comments:
    

```
/*
if device not found, retry every X millisecond.
must be larger than 0, else would exit rather wait
when device not plugged in.
recommend value: 1000, blance cpu use and delay.
*/
retry=1000
#forward events
//map mouse events
map_mouse = 1
//map key events
map_key = 1    
#found EV_MSC in evtest, no hurt to drop them.
map_msc=0
#run in background
daemon=1
#vaild only to debug builds
verbose=255
/* there cannot be extra space in section name. 
you can find the name of one input device by running:  
KeyRemapper -list device
*/
[Logitech M585/M590]
#keycode remap to key codes
#names can be found in remaper.c, keycodes are okay though.
ExtraBtn=LeftControl
SideBtn=RightCtrl
MiddleBtn=Enter
```

Then you can do a simple test by run `KeyRemapper`, if it works, 
write your own systemctl or rc.local line to make it start as soon as boot completed.


## Further More


It's somehow simple indeed,  any good idea or suggention is welcome.
If you like it, please star it :P !
