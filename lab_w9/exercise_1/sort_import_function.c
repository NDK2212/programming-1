#include <dlfcn.h>
#include <stddef.h>
#include <stdio.h>

void *handle = NULL;
#define GetProcAddress dlsym

// declare function pointers

int (*greater)(int, int);
int (*less)(int, int);
void (*bubble_sort)(int *, int, int (*)(int, int));

void DllOpen(const char *lib_name)
{
    handle = dlopen(lib_name, RTLD_LAZY);

    if (!handle)
    {
        printf("Could not load library: %s\n", lib_name);
        return;
    }

    greater = (int (*)(int, int))GetProcAddress(handle, "greater");
    less = (int (*)(int, int))GetProcAddress(handle, "less");
    bubble_sort = (void (*)(int *, int, int (*)(int, int)))GetProcAddress(handle, "bubble_sort");
}

int main()
{
    int N = 5;
    int arr[] = {1, 4, 3, 7, 6};
    DllOpen("./sort_lib.so");

    bubble_sort(arr, N, greater);
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0; // set break point
    // gcc - c - fPIC sort_lib.c - o sort_lib.o
    // gcc sort_lib.o - shared - o sort_lib.so
    // cd "d:\programming-1\lab_w9\exercise_1\" ; if ($?) { gcc sort_import_function.c -o sort_import_function } ; if ($?) { .\sort_import_function }
}