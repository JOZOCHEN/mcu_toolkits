/**
 * @file queue.h
 * @author jozochen (jozocyz@hotmail.com)
 * @brief 
 * @date 2019-11-30
 * @copyright Apache License 2.0
 *            jozochen (jozocyz@hotmail.com) Copyright (c) 2019
 */ 
#ifndef _QUEUE_H
#define _QUEUE_H

#ifndef NULL
#define NULL ((void *)0)
#endif

#ifndef FALSE
#define FALSE (0u)
#endif

#ifndef TRUE
#define TRUE (1u)
#endif

#define E_QUEUE_OK (0)
#define E_QUEUE_FAIL (-1)

typedef struct 
{
    unsigned char* pbuf;
    unsigned long  element_ind_max;
    unsigned short  element_size;
    unsigned long  head_ind;
    unsigned long  tail_ind;
    unsigned char  full_flg;
    unsigned char  empty_flg;
}Queue_HandleType;

int Queue_Creat(Queue_HandleType* handle, unsigned char* buf, 
                        unsigned short  element_size, unsigned short  element_num);
int Queue_Push(Queue_HandleType* handle, unsigned char* data);
int Queue_Pop(Queue_HandleType* handle, unsigned char* data);
#if 0
void Queue_test(void);
#endif
#endif
