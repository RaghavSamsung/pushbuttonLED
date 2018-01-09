#ifndef __SSIC_LED_LIB_H__
#define __SSIC_LED_LIB_H__
#include <hidapi/hidapi.h>
#include <iostream>
#include <vector>
#include <cstdint>
class SSIC_LED
{
 public:
  SSIC_LED(void);
  SSIC_LED(bool debug){set_debug(debug);};
  ~SSIC_LED(void);
  void init(void);
  void set_debug(bool debug){m_debug=debug;};
  void find_blinkstick(void);
  void enumerate_usb_bus(void);
  std::vector<uint8_t> build_control_message(int index, std::vector<uint8_t> color);
  void turn_off(uint8_t index);
  void set_led_color(uint8_t index, uint8_t red, uint8_t green, uint8_t blue); 
 private:

  std::vector<uint8_t> m_message;
  bool m_debug;
  
  void debug(const char* fmt, ...);
  static int const m_vendor_id = 8352;
  static int const m_product_id = 16869;
  hid_device* m_hid_dev_handle;
  void clean_up(void);
  enum rgb{RED=0,GREEN,BLUE};
  std::vector<uint8_t> rgb_to_message(uint8_t red, uint8_t green, uint8_t blue);
  bool m_enum;
  bool m_open;
  hid_device_info * m_dev_info; 
 protected:
};

class SSIC_LED_EXCEPTION
{
 public:
  SSIC_LED_EXCEPTION(void);
  ~SSIC_LED_EXCEPTION(void);
  void setmsg(uint32_t line, std::string msg);
  std::string getmsg(void){return m_msg;};
 private:
  
  std::string m_msg;
 
};

#endif /*__SSIC_LED_LIB_H__*/
