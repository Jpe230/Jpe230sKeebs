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