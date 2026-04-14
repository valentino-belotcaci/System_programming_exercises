#!/bin/sh

#
# test 1
#
cat > test1.in <<EOF
fiat bravo 105 30000
bmw 305i 120 50000
bmw 305 100 45000
fiat 500 80 25000
EOF
./sort_cars < test1.in > test1.out
cat > test1.expected <<EOF
fiat bravo 105 30000
fiat 500 80 25000
bmw 305i 120 50000
bmw 305 100 45000
EOF
if diff -q test1.out test1.expected; then
    rm -f test1.out test1.expected
else
    echo "Test 1 FAILED"
    diff test1.out test1.expected
    exit 1
fi
#
# test 2
#
./sort_cars +model < test1.in > test1.out
cat > test1.expected <<EOF
bmw 305 100 45000
bmw 305i 120 50000
fiat 500 80 25000
fiat bravo 105 30000
EOF
if diff -q test1.out test1.expected; then
    rm -f test1.out test1.expected
else
    echo "Test 2 FAILED"
    diff test1.out test1.expected
    exit 1
fi
#
# test 3
#
./sort_cars -power < test1.in > test1.out
cat > test1.expected <<EOF
bmw 305i 120 50000
fiat bravo 105 30000
bmw 305 100 45000
fiat 500 80 25000
EOF
if diff -q test1.out test1.expected; then
    rm -f test1.out test1.expected
else
    echo "Test 3 FAILED"
    diff test1.out test1.expected
    exit 1
fi
#
# test 4
#
./sort_cars +power < test1.in > test1.out
cat > test1.expected <<EOF
fiat 500 80 25000
bmw 305 100 45000
fiat bravo 105 30000
bmw 305i 120 50000
EOF
if diff -q test1.out test1.expected; then
    rm -f test1.out test1.expected
else
    echo "Test 4 FAILED"
    diff test1.out test1.expected
    exit 1
fi
#
# test 5
#
./sort_cars +price < test1.in > test1.out
cat > test1.expected <<EOF
fiat 500 80 25000
fiat bravo 105 30000
bmw 305 100 45000
bmw 305i 120 50000
EOF
if diff -q test1.out test1.expected; then
    rm -f test1.out test1.expected
else
    echo "Test 5 FAILED"
    diff test1.out test1.expected
    exit 1
fi
#
# test 6
#
./sort_cars -price < test1.in > test1.out
cat > test1.expected <<EOF
bmw 305i 120 50000
bmw 305 100 45000
fiat bravo 105 30000
fiat 500 80 25000
EOF
if diff -q test1.out test1.expected; then
    rm -f test1.out test1.expected
else
    echo "Test 6 FAILED"
    diff test1.out test1.expected
    exit 1
fi
rm -f test1.in
#
# test 7
#
(for x in `seq 1 200`; do for y in `seq 100 300`; do echo "maker$x model$y 1$x ${x}9$y"; done; done ) > test1.in
./sort_cars +price < test1.in > test1.out
sort -n -k 4 < test1.in > test1.expected
if diff -q test1.out test1.expected; then
    rm -f test1.out test1.expected
else
    echo "Test 7 FAILED"
    diff test1.out test1.expected
    exit 1
fi
rm -f test1.in
echo PASSED
