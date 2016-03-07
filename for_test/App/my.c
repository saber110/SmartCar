/*!
 *     COPYRIGHT NOTICE
 *     Copyright (c) 2016������
 *     All rights reserved.
 *     �������ۣ�����Ĳ��� http://www.chenxublog.com
 *
 *     ��ע�������⣬�����������ݰ�Ȩ�����������У�δ������������������ҵ��;��
 *     �޸�����ʱ���뱣������İ�Ȩ������
 *
 * @file       my.c
 * @brief      K60�Աຯ��
 * @author     ����
 * @version    v1.0
 * @date       2016-3-7
 */

#include "common.h"
#include"include.h"


/*!
 *  @brief      K60��ʼ��
 *  @since      v1.0
 *  Sample usage:            mk60int();    //��ʼ��K60
 */
void mk60int()
{
    ftm_pwm_init(FTM0, FTM_CH2,10*1000,0);         //��ʼ�� FTM PWM ��ʹ�� FTM0_CH3��Ƶ��Ϊ10k ��ռ�ձ�Ϊ 100 / FTM0_PRECISON
    ftm_pwm_init(FTM0, FTM_CH3,10*1000,0);
    ftm_pwm_init(FTM0, FTM_CH4,10*1000,0);
    ftm_pwm_init(FTM0, FTM_CH5,10*1000,0);

    ftm_pwm_init(S3010_FTM, S3010_CH,S3010_HZ,100);
    control_actuator(0);

    OLED_Init();    //OLED��ʼ��

    pit_init_ms(PIT0, 5);                                //��ʼ��PIT0����ʱʱ��Ϊ�� 5ms
    set_vector_handler(PIT0_VECTORn ,PIT0_IRQHandler);      //����PIT0���жϷ�����Ϊ PIT0_IRQHandler
    enable_irq (PIT0_IRQn);                                 //ʹ��PIT0�ж�

    key_init(KEY_U);
    key_init(KEY_D);
}


/*!
 *  @brief      ����������
 *  @since      v1.0
 *  @note       ����ֵ��Χ-1��1   ������
 *  Sample usage:            control_actuator(-0.2);    //����������0.2
 */
void control_actuator(float Voltage)
{
    if(Voltage>1 || Voltage<-1)
        return;
    if(Voltage<0)
    {
        ftm_pwm_duty(S3010_FTM, S3010_CH,(int)((control_actuator_center-control_actuator_min)*Voltage+control_actuator_center));
    }else
    {
        ftm_pwm_duty(S3010_FTM, S3010_CH,(int)((control_actuator_max-control_actuator_center)*Voltage+control_actuator_center));
    }
}


/*!
 *  @brief      ����������
 *  @since      v1.0
 *  @note       ����ֵ��Χ-1��1   ������
 *  Sample usage:            SetMotorVoltage(0.1,0.2);    //�����������0.1���ҵ������0.2
 */
void SetMotorVoltage(float fLeftVoltage,float fRightVoltage)
{
    int nOut;
    if(fLeftVoltage>0)
    {
	ftm_pwm_duty(FTM0,FTM_CH2,0);//���������˶�PWMռ�ձ�Ϊ0
	nOut=(int)(fLeftVoltage*PERIOD);//
	if(nOut>1000)
	{
		nOut=1000;
	}
	ftm_pwm_duty(FTM0,FTM_CH3,nOut);//���ַ����˶�PWMռ�ձ�ΪnOut
    }                                                   //������ת
    else
    {
	ftm_pwm_duty(FTM0,FTM_CH3,0);//���ַ����˶�PWMռ�ձ�Ϊ0
	fLeftVoltage=-fLeftVoltage;
	nOut=(int)(fLeftVoltage*PERIOD);
	if(nOut>1000)
	{
		nOut=1000;
	}
	ftm_pwm_duty(FTM0,FTM_CH2,nOut);//���������˶�PWMռ�ձ�ΪnOut
    }                                                    //������ת

    if(fRightVoltage>0)
    {
	ftm_pwm_duty(FTM0,FTM_CH4,0);//���������˶�PWMռ�ձ�Ϊ0
	nOut=(int)(fRightVoltage*PERIOD);
	if(nOut>1000)
	{
		nOut=1000;
	}
	ftm_pwm_duty(FTM0,FTM_CH5,nOut);//���ַ����˶�PWMռ�ձ�ΪnOut
    }                                                     //�ҵ����ת
    else
    {
	ftm_pwm_duty(FTM0,FTM_CH5,0);//���ַ����˶�PWMռ�ձ�Ϊ0
	fRightVoltage=-fRightVoltage;
	nOut=(int)(fRightVoltage*PERIOD);
	if(nOut>1000)
	{
		nOut=1000;
	}
	ftm_pwm_duty(FTM0,FTM_CH4,nOut);//���������˶�PWMռ�ձ�ΪnOut
    }                                                     //�ҵ����ת
}