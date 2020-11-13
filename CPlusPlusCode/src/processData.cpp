#include "processData.h"

enum CodeValue { insCode, delCode, updCode, stCode, mbCode, djCode, egCode, comCode };

static map<string, CodeValue> s_mapCodeValues = {
	{ "INS",insCode },
	{ "DEL",delCode },
	{ "UPD",updCode },
	{ "ST",stCode },
	{ "MB",mbCode },
	{ "DJ",djCode },
	{ "EG",egCode }
};


ProcessData::ProcessData() {
	data = new LList<Exchange>();
	//data = nullptr;
}
ProcessData::~ProcessData() {
	delete data;
}
/*
Split the command line into instruction and its parameters
(This version is simplified to return just the instruction only; students should rewrite to make it return instruction's parameters)
Input:
line: the command line
sp: pass-by-reference parameter used as an output: return the array of strings keeping instruction and its parameter
Output: return the number of elements in array sp.
*/
int ProcessData::split(string line, string* &sp) {//da code lai
	/////////////check khoang trang
	if (line[0] == ' ' || line[line.length() - 1] == ' ') return -1;
	for (int i = 0; i < line.length(); i++)
	{
		if (line[i] == ' ')
		{
			if (line[i + 1] == ' ')
			{
				return -1;
			}
		}
	}
	/////////////
	sp = new string[MAXSIZECODE];
	line = line + " ";
	const string SEP = " ";
	int pos = 0, lastpos = 0, idx = 0;
	while (pos != line.length() - 1)
	{
		pos = line.find(SEP, lastpos);
		sp[idx] = line.substr(lastpos, pos - lastpos);
		lastpos = pos + 1;
		idx++;
	}
	return idx;
}
void ProcessData::printfBCQC() {
	data->printfdata();
}
void ProcessData::soluongnen() {
	cout << data->length() << "\n";
}
int ProcessData::process(string line) {
	string* p;
	int n = ProcessData::split(line, p);
	if (n <= 0) {
		delete[] p;
		return -1;
	}
	//////check noi dung lenh
	if (p[0] != "INS"&& p[0] != "DEL" && p[0] != "UPD"&& p[0] != "ST"&& p[0] != "MB"&& p[0] != "DJ"&& p[0] != "EG") return -1;
	if (p[0] == "INS" || p[0] == "UPD")// xu li loi INS
	{
		if (n < 8) return -1;
		for (int i = 3; i < 8; i++)
		{
			for (int j = 0; j < p[i].length(); j++)
			{
				if ((p[i][j]<'0' || p[i][j]>'9') && p[i][j] != '.')
				{
					return -1;
				}
			}
		}
	}
	if (p[0] == "DEL" || p[0] == "ST" || p[0] == "MB")
	{
		if (n < 3 || n>5) return -1;
		for (int i = 3; i < n; i++)
		{
			for (int j = 0; j < p[i].length(); j++)
			{
				if ((p[i][j]<'0' || p[i][j]>'9') && p[i][j] != '.')
				{
					return -1;
				}
			}
		}
	}
	if (p[0] == "DJ"||p[0]=="EG")
	{
		if (n < 3 || n>6) return -1;
		if (p[3] == "C1" || p[3] == "C2" || p[3] == "C3" || p[3] == "C4")
		{
			for (int i = 4; i < n; i++)
			{
				for (int j = 0; j < p[i].length(); j++)
				{
					if ((p[i][j]<'0' || p[i][j]>'9') && p[i][j] != '.')
					{
						return -1;
					}
				}
			}
		}
		else
		{
			if (n == 6)
			{
				if (p[3] != "C1" && p[3] != "C2" && p[3] != "C3" && p[3] != "C4")
				{
					return -1;
				}
			}
			for (int i = 3; i < n; i++)
			{
				for (int j = 0; j < p[i].length(); j++)
				{
					if ((p[i][j]<'0' || p[i][j]>'9') && p[i][j] != '.')
					{ 
						return -1;
					}
				}
			}
		}
	}
	///////
	int res = -1;
	try {
		switch (s_mapCodeValues[p[0]]) {
		case insCode:
		{
			res = insert(p,n);
			break;
		}
		case updCode:
		{
			res = updateNen(p, n);
			break;
		}
		case delCode:
		{
			res = deleteNen(p,n);
			break;
		}
		case stCode:
		{
			res = stNen(p, n);
			break;
		}
		case mbCode:
		{
			res = mbNen(p, n);
			break;
		}
		case djCode:
		{
			res = djNen(p, n);
			break;
		}
		case egCode:
		{
			res = egNen(p, n);
			break;
		}
		default:
			res = -1;
			break;
		}
	}
	catch (invalid_argument iax) {
		delete[] p;
		return res;
	}
	delete[] p;
	return res;
}
/*
To process insert instruction
(This is the simplified version)
Input:
sp: pointer to string array keeping instruction and its parameters
n: the number of elements in sp
Output:
return the result as required
*/
int ProcessData::insert(const string* sp, const int n) {
	Exchange B;
	B.BC = sp[1];
	B.QC = sp[2];
	B.Next = nullptr;
	B.Nen.Time = sp[3];
	B.Nen.OP = sp[4];
	B.Nen.HP = sp[5];
	B.Nen.LP = sp[6];
	B.Nen.CP = sp[7];
	data->insert(B);
	return data->length();
}
int ProcessData::deleteNen(const string* sp, const int n) {
	if (sp[3] =="" && sp[4] == "")
	{
		
		//cout<<"so luong nen bi xoa la(xoa toan bo): "<<data->deleteall(sp[1],sp[2])<<"\n";
		return data->deleteall(sp[1], sp[2]);
	}
	else if(sp[4]==""&&sp[3]!="")
	{
		//cout<<"so luong nen bi xoa la(xoa theo Time): "<<data->deleteTimeA(sp[1],sp[2],sp[3])<<"\n";
		return data->deleteTimeA(sp[1], sp[2], sp[3]);
	}
	else if (sp[4] !="" &&sp[3] !="")
	{
		//cout<< "so luong nen bi xoa la(xoa theo TIME A TIME B: " << data->deleteTimeATimeB(sp[1], sp[2], sp[3],sp[4]) << "\n";
		return data->deleteTimeATimeB(sp[1], sp[2], sp[3], sp[4]);
	}
}
int ProcessData::updateNen(const string* sp, const int n)
{
	Exchange B;
	B.BC = sp[1];
	B.QC = sp[2];
	B.Next = nullptr;
	B.Nen.Time = sp[3];
	B.Nen.OP = sp[4];
	B.Nen.HP = sp[5];
	B.Nen.LP = sp[6];
	B.Nen.CP = sp[7];
	//cout << data->update(B);
	return data->update(B);
}
int ProcessData::stNen(const string* sp, const int n)
{
	if (sp[3] == "" && sp[4] == "")
	{
		//cout << data->stfull(sp[1], sp[2]);
		return data->stfull(sp[1], sp[2]);
	}
	else if (sp[3] != "" && sp[4] == "")
	{
		//cout << data->stTime(sp[1], sp[2], sp[3]);
		return data->stTime(sp[1], sp[2], sp[3]);
	}
	else
	{
		//cout << data->stTime_Time(sp[1], sp[2], sp[3], sp[4]);
		return data->stTime_Time(sp[1], sp[2], sp[3], sp[4]);
	}
	return 0;
}
int ProcessData::mbNen(const string* sp, const int n)
{
	if (sp[3] == "" && sp[4] == "")
	{
		//cout << data->mbfull(sp[1], sp[2]);
		return data->mbfull(sp[1], sp[2]);
	}
	else if (sp[3] != "" && sp[4] == "")
	{
		//cout << data->mbTime(sp[1], sp[2], sp[3]);
		return data->mbTime(sp[1], sp[2], sp[3]);
	}
	else
	{
		//cout << data->mb(sp[1], sp[2], sp[3], sp[4]);
		return data->mb(sp[1], sp[2], sp[3], sp[4]);
	}
	return 0;
}
int ProcessData::djNen(const string* sp, const int n)
{
	if (sp[3]!="C1"&&sp[3] != "C2"&&sp[3] != "C3"&&sp[3] != "C4")
	{
		if (sp[3] == "" && sp[4] == "")
		{
			//cout << data->djfull(sp[1], sp[2]);
			return data->djfull(sp[1], sp[2]);
		}
		else if (sp[3] != "" && sp[4] == "")
		{
			//cout << data->djTime(sp[1], sp[2], sp[3]);
			return data->djTime(sp[1], sp[2], sp[3]);
		}
		else
		{
			//cout << data->dj(sp[1], sp[2], sp[3], sp[4]);
			return data->dj(sp[1], sp[2], sp[3], sp[4]);
		}
	}
	else
	{
		if (sp[4] == ""&&sp[5] == "")
		{
			//cout << data->djwithCodefull(sp[1], sp[2], sp[3]);
			return data->djwithCodefull(sp[1], sp[2], sp[3]);
		}
		else if (sp[4] != ""&&sp[5] == "")
		{
			//cout << data->djwithCodeTime(sp[1], sp[2], sp[3], sp[4]);
			return data->djwithCodeTime(sp[1], sp[2], sp[3], sp[4]);
		}
		else
		{
			//cout << data->djwithCode(sp[1], sp[2], sp[3], sp[4], sp[5]);
			return data->djwithCode(sp[1], sp[2], sp[3], sp[4], sp[5]);
		}
	}
	return 0;
}
int ProcessData::egNen(const string* sp, const int n)
{
	if (sp[3] != "C1"&&sp[3] != "C2")
	{
		if (sp[3] == "" && sp[4] == "")
		{
			//cout << data->cumnenfull(sp[1], sp[2]);
			return data->cumnenfull(sp[1], sp[2]);
		}
		else if (sp[3] != ""&&sp[4] == "")
		{
			//cout << data->cumnenTime(sp[1], sp[2], sp[3]);
			return data->cumnenTime(sp[1], sp[2], sp[3]);
		}
		else
		{
			//cout << data->cumnen(sp[1], sp[2], sp[3], sp[4]);
			return data->cumnen(sp[1], sp[2], sp[3], sp[4]);
		}
	}
	else
	{
		if (sp[4] == ""&&sp[5] == "")
		{
			//cout << data->cumnenwithcodefull(sp[1], sp[2], sp[3]);
			return  data->cumnenwithcodefull(sp[1], sp[2], sp[3]);
		}
		else if (sp[4] != ""&&sp[5] == "")
		{
			//cout << data->cumnenwithcodeTime(sp[1], sp[2], sp[3], sp[4]);
			return data->cumnenwithcodeTime(sp[1], sp[2], sp[3], sp[4]);
		}
		else
		{
			//cout << data->cumnenwithcode(sp[1], sp[2], sp[3], sp[4], sp[5]);
			return data->cumnenwithcode(sp[1], sp[2], sp[3], sp[4], sp[5]);
		}
	}
	return 0;
}

