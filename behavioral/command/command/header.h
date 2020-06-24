#ifndef HEADER_H
#define HEADER_H

#include "commandInvoker.h"
#include <limits>

LPCSTR pathToDirectory{ R"(..\exampleDirectory)" };

enum class commands : short { fileCreator, directoryCreator, fileRemover, finisher};

#endif // HEADER_H