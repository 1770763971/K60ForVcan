#ifndef _SCREEN_H_
#define _SCREEN_H_

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

#define SECTOR_NUM  (FLASH_SECTOR_NUM-1)         //������������������ȷ����ȫ
//��1���ֽ�����д�� FLASH_MARK ����9���ֽڿ�ʼ�洢 ������У�����

#define FLASH_MARK  0xAA55A55A
   
   
int flash_load(uint8 *buff,uint32 len);
int flash_save(uint8 *buff,uint32 len);
void Palette_Init(void);
void Palette_draw_point(Site_t site);



#endif