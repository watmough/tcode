#include <stdio.h>
#include <time.h>
#include <string.h>

#define MAX_BUF 1024

//--------------------------------------------------------------------------------
// main
//
// This program reads from standard input and prefixes each line read with the 
// elapsed time in hours:minutes:seconds, from when the program was started.
//
// You might want to use this to add a time code to ICYCast/Shoutcast song titles
// that are output from mplayer when downloading an internet stream, as it does not
// appear to preserve the ICYCast data when dumping the stream.
//
// OS X Usage:
/*
 
#!/bin/sh
/Library/Application\ Support/ffmpegX/mplayer -dumpstream <STREAM> -dumpfile `date "+%Y%m%d"`_<NAME>.pls | ./tcode
 
*/
//--------------------------------------------------------------------------------
int main (int argc, const char * argv[]) {
    
	// declare a buffer
	char buffer[MAX_BUF];
	
	// start time -- optional move this to trip when we get the first line
	// streams usually start up pretty fast, so unlikely to be > few secs out
	time_t start;
	start = time(NULL);				// seconds since Jan 1970 on Mac OS X

	// read a line
    while( fgets(&buffer[0], MAX_BUF, stdin)) {
		
		// calculate elapsed time
		time_t elapsed = time(NULL)-start;
		int hours = elapsed / (60*60);
		int minutes = (elapsed / 60) % 60;
		int seconds = elapsed % 60;
		
		// prefix non-blank lines with elapsed time
		if(strlen(buffer)>2)
			printf("%02d:%02d:%02d %s",hours,minutes,seconds,buffer);
		else
			printf("%s",buffer);
	}
	
	return 0;
}

