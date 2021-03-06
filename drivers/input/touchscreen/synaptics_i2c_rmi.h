/* Synaptics Register Mapped Interface (RMI4) I2C Physical Layer Driver.
 * Copyright (c) 2007-2012, Synaptics Incorporated
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */
#ifndef _SYNAPTICS_RMI4_H_
#define _SYNAPTICS_RMI4_H_

#define SYNAPTICS_RMI4_DRIVER_VERSION "DS5 1.0"
#include <linux/device.h>
#include <linux/i2c/synaptics_rmi.h>

#ifdef CONFIG_POWERSUSPEND
#include <linux/powersuspend.h>
#endif

/*#define dev_dbg(dev, fmt, arg...) dev_info(dev, fmt, ##arg)*/

/* DVFS feature : TOUCH BOOSTER */
#define TSP_BOOSTER
#ifdef TSP_BOOSTER
#define DVFS_STAGE_NINTH		9
#define DVFS_STAGE_DUAL		2
#define DVFS_STAGE_SINGLE	1
#define DVFS_STAGE_NONE		0
#include <linux/cpufreq.h>

#define TOUCH_BOOSTER_OFF_TIME	300
#define TOUCH_BOOSTER_CHG_TIME	200
#define TOUCH_BOOSTER_HIGH_OFF_TIME	1000
#define TOUCH_BOOSTER_HIGH_CHG_TIME	500
#endif

/* To support suface touch, firmware should support data
 * which is required related app ex) MT_ANGLE, MT_PALM ...
 * Synpatics IC report those data through F51's edge swipe
 * fucntionality.
 */
#define SYNAPTICS_PRODUCT_ID_B0	"SY 01"
#define SYNAPTICS_PRODUCT_ID_B0_SPAIR	"S5000B"

#if defined(CONFIG_MACH_JACTIVE_EUR) || defined(CONFIG_MACH_JACTIVE_ATT)
#define FW_IMAGE_NAME_B0_HSYNC		"tsp_synaptics/jactive/synaptics_b0_hsync.fw"
#define FW_IMAGE_NAME_B0_HSYNC_FAC	"tsp_synaptics/jactive/synaptics_b0_hsync_fac.fw"
#define FW_IMAGE_NAME_B0_HSYNC04	"tsp_synaptics/jactive/synaptics_b0_hsync04.fw"
#define FW_IMAGE_NAME_B0_HSYNC04_FAC	"tsp_synaptics/jactive/synaptics_b0_hsync04_fac.fw"

/* NON HYNC F/W will be removed */
/* PRODUCT ID : SY 01, SY 02, S5000B */
#define FW_IMAGE_NAME_B0_NON_HSYNC	"tsp_synaptics/jactive/synaptics_b0_non_hsync.fw"
#define FW_IMAGE_NAME_B0_NON_HSYNC_FAC	"tsp_synaptics/jactive/synaptics_b0_non_hsync_fac.fw"

#else
#define FW_IMAGE_NAME_A1			"tsp_synaptics/synaptics_a1.fw"
#define FW_IMAGE_NAME_B0_34			"tsp_synaptics/synaptics_b0_3_4.fw"
#endif
#define FW_IMAGE_NAME_B0_40			"tsp_synaptics/synaptics_b0_4_0.fw"
#define FW_IMAGE_NAME_B0_43			"tsp_synaptics/synaptics_b0_4_3.fw"
#define FW_IMAGE_NAME_B0_51			"tsp_synaptics/synaptics_b0_5_1.fw"
#define FW_IMAGE_NAME_B0_FAC		"tsp_synaptics/synaptics_b0_fac.fw"
#define FW_IMAGE_NAME_B0_5_1_FAC	"tsp_synaptics/synaptics_b0_5_1_fac.fw"
#define SYNAPTICS_FW_UMS			"/sdcard/synaptics.fw"

#if defined(CONFIG_MACH_JACTIVE_EUR) || defined(CONFIG_MACH_JACTIVE_ATT)
#define FW_IMAGE_TEST	"tsp_synaptics/synaptics_d0.fw"
#define SYNAPTICS_DEVICE_NAME		"GT-I9295"
#else
#define SYNAPTICS_DEVICE_NAME		"SGH-I337"
#endif
#define SYNAPTICS_MAX_FW_PATH	64

#define DATE_OF_FIRMWARE_BIN_OFFSET	0xEF00
#define IC_REVISION_BIN_OFFSET	0xEF02
#define FW_VERSION_BIN_OFFSET	0xEF03

