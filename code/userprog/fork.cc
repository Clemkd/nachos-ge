#include "fork.h"

void ProcessHandler(int arg)
{
	AddrSpace* space = (AddrSpace*) arg;
	currentThread->space = space;
	currentThread->space->InitRegisters();
	currentThread->space->RestoreState();
	//machine->WriteRegister(RetAddrReg, (int)ProcessExit);

	machine->Run();
}

int ForkExec(char* s)
{
	OpenFile *executable = fileSystem->Open (s);
	Thread* t = new Thread("forked thread");
	t->PID = Thread::PIDcnt;
	t->PIDcnt++;
	int i;
	processListLock->Acquire();
	for(i = 0; i < NumPhysPages; i++)
	{
		if(processList[i] == -1)
		{
			processList[i] = t->PID;
			break;
		}

	}
	processListLock->Release();
    if (executable == NULL)
    {
		printf ("Unable to open file %s\n", s);
		return -1;
    }
    printf("%d\n", t->PID);

    AddrSpace *space = new AddrSpace (executable);

    delete executable;

    t->Fork(ProcessHandler, (int) space);

    currentThread->Yield();

    return t->PID;
}

void ProcessExit()
{
	currentThread->space->verrou->P();
	//printf("JE MEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEURS\n");
	//while(1){}
	int i;
	processListLock->Acquire();
	for(i = 0; i < NumPhysPages; i++){
		if(processList[i] == currentThread->PID){
			processList[i] = -1;
			break;
		}
	}

	for(i = 0; i < NumPhysPages; i++){
		if(processList[i] >= 0){
			processListLock->Release();
			currentThread->Finish();
		}
	}
	processListLock->Release();
	interrupt->Halt();
}