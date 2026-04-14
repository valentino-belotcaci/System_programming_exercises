#!/bin/bash

exec "$1" 12 21 12 21 12 21 12 21 1221 1221 1221 122 121 X X X X X | sort
exit ${PIPESTATUS[0]}