#define PDT_PROPS (0X00EF)
#define PDT_START (0x00E9)
#define PDT_END (0x000A)
#define PDT_ENTRY_SIZE (0x0006)
#define PAGES_TO_SERVICE (10)
#define PAGE_SELECT_LEN (2)

#define SYNAPTICS_RMI4_F01 (0x01)
#define SYNAPTICS_RMI4_F11 (0x11)
#define SYNAPTICS_RMI4_F12 (0x12)
#define SYNAPTICS_RMI4_F1A (0x1a)
#define SYNAPTICS_RMI4_F34 (0x34)
#define SYNAPTICS_RMI4_F51 (0x51)
#define SYNAPTICS_RMI4_F54 (0x54)

#define SYNAPTICS_RMI4_PRODUCT_INFO_SIZE 2
#define SYNAPTICS_RMI4_DATE_CODE_SIZE 3
#define SYNAPTICS_RMI4_PRODUCT_ID_SIZE 10
#define SYNAPTICS_RMI4_BUILD_ID_SIZE 3
#define SYNAPTICS_RMI4_PRODUCT_ID_LENGTH 10

#define MAX_NUMBER_OF_BUTTONS 4
#define MAX_INTR_REGISTERS 4
#define MAX_NUMBER_OF_FINGERS 10

#define MASK_16BIT 0xFFFF
#define MASK_8BIT 0xFF
#define MASK_7BIT 0x7F
#define MASK_6BIT 0x3F
#define MASK_5BIT 0x1F
#define MASK_4BIT 0x0F
#define MASK_3BIT 0x07
#define MASK_2BIT 0x03
#define MASK_1BIT 0x01

/*
 * struct synaptics_rmi4_fn_desc - function descriptor fields in PDT
 * @query_base_addr: base address for query registers
 * @cmd_base_addr: base address for command registers
 * @ctrl_base_addr: base address for control registers
 * @data_base_addr: base address for data registers
 * @intr_src_count: number of interrupt sources
 * @fn_number: function number
 */
struct synaptics_rmi4_fn_desc {
	unsigned char query_base_addr;
	unsigned char cmd_base_addr;
	unsigned char ctrl_base_addr;
	unsigned char data_base_addr;
	unsigned char intr_src_count;
	unsigned char fn_number;
};

/*
 * synaptics_rmi4_fn_full_addr - full 16-bit base addresses
 * @query_base: 16-bit base address for query registers
 * @cmd_base: 16-bit base address for data registers
 * @ctrl_base: 16-bit base address for command registers
 * @data_base: 16-bit base address for control registers
 */
struct synaptics_rmi4_fn_full_addr {
	unsigned short query_base;
	unsigned short cmd_base;
	unsigned short ctrl_base;
	unsigned short data_base;
};

/*
 * struct synaptics_rmi4_fn - function handler data structure
 * @fn_number: function number
 * @num_of_data_sources: number of data sources
 * @num_of_data_points: maximum number of fingers supported
 * @size_of_data_register_block: data register block size
 * @data1_offset: offset to data1 register from data base address
 * @intr_reg_num: index to associated interrupt register
 * @intr_mask: interrupt mask
 * @full_addr: full 16-bit base addresses of function registers
 * @link: linked list for function handlers
 * @data_size: size of private data
 * @data: pointer to private data
 */
struct synaptics_rmi4_fn {
	unsigned char fn_number;
	unsigned char num_of_data_sources;
	unsigned char num_of_data_points;
	unsigned char size_of_data_register_block;
	unsigned char data1_offset;
	unsigned char intr_reg_num;
	unsigned char intr_mask;
	struct synaptics_rmi4_fn_full_addr full_addr;
	struct list_head link;
	int data_size;
	void *data;
};

/*
 * struct synaptics_rmi4_device_info - device information
 * @version_major: rmi protocol major version number
 * @version_minor: rmi protocol minor version number
 * @manufacturer_id: manufacturer id
 * @product_props: product properties information
 * @product_info: product info array
 * @date_code: device manufacture date
 * @tester_id: tester id array
 * @serial_number: device serial number
 * @product_id_string: device product id
 * @support_fn_list: linked list for function handlers
 */
