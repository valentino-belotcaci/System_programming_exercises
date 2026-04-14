#!/bin/sh
exec "$1" 100 <<EOF
10 20 10
3 3 1
7 12 2
EOF
