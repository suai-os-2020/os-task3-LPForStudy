#include "lab3.h"
#include <windows.h>
#include <stdio.h>
#include <map>
#include <string>

#define MAX_SEM_COUNT 10
#define THREADCOUNT 12

//
// lab3 code should be located here!
//

//global ones
HANDLE stdout_mutex;
HANDLE app_mutex;
//std::vector<HANDLE> semaphores;
//regular sems
HANDLE semA, semB, semC, semD, semF, semE, semG, semH, semK, semM, semN, semP;
//for continueted threads
HANDLE semB1, semB2, semB3, semB4, semD1, semF1, semM1, semK1;
//for sequntial_threads
HANDLE semDS, semES, semFS, semBS;
//std::map<std::string, HANDLE> semaphors_map;
std::vector<HANDLE> threads;

unsigned int lab3_thread_graph_id()
{
	return 1;
}

const char* lab3_unsynchronized_threads()
{
	return "bkhm";
}

const char* lab3_sequential_threads()
{
	return "bdef";
}

//http://www.firststeps.ru/mfc/winapi/r.php?117
//1.Run: a
//Wait: none

//2.Run: dcfb
//Wait: a

//3.Run: defb
//Wait: c

//4.mgkb
//Wait: def

//5.mhkb
//Wait: g

//6.Run: nb
//Wait: mhk

//7.Run: p
//Wait: nb

//Threads
DWORD WINAPI thread_a(LPVOID);
DWORD WINAPI thread_b(LPVOID);
DWORD WINAPI thread_c(LPVOID);
DWORD WINAPI thread_d(LPVOID);
DWORD WINAPI thread_e(LPVOID);
DWORD WINAPI thread_f(LPVOID);
DWORD WINAPI thread_g(LPVOID);
DWORD WINAPI thread_k(LPVOID);
DWORD WINAPI thread_h(LPVOID);
DWORD WINAPI thread_m(LPVOID);
DWORD WINAPI thread_n(LPVOID);
DWORD WINAPI thread_p(LPVOID);

HANDLE sem_init(int n)
{
	HANDLE new_sem = CreateSemaphore(nullptr, n, MAX_SEM_COUNT, nullptr);
	if (new_sem)
		return new_sem;
	std::cerr << "Cannot create semaphore, code:" << GetLastError() << std::endl;
	exit(-1);
}

HANDLE create_thread(DWORD(WINAPI* temp)(LPVOID))
{
	HANDLE new_thread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)temp, NULL, 0, NULL);
	if (new_thread)
		return new_thread;
	std::cerr << "Cannot create thread, error code: " << GetLastError() << std::endl;
	exit(-1);
}

void wait_threads()
{
	for (int i = 0; i < THREADCOUNT; i++) 
	{
		//Wait for execute
		while (WaitForSingleObject(threads[i], 0) == WAIT_TIMEOUT) 
		{
			Sleep(0);
		}
	}
}

void print_char(char c)
{
	while (WaitForSingleObject(stdout_mutex, 0) == WAIT_TIMEOUT)
		Sleep(0);
	std::cout << c << std::flush;
	ReleaseMutex(stdout_mutex);
}

//void sem_wait(int i)
//{
//	DWORD dwWaitResult;
//	BOOL bContinue = TRUE;
//	while (dwWaitResult != WAIT_OBJECT_0)
//	{
//		dwWaitResult = WaitForSingleObject(semaphores[i], 0);
//	}
//	if (ReleaseSemaphore(semaphores[i], 1, NULL));
//}

void sem_wait(HANDLE s)
{
	auto status = WaitForSingleObject(s, 0);
	while (status == WAIT_TIMEOUT)
	{
		status = WaitForSingleObject(s, 0);
	}
}

void sem_post(HANDLE s)
{
	ReleaseSemaphore(s, 1, NULL);
}


