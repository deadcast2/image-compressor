#define STB_IMAGE_IMPLEMENTATION
#define STBI_NO_SIMD
#define STB_IMAGE_WRITE_IMPLEMENTATION

#include <windows.h>
#include <stdio.h>
#include "fastlz.h"
#include "stb_image.h"
#include "stb_image_write.h"

int main(int argc, char *argv[])
{
  if(argc < 3)
  {
    return printf("Usage: %s input.png output.png.lz\n", argv[0]);
  }
  return 0;
}
