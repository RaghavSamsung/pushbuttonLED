#include "libblinkstick.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <wchar.h>
#include <string>

SSIC_LED_EXCEPTION::SSIC_LED_EXCEPTION(void)
{
  m_msg.append("Exception in ");
  m_msg.append(__FILE__);
  m_msg.append(" on line: ");
}
SSIC_LED_EXCEPTION::~SSIC_LED_EXCEPTION(void)
{
}
void SSIC_LED_EXCEPTION::setmsg(uint32_t line, std::string msg)
{
  m_msg = m_msg + std::to_string(line) + " " + msg;
}

SSIC_LED::SSIC_LED(void):
  m_debug(false),
  m_enum(false),
  m_open(false)
{
}

std::vector<uint8_t> SSIC_LED::rgb_to_message(uint8_t red, uint8_t green, uint8_t blue)
{
  std::vector<uint8_t> message(3);
  message[SSIC_LED::RED]   = red & 0xff;
  message[SSIC_LED::GREEN] = green & 0xff;
  message[SSIC_LED::BLUE]  = blue & 0xff;
  return message;
}
void SSIC_LED::debug(const char* fmt, ...)
{
  if (m_debug) {
    char buffer[1024];
    va_list ap;
    va_start(ap, fmt);
    vsprintf(buffer, fmt, ap);
    va_end(ap);
    puts(buffer);
  }
}
void SSIC_LED::clean_up(void)
{
  if(m_enum){
    hid_free_enumeration(m_dev_info); 
  
  }
  if(m_open){
    hid_close(m_hid_dev_handle);
  }
  hid_exit();
}
void SSIC_LED::init(void)
{
  find_blinkstick();
}
void SSIC_LED::find_blinkstick(void)
{
  SSIC_LED_EXCEPTION except;

  if(hid_init() != 0) {
    except.setmsg(__LINE__, "Failed to initialized hid");
    throw except;
  }
  
  m_dev_info = hid_enumerate(m_vendor_id, m_product_id);

  if(m_dev_info == NULL) {
    except.setmsg(__LINE__, "Failed to Enumerate hid");
    clean_up();
    throw except;
  }
  m_enum = true;  
  m_hid_dev_handle = hid_open_path(m_dev_info->path);
  if(m_hid_dev_handle == NULL) {
    
    clean_up();
    except.setmsg(__LINE__, "Failed to open hid dev handle");
    throw except;
  }
  m_open = true;
  std::cout << "Found device: " << m_dev_info->path << std::endl;
}
void SSIC_LED::enumerate_usb_bus(void)
{
  hid_device_info *devs, *cur_dev;
  devs = hid_enumerate(0x0, 0x0);
  cur_dev = devs; 
  while (cur_dev) {
    std::cout << "*************************************************************" << std::endl;
    std::cout << "Device Found" << std::endl;
    std::cout << "Type: " << cur_dev->vendor_id << " " << cur_dev->product_id << std::endl;
    std::cout << "Path: " << cur_dev->path << std::endl;
    std::cout << "Serial number:"  << cur_dev->serial_number << std::endl;
    std::cout << "Manufacturer: " << cur_dev->manufacturer_string << std::endl;
    std::cout << "Product: " << cur_dev->product_string << std::endl;
    std::cout << "Release: " << std::hex << cur_dev->release_number << std::endl;
    std::cout << "Interface: " << cur_dev->interface_number << std::endl;
    cur_dev = cur_dev->next;
  }
  std::cout << "*************************************************************" << std::endl;
  hid_free_enumeration(devs);
}

std::vector<uint8_t> SSIC_LED::build_control_message(int index, std::vector<uint8_t> color)
{
  SSIC_LED_EXCEPTION except;

  if(index > 8){
    std::cout << index << std::endl;
    except.setmsg(__LINE__, "Index is too large. Blinkstick max index is 7");
    throw except;
  }
  if(color.size() > 3){
    except.setmsg(__LINE__, "Color Vector is too large");
    throw except;
  }
    
  std::vector<uint8_t> msg;
  if(index == 0) {
    msg.push_back(0x1);
  } else {
    msg.push_back(0x005);
    msg.push_back(0x05);
    msg.push_back(index & 0xFF);
  }

  for(size_t i = 0; i < color.size(); i++)
    msg.push_back(color[i]);
  
  return msg;
}
void SSIC_LED::set_led_color(uint8_t index, uint8_t red, uint8_t green, uint8_t blue)
{
  //Add index protection
  SSIC_LED_EXCEPTION except;
  std::vector<uint8_t> color = rgb_to_message(red,green,blue);
  std::vector<uint8_t> msg = build_control_message(index,color);
						
  int res = hid_write(m_hid_dev_handle, msg.data(), msg.size());
  if(res < 0){
    std::cout << "msg size: " << msg.size() << std::endl;
    except.setmsg(__LINE__, "Failed to write hid interface");
    clean_up();
    throw except;
  }
}
void SSIC_LED::turn_off(uint8_t index)
{
  set_led_color(index, 0, 0, 0);
}

SSIC_LED::~SSIC_LED(void)
{
  clean_up();
}
