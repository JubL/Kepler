#ifndef FILEIO_H
#define FILEIO_H

#include <iostream>
#include <iomanip>
#include <vector>

#include "functions.h"

using namespace std;

class FileIO
{
  public:
    FileIO(string filename, size_t numTime = 262144);
    ~FileIO();

//    string filename;
    vector<double> data;

    void writeHeader();
    void flushData(vector<double> times);

  private:
    ofstream datafile;
};

#endif
