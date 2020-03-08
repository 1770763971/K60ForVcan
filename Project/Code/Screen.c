/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2013,ɽ��Ƽ�
 *     All rights reserved.
 *     �������ۣ�ɽ����̳ http://www.vcan123.com
 *
 *     ��ע�������⣬�����������ݰ�Ȩ����ɽ��Ƽ����У�δ����������������ҵ��;��
 *     �޸�����ʱ���뱣��ɽ��Ƽ��İ�Ȩ������
 *
 * @file       main.c
 * @brief      ɽ��K60 ƽ̨������
 * @author     ɽ��Ƽ�
 * @version    v5.0
 * @date       2013-08-28
 */

#include "common.h"

#include "VCAN_LCD.h"
#include "VCAN_LCD_ILI9325.h"
#include "Vcan_touch.h"
#include  "VCAN_key_event.h"    //������Ϣ����
#include "MK60_FLASH.h"
#include "Screen.h"



int flash_load(uint8 *buff,uint32 len)
{
    int i;

    if(flash_read(SECTOR_NUM, 0, uint32) != FLASH_MARK)
    {
        return 0;           //У�����ݲ��ԣ�����ʧ��
    }

    for(i=0;i<len;i++)
    {
        buff[i] = flash_read(SECTOR_NUM,i+8,uint8);  //��flash��ĵ�9���ֽڿ�ʼ�洢 ������У�������������Ҫ i+8
    }
    return 1;
}

//����
int flash_save(uint8 *buff,uint32 len)
{
    if(flash_write(SECTOR_NUM, 0, FLASH_MARK) == 0)     //д��У����
    {
        return 0; //����ʧ��
    }

    return flash_write_buf (SECTOR_NUM,8,len, buff);    //д������
}

uint16 pencolor_a[] = {WHITE,GREEN,BLUE,BRED,GRED,GBLUE,BLACK,RED};

/*
* �����ʼ��������ȡɫ��
*/
void Palette_Init(void)
{
    /* ������Ϊ��ɫ */
    LCD_clear(WHITE);

    /* ������ֱ�� */
    LCD_rectangle((Site_t){39, 0},(Size_t){ 1, 30}, BLACK);
    LCD_rectangle((Site_t){0, 29},(Size_t){ 40, 1}, BLACK);

    //д��������
    LCD_str((Site_t){7, 10}, (uint8_t *)"CLR", RED,BLACK);

    //��ɫ��ľ��ο�
    LCD_rectangle((Site_t){0,  30},(Size_t){ 40, 30}, pencolor_a[1]);
    LCD_rectangle((Site_t){0,  60},(Size_t){ 40, 30}, pencolor_a[2]);
    LCD_rectangle((Site_t){0,  90},(Size_t){ 40, 30}, pencolor_a[3]);
    LCD_rectangle((Site_t){0, 120},(Size_t){ 40, 30}, pencolor_a[4]);
    LCD_rectangle((Site_t){0, 150},(Size_t){ 40, 30}, pencolor_a[5]);
    LCD_rectangle((Site_t){0, 180},(Size_t){ 40, 30}, pencolor_a[6]);
    LCD_rectangle((Site_t){0, 210},(Size_t){ 40, 30}, pencolor_a[7]);

}

/******************************************************
* ��������Palette_draw_point
* ����  ����LCDָ��λ�û�һ�����(�����ĸ�С��)
* ����  : Xpos      --X����λ��
*         Ypos      --Y����λ��
* ���  ����
* ����  ��Palette_draw_point(100,100);
* ע��  ���ú����� "��������Ӧ��ʵ��" ר�ú���
*********************************************************/
void Palette_draw_point(Site_t site)
{
    /* ����Ĭ��Ϊ��ɫ */
    static uint16 Pen_color=0;
    uint8 n;

    /* �ڻ�����ȡɫ */
    if( site.x<40 )
    {
        n = site.y/30;          //ɫ���λ��
        if( n==0 )
        {
            LCD_rectangle((Site_t){40,0},(Size_t){280,240}, WHITE);          //����
        }
        else
        {
            Pen_color = pencolor_a[n];    //����ɫ�����ı仭����ɫ
        }
    }
    else
    {
        LCD_cross(site,3,Pen_color);
    }
}

