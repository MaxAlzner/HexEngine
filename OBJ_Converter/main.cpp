
#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>
#include <math.h>
#include <conio.h>
#include <limits.h>
#include <algorithm>

#include <MALib.h>

using namespace std;

int main()
{
	while (true)
	{
		cout << endl << "    Enter filename : ";

		std::string filename;
		getline(cin, filename);
		filename.push_back('\0');
		if (filename[0] == '\0') break;

		cout << endl << "    Converting " << filename << "...";

		bool successful = true;
		
		MALib::OBJ_MESH* obj = 0;
		MALib::VERTEXBUFFER* vb = 0;

		if (!MALib::ImportOBJFile(filename.c_str(), &obj)) successful = false;
		if (!MALib::BakeOBJ(obj, &vb)) successful = false;
		
		std::string vb_filename = filename;
		vb_filename[vb_filename.size() - 4] = 'v';
		vb_filename[vb_filename.size() - 3] = 'm';
		vb_filename[vb_filename.size() - 2] = 'p';
		if (!MALib::ExportVMPFile(vb_filename.c_str(), vb)) successful = false;

		if (successful) cout << " Done" << endl;
		else cout << " Failed" << endl;

		if (obj != 0) MALib::FreeOBJMesh(&obj);
		if (vb != 0) MALib::FreeVertexBuffer(&vb);
	}

	return 0;
}