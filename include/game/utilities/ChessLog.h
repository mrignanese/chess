#pragma once

#include <iostream>

#if DEBUG
#define CHESS_LOG(msg, val) std::cout << msg << ": " << val << std::endl;
#else
#define CHESS_LOG(msg, val)
#endif
