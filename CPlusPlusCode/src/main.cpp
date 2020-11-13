#include "main.h"
#include "processData.h"

using namespace std;
void usage();


int main(int argc, char** argv) {
	ifstream inFile;
	ofstream outFile;

	if (argc != 3)
		usage();

	inFile.open(argv[1]);
	if (!inFile) {
		cout << "Unable to open file " << argv[1];
		exit(1); // terminate with error
	}

	outFile.open(argv[2]);
	if (!outFile) {
		cout << "Unable to open file " << argv[2];
		exit(1); // terminate with error
	}

	ProcessData * data = new ProcessData();

	string line;
	while (getline(inFile, line)) {
		outFile << data->process(line) << endl;
	}

	inFile.close();
	outFile.close();
	delete data;
	/*string line = "DJW EUR USD 322 321 221";
	string line1 = "INS EUR USD 15000 1 5 1 5";
	string line2 = "INS EUR USD 10000 2 3 2 5";
	string line3 = "INS EUR USD 12200 5 3 2 2";
	string line4 = "INS EUR USD 15300 6 1.3220 1.2310 1";
	string line5 = "INS VND USD 26200 1.2300 1.3220 1.2310 1.1121";
	string line8 = "INS JAP USD 26200 2 1.3220 0.523 1.6245";
	string line9 = "INS JAP USD 30200 1.2300 1.3220 1.2310 1.1121";
	string line6 = "DEL JAP USD 10000";
	string line7 = "UPD JaP USD 30200 10000 30000 50000 10000";
	string line10 = "EG EUR USD C1 1000 9000";

	ProcessData * data = new ProcessData();
	////////////////////
	data->process(line);
	data->process(line1);
	data->process(line2);
	data->process(line4);
	data->process(line3);
	data->process(line5);
	data->process(line8);
	data->process(line9);
	data->process(line10);
	//data->process(line7);
	//data->process(line7);*/
	/////////////////////
	//data->printfBCQC();
	//data->soluongnen();
	return 0;
}
void usage() {
	cout << "Usage: main <input file> <output file>" << endl;
	exit(1);
}