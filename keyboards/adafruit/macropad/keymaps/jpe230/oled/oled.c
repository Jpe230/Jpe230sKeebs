/* Copyright 2022 Jose Pablo Ramirez <jp.ramangulo@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "jpe230.h"

uint8_t oled_state = DEFAULT_OLED;

bool indicator_oled_state[MATRIX_ROWS][MATRIX_COLS] = {
    { false, false, false },
    { false, false, false },
    { false, false, false },
    { false, false, false },
    { false, false, false }
};

const char* PROGMEM layer_strings[] = {
    "Media",
    "Teams",
    "Edge",
    "VSCode",
    "Visual Studio",
    "Discord",
    "Configuration",
    "Configuration 2",
    SECRET_LAYER_STRINGS
    "Empty"
};

const char PROGMEM *key_strings[][MATRIX_ROWS][MATRIX_COLS] = {
    {
        {___ns____, ___ns____, "RGB TOG"},
        {___ns____, "Vol. Up", ___ns____},
        {___ns____, "Vol. Dn", ___ns____},
        {___ns____, "Mute"   , ___ns____},
        {"Prev T ", "Play"   , "Next T."}
    },
    {
        {___ns____, ___ns____, "RGB TOG"},
        {"Vol. +" , "Accpt C", " Mute M"},
        {"Vol. -" , "Accpt V", " Tog V" },
        {"Mute"   , "Decln C", ___ns____},
        {___ns____, "End Cll", ___ns____}
    },
    {
        {___ns____, ___ns____, "RGB TOG"},
        {"Zoom +" , "New Tab", " Vol. +"},
        {"Zoom -" , "Nxt Tab", " Vol. -"},
        {"Cls Tb ", "Prv Tab", " Mute"  },
        {"Prev T.", "Play"   , "Next T."}
    },
    {
        {___ns____, ___ns____, "RGB TOG"},
        {"Zoom +" , ___ns____, "Sidebar"},
        {"Zoom -" , "Nxt Tab", " Cmment"},
        {___ns____, "Prv Tab", " Ucmmnt"},
        {"Bck cur", ___ns____, "Nxt cur"}
    },
    {
        {___ns____, ___ns____, "RGB TOG"},
        {"Zoom +" , "RunDbg" , ___ns____},
        {"Zoom -" , ___ns____, " Cmment"},
        {___ns____, "StepIn",  " Ucmmnt"},
        {"Bckcur ", "NextBp ", " Nxtcur"}
    },
    {
        {___ns____, ___ns____, "RGB TOG"},
        {"Acpt C ", "PrvMsg ", "NxtMsg" },
        {___ns____, "PageUp ", "Vol. +" },
        {___ns____, "PageDn ", "Vol. -" },
        {___ns____, ___ns____, ___ns____}
    },
    {
        {___ns____, ___ns____, "RGB TOG"},
        {"TgOLED ", "TgIndi ", "MskAnim"},
        {"BongoC ", "RGBHUE ", "ShwAnim"},
        {"Logo"   , "RGBSAT ", "RGBMOD "},
        {"LShift ", "RGBVAL ", "RGBSPD "}
    },
    {
        {___ns____, ___ns____, ___ns____},
        {"EERESET", ___ns____, ___ns____},
        {___ns____, ___ns____, ___ns____},
        {___ns____, ___ns____, ___ns____},
        {___ns____, ___ns____, ___ns____}
    },
    SECRET_KEY_STRING
    {
        {___ns____, ___ns____, ___ns____},
        {___ns____, ___ns____, ___ns____},
        {___ns____, ___ns____, ___ns____},
        {___ns____, ___ns____, ___ns____},
        {___ns____, ___ns____, ___ns____}
    }
};


void center_text(const char *text, char *output, int width) {
    /* If string is bigger than the available width, trim it */
    if(strlen(text) > width){
        memcpy(output, text, width);
        return;
    }

    /* Try to center the TEXT, TODO: Handle Even lengths*/
    int padlen_l = (width - strlen(text)) / 2;
    int padlen_r = (padlen_l * 2) + strlen(text) == width ? padlen_l : padlen_l + 1;
    sprintf(output, "%*s%s%*s", padlen_l, "", text, padlen_r, "");
}

void render_layer_indicators(int layer) {
    /* Print Title */
    char title[CHARS_PER_LINE];
    center_text(layer_strings[layer], title, CHARS_PER_LINE);
    oled_write_ln((const char *)title, true);

    /* Print Keys */
    for(uint8_t row = 0; row < MATRIX_ROWS; row++)
    {
        for(uint8_t col = 0; col < MATRIX_COLS; col++)
        {
            char name[CHARS_PER_KEY];
            center_text(key_strings[layer][row][col], name, CHARS_PER_KEY);
            bool invert = key_strings[layer][row][col][0] != '\0' && indicator_oled_state[row][col];
            oled_write((const char*)name, invert);
        }
    }

    /* Empty Line */
    oled_write_ln("", false);
}

void render_default_state(void){
    /* Get the active layer */
    int layer_idx = get_highest_layer(layer_state|default_layer_state);

    /* Render the Logo on emptylayer */
    switch(layer_idx)
    {
        case EMPTLAYER:
            render_logo();
            return;
        SECRET_OLED_LAYER_RENDER
        default:
            /* Render the indicators */
            render_layer_indicators(layer_idx);
    }
}

bool oled_task_user(void) {
    /* Decay each frame */
    fake_wpm_decay();

    switch (oled_state)
    {
    case DEFAULT_OLED:
        render_default_state();
        break;

    case BONGO_CAT:
        render_bongo_cat();
        break;

    case LOGO:
        render_logo();
        break;

    default:
        break;
    }

    return true;
}

/* Fake WPM */
static uint8_t current_wpm = 0;
static uint8_t decay_calls = 0;

void fake_wpm_increment(void)
{
    if (current_wpm + increment_amount >= 255)
        current_wpm = 255;
    else
        current_wpm += increment_amount;
}

void fake_wpm_decay(void)
{
    if (decay_calls == 0)
    {
        if (!current_wpm == 0){
            current_wpm --;
        }
        else
            return;
    }

    if (decay_calls > decay_every_x)
        decay_calls = 0;
    else
        decay_calls ++;
}

uint8_t get_current_wpm(void)
{
    return current_wpm;
}
