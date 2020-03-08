#ifndef _SCREEN_H_
#define _SCREEN_H_

/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,山外科技
 *     All rights reserved.
 *     技术讨论：山外论坛 http://www.vcan123.com
 *
 *     除注明出处外，以下所有内容版权均属山外科技所有，未经允许，不得用于商业用途，
 *     修改内容时必须保留山外科技的版权声明。
 *
 * @file       main.c
 * @brief      山外K60 平台主程序
 * @author     山外科技
 * @version    v5.0
 * @date       2013-08-28
 */

#define SECTOR_NUM  (FLASH_SECTOR_NUM-1)         //尽量用最后面的扇区，确保安全
//第1个字节用于写入 FLASH_MARK ，第9个字节开始存储 触摸屏校验参数

#define FLASH_MARK  0xAA55A55A
   
   
int flash_load(uint8 *buff,uint32 len);
int flash_save(uint8 *buff,uint32 len);
void Palette_Init(void);
void Palette_draw_point(Site_t site);



#endif