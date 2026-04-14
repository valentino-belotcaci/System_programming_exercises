#!/bin/bash

exec "$1" ciao aic mamma ammama  12340 43210  1234 43211 2 1 | sort
exit ${PIPESTATUS[0]}


