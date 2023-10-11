// Copyright 2022 Jose Pablo Ramirez (@jpe230)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "jpe230.h"
#include "gb_settings.h"
#include "peanut_gb.h"

static struct gb_s gb;

/* Required functions for the GB emulators*/

/*-----------------------------------RAM------------------------------------*/
static uint8_t ram[32768];

/* Read external ram*/
uint8_t gb_cart_ram_read(struct gb_s *gb, const uint_fast32_t addr)
{
	(void) gb;
	return ram[addr];
}

/* Write external ram*/
void gb_cart_ram_write(struct gb_s *gb, const uint_fast32_t addr, const uint8_t val)
{
	ram[addr] = val;
}

/* Read save data from USB */
void raw_hid_receive(uint8_t *data, uint8_t length) {
	//Sanity check (?)
	if(length < 5)
		return;

	uint32_t addr =  (data[3] << 24) | (data[2] << 16) | (data[1] << 8) | data[0];

	dprintf("Receiving %d bytes and writing to addr %ld\n", length, addr);
	// Todo use memcpy or similar
	for(int i = 4; i < length; i++)
	{
		uint32_t w_addr = addr + (i - 4);
		ram[w_addr] = data[i];
	} 
}

/*-----------------------------------ROM------------------------------------*/
extern const unsigned char rom[];  // Main rom
unsigned char rom_bank0[16384];    // Rom bank 0

/* Read ROM at addr*/
uint8_t gb_rom_read(struct gb_s *gb, const uint_fast32_t addr)
{
	(void) gb;
	if(addr < sizeof(rom_bank0))
		return rom_bank0[addr];

	return rom[addr];
}


/*--------------------------ERROR HANDLING------------------------------------*/
void gb_error(struct gb_s *gb, const enum gb_error_e gb_err, const uint16_t val)
{
	const char* gb_err_str[4] = {
			"UNKNOWN",
			"INVALID OPCODE",
			"INVALID READ",
			"INVALID WRITE"
		};
	dprintf("Error %d occurred: %s\n. Abort.\n",
		gb_err,
		gb_err >= GB_INVALID_MAX ?
		gb_err_str[0] : gb_err_str[gb_err]);
	abort();
}

/*--------------------------Screen API------------------------------------*/

static uint16_t start_x = (QP_SCR1_X / 2) - (LCD_WIDTH / 2 );
static uint16_t start_y = (QP_SCR1_Y / 2) - (LCD_HEIGHT / 2 );

void lcd_draw_line(struct gb_s *gb, const uint8_t pixels[LCD_WIDTH], const uint_fast8_t line)
{
   	const uint16_t palette[3][4] = {
		{ 0xFFFF, 0x30FC, 0xC791, 0x0000 }, /* OBJ0 */
		{ 0xFFFF, 0xE67F, 0x0080, 0x0000 }, /* OBJ1 */
		{ 0xFFFF, 0x30FC, 0xC791, 0x0000 }  /* BG */
	};

    static uint16_t fb[LCD_WIDTH];

    for(unsigned int x = 0; x < LCD_WIDTH; x++)
	{
		fb[x] = palette[(pixels[x] & LCD_PALETTE_ALL) >> 4][pixels[x] & 3];
	}
	
    qp_viewport(display, start_x, line + start_y, start_x + (LCD_WIDTH - 1), line + start_y);
    qp_pixdata(display, (void *)fb, LCD_WIDTH);
    qp_flush(display);
}


/*--------------------------External API------------------------------------*/
bool emu_started = false;

void gb_main()
{
     // Copy first bank to ram
    memcpy(rom_bank0, rom, sizeof(rom_bank0)); 

    // Init peanut gb emu
    enum gb_init_error_e ret;
	ret = gb_init(&gb, &gb_rom_read, &gb_cart_ram_read, &gb_cart_ram_write, &gb_error, NULL);

    // Init lcd
    gb_init_lcd(&gb, &lcd_draw_line);
    gb.direct.interlace  = 1;         //Allow Interlacing
	gb.direct.frame_skip = 1;         //Allow frameskip

    if(ret != GB_INIT_NO_ERROR)
	{
		dprintf("Error: %d\n", ret);
        return;
	}

    // Start main loop
	emu_started = true;
}


void game_loop()
{
	if(!emu_started){
		return;
	}
    // Read Keys
	gb.direct.joypad_bits.up  = !game_keys[0];
	gb.direct.joypad_bits.right  = !game_keys[1];
	gb.direct.joypad_bits.down  = !game_keys[2];
	gb.direct.joypad_bits.left = !game_keys[3];
	gb.direct.joypad_bits.a = !game_keys[4];
	gb.direct.joypad_bits.b = !game_keys[5];
	gb.direct.joypad_bits.start = !game_keys[6];

	gb_run_frame(&gb);
}