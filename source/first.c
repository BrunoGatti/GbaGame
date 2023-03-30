#include <tonc.h>

int main()
{
    // Load the sprite image into memory
    u32* spriteData = (u32*)malloc(32 * 32 / 2);
    loadBmp("sprite.bmp", spriteData);

    // Set the sprite's attributes
    OBJATTR spriteAttr = {
        ATTR0_SQUARE,           // Square shape
        ATTR1_SIZE_32,          // 32x32 size
        ATTR2_PALBANK(0) | 0,   // Use palette 0 and tile index 0
    };

    // Copy the sprite data to OAM
    oam_memset(&oam_main, 0, sizeof(oam_main));  // Clear OAM
    oam_set(&oam_main, 0, 0, 0, 0, &spriteAttr); // Set sprite attributes

    // Enable the display of sprites
    REG_DISPCNT |= DCNT_OBJ | DCNT_OBJ_1D;

    // Loop forever
    while(1) {
        // Wait for VBlank
        vid_vsync();

        // Update OAM
        oam_copy(&oam_main, obj_buffer, 1);

        // Update the screen
        vid_flip();
    }

    return 0;
}
