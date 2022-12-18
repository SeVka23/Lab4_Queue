#ifndef __TJobStream_H__
#define __TJobStream_H__

class TJobStream
{
protected:
  double jobIntens;
  int jobCount;
public:
  TJobStream(double intens);
  int GetNewJob();
  double GetJobIntens();
  int GetJobCount();
};
#endif