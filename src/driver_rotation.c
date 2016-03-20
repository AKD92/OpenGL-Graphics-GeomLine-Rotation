

/************************************************************************************
	Driver File (MAIN)
	Author:             Ashis Kumar Das
	ID:                 11301002
	Email:              akd.bracu@gmail.com
*************************************************************************************/



#include <math.h>
#include <conio2.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iup.h>                /* For GUI toolkit */
#include <iupgl.h>


#define ANGLE				-0.05f
#define BTN_CLOSE			"btnClose"
#define GL_CANVAS			"GLCanvas"
#define MAIN_WINDOW			"423Homework07bMainWindow"



/************************************************************************************
*
*   Function Prototypes and Variable Definitions
*
*************************************************************************************/


struct line_ {
	
	float x0, y0;
	float x1, y1;
	float x2, y2;
	float x3, y3;
	
};

struct line_ line;

char *labTitle = "Graphics Homework 07(B) (11301002)\n"
					"Geometric Rotation of Lines";
					
					

					
					
					
int main(void);

Ihandle * createMainWindow(void);
int repaint_cb(Ihandle *canvas);
int btnRotate_cb(Ihandle *btn);
int exit_cb(Ihandle *btn);



/*	OpenGL related functions	*/

void clipal_drawClipRectangle(void);
void mygl_drawGenericLine(float x0, float y0, float x1, float y1);






/************************************************************************************
*
*   Implementation of midpoint driver routines
*
*************************************************************************************/


Ihandle * createMainWindow(void) {

	Ihandle *bottomHbox, *mainVbox;
	Ihandle *lblTitle, *glCanvas;
	Ihandle *btnRotate, *btnClose;
	Ihandle *dialog;

	lblTitle = IupLabel(labTitle);
	IupSetAttribute(lblTitle, "EXPAND", "HORIZONTAL");
	IupSetAttribute(lblTitle, "ALIGNMENT", "ALEFT:ACENTER");
	IupSetAttribute(lblTitle, "FONTSIZE", "10");

	glCanvas = IupGLCanvas(0);
	IupSetAttribute(glCanvas, "EXPAND", "YES");
	IupSetAttribute(glCanvas, "BORDER", "NO");
	IupSetAttribute(glCanvas, "CANFOCUS", "NO");
	IupSetCallback(glCanvas, "ACTION", (Icallback) repaint_cb);

	btnRotate = IupButton("Rotate", 0);
	IupSetAttribute(btnRotate, "RASTERSIZE", "60x33");
	IupSetCallback(btnRotate, "ACTION", (Icallback) btnRotate_cb);
	
	btnClose = IupButton("Close", 0);
	IupSetAttribute(btnClose, "RASTERSIZE", "80x33");
	IupSetCallback(btnClose, "ACTION", (Icallback) exit_cb);

	bottomHbox = IupHbox(btnRotate, IupFill(), btnClose, 0);
	IupSetAttribute(bottomHbox, "EXPAND", "HORIZONTAL");
	IupSetAttribute(bottomHbox, "NGAP", "5");
	IupSetAttribute(bottomHbox, "NMARGIN", "0x5");

	mainVbox = IupVbox(lblTitle, glCanvas, bottomHbox, 0);
	IupSetAttribute(mainVbox, "NMARGIN", "10x10");
	IupSetAttribute(mainVbox, "NGAP", "10");
	
	IupSetHandle(BTN_CLOSE, btnClose);
	IupSetHandle(GL_CANVAS, glCanvas);

	dialog = IupDialog(mainVbox);
	IupSetAttribute(dialog, "TITLE", "GL Labwork");
	IupSetAttribute(dialog, "RASTERSIZE", "425x550");
	IupSetAttribute(dialog, "SHRINK", "YES");
	IupSetAttribute(dialog, "DEFAULTESC", BTN_CLOSE);
	
	IupSetHandle(MAIN_WINDOW, dialog);

	return dialog;
}




int repaint_cb(Ihandle *canvas) {
	
	if (IupGLIsCurrent(canvas) == 0) {
		IupGLMakeCurrent(canvas);                   /* Declare our canvas for OpenGL */
		glClearColor(0.0, 0.0, 0.0, 0.0);
		glPointSize(1.0);
	}
	glClear(GL_COLOR_BUFFER_BIT);
	
	
	glBegin(GL_POINTS);
		
		glColor3f(0.0f, 1.0f, 0.0f);				/* Color RED to first line */
		mygl_drawGenericLine(line.x0, line.y0, line.x1, line.y1);
		
		glColor3f(1.0f, 0.0f, 0.0f);				/* Color GREEN to second line */
		mygl_drawGenericLine(line.x2, line.y2, line.x3, line.y3);
	
	glEnd();

	glFlush();

	return IUP_DEFAULT;
}


int btnRotate_cb(Ihandle *btn) {
	
	unsigned int i;
	Ihandle *canvas;
	canvas = IupGetHandle(GL_CANVAS);
	
	float x0, y0, x1, y1;
	float x2, y2, x3, y3;
	
	i = 0;
	while (i < 150) {
		
		x0 = line.x0;
		y0 = line.y0;
		x1 = line.x1;
		y1 = line.y1;
		
		x2 = line.x2;
		y2 = line.y2;
		x3 = line.x3;
		y3 = line.y3;
		
		line.x0 = (x0 * cosf(ANGLE) - y0 * sinf(ANGLE));
		line.y0 = (x0 * sinf(ANGLE) + y0 * cosf(ANGLE));
		line.x1 = (x1 * cosf(ANGLE) - y1 * sinf(ANGLE));
		line.y1 = (x1 * sinf(ANGLE) + y1 * cosf(ANGLE));
		
		line.x2 = (x2 * cosf(ANGLE) - y2 * sinf(ANGLE));
		line.y2 = (x2 * sinf(ANGLE) + y2 * cosf(ANGLE));
		line.x3 = (x3 * cosf(ANGLE) - y3 * sinf(ANGLE));
		line.y3 = (x3 * sinf(ANGLE) + y3 * cosf(ANGLE));
		
		IupRedraw(canvas, 0);
		
		delay(30);
		i += 1;
	}
	
	return IUP_DEFAULT;
}



int exit_cb(Ihandle *btn) {

	return IUP_CLOSE;
}





int main(void) {

	Ihandle *dlgMainWindow;
	
	line.x0 = 0.0f;
	line.y0 = 0.8f;
	line.x1 = 0.0f;
	line.y1 = -0.8f;
	
	line.x2 = 0.8f;
	line.y2 = 0.0f;
	line.x3 = -0.8f;
	line.y3 = 0.0f;
	
	IupOpen(0, 0);
		IupGLCanvasOpen();

		dlgMainWindow = createMainWindow();
		IupShowXY(dlgMainWindow, IUP_CENTER, IUP_CENTER);

		IupMainLoop();
	IupClose();
	
	return 0;
}
