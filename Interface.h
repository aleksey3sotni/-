#pragma once
#include "Recorder.h"
#include <string>

class Interface
{
    int PORT;
public:
    Interface(){}
    int comm_proc(int argc, const char** argv);
};
