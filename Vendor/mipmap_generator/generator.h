#pragma once
#include "../stb_image/stb_image.h"
#include "../stb_image/stb_image_write.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
using namespace std;

class generator
{
public:
	static string no_extension(string path, string* extension = nullptr)
	{
		for (int i = path.length() - 2; i >= 0; i--)
		{
			if (path[i] == '.')
			{
				if (extension != nullptr)
					*extension = path.substr(i, path.length() - i);
				return path.substr(0, i);
			}
		}
		return path;
	}
private:

	static vector<uint8_t> take_pixel(int x, int y, int noc, uint8_t* buffer, int buffer_n)
	{
		vector<uint8_t> v1(noc);
		for (int i = 0; i < noc; i++)
			v1[i] = buffer[(x * buffer_n + y) * noc + i];
		return v1;
	}

	static void print_pixel(vector<uint8_t> pixel)
	{
		for (int i = 0; i < pixel.size(); i++)
		{
			cout << setfill('0') << setw(3) << (int)pixel[i] << (i == pixel.size() - 1 ? "" : ",");
		} cout << endl;
	}

	static vector<uint8_t> merge_pixels(vector<uint8_t>& p1, vector<uint8_t>& p2, vector<uint8_t>& p3, vector<uint8_t>& p4)
	{
		int n = p1.size();
		vector<uint8_t> p(n);
		for (int i = 0; i < n; i++)
			p[i] = (p1[i] + p2[i] + p3[i] + p4[i]) / 4;
		//print_pixel(p);
		return p;
	}
public:
	static void generate(string filePath, int levels = 4)
	{
		cout << "Generating . . . \n";

		uint8_t* mainBuffer;
		int width, height, noc;

		mainBuffer = stbi_load(filePath.c_str(), &width, &height, &noc, 4);

		if (width != height)
		{
			cout << "Slika mora biti jednakih dimenzija !";
			throw;
		}

		for (int level = 1; level < levels; level++)
		{
			int n = width / 2;
			uint8_t* levelBuffer = new uint8_t[n * n * noc];
			for (int i = 0; i < n; i++)
			{
				for (int j = 0; j < n; j++)
				{
					vector<uint8_t> p, p1, p2, p3, p4;

					p1 = take_pixel(i * 2 + 0, j * 2 + 0, noc, mainBuffer, width);
					p2 = take_pixel(i * 2 + 0, j * 2 + 1, noc, mainBuffer, width);
					p3 = take_pixel(i * 2 + 1, j * 2 + 0, noc, mainBuffer, width);
					p4 = take_pixel(i * 2 + 1, j * 2 + 1, noc, mainBuffer, width);

					p = merge_pixels(p1, p2, p3, p4);

					for (int x = 0; x < noc; x++)
						levelBuffer[(i * n + j) * 4 + x] = p[x];
				}
			}
			string extension;
			stringstream name;
			name << no_extension(filePath, &extension) << level << extension;
			stbi_write_png(name.str().c_str(), n, n, noc, levelBuffer, n * noc);
			width = n;
			delete[] mainBuffer;
			mainBuffer = levelBuffer;
			if (level == levels - 1)
				delete[] levelBuffer;
		}
	}
};