/********************************************************************
 *                                                                  *
 * THIS FILE IS PART OF THE OggVorbis 'TREMOR' CODEC SOURCE CODE.   *
 *                                                                  *
 * USE, DISTRIBUTION AND REPRODUCTION OF THIS LIBRARY SOURCE IS     *
 * GOVERNED BY A BSD-STYLE SOURCE LICENSE INCLUDED WITH THIS SOURCE *
 * IN 'COPYING'. PLEASE READ THESE TERMS BEFORE DISTRIBUTING.       *
 *                                                                  *
 * THE OggVorbis 'TREMOR' SOURCE CODE IS (C) COPYRIGHT 1994-2002    *
 * BY THE Xiph.Org FOUNDATION http://www.xiph.org/                  *
 *                                                                  *
 ********************************************************************

 function: simple example decoder using vorbisidec

 ********************************************************************/

/* Takes a vorbis bitstream from stdin and writes raw stereo PCM to
   stdout using vorbisfile. Using vorbisfile is much simpler than
   dealing with libvorbis. */

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "ivorbiscodec.h"
#include "ivorbisfile.h"
#include "time.h"
#include "windows.h"

#define PROFILE

#ifdef _WIN32 /* We need the following two to set stdin/stdout to binary */
#include <io.h>
#include <fcntl.h>
#endif

char pcmout[4096]; /* take 4k out of the data segment, not the stack */
char ref[4096];    /* take 4k out of the data segment, not the stack */
char text[4096];

void Output(const char *fmt, ...)
{
#ifdef _WIN32_WCE
  va_list  ap;
  char    *t = text;
  WCHAR    uni[4096];
  WCHAR   *u = uni;

  va_start(ap,fmt);
  vsprintf(text, fmt, ap);
  va_end(ap);

  while (*t != 0)
  {
      *u++ = (WCHAR)(*t++);
  }
  *u++ = 0;
  OutputDebugString(uni);
#else
  vfprintf(stderr, fmt, ap);
#endif
}

typedef struct
{
    FILE *in;
    FILE *out;
    FILE *refin;
    FILE *refout;
    int   max_samples;
} TestParams;

static DWORD run_test(void *tp)
{
  TestParams     *params      = (TestParams *)tp;
  FILE           *in          = params->in;
  FILE           *out         = params->out;
  FILE           *refin       = params->refin;
  FILE           *refout      = params->refout;
  int             max_samples = params->max_samples;
  OggVorbis_File  vf;
  int eof=0;
  int current_section;
  int maxdiff = 0;
  int countdiffs = 0;
  int samples = 0;

  if(ov_open(in, &vf, NULL, 0) < 0) {
    Output("Input does not appear to be an Ogg bitstream.\n");
    exit(1);
  }

  /* Throw the comments plus a few lines about the bitstream we're
     decoding */
  {
    char **ptr=ov_comment(&vf,-1)->user_comments;
    vorbis_info *vi=ov_info(&vf,-1);
    if (out != NULL)
    {
      while(*ptr){
        Output("%s\n",*ptr);
        ++ptr;
      }
      Output("\nBitstream is %d channel, %ldHz\n",vi->channels,vi->rate);
      Output("\nDecoded length: %ld samples\n",
             (long)ov_pcm_total(&vf,-1));
      Output("Encoded by: %s\n\n",ov_comment(&vf,-1)->vendor);
    }
  }

  while((!eof) && (max_samples > 0)){
    long ret=ov_read(&vf,pcmout,sizeof(pcmout),&current_section);
    if (ret == 0) {
      /* EOF */
      eof=1;
    } else if (ret < 0) {
      /* error in the stream.  Not a problem, just reporting it in
	 case we (the app) cares.  In this case, we don't. */
    } else {
      /* we don't bother dealing with sample rate changes, etc, but
	 you'll have to*/
      if (out != NULL)
      {
        fwrite(pcmout,1,ret,out);
      }
      max_samples -= ret>>1;
      if (refout != NULL)
      {
        fwrite(pcmout,1,ret,refout);
        samples += ret>>1;
        Output("%d", samples);
      }
      if (refin != NULL)
      {
        int i, diff;

        fread(ref,1,ret,refin);
        for (i=0; i<(ret>>1);i++)
        {
          diff = ((short *)pcmout)[i] - ((short *)ref)[i];
          if (diff != 0)
          {
            if (diff < 0)
              diff = -diff;
            if (diff > maxdiff)
              maxdiff = diff;
            countdiffs++;
            if (countdiffs < 50)
            {
              Output("samples differ: %x vs %x\n",
                     ((unsigned short *)pcmout)[i],
                     ((unsigned short *)ref)[i]);
            }
            else if ((countdiffs % 100) == 0)
            {
              Output("%d differences, maximum = %d\n",
                     countdiffs, maxdiff);
            }
          }
        }
      }
    }
  }

  /* cleanup */
  ov_clear(&vf);

  return 0;
}

