#include <windows.h>
#include <stdio.h>
#include "fastlz.h"

int main(int argc, char *argv[])
{
  if(argc < 3)
  {
    return printf("Usage: %s input.png output.png.lz\n", argv[0]);
  }
  return 0;
}
