#include "lankey.h"
static int fd = -1;
int kbd_init(){
	int k=0;
	while(fd < 0 && UINPUT_FILEPATHS[k] != NULL){
		fd = open(UINPUT_FILEPATHS[k], O_WRONLY | O_NONBLOCK);
		k++;
	}
    if(fd < 0)
        die("error: open device for kbd.");
    return fd;
}

void kbd_create(){
	struct uinput_user_dev uidev;
    memset(&uidev, 0, sizeof(uidev));
    snprintf(uidev.name, UINPUT_MAX_NAME_SIZE, "Chilau-keyboard");
    uidev.id.bustype = BUS_USB;
    uidev.id.vendor  = 0x1a2c;
    uidev.id.product = 0x0e24;
    uidev.id.version = 0;
    
    if(write(fd, &uidev, sizeof(uidev)) < 0)
        die("error: write kdb info.");
    if(ioctl(fd, UI_DEV_CREATE) < 0)
        die("error: ioctl creating device");
}

void kbd_sync(){
	const struct input_event ev_syn={.type = EV_SYN,.code=0,.value=0};
    if(write(fd, &ev_syn, sizeof(struct input_event)) < 0)
		die("error: sync failed");
}

void kbd_destory(){
	if(ioctl(fd, UI_DEV_DESTROY) < 0)
		die("error: device destory");
    close(fd);
}
