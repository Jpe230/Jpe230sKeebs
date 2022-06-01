#!/bin/sh

echo 'Copying contents as symlinks'
cp -as ~/qmk/jpe230s_keebs/* ~/qmk/qmk_firmware > /dev/null 2>&1
echo 'Done copying'

readonly EXCLUDE=/home/jpe230/qmk/qmk_firmware/.git/info/exclude

if grep -Fxq "# jpe230 excludes" $EXCLUDE
then
  echo '.git/info/excludes already modified!'
else
  echo '.git/info/excludes not modified!'

  {
    echo ''
    echo '# jpe230 excludes'
    echo ''
    echo 'LICENSE'
    echo 'README.md'
    echo 'keyboards/keychron/k14/keymaps/jpe230/*'
    echo 'keyboards/adafruit/macropad/keymaps/jpe230/*'
    echo 'keyboards/crkbd/keymaps/jpe230_rp/*'
    echo 'keyboards/handwired/bigkey/*'
    echo 'keyboards/keychron/q2/q2_ansi_stm32l432_ec11/keymaps/jpe230/*'
  } >> $EXCLUDE

  echo 'Done modifying excludes file!'

fi