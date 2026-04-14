#!/bin/sh
exec "$1" 2000 <<EOF
10 20 10
3 3 1
7 12 2
EOF
