#!/bin/sh
export LANG=C.UTF-8
export LC_ALL=C.UTF-8
openbox &
sleep 5
dh_auto_test --no-parallel
