#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include"freertos/queue.h"
const TickType_t xDelay1 =1000 / portTICK_PERIOD_MS;
const TickType_t xDelay2=2000 / portTICK_PERIOD_MS;
const TickType_t xDelay3 =5000 / portTICK_PERIOD_MS;
static int taskcore = 1;

TaskHandle_t first_task_handle;
TaskHandle_t second_task_handle;
TaskHandle_t third_task_handle;
TaskHandle_t fourth_task_handle;

QueueHandle_t queue_buff_handle;


void first_task(void *data)
{
   
   printf("task1\n");
   while(1)
   {
   printf("enter in task 1 \n");
   
    vTaskDelay(xDelay1);
   }
   vTaskDelete(NULL);
}

void second_task(void *data)
{
  
   printf("task2\n");
   while(1)
   {
    printf("enter in the task 2\n");
    vTaskDelay(xDelay2);
   }
   vTaskDelete(NULL);
}
void third_task(void *data)
{
   
   printf("task3\n");
   while(1)
   {
    printf("enter in the task 3\n");
    vTaskDelay(xDelay2);
   }
   vTaskDelete(NULL);
}
void fourth_task(void *data)
{
   int task2_data=100;
   printf("task4 \n");
   while(1)
   {
    task2_data++;
    xQueueSend(queue_buff_handle,&task2_data,xDelay1);
    vTaskDelay(xDelay1);
   }
   vTaskDelete(NULL);
}

void five_task(void *data)

{
    int buffer=0;
    int count=0;

   printf("task5\n");
   while(1)
   {
    xQueueReceive(queue_buff_handle,&buffer,xDelay1);
    printf("task5:recieved data:%d\n",buffer);
    count++;
    if(count>50)
    {
        count=0;
        
        vTaskDelay(xDelay1);
    }
    }
   vTaskDelete(NULL);
}

void app_main()
{
  
    printf("DESD RTOS\n");
    queue_buff_handle=xQueueCreate(4,1);
    
    xTaskCreatePinnedToCore(first_task,"firsttask",2048,NULL,5,&first_task_handle,taskcore);
    xTaskCreatePinnedToCore(second_task,"secondtask",2048,NULL,6,&second_task_handle,taskcore);
    xTaskCreatePinnedToCore(third_task,"third",2048,NULL,7,&third_task_handle,taskcore); 
     xTaskCreatePinnedToCore(fourth_task,"fourth",2048,NULL,8,&second_task_handle,taskcore);
    xTaskCreatePinnedToCore(five_task,"five",2048,NULL,9,&third_task_handle,taskcore); 

}