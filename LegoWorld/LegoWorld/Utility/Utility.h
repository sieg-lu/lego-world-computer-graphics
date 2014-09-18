/*
 * This file contains some utility functions
 */

#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>
#include <cg\cg.h>
#include <cg\cgGL.h>
#include <iostream>
using namespace std;

GLuint					LoadGLTexture(const char *filename);
void					CheckForCgError(const char *situation, CGcontext cgctxt);
bool					IsInLegalRange(int num, int low, int high);
bool					FloatEquals(float a, float b, float eps = 1e-3);
