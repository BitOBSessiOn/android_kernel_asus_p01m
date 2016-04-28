/*
 * Copyright (c) 2013, ASUSTek, Inc. All Rights Reserved.
 * Written by chris chang Chris1_Chang@asus.com
 */

#ifndef __BQ27520_BATTERY_UPT_I2C_H__
#define __BQ27520_BATTERY_UPT_I2C_H__

#include <linux/module.h>
#include <linux/param.h>
#include <linux/i2c.h>
//372CL LG(SANYO) COSLIGHT(ATL)
#ifdef CONFIG_ME372CG
    #define FW_CELL_TYPE_LG                 0x0335
    #define FW_CELL_TYPE_COS_LIGHT          0x133
    #define LATEST_FW_CFG_VERSION           0x3131
    #define BQ27XXX_WITH_CELL_DATA
#elif defined(CONFIG_ME302C)
    #define FW_CELL_TYPE_LG                 0x1108
    #define FW_CELL_TYPE_COS_LIGHT          0x133
    #define LATEST_FW_CFG_VERSION           0x3130
    #define BQ27XXX_WITH_CELL_DATA
#elif defined(CONFIG_ME372CL)
    #define FW_CELL_TYPE_LG                 0x0368
    #define FW_CELL_TYPE_COS_LIGHT          0x0335
    #define LATEST_FW_CFG_VERSION           0x3131
    #define BQ27XXX_WITH_CELL_DATA
#elif defined(CONFIG_FE380CG)
    #define FW_CELL_TYPE_LG                 0x3140
    #define FW_CELL_TYPE_COS_LIGHT          0x0
    #define LATEST_FW_CFG_VERSION           0x3031
    #define BQ27XXX_WITH_CELL_DATA
#elif defined(CONFIG_A503ML)
    #define FW_CELL_TYPE_LG                 0x3243
    #define FW_CELL_TYPE_COS_LIGHT          0x0
    #define LATEST_FW_CFG_VERSION           0x3031
    #define BQ27XXX_WITH_CELL_DATA
#elif defined(CONFIG_Z580C)
    #define FW_CELL_TYPE_LG                 0x3140
    #define FW_CELL_TYPE_COS_LIGHT          0x0
    #define LATEST_FW_CFG_VERSION           0x3331
    #define BQ27XXX_WITH_CELL_DATA
#else
    #define FW_CELL_TYPE_LG                 0x0
    #define FW_CELL_TYPE_COS_LIGHT          0x0
    #define LATEST_FW_CFG_VERSION           0x0
    #define BQ27XXX_WITH_CELL_DATAx
#endif

#define BQ27520_UPDATE_FORCE_CHECKING

typedef enum _cell_type {
    TYPE_COS_LIGHT=0,
    TYPE_LG,
} cell_type;

typedef enum _update_status {
    UPDATE_BATT_ID_FAIL = -5,
    UPDATE_PROCESS_FAIL = -4,
    UPDATE_ERR_MATCH_OP_BUF = -3,
    UPDATE_CHECK_MODE_FAIL = -2,
    UPDATE_VOLT_NOT_ENOUGH = -1,
    UPDATE_NONE = 0,
    UPDATE_OK,
    UPDATE_FROM_ROM_MODE,
} update_status;

#define OP_ROM_READ     0
#define OP_ROM_WRITE    1
#define OP_ROM_CMP      2
#define OP_ROM_END      3
#define OP_I2C_START    4
#define OP_I2C_READ     5
#define OP_I2C_WRITE    6
#define OP_I2C_CMP      7
#define OP_WAIT         8

struct update_op {
    u32 bq_op;
    u32 off; //OP_WAIT not use
    u32 arg;
} ;

struct bq27xx_dffs_data {
    u32 cell_type;
    u32 num_op;
    struct update_op *op;
};

int bq27520_bat_upt_i2c_init(void);
void bq27520_bat_upt_i2c_exit(void);
int bq27520_enter_rom_mode(void);
int bq27520_exit_rom_mode(void);
int bq27520_rom_mode_cmp(int reg_off, int value);
int bq27520_rom_mode_wait(int m_secs);
int bq27520_rom_mode_write_i2c(u8 reg, int value, int b_single);
int bq27520_rom_mode_read_i2c(u8 reg, int *rt_value, int b_single);
int bq27520_bat_upt_main_update_flow(void);
int update_normal(int curr_cell_type);

#endif //#define __BQ27520_BATTERY_UPT_I2C_H__