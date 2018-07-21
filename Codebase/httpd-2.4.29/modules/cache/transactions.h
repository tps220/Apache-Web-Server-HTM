#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H
#include <pthread.h>
#include <immintrin.h>
#include <x86intrin.h>


extern int capacity_abort;
extern int conflict_abort;
extern int other_abort;
extern int gl_abort;
extern int gl_count;
extern int htm_count;

#define THREAD_MUTEX_T pthread_mutex_t
extern THREAD_MUTEX_T plock;

#define IS_LOCKED(plock) *((volatile int*)(&plock)) != 0
#define THREAD_MUTEX_INIT(plock) pthread_mutex_init(&(plock), NULL)
#define THREAD_MUTEX_LOCK(plock) pthread_mutex_lock(&(plock))
#define THREAD_MUTEX_UNLOCK(plock) pthread_mutex_unlock(&(plock))


# define TM_BEGIN									\
    {												\
        int tries = 50;      						\
        while(1){									\
            while(IS_LOCKED(plock)){					\
                __asm__ ( "pause;" );				\
            } 										\
            int status = _xbegin();					\
            if(status == _XBEGIN_STARTED){			\
                if(IS_LOCKED(plock)){				\
                    _xabort(30);					\
                }									\
                break;								\
            }										\
            if(status & _XABORT_CODE(30)){			\
                gl_abort++;							\
            } else if(status & _XABORT_CAPACITY){	\
                capacity_abort++;					\
            } else if(status & _XABORT_CONFLICT){	\
                conflict_abort++;					\
            } else{									\
                other_abort++;						\
            }										\
            tries--;								\
            if(tries <= 0){							\
                pthread_mutex_lock(&plock);			\
                break;								\
            }										\
        }

# define TM_END										\
        if(tries > 0){								\
            _xend();								\
            htm_count++;							\
        } else {									\
            pthread_mutex_unlock(&plock);			\
            gl_count++;								\
        }											\
    };

#endif // TRANSACTIONS_H
