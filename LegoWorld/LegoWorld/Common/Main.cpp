/*
 *		This Code Was Created By Brett Porter For NeHe Productions 2000
 *		Visit NeHe Productions At http://nehe.gamedev.net
 *		
 *		Visit Brett Porter's Web Page at
 *		http://www.geocities.com/brettporter/programming
 */

/*
 * This is the entry file of the project.
 * It contains some functions that communicate with the OS/OpenGL directly.
 */

#include "Global.h"
#include "..\UI\UIButtonManager.h"
#include "..\Lego\LegoManager.h"
#include "..\Utility\Utility.h"
#include "..\Utility\TSControl.h"

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glaux.lib")
#pragma comment(lib, "WINMM.LIB")

TSConsole				console;
UIButtonManager			gUIMgr;

float					yrot = 0.0f;
bool					pPressed = false;

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)					
{
	if (height == 0) {
		height = 1;
	}

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 1.0f, 1000.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

bool MousePicking(int mx, int my, bool putting = false)
{
	GLuint buffer[512];
	GLint hits;

	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	glSelectBuffer(512, buffer);

	glRenderMode(GL_SELECT);

	glInitNames();
	glPushName(0);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	gluPickMatrix((GLdouble) mx, (GLdouble)(viewport[3] - my), 2.0f, 2.0f, viewport);

	gluPerspective(45.0f, (GLfloat)(viewport[2] - viewport[0]) / (GLfloat)(viewport[3] - viewport[1]), 0.1f, 1000.0f);
	glMatrixMode(GL_MODELVIEW);
	LegoManager::Instance()->Update();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	hits = glRenderMode(GL_RENDER);

	if (hits > 0) {
		LegoManager::Instance()->ProcessHit(hits, buffer, putting);
		return true;
	}
//	printf("%d\n", hits);
	return false;
}

DWORD WINAPI MusicProc(LPVOID lpParameter)
{
	BOOL music = FALSE;
//	PlaySound("Hikari_to_Yami_no_Douwa.wav", NULL, music);

	return 0;
}

bool InitializeScene()
{
	HANDLE hThreadMusic = CreateThread(NULL, 0, MusicProc, NULL, 0, NULL);
	CloseHandle(hThreadMusic);
	LegoManager::Instance()->Initialize();
	gUIMgr.Initialize();

	return true;
}

bool InitializeGL()
{
	glShadeModel(GL_SMOOTH);
	glClearColor(0.6f, 0.4f, 0.9f, 0.5f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	if (!InitializeScene()) {
		return false;
	}

	return true;
}

bool RenderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gUIMgr.Update();
	glMatrixMode(GL_MODELVIEW);

	gluLookAt(
		LegoManager::Instance()->getCurrentEyePosition().getPositionX(), 
		LegoManager::Instance()->getCurrentEyePosition().getPositionY(), 
		LegoManager::Instance()->getCurrentEyePosition().getPositionZ(), 
		LegoManager::Instance()->getLookToPositionX(), 
		LegoManager::Instance()->getLookToPositionY(), 
		LegoManager::Instance()->getLookToPositionZ(), 
		0, 1, 0);

//	glPushMatrix();
//	glRotatef(yrot, 0.0f, 1.0f, 0.0f);
	LegoManager::Instance()->Update();

	yrot++;
	if (yrot > 360.0f) {
		yrot = 0.0f;
	}

//	glPopMatrix();

	return true;
}

bool UpdateScene()
{
	RenderScene();
	switch (LegoManager::Instance()->getGameStatus())
	{
	case eGameStatus::eNormal:
		{
			if (LegoManager::Instance()->IsKeyPressed('P') && !pPressed) {
				LegoManager::Instance()->StartPuttingBlock();
				LegoManager::Instance()->setGameStatus(eAddingBlock1x1x1);
				pPressed = true;
			} else if (!LegoManager::Instance()->IsKeyPressed('P')) {
				pPressed = false;
			}
		} break;
	case eGameStatus::eChangingView:
		{

		} break;
	case eGameStatus::eAddingBlock1x1x1:
		{
			if (LegoManager::Instance()->IsKeyPressed('P') && !pPressed) {
				LegoManager::Instance()->EndPuttingBlock();
				LegoManager::Instance()->setGameStatus(eNormal);
				pPressed = true;
			} else if (!LegoManager::Instance()->IsKeyPressed('P')) {
				pPressed = false;
			}
		} break;
	}

	return true;
}

bool DestroyScene()
{
	LegoManager::Instance()->Destroy();
	gUIMgr.Destroy();

	return true;
}

void KillGLWindow()
{
	DestroyScene();

	if (hRC) {
		if (!wglMakeCurrent(NULL, NULL)) {
			MessageBox(NULL,"Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC)) {
			MessageBox(NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		hRC = NULL;
	}

	if (hDC && !ReleaseDC(hWnd,hDC)) {
		MessageBox(NULL,"Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hDC = NULL;
	}

	if (hWnd && !DestroyWindow(hWnd)) {
		MessageBox(NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;
	}

	if (!UnregisterClass("OpenGL",hInstance)) {
		MessageBox(NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;
	}
}

bool LeftButtonDownHandle(LPARAM lParam)
{
	if (gUIMgr.LeftClickDown((int)LOWORD(lParam), WINDOW_HEIGHT - (int)HIWORD(lParam))) {
				
	} else {
// 		int mousex = LOWORD(lParam);          
// 		int mousey = HIWORD(lParam);
// 		MousePicking(mousex, mousey);
// 		return 0;
	}

	return true;
}

bool LeftButtonUpHandle(LPARAM lParam)
{
	if (!gUIMgr.LeftClickUp((int)LOWORD(lParam), WINDOW_HEIGHT - (int)HIWORD(lParam))) {
		int mousex = LOWORD(lParam);
		int mousey = HIWORD(lParam);
		MousePicking(mousex, mousey, true);
	}
	return true;
}

bool MouseMoveHandle(LPARAM lParam)
{
	switch (LegoManager::Instance()->getGameStatus())
	{
	case eAddingBlock1x1x1:
	case eAddingBlock1x2x1:
	case eAddingBlock2x1x1:
	case eAddingBlock2x2x1:
	case eAddingBlock3x1x1:
	case eAddingBlock3x1x2:
	case eAddingBlock4x1x1:
	case eAddingBlock4x1x2:
		{
			int mousex = LOWORD(lParam);
			int mousey = HIWORD(lParam);
			MousePicking(mousex, mousey);
		} break;
	}

	return true;
}

/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
 *	title			- Title To Appear At The Top Of The Window				*
 *	width			- Width Of The GL Window Or Fullscreen Mode				*
 *	height			- Height Of The GL Window Or Fullscreen Mode			*
 *	bits			- Number Of Bits To Use For Color (8/16/24/32)			*
 *	fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*/
 
bool CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint				PixelFormat;								// Holds The Results After Searching For A Match
	WNDCLASS			wc;											// Windows Class Structure
	DWORD				dwExStyle;									// Window Extended Style
	DWORD				dwStyle;									// Window Style
	RECT				WindowRect;									// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left		= (long)0;									// Set Left Value To 0
	WindowRect.right	= (long)width;								// Set Right Value To Requested Width
	WindowRect.top		= (long)0;									// Set Top Value To 0
	WindowRect.bottom	= (long)height;								// Set Bottom Value To Requested Height

	hInstance			= GetModuleHandle(NULL);					// Grab An Instance For Our Window
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;		// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc		= (WNDPROC) WndProc;						// WndProc Handles Messages
	wc.cbClsExtra		= 0;										// No Extra Window Data
	wc.cbWndExtra		= 0;										// No Extra Window Data
	wc.hInstance		= hInstance;								// Set The Instance
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);				// Load The Default Icon
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);				// Load The Arrow Pointer
	wc.hbrBackground	= NULL;										// No Background Required For GL
	wc.lpszMenuName		= NULL;										// We Don't Want A Menu
	wc.lpszClassName	= "OpenGL";									// Set The Class Name

	if (!RegisterClass(&wc)) {
		MessageBox(NULL, "Failed To Register The Window Class.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;												// Return FALSE
	}

	dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;				// Window Extended Style
	dwStyle = WS_OVERLAPPEDWINDOW;								// Windows Style

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd=CreateWindowEx(dwExStyle,							// Extended Style For The Window
							  "OpenGL",								// Class Name
							  title,								// Window Title
							  dwStyle |								// Defined Window Style
							  WS_CLIPSIBLINGS |						// Required Window Style
							  WS_CLIPCHILDREN,						// Required Window Style
							  0, 0,									// Window Position
							  WindowRect.right-WindowRect.left,		// Calculate Window Width
							  WindowRect.bottom-WindowRect.top,		// Calculate Window Height
							  NULL,									// No Parent Window
							  NULL,									// No Menu
							  hInstance,							// Instance
							  NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();												// Reset The Display
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;												// Return FALSE
	}

	static PIXELFORMATDESCRIPTOR pfd =								// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),								// Size Of This Pixel Format Descriptor
		1,															// Version Number
		PFD_DRAW_TO_WINDOW |										// Format Must Support Window
		PFD_SUPPORT_OPENGL |										// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,											// Must Support Double Buffering
		PFD_TYPE_RGBA,												// Request An RGBA Format
		bits,														// Select Our Color Depth
		0, 0, 0, 0, 0, 0,											// Color Bits Ignored
		0,															// No Alpha Buffer
		0,															// Shift Bit Ignored
		0,															// No Accumulation Buffer
		0, 0, 0, 0,													// Accumulation Bits Ignored
		16,															// 16Bit Z-Buffer (Depth Buffer)  
		0,															// No Stencil Buffer
		0,															// No Auxiliary Buffer
		PFD_MAIN_PLANE,												// Main Drawing Layer
		0,															// Reserved
		0, 0, 0														// Layer Masks Ignored
	};
	
	if (!(hDC = GetDC(hWnd)))	{
		KillGLWindow();												// Reset The Display
		MessageBox(NULL, "Can't Create A GL Device Context.","ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;												// Return FALSE
	}

	if (!(PixelFormat = ChoosePixelFormat(hDC,&pfd))) {
		KillGLWindow();												// Reset The Display
		MessageBox(NULL, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;												// Return FALSE
	}

	if (!SetPixelFormat(hDC, PixelFormat, &pfd)) {
		KillGLWindow();												// Reset The Display
		MessageBox(NULL, "Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;												// Return FALSE
	}

	if (!(hRC = wglCreateContext(hDC))) {
		KillGLWindow();												// Reset The Display
		MessageBox(NULL, "Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;												// Return FALSE
	}

	if (!wglMakeCurrent(hDC, hRC)) {
		KillGLWindow();												// Reset The Display
		MessageBox(NULL, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;												// Return FALSE
	}

	ShowWindow(hWnd, SW_SHOW);										// Show The Window
	SetForegroundWindow(hWnd);										// Slightly Higher Priority
	SetFocus(hWnd);													// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);									// Set Up Our Perspective GL Screen

	if (!InitializeGL()) {
		KillGLWindow();												// Reset The Display
		MessageBox(NULL, "Initialization Failed.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return false;												// Return FALSE
	}

	return true;													// Success
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)													// Check For Windows Messages
	{
		case WM_ACTIVATE:											// Watch For Window Activate Message
		{
			if (!HIWORD(wParam)) {
				active = true;										// Program Is Active
			} else {
				active = false;										// Program Is No Longer Active
			}

			return 0;												// Return To The Message Loop
		}

		case WM_SYSCOMMAND:											// Intercept System Commands
		{
			switch (wParam)											// Check System Calls
			{
				case SC_SCREENSAVE:									// Screensaver Trying To Start?
				case SC_MONITORPOWER:								// Monitor Trying To Enter Powersave?
				return 0;											// Prevent From Happening
			}
			break;													// Exit
		}

		case WM_CLOSE:												// Did We Receive A Close Message?
		{
			PostQuitMessage(0);										// Send A Quit Message
			return 0;												// Jump Back
		}

		case WM_KEYDOWN:											// Is A Key Being Held Down?
		{
			LegoManager::Instance()->PressKey(wParam);				// If So, Mark It As TRUE
			return 0;												// Jump Back
		}

		case WM_KEYUP:												// Has A Key Been Released?
		{
			LegoManager::Instance()->ReleaseKey(wParam);			// If So, Mark It As FALSE
			return 0;												// Jump Back
		}

		case WM_SIZE:												// Resize The OpenGL Window
		{
			ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));			// LoWord=Width, HiWord=Height
			return 0;												// Jump Back
		}

		case WM_LBUTTONDOWN:
		{
			LeftButtonDownHandle(lParam);
			return 0;
		}

		case WM_LBUTTONUP:
		{
			LeftButtonUpHandle(lParam);
			return 0;
		}

		case WM_MOUSEMOVE:
		{
			MouseMoveHandle(lParam);
			return 0;
		}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	MSG		msg;													// Windows Message Structure
	bool	done = false;											// Bool Variable To Exit Loop

	// Create Our OpenGL Window
	if (!CreateGLWindow("Lego World", WINDOW_WIDTH, WINDOW_HEIGHT, 32, false)) {
		return 0;													// Quit If Window Was Not Created
	}

	while (!done) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				done = true;										// If So done=TRUE
			} else {
				TranslateMessage(&msg);								// Translate The Message
				DispatchMessage(&msg);								// Dispatch The Message
			}
		} else {
			if (active) {
				if (LegoManager::Instance()->IsKeyPressed(VK_ESCAPE)) {
					done = TRUE;
				} else {
					DWORD starttime = timeGetTime();
					UpdateScene();
					SwapBuffers(hDC);

					// limit the FPS
					DWORD endtime = timeGetTime() - starttime;
					if (endtime < 1000 / FPS) {
						Sleep(1000 / FPS - endtime);
					}
					endtime = timeGetTime() - starttime;
					if (endtime == 0) {
						fps = 60;
					} else {
						fps = 1000 / endtime;
					}
					//std::cout << gFps << std::endl;
				}
			}
		}
	}

	// Shutdown
	KillGLWindow();													// Kill The Window
	return (msg.wParam);											// Exit The Program
}
