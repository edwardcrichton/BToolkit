/* Copyright (c) 2007, B-Core (UK) Ltd
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following
conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in
   the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT 
NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE 
COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/
#ifdef MAC_VERSION
#include <Carbon/Carbon.h>
#endif

/*
 * launch.c 2007/06/08
 * 
 * One click launch of the toolkit for non-command line bods.
 * Allows a symbolic link to the resulting executable to launch
 * the toolkit. Also symbolic links to this executable
 * will call the BKIT executable with the symlink name
 * e.g. usr/bin/BToolkitd_util -> .../BKIT/Blauncher allows BToolkitd_util
 * to be called from the command line
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <limits.h>
#include <unistd.h>

/*
	Moves the null character to the end of the last slash.
*/
void dirname(path)
char* path;
{
	size_t end;

	end=strlen(path);
	while(path[end]!='/' && end){end--;}	
	path[end]='\0';
}

/*
	Resolves symbolic links. Overwrites the contents of path. path should have size PATH_MAX.
*/
void canonical(path)
char* path;
{
	char buf[PATH_MAX];
	buf[0]='\0';

	if (realpath(path, buf))
	{
		path[0]='\0';
		strcat(path,buf);
	}
}

/*
	Obvious.
*/

int file_exists(char* filename)
{
	struct stat buf;
	int i;
	i=stat(filename,&buf);
	return (i==0) ? 1 : 0;
}

/*
	Takes the executable path and returns the location of its directory after resolving to an absolute path
        with symbolic links resolved.
*/

char* getExecutableDir(argv0)
const char* argv0;
{
	char *pwd;
	char* result;
	FILE* pfile;
	char which[PATH_MAX];
	
	result=(char *)malloc((size_t) PATH_MAX);
	result[0]='\0';


	if(argv0[0]!='/')
	{
		/* a relative path */

		pwd=(char *)malloc((size_t) PATH_MAX);
		getcwd(pwd, (size_t)PATH_MAX);

		strcat(result,pwd);
		strcat(result,"/");
		strcat(result,argv0);
		
		free(pwd);
		
		/* does this file exist ?
		* If not then ask the shell
		*/

		if(file_exists(result) == 0)
		{			
			strcpy(which,"which ");
			strcat(which,argv0);

                        result[0]='\0';

			pfile=popen(which,"r");
			fgets(result,PATH_MAX,pfile);
			pclose(pfile);
			while( strlen(result) > 0 && result[strlen(result)-1]=='\n')
			{
				result[strlen(result)-1]='\0';
			}
		}
	}
	else
	{
		/* an absolute path */
		strcat(result,argv0);
	}

	canonical(result);
	dirname(result);
	return result;
}

/*
	Gets the directory that this executable is in. Finds the BKIT directory.
	Sets the $BKIT environment variable.
	Creates the B_Projects directory in $HOME
		- if created
		  copies demo directories from $BKIT/BDEMO into $HOME/B_Projects
        If there is no $HOME/XBMotif it copies it from $BKIT .
	Changes working directory to $HOME/B_Projects .
	Adds $BKIT/BLIB to the $PATH variable so that the scripts can be ran without having
	     to know the full path when setting options.
	Ensures the DISPLAY environment variable.
	Calls $BKIT/BToolkit or the executable with the same name used to call this executable in $BKIT
*/

