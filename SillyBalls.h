#define kMinSize	23				/* application's minimum size (in K) */
#define kPrefSize	35				/* application's preferred size (in K) */

#define	rMenuBar	128				/* application's menu bar */
#define	rAboutAlert	128				/* about alert */
#define	rUserAlert	129				/* error user alert */
#define	rWindow		128				/* application's window */

/* The following constants are used to identify menus and their items. The menu IDs
   have an "m" prefix and the item numbers within each menu have an "i" prefix. */

#define	mApple					128		/* Apple menu */
#define	iAbout					1

#define	mFile					129		/* File menu */
#define	iNew					1
#define	iClose					4
#define	iQuit					12

#define	mEdit					130		/* Edit menu */
#define	iUndo					1
#define	iCut					3
#define	iCopy					4
#define	iPaste					5
#define	iClear					6

/* these #defines are used to set enable/disable flags of a menu */

#define AllItems	0b1111111111111111111111111111111	/* 31 flags */
#define NoItems		0b0000000000000000000000000000000
#define MenuItem1	0b0000000000000000000000000000001
#define MenuItem2	0b0000000000000000000000000000010
#define MenuItem3	0b0000000000000000000000000000100
#define MenuItem4	0b0000000000000000000000000001000
#define MenuItem5	0b0000000000000000000000000010000
#define MenuItem6	0b0000000000000000000000000100000
#define MenuItem7	0b0000000000000000000000001000000
#define MenuItem8	0b0000000000000000000000010000000
#define MenuItem9	0b0000000000000000000000100000000
#define MenuItem10	0b0000000000000000000001000000000
#define MenuItem11	0b0000000000000000000010000000000
#define MenuItem12	0b0000000000000000000100000000000
