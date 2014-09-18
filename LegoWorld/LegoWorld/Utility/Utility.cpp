#include <cmath>
#include "Utility.h"

GLuint LoadGLTexture(const char *filename)
{
	GLuint texid;
	HBITMAP hBMP;
	BITMAP BMP;
	glGenTextures(1, &texid);
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), filename, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	if(!hBMP) {
		return false;
	}
	GetObject(hBMP, sizeof(BMP), &BMP);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glBindTexture(GL_TEXTURE_2D, texid);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
	DeleteObject(hBMP);
	return texid;
}

void CheckForCgError(const char *situation, CGcontext cgctxt)
{
	CGerror error;
	const char *string = cgGetLastErrorString(&error);

	if (error != CG_NO_ERROR) {
		printf("%s: %s\n", situation, string);
		if (error == CG_COMPILER_ERROR) {
			printf("%s\n", cgGetLastListing(cgctxt));
		}
		system("pause");
		exit(1);
	}
}

bool IsInLegalRange(int num, int low, int high)
{
	return (num >= low && num < high);
}

bool FloatEquals(float a, float b, float eps /*= 1e-3*/)
{
	return fabs(a - b) < eps;
}
