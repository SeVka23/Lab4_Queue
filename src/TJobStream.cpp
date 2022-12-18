#include <cstdlib>
#include "TJobStream.h"

TJobStream::TJobStream(double intens)
{
  if ((intens < 0.0) || (intens > 1.0)) throw "error";
  jobIntens = intens;
  jobCount = 1;
}

int TJobStream::GetNewJob()
{
  double job = (double)rand() / (double)RAND_MAX;
  if (job <= jobIntens)
  {
    jobCount++;
    return jobCount - 1;
  }
  else
    return 0;
}

double TJobStream::GetJobIntens()
{
  return jobIntens;
}

int TJobStream::GetJobCount()
{
  return jobCount;
}