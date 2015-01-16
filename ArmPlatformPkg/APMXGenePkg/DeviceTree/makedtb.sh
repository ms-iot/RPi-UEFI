dtc -o tmp.dtb -i . -O dtb -I dts apm-mustang.dts
hexdump -v -f dtb.format tmp.dtb | sed "s/,0x  //g" > tmp.array
cat header.c tmp.array tail.c > DeviceTree.c
