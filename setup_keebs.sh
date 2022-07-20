#!/bin/sh

readonly QMKDIR=$HOME/qmk/qmk_firmware
readonly EXCLUDE=$QMKDIR/.git/info/exclude
readonly CONFIG=$QMKDIR/.git/config

if [ ! -d "$QMKDIR" ]; then
  echo 'QMK not cloned, cloning'
  qmk setup -H $QMKDIR
else
  echo 'QMK cloned!'
fi

# echo 'Restoring branch'
# git -C $QMKDIR reset --hard HEAD

# echo 'Restoring submodules'
# make -C $QMKDIR git-submodule

echo 'Removing symlinked files'
find $QMKDIR -type l -not -path "$QMKDIR/users/*" -delete

echo 'Removing dir. structure'
find $QMKDIR -empty -type d -not -path "$QMKDIR/.git/*" -delete

echo 'Copying contents as symlinks'
cp -as $HOME/qmk/jpe230s_keebs/keyboards/* $QMKDIR/keyboards/ >/dev/null 2>&1

if grep -Fxq '[remote "Jpe230"]' $CONFIG; then
  echo '.git/config already modified!'
else
  echo '.git/config not modified!'

  yes | cp -rf ./jpe230_config $CONFIG

fi

# if grep -Fxq "# jpe230 excludes" $EXCLUDE; then
#   echo '.git/info/excludes already modified!'
# else
#   echo '.git/info/excludes not modified!'
  echo 'Modifying .git/info/excludes'
  rm $EXCLUDE
  touch $EXCLUDE
  {
    echo '# jpe230 excludes'
    echo ''
    echo 'LICENSE'
    echo 'README.md'
    echo 'keyboards/keychron/k14/keymaps/jpe230/*'
    echo 'keyboards/adafruit/macropad/keymaps/jpe230/*'
    echo 'keyboards/adafruit/macropad/keymaps/default-macros/*'
    echo 'keyboards/crkbd/keymaps/jpe230_rp/*'
    echo 'keyboards/handwired/bigkey/*'
    echo 'keyboards/keychron/q2/q2_ansi_stm32l432_ec11/keymaps/jpe230/*'
    echo 'keyboards/nullbitsco/tidbit/keymaps/aspect/*'
  } >> $EXCLUDE

# fi

echo 'Done! Have fun'
