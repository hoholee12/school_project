#include<windows.h>
#include<stdio.h>
#include<signal.h>

DWORD WINAPI MyThreadFunction(LPVOID long_pointer_param){
	for (int i=0;;i++){
		Sleep(1000);
		printf("%dhello\n", i);
	
	}
	return 0;
}

HANDLE handled_thread;

void kill_thread(){
	if(CloseHandle(handled_thread)) printf("closed properly\n");
	exit(0);
}

int main(){
	DWORD dword_thread_id, dword_thread_param = 1;


	handled_thread = _beginthreadex( //use this instead of CreateThread()
		NULL, // default security attributes
		0, // use default stack size
		MyThreadFunction, // thread function
		&dword_thread_param, // argument to thread function
		0, // use default creation flags
		&dword_thread_id
		);
	signal(SIGINT, kill_thread);

	if (!handled_thread){
		printf("problem.");
		abort();
	}
	else printf("handled thread id is %u\n", dword_thread_id);
	for (;;){
		Sleep(1000);
	
	}
	//if (CloseHandle(handled_thread)) printf("closed properly!\n");

	return 0;
}