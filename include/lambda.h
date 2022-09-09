#ifndef __LAMBDA_H_
#define __LAMBDA_H_

typedef struct Lambda Lambda;

typedef struct Lambda {
    void (*app)(Lambda, void*);
    void* value;
    void* ctx;
} Lambda;
    

#define GET_POINTED_VALUE(T, PTR) ({ \
        T* __ptr_ = PTR; \
        T __ptr_val_ = *__ptr_; \
        __ptr_val_; \
        })


#define LAMBDA_SET_VALUE(LAMBDA, VALUE) ({ \
        typeof(VALUE)* __lambda_value_ptr_casted_ = LAMBDA.value; \
        *__lambda_value_ptr_casted_ = VALUE; \
        })


#endif
