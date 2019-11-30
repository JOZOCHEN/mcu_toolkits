/**
 * @file filter.c
 * @author jozochen (jozocyz@hotmail.com)
 * @brief 
 * @date 2019-11-30
 * @copyright Apache License 2.0
 *            jozochen (jozocyz@hotmail.com) Copyright (c) 2019
 */
#include "filter.h"

#define FILTER_MAGIC_INIT (0xFE)

static inline uint16 Filter_Ave_Calc(uint16* buffer, uint8 len);

uint16 Filter_Ave_GetVal(Filter_Ave_Handler* handler, uint16 new_data)
{
    uint16 ret_val = 0u;
    uint8 i =0u;

    if(handler == NULL)
    {

    }
    else
    {
        if(handler->init != FILTER_MAGIC_INIT)
        {
            for(i = 0u; i < FILTER_AVE_BUFFER_LEN; i++)
            {
                handler->buffer[i] = new_data;
            }
            handler->ind = 0u;
            handler->init = FILTER_MAGIC_INIT;
        }
        else
        {
            handler->buffer[handler->ind] = new_data;
            handler->ind++;
            if(handler->ind >= FILTER_AVE_BUFFER_LEN)
            {
                handler->ind = 0u;
            }
        } 
        ret_val = Filter_Ave_Calc(handler->buffer, FILTER_AVE_BUFFER_LEN);      
    }  
		return ret_val;
}

static inline uint16 Filter_Ave_Calc(uint16* buffer, uint8 len)
{
    uint16 ret_val = 0u;
    uint16 max_val = 0u;
    uint16 min_val = 0u;
    uint8 i = 0u;

    if(len >= FILTER_AVE_BUFFER_LEN_MIN)
    {
        max_val = buffer[0];
        min_val = buffer[0];
        for(i = 0u; i < len; i++)
        {
            ret_val += buffer[i];
            if(buffer[i] > max_val)
            {
                max_val = buffer[i];
            }
            else
            {
                /* code */
            }
            
            if(buffer[i] < min_val)
            {
                min_val = buffer[i];
            }
            else
            {
                /* code */
            }
            
        }
       
        ret_val = (ret_val - max_val - min_val) / (len - 2u);
    }
    else
    {
        ret_val = 0u;
    }

    return ret_val;
}

uint8 Filter_Debounce_GetVal(Filter_Debounce_Handler* handler, uint8 new_state)
{
    uint8 ret = FALSE;

    if( handler == NULL )
    {
        ret = FALSE;
    }
    else
    {
        if(handler->last_state == new_state)
        {
            if(handler->cnt < FILTER_DEBOUNCE_CNT_MAX)
            {
                handler->cnt++;
            }
            else
            {
                handler->stable_state = handler->last_state;
            }           
        }
        else
        {
            handler->last_state = new_state;
            handler->cnt = 0u;
        }

        ret = handler->stable_state; 
    }
    
    return ret;
}
