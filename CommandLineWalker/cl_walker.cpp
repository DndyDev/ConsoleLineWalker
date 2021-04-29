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
/// Maximum render distance
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

	map += L"#########.......";
	map += L"#...............";
	map += L"#........#######";
	map += L"#..............#";
	map += L"#......##......#";
	map += L"#......##......#";
	map += L"#..............#";
	map += L"###............#";
	map += L"##.............#";
	map += L"##.....####..###";
	map += L"##.....#.....###";
	map += L"##.....#.....###";
	map += L"##...........###";
	map += L"##......########";
	map += L"##.............#";
	map += L"################";

	auto tp1 = chrono::system_clock::now();
	auto tp2 = chrono::system_clock::now();

	while (true) {
		//We'll need time differential per frame to calculate modification
		//to movement speeds,to ensure consistant movement, as ray-tracing
		// is non-determinic
		tp2 = chrono::system_clock::now();
		chrono::duration<float> elapsedTime = tp2 - tp1;
		tp1 = tp2;
		float fElapsedTime = elapsedTime.count();


		//Handle left(Counterclock-wise) Rotation
		if (GetAsyncKeyState((unsigned short)'A') & 0x8000)
			fPlayerA -= (fSpeed * 0.75f) * fElapsedTime;

		//Handle right(CW) Rotation
		if (GetAsyncKeyState((unsigned short)'D') & 0x8000)
			fPlayerA += (fSpeed * 0.75f) * fElapsedTime;

		//Handle Forward movement & collision
		if (GetAsyncKeyState((unsigned short)'W') & 0x8000) {
			fPlayerX += sinf(fPlayerA) * fSpeed * fElapsedTime;
			fPlayerY += cosf(fPlayerA) * fSpeed * fElapsedTime;

			if (map.c_str()[(int)fPlayerX * nMapWidth + (int)fPlayerY] == '#')
			{
				fPlayerX -= sinf(fPlayerA) * fSpeed * fElapsedTime;;
				fPlayerY -= cosf(fPlayerA) * fSpeed * fElapsedTime;;
			}
		}

		//Handle backward movement & collision
		if (GetAsyncKeyState((unsigned short)'S') & 0x8000) {
			fPlayerX -= sinf(fPlayerA) * fSpeed * fElapsedTime;;
			fPlayerX -= cosf(fPlayerA) * fSpeed * fElapsedTime;;

			if (map.c_str()[(int)fPlayerX * nMapWidth + (int)fPlayerY] == '#') {
				fPlayerX += sinf(fPlayerA) * fSpeed * fElapsedTime;
				fPlayerY += cosf(fPlayerA) * fSpeed * fElapsedTime;
			}
		}
		for (int x = 0; x < nScreenWidth; ++x) {
			// For each column, calulate the projected ray angle into space
			float fRayAngle = (fPlayer - fFOV / 2.0f) + ((float)x / (float)nScreenWidth) * fFOV;
		}
	}
}