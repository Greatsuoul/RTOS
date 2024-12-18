#include<stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
// #include "freertos/timer.h"
// #include <unistd.h>

TaskHandle_t s1;
TaskHandle_t s2;
TaskHandle_t s3;
TimerHandle_t timer;

void stimer(TimerHandle_t x){
    printf("Timer Invoked\n");
}

void serial_func1(void *data){

    printf("Task1 Successful\n");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    vTaskResume(s2);
    vTaskDelete(NULL);
}

void serial_func2(void *data){
    printf("Task2 Successful\n");
    vTaskDelay(3000 / portTICK_PERIOD_MS);
    vTaskResume(s2);
    vTaskDelete(NULL);
}

void serial_func3(void *data){
    vTaskDelay(5000 / portTICK_PERIOD_MS);
    timer = xTimerCreate("Oneshot Timer", 5000 / portTICK_PERIOD_MS, pdTRUE, (void *)1, stimer);
    xTimerStart(timer, 0);
    printf("Task3 Successful\n");
    vTaskDelete(NULL);
}


void app_main(){
    xTaskCreatePinnedToCore(serial_func1, "Task1Function", 1024, NULL, 5, &s1, 1);
    xTaskCreatePinnedToCore(serial_func2, "Task2Function", 1024, NULL, 4, &s2, 1);
    xTaskCreatePinnedToCore(serial_func3, "Task3Function", 1024, NULL, 3, &s3, 1);
}