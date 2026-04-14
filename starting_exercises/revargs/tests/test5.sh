#!/bin/bash

exec "$1" ciao aic mamma 2 ammama  12340 43210  1234 43211 2 1  11  | sort
exit ${PIPESTATUS[0]}



