#!/bin/sh

clear

CONFIGURE_FILE="ppp_configure"
DIALER_SCRIPT=$(pwd)/ppp_dialer
exec pppd call $CONFIGURE_FILE