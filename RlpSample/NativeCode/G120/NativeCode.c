#define G120

#include "../RLP.h"

int TestFungsi(void** args) {
    int arg1 = *(int*)(args[0]); //ambil parameter 1
	int arg2 = *(int*)(args[1]); //ambil parameter 2
	unsigned char* arg3 = (unsigned char*)(args[2]); //ambil parameter 3 (byte array)

	int hasil = 1;
	int x;
	for (x = arg2;x > 0;x--) {
		hasil = hasil*arg1;
	}
	
	for (x = 1;x <= sizeof(arg3);x++) {
		arg3[0] += arg3[x];
	}
    return hasil;
}

RLP_Task task;

void TaskCallback(void* arg)
{
	unsigned int* count = (unsigned int*)arg;
	
	RLP->PostManagedEvent(*count);
		
	if (*count > 0)
	{		
		*count -= 1;
		
		RLP->Task.ScheduleTimeOffset(&task, 1000000);	
	}
	else
	{
		RLP->Task.Abort(&task);
	}
}

int StartTask(void** args)
{
	RLP->Task.Initialize(&task, TaskCallback, args[0], RLP_FALSE);
	RLP->Task.Schedule(&task);
	
	return 1;
}
