#include <windows.h>
#include <stdio.h>
#include "fastlz.h"
#include "lodepng.h"
#include "libimagequant.h"

int encodeAndWrite(const char *inputName, const char *outputName)
{
  unsigned int width, height;
  unsigned char *pixelData;
  unsigned int status = lodepng_decode32_file(&pixelData, &width,
    &height, inputName);
  if(status) return printf("Could not decode png\n");

  liq_attr *handle = liq_attr_create();
  liq_image *inputImage = liq_image_create_rgba(handle, pixelData,
    width, height, 0);
  liq_result *quantResult;
  if(liq_image_quantize(inputImage, handle, &quantResult) != LIQ_OK)
  {
    return printf("Could not quantize png\n");
  }

  size_t pixelCount = width * height;
  unsigned char *raw8bitPixels = malloc(pixelCount);
  liq_set_dithering_level(quantResult, 1.0);
  liq_write_remapped_image(quantResult, inputImage, raw8bitPixels, pixelCount);
  const liq_palette *palette = liq_get_palette(quantResult);

  LodePNGState state;
  lodepng_state_init(&state);
  state.info_raw.colortype = LCT_PALETTE;
  state.info_raw.bitdepth = 8;
  state.info_png.color.colortype = LCT_PALETTE;
  state.info_png.color.bitdepth = 8;
  for(int i=0; i < palette->count; i++) {
     lodepng_palette_add(&state.info_png.color, palette->entries[i].r,
       palette->entries[i].g, palette->entries[i].b, palette->entries[i].a);
     lodepng_palette_add(&state.info_raw, palette->entries[i].r,
       palette->entries[i].g, palette->entries[i].b, palette->entries[i].a);
  }

  unsigned char *outputData;
  size_t outputSize;
  unsigned int out_status = lodepng_encode(&outputData,
    &outputSize, raw8bitPixels, width, height, &state);
  if(out_status) return printf("Could not re-encode png\n");

  FILE *file = fopen(outputName, "wb");
  if(!file) return printf("Could not write new png\n");
  fwrite(outputData, 1, outputSize, file);
  fclose(file);

  liq_result_destroy(quantResult);
  liq_image_destroy(inputImage);
  liq_attr_destroy(handle);
  free(raw8bitPixels);
  lodepng_state_cleanup(&state);
}

int main(int argc, char *argv[])
{
  if(argc < 3)
  {
    return printf("Usage: %s input.png output.png.lz\n", argv[0]);
  }
  encodeAndWrite(argv[1], argv[2]);
  return 0;
}
