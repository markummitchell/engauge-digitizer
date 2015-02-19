#include <iostream>
#include "LoggerUpload.h"

using namespace std;

LoggerUpload::LoggerUpload()
{
}

void LoggerUpload::assert(bool condition,
                          const char* file,
                          int line)
{
  if (!condition) {

    // Houston, we have a problem
    cerr << "Error in file " << file << " at line " << line << endl;
  }
}
