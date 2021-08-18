#include "font.h"
#include <stdio.h>

int main() {
    fbInit();
    fbDrawUtf8String("你好世界");
    for (int y = 0; y < halGetScreenHeight(); y++) {
        for (int x = 0; x < halGetScreenWidth(); x++) {
            printf("%c", frameBuffer[y][x] ? '*': ' ');
        }
        printf("\n");
    }
    return 0;
}