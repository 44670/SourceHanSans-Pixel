#pragma once
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

u8 frameBuffer[32][64];

int halGetScreenWidth() { return 64; }

int halGetScreenHeight() { return 32; }

void halDrawPixel(int x, int y, u32 color) { frameBuffer[y][x] = (u8)color; }

const u8 *halGetFontDataPtr() {
  FILE *fp = fopen("../../font16x15.4FN", "rb");
  fseek(fp, 0, SEEK_END);
  int fileLen = ftell(fp);
  printf("fileLen: %d\n", fileLen);
  fseek(fp, 0, SEEK_SET);

  u8 *buf = (u8 *)malloc(fileLen);
  fread(buf, fileLen, 1, fp);
  fclose(fp);

  return buf;
}