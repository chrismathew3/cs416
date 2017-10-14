// File:	my_pthread_t.h
// Author:	Yujie REN
// Date:	09/23/2017

// name:
// username of iLab:
// iLab Server: 
#ifndef MY_PTHREAD_T_H
#define MY_PTHREAD_T_H

#define _GNU_SOURCE

/* include lib header files that you need here: */
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#include <sys/time.h>
#include <signal.h>

tcb* scheduler = malloc(sizeof(tcb));
int scheduler_running = 0;
int execution_time = 0;
uint mutex_id = 0;

typedef uint my_pthread_t;

typedef struct thread_node {
    my_pthread* thread;
    struct thread_node* next;
} thread_node;

typedef struct waiting_mutex_queue_node_ {
    my_pthread *thread;
    uint mutex_lock;
    struct waiting_mutex_queue_node_ *next;
} waiting_mutex_queue_node;

typedef struct waiting_thread_queue_node_
{
    my_pthread *thread;
    my_pthread_t pid;
    struct waiting_thread_queue_node_ *next;
} waiting_thread_queue_node;

typedef struct threadControlBlock {
    thread_node* running_queue;
    waiting_queue_node* waiting_queue;
} tcb; 

typedef struct my_pthread {
    ucontext_t context;
    int priority_level;
    int execution_time;
    my_pthread_t pid;
} my_pthread;

/* mutex struct definition */
typedef struct my_pthread_mutex_t {
    uint pid; // thread id of owner
    int mutex_lock; // lock or unlock
    uint mid; // mutex id
} my_pthread_mutex_t;

/* define your data structures here: */

// Feel free to add your own auxiliary data structures


/* Function Declarations: */

/* create a new thread */
int my_pthread_create(my_pthread_t * thread, pthread_attr_t * attr, void *(*function)(void*), void * arg);

/* give CPU pocession to other user level threads voluntarily */
int my_pthread_yield();

/* terminate a thread */
void my_pthread_exit(void *value_ptr);

/* wait for thread termination */
int my_pthread_join(my_pthread_t thread, void **value_ptr);

/* initial the mutex lock */
int my_pthread_mutex_init(my_pthread_mutex_t *mutex, const pthread_mutexattr_t *mutexattr);

/* aquire the mutex lock */
int my_pthread_mutex_lock(my_pthread_mutex_t *mutex);

/* release the mutex lock */
int my_pthread_mutex_unlock(my_pthread_mutex_t *mutex);

/* destroy the mutex */
int my_pthread_mutex_destroy(my_pthread_mutex_t *mutex);

#endif