int main(int argc, char* argv[])
{
	char* executabledir;
	size_t exelen=0;
	char env1[PATH_MAX];
	char env3[PATH_MAX];
	char bkit[PATH_MAX];
	char homedir[PATH_MAX];
	char display[PATH_MAX];
	char commandlineargs[PATH_MAX];
	char uname[PATH_MAX];
	char* HOME;
	char* PATH;
	char* DISPLAY;
	FILE* pfile;
	int returnValue;
	
	

	int madeB_Projects=0;

	char* myname;
	int mynamelength;
	int i;
	
	myname=argv[0];
	mynamelength=strlen(myname);
	for(;;)
	{
		if(mynamelength==0){break;}
		if(myname[--mynamelength]=='/')
		{
			myname=myname+mynamelength+1;
			break;
		}
	}
	
	executabledir=getExecutableDir(argv[0]);
	strcpy(bkit,executabledir);

	exelen=strlen(bkit);
	
	if(	!(bkit[exelen-4]=='B' &&
		bkit[exelen-3]=='K' &&
		bkit[exelen-2]=='I' &&
		bkit[exelen-1]=='T'))
	{
		strcat(bkit,"/BKIT");
	}

	strcpy(env1,"BKIT=");
	strcat(env1,bkit);

	putenv(env1);
	
	/*printf("%s\n",env1);*/
	
	/* allow the user to call the btoolkit as BToolkit or btoolkit */
	
	if(strlen(myname)>2)
	{
		if(myname[0]=='b' && myname[1]=='t')
		{
			myname[0]='B';
			myname[1]='T';
		}
		else
		if(myname[0]=='b' && myname[1]=='u')
		{
			myname[0]='B';
			myname[1]='U';
		}
		else
		if(myname[0]=='b' && myname[1]=='p')
		{
			myname[0]='B';
			myname[1]='P';
		}
		else
		if(myname[0]=='b')
		{
			myname[0]='B';
		}
	}
	
	/*
	if this is the btoolkit executable then copy B_Projects
	and change current working directory
	*/
	
	if(
	strcmp(myname,"BToolkit")==0 ||
	strcmp(myname,"Blauncher")==0)
	{

		HOME=getenv("HOME");

		/* make the B_Projects directory
		*  copy the demos
		*  copy XBMotif into $HOME */

		strcpy(homedir,HOME);
		strcat(homedir,"/B_Projects");
		madeB_Projects=mkdir(homedir,S_IRWXU);

		if(madeB_Projects==0)
		{
			/* created it - so copy the DEMO directory too */
			strcpy(homedir,"cp -r ");
			strcat(homedir,bkit);
			strcat(homedir,"/BDEMO/* ");
			strcat(homedir,HOME);
			strcat(homedir,"/B_Projects");
			system(homedir);
		}

		strcpy(homedir,HOME);
		strcat(homedir,"/XBMotif");

		if(file_exists(homedir)==0)
		{
			/* copy XBMotif */
			strcpy(homedir,"cp ");
			strcat(homedir,bkit);
			strcat(homedir,"/XBMotif ");
			strcat(homedir,HOME);
			system(homedir);
		}

		/* change working directory to the B_Projects directory */

		strcpy(homedir,HOME);
		strcat(homedir,"/B_Projects");
		chdir(homedir);
	}
		
	/* add $BKIT/BLIB to path */
	
	strcpy(env3,"PATH=");
	strcat(env3,bkit);
	strcat(env3,"/BLIB:.");
        PATH=getenv("PATH");
	if(PATH!=NULL)
	{
		strcat(env3,":");
		strcat(env3,PATH);
	}
	putenv(env3);
	/*printf("%s\n",env3);*/
	
	if(
	strcmp(myname,"BToolkit")==0 ||
	strcmp(myname,"Blauncher")==0)
	{
		/* ensure that the DISPLAY environment variable
		 is set */
		DISPLAY=getenv("DISPLAY");
		if(DISPLAY==NULL)
		{
			strcpy(display,"DISPLAY=:0.0");
			putenv(display);
			printf("%s\n",display);
		}
		/* need to start X11?*/
		
		uname[0]='\0';
		pfile=popen("uname -s","r");
		fgets(uname,PATH_MAX,pfile);
		pclose(pfile);
		
		if(strstr(uname,"Darwin")!=NULL)
		{
			returnValue=system("xprop -root -len 1 > /dev/null");
			if(returnValue==127)
			{
				system("/usr/bin/osascript <<EOF\ntell app \"System Events\"\ndisplay dialog \"X server?\"\nend tell\nEOF\n");
				exit(1);
			}
			if(returnValue==1)
			{
				system("/usr/bin/osascript -e \'tell app \"System Events\"\ndisplay dialog \"Starting X11\" with title \"BToolkit\" with icon note buttons {\"Ok\"} giving up after 5\nend tell\' > /dev/null &");
				/*printf("open $BKIT/start.x11app\n",display);*/
				system("open $BKIT/start.x11app");
				sleep(5);
			}
		}
	
		/* invoke the toolkit */
		/* MAC OS */
		#ifdef MAC_VERSION
		/*
		RunApplicationEventLoop();
		*/
		EventRef theEvent;
		EventTargetRef theTarget;
 
		theTarget = GetEventDispatcherTarget();
 		/*
    		while  (ReceiveNextEvent(0, NULL,kEventDurationForever,true, &theEvent)== noErr)
        	{
           	 SendEventToEventTarget (theEvent, theTarget);
           	 ReleaseEvent(theEvent);
		 
        	}
		*/
		system("$BKIT/BToolkit &");
		/* clean up
		system("kill -9 `lsof -a -tc BMotif -u $USER`");
		system("kill -9 `lsof -a -tc BSession -u $USER`");
		system("kill -9 `lsof -a -tc bplatform -u $USER`");
		*/
		#else
		system("$BKIT/BToolkit");
		#endif
	}
	else
	{
		strcpy(commandlineargs,"$BKIT/");
		strcat(commandlineargs,myname);
		strcat(commandlineargs," ");
		/*
		invoke whatever name is given
		along with the arguments
		*/
		for(i=1;i<argc;i++)
		{
			strcat(commandlineargs,"\'");
			strcat(commandlineargs,argv[i]);
			strcat(commandlineargs,"\'");
			if(i+1<argc)
			{
				strcat(commandlineargs," ");
			}
			
		}
		system(commandlineargs);
	}
}
