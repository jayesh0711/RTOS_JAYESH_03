#include<stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/FreeRTOSConfig.h>
#include<freertos/task.h>
#include<freertos/timers.h>


TaskHandle_t task1Handle, task2Handle, task3Handle;
TimerHandle_t TimerCreate;
static int Taskcore = 1;

void TimerCallback(TimerHandle_t xTimer) 
{
    printf("in the callback function");
}


void Task1(void * data) 
{
    
    const TickType_t xDelay = 1000 / portTICK_PERIOD_MS;
   
    while(1)
    {
        printf("Task1 : running...\n");
        vTaskDelay(xDelay);
    }
    vTaskDelete(task1Handle);
}

void Task2(void * data) 
{
    
    const TickType_t xDelay = 2000 / portTICK_PERIOD_MS;
    
    while(1)
    {
        printf("Task2 : running...\n");
        vTaskDelay(xDelay);
    }
    vTaskDelete(task2Handle);
}

void Task3(void * data) 
{
    
    const TickType_t xDelay = 5000 / portTICK_PERIOD_MS;
    TimerCreate = xTimerCreate("Timer is started", pdMS_TO_TICKS(10000), pdFALSE, (void*)0, TimerCallback);
    if(TimerCreate == NULL) {
        perror("error in timer creation ");
        exit(EXIT_FAILURE);
    }
    printf("Timer started......\n");
    xTimerStart(TimerCreate,0);

    while(1)
    {
        printf("Task3 : running....\n");
        vTaskDelay(xDelay);
    }

   
    vTaskDelete(task3Handle);
}


void app_main()
{ 
    //Base_t
     xTaskCreatePinnedToCore(Task1, "Task2", 2048, NULL, 5, &task2Handle,Taskcore);
    //if(task1Return != pdPASS) {
      //  perror("error in task1 ");
        //exit(EXIT_FAILURE);
    //}
    printf("Task1 : created\n");
     xTaskCreatePinnedToCore(Task2, "Task2", 2048, NULL, 6, &task2Handle,Taskcore);
    // if(task2Return != pdPASS) {
    //     perror("error in task2 ");
    //     exit(EXIT_FAILURE);
    // }
    printf("Task2 : created\n");

    xTaskCreatePinnedToCore(PinnedToCreateTask3, "Task3", 2048, NULL, 7, &task3Handle,Taskcore);
    // if(task3Return != pdPASS) {
    //     perror("error in task3 ");
    //     exit(EXIT_FAILURE);
    // }
    printf("Task3 : created\n");
}