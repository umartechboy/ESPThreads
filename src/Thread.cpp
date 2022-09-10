#include "Thread.h"

Thread* threadToTask = 0;
bool taskStarted = false;
void runFunc(Thread& thread)
{
}
void taskFunc( void * pvParameters ){
    auto thread = threadToTask;
    taskStarted = true;
    (*(thread->TaskFunc))();
    vTaskDelete(0);
}
Thread::Thread(void (*Func)(), long stackSize, int core) {
    this->TaskFunc = Func;
    this->stackSizeForTask = stackSize;
}
void Thread::Start() {
    if (this->Stage != 0)
        return;
    threadToTask = this;
    xTaskCreatePinnedToCore(taskFunc, "", this->stackSizeForTask, 0, tskIDLE_PRIORITY, &taskHandle, 0);
    
    taskStarted = false;
    while(!taskStarted){
        yield();
    }
    delay(1);
    this->Stage = 1;
}
void Thread::Abort(){
    if (this->Stage != 1)
        return;
    Stage = 2;
    vTaskDelete(taskHandle);
}