struct synaptics_rmi4_device_info {
	unsigned int version_major;
	unsigned int version_minor;
	unsigned char manufacturer_id;
	unsigned char product_props;
	unsigned char product_info[SYNAPTICS_RMI4_PRODUCT_INFO_SIZE];
	unsigned char date_code[SYNAPTICS_RMI4_DATE_CODE_SIZE];
	unsigned short tester_id;
	unsigned short serial_number;
	unsigned char product_id_string[SYNAPTICS_RMI4_PRODUCT_ID_SIZE + 1];
	unsigned char build_id[SYNAPTICS_RMI4_BUILD_ID_SIZE];
	struct list_head support_fn_list;
};

/**
 * struct synaptics_finger - Represents fingers.
 * @ state: finger status.
 * @ mcount: moving counter for debug.
 */
struct synaptics_finger {
	unsigned char state;
	unsigned short mcount;
};

#if defined(CONFIG_TOUCHSCREEN_FACTORY_PLATFORM)
/*
 * struct synaptics_hover - Represents Hovering.
 * @ state: Hover status.
 * @ mcount: moving counter for debug.
 */
struct synaptics_hover {
	unsigned char state;
	unsigned short mcount;
};
#endif

/*
 * struct synaptics_rmi4_data - rmi4 device instance data
 * @i2c_client: pointer to associated i2c client
 * @input_dev: pointer to associated input device
 * @board: constant pointer to platform data
 * @rmi4_mod_info: device information
 * @regulator: pointer to associated regulator
 * @rmi4_io_ctrl_mutex: mutex for i2c i/o control
 * @power_suspend: instance to support power suspend power management
 * @current_page: current page in sensor to acess
 * @button_0d_enabled: flag for 0d button support
 * @full_pm_cycle: flag for full power management cycle in power suspend stage
 * @num_of_intr_regs: number of interrupt registers
 * @f01_query_base_addr: query base address for f01
 * @f01_cmd_base_addr: command base address for f01
 * @f01_ctrl_base_addr: control base address for f01
 * @f01_data_base_addr: data base address for f01
 * @irq: attention interrupt
 * @sensor_max_x: sensor maximum x value
 * @sensor_max_y: sensor maximum y value
 * @irq_enabled: flag for indicating interrupt enable status
 * @touch_stopped: flag to stop interrupt thread processing
 * @fingers_on_2d: flag to indicate presence of fingers in 2d area
 * @sensor_sleep: flag to indicate sleep state of sensor
 * @wait: wait queue for touch data polling in interrupt thread
 * @i2c_read: pointer to i2c read function
 * @i2c_write: pointer to i2c write function
 * @irq_enable: pointer to irq enable function
 */

struct synaptics_rmi4_data {
	struct i2c_client *i2c_client;
	struct input_dev *input_dev;
	const struct synaptics_rmi4_platform_data *board;
	struct synaptics_rmi4_device_info rmi4_mod_info;
	struct regulator *regulator;
	struct mutex rmi4_reset_mutex;
	struct mutex rmi4_io_ctrl_mutex;
	struct mutex rmi4_reflash_mutex;
	struct timer_list f51_finger_timer;
#ifdef CONFIG_POWERSUSPEND
	struct power_suspend power_suspend;
#endif
	unsigned char *firmware_image;

	struct completion init_done;
	struct synaptics_finger finger[MAX_NUMBER_OF_FINGERS];
#if defined (CONFIG_TOUCHSCREEN_FACTORY_PLATFORM)
	struct synaptics_hover hover;
#endif

	unsigned char current_page;
	unsigned char button_0d_enabled;
	unsigned char full_pm_cycle;
	unsigned char num_of_rx;
	unsigned char num_of_tx;
	unsigned char num_of_node;
	unsigned char num_of_fingers;
	unsigned char max_touch_width;
	unsigned char intr_mask[MAX_INTR_REGISTERS];
	unsigned short num_of_intr_regs;
	unsigned short f01_query_base_addr;
	unsigned short f01_cmd_base_addr;
	unsigned short f01_ctrl_base_addr;
	unsigned short f01_data_base_addr;
	int irq;
	int sensor_max_x;
	int sensor_max_y;
	int touch_threshold;
	int gloved_sensitivity;
	int ta_status;
	bool flash_prog_mode; /* prog_mod == TRUE ?  boot mode : normal mode */
	bool irq_enabled;
	bool touch_stopped;
	bool fingers_on_2d;
	bool f51_finger;
	bool sensor_sleep;
	bool stay_awake;
	bool staying_awake;
	bool fast_glove_state;

