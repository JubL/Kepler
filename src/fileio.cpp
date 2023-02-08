#include "fileio.h"

using namespace std;

FileIO::FileIO(string filename, size_t numTime)
{
    data.reserve(numTime);

    datafile.open(filename);
}

FileIO::~FileIO()
{
    datafile.close();
}

void FileIO::writeHeader()
{
    datafile << "# time in days | normalized lightcurve | magnitude" << endl;
}

void FileIO::flushData(vector<double> times)
{
    datafile << setprecision(16);
    for(size_t i = 0; i < data.size(); i++)
    {
        datafile << times[i]/86400. << " " << data[i] << " " << calcMag(data[i]) << endl;
    }
    data.clear();
}
