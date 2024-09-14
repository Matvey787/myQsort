#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

int compareIntTypes(void* a, void* b);
int compareDoubleTypes(void* a, void* b);
int compareStringTypes(void* a, void* b);

void mySort(void* data, size_t size, size_t sizeOftype, int (*compareFunc)(void*, void*));
static void mySwap(void* a, void* b, size_t elemMemory);

typedef int(* t_compIntFunc)( void* a,  void* b);
typedef int(* t_compDblFunc)( void* a,  void* b);
typedef int(* t_compStrFunc)( void* a,  void* b);

int main(){

    t_compIntFunc typeInt = compareIntTypes;
    t_compDblFunc typeDbl = compareDoubleTypes;
    t_compStrFunc typeStr = compareStringTypes;

    size_t i = 0;

    //---------------------int array---------------------
    int int_array[] = {1, 3, 2, 4, 5, 6};
    size_t int_length = sizeof(int_array)/sizeof(*int_array);

    mySort(int_array, int_length, sizeof(int), typeInt);

    for (; i < int_length; i++)
        printf("%d ", int_array[i]);
    printf("\n");

    //---------------------double array---------------------
    double dbl_array[] = {1.9, 3.8, 2, 4, 5, 6};
    size_t dbl_length = sizeof(dbl_array)/sizeof(*dbl_array);

    mySort(dbl_array, dbl_length, sizeof(double), typeDbl);

    for (i = 0; i < dbl_length; i++)
        printf("%g ", dbl_array[i]);
    printf("\n");

    //---------------------array of strings---------------------
    const char* str_array[] = {"b_I", "a_hate", "c_matan", "!"};
    size_t str_length = sizeof(str_array)/sizeof(*str_array);

    mySort(str_array, str_length, sizeof(char*), typeStr);

    for (i = 0; i < str_length; i++)
        printf("%s ", str_array[i]);
    printf("\n");

}

void mySort(void* data, size_t size, size_t sizeOftype, int (*compareFunc)(void*, void*)){
    for (size_t i = 0; i < size; i++){
        for (size_t j = 0; j < size-i-1; j++)
            if (compareFunc((char*)data + j*sizeOftype, (char*)data + (j+1)*sizeOftype)){
                mySwap((char*)data + j*sizeOftype, (char*)data + (j+1)*sizeOftype, sizeOftype);
        }
    }

}

int compareIntTypes(void* a, void* b){
    return (*(const int*)a - *(const int*)b) > 0 ? 1 : 0;
}

int compareDoubleTypes(void* a,void* b){
    return (*(const double*)a - *(const double*)b) > 0.001 ? 1 : 0;
}

int compareStringTypes(void* a,void* b){
    return strcmp(*(const char**)a, *(const char**)b) > 0 ? 1 : 0;
}

static void mySwap(void* a, void* b, size_t elemMemory){
    assert("mySwap: first element is null pointer" && a != NULL);
    assert("mySwap: second element is null pointer" && b != NULL);
    size_t summ = 0;

    uint64_t* a_long = (uint64_t*)a;
    uint64_t* b_long = (uint64_t*)b;


    while (summ + sizeof(uint64_t) <= elemMemory){

        uint64_t buf = *a_long;
        *a_long = *b_long;
        *b_long = buf;

        a_long += 1;
        b_long += 1;
        summ += sizeof(uint64_t);

    }
    uint32_t* a_int = (uint32_t*)a_long;
    uint32_t* b_int = (uint32_t*)b_long;

    if (summ + sizeof(uint32_t) <= elemMemory){

        uint32_t buf = *a_int;
        *a_int = *b_int;
        *b_int = buf;

        a_int += 1;
        b_int += 1;
        summ += sizeof(uint32_t);

    }

    uint16_t* a_short = (uint16_t*)a_int;
    uint16_t* b_short = (uint16_t*)b_int;

    if (summ + sizeof(uint16_t) <= elemMemory){

        uint16_t buf = *a_short;
        *a_short = *b_short;
        *b_short = buf;

        a_short += 1;
        b_short += 1;
        summ += sizeof(uint16_t);

    }

    uint8_t* a_char = (uint8_t*)a_short;
    uint8_t* b_char = (uint8_t*)b_short;

    if (summ + sizeof(uint8_t) <= elemMemory){

        uint8_t buf = *a_char;
        *a_char = *b_char;
        *b_char = buf;

        a_char += 1;
        b_char += 1;
        summ += sizeof(uint8_t);

    }
}