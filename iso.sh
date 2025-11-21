#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/qemos.kernel isodir/boot/qemos.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "qemos" {
	multiboot /boot/qemos.kernel
}
EOF
grub-mkrescue -o qemos.iso isodir