static int filetimetoms(FILETIME *time)
{
  unsigned long long l;

  l = ((unsigned long long)time->dwLowDateTime) + (((unsigned long long)time->dwHighDateTime)<<32);

  return (int)(l/10000);
}

char speedblock[32768];
void speedtest()
{
  int      readtime;
  FILETIME userStartTime, userStopTime;
  FILETIME kernelStartTime, kernelStopTime;
  FILETIME exitStartTime, exitStopTime;
  FILETIME creationStartTime, creationStopTime;

  Output("Speed test: STMIA speed\n");

  GetThreadTimes(GetCurrentThread(),
                 &creationStartTime,
                 &exitStartTime,
                 &kernelStartTime,
                 &userStartTime);
  stmiaTest(speedblock, 32768, 65536);
  GetThreadTimes(GetCurrentThread(),
                 &creationStopTime,
                 &exitStopTime,
                 &kernelStopTime,
                 &userStopTime);
  readtime = filetimetoms(&userStopTime)-filetimetoms(&userStartTime);
  Output("Speed test complete: Timing=%g\n",
          ((double)readtime)/1000);

  Output("Speed test: STR speed\n");

  GetThreadTimes(GetCurrentThread(),
                 &creationStartTime,
                 &exitStartTime,
                 &kernelStartTime,
                 &userStartTime);
  strTest(speedblock, 32768, 65536);
  GetThreadTimes(GetCurrentThread(),
                 &creationStopTime,
                 &exitStopTime,
                 &kernelStopTime,
                 &userStopTime);
  readtime = filetimetoms(&userStopTime)-filetimetoms(&userStartTime);
  Output("Speed test complete: Timing=%g\n",
          ((double)readtime)/1000);

  Output("Speed test: SMULL speed\n");

  GetThreadTimes(GetCurrentThread(),
                 &creationStartTime,
                 &exitStartTime,
                 &kernelStartTime,
                 &userStartTime);
  smullTest(speedblock, 32768, 65536);
  GetThreadTimes(GetCurrentThread(),
                 &creationStopTime,
                 &exitStopTime,
                 &kernelStopTime,
                 &userStopTime);
  readtime = filetimetoms(&userStopTime)-filetimetoms(&userStartTime);
  Output("Speed test complete: Timing=%g\n",
          ((double)readtime)/1000);
}

