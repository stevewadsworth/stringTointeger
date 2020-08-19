#include <stdbool.h>
#include <stdio.h>
#include "./stringToInteger.h"

static bool isDigit(const char digit)
{
    return (digit >= '0' && digit <= '9');
}

static bool isHex(const char digit)
{
  return (digit >= '0' && digit <= '9') ||
         (digit >= 'a' && digit <= 'f') ||
         (digit >= 'A' && digit <= 'F');
}

char hexDigitToNibble(const char digit)
{
  if (digit >= '0' && digit <= '9')
  {
    return digit - '0';
  }
  if (digit >= 'a' && digit <= 'f')
  {
    return digit - 'a' + 10;
  }
  if (digit >= 'A' && digit <= 'F')
  {
    return digit - 'A' + 10;
  }
  return 0;
}

eStringToIntegerReturn hexStringToInteger(const char *buf, const int len, int *value)
{
  int i = 0;
  int acc = 0;
  int overflowCheck = 0;
  eStringToIntegerReturn result = EOK;

  *value = 0;

  if (len > 2)
  {
    // Check for hex indicator
    if (buf[i] == '0' && buf[i + 1] == 'x')
    {
      // Skip over the 0x if present
      i = i + 2;
    }
  }

  for (; i < len; i++)
  {
    if (isHex(buf[i]))
    {
      overflowCheck = acc;
      acc = (acc << 4) + hexDigitToNibble(buf[i]);
      if (acc < overflowCheck)
      {
        acc = 0;
        result = EWOULDOVERFLOW;
        break;
      }
    }
    else
    {
      result = EBADINPUT;
      acc = 0;
      break;
    }
  }

  *value = acc;

  return result;
}

eStringToIntegerReturn decimalStringToInteger(const char *buf, const int len, int *value)
{
  int i = 0;
  int acc = 0;
  int overflowCheck = 0;
  bool positiveSign = true;
  eStringToIntegerReturn result = EOK;

  *value = 0;

  if (buf[i] == '-')
  {
    positiveSign = false;
    i++;
  }

  if (buf[i] == '+')
  {
    i++;
  }

  for (; i < len; i++)
  {
    if (!isDigit(buf[i]))
    {
      result = EBADINPUT;
      acc = 0;
      break;
    }
    overflowCheck = acc;
    acc = (acc * 10) + (buf[i] - '0');
    if (acc < overflowCheck)
    {
      acc = 0;
      result = EWOULDOVERFLOW;
      break;
    }
  }

  if (!positiveSign)
  {
    // Since the negative maximum is one greater than the positive maximum this cannot overflow
    acc = acc * -1;
  }

  *value = acc;

  return result;
}

eStringToIntegerReturn stringToInteger(const char *buf, const int len, int *value)
{
  *value = 0;

  if (buf && len > 0)
  {
    int i = 0;

    // Eat any leading whitespace
    for (; buf[i] == ' ' || buf[i] == '\t'; i++);

    if (len - i > 2)
    {
      // Check for hex indicator
      if (buf[i] == '0' && buf[i+1] == 'x')
      {
        return hexStringToInteger(buf + i, len - i, value);
      }
    }

    return decimalStringToInteger(buf + i, len - i, value);
  }
  return EBADINPUT;
}
