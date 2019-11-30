/**
 * @file Scheduler.h
 * @author jozochen (jozocyz@hotmail.com)
 * @brief 
 * @date 2019-11-30
 * @copyright Apache License 2.0
 *            jozochen (jozocyz@hotmail.com) Copyright (c) 2019
 */
#ifndef __SCHEDULER_H
#define __SCHEDULER_H

#ifndef NULL
#define NULL ((void*)0)
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#define SCD_E_OK (0)
#define SCD_E_FAIL (-1)

typedef void(*scd_callback_func)(void);

#define SCD_BACKGROUND_FUNC scd_callback_func
#define SCD_1MS_FUNC scd_callback_func
#define SCD_5MS_FUNC scd_callback_func
#define SCD_10MS_FUNC scd_callback_func
#define SCD_20MS_FUNC scd_callback_func
#define SCD_50MS_FUNC scd_callback_func
#define SCD_100MS_FUNC scd_callback_func
#define SCD_200MS_FUNC scd_callback_func
#define SCD_500MS_FUNC scd_callback_func
#define SCD_1000MS_FUNC scd_callback_func

#define SCD_FUNC_NULL NULL

typedef struct Scd_CbFuncs
{
    SCD_BACKGROUND_FUNC func_background;
    SCD_1MS_FUNC func_1ms;
    SCD_5MS_FUNC func_5ms;
    SCD_10MS_FUNC func_10ms;
    SCD_20MS_FUNC func_20ms;
    SCD_50MS_FUNC func_50ms;
    SCD_100MS_FUNC func_100ms;
    SCD_200MS_FUNC func_200ms;
    SCD_500MS_FUNC func_500ms;
    SCD_1000MS_FUNC func_1000ms;
}Scd_Config;

typedef volatile unsigned long Scd_FlagType;

typedef struct
{
    Scd_FlagType event_flgs;
    Scd_Config cb_funcs;
}Scd_Handler;

int Scd_Creat(Scd_Handler* handler, Scd_Config* config);
void Scd_Main(Scd_Handler* handler);
/**
 * @brief call isr funcs by this sequnce:
 * Scd_IsrHandlerSysStart();
 * Scd_IsrHandlerUsr(handler1);
 * Scd_IsrHandlerUsr(handler2);
 * Scd_IsrHandlerUsr(handlern);
 * Scd_IsrHandlerSysEnd();
 * 
 */
void Scd_IsrHandlerSysStart(void);
void Scd_IsrHandlerSysEnd(void);
void Scd_IsrHandlerUsr(Scd_Handler* handler);
#endif
