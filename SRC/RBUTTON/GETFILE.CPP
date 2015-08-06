/*
	 MiG Alley
	 Copyright (C) 1998, 1999, 2000, 2001 Empire Interactive (Europe) Ltd,
	 677 High Road, North Finchley, London N12 0DA

	 Please see the document licence.doc for the full licence agreement

2. LICENCE
 2.1 	
 	Subject to the provisions of this Agreement we now grant to you the 
 	following rights in respect of the Source Code:
  2.1.1 
  	the non-exclusive right to Exploit  the Source Code and Executable 
  	Code on any medium; and 
  2.1.2 
  	the non-exclusive right to create and distribute Derivative Works.
 2.2 	
 	Subject to the provisions of this Agreement we now grant you the
	following rights in respect of the Object Code:
  2.2.1 
	the non-exclusive right to Exploit the Object Code on the same
	terms and conditions set out in clause 3, provided that any
	distribution is done so on the terms of this Agreement and is
	accompanied by the Source Code and Executable Code (as
	applicable).

3. GENERAL OBLIGATIONS
 3.1 
 	In consideration of the licence granted in clause 2.1 you now agree:
  3.1.1 
	that when you distribute the Source Code or Executable Code or
	any Derivative Works to Recipients you will also include the
	terms of this Agreement;
  3.1.2 
	that when you make the Source Code, Executable Code or any
	Derivative Works ("Materials") available to download, you will
	ensure that Recipients must accept the terms of this Agreement
	before being allowed to download such Materials;
  3.1.3 
	that by Exploiting the Source Code or Executable Code you may
	not impose any further restrictions on a Recipient's subsequent
	Exploitation of the Source Code or Executable Code other than
	those contained in the terms and conditions of this Agreement;
  3.1.4 
	not (and not to allow any third party) to profit or make any
	charge for the Source Code, or Executable Code, any
	Exploitation of the Source Code or Executable Code, or for any
	Derivative Works;
  3.1.5 
	not to place any restrictions on the operability of the Source 
	Code;
  3.1.6 
	to attach prominent notices to any Derivative Works stating
	that you have changed the Source Code or Executable Code and to
	include the details anddate of such change; and
  3.1.7 
  	not to Exploit the Source Code or Executable Code otherwise than
	as expressly permitted by  this Agreement.

questions about this file may be asked at http://www.simhq.com/
*/

#include "stdafx.h"

// this global function searches F_GRAFIX.G and returns the file
// number of a given file equate

int GetFileNum(const char* text)
{
	// ok first open F_GRAFIX.G which we'll assume is in
	// \mig\src\h
	FILE* fp;
	fp=fopen("\\mig\\src\\h\\F_GRAFIX.G","rb");
	if (fp==NULL) 
	{
		MessageBox(AfxGetMainWnd()->m_hWnd,"Cannot find \\mig\\src\\mfc\\f_grafix.g","ERROR",MB_OK);
		return -1;
	}
	// now parse it
	char c;
	int textlen=strlen(text);
	char buffer[255];
// first search for first letter of string...
	while (true)
	{
		while(true)
		{
			if(fread(&c,1,1,fp)==NULL) {fclose(fp);return 0;} // failed to find it
			if (c==text[0]) break;
		}
		buffer[0]=c;
		// now check if the rest of the string is after it
		if(fread((buffer+1),1,textlen,fp)<textlen-1) {fclose(fp);return 0;}
		if (buffer[textlen]=='\t') // prevents triggering on partial successes...
		{
			buffer[textlen]=NULL; // NULL terminate the buffer
			if (strcmp(buffer,text)==0)
				break;
		}
		fseek(fp,-textlen,SEEK_CUR); // failed so backup and carry on...
	}
	// ok we have a match...
	// so find the string
	// first skip over spaces...
	while(true)
	{
		if(fread(&c,1,1,fp)==NULL) {fclose(fp);return 0;} // so near yet so far...
		if (c!='\t') break;
	}
	// extract string...
	int x=0;
	while(true)
	{
		if (c==13)
		{
			buffer[x]=NULL;
			break;
		}
		if (c!='=' && c!=',')
		{
			buffer[x]=c;
			x++;
		}
		if(fread(&c,1,1,fp)==NULL) {fclose(fp);return 0;} // so near yet so far...
	}
	fclose(fp);
	return strtol(buffer,NULL,16); // success!!!!;
}

