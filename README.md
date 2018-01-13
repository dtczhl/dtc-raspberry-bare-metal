# raspberry-bare-metal

This repo is adapted from my ECS 251: Operating Systems at UC Davis

It is a bare-metal OS written from scracth, without OS and hence everything is under control, e.g., no process switching, etc.

I think it could be useful for projects that require precise real-time control. For example, simultaneously control multiple LED lights. 

## Target boards

Rasbperry Pi 2 and 3. They have four cores, and therefore you can use each core to do its own task. 



## Prerequisite

If you are familiar with C, you are good to go.

## Note

* Format SD card to FAT

* Copy bootcode.bin and start.elf to SD card (you can find them under external_resources folder)

* Cross-compiler can be found under external_resources/arm-gcc/. Add PATH to gcc-arm-*/bin 

* If everything is correct, simply type `make` in the main source folder will generate kernel7.img. Copy this image to SD card.

* `make clean` as needed

* I referred to several materials and online codes when I was doing this project. I could miss references and credits for these sources. 
