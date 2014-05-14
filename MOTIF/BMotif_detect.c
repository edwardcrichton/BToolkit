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
void canonical(path)
char* path;
{
/* Resolves symbolic links. Overwrites the contents of path. path should have size PATH_MAX. */
	char buf[PATH_MAX];
	buf[0]='\0';

	if (realpath(path, buf))
	{
		path[0]='\0';
		strcat(path,buf);
	}
}

char* detectApplications(char* known[], size_t total)
{
	size_t i;
	char which[PATH_MAX];
	char which_output[PATH_MAX];
	char which_output_canonical[PATH_MAX];
	FILE* pfile;
	char* applicationList;
	char canonicalList[PATH_MAX*30];
	
	printf("detectApplications\n");
	
	applicationList= (char *) malloc(PATH_MAX*total);
	applicationList[0]='\0';
	canonicalList[0]='\0';
	
	for(i=0;i<total;i++)
	{
		if(known[i] != NULL)
		{
			which[0]='\0';
			which_output[0]='\0';
			which_output_canonical[0]='\0';
			strcat(which,"which ");
			strcat(which,known[i]);
			pfile=popen(which,"r");
			fgets(which_output,PATH_MAX,pfile);
			pclose(pfile);
			
			if(which_output[0]!='/')
			{
				/* dont want any other rubbish - just paths */
				continue;
			}
			
			while( strlen(which_output) > 0 && which_output[strlen(which_output)-1]=='\n')
			{
				which_output[strlen(which_output)-1]='\0';
			}
			
			strcat(which_output_canonical,which_output);
			canonical(which_output_canonical);
			
			if(strstr(canonicalList,which_output_canonical)==NULL)
			{
				if(strlen(canonicalList)>0)
				{
					if(canonicalList[strlen(canonicalList)-1] != ':' )
					strcat(canonicalList,":");
				}
				strcat(canonicalList,which_output_canonical);
			
				if(strstr(applicationList,which_output)==NULL)
				{
					if(strlen(applicationList)>0)
					{
						if(applicationList[strlen(applicationList)-1] != ':' )
						strcat(applicationList,":");
					}
					strcat(applicationList,which_output);
				}
			}
		}
	}
	if(applicationList!=NULL)
	{
		if(strlen(applicationList)==0)
		{
			free(applicationList);
			applicationList=NULL;
		}
	}
	
	printf("/detectApplications\n");
	
	return applicationList;
}

/*
   Make a colon separated list of editors from $VISUAL, $XEDITOR and a
   list of known editors.
*/

char* detectEditors()
{
	char* known[]=
	{
                NULL, /* placeholder for $VISUAL */
                NULL, /* placeholder for $XEDITOR */
		"nedit",
		"gedit",
		"xedit",
		"textedit",
		"/Applications/TextWrangler.app/Contents/MacOS/TextWrangler",
		"/Applications/TextEdit.app/Contents/MacOS/TextEdit",
		"xemacs",
		"emacs",
		"/Applications/Emacs.app/Contents/MacOS/Emacs",
		"kedit",
		"gvim",
		"nano",
		"pico",
		"vi"
	};
        size_t total=sizeof(known)/sizeof(known[0]);
        known[0]=getenv("VISUAL");
        known[1]=getenv("XEDITOR");
	return detectApplications(known,total);
}

char* detectBrowsers()
{
	char* known[]=
	{
		"firefox",
		"google-chrome",
		"/Applications/Firefox.app/Contents/MacOS/firefox",
		"/Applications/Safari.app/Contents/MacOS/Safari",
		"/Applications/Google Chrome.app/Contents/MacOS/Google Chrome",
		"netscape",
		"w3m",
		"konqueror",
		"opera",
		"elinks",
		"links",
		"lynx",
		"yelp"
	};
	size_t total=sizeof(known)/sizeof(known[0]);
	return detectApplications(known,total);	
}

