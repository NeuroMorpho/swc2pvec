/***********
//Code by Yanjie Li
//Oct. 2016
***********/
#include "Graph.h"
#include "FileFun.h"
#include <iomanip>
#include <unistd.h>

using namespace std;

class myComp3D
{
	bool reverse;
	Point3D p;
public:
	myComp3D(Point3D pp, const bool& revparam)
	{
		p = pp;
		reverse = revparam;
	}
	bool operator() (const std::pair<int, Point3D> & lhs, const std::pair<int, Point3D> &rhs) const
	{
		if (reverse) return (computePointDistance(p, lhs.second) > computePointDistance(p, rhs.second));
		else return (computePointDistance(p, lhs.second) < computePointDistance(p, rhs.second));
	}
};

//typedef std::priority_queue<std::pair<int, Point3D>, std::vector< std::pair<int, Point3D> >, myComp3D> mypq_type;


string extractFileName(string fileName){
	int slashIndex = fileName.find_last_of('/');
	size_t dotPos = fileName.find_last_of('.');
	if (dotPos == string::npos)
		return fileName.substr(slashIndex+1);
	else
		return fileName.substr(slashIndex + 1, dotPos - slashIndex - 1);
}

void printPersistentDiagramsWithDiameter(vector<string> files, string outputFolder){
	unsigned int fileNum = files.size();
	std::string fileName;
	double delta;
	vector<Point3D> vP;
	//Debug
	cout<<"Starting loop"<<endl;
	for(size_t i=0;i<fileNum;i++){
		fileName = files[i];
		cout<<"process "<< i<<": "<< fileName << endl;
		delta = 0.1;
		std::ifstream ifs;
		double x, y, z;
		int i1, i2;
		double d;
		vP.clear();
		ifs.open(fileName.c_str());
		int countP, countF;
		ifs >> countP >> countF;
		cout<<"Starting pushback loop"<<endl;
		for(int j = 0; j < countP; j++){
			ifs >> x >> y >> z;
			Point3D p;
			p.x = x;
			p.y = y;
			p.z = z;
			vP.push_back(p);
		}
		cout<<"pushback loop complete"<<endl;
		cout<<delta;
		std::printf("vp.size(): %llu countF: %llu\n", (unsigned long long) vP.size(), (unsigned long long) countF);
		Graph ga(vP.size(), delta, countF);
		ga.setVP(vP);
		cout<<"Starting Edge loop"<<endl;
		cout<<"Starting Edge loop"<<endl;
		
		for(int j = 0; j < countF; j++){
			ifs >> i1 >> i2;
			ga.addEdge(i1, i2);
		}
		cout<<"Edge loop complete"<<endl;

		cout<<"Starting setfuncloop"<<endl;
		for(int j = 0; j < countP; j++){
			ifs >> d;
			ga.setFuncVal(j, d);
		}
		cout<<"setfuncloop loop complete"<<endl;
		ifs.close();
		ifs.clear();
		vP.clear();
		ga.outputPersistenceDiagramsOnlyData(outputFolder + extractFileName(fileName) + ".pdg");
	}
	cout<<"Outer loop complete"<<endl;
}

void getPersistentDiagrams(string filePath, string outputFolder){
	vector<string> files;
	getFiles(filePath, "des", files);
	//vector<string> filesFixIndex = getFixIndexFiles(files);
	printPersistentDiagramsWithDiameter(files, outputFolder);
}

int main(int argc, char **argv){
//	if(argc != 3){
//		cout << "usage: PDmain <input folder name> <output folder name>" << endl;
//		return 0;
//	}
//	string euclideanWithFuncVal(argv[1]);
//	string persistenceDiagramFolder(argv[2]);

	if(argc != 3){
		cout << "usage: main <input folder name> <output folder name>" << endl;
	}

	string inputFolder(argv[1]);
	string outputFolder(argv[2]);

	cout << inputFolder;
	inputFolder = inputFolder +"/";
	cout << outputFolder;

	//string inputFolder = "C:\\FileCreator\\CPP\\Input\\";
	//string outputFolder = "C:\\FileCreator\\CPP\\Output\\";

	char buffer[FILENAME_MAX];
	char *answer = getcwd(buffer, sizeof(buffer));
	string s_cwd;
	if (answer)
	{
	    s_cwd = answer;
	}

	cout << s_cwd;
	//string inputFolder = s_cwd + separator() + "temp" + separator();

	//string outputFolder = s_cwd + separator() + "Output" + separator();

//	if(outputFolder.find_last_of('\\') != outputFolder.size() - 1){
//		outputFolder += '\\';
//	}
	getPersistentDiagrams(inputFolder, outputFolder);
}
