#include <iostream>
#include "TProc.h"

int main()
{
  TQueue<int> a(4);
  a.Put(4);
  a.Put(3);
  a.Pop();
  a.Put(2);
  a.Put(3);
  a.Put(4);
  a.Pop();
  a.Pop();
  a.Put(4);
  a.Put(4);
  for (int i = 0; i < 4; i++)
  {
    std::cout << a.Pop() << std::endl;
  }
  TProc proc[3] = { TProc(0.5), TProc(0.2), TProc(0.5) };
  TJobStream jobstream[3] = { TJobStream(0.5), TJobStream(0.5), TJobStream(0.2) };
  int tactsCount[3] = { 10, 10, 10 };
  TQueue<int> queue;
  for (int i = 0; i < 3; i++)
  {
    std::cout << "Count of tacts " << tactsCount[i] << ", Queue size 3, JobsIntense " << jobstream[i].GetJobIntens() << ", Proc rate " << proc[i].GetProcRate() << '.' << std::endl;
    for (int j = 0; j < tactsCount[i]; j++)
    {
      int temp_job = jobstream[i].GetNewJob();
      if (temp_job > 0)
        queue.Put(temp_job);
      if (!queue.IsEmpty())
        if (proc[i].RunNewJob(queue.Top()))
          queue.Pop();
      proc[i].Work();
    }
    std::cout << "Jobs Generated " << jobstream[i].GetJobCount() << ", Proc Jobs Done " << \
      proc[i].GetJobsDone() << ", Proc Jobs Overflow " << proc[i].GetTimeLim() << \
      ", Proc No Jobs Tacts " << proc[i].GetIdleProc() << ", average " << ((double)(tactsCount[i]) / (double)(proc[i].GetJobsDone())) << \
      " tacts done per job." << std::endl << std::endl;
  }
  return 0;
}