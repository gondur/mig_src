#if !defined(MESSAGES_H_INCLUDED)
#define MESSAGES_H_INCLUDED

// these messages are primarily used for communicating between
// ActiveX controls and the main application or for any situation
// where you are not certain of the type of the target window
// change the numbers at will if there is a version conflict

#define WM_GETARTWORK (WM_USER + 1)
#define WM_GETXYOFFSET (WM_USER + 2)
#define WM_GETGLOBALFONT (WM_USER + 3)
#define WM_GETFILE (WM_USER + 4)
#define WM_RELEASELASTFILE (WM_USER + 5)
#define WM_SELECTTAB (WM_USER + 6)
#define WM_CANACCEPTDROP (WM_USER + 7)
#define WM_DROPPEDON (WM_USER + 8)
#define WM_GETX2FLAG (WM_USER + 9)
#define WM_GETOFFSCREENDC (WM_USER + 10)
#define WM_GETHINTBOX (WM_USER + 11)
#define WM_PLAYSOUND (WM_USER + 12)
#define WM_GETCOMBOLISTBOX (WM_USER + 13)
#define WM_GETCOMBODIALOG (WM_USER + 14)
#define WM_ACTIVEXSCROLL (WM_USER + 15)
#define WM_GETSTRING (WM_USER + 16)

#endif
