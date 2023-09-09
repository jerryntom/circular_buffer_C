#include <stdio.h>
#include "circular_buffer.h"

int main(void) {
    int buffer_size, operation, num, res, err_code = 0;
    struct circular_buffer_t *cb;
    printf("Please input the size of buffer you want to create:");
    if(scanf("%d", &buffer_size) != 1) {
        printf("Incorrect input");
        return 1;
    }
    else if(buffer_size <= 0) {
        printf("Incorrect input data");
        return 2;
    }
    else res = circular_buffer_create_struct(&cb, buffer_size);

    if(res == 2 || cb == NULL || cb->ptr == NULL) {
        printf("Failed to allocate memory");
        return 8;
    }
    else {
        while(1) {
            printf("Please input operation type:");
            if(scanf("%d", &operation) != 1) {
                printf("Incorrect input");
                circular_buffer_destroy_struct(&cb);
                return 1;
            }

            if(operation == 0) {
                circular_buffer_destroy_struct(&cb);
                return 0;
            }
            else if(operation == 1) {
                printf("Please input number:");
                if(scanf("%d", &num) != 1) {
                    circular_buffer_destroy_struct(&cb);
                    printf("Incorrect input");
                    return 1;
                }
                else circular_buffer_push_back(cb, num);
            }
            else if(operation == 2) {
                num = circular_buffer_pop_back(cb, &err_code);
                if(err_code == 2) {
                    printf("Buffer is empty\n");
                }
                else if(err_code == 0) {
                    printf("%d\n", num);
                }
            }
            else if(operation == 3) {
                num = circular_buffer_pop_front(cb, &err_code);
                if(err_code == 2) {
                    printf("Buffer is empty\n");
                }
                else if(err_code == 0) {
                    printf("%d\n", num);
                }
            }
            else if(operation == 4) {
                if(circular_buffer_empty(cb)) {
                    printf("Buffer is empty");
                }
                else circular_buffer_display(cb);
                printf("\n");
            }
            else if(operation == 5) {
                if(circular_buffer_empty(cb)) {
                    printf("1\n");
                }
                else printf("0\n");
            }
            else if(operation == 6) {
                if(circular_buffer_full(cb)) {
                    printf("1\n");
                }
                else printf("0\n");
            }
            else {
                printf("Incorrect input data\n");
            }
        }
    }
}
