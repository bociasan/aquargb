
#define EVERY_MS(x) \
  static uint32_t tmr;\
  bool flag = millis() - tmr >= (x);\
  if (flag) tmr = millis();\
  if (flag)


  #define EVERY_MSS(x) \
  static uint32_t tmrs;\
  bool flags = millis() - tmrs >= (x);\
  if (flags) tmrs = millis();\
  if (flags)