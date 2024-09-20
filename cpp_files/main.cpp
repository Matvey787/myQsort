#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <math.h>

int compareIntTypes(void* a, void* b);
int compareDoubleTypes(void* a, void* b);
int compareStringTypes(void* a, void* b);

void mySort(void* data, size_t size, size_t sizeOftype, int (*compareFunc)(void*, void*));
static void mySwap(void* a, void* b, size_t elemMemory);
void quickSort(void* data, long int left, long int right, size_t sizeOftype, int (*compareFunc)(void*, void*));

typedef int(* t_compIntFunc)( void* a,  void* b);
typedef int(* t_compDblFunc)( void* a,  void* b);
typedef int(* t_compStrFunc)( void* a,  void* b);

int main(){
    t_compIntFunc typeInt = compareIntTypes;
    t_compDblFunc typeDbl = compareDoubleTypes;
    t_compStrFunc typeStr = compareStringTypes;
    assert(typeInt != NULL);
    assert(typeDbl != NULL);
    assert(typeStr != NULL);
    
    size_t i = 0;

    //---------------------int array---------------------
    int int_array[] = {1, 3, 2, 4, 5, 100, 89, 5, 1000, 100432};
    size_t int_length = sizeof(int_array)/sizeof(*int_array);

    quickSort(int_array, 0, int_length - 1, sizeof(int), typeInt);

    for (; i < int_length; i++)
        printf("%d ", int_array[i]);
    printf("\n");

    //---------------------array of strings---------------------
    const char* str_array[] = {"b_I", "a_hate", "c_matan", "c_matan", "!"};
    size_t str_length = sizeof(str_array)/sizeof(*str_array);

    quickSort(str_array, 0, str_length - 1, sizeof(char*), typeStr);

    for (i = 0; i < str_length; i++)
        printf("%s ", str_array[i]);
    printf("\n");

    //---------------------double array---------------------
    double dbl_array[] = {4.6, 1.3, 4.6, 12, 12, 123 };
    size_t dbl_length = sizeof(dbl_array)/sizeof(*dbl_array);

    quickSort(dbl_array, 0, dbl_length - 1, sizeof(double), typeDbl);

    for (i = 0; i < dbl_length; i++)
        printf("%g ", dbl_array[i]);
    printf("\n");

}

void quickSort(void* data, long int left, long int right, size_t sizeOftype, int (*compareFunc)(void*, void*)){
    assert(data != NULL);
    if (left > right) return;
    long int pivot = (left+right)/2;
    long int i = left;
    long int j = right;
    while (i <= j){
        while (compareFunc((char*)data + i*sizeOftype, (char*)data + pivot*sizeOftype)) i++;
        while (!compareFunc((char*)data + j*sizeOftype, (char*)data + pivot*sizeOftype) && (j != pivot)) j--;
        if (i <= j){
            mySwap((char*)data + i*sizeOftype, (char*)data + j*sizeOftype, sizeOftype);
            i++;
            j--;
        }
    }
    quickSort(data, left, j, sizeOftype, compareFunc);
    quickSort(data, i, right, sizeOftype, compareFunc);
}

int compareIntTypes(void* a, void* b){
    /* if (*(const int*)a > *(const int*)b)
        printf("%d %d\n", *(const int*)a, *(const int*)b); */
    return *(const int*)a > *(const int*)b;
}

int compareDoubleTypes(void* a,void* b){
    printf("%.1f %.1f %d\n", *(const double*)a, *(const double*)b,((*(const double*)a - *(const double*)b) > 0.000001));
    return (*(const double*)a - *(const double*)b) > 0.000000000001;
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