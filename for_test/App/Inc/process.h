/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2016������
 *     All rights reserved.
 *     �������ۣ�����Ĳ��� http://www.chenxublog.com
 *
 *     ��ע�������⣬�����������ݰ�Ȩ�����������У�δ������������������ҵ��;��
 *     �޸�����ʱ���뱣������İ�Ȩ������
 *
 * @file       process.h
 * @brief      �������ݴ���ͷ�ļ�
 * @author     ����
 * @version    v1.0
 * @date       2016-3-29
 */
#ifndef __PROCESS_H__
#define __PROCESS_H__

int get_camere_center(uint8 img[OV7725_EAGLE_H][OV7725_EAGLE_W],uint8 line);

int get_camere_ok(uint8 img[OV7725_EAGLE_H][OV7725_EAGLE_W]);

int get_camere_white_count(uint8 img[OV7725_EAGLE_H][OV7725_EAGLE_W],uint8 line);

int get_camere_left(uint8 img[OV7725_EAGLE_H][OV7725_EAGLE_W],uint8 line);

int get_camere_right(uint8 img[OV7725_EAGLE_H][OV7725_EAGLE_W],uint8 line);

#endif   //__PROCESS_H__