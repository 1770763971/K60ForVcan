/************************************************************
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,山外科技
 *     All rights reserved.
 *     技术讨论：山外论坛 http://www.vcan123.com
 * @file       main.c
 * @brief      山外K60 平台主程序
 * @author     山外科技
 * @version    v5.0
 * @date       2013-08-28
************************************************************/

#include "main.h"

void SysInit ()
{
    flash_init();                                       //初始化flash
    key_init(KEY_START);
    DELAY_MS(100);
    LCD_init();
    LCD_SET_DIR(0);     //设为横屏
    //LCD_cross(site,len,BLUE);
    touch_init();       //触摸屏初始化
    
    if(key_check(KEY_START) == KEY_DOWN) //检测key状态（带延时消抖）
    {
        flash_erase_sector(SECTOR_NUM);                     //擦除扇区
    }

    if(touch_load(flash_load) == 0)
    {
        while(!touch_calibrate());      //等待校正成功
        touch_save(flash_save);
    }

    Palette_Init();
}


void main()
{
   Site_t site;
   
   SysInit();  //Init all you have to use

    while(1)
    {
        if(touch_get_point(& site))
        {
            Palette_draw_point(site);
        }
    }
}
  