int main(int argc, char *argv[]){
  FILE       *in;
  FILE       *out = NULL;
  FILE       *refin = NULL;
  FILE       *refout = NULL;
  int         dectime, readtime;
  FILETIME    userStartTime, userStopTime;
  FILETIME    kernelStartTime, kernelStopTime;
  FILETIME    exitStartTime, exitStopTime;
  FILETIME    creationStartTime, creationStopTime;
  TestParams  params;

  if (argc < 2)
  {
    Output("Syntax: testtremor <infile> [<outfile>]\n");
    exit(EXIT_FAILURE);
  }

#ifdef PROFILE
  in = fopen(argv[1], "rb");
  if (in == NULL)
  {
    Output("Failed to open '%s' for input\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  params.in          = in;
  params.out         = NULL;
  params.refin       = NULL;
  params.refout      = NULL;
  params.max_samples = 0x7FFFFFFF;
  Profile_init(184000, 4);
  run_test(&params);
  Profile_dump();
#else
  in = fopen(argv[1], "rb");
  if (in == NULL)
  {
    Output("Failed to open '%s' for input\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  if (argc >= 3)
  {
    out = fopen(argv[2], "wb");
    if (out == NULL)
    {
      Output("Failed to open '%s' for output\n", argv[2]);
      exit(EXIT_FAILURE);
    }
  }

  if (argc >= 4)
  {
    refin = fopen(argv[3], "rb");
    if (refin == NULL)
    {
      Output("Can't find reference file. Creating instead.\n");
      refout = fopen(argv[3], "wb");
      if (refout == NULL)
      {
        Output("Failed to open '%s' as output reference file\n", argv[3]);
        exit(EXIT_FAILURE);
      }
    }
  }

  Output("First test: Decode correctness\n");
  params.in          = in;
  params.out         = out;
  params.refin       = refin;
  params.refout      = refout;
  params.max_samples = 1*1024*1024;
  run_test(&params);
  Output("First test complete\n");
  if (out != NULL)
    fclose(out);
  if (refin != NULL)
    fclose(refin);
  if (refout != NULL)
    fclose(refout);
  Output("Second test: Decode speed\n");
  in = fopen(argv[1], "rb");
  if (in == NULL)
  {
    Output("Failed to open '%s' for input\n", argv[1]);
    exit(EXIT_FAILURE);
  }
  GetThreadTimes(GetCurrentThread(),
                 &creationStartTime,
                 &exitStartTime,
                 &kernelStartTime,
                 &userStartTime);
  params.in          = in;
  params.out         = NULL;
  params.refin       = NULL;
  params.refout      = NULL;
  params.max_samples = 0x7FFFFFFF;
  run_test(&params);
  GetThreadTimes(GetCurrentThread(),
                 &creationStopTime,
                 &exitStopTime,
                 &kernelStopTime,
                 &userStopTime);

  dectime = filetimetoms(&userStopTime)-filetimetoms(&userStartTime);
  Output("Second test complete: Timing=%g\n",
         ((double)dectime)/1000);
  Output("Third test: File read speed\n");

  in = fopen(argv[1], "rb");
  if (in == NULL)
  {
    Output("Failed to open '%s' for input\n", argv[1]);
    exit(EXIT_FAILURE);
  }
  GetThreadTimes(GetCurrentThread(),
                 &creationStartTime,
                 &exitStartTime,
                 &kernelStartTime,
                 &userStartTime);
  while (!feof(in))
  {
    fread(pcmout,1,4096,in);
  }
  GetThreadTimes(GetCurrentThread(),
                 &creationStopTime,
                 &exitStopTime,
                 &kernelStopTime,
                 &userStopTime);
  readtime = filetimetoms(&userStopTime)-filetimetoms(&userStartTime);
  Output("Third test complete: Timing=%g\n",
          ((double)readtime)/1000);
  Output("Adjusted decode time: Timing=%g\n",
         ((double)(dectime-readtime))/1000);
#endif
  Output("Done.\n");
  return(0);
}

#ifdef _WIN32_WCE

#define TESTFILE 0

int WinMain(HINSTANCE h,HINSTANCE i,LPWSTR l,int n)
{
#if TESTFILE == 9
  char *argv[] = { "testtremor",
                   "\\Storage Card\\Tremolo\\infile9.ogg",
                   "\\Storage Card\\Tremolo\\output9.pcm",
#ifdef _LOW_ACCURACY_
                   "\\Storage Card\\Tremolo\\outputL9.ref",
#else
                   "\\Storage Card\\Tremolo\\output9.ref",
#endif /* _LOW_ACCURACY_ */
                   NULL };
#endif
#if TESTFILE == 2
  char *argv[] = { "testtremor",
                   "\\Storage Card\\Tremolo\\infile2.ogg",
                   "\\Storage Card\\Tremolo\\output2.pcm",
#ifdef _LOW_ACCURACY_
                   "\\Storage Card\\Tremolo\\outputL2.ref",
#else
                   "\\Storage Card\\Tremolo\\output2.ref",
#endif /* _LOW_ACCURACY_ */
                   NULL };
#endif
#if TESTFILE == 0
  char *argv[] = { "testtremor",
                   "\\Storage Card\\Tremolo\\infile.ogg",
                   "\\Storage Card\\Tremolo\\output.pcm",
#ifdef _LOW_ACCURACY_
                   "\\Storage Card\\Tremolo\\outputL.ref",
#else
                   "\\Storage Card\\Tremolo\\output.ref",
#endif /* _LOW_ACCURACY_ */
                   NULL };
#endif
  return main(4, argv);
}
#endif

