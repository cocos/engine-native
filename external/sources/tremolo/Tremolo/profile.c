/*
 * Dead simple processor sampling profiling code.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "windows.h"

static int             *Profile_table             = NULL;
static int              Profile_table_size        = 0;
static int              Profile_table_granularity = 0;
static DWORD            (*ProfileFn)(void *);
static void            *ProfileArgs;
static volatile HANDLE  threadToProfile = NULL;
static volatile HANDLE  thread = NULL;
static volatile int     die = 0;
static volatile int     taskDone = 0;

void Profile_dump()
{
    FILE *file;

    die = 1;
    while (die)
    {
        Sleep(1);
    }

    file = fopen("profile", "wb");
    if(file == NULL)
    {
        Output("Failed to open profile output");
        return;
    }
    Output("Dumping profile...");

    fputc('P', file);
    fputc('R', file);
    fputc('0', file);
    fputc('F', file);

    fwrite(&Profile_table_granularity, 4, 1, file);
    fwrite(Profile_table, 4, Profile_table_size>>2, file);
    fclose(file);
}

static DWORD ticker(LPVOID dummy)
{
    CONTEXT context;
    int     offset;

    memset(&context, 0, sizeof(CONTEXT));
    {
        while (!die)
        {
            Sleep(10);
            context.ContextFlags = CONTEXT_FULL;
            if (GetThreadContext(thread, &context))
            {
                offset = context.Pc & ~0xF0000000;

                offset >>= Profile_table_granularity+2;
                if (offset >= (Profile_table_size>>2))
                {
                    offset = 0;
                }
            }
            else
            {
                offset = 0;
            }
            Profile_table[offset]++;
        }
    }
    die = 0;
}

void Profile_init(int size,
                  int granularity)
{
    HANDLE myThread;

    Profile_table_granularity = granularity;
    Profile_table_size        = (size+(1<<granularity)-1)>>granularity;
    Profile_table             = (int *)malloc(Profile_table_size);
    if (Profile_table == NULL)
    {
        Output("Failed to get memory for Profile table\n");
        exit(EXIT_FAILURE);
    }
    memset(Profile_table, 0, Profile_table_size);

    thread = (HANDLE)GetCurrentThreadId();

    Output("Commencing profiling");
    myThread = CreateThread(NULL, /* Security Attributes */
                            0,
                            &ticker,
                            NULL,
                            0,
                            NULL);
    if (myThread == NULL)
    {
        Output("Profiler failed to start");
        exit(EXIT_FAILURE);
    }

    SetThreadPriority(myThread, THREAD_PRIORITY_ABOVE_NORMAL);
}