int lab3_init()
{
	//Mutex
	stdout_mutex = CreateMutex(NULL, false, NULL);
	app_mutex = CreateMutex(NULL, false, NULL);
	//Sems


	/*semaphores.resize(15);
	for (int i = 0; i < 15; i++)
	{
		if (i == 12) semaphores[i] = sem_init(1);
		else semaphores[i] = sem_init(0);
	}*/

	semA = sem_init(0);
	semB = sem_init(0);
	semC = sem_init(0);
	
	semD = sem_init(0);
	semF = sem_init(0);
	semE = sem_init(0);
	
	semG = sem_init(0);
	semH = sem_init(0);
	semK = sem_init(0);
	
	semM = sem_init(0);
	semN = sem_init(0);
	semP = sem_init(0);

	semB1 = sem_init(0);
	semB2 = sem_init(0);
	semB3 = sem_init(0);
	semB4 = sem_init(0);
	semD1 = sem_init(0);
	semF1 = sem_init(0);
	semM1 = sem_init(0);
	semK1 = sem_init(0);

	semDS = sem_init(0);
	semBS = sem_init(1);
	semES = sem_init(0);
	semFS = sem_init(0);

	int count = 0;
	//CreateThread(...);
	//Launching threads
	//1
	threads.resize(12);
	threads[count] = create_thread(thread_a);
	count++;
	//2

	threads[count] = create_thread(thread_b);
	count++;
	threads[count] = create_thread(thread_c);
	count++;
	threads[count] = create_thread(thread_d);
	count++;
	threads[count] = create_thread(thread_f);
	count++;
	//3
	threads[count] = create_thread(thread_e);
	count++;
	////4
	threads[count] = create_thread(thread_g);
	count++;
	threads[count] = create_thread(thread_k);
	count++;
	threads[count] = create_thread(thread_m);
	count++;
	////5
	threads[count] = create_thread(thread_h);
	count++;
	////6
	threads[count] = create_thread(thread_n);
	count++;
	////7
	threads[count] = create_thread(thread_p);
	count++;


	wait_threads();
	//WaitForMultipleObjects(...);
	//Await completion
	//WaitForMultipleObjects(THREADCOUNT, thread_a, TRUE, INFINITE);

	//clear memory
	CloseHandle(stdout_mutex);
	CloseHandle(app_mutex);
	
	CloseHandle(semA);
	CloseHandle(semB);
	CloseHandle(semC);

	return 0;
}

void stage2_wait()
{
	sem_wait(semB);
	sem_wait(semC);
	sem_wait(semF);
	sem_wait(semD);
}

void stage3_wait()
{
	sem_wait(semE);
	sem_wait(semF1);
	sem_wait(semD1);
	sem_wait(semB1);
}

void stage4_wait()
{
	sem_wait(semG);
	sem_wait(semM);
	sem_wait(semK);
	sem_wait(semB2);
}

void stage5_wait()
{
	sem_wait(semH);
	sem_wait(semM1);
	sem_wait(semK1);
	sem_wait(semB3);
}

void stage6_wait()
{
	sem_wait(semN);
	sem_wait(semB4);
}

DWORD WINAPI thread_a(LPVOID)
{

	for (int i = 0; i < 3; i++) { print_char('a'); computation(); }

	//post 1 stage
	for (int i = 0; i < 4; i++) { sem_post(semA); }
	return 0;
}

DWORD WINAPI thread_b(LPVOID)
{
	sem_wait(semA);//wait 1 stage

	for (int i = 0; i < 3; i++) { print_char('b'); computation(); }

	for (int i = 0; i < 4; i++) { sem_post(semB); }
	//Stage 2 wait
	stage2_wait();
	
	//sequential
	for (int i = 0; i < 3; i++) 
	{ 
		sem_wait(semBS);
		print_char('b'); 
		computation(); 
		sem_post(semDS);
	}

	for (int i = 0; i < 4; i++) { sem_post(semB1); }
	stage3_wait();

	for (int i = 0; i < 3; i++) { print_char('b'); computation(); }
	
	for (int i = 0; i < 4; i++) { sem_post(semB2); }
	stage4_wait();

	for (int i = 0; i < 3; i++) { print_char('b'); computation(); }
	
	for (int i = 0; i < 2; i++) { sem_post(semB3); }
	stage5_wait();

	for (int i = 0; i < 3; i++) { print_char('b'); computation(); }
	
	for (int i = 0; i < 1; i++) { sem_post(semB4); }

	return 0;
}

