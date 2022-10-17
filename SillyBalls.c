#include <Types.h>
#include <Memory.h>
#include <Quickdraw.h>
#include <Fonts.h>
#include <Events.h>
#include <Menus.h>
#include <Windows.h>
#include <TextEdit.h>
#include <Dialogs.h>
#include <Sound.h>
#include <ToolUtils.h>
#include <Processes.h>

/* Constants */
#define BallWidth		20
#define BallHeight		20
#define BobSize			8		/* Size of text in each ball */

/* Globals */
Rect		windRect;

/* The qd global has been removed from the libraries */
QDGlobals qd;


/* Prototypes */
void Initialize(void);
void NewBall(void);

/* 
**	Main body of program SillyBalls
*/
void main(void)
{
	Initialize();
	
	do {
		NewBall();
	} while (!Button());
	
}

/* 
**	Initialize everything for the program, make sure we can run
*/
void Initialize(void)
{
	WindowPtr	mainPtr = NULL;
	OSErr		error = noErr;
	SysEnvRec	theWorld;
    Handle      menuBar = NULL;
	
	/*
	**	Test the computer to be sure we can do color.  
	**	If not we would crash, which would be bad.  
	**	If we can�t run, just beep and exit.
	*/
	error = SysEnvirons(1, &theWorld);
	if (theWorld.hasColorQD == false) {
		SysBeep(50);
		ExitToShell();					/* If no color QD, we must leave. */
	}
	
	/* Initialize all the needed managers. */
	InitGraf(&qd.thePort);
	InitFonts();
	InitWindows();
	InitMenus();
	TEInit();
	InitDialogs(nil);
	InitCursor();

	/*
	**	To make the Random sequences truly random, we need to make the seed start
	**	at a different number.  An easy way to do this is to put the current time
	**	and date into the seed.  Since it is always incrementing the starting seed
	**	will always be different.  Don�t for each call of Random, or the sequence
	**	will no longer be random.  Only needed once, here in the init.
	*/
	GetDateTime((unsigned long*) &qd.randSeed);

    menuBar = GetNewMBar(128);
    SetMenuBar(menuBar);
    DisposeHandle(menuBar);
    AppendResMenu(GetMenuHandle(128), 'DRVR');
    DrawMenuBar();

    /*
    **	Make a new window for drawing in, and it must be a color window.
    **	The window is full screen size, made smaller to make it more visible.
    */
	windRect = qd.screenBits.bounds;
	InsetRect(&windRect, 50, 50);
	mainPtr = NewCWindow(nil, &windRect, "\pBo3b Land", true, documentProc, 
						(WindowPtr) -1, false, 0);
		
	SetPort(mainPtr);						/* set window to current graf port */
	TextSize(BobSize);						/* smaller font for drawing. */
}


/* 
**	NewBall: make another ball in the window at a random location and color.
*/
void NewBall(void)
{
	RGBColor	ballColor;
	Rect		ballRect;
	long int	newLeft,
				newTop;
	
	/* 
	**	Make a random new color for the ball.
	*/
	ballColor.red   = Random();
	ballColor.green = Random();
	ballColor.blue  = Random();
	
	/* 
	**	Set that color as the new color to use in drawing.
	*/
	RGBForeColor (&ballColor);

	/*	
	**	Make a Random new location for the ball, that is normalized to the window size.  
	**	This makes the Integer from Random into a number that is 0..windRect.bottom
	**	and 0..windRect.right.  They are normalized so that we don't spend most of our
	**	time drawing in places outside of the window.
	*/
	newTop = Random();	newLeft = Random();
	newTop = ((newTop+32767) * windRect.bottom)/65536;
	newLeft = ((newLeft+32767) * windRect.right)/65536;
	SetRect(&ballRect, newLeft, newTop, newLeft+BallWidth, newTop+BallHeight);
	
	/*
	**	Move pen to the new location, and paint the colored ball.
	*/
	MoveTo(newLeft, newTop);
	PaintOval (&ballRect);
	
	/*
	**	Move the pen to the middle of the new ball position, for the text
	*/
	MoveTo(ballRect.left + BallWidth/2 - BobSize, 
		ballRect.top + BallHeight/2 + BobSize/2 -1);
	
	/*	
	**	Invert the color and draw the text there.  This won�t look quite right in 1 bit
	**	mode, since the foreground and background colors will be the same.
	**	Color QuickDraw special cases this to not invert the color, to avoid
	**	invisible drawing.
	*/
	InvertColor(&ballColor); 
	RGBForeColor(&ballColor);
	DrawString("\pBob");
}

