#include <Arduino.h>

class Thread{
public:
    /// @brief Creates a new thread object
    /// @param Func The function to act as the thread core
    /// @param stackSize The stack size to request from FreeRTOS
    /// @param core The core on which the task has to run. Setup and loop runs on core 1, WiFi routine on 0
    Thread(void (*Func)(), long stackSize = 10000, int core = 1);
    void Start();
    void Abort();
    void (*TaskFunc)();
    TaskHandle_t taskHandle;
private:
    int Stage = 0;
    long stackSizeForTask = 0;
};