DWORD WINAPI thread_c(LPVOID)
{
	sem_wait(semA);//wait 1 stage


	for (int i = 0; i < 3; i++) { print_char('c'); computation(); }

	for (int i = 0; i < 4; i++) { sem_post(semC); }

	return 0;
}

DWORD WINAPI thread_d(LPVOID)
{
	sem_wait(semA);//wait 1 stage


	for (int i = 0; i < 3; i++) { print_char('d'); computation(); }

	for (int i = 0; i < 4; i++) { sem_post(semD); }
	//Stage 2 wait
	stage2_wait();
	
	
	//sequential
	for (int i = 0; i < 3; i++) 
	{
		sem_wait(semDS);
		print_char('d'); 
		computation(); 
		sem_post(semES);
	}

	for (int i = 0; i < 4; i++) { sem_post(semD1); }

	return 0;
}

DWORD WINAPI thread_e(LPVOID)
{
	//Stage 2 wait
	stage2_wait();

	//sequential
	for (int i = 0; i < 3; i++) 
	{ 
		sem_wait(semES);
		print_char('e'); 
		computation();
		sem_post(semFS);
	}

	for (int i = 0; i < 4; i++) { sem_post(semE); }

	return 0;
}

DWORD WINAPI thread_f(LPVOID)
{
	sem_wait(semA);//wait 1 stage

	for (int i = 0; i < 3; i++) { print_char('f'); computation(); }

	for (int i = 0; i < 4; i++) { sem_post(semF); }
	//Stage 2 wait
	stage2_wait();
	
	//sequential
	for (int i = 0; i < 3; i++) 
	{ 
		sem_wait(semFS);
		print_char('f'); 
		computation();
		sem_post(semBS);
	}

	for (int i = 0; i < 4; i++) { sem_post(semF1); }

	return 0;
}

DWORD WINAPI thread_g(LPVOID)
{
	stage3_wait();
	for (int i = 0; i < 3; i++) { print_char('g'); computation(); }

	for (int i = 0; i < 4; i++) { sem_post(semG); }
	return 0;
}

DWORD WINAPI thread_h(LPVOID)
{
	stage4_wait();
	for (int i = 0; i < 3; i++) { print_char('h'); computation(); }

	for (int i = 0; i < 2; i++) { sem_post(semH); }
	return 0;
}

DWORD WINAPI thread_k(LPVOID)
{
	stage3_wait();
	for (int i = 0; i < 3; i++) { print_char('k'); computation(); }
	
	for (int i = 0; i < 4; i++) { sem_post(semK); }
	
	stage4_wait();

	for (int i = 0; i < 3; i++) { print_char('k'); computation(); }

	for (int i = 0; i < 2; i++) { sem_post(semK1); }

	return 0;
}

DWORD WINAPI thread_m(LPVOID)
{
	stage3_wait();
	for (int i = 0; i < 3; i++) { print_char('m'); computation(); }

	for (int i = 0; i < 4; i++) { sem_post(semM); }

	stage4_wait();

	for (int i = 0; i < 3; i++) { print_char('m'); computation(); }

	for (int i = 0; i < 2; i++) { sem_post(semM1); }

	return 0;
}

DWORD WINAPI thread_n(LPVOID)
{
	stage5_wait();
	for (int i = 0; i < 3; i++) { print_char('n'); computation(); }

	for (int i = 0; i < 1; i++) { sem_post(semN); }
	return 0;
}

DWORD WINAPI thread_p(LPVOID)
{
	stage6_wait();
	for (int i = 0; i < 3; i++) { print_char('p'); computation(); }


	return 0;
}