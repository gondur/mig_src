//------------------------------------------------------------------------------
//Filename       forms.h
//System         Flying Corp
//Author         Dave Whiteside
//Date           Thu 5 Oct 1995
//Description    Forms.asm replacement FORMS IS NOW PART OF THE UISheet CLASS
//				 It uses STATIC variables for various tricks
//------------------------------------------------------------------------------
//DeadCode JIM 15Nov95 #ifndef	FORMS_Included
//DeadCode JIM 15Nov95 #define	FORMS_Included
//DeadCode JIM 15Nov95 
//DeadCode JIM 15Nov95 #define	DEFAULT_FORMS 0
//DeadCode JIM 15Nov95 
//DeadCode JIM 15Nov95 
//DeadCode JIM 15Nov95 //------------------------------------------------------------------------------
//DeadCode JIM 15Nov95 //Author		Dave Whiteside
//DeadCode JIM 15Nov95 //Date			Thu 19 Oct 1995
//DeadCode JIM 15Nov95 //Modified	
//DeadCode JIM 15Nov95 //
//DeadCode JIM 15Nov95 //Description	
//DeadCode JIM 15Nov95 //
//DeadCode JIM 15Nov95 //Inputs		
//DeadCode JIM 15Nov95 //------------------------------------------------------------------------------
//DeadCode JIM 15Nov95 class	Forms
//DeadCode JIM 15Nov95 	{
//DeadCode JIM 15Nov95 	public:
//DeadCode JIM 15Nov95 			Forms::Forms();
//DeadCode JIM 15Nov95 			Forms::~Forms();
//DeadCode JIM 15Nov95 			Forms::DrawSheet(ScreenRecord	*screen);
//DeadCode JIM 15Nov95 	UWord	Forms::HandleInput();
//DeadCode JIM 15Nov95 
//DeadCode JIM 15Nov95 	UWord	Forms::Bye();
//DeadCode JIM 15Nov95  
//DeadCode JIM 15Nov95 	protected:
//DeadCode JIM 15Nov95 
//DeadCode JIM 15Nov95 
//DeadCode JIM 15Nov95 	private:
//DeadCode JIM 15Nov95 		FileNum		LastPic;
//DeadCode JIM 15Nov95 		UIControl*	Start;
//DeadCode JIM 15Nov95 
//DeadCode JIM 15Nov95 		UWord		TimeOut;
//DeadCode JIM 15Nov95 
//DeadCode JIM 15Nov95 	};
//DeadCode JIM 15Nov95 
//DeadCode JIM 15Nov95 
//DeadCode JIM 15Nov95 
//DeadCode JIM 15Nov95 
//DeadCode JIM 15Nov95 #endif