char* getCommandExecutableName(char* commandline)
{
	/* removes the path from the front and parameters from the end
	* and returns executable name
	* the caller must free the string pointer.
	*/
	
	char* nameStart;
	char* nameEnd;
	char* name;
	int length;
	
	nameStart=commandline;
	nameEnd=commandline;
	
	for(;;)
	{
		if(nameEnd[0]<=32)
		{
			nameEnd--;
			break;
		}
		if(nameEnd[0]=='/')
		{
			nameEnd=nameEnd+1;
			nameStart=nameEnd;
			continue;
		}
		nameEnd=nameEnd+1;
	}
	
	length=(nameEnd-nameStart)+1;
	
	name=(char *)malloc((size_t) (length+1));
	memcpy(name,nameStart,(size_t) length);
	name[length]='\0';
	
	return name;
}

char* escapeQuotesAndBackslashes(char* arguments)
{
	char* result;
	int length;
	int argslength;
	int i;
	int j;
	
	argslength=strlen(arguments);
	
	length=0;
	
	for(i=0;i<argslength;i++)
	{
		length++;
		if(arguments[i]=='\\' || arguments[i]=='\"')
		{
			length++;
		}
	}
	
	result=(char *)malloc((size_t) (length+1));
	
	j=0;
	for(i=0;i<argslength;i++)
	{
		if(arguments[i]=='\\' || arguments[i]=='\"')
		{
			result[j]='\\';
			j++;
		}
		result[j]=arguments[i];
		j++;
	}
	result[length]='\0';
	return result;
}

char* getApplicationCommandLineTemplate(char* cmd,char* known[], char* xterm[], int total)
{
	int i;
	int match;
	char* name;
	char localResult[PATH_MAX*4];
	int isXterm;
	char* result;
	char* escaped;
	
	match=-1;
	
	name=getCommandExecutableName(cmd);
	
	for(i=0;i<total;i=i+1)
	{
		if(strcmp(name,known[i])==0)
		{
			match=i;
			break;
		}
	}
	
	free(name);
	
	localResult[0]='\0';
	
	if(match!=-1)
	{

		isXterm=0;
		if(strcmp(xterm[match],"y")==0)
		{
			isXterm=1;
		}
		if(isXterm)
		{
			strcat(localResult,"xterm -e \"");
		}
		
		if(isXterm)
		{
			escaped=escapeQuotesAndBackslashes(cmd);
			strcat(localResult,escaped);
			free(escaped);
		}
		else
		{
			strcat(localResult,cmd);
		}
		
		if(strcmp(known[match],"netscape")==0)
		{
			strcat(localResult," -remote \"openFile(%s)\"");
		}
		else
		{
			strcat(localResult," ");
			if(isXterm)
			{
				strcat(localResult,"\\\"");
			}
			else
			{
				strcat(localResult,"\"");
			}
			strcat(localResult,"%s");
			if(isXterm)
			{
				strcat(localResult,"\\\"");
			}
			else
			{
				strcat(localResult,"\"");
			}
		}
		if(isXterm)
		{
			strcat(localResult,"\"");
		}
	}
	else
	{
		strcat(localResult,cmd);
		strcat(localResult," \"%s\"");
	}
	
	result=(char *)malloc((size_t) (strlen(localResult)+1));
	result[0]='\0';
	strcat(result,localResult);
	
	return result;
}

/*
   Will take the cmd as name / path / path+arguments of an application
   and the filename and will return the command line, including wrapping
   text only browsers in an xterm and escaping any \ or " in parameters given.
*/

char* getApplicationCommandLine(char* application,char* filename, char* known[], char* xterm[], int total)
{
	char* template;
	char* result;
	int totalSize;
	
	template=getApplicationCommandLineTemplate(application,known,xterm,total);
	
	totalSize=strlen(template)+strlen(filename);
	result=(char *)malloc((size_t) (totalSize+1));
	result[0]='\0';
	
	sprintf(result,template,filename);
	
	free(template);
	
	return result;
}

char* getBrowserCommandLine(char* application,char* filename)
{
	char* known[]=
	{
		"konqueror", "netscape",
		"firefox", "/Applications/Firefox.app/Contents/MacOS/firefox","/Applications/Safari.app/Contents/MacOS/Safari",
		"elinks", "links", "opera", "yelp", "lynx", "w3m"
	};
	char* xterm[]=
	{
		"n"        , "n"       ,
		"n"      , "n"        , "n"       ,
		"y"     , "y"    , "n"    , "n"   , "y"   , "y"
	};
	int total=11;
	return getApplicationCommandLine(application,filename, known, xterm, total);
}

