#pragma once
#include "Recorder.h"
#include <string>

class Interface
{
    int port_value;
public:
    Interface() = default;
    int comm_proc(int argc, const char** argv);
};
