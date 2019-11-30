/**
 * @file filter.h
 * @author jozochen (jozocyz@hotmail.com)
 * @brief 
 * @date 2019-11-30
 * @copyright Apache License 2.0
 *            jozochen (jozocyz@hotmail.com) Copyright (c) 2019
 */
#ifndef __FILTER_H
#define __FILTER_H

#include "common_types.h"

#define FILTER_AVE_BUFFER_LEN (6u)

#define FILTER_AVE_BUFFER_LEN_MIN (3u)
#if (FILTER_AVE_BUFFER_LEN < FILTER_AVE_BUFFER_LEN_MIN)
    #error "FILTER_BUFFER_LEN must greater than 3"
#endif

#define FILTER_DEBOUNCE_CNT_MAX (3u)

typedef struct 
{
    uint8 init;
    uint8 ind;
    uint16 buffer[FILTER_AVE_BUFFER_LEN];
}Filter_Ave_Handler;

typedef struct 
{
    uint8 cnt;
    uint8 last_state;
    uint8 stable_state;
}Filter_Debounce_Handler;

uint16 Filter_Ave_GetVal(Filter_Ave_Handler* handler, uint16 new_data);
uint8 Filter_Debounce_GetVal(Filter_Debounce_Handler* handler, uint8 new_state);
#endif
