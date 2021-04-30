#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <chrono>

using namespace std;

#include <stdio.h>
#include <Windows.h>

int nScreenWidth = 120;
int nScreenHight = 60; // должно быть 40
int nMapWidth = 16;
int nMapHight = 16;

// Start postion
float fPlayerX = 14.7f;
float fPlayerY = 5.09f;
// Start Rotation
float fPlayerA = 0.0f;
// Field of Vision
float fFOV = 3.14159f / 4.0f;
// Maximum render distance
// because 16 pixel map
float fDepth = 16.0f;

float fSpeed = 5.0f;

int main() {

	// Screen Buffer
	wchar_t* screen = new wchar_t[nScreenWidth * nScreenHight];
	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWriten = 0;

	// Create World Map 
	// # = wall block
	// . = space
	
	wstring map;

	map += L"################";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"#..............#";
	map += L"################";


	while (true) {

		for (int x < 0; x < nScreenWidth; x++) {

			//For each column calc the projected ray angle	into world space
			float fRayAngle = (fPlayerA - fFOV / 2.0f) + ((float)x / nScreenWidth) * fFOV;

			float fDistanceToWall = 0;
			bool bHitHall = false;

			// Unit vector for ray in player space
			float fEyeX = sinf(fRayAngle);
			float fEyeY = cosf(fRayAngle);

			while (!bHitWall && fDistanceToWall < fDepth) {
				fDistanceToWall += 0.1f

					int nTestX = (int)(fPlayerX + fEyeX * fDistanceToWall);
					int nTestY = (int)(fPlayerY + fEyeX * fDistanceToWall);
					// Test if aray is out of bounds
					if (nTestX < 0 || nTestX >= nMapWidth || nTestY < 0 || nTestY >= nMapHight) {
						// Just set distance to maximum depth
						bHitWall = true;
						fDistanceToWall = fDepth;

					}
			}
		}
		screen[nScreenWidth * nScreenHight - 1] = '\0';
		WriteConsoleOutputCharacter(hConsole, screen, nScreemWidth * nScreenHight, { 0,0 }, &dwBytesWriten);
	}
}