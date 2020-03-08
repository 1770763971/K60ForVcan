/************************************************************
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,ɽ��Ƽ�
 *     All rights reserved.
 *     �������ۣ�ɽ����̳ http://www.vcan123.com
 * @file       main.c
 * @brief      ɽ��K60 ƽ̨������
 * @author     ɽ��Ƽ�
 * @version    v5.0
 * @date       2013-08-28
************************************************************/

#include "main.h"

void SysInit ()
{
    flash_init();                                       //��ʼ��flash
    key_init(KEY_START);
    DELAY_MS(100);
    LCD_init();
    LCD_SET_DIR(0);     //��Ϊ����
    //LCD_cross(site,len,BLUE);
    touch_init();       //��������ʼ��
    
    if(key_check(KEY_START) == KEY_DOWN) //���key״̬������ʱ������
    {
        flash_erase_sector(SECTOR_NUM);                     //��������
    }

    if(touch_load(flash_load) == 0)
    {
        while(!touch_calibrate());      //�ȴ�У���ɹ�
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
  
