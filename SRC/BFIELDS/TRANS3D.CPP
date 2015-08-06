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

//------------------------------------------------------------------------------
//Filename       trans3d.cpp
//System         
//Author         Robert Slater
//Date           Mon 1 Apr 1996
//Description    Dictionary and 3dstudio translation
//------------------------------------------------------------------------------

#include	"Trans3d.h"

point	*pointroot = NULL;
point	*nextpoint = NULL;


//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		checktoken
//Author		Robert Slater
//Date			Tue 30 Jan 1996
//
//Description	Informs whether the required tokencode has been found,
//				with regards to the current item of text.
//				If true, it returns the next item of text.	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
static	Bool	Trans3d::checktoken(file	ifile, string text, TokenCode requiredcode)
{
	TokenName	*tokenname;
	
	if (	TokenSpell::testspelling(text,tokenname)
		&& (tokenname->tokencode == requiredcode)	)
	{
		text = TokenSpell::getword(ifile);
		return(TRUE);
	}
	else
		return(FALSE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		isnumeric
//Author		Robert Slater
//Date			Tue 30 Jan 1996
//
//Description	Checks if text is a number, and returns sign
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
static	Bool	Trans3d::isnumeric(string numtext, char &sign)
{
	char	compchar;

	compchar = numtext[0];
	sign = '+';

	if (((compchar >= '0') && (compchar <= '9')) || (compchar == '-'))
	{
		// Could be a number...

		if (compchar == '-')
		{
			// Could be a negative number...

			compchar = *(++numtext);

			if (!((compchar >= '0') &&( compchar <= '9')))
				EmitSysErr("Expecting digit after '-', but found %s",numtext);
			else
			{
				sign = '-';
				return(TRUE);
			}
		}
		else
			return(TRUE);
	}
	elser
		return(FALSE);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		texttoint
//Author		Robert Slater
//Date			Tue 30 Jan 1996
//
//Description	Converts text to an integer
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
static	int		Trans3d::texttoint(string text)
{
	char		compchar, sign;
	int			places, count, coreno, fstdec;
	char		temp[80];


	compchar = text[0];
	places = 0;
	count = 0;
	fstdec = 0;
	coreno = 0;

	if (isnumeric(text,sign))
	{
		if (sign == '-')
			compchar = *++text;

		while (compchar && (places == 0))
		{
			if (compchar == '.')
			{
				places = count;
				fstdec = *++text-'0';
			}
			else
			{
				temp[count] = compchar;
				count = count + 1;
				compchar = *++text;
			}
		}

		temp[count] = NULL;

		coreno = atoi(temp);

		// Round the number...

		if ((places > 0) && (fstdec >= 5))
			coreno = coreno + 1;

		// Adjust according to sign...

		if (sign == '-')
		{
			coreno = 0 - coreno;
		}
	}
	else
		EmitSysErr("Failed to convert to integer : %s", text);

		
	return(coreno);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		striptilltoken
//Author		Robert Slater
//Date			Thu 1 Feb 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
static	string	Trans3d::striptilltoken(file	ifile, TokenCode requiredcode)
{
	char	*text;

	text = TokenSpell::getword(ifile);

	while (!checktoken(ifile,text,requiredcode))
		text = TokenSpell::getword(ifile);

	return(text);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		pullvertex
//Author		Robert Slater
//Date			Tue 30 Jan 1996
//
//Description	Extracts a single line of vertex points
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
static	void	Trans3d::pullvertex(file	ifile, int &x, int &y, int &z)
{
	char		*text;
	char		sign;

	// Default cock-up values...

	x = 0; y = 0; z = 0;

	text = striptilltoken(ifile,T_vertex);	

	Assert (isnumeric(text,sign));
	{
		text = TokenSpell::getword(ifile);

		Assert (text[0] == ':');
		{
			// Get data...

			text = TokenSpell::getword(ifile);

			Assert (	checktoken(ifile,text,T_x)
					&&	(text[0] == ':')	   		);
				x = texttoint(TokenSpell::getword(ifile));

			text = TokenSpell::getword(ifile);

			Assert (	checktoken(ifile,text,T_y)
					&&	(text[0] == ':')		   	);
				y = texttoint(TokenSpell::getword(ifile));

			text = TokenSpell::getword(ifile);

			Assert (	checktoken(ifile,text,T_z)
					&&	(text[0] == ':')		 	);
				z = texttoint(TokenSpell::getword(ifile));

		}
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		pullfaceline
//Author		Robert Slater
//Date			Tue 30 Jan 1996
//
//Description	Extracts a single line of face information
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
static	string	Trans3d::pullfaceline(file	ifile, int &a, int &b, int &c)
{
	char		*text;
	string		material;
	char		*temp;
	char		sign;
	int			count;
	char		charcopy;
	Bool		stop;

	// Default cock-up values...

	a = -1; b = -1; c = -1;
	material = NULL;

	text = striptilltoken(ifile,T_face);

	Assert (isnumeric(text,sign));
	{
		text = TokenSpell::getword(ifile);

		Assert (text[0] == ':');
		{
			text = TokenSpell::getword(ifile);

			Assert (	checktoken(ifile,text,T_a)
					&&	(text[0] == ':')		  	);
			   	a = texttoint(TokenSpell::getword(ifile));

			text = TokenSpell::getword(ifile);

			Assert (	checktoken(ifile,text,T_b)
					&&	(text[0] == ':')		 	);
				b = texttoint(TokenSpell::getword(ifile));

			text = TokenSpell::getword(ifile);

			Assert (	checktoken(ifile,text,T_c)
					&&	(text[0] == ':')		  	);
				c = texttoint(TokenSpell::getword(ifile));	 

			text = TokenSpell::getword(ifile);

			while (!checktoken(ifile,text,T_mtl))
				text = TokenSpell::getword(ifile);

			if (text[0] == ':')
			{
				material = temp = TokenSpell::getword(ifile);
			
				// Remove quotes & full stops...

				count = 0;
				stop = FALSE;

				charcopy = temp[0];
				if (*temp=='"')
					material = ++temp;
				while (*temp!=0 && *temp!='"' && *temp!='.') temp++;
				*temp=0;
								
				if (strcmp(material,"Default") == 0)
					return(NULL);

			}
			else
				EmitSysErr("Material description not found!");

		}
	}

	return(material);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		pullvertices
//Author		Robert Slater
//Date			Wed 31 Jan 1996
//
//Description	Creates a list of all the vertices
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
static	void	Trans3d::pullvertices(file	ifile, int noverts, Coordinates* &vertlist)
{
	int			count;
	int			x, y, z;

	vertlist = new Coordinates[noverts];	Assert(vertlist&&"memory!");

	
	// Clear header and garbage

	striptilltoken(ifile,T_vertex);

	// Loop through vertices and extract each vertex...

	for(count=0; count<noverts; count++)
	{
	    pullvertex(ifile,x,y,z);
		vertlist[count].x = x * 100;
		vertlist[count].y = z * 100;
		vertlist[count].z = y * 100;
	}
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		pullfaces
//Author		Robert Slater
//Date			Wed 31 Jan 1996
//
//Description	Creates a list of all the faces
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
static	string	Trans3d::pullfaces(file	ifile, int nofaces, Connections* &facelist)
{
	char		*text, *material;
	int			count;
	int			a, b, c;

	facelist = new Connections[nofaces];	Assert(facelist&&"memory!");

	
	// Clear header and garbage 

	striptilltoken(ifile,T_face);

	// Loop through face list and extract...

	text = pullfaceline(ifile,a,b,c);

	if (text)
	{
		material = new char[strlen(text)+1]; Assert(material&&"memory!");
		strcpy(material,text);
	}
	else
		material = NULL;

	facelist[0].a = a;
	facelist[0].b = b;
	facelist[0].c = c;

	for(count=1; count<nofaces; count++)
	{
		pullfaceline(ifile,a,b,c);

		facelist[count].a = a;
		facelist[count].b = b;
		facelist[count].c = c;
	}

	return(material);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		checkforroute
//Author		Robert Slater
//Date			Wed 31 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
static	Bool	Trans3d::checkforroute(Connections *facelist, int nofaces, int noverts)
{
	int			common, number, count;
	Bool		isroute;
	int			prev1, prev2;

	if (noverts == 3)
		return(TRUE);

	isroute = TRUE;

	for(count = 1; count < nofaces; count ++)
	{
		common = 0;

		number = facelist[count].a;

	   	if (	(number == facelist[count-1].a) 
			||	(number == facelist[count-1].b) 
			||	(number == facelist[count-1].c)	)
					common = common + 1;

		number = facelist[count].b;

	   	if (	(number == facelist[count-1].a) 
			||	(number == facelist[count-1].b) 
			||	(number == facelist[count-1].c)	)
					common = common + 2;

		number = facelist[count].c;

	   	if (	(number == facelist[count-1].a) 
			||	(number == facelist[count-1].b) 
			||	(number == facelist[count-1].c)	)
					common = common + 4;

		switch (common)
		{
		case 1:
		{
			// A is common. Do nothing, because it is in order
		}
		break;
		case 2:
		{
			// Rotate left if B is common
		
			prev1 = facelist[count].a;
			prev2 = facelist[count].c;
			
			facelist[count].a = facelist[count].b;
			facelist[count].b = prev2;
			facelist[count].c = prev1;
		}
		break;
		case 4:
		{
			// Rotate right	if C is common
			
			prev1 = facelist[count].b;
			prev2 = facelist[count].a;
			
			facelist[count].a = facelist[count].c;
			facelist[count].b = prev2;
			facelist[count].c = prev1;
		}
		break;
		default:
			isroute = FALSE;
		}
		
	}

	// Cater for Face0...

	if (isroute)
	{
		number = facelist[0].a;

		// Rotate left if A is common

	   	if (number == facelist[1].a)
		{
			prev1 = facelist[0].a;
			prev2 = facelist[0].c;
			
			facelist[0].a = facelist[0].b;
			facelist[0].b = prev2;
			facelist[0].c = prev1;
		}

		number = facelist[0].b;

		// Rotate right	if B is common
	   
		if (number == facelist[1].a)
		{
			prev1 = facelist[0].b;
			prev2 = facelist[0].a;
			
			facelist[0].a = facelist[0].c;
			facelist[0].b = prev2;
			facelist[0].c = prev1;
		}

	}

	return(isroute);

}
	
//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		get3dsentry
//Author		Robert Slater
//Date			Tue 30 Jan 1996
//
//Description	
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
static	void	Trans3d::get3dsentry(file	ifile)
{	
	char		name[80], *nexttext, letter;
	char		nvertstext[80], nfacestext[80];
	Bool		finished, route;
	int			noverts, nofaces, vertno;
	Coordinates	*vertex;
	Connections	*face;
	char		tag[4];
	char		routename[80];
	char		*material;


	strcpy(name,TokenSpell::getword(ifile));

	finished = FALSE;

	while(!finished)
	{
		nexttext = TokenSpell::getword(ifile);

		if (	checktoken(ifile,nexttext,T_vertex)
			&&	(nexttext[0] == ':')				)
					strcpy(nvertstext,TokenSpell::getword(ifile));

		if (	checktoken(ifile,nexttext,T_face)
			&&	(nexttext[0] == ':')				)
		{
			strcpy(nfacestext,TokenSpell::getword(ifile));
			finished = TRUE;
		}
	}

	noverts = texttoint(nvertstext);
	nofaces = texttoint(nfacestext);

	if (noverts <= 30)
	{
		pullvertices(ifile,noverts,vertex);
		material = pullfaces(ifile,nofaces,face);

		route = checkforroute(face,nofaces,noverts);

		if (route)
		{
			for(vertno = 0; vertno < noverts; vertno++)
			{
				letter = (char)('A' + vertno);

				tag[0] = '_';
				tag[1] = letter;
				tag[2] = 0;

				strcpy(routename,name);
				strcat(routename,tag);

 				add3dsentry(routename, vertex[vertno].x, vertex[vertno].y,
							vertex[vertno].z, NULL);
			}
		}
		else
 			add3dsentry(name, vertex[0].x, vertex[0].y, vertex[0].z, material);
																
		delete []material;										
		delete []face;
		delete []vertex;
	}

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		makepointlist
//Author		Robert Slater
//Date			Tue 2 Apr 1996
//
//Description	Constructs a linked list of 3dstudio vertices.
//				If it is a route then the points are linked,
//				otherwise they are stored as single points.
//
//Inputs		
//
//Returns	
//
//------------------------------------------------------------------------------
static	void	Trans3d::makepointlist(file	ifile)
{	
	char		name[80], *nexttext, letter;
	char		nvertstext[80], nfacestext[80];
	Bool		finished, route;
	int			noverts, nofaces, vertno;
	Coordinates	*vertex;
	Connections	*face;
	char		*material;
	point		*thispoint;
	int			number;


	strcpy(name,TokenSpell::getword(ifile));

	finished = FALSE;

	while(!finished)
	{
		nexttext = TokenSpell::getword(ifile);

		if (	checktoken(ifile,nexttext,T_vertex)
			&&	(nexttext[0] == ':')				)
					strcpy(nvertstext,TokenSpell::getword(ifile));

		if (	checktoken(ifile,nexttext,T_face)
			&&	(nexttext[0] == ':')				)
		{
			strcpy(nfacestext,TokenSpell::getword(ifile));
			finished = TRUE;
		}
	}

	noverts = texttoint(nvertstext);
	nofaces = texttoint(nfacestext);

	if (noverts > 0)
	{
		pullvertices(ifile,noverts,vertex);
		material = pullfaces(ifile,nofaces,face);
		route = checkforroute(face,nofaces,noverts);

		for (vertno = 0; vertno < noverts; vertno++)
		{
			thispoint = (point*)	new point;

			thispoint->x = (vertex[vertno].x / 512) * 100;
			thispoint->y = (vertex[vertno].y / 512) * 100;

			thispoint->adj1 = NULL;
			thispoint->adj2 = NULL;

			if (pointroot)
			{
				nextpoint->next = thispoint;
				nextpoint = thispoint;
			}
			else
				pointroot = nextpoint = thispoint;
		}

		nextpoint->next = NULL;

		if (route)
		{
			nextpoint = pointroot;

			do
			{
				thispoint = nextpoint;

				nextpoint = thispoint->next;

				thispoint->adj1 = nextpoint;

				if (nextpoint)
					nextpoint->adj2 = thispoint;

			}
			while (nextpoint);

			nextpoint = thispoint;
		}

		delete []material;										
		delete []face;
		delete []vertex;
	}

}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//
//Procedure		bfieldstudiointerpreter
//Author		Rob Slater
//Date			Mon 29 Jan 1996
//
//Description	Converts a 3d studio file to a bfield text tree
//
//Inputs		The 3d studio ascii file
//
//Returns
//
//------------------------------------------------------------------------------
static	void	Trans3d::bfieldstudiointerpreter(file	ifile)
{
	char		*nexttext;

	while (TokenSpell::stripwhite(ifile))
	{
		nexttext = TokenSpell::getword(ifile);

		if (	checktoken(ifile,nexttext,T_named)
			&&	checktoken(ifile,nexttext,T_object)	)
		{
			if (nexttext[0] != ':')
				EmitSysErr("':' was expected; not a standard 3d Studio file!");

			get3dsentry(ifile);

 		}
	}

	fclose(ifile);
}

//컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴
//Procedure		pointliststudiointerpreter
//Author		Robert Slater
//Date			Wed 3 Apr 1996
//
//Description	Converts a 3d studio file to a world coordinate point list
//
//Inputs		The 3d studio ascii file
//
//Returns	
//
//------------------------------------------------------------------------------
static	point*	Trans3d::pointliststudiointerpreter(file	ifile)
{
	char		*nexttext;

	while (TokenSpell::stripwhite(ifile))
	{
		nexttext = TokenSpell::getword(ifile);

		if (	checktoken(ifile,nexttext,T_named)
			&&	checktoken(ifile,nexttext,T_object)	)
		{
			if (nexttext[0] != ':')
				EmitSysErr("':' was expected; not a standard 3d Studio file!");

			makepointlist(ifile);
 		}
	}

	fclose(ifile);

	return(pointroot);
}

