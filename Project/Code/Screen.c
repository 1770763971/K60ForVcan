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

#include "common.h"

#include "VCAN_LCD.h"
#include "VCAN_LCD_ILI9325.h"
#include "Vcan_touch.h"
#include  "VCAN_key_event.h"    //按键消息处理
#include "MK60_FLASH.h"
#include "Screen.h"



int flash_load(uint8 *buff,uint32 len)
{
    int i;

    if(flash_read(SECTOR_NUM, 0, uint32) != FLASH_MARK)
    {
        return 0;           //校验数据不对，加载失败
    }

    for(i=0;i<len;i++)
    {
        buff[i] = flash_read(SECTOR_NUM,i+8,uint8);  //在flash里的第9个字节开始存储 触摸屏校验参数，所以需要 i+8
    }
    return 1;
}

//保存
int flash_save(uint8 *buff,uint32 len)
{
    if(flash_write(SECTOR_NUM, 0, FLASH_MARK) == 0)     //写入校验码
    {
        return 0; //保存失败
    }

    return flash_write_buf (SECTOR_NUM,8,len, buff);    //写入数据
}

uint16 pencolor_a[] = {WHITE,GREEN,BLUE,BRED,GRED,GBLUE,BLACK,RED};

/*
* 画板初始化，用于取色用
*/
void Palette_Init(void)
{
    /* 整屏清为白色 */
    LCD_clear(WHITE);

    /* 画两条直线 */
    LCD_rectangle((Site_t){39, 0},(Size_t){ 1, 30}, BLACK);
    LCD_rectangle((Site_t){0, 29},(Size_t){ 40, 1}, BLACK);

    //写清屏文字
    LCD_str((Site_t){7, 10}, (uint8_t *)"CLR", RED,BLACK);

    //画色板的矩形框
    LCD_rectangle((Site_t){0,  30},(Size_t){ 40, 30}, pencolor_a[1]);
    LCD_rectangle((Site_t){0,  60},(Size_t){ 40, 30}, pencolor_a[2]);
    LCD_rectangle((Site_t){0,  90},(Size_t){ 40, 30}, pencolor_a[3]);
    LCD_rectangle((Site_t){0, 120},(Size_t){ 40, 30}, pencolor_a[4]);
    LCD_rectangle((Site_t){0, 150},(Size_t){ 40, 30}, pencolor_a[5]);
    LCD_rectangle((Site_t){0, 180},(Size_t){ 40, 30}, pencolor_a[6]);
    LCD_rectangle((Site_t){0, 210},(Size_t){ 40, 30}, pencolor_a[7]);

}

/******************************************************
* 函数名：Palette_draw_point
* 描述  ：在LCD指定位置画一个大点(包含四个小点)
* 输入  : Xpos      --X方向位置
*         Ypos      --Y方向位置
* 输出  ：无
* 举例  ：Palette_draw_point(100,100);
* 注意  ：该函数是 "触摸画板应用实例" 专用函数
*********************************************************/
void Palette_draw_point(Site_t site)
{
    /* 画笔默认为黑色 */
    static uint16 Pen_color=0;
    uint8 n;

    /* 在画板内取色 */
    if( site.x<40 )
    {
        n = site.y/30;          //色板的位置
        if( n==0 )
        {
            LCD_rectangle((Site_t){40,0},(Size_t){280,240}, WHITE);          //清屏
        }
        else
        {
            Pen_color = pencolor_a[n];    //根据色板来改变画板颜色
        }
    }
    else
    {
        LCD_cross(site,3,Pen_color);
    }
}