char* getEditorCommandLine(char* editor,char* filename)
{
	char* known[]=
	{
		"nedit", "xedit", "textedit" , "/Applications/TextEdit.app/Contents/MacOS/TextEdit",
		"xemacs", "emacs" ,"/Applications/Emacs.app/Contents/MacOS/Emacs", "gvim", "kedit",
		"vi", "nano", "pico"
	};
	char* xterm[]=
	{
		"n"    , "n"    , "n"        , "n",
		"n"    , "n"     , "n"  , "n"   , "n",
		"y" , "y"   , "y"
	};
	int total=12;
	return getApplicationCommandLine(editor,filename,known,xterm,total);
}


void getEditorOptions()
{
	/* fills the global editors[] array with detected editors */
	/* if any of the strings are not null then they are freed */
	/* and set to null */
	
	char *BEDITORS;
	char *end;
	char *pos;
	char *current;
	int at;
	int pathLength;
	char buf[250];
	int i;
	
	for(i=0;i<editorsCount;i++)
	{
		if(editors[i]!=NULL)
		{
			free(editors[i]);
			editors[i]=NULL;
		}
	}
	
	at=0;
	BEDITORS=detectEditors();
	
	if(BEDITORS==NULL)
	{
		if(at<editorsCount)
		{
			if ( strcmp ( platform, "Solaris" ) == 0 )
			{
				editors[at]=(char *)malloc((size_t) 9);
				editors[at][0]='\0';
				strcat(editors[at],"textedit");
			}
			else
			{
				editors[at]=(char *)malloc((size_t) 6);
				editors[at][0]='\0';
				strcat(editors[at],"xedit");
			}
			at=at+1;
		}
		return;
	}
	
	end=BEDITORS+strlen(BEDITORS);
	current=BEDITORS;
	
	while(at<editorsCount && current<end)
	{
		pos=strstr(current,":");

		if(pos==NULL)
		{
			pathLength=(int) (end-current);
		}
		else
		{
			pathLength=(int) (pos-current);
		}
		if(pathLength>0)
		{
			editors[at]=(char *)malloc((size_t) (pathLength+1));
			memcpy(editors[at],current,(size_t) pathLength);
			editors[at][pathLength]='\0';
			at++;
		}
		current=current+pathLength+1;
	}
	
	free( BEDITORS );
}

void getEditorOption(char* buf)
{
	/* looks up the default editor. Picks the first one */
	
	getEditorOptions();
	buf[0]='\0';
	strcat(buf,editors[0]);
}

void getBrowserOptions()
{
	/* fills the global browsers[] array with detected browsers */
	/* if any of the strings are not null then they are freed */
	/* and set to null */
	
	char *BBROWSERS;
	char *end;
	char *pos;
	char *current;
	int at;
	int pathLength;
	char buf[250];
	
	int i;
	
	for(i=0;i<browsersCount;i++)
	{
		if(browsers[i]!=NULL)
		{
			free(browsers[i]);
			browsers[i]=NULL;
		}
	}
	
	at=0;
	BBROWSERS=detectBrowsers();
	
	if(BBROWSERS==NULL)
	{
		if(at<browsersCount)
		{
			browsers[at]=(char *)malloc((size_t) 8);
			browsers[at][0]='\0';
			strcat(browsers[at],"firefox");
			at=at+1;
		}
		return;
	}
	
	end=BBROWSERS+strlen(BBROWSERS);
	current=BBROWSERS;
	
	while(at<browsersCount && current<end)
	{
		pos=strstr(current,":");
		if(pos==NULL)
		{
			pathLength=(int) (end-current);
		}
		else
		{
			pathLength=(int) (pos-current);
		}
		if(pathLength>0)
		{
			browsers[at]=(char *)malloc((size_t) (pathLength+1));
			memcpy(browsers[at],current,(size_t) pathLength);
			browsers[at][pathLength]='\0';
			at++;
		}
		current=current+pathLength+1;
	}
	free( BBROWSERS );
}

void getBrowserOption(char* buf)
{
	/* looks up the default browser. Picks the first one */
	getBrowserOptions();
	buf[0]='\0';
	strcat(buf,browsers[0]);
}

/**************************************************
          /detect environment
***************************************************/
