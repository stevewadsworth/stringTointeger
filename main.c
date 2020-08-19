#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "./stringToInteger.h"

int main(int argc, char *argv[])
{
  // printf("argc = %d\n", argc);
  // for (int i = 0; i < argc; i++)
  // {
  //   printf("%d - %s\n", i, argv[i]);
  // }
  int value;
  eStringToIntegerReturn ret;

  if (argc == 2)
  {
    ret = stringToInteger(argv[1], strlen(argv[1]), &value);
    if (ret == 0)
    {
      printf("%s: 0x%x : %d\n", argv[1], value, value);
    }
    else
    {
      printf("%s - bad value (%d)\n", argv[1], ret);
    }

  }
  else
  {
    // Run some tests
    char* fiftyfive = "55";
    char *leadingspace = "  55";
    char *minus3875 = "-3875";
    char *overflow = "999999999999999999999999999999";
    char *hexad = "0xad";
    char *hex3C = "0x3C";
    char *hexBig = "0xf3A67ff";

    ret = stringToInteger(NULL, 0, &value);
    printf("%s == %d : %d\n", "NULL", value, ret);
    ret = stringToInteger(fiftyfive, strlen(fiftyfive), &value);
    printf("%s == %d : %d\n", fiftyfive, value, ret);
    ret = stringToInteger(leadingspace, strlen(leadingspace), &value);
    printf("%s == %d : %d\n", leadingspace, value, ret);
    ret = stringToInteger(minus3875, strlen(minus3875), &value);
    printf("%s == %d : %d\n", minus3875, value, ret);
    ret = stringToInteger(overflow, strlen(overflow), &value);
    printf("%s == %d : %d\n", overflow, value, ret);
    ret = stringToInteger(hexad, strlen(hexad), &value);
    printf("%s == 0x%x : %d\n", hexad, value, ret);
    ret = stringToInteger(hex3C, strlen(hex3C), &value);
    printf("%s == 0x%x : %d\n", hex3C, value, ret);
    ret = stringToInteger(hexBig, strlen(hexBig), &value);
    printf("%s == 0x%x : %d\n", hexBig, value, ret);
  }

  exit(0);
}
