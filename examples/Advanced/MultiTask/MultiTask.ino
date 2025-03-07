/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with Atom-Lite/Matrix sample source code
*                          配套  Atom-Lite/Matrix 示例源代码
* Visit the website for more information：https://docs.m5stack.com/en/products
* 获取更多资料请访问：https://docs.m5stack.com/zh_CN/products
*
* describe：MultiTask.  多线程
* date：2021/7/27
*******************************************************************************
*/

#include <M5Atom.h>

void task1(void * pvParameters) { //Define the tasks to be executed in thread 1.  定义线程1内要执行的任务
  while(1){ //Keep the thread running.  使线程一直运行
    Serial.print("task1 Uptime (ms): ");
    Serial.println(millis()); //The running time of the serial port printing program.  串口打印程序运行的时间
    delay(100); //With a delay of 100ms, it can be seen in the serial monitor that every 100ms, thread 1 will be executed once.  延迟100ms,在串口监视器内可看到每隔100ms,线程1就会被执行一次
  }
}

void task2(void * pvParameters) {
  while(1){
    Serial.print("task2 Uptime (ms): ");
    Serial.println(millis());
    delay(200);
  }
}

void task3(void * pvParameters) {
  while(1){
    Serial.print("task3 Uptime (ms): ");
    Serial.println(millis());
    delay(1000);
  }
}

void setup() {
  M5.begin(true, false, true); //Init Atom(Initialize serial port, LED).  初始化 ATOM(初始化串口、LED点阵)
  // Creat Task1.  创建线程1
  xTaskCreatePinnedToCore(
                  task1,     //Function to implement the task.  线程对应函数名称(不能有返回值)
                  "task1",   //线程名称
                  4096,      // The size of the task stack specified as the number of * bytes.任务堆栈的大小(字节)
                  NULL,      // Pointer that will be used as the parameter for the task * being created.  创建作为任务输入参数的指针
                  1,         // Priority of the task.  任务的优先级
                  NULL,      // Task handler.  任务句柄
                  0);        // Core where the task should run.  将任务挂载到指定内核

  // Task 2
  xTaskCreatePinnedToCore(
                  task2,
                  "task2",
                  4096,
                  NULL,
                  2,
                  NULL,
                  0);

  // Task 3
  xTaskCreatePinnedToCore(
                  task3,
                  "task3",
                  4096,
                  NULL,
                  3,
                  NULL,
                  0);
}

void loop() {
  M5.dis.fillpix(0xFFA500);
}