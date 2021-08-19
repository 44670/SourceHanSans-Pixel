#pragma once
#include "hal.h"

u16 fbPosX;
u16 fbPosY;

typedef struct _FB_FONT {
  int valid;
  int charWidth;
  int charHeight;
  int charDataSize;
  int pageSize;
  u8 *pData;
  u8 *pIndex;
  u8 *pCharData;
} FB_FONT;

FB_FONT fbFontCJK16;
FB_FONT *fbCurrentFont;

static int fbLoadFontData(FB_FONT *pFont, const u8 *fontData) {
  memset(pFont, 0, sizeof(FB_FONT));
  // TODO: check the magic of the font file
  pFont->valid = 1;
  pFont->charWidth = *(u8 *)(fontData + 13);
  pFont->charHeight = *(u8 *)(fontData + 14);
  printf("%d %d\n", pFont->charWidth, pFont->charHeight);
  pFont->charDataSize = 1 + ((pFont->charWidth + 7) / 8) * pFont->charHeight;
  pFont->pageSize = pFont->charDataSize * 256;
  pFont->pData = (u8 *)fontData;
  pFont->pIndex = pFont->pData + 16;
  pFont->pCharData = pFont->pIndex + 256;
  return 0;
}

void fbInit() {
  FB_FONT *pFont = &fbFontCJK16;
  const u8 *fontDataBuf = halGetFontDataPtr();
  fbLoadFontData(pFont, fontDataBuf);

  fbCurrentFont = pFont;
}

static int fbDrawUnicodeRune(u32 rune) {
  if (!fbCurrentFont) {
    return 0;
  }
  // int fontW = fbCurrentFont->charWidth;
  int fontH = fbCurrentFont->charHeight;
  int fontCharSize = fbCurrentFont->charDataSize;
  int fontPageSize = fbCurrentFont->pageSize;

  int screenW = halGetScreenWidth();
  int screenH = halGetScreenHeight();
  rune = (u16)(rune);
  if (rune == '\n') {
    fbPosY += fontH + 1;
    fbPosX = 0;
    return 0;
  }
  u8 pgOffset = fbCurrentFont->pIndex[rune >> 8];
  if (pgOffset == 0xFF) {
    return 0;
  }
  u8 *ptr = fbCurrentFont->pCharData + fontPageSize * pgOffset +
            fontCharSize * (rune & 0xff);
  u8 width = *ptr;
  ptr++;

  if (fbPosX + width >= screenW) {
    fbPosY += fontH + 1;
    fbPosX = 0;
  }
  if (fbPosY + fontH >= screenH) {
    return 0;
  }
  for (u8 y = 0; y < fontH; y++) {
    for (u8 x = 0; x < width; x++) {
      u8 pix = ptr[y * 2 + x / 8] & (1 << (x % 8));
      if (pix) {
        halDrawPixel(fbPosX + x, fbPosY + y, 1);
      }
    }
  }
  fbPosX += width + 1;
  if (fbPosX >= screenW) {
    fbPosY += fontH + 1;
    fbPosX = 0;
  }
  return width;
}

void fbDrawUtf8String(const char *utf8Str) {
  u8 *p = (u8 *)utf8Str;
  u16 rune = 0;
  while (*p) {
    rune = 0;
    u8 byte1 = *p;
    p++;
    if ((byte1 & 0x80) == 0) {
      rune = byte1;
    } else {
      u8 byte2 = *p;
      p++;
      if (byte2 == 0) {
        break;
      }
      if ((byte1 & 0xE0) == 0xC0) {
        rune = ((byte1 & 0x1F) << 6) | (byte2 & 0x3F);
      } else {
        u8 byte3 = *p;
        p++;
        if (byte3 == 0) {
          break;
        }
        if ((byte1 & 0xf0) == 0xE0) {
          rune =
              ((byte1 & 0x0F) << 12) | ((byte2 & 0x3F) << 6) | (byte3 & 0x3F);
        } else {
          break;
        }
      }
    }
    fbDrawUnicodeRune(rune);
  }
}