	int ic_revision_of_ic;		/* revision of reading from IC */
	int fw_version_of_ic;		/* firmware version of IC */
	int ic_revision_of_bin;		/* revision of reading from binary */
	int fw_version_of_bin;		/* firmware version of binary */
	int fw_release_date_of_ic;	/* Config release data from IC */
	int panel_revision;		/* Octa panel revision */
	int factory_read_panel_wakeup;
	bool doing_reflash;

#ifdef CONFIG_GLOVE_TOUCH
	int glove_touch_addr;
	bool touchkey_glove_mode_status;
	unsigned char glove_mode_feature;
	unsigned char glove_mode_enables;
	unsigned short glove_mode_enables_addr;
#endif

#ifdef TSP_BOOSTER
	struct delayed_work	work_dvfs_off;
	struct delayed_work	work_dvfs_chg;
	struct mutex		dvfs_lock;
	bool dvfs_lock_status;
	int dvfs_old_stauts;
	int dvfs_boost_mode;
	int dvfs_freq;
#endif

	struct delayed_work work_init_power_on;
	struct delayed_work	work_rezero;

	void (*register_cb)(struct synaptics_rmi_callbacks *);
	struct synaptics_rmi_callbacks callbacks;

	int (*i2c_read)(struct synaptics_rmi4_data *pdata, unsigned short addr,
			unsigned char *data, unsigned short length);
	int (*i2c_write)(struct synaptics_rmi4_data *pdata, unsigned short addr,
			unsigned char *data, unsigned short length);
	int (*irq_enable)(struct synaptics_rmi4_data *rmi4_data, bool enable);
	int (*reset_device)(struct synaptics_rmi4_data *rmi4_data);
};

enum exp_fn {
	RMI_DEV = 0,
	RMI_F54,
	RMI_FW_UPDATER,
	RMI_LAST,
};

struct synaptics_rmi4_exp_fn_ptr {
	int (*read)(struct synaptics_rmi4_data *rmi4_data, unsigned short addr,
			unsigned char *data, unsigned short length);
	int (*write)(struct synaptics_rmi4_data *rmi4_data, unsigned short addr,
			unsigned char *data, unsigned short length);
	int (*enable)(struct synaptics_rmi4_data *rmi4_data, bool enable);
};

int synaptics_rmi4_new_function(enum exp_fn fn_type,
		int (*func_init)(struct synaptics_rmi4_data *rmi4_data),
		void (*func_remove)(struct synaptics_rmi4_data *rmi4_data),
		void (*func_attn)(struct synaptics_rmi4_data *rmi4_data,
				unsigned char intr_mask));

int rmidev_module_register(void);
int rmi4_f54_module_register(void);
int synaptics_rmi4_f54_set_control(struct synaptics_rmi4_data *rmi4_data);

int rmi4_fw_update_module_register(void);

int synaptics_fw_updater(unsigned char *fw_data, bool mode, bool factory_fw);
int synaptics_rmi4_glove_mode_enables(struct synaptics_rmi4_data *rmi4_data);

int synaptics_rmi4_reset_device(struct synaptics_rmi4_data *rmi4_data);
int synaptics_proximity_no_sleep_set(bool enables);
void synaptics_rmi4_f51_set_custom_rezero(struct synaptics_rmi4_data *rmi4_data);

extern int synaptics_rmi4_proximity_enables(unsigned char enables);

extern struct class *sec_class;
static inline ssize_t synaptics_rmi4_show_error(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	dev_warn(dev, "%s Attempted to read from write-only attribute %s\n",
			__func__, attr->attr.name);
	return -EPERM;
}

static inline ssize_t synaptics_rmi4_store_error(struct device *dev,
		struct device_attribute *attr, const char *buf, size_t count)
{
	dev_warn(dev, "%s Attempted to write to read-only attribute %s\n",
			__func__, attr->attr.name);
	return -EPERM;
}

static inline void batohs(unsigned short *dest, unsigned char *src)
{
	*dest = src[1] * 0x100 + src[0];
}

static inline void hstoba(unsigned char *dest, unsigned short src)
{
	dest[0] = src % 0x100;
	dest[1] = src / 0x100;
}
#ifdef CONFIG_FB_MSM_MIPI_SAMSUNG_OCTA_VIDEO_FULL_HD_PT_PANEL
extern int touch_display_status;
#endif
#endif
