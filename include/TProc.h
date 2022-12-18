#ifndef __TProc_H__
#define __TProc_H__

#include "TQueue.h"
#include "TJobStream.h"

class TProc
{
protected:
  TQueue<int> jobs;
  double procRate;
  int idleProc;
  int jobsDone;
  int timeLim;
public:
  TProc(double rate);
  int IsProcBusy();
  bool IsProcFull();
  int RunNewJob(int _jobId);
  int Work();
  double GetProcRate();
  int GetIdleProc();
  int GetJobsDone();
  int GetTimeLim();
};
#endif