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

/* --------------[NOTE FOR THE READER]---------------
 * 
 *  This file serves as a template to add secrets  to
 *  my keymap. My whole keymap uses "SECRET_****"  to
 *  denote a "secret" part of it, this way I can have
 *  a public version of this km as  well as a  secret 
 *  version of it.
 * 
 *  Keep in mind that if security is highly important
 *  to you, you should use hash the values of passwrd
 *  or keys.
 * 
 *  For example the private version of this map, uses
 *  a lockscreen to enter to the TOTP layer:
 * 
 *    - The password is stored as a hashed valued,the
 *      input  password is then  hashed and  compared
 *      to the stored value.
 * 
 *    - The  private   keys  for  the  TOPT are saved
 *      encrypted and then decrypted using my passwd.
 * 
 *  You can compile  the public version of  this  map
 *  without  any  problems  but if you  need  to  use
 *  secrets  you  will  need  to figure it out on your
 *  own.
 * 
 *  Note: This is file is necessary to compile the 
 *  public version.
 * 
 * --------------------------------------------------
 */

/* --------------------------------------------------
 * Secret Keycodes
 * Example:
 * #define SECRET_KEYCODES SECRET_1, ..., SECRET_N
 * --------------------------------------------------
 */

#define SECRET_KEYCODES

/* --------------------------------------------------
 * Secret LAYERS
 *
 * Example:
 * #define SECRET_LAYERS SECRET_L1, ..., SECRET_LN,
 * 
 * Note: Notice the comma at the end!!!
 * 
 * #define SECRET_LAYER_COUNT N 
 * 
 * Note: N = number of secret layers
 * --------------------------------------------------
 */
#define SECRET_LAYERS
#define SECRET_LAYER_COUNT 0

/* --------------------------------------------------
 * Secret Keymap
 *
 * #define SECRET_KEYMAP [SECRET_L1] = LAYOUT(...),
 * 
 * Note: Notice the comma at the end!!!
 * --------------------------------------------------
 */
#define SECRET_KEYMAP

/* --------------------------------------------------
 * Secret Indicator
 *
 * #define SECRET_INDICATORS {{{...},{{...}},{{...}}},
 * 
 * Note: Notice the comma at the end!!!
 * --------------------------------------------------
 */
#define SECRET_INDICATORS

/* --------------------------------------------------
 * Secret OLED text
 *
 * #define SECRET_KEY_STRING {{"", "",  ""}},
 * 
 * Note: Notice the comma at the end!!!
 * 
 * #define SECRET_LAYER_STRINGS "Secret Layer1",
 * 
 * Note: Notice the comma at the end!!!
 * --------------------------------------------------
 */
#define SECRET_KEY_STRING
#define SECRET_LAYER_STRINGS

/* --------------------------------------------------
 * Secret OLED Layer Render
 *
 * #define SECRET_OLED_LAYER_RENDER case SECRET_L1:\
 *                                   do_something();
 * --------------------------------------------------
 */
#define SECRET_OLED_LAYER_RENDER

/* --------------------------------------------------
 * Secret Handling
 *
 * #define SECRET_LAYER_HANDLING case SECRET_L1:\
 *                                    do_something();
 * 
 * #define SECRET_KC_HANDLING case SECRET_1:\
 *                                 do_something();
 * --------------------------------------------------
 */
#define SECRET_LAYER_HANDLING
#define SECRET_KC_HANDLING