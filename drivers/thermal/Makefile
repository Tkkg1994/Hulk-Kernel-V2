#
# Makefile for sensor chip drivers.
#

obj-$(CONFIG_THERMAL)		+= thermal_sys.o
obj-$(CONFIG_THERMAL_MSM_POPMEM)	+= msm_popmem-tm.o
obj-$(CONFIG_THERMAL_TSENS)	+= msm_tsens.o
obj-$(CONFIG_THERMAL_TSENS8960) += msm8960_tsens.o
obj-$(CONFIG_THERMAL_PM8XXX)	+= pm8xxx-tm.o
ifeq ($(CONFIG_INTELLI_THERMAL),y)
obj-y				+= intelli/msm_thermal.o
else
obj-$(CONFIG_THERMAL_MONITOR)	+= msm_thermal.o
endif
obj-$(CONFIG_SPEAR_THERMAL)	+= spear_thermal.o
obj-$(CONFIG_THERMAL_TSENS8974)	+= msm8974-tsens.o
