#!/bin/bash
{
	make mrproper
	make VARIANT_DEFCONFIG=jf_eur_defconfig jf_defconfig SELINUX_DEFCONFIG=selinux_defconfig
        make -j3
}
