#include "libblinkstick.h"

bool print_debug = false;

void debug(const char *fmt, ...) {
  if (print_debug) {
    char buffer[256];
    va_list ap;
    va_start(ap, fmt);
    vsprintf(buffer, fmt, ap);
    va_end(ap);

    puts(buffer);
  }
}

void set_debug_true() {
  print_debug = true;
  debug("STARTING LIBBLINKSTICK WITH DEBUG LOGGING");
}

int is_product_and_vendor_id(int vendor_id, int product_id) {
  return ((vendor_id == BLINKSTICK_VENDOR_ID) && (product_id == BLINKSTICK_PRODUCT_ID));
}

int is_blinkstick(libusb_device *device) {
  struct libusb_device_descriptor desc;
  int result = libusb_get_device_descriptor(device, &desc);

  if (result >= 0) {
    if (is_product_and_vendor_id(desc.idVendor, desc.idProduct)) {
      debug("Found the blinkstick\n");

      return true;
    }
  }

  return false;
}

libusb_device_handle* claim_device(libusb_device* device) {
  if (device == NULL) {
    debug("No device to claim\n");
    return NULL;
  }

  libusb_device_handle *dev_handle = NULL;
  int open_device_result;

  open_device_result = libusb_open(device, &dev_handle);

  if (open_device_result >= 0) {
    libusb_claim_interface(dev_handle, 0);
    libusb_ref_device(device);
  } else {
    debug("Failed at claiming device\n");
  }

  return dev_handle;
}

int find_all_blinkstick(blinkstick_device *list[]) {
  libusb_device **devices;
  libusb_context *context = NULL;
  int count = 0;

  ssize_t device_count;
  debug("Initializing USB context");

  libusb_init(&context);
  if (print_debug) {
    libusb_set_debug(context, 3);
  }

  device_count = libusb_get_device_list(context, &devices);
  debug("Found %d usb devices.", device_count);
  libusb_device *blinkstick = NULL;
  libusb_device_handle *dev_handle;

  int i;
  for(i = 0; i < device_count; i++) {
    libusb_device *device = devices[i];

    if(is_blinkstick(device)) {
      blinkstick = device;
      libusb_device_handle *dev_handle = claim_device(blinkstick);
      blinkstick_device *bdevice = malloc(sizeof(blinkstick_factory));
      bdevice->handle = dev_handle;
      bdevice->usb_context = context;
      list[count++] = bdevice;
    }
  }

  libusb_free_device_list(devices, 1);
  return count;
}

void set_color(int index, rgb_color *color, blinkstick_device *blinkstick) {
  unsigned char hex_index[1];
  hex_index[0] = (index & 0xff);
  unsigned char color_to_transfer[6] = {'\x05', '\x00', hex_index[0], color->bytes[0], color->bytes[1],color->bytes[2] };
  libusb_control_transfer(blinkstick->handle, 0x20, 0x9, 0x0005, 0x0000, color_to_transfer, 6, 2);
}


void destroy_blinkstick(blinkstick_device *device) {
  libusb_close(device->handle);
  libusb_exit(device->usb_context);
  free(device);
}

blinkstick_device* blinkstick_factory(libusb_device_handle *handle, libusb_context *context) {
  blinkstick_device *device = malloc(sizeof(blinkstick_factory));
  device->handle = handle;
  device->usb_context = context;
  return device;
}

// RGB
rgb_color* rgb_color_factory(int red, int green, int blue) {
  rgb_color *color = malloc(sizeof(rgb_color));

  color->red = red;
  color->green = green;
  color->blue = blue;
  color->bytes = rgb_to_char(color);

  return color;
}

unsigned char * rgb_to_char(rgb_color *color) {
  unsigned char* bytes = malloc(sizeof(unsigned char[3]));
  bytes[0] = (color->red & 0xff);
  bytes[1] = (color->green & 0xff);
  bytes[2] = (color->blue & 0xff);

  return bytes;
}

void destroy_color(rgb_color *color) {
  free(color->bytes);
  free(color);
}

