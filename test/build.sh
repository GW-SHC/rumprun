#!/bin/bash

export PATH="${PATH}:$(pwd)/../app-tools/"

rm helloer-rumprun
rm rumprun-helloer-rumprun.bin
rm rumprun-rumprun-helloer-rumprun.bin.iso

i486-rumprun-netbsdelf-gcc -o helloer-rumprun udp_server.c
rumpbake hw_generic rumprun-helloer-rumprun.bin helloer-rumprun

#ip tuntap add tap0 mode tap
#ip addr add 10.0.120.100/24 dev tap0
#ip link set dev tap0 up
#rumprun qemu -i -M 128 \
#	-I if,vioif,'-net tap,script=no,ifname=tap0' \
#        -W if,inet,static,10.0.120.101/24 \
#	rumprun-helloer-rumprun.bin

rumprun iso rumprun-helloer-rumprun.bin
sudo dd if=rumprun-rumprun-helloer-rumprun.bin.iso of=/dev/sdb bs=8M
ls /dev/sd*
