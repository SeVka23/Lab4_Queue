#include "TProc.h"

TProc::TProc(double rate)
{
  if ((rate < 0.0) || (rate > 1.0)) throw "error";
  procRate = rate;
  idleProc = 0;
  jobsDone = 0;
  timeLim = 0;
}

int TProc::IsProcBusy()
{
  if (jobs.IsEmpty()) return 0;
  else
    return jobs.Top();
}

bool TProc::IsProcFull()
{
  return jobs.IsFull();
}

int TProc::RunNewJob(int _jobId)
{
  if (_jobId > 0)
  {
    if (IsProcFull())
    {
      timeLim++;
      return 0;
    }
    else
    {
      jobs.Put(_jobId);
      return _jobId;
    }
  }
}

int TProc::Work()
{
  if (!IsProcBusy())
  {
    idleProc++;
    return 0;
  }
  double job = (double)rand() / (double)RAND_MAX;
  if (job <= procRate && IsProcBusy())
  {
    int lastJob = jobs.Pop();
    jobsDone++;
    return lastJob;
  }
  else
    return jobs.Top();
}

double TProc::GetProcRate()
{
  return procRate;
}

int TProc::GetIdleProc()
{
  return idleProc;
}

int TProc::GetJobsDone()
{
  return jobsDone;
}

int TProc::GetTimeLim()
{
  return timeLim;
}