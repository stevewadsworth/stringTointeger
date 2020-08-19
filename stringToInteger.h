
typedef enum
{
  EOK = 0,
  EBADINPUT = -1,
  EWOULDOVERFLOW = -2,
} eStringToIntegerReturn;

char hexDigitToNibble(const char digit);
eStringToIntegerReturn hexStringToInteger(const char *buf, const int len, int *value);
eStringToIntegerReturn decimalStringToInteger(const char *buf, const int len, int *value);
eStringToIntegerReturn stringToInteger(const char *buf, const int len, int *value);
