#ifndef __LANKEY_H__
#define __LANKEY_H__ 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
#include <linux/uinput.h>
#define die(x) printf(#x"\n");

static char * UINPUT_FILEPATHS[] = {
    "/dev/uinput",
    "/dev/input/uinput",
    NULL
};
int kbd_init();
void kbd_create();
#define DEV_INPUT_EVENT "/dev/input/event"
#define BITS_PER_LONG (sizeof(long) * 8)
#define NBITS(x) ((((x)-1)/BITS_PER_LONG)+1)
#define OFF(x)  ((x)%BITS_PER_LONG)
#define BIT(x)  (1UL<<OFF(x))
#define LONG(x) ((x)/BITS_PER_LONG)
#define test_bit(bit, array)	(((array)[LONG(bit)] >> OFF(bit)) & 1)
#define kbd_input(fd,ev) write(fd, ev, sizeof(struct input_event))
void kbd_destory();

#endif
