#pragma once

//-------------------------------------
// Creamos aquí esta clase para no crear dependencias entre Core y Kernel
//-------------------------------------

//-------------------------------------
#if defined(WIN32) || defined(_WIN32)
	#define WIN32_LEAN_AND_MEAN 1
	#include <Windows.h>

	#undef GetCurrentTime
	#undef SendMessage
#else
	#include <pthread.h>
	
	#if defined(PTHREAD_MUTEX_RECURSIVE) && !defined(PTHREAD_MUTEX_RECURSIVE_NP)
		#define PTHREAD_MUTEX_RECURSIVE_NP	PTHREAD_MUTEX_RECURSIVE
	#endif
#endif
//-------------------------------------

//-------------------------------------
namespace MindShake
{

#if defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)

	#if defined(_MSC_VER)
		#define	kTRY		__try {
		#define	kEXCEPT		} __except(EXCEPTION_EXECUTE_HANDLER) { }
	#else
		#define	kTRY
		#define	kEXCEPT
	#endif

	//-------------------------------------
	class CMiniCriticalSection
	{
		public:
			inline
			CMiniCriticalSection()
			{
				kTRY
				InitializeCriticalSection(&mCriticalSection);
				kEXCEPT
			}
				
			inline
			~CMiniCriticalSection()
			{
				kTRY
				DeleteCriticalSection(&mCriticalSection);
				kEXCEPT
			}

			inline void
			Lock()
			{
				EnterCriticalSection(&mCriticalSection);
			}
			
			inline void
			Unlock()
			{
				LeaveCriticalSection(&mCriticalSection);
			}

		protected:
			CRITICAL_SECTION	mCriticalSection;
	};
	
#else

	//-------------------------------------
	class CMiniCriticalSection
	{
		public:
			inline
			CMiniCriticalSection()
			{
				// Set the mMutex as a recursive mMutex
				pthread_mutexattr_settype(&mMutexAttr, PTHREAD_MUTEX_RECURSIVE_NP);

				// create the mMutex with the attributes set
				pthread_mutex_init(&mMutex, &mMutexAttr);

				//After initializing the mMutex, the thread attribute can be destroyed
				pthread_mutexattr_destroy(&mMutexAttr);
			}
				
			inline
			~CMiniCriticalSection()
			{
				// Destroy / close the mMutex
				pthread_mutex_destroy(&mMutex);
			}

			inline void
			Lock()
			{
				// Acquire the mMutex to access the shared resource
				pthread_mutex_lock(&mMutex);
			}
			
			inline void
			Unlock()
			{
				// Release the mMutex and release the access to shared resource
				pthread_mutex_unlock(&mMutex);
			}

		protected:
			pthread_mutex_t		mMutex;       // Mutex
			pthread_mutexattr_t mMutexAttr;   // Mutex attribute variable
	};

#endif

} // end of namespace
