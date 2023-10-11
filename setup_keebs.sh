#!/bin/sh

readonly QMKPATH=$HOME # The parent folder for "qmk_firmware"

readonly QMKDIR=$QMKPATH/qmk_firmware
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
cp -as $(pwd)/keyboards/* $QMKDIR/keyboards/ >/dev/null 2>&1

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
  echo 'Creating clean .git/info/excludes'
  rm $EXCLUDE
  touch $EXCLUDE

  echo 'Modifying .git/info/excludes'
  
  # Mark the exlucde file
  echo '# jpe230 excludes' >> $EXCLUDE
  
  # Find all the keebs
  find keyboards -name ".keeb" -type f -exec dirname {} \; >> $EXCLUDE

  # Fetch all repos
  #git -C $QMKDIR fetch --all

# fi

echo 'Done! Have fun'
