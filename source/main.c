// source/main.c
#include "nds/arm9/background.h"
#include "nds/arm9/input.h"
#include "nds/arm9/sprite.h"
#include "nds/arm9/trig_lut.h"
#include "nds/arm9/video.h"
#include <nds.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "bg.h"
#include "clang.h"
#include "nds/input.h"
#include "nds/interrupts.h"

int main(int argc, char **argv)
{

    // 背景設定

    videoSetMode(MODE_0_2D);

    vramSetBankA(VRAM_A_MAIN_BG);

    int bg = bgInitHidden(0, BgType_Text8bpp, BgSize_B8_256x256, 0, 1);

    memcpy(bgGetGfxPtr(bg), bgTiles, bgTilesLen);
    memcpy(bgGetMapPtr(bg), bgMap, bgMapLen);
    memcpy(BG_PALETTE, bgPal, bgPalLen);

    bgShow(bg);

    
    // スプライト表示

    vramSetBankB(VRAM_B_MAIN_SPRITE);

    oamInit(&oamMain, SpriteMapping_1D_32, false);

    u16 *gfxMain = oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_16Color);

    memcpy(gfxMain, clangTiles, clangTilesLen);
    memcpy(SPRITE_PALETTE, clangPal, clangPalLen);

    int x = 128 - 16;
    int y = 92 - 16;

    oamSet(&oamMain, 0, x, y, 0, 0, SpriteSize_32x32, SpriteColorFormat_16Color, gfxMain, 0, true, false, false, false, false);


    // 下画面をテキストコンソールにする
    
    consoleDemoInit();

    printf("\n");
    printf("Hello, DS!\n");
    printf("Hello, C lang!\n");


    int angle = 0;
    int scale = 0;

    while (1)
    {
        // 次のフレームまで待つ（60FPS）
        swiWaitForVBlank();

        // 座標を更新
        oamSetXY(&oamMain, 0, x, y);
        // 回転・拡大縮小
        oamRotateScale(&oamMain, 0, degreesToAngle(angle), (1 << 8) + scale * (1 << 3), (1 << 8) + scale * (1 << 3));
        // 再描画
        oamUpdate(&oamMain);

        scanKeys();

        u16 keys_held = keysHeld();

        // キーを押したら移動
        if (keys_held & KEY_UP) y--;
        if (keys_held & KEY_LEFT) x--;
        if (keys_held & KEY_DOWN) y++;
        if (keys_held & KEY_RIGHT) x++;

        // キーを押したら回転・拡大縮小
        if (keys_held & KEY_A) angle--;
        if (keys_held & KEY_B) scale++;
        if (keys_held & KEY_X) scale--;
        if (keys_held & KEY_Y) angle++;
    }
    return 0;
}