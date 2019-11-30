/**
 * @file Scheduler.c
 * @author jozochen (jozocyz@hotmail.com)
 * @brief 
 * @date 2019-11-30
 * @copyright Apache License 2.0
 *            jozochen (jozocyz@hotmail.com) Copyright (c) 2019
 */
#include "Scheduler.h"
#include "stddef.h"

typedef enum
{
    SCD_EVENT_1MS = 0,
    SCD_EVENT_5MS,
    SCD_EVENT_10MS,
    SCD_EVENT_20MS,
    SCD_EVENT_50MS,
    SCD_EVENT_100MS,
    SCD_EVENT_200MS,
    SCD_EVENT_500MS,
    SCD_EVENT_1000MS
}Scd_EventPos;

static Scd_FlagType l_event_flags = 0u;

static inline void Scd_Setbit(Scd_FlagType* flgs, Scd_EventPos pos)
{
    *flgs |= (1u << pos);
}

static inline unsigned char Scd_Getbit(Scd_FlagType* flgs, Scd_EventPos pos)
{
    return ((*flgs & (1u << pos)) >> pos);
}

static inline void Scd_Clearbit(Scd_FlagType* flgs, Scd_EventPos pos)
{
    *flgs &= ~(1u << pos);
}

int Scd_Creat(Scd_Handler* handler, Scd_Config* config)
{
    int ret = SCD_E_FAIL;

    if((handler == NULL) || (config== NULL))
    {
        ret = SCD_E_FAIL;
    }
    else
    {
        handler->event_flgs = 0u;
        handler->cb_funcs = *config;
        ret = SCD_E_OK;
    }
    return ret;
}

void Scd_IsrHandlerSysStart(void)
{
    #define CNT_MAX 50000u

    static unsigned short cnt_1ms = 0u;

    // printf("cnt_1ms:%d\n",cnt_1ms);
    if(cnt_1ms % 1 == 0u)
    {
        Scd_Setbit(&l_event_flags, SCD_EVENT_1MS);
    }
    if(cnt_1ms % 5 == 1u)
    {
        Scd_Setbit(&l_event_flags, SCD_EVENT_5MS);
    }
    if(cnt_1ms % 10 == 3u)
    {
        Scd_Setbit(&l_event_flags, SCD_EVENT_10MS);
    }
    if(cnt_1ms % 20 == 5u)
    {
        Scd_Setbit(&l_event_flags, SCD_EVENT_20MS);
    }
    if(cnt_1ms % 50 == 7u)
    {
        Scd_Setbit(&l_event_flags, SCD_EVENT_50MS);
    }
    if(cnt_1ms % 100 == 9u)
    {
        Scd_Setbit(&l_event_flags, SCD_EVENT_100MS);
    }
    if(cnt_1ms % 200 == 11u)
    {
        Scd_Setbit(&l_event_flags, SCD_EVENT_200MS);
    }
    if(cnt_1ms % 500 == 13u)
    {
        Scd_Setbit(&l_event_flags, SCD_EVENT_500MS);
    }
    if(cnt_1ms % 1000 == 15u)
    {
        Scd_Setbit(&l_event_flags, SCD_EVENT_1000MS);
    }

    cnt_1ms++;
    if(cnt_1ms >= CNT_MAX)
    {
        cnt_1ms = 0u;
    }
    else
    {
        /*nothing*/
    }
}

void Scd_IsrHandlerSysEnd(void)
{
    l_event_flags = 0u;
}

void Scd_IsrHandlerUsr(Scd_Handler* handler)
{
    if(handler == NULL)
    {
        /*nothing*/
    }
    else
    {
        handler->event_flgs |= l_event_flags;
        // printf("event_flgs:0x%x\n",handler->event_flgs);
    }
}

#define CALL_FUNC(func) { if(func != SCD_FUNC_NULL)func(); }while(0);
void Scd_Main(Scd_Handler* handler)
{
    if(handler == NULL)
    {
        /*nothing*/
    }
    else
    {
        CALL_FUNC(handler->cb_funcs.func_background);

        if(Scd_Getbit(&handler->event_flgs, SCD_EVENT_1MS))
        {
            CALL_FUNC(handler->cb_funcs.func_1ms);
            Scd_Clearbit(&handler->event_flgs, SCD_EVENT_1MS);
        }
        if(Scd_Getbit(&handler->event_flgs, SCD_EVENT_5MS))
        {
            CALL_FUNC(handler->cb_funcs.func_5ms);
            Scd_Clearbit(&handler->event_flgs, SCD_EVENT_5MS);
        }
        if(Scd_Getbit(&handler->event_flgs, SCD_EVENT_10MS))
        {
            CALL_FUNC(handler->cb_funcs.func_10ms);
            Scd_Clearbit(&handler->event_flgs, SCD_EVENT_10MS);
        }
        if(Scd_Getbit(&handler->event_flgs, SCD_EVENT_20MS))
        {
            CALL_FUNC(handler->cb_funcs.func_20ms);
            Scd_Clearbit(&handler->event_flgs, SCD_EVENT_20MS);
        }
        if(Scd_Getbit(&handler->event_flgs, SCD_EVENT_50MS))
        {
            CALL_FUNC(handler->cb_funcs.func_50ms);
            Scd_Clearbit(&handler->event_flgs, SCD_EVENT_50MS);
        }
        if(Scd_Getbit(&handler->event_flgs, SCD_EVENT_100MS))
        {
            CALL_FUNC(handler->cb_funcs.func_100ms);
            Scd_Clearbit(&handler->event_flgs, SCD_EVENT_100MS);
        }
        if(Scd_Getbit(&handler->event_flgs, SCD_EVENT_200MS))
        {
            CALL_FUNC(handler->cb_funcs.func_200ms);
            Scd_Clearbit(&handler->event_flgs, SCD_EVENT_200MS);
        }
        if(Scd_Getbit(&handler->event_flgs, SCD_EVENT_500MS))
        {
            CALL_FUNC(handler->cb_funcs.func_500ms);
            Scd_Clearbit(&handler->event_flgs, SCD_EVENT_500MS);
        }
        if(Scd_Getbit(&handler->event_flgs, SCD_EVENT_1000MS))
        {
            CALL_FUNC(handler->cb_funcs.func_1000ms);
            Scd_Clearbit(&handler->event_flgs, SCD_EVENT_1000MS);
        }
    }
}
    
