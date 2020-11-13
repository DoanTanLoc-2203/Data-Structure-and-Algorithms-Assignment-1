#include "main.h"

struct StructNen {
	string	Time;
	string OP;
	string HP;
	string LP;
	string CP;
};
struct NodeNen {
	StructNen datanen;
	NodeNen * Next;
};
class ListNen {
public:
	NodeNen* fron;
	NodeNen* current;
	NodeNen* rear;
public:
	ListNen() { fron = current = rear = nullptr;  }
	int AddNen(StructNen &A)
	{
		bool checkTime = false;
		NodeNen *Node = new NodeNen();
		Node->datanen = A;
		Node->Next = nullptr;
		if (fron == nullptr)
		{
			fron = Node;
			rear = Node;
		}
		else
		{
			if (Node->datanen.Time>rear->datanen.Time)
			{
				rear->Next = Node;
				rear = Node;
			}
			else if (Node->datanen.Time < fron->datanen.Time)
			{
				Node->Next = fron;
				fron = Node;
			}
			else
			{
				current = fron;
				while (true)
				{
					if ((current->datanen.Time < Node->datanen.Time) && (Node->datanen.Time < ((current->Next)->datanen.Time)))
					{
						break;
					}
					if (Node->datanen.Time == current->datanen.Time)
					{
						checkTime = true;
						break;
					}
					current = current->Next;
				}
				if (checkTime == false)
				{
					Node->Next = current->Next;
					current->Next = Node;
				}
			}
		}
	}
	int lengthNen()
	{
		int soluongnen = 0;
		current = fron;
		while (current != nullptr)
		{
			soluongnen++;
			current = current->Next;
		}
		return soluongnen;
	}
	int deleteTime(const string _Time)
	{
		bool check = false;
		current = fron;
		while (current != nullptr)
		{
			if (current->datanen.Time == _Time)//kiem tra xem co Time tuong ung khong
			{
				check = true;
				break;
			}
			else check = false;
			current = current->Next;
		}
		if (check == true)
		{
			if (rear == fron)
			{
				rear = fron = nullptr;
				return 1;
			}
			if (fron->datanen.Time == _Time&&fron != rear)//xoa node dau
			{
				NodeNen * temp = fron;
				fron = temp->Next;
				delete temp;
			}
			else if (rear->datanen.Time == _Time)// xoa node cuoi
			{
				current = fron;
				while (current != nullptr)
				{
					if (current->Next == rear)
					{
						break;
					}
					current = current->Next;
				}
				NodeNen *temp = rear;
				current->Next = nullptr;
				rear = current;
				delete temp;
			}
			else// xoa node ngau nhien
			{
				current = fron;
				while (current != nullptr)
				{
					if ((current->Next)->datanen.Time == _Time)
					{
						break;
					}
					current = current->Next;
				}
				NodeNen *temp = current->Next;
				current->Next = temp->Next;
				delete temp;
			}
			return 1;
		}
		else
		{
			return 0;
		}
		
	}
	int deleteTime_Time(const string _TimeA, const string _TimeB)
	{
		int sonenbixoa = 0;
		int TimeAconve = atoi(_TimeA.c_str());
		int TimeBconve = atoi(_TimeB.c_str());
		bool checkTime = false;
		current = fron;
		while (current != nullptr)
		{
			if ((atoi(current->datanen.Time.c_str()) >= TimeAconve) && (atoi(current->datanen.Time.c_str()) <= TimeBconve))
			{
				checkTime = true;
				break;
			}
			else checkTime = false;
			current = current->Next;
		}
		if (checkTime == true)
		{
			while((atoi(current->datanen.Time.c_str()) <= TimeBconve))
			{
				deleteTime(current->datanen.Time);
				sonenbixoa++;
				if (current->Next == nullptr) break;
				current = current->Next;
			}
			return sonenbixoa;
		}
		return sonenbixoa;
	}
	int update(const string _Time,const string _OP, const string _HP, const string _LP, const string _CP)
	{
		bool check = false;
		current = fron;
		while (current!=nullptr)
		{
			if (current->datanen.Time == _Time)
			{
				check = true;
				break;
			}
			current = current->Next;
		}
		if (check == true)
		{
			current->datanen.OP = _OP;
			current->datanen.HP = _HP;
			current->datanen.LP = _CP;
			current->datanen.CP = _CP;
			return 1;
		}
		else
		{
			return 0;
		}
	}
	int nenxoay(const int _TimeA, const int _TimeB)
	{
		bool check = false;
		current = fron;
		while (current!=nullptr)
		{
			if ((atoi(current->datanen.Time.c_str()) >= _TimeA) && (atoi(current->datanen.Time.c_str()) <= _TimeB))
			{
				check = true;
				break;
			}
			else check = false;
			current = current->Next;
		}
		if (check == true)
		{
			int sonen = 0;
			while (atoi(current->datanen.Time.c_str())<=_TimeB)
			{
				float giaOP = atof(current->datanen.OP.c_str());
				float giaLP = atof(current->datanen.LP.c_str());
				float giaHP = atof(current->datanen.HP.c_str());
				float giaCP = atof(current->datanen.CP.c_str());
				float bongtren;
				float bongduoi;
				float thannen;
				if (giaOP < giaCP)//nen tang
				{
					bongtren = abs(giaHP - giaCP);
					bongduoi = abs(giaOP - giaLP);
					thannen =  abs(giaOP - giaCP);
				}
				else//nen giam
				{
					bongtren = abs(giaHP - giaOP);
					bongduoi = abs(giaCP - giaLP);
					thannen = abs(giaOP - giaCP);
				}
				//cout << bongtren << " " << bongduoi << " " << thannen << "\n";
				if ((roundf(bongtren * 100) / 100) > 0.5f && (roundf(bongduoi * 100) / 100) > 0.5f && (roundf(thannen * 100) / 100) <= 0.5f)
				{
					sonen++;
				}
				if (current->Next == nullptr) break;
				current = current->Next;
			}
			return sonen;
		}
		else
		{
			return 0;
		}
	}
	int nenxoayTime(const int _TimeA)
	{
		bool check = false;
		current = fron;
		while (current != nullptr)
		{
			if ((atoi(current->datanen.Time.c_str()) == _TimeA))
			{
				check = true;
				break;
			}
			else check = false;
			current = current->Next;
		}
		if (check == true)
		{
			float giaOP = atof(current->datanen.OP.c_str());
			float giaLP = atof(current->datanen.LP.c_str());
			float giaHP = atof(current->datanen.HP.c_str());
			float giaCP = atof(current->datanen.CP.c_str());
			float bongtren;
			float bongduoi;
			float thannen;
			if (giaOP < giaCP)//nen tang
			{
				bongtren = abs(giaHP - giaCP);
				bongduoi = abs(giaOP - giaLP);
				thannen = abs(giaOP - giaCP);
			}
			else//nen giam
			{
				bongtren = abs(giaHP - giaOP);
				bongduoi = abs(giaCP - giaLP);
				thannen = abs(giaOP - giaCP);
			}
			//cout << bongtren << " " << bongduoi << " " << thannen << "\n";
			if ((roundf(bongtren * 100) / 100) > 0.5f && (roundf(bongduoi * 100) / 100) > 0.5f && (roundf(thannen * 100) / 100) <= 0.5f)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else
		{
			return 0;
		}
	}
	int nenxoayfull()
	{
		current = fron;
		int sonen = 0;
		while (current != nullptr)
		{
			float giaOP = atof(current->datanen.OP.c_str());
			float giaLP = atof(current->datanen.LP.c_str());
			float giaHP = atof(current->datanen.HP.c_str());
			float giaCP = atof(current->datanen.CP.c_str());
			float bongtren;
			float bongduoi;
			float thannen;
			if (giaOP < giaCP)//nen tang
			{
				bongtren = abs(giaHP - giaCP);
				bongduoi = abs(giaOP - giaLP);
				thannen = abs(giaOP - giaCP);
			}
			else//nen giam
			{
				bongtren = abs(giaHP - giaOP);
				bongduoi = abs(giaCP - giaLP);
				thannen = abs(giaOP - giaCP);
			}
			//cout << bongtren << " " << bongduoi << " " << thannen << "\n";
			if ((roundf(bongtren * 100) / 100) > 0.5f && (roundf(bongduoi * 100) / 100) > 0.5f && (roundf(thannen * 100) / 100) <= 0.5f)
			{
				sonen++;
			}
			current = current->Next;
		}
		return sonen;
	}
	int nenmb(const int _TimeA, const int _TimeB)
	{
		bool check = false;
		current = fron;
		while (current != nullptr)
		{
			if ((atoi(current->datanen.Time.c_str()) >= _TimeA) && (atoi(current->datanen.Time.c_str()) <= _TimeB))
			{
				check = true;
				break;
			}
			else check = false;
			current = current->Next;
		}
		if (check == true)
		{
			int sonen = 0;
			while (atoi(current->datanen.Time.c_str()) <= _TimeB)
			{
				float giaOP = atof(current->datanen.OP.c_str());
				float giaLP = atof(current->datanen.LP.c_str());
				float giaHP = atof(current->datanen.HP.c_str());
				float giaCP = atof(current->datanen.CP.c_str());
				float bongtren;
				float bongduoi;
				float thannen;
				if (giaOP < giaCP)//nen tang
				{
					bongtren = abs(giaHP - giaCP);
					bongduoi = abs(giaOP - giaLP);
					thannen = abs(giaOP - giaCP);
				}
				else//nen giam
				{
					bongtren = abs(giaHP - giaOP);
					bongduoi = abs(giaCP - giaLP);
					thannen = abs(giaOP - giaCP);
				}
				//cout << bongtren << " " << bongduoi << " " << thannen << "\n";
				if (bongtren ==0 && bongduoi ==0 && thannen >0)
				{
					sonen++;
				}
				if (current->Next == nullptr) break;
				current = current->Next;
			}
			return sonen;
		}
		else
		{
			return 0;
		}
	}
	int nenmbTime(const int _TimeA)
	{
		bool check = false;
		current = fron;
		while (current != nullptr)
		{
			if ((atoi(current->datanen.Time.c_str()) == _TimeA))
			{
				check = true;
				break;
			}
			else check = false;
			current = current->Next;
		}
		if (check == true)
		{
			float giaOP = atof(current->datanen.OP.c_str());
			float giaLP = atof(current->datanen.LP.c_str());
			float giaHP = atof(current->datanen.HP.c_str());
			float giaCP = atof(current->datanen.CP.c_str());
			float bongtren;
			float bongduoi;
			float thannen;
			if (giaOP < giaCP)//nen tang
			{
				bongtren = abs(giaHP - giaCP);
				bongduoi = abs(giaOP - giaLP);
				thannen = abs(giaOP - giaCP);
			}
			else//nen giam
			{
				bongtren = abs(giaHP - giaOP);
				bongduoi = abs(giaCP - giaLP);
				thannen = abs(giaOP - giaCP);
			}
			//cout << bongtren << " " << bongduoi << " " << thannen << "\n";
			if (bongtren == 0 && bongduoi == 0 && thannen >0)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else
		{
			return 0;
		}
	}
	int nenmbfull()
	{
		current = fron;
		int sonen = 0;
		while (current != nullptr)
		{
			float giaOP = atof(current->datanen.OP.c_str());
			float giaLP = atof(current->datanen.LP.c_str());
			float giaHP = atof(current->datanen.HP.c_str());
			float giaCP = atof(current->datanen.CP.c_str());
			float bongtren;
			float bongduoi;
			float thannen;
			if (giaOP < giaCP)//nen tang
			{
				bongtren = abs(giaHP - giaCP);
				bongduoi = abs(giaOP - giaLP);
				thannen = abs(giaOP - giaCP);
			}
			else//nen giam
			{
				bongtren = abs(giaHP - giaOP);
				bongduoi = abs(giaCP - giaLP);
				thannen = abs(giaOP - giaCP);
			}
			//cout << bongtren << " " << bongduoi << " " << thannen << "\n";
			if (bongtren == 0 && bongduoi == 0 && thannen >0)
			{
				sonen++;
			}
			current = current->Next;
		}
		return sonen;
	}
	int nendj(const int _TimeA, const int _TimeB)
	{
		bool check = false;
		current = fron;
		while (current != nullptr)
		{
			if ((atoi(current->datanen.Time.c_str()) >= _TimeA) && (atoi(current->datanen.Time.c_str()) <= _TimeB))
			{
				check = true;
				break;
			}
			else check = false;
			current = current->Next;
		}
		if (check == true)
		{
			int sonen = 0;
			while (atoi(current->datanen.Time.c_str()) <= _TimeB)
			{
				float giaOP = atof(current->datanen.OP.c_str());
				float giaLP = atof(current->datanen.LP.c_str());
				float giaHP = atof(current->datanen.HP.c_str());
				float giaCP = atof(current->datanen.CP.c_str());
				float bongtren;
				float bongduoi;
				float thannen;
				if (giaOP < giaCP)//nen tang
				{
					bongtren = abs(giaHP - giaCP);
					bongduoi = abs(giaOP - giaLP);
					thannen = abs(giaOP - giaCP);
				}
				else//nen giam
				{
					bongtren = abs(giaHP - giaOP);
					bongduoi = abs(giaCP - giaLP);
					thannen =  abs(giaOP - giaCP);
				}
				//cout << bongtren << " " << bongduoi << " " << thannen << "\n";
				if (thannen>=0 && (roundf(thannen*100)/100)<=0.2f)
				{
					sonen++;
				}
				if (current->Next == nullptr) break;
				current = current->Next;
			}
			return sonen;
		}
		else
		{
			return 0;
		}
	}
	int nendjTime(const int _TimeA)
	{
		bool check = false;
		current = fron;
		while (current != nullptr)
		{
			if ((atoi(current->datanen.Time.c_str()) == _TimeA))
			{
				check = true;
				break;
			}
			else check = false;
			current = current->Next;
		}
		if (check == true)
		{
			float giaOP = atof(current->datanen.OP.c_str());
			float giaLP = atof(current->datanen.LP.c_str());
			float giaHP = atof(current->datanen.HP.c_str());
			float giaCP = atof(current->datanen.CP.c_str());
			float bongtren;
			float bongduoi;
			float thannen;
			if (giaOP < giaCP)//nen tang
			{
				bongtren = abs(giaHP - giaCP);
				bongduoi = abs(giaOP - giaLP);
				thannen = abs(giaOP - giaCP);
			}
			else//nen giam
			{
				bongtren = abs(giaHP - giaOP);
				bongduoi = abs(giaCP - giaLP);
				thannen = abs(giaOP - giaCP);
			}
			//cout << bongtren << " " << bongduoi << " " << thannen << "\n";
			if (thannen >= 0 && (roundf(thannen * 100) / 100) <= 0.2f)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else
		{
			return 0;
		}
	}
	int nendjfull()
	{
		current = fron;
		int sonen = 0;
		while (current != nullptr)
		{
			float giaOP = atof(current->datanen.OP.c_str());
			float giaLP = atof(current->datanen.LP.c_str());
			float giaHP = atof(current->datanen.HP.c_str());
			float giaCP = atof(current->datanen.CP.c_str());
			float bongtren;
			float bongduoi;
			float thannen;
			if (giaOP < giaCP)//nen tang
			{
				bongtren = abs(giaHP - giaCP);
				bongduoi = abs(giaOP - giaLP);
				thannen = abs(giaOP - giaCP);
			}
			else//nen giam
			{
				bongtren = abs(giaHP - giaOP);
				bongduoi = abs(giaCP - giaLP);
				thannen = abs(giaOP - giaCP);
			}
			//cout << bongtren << " " << bongduoi << " " << thannen << "\n";
			if (thannen >= 0 && (roundf(thannen * 100) / 100) <= 0.2f)
			{
				sonen++;
			}
			current = current->Next;
		}
		return sonen;
	}
	int nendjcode(const int _TimeA, const int _TimeB, const string code)
	{
		bool check = false;
		current = fron;
		while (current != nullptr)
		{
			if ((atoi(current->datanen.Time.c_str()) >= _TimeA) && (atoi(current->datanen.Time.c_str()) <= _TimeB))
			{
				check = true;
				break;
			}
			else check = false;
			current = current->Next;
		}
		if (check == true)
		{
			int sonen = 0;
			while (atoi(current->datanen.Time.c_str()) <= _TimeB)
			{
				float giaOP = atof(current->datanen.OP.c_str());
				float giaLP = atof(current->datanen.LP.c_str());
				float giaHP = atof(current->datanen.HP.c_str());
				float giaCP = atof(current->datanen.CP.c_str());
				float bongtren;
				float bongduoi;
				float thannen;
				if (giaOP < giaCP)//nen tang
				{
					bongtren = abs(giaHP - giaCP);
					bongduoi = abs(giaOP - giaLP);
					thannen = abs(giaOP - giaCP);
				}
				else//nen giam
				{
					bongtren = abs(giaHP - giaOP);
					bongduoi = abs(giaCP - giaLP);
					thannen = abs(giaOP - giaCP);
				}
				//cout << bongtren << " " << bongduoi << " " << thannen << "\n";
				if (thannen >= 0 && (roundf(thannen * 100) / 100) <= 0.2f)
				{
					if (code == "C1")// doji bong dai
					{
						if ((roundf(bongtren * 100) / 100) > 0.5f && (roundf(bongduoi * 100) / 100) > 0.5f)
						{
							sonen++;
						}
					}
					else if (code == "C2")// doji chuon chuon
					{
						if (bongtren == 0 && (roundf(bongduoi * 100) / 100) > 0.5f)
						{
							sonen++;
						}
					}
					else if (code == "C3")//doji bia mo
					{
						if (bongduoi == 0 && (roundf(bongtren * 100) / 100) > 0.5f)
						{
							sonen++;
						}
					}
					else if (code == "C4")//doji bon gia
					{
						if (giaCP == giaHP && giaHP == giaLP && giaLP == giaOP)
						{
							sonen++;
						}
					}
				}
				if (current->Next == nullptr) break;
				current = current->Next;
			}
			return sonen;
		}
		else
		{
			return 0;
		}
	}
	int nendjcodeTime(const int _TimeA, const string code)
	{
		bool check = false;
		current = fron;
		while (current != nullptr)
		{
			if (atoi(current->datanen.Time.c_str()) == _TimeA)
			{
				check = true;
				break;
			}
			else check = false;
			current = current->Next;
		}
		if (check == true)
		{
			float giaOP = atof(current->datanen.OP.c_str());
			float giaLP = atof(current->datanen.LP.c_str());
			float giaHP = atof(current->datanen.HP.c_str());
			float giaCP = atof(current->datanen.CP.c_str());
			float bongtren;
			float bongduoi;
			float thannen;
			if (giaOP < giaCP)//nen tang
			{
				bongtren = abs(giaHP - giaCP);
				bongduoi = abs(giaOP - giaLP);
				thannen = abs(giaOP - giaCP);
			}
			else//nen giam
			{
				bongtren = abs(giaHP - giaOP);
				bongduoi = abs(giaCP - giaLP);
				thannen = abs(giaOP - giaCP);
			}
			//cout << bongtren << " " << bongduoi << " " << thannen << "\n";
			if (thannen >= 0 && (roundf(thannen * 100) / 100) <= 0.2f)
			{
				if (code == "C1")// doji bong dai
				{
					if ((roundf(bongtren * 100) / 100) > 0.5f && (roundf(bongduoi * 100) / 100) > 0.5f)
					{
						return 1;
					}
					else return 0;
				}
				else if (code == "C2")// doji chuon chuon
				{
					if (bongtren == 0 && (roundf(bongduoi * 100) / 100) > 0.5f)
					{
						return 1;
					}
					else return 0;
				}
				else if (code == "C3")//doji bia mo
				{
					if (bongduoi == 0 && (roundf(bongtren * 100) / 100) > 0.5f)
					{
						return 1;
					}
					else return 0;
				}
				else if (code == "C4")//doji bon gia
				{
					if (giaCP == giaHP && giaHP == giaLP && giaLP == giaOP)
					{
						return 1;
					}
					else return 0;
				}
			}
			else return 0;
		}
		else
		{
			return 0;
		}
	}
	int nendjcodefull(const string code)
	{
		int sonen = 0;
		current = fron;
		while (current != nullptr)
		{
			float giaOP = atof(current->datanen.OP.c_str());
			float giaLP = atof(current->datanen.LP.c_str());
			float giaHP = atof(current->datanen.HP.c_str());
			float giaCP = atof(current->datanen.CP.c_str());
			float bongtren;
			float bongduoi;
			float thannen;
			if (giaOP < giaCP)//nen tang
			{
				bongtren = abs(giaHP - giaCP);
				bongduoi = abs(giaOP - giaLP);
				thannen = abs(giaOP - giaCP);
			}
			else//nen giam
			{
				bongtren = abs(giaHP - giaOP);
				bongduoi = abs(giaCP - giaLP);
				thannen = abs(giaOP - giaCP);
			}
			//cout << bongtren << " " << bongduoi << " " << thannen << "\n";
			if (thannen >= 0 && (roundf(thannen * 100) / 100) <= 0.2f)
			{
				if (code == "C1")// doji bong dai
				{
					if ((roundf(bongtren * 100) / 100) > 0.5f && (roundf(bongduoi * 100) / 100) > 0.5f)
					{
						sonen++;
					}
				}
				else if (code == "C2")// doji chuon chuon
				{
					if (bongtren == 0 && (roundf(bongduoi * 100) / 100) > 0.5f)
					{
						sonen++;
					}
				}
				else if (code == "C3")//doji bia mo
				{
					if (bongduoi == 0 && (roundf(bongtren * 100) / 100) > 0.5f)
					{
						sonen++;
					}
				}
				else if (code == "C4")//doji bon gia
				{
					if (giaCP == giaHP && giaHP == giaLP && giaLP == giaOP)
					{
						sonen++;
					}
				}
			}
			current = current->Next;
		}
		return sonen;
	}
	int nennhanchimfull()
	{
		int socumnen=0;
		current = fron;
		while (current->Next!=nullptr)
		{
			float giaOP = atof(current->datanen.OP.c_str());
			float giaCP = atof(current->datanen.CP.c_str());
			float giaOPnext= atof((current->Next)->datanen.OP.c_str());
			float giaCPnext= atof((current->Next)->datanen.CP.c_str());
			float thannen = abs(giaOP - giaCP);
			float thannenNext = abs(giaOPnext - giaCPnext);
			if (giaOP < giaCP)//nen tang, dme cum nen giam
			{
				if (giaOPnext >= giaCPnext && thannenNext-thannen > 0.5f) // nen giam
				{
					if (giaOPnext>=giaCP && giaCPnext<=giaOP)
					{
						socumnen++;
					}
				}
			}
			else//nen giam, dem cum nen tang
			{
				if (giaOPnext <= giaCPnext && thannenNext - thannen > 0.5f)//nen tang
				{
					if (giaOP <= giaCPnext && giaCP >= giaOPnext)
					{
						socumnen++;
					}
				}
			}
			current = current->Next;
		}
		return socumnen;
	}
	int nennhanchimTime(const int _TimeA)
	{
		bool check = false;
		current = fron;
		while (current != nullptr)
		{
			if ((atoi(current->datanen.Time.c_str()) == _TimeA))
			{
				check = true;
				break;
			}
			else check = false;
			current = current->Next;
		}
		if (check == true)
		{
			if (current->Next != nullptr)
			{
				float giaOP = atof(current->datanen.OP.c_str());
				float giaCP = atof(current->datanen.CP.c_str());
				float giaOPnext = atof((current->Next)->datanen.OP.c_str());
				float giaCPnext = atof((current->Next)->datanen.CP.c_str());
				float thannen = abs(giaOP - giaCP);
				float thannenNext = abs(giaOPnext - giaCPnext);
				if (giaOP < giaCP)//nen tang, dme cum nen giam
				{
					if (giaOPnext >= giaCPnext && thannenNext - thannen > 0.5f) // nen giam
					{
						if (giaOPnext >= giaCP && giaCPnext <= giaOP)
						{
							return 1;
						}
						else return 0;
					}
					else return 0;
				}
				else//nen giam, dem cum nen tang
				{
					if (giaOPnext <= giaCPnext && thannenNext - thannen > 0.5f)//nen tang
					{
						if (giaOP <= giaCPnext && giaCP >= giaOPnext)
						{
							return 1;
						}
						else return 0;
					}
					else return 0;
				}
			}
			else return 0;
		}
		else
		{
			return 0;
		}
	}
	int nennhanchim(const int _TimeA, const int _TimeB)
	{
		bool check = false;
		current = fron;
		while (current != nullptr)
		{
			if ((atoi(current->datanen.Time.c_str()) >= _TimeA) && (atoi(current->datanen.Time.c_str()) <= _TimeB))
			{
				check = true;
				break;
			}
			else check = false;
			current = current->Next;
		}
		if (check == true)
		{
			int socumnen = 0;
			while (atoi(current->datanen.Time.c_str()) <= _TimeB&&current->Next!=nullptr)
			{
				float giaOP = atof(current->datanen.OP.c_str());
				float giaCP = atof(current->datanen.CP.c_str());
				float giaOPnext = atof((current->Next)->datanen.OP.c_str());
				float giaCPnext = atof((current->Next)->datanen.CP.c_str());
				float thannen = abs(giaOP - giaCP);
				float thannenNext = abs(giaOPnext - giaCPnext);
				if (giaOP < giaCP)//nen tang, dme cum nen giam
				{
					if (giaOPnext >= giaCPnext && thannenNext - thannen > 0.5f) // nen giam
					{
						if (giaOPnext >= giaCP && giaCPnext <= giaOP)
						{
							socumnen++;
						}
					}
				}
				else//nen giam, dem cum nen tang
				{
					if (giaOPnext <= giaCPnext && thannenNext - thannen > 0.5f)//nen tang
					{
						if (giaOP <= giaCPnext && giaCP >= giaOPnext)
						{
							socumnen++;
						}
					}
				}
				current = current->Next;
			}
			return socumnen;
		}
		else
		{
			return 0;
		}
	}
	int nennhanchimwithCodefull(const string code)
	{
		int socumnen = 0;
		current = fron;
		while (current->Next != nullptr)
		{
			float giaOP = atof(current->datanen.OP.c_str());
			float giaCP = atof(current->datanen.CP.c_str());
			float giaOPnext = atof((current->Next)->datanen.OP.c_str());
			float giaCPnext = atof((current->Next)->datanen.CP.c_str());
			float thannen = abs(giaOP - giaCP);
			float thannenNext = abs(giaOPnext - giaCPnext);
			if (code == "C2")
			{
				if (giaOP < giaCP)//nen tang, dme cum nen giam
				{
					if (giaOPnext >= giaCPnext && thannenNext - thannen > 0.5f) // nen giam
					{
						if (giaOPnext >= giaCP && giaCPnext <= giaOP)
						{
							socumnen++;
						}
					}
				}
			}
			else if (code == "C1")
			{   //nen giam, dem cum nen tang
				if (giaOP > giaCP)
				{
					if (giaOPnext <= giaCPnext && thannenNext - thannen > 0.5f)//nen tang
					{
						if (giaOP <= giaCPnext && giaCP >= giaOPnext)
						{
							socumnen++;
						}
					}
				}
			}
			current = current->Next;
		}
		return socumnen;
	}
	int nennhanchimwithCodeTime(const int _TimeA, const string code)
	{
		bool check = false;
		current = fron;
		while (current != nullptr)
		{
			if ((atoi(current->datanen.Time.c_str()) == _TimeA))
			{
				check = true;
				break;
			}
			else check = false;
			current = current->Next;
		}
		if (check == true)
		{
			if (current->Next != nullptr)
			{
				float giaOP = atof(current->datanen.OP.c_str());
				float giaCP = atof(current->datanen.CP.c_str());
				float giaOPnext = atof((current->Next)->datanen.OP.c_str());
				float giaCPnext = atof((current->Next)->datanen.CP.c_str());
				float thannen = abs(giaOP - giaCP);
				float thannenNext = abs(giaOPnext - giaCPnext);
				if (code == "C2")
				{
					if (giaOP < giaCP)//nen tang, dme cum nen giam
					{
						if (giaOPnext >= giaCPnext && thannenNext - thannen > 0.5f) // nen giam
						{
							if (giaOPnext >= giaCP && giaCPnext <= giaOP)
							{
								return 1;
							}
							else return  0;
						}
						else return 0;
					}
					else return 0;
				}
				else if (code == "C1")
				{   //nen giam, dem cum nen tang
					if (giaOP > giaCP)
					{
						if (giaOPnext <= giaCPnext && thannenNext - thannen > 0.5f)//nen tang
						{
							if (giaOP <= giaCPnext && giaCP >= giaOPnext)
							{
								return 1;
							}
							else return 0;
						}
						else return 0;
					}
					else return 0;
				}
			}
			return 0;
		}
		else
		{
			return 0;
		}
	}
	int nennhanchimwithCode(const int _TimeA, const int _TimeB, const string code)
	{
		bool check = false;
		current = fron;
		while (current != nullptr)
		{
			if ((atoi(current->datanen.Time.c_str()) >= _TimeA) && (atoi(current->datanen.Time.c_str()) <= _TimeB))
			{
				check = true;
				break;
			}
			else check = false;
			current = current->Next;
		}
		if (check == true)
		{
			int socumnen = 0;
			while (atoi(current->datanen.Time.c_str()) <= _TimeB&&current->Next != nullptr)
			{
				float giaOP = atof(current->datanen.OP.c_str());
				float giaCP = atof(current->datanen.CP.c_str());
				float giaOPnext = atof((current->Next)->datanen.OP.c_str());
				float giaCPnext = atof((current->Next)->datanen.CP.c_str());
				float thannen = abs(giaOP - giaCP);
				float thannenNext = abs(giaOPnext - giaCPnext);
				if (code == "C2")
				{
					if (giaOP < giaCP)//nen tang, dme cum nen giam
					{
						if (giaOPnext >= giaCPnext && thannenNext - thannen > 0.5f) // nen giam
						{
							if (giaOPnext >= giaCP && giaCPnext <= giaOP)
							{
								socumnen++;
							}
						}
					}
				}
				else if (code == "C1")
				{   //nen giam, dem cum nen tang
					if (giaOP > giaCP)
					{
						if (giaOPnext <= giaCPnext && thannenNext - thannen > 0.5f)//nen tang
						{
							if (giaOP <= giaCPnext && giaCP >= giaOPnext)
							{
								socumnen++;
							}
						}
					}
				}
				current = current->Next;
			}
			return socumnen;
		}
		else
		{
			return 0;
		}
	}
	void printfNen()
	{
		current = fron;
		int index = 0;
		while (current != nullptr)
		{
			index++;
			cout << "Thu tu: " << index << "\t" << "Time: " << current->datanen.Time << "\t" << "OP: " << current->datanen.OP << "\t" << "HP: " << current->datanen.HP << "\t" << "LP: " << current->datanen.LP << "\t" << "CP: "<< current->datanen.CP << "\n";
			current = current->Next;
		}
		index = 0;
	}
};
struct Exchange {
	string BC;
	string QC;
	Exchange *Next;
	StructNen Nen;
	ListNen *danhsach;
	int sonen;
};
template <typename T>
class Link {
	public:
		T data;
		Link<T>* next;
		Link<T>(Link<T> *n=nullptr) {next = n;} 
		Link<T>(const T& ele, Link<T> *n=nullptr) {
			data = ele;
			next = n;
		}
};
template <typename T>
class List {
  // Return: The number of elements in the list.
  	virtual int length() const = 0;
	virtual void insert(const T& ele) = 0;
};
template <typename T>
class LList: public List<T> {
	private:
		Link<T>* head;
		Link<T>* last;
		Link<T>* curr;
		int cnt;
	public:
		LList() { head = last = curr = nullptr; cnt = 0; }
		int length() const {return cnt;}
		void insert(const T& ele) {
			bool checkBCQC = false;
			Link<T> *Node = new Link<T>(ele);	
			StructNen NenA;
			NenA.Time = ele.Nen.Time;
			NenA.OP = ele.Nen.OP;
			NenA.HP = ele.Nen.HP;
			NenA.LP = ele.Nen.LP;
			NenA.CP = ele.Nen.CP;
			if (head == nullptr&&head==last)
			{
				Node->data.danhsach = new ListNen();
				Node->data.danhsach->AddNen(NenA);
				head = Node;
				last = Node;
				cnt = 1;
				head->data.sonen = cnt;
			}
			else
			{
				curr = head;
				while (curr != nullptr)
				{
					if( (curr->data.QC == Node->data.QC)&&(curr->data.BC == Node->data.BC))//check xem BC QC da co chua
					{
						checkBCQC = true;
						break;
					}
					else
					{
						checkBCQC = false;
					}
					curr = curr->next;
				}
				if (checkBCQC == false)// chua co cap BC QC
				{
					last->next = Node;
					last = Node;
					Node->data.danhsach = new ListNen();
					Node->data.danhsach->AddNen(NenA);
					cnt = 1;
					last->data.sonen = cnt;
				}
				else
				{
					curr->data.danhsach->AddNen(NenA);
					cnt = curr->data.danhsach->lengthNen();
					curr->data.sonen = cnt;
				}
			}
			
		}
		int sonenBCQC(const string _BC, const string _QC)
		{
			curr = head;
			while (curr != nullptr)
			{
				if (curr->data.BC ==_BC&&curr->data.QC == _QC)
				{
					return curr->data.sonen;
				}
				curr = curr->next;
			}
		}
		int deleteall(const string _BC, const string _QC)
		{
			bool check = false;
			int sonenbixoa;
			curr = head;
			while (curr != nullptr)//check coi có cap BC QC ko
			{
				if (curr->data.BC == _BC && curr->data.QC == _QC)
				{
					check = true;
					break;
				}
				else check = false;
				curr = curr->next;
			}
			if (check == true)
			{
				if (head->data.BC == _BC && head->data.QC == _QC && head != last)// xoa node dau
				{
					sonenbixoa = head->data.danhsach->lengthNen();
					Link<T> *temp = head;
					head = head->next;
					delete temp;
				}
				else if (last->data.BC == _BC && last->data.QC == _QC)//xoa node cuoi
				{
					sonenbixoa = last->data.danhsach->lengthNen();
					curr = head;
					while (curr != nullptr)
					{
						if (curr->next == last)
						{
							last = curr;
							last->next = nullptr;
							break;
						}
						curr = curr->next;
					}
				}
				else// xoa node ngau nhien
				{
					curr = head;
					while (curr != nullptr)
					{
						if ((curr->next)->data.BC == _BC && (curr->next)->data.QC == _QC)
						{
							break;
						}
						curr = curr->next;
					}
					sonenbixoa =(curr->next)->data.danhsach->lengthNen();
					Link<T> *temp = curr->next;
					curr->next = temp->next;
					delete temp;
				}

				return sonenbixoa;
			}	
			else
			{
				sonenbixoa = 0;
				return sonenbixoa;
			}
		}
		int deleteTimeA(const string _BC, const string _QC, const string _TimeA)
		{
			bool check = false;
			curr = head;
			while (curr != nullptr)//check coi có cap BC QC ko
			{
				if (curr->data.BC == _BC && curr->data.QC == _QC)
				{
					check = true;
					break;
				}
				else check = false;
				curr = curr->next;
			}
			if (check == true)
			{
				int sonenbixoa = curr->data.danhsach->deleteTime(_TimeA);
				if (curr->data.danhsach->fron == nullptr)
				{
					deleteall(curr->data.BC, curr->data.QC);
				}
				return sonenbixoa;
			}
			else
			{
				return 0;
			}
		}
		int deleteTimeATimeB(const string _BC, const string _QC, const string _TimeA, const string _TimeB)
		{
			bool check = false;
			curr = head;
			while (curr != nullptr)
			{
				if (curr->data.BC == _BC && curr->data.QC == _QC)
				{
					check = true;
					break;
				}
				else check = false;
				curr = curr->next;
			}
			if (check == true)
			{
				int sonenbixoa = curr->data.danhsach->deleteTime_Time(_TimeA, _TimeB);
				if (curr->data.danhsach->fron == nullptr)
				{
					deleteall(curr->data.BC, curr->data.QC);
				}
				return sonenbixoa;
			}
			else
			{
				return 0;
			}
		}
		int update(const T&ele)
		{
			bool check = false;
			curr = head;
			while (curr != nullptr)
			{
				if (curr->data.BC == ele.BC && curr->data.QC == ele.QC)
				{
					check = true;
					break;
				}
				else check = false;
				curr = curr->next;
			}
			if (check == true)
			{
				return curr->data.danhsach->update(ele.Nen.Time, ele.Nen.OP, ele.Nen.HP, ele.Nen.LP, ele.Nen.CP);
			}
			else
			{
				return 0;
			}
		}
		int stTime_Time(const string _BC, const string _QC, const string _TimeA, const string _TimeB)
		{
			bool check = false;
			curr = head;
			while (curr != nullptr)
			{
				if (curr->data.BC == _BC&&curr->data.QC == _QC)
				{
					check = true;
					break;
				}
				curr = curr->next;
			}
			if (check == true)
			{
				return curr->data.danhsach->nenxoay(atoi(_TimeA.c_str()), atoi(_TimeB.c_str()));
			}
			else
			{
				return 0;
			}
		}
		int stTime(const string _BC, const string _QC, const string _TimeA)
		{
			bool check = false;
			curr = head;
			while (curr != nullptr)
			{
				if (curr->data.BC == _BC&&curr->data.QC == _QC)
				{
					check = true;
					break;
				}
				curr = curr->next;
			}
			if (check == true)
			{
				return curr->data.danhsach->nenxoayTime(atoi(_TimeA.c_str()));
			}
			else
			{
				return 0;
			}
		}
		int stfull(const string _BC, const string _QC)
		{
			bool check = false;
			curr = head;
			while (curr != nullptr)
			{
				if (curr->data.BC == _BC&&curr->data.QC == _QC)
				{
					check = true;
					break;
				}
				curr = curr->next;
			}
			if (check == true)
			{
				return curr->data.danhsach->nenxoayfull();
			}
			else
			{
				return 0;
			}
		}
		int mb(const string _BC, const string _QC, const string _TimeA, const string _TimeB)
		{
			bool check = false;
			curr = head;
			while (curr != nullptr)
			{
				if (curr->data.BC == _BC&&curr->data.QC == _QC)
				{
					check = true;
					break;
				}
				curr = curr->next;
			}
			if (check == true)
			{
				return curr->data.danhsach->nenmb(atoi(_TimeA.c_str()), atoi(_TimeB.c_str()));
			}
			else
			{
				return 0;
			}
		}
		int mbTime(const string _BC, const string _QC, const string _TimeA)
		{
			bool check = false;
			curr = head;
			while (curr != nullptr)
			{
				if (curr->data.BC == _BC&&curr->data.QC == _QC)
				{
					check = true;
					break;
				}
				curr = curr->next;
			}
			if (check == true)
			{
				return curr->data.danhsach->nenmbTime(atoi(_TimeA.c_str()));
			}
			else
			{
				return 0;
			}
		}
		int mbfull(const string _BC, const string _QC)
		{
			bool check = false;
			curr = head;
			while (curr != nullptr)
			{
				if (curr->data.BC == _BC&&curr->data.QC == _QC)
				{
					check = true;
					break;
				}
				curr = curr->next;
			}
			if (check == true)
			{
				return curr->data.danhsach->nenmbfull();
			}
			else
			{
				return 0;
			}
		}
		int dj(const string _BC, const string _QC, const string _TimeA, const string _TimeB)
		{
			bool check = false;
			curr = head;
			while (curr != nullptr)
			{
				if (curr->data.BC == _BC&&curr->data.QC == _QC)
				{
					check = true;
					break;
				}
				curr = curr->next;
			}
			if (check == true)
			{
				return curr->data.danhsach->nendj(atoi(_TimeA.c_str()), atoi(_TimeB.c_str()));
			}
			else
			{
				return 0;
			}
		}
		int djTime(const string _BC, const string _QC, const string _TimeA)
		{
			bool check = false;
			curr = head;
			while (curr != nullptr)
			{
				if (curr->data.BC == _BC&&curr->data.QC == _QC)
				{
					check = true;
					break;
				}
				curr = curr->next;
			}
			if (check == true)
			{
				return curr->data.danhsach->nendjTime(atoi(_TimeA.c_str()));
			}
			else
			{
				return 0;
			}
		}
		int djfull(const string _BC, const string _QC)
		{
			bool check = false;
			curr = head;
			while (curr != nullptr)
			{
				if (curr->data.BC == _BC&&curr->data.QC == _QC)
				{
					check = true;
					break;
				}
				curr = curr->next;
			}
			if (check == true)
			{
				return curr->data.danhsach->nendjfull();
			}
			else
			{
				return 0;
			}
		}
		int djwithCode(const string _BC, const string _QC, const string Code, const string _TimeA, const string _TimeB)
		{
			bool check = false;
			curr = head;
			while (curr != nullptr)
			{
				if (curr->data.BC == _BC&&curr->data.QC == _QC)
				{
					check = true;
					break;
				}
				curr = curr->next;
			}
			if (check == true)
			{
				return curr->data.danhsach->nendjcode(atoi(_TimeA.c_str()), atoi(_TimeB.c_str()), Code);
			}
			else
			{
				return 0;
			}
		}
		int djwithCodeTime(const string _BC, const string _QC, const string Code, const string _TimeA)
		{
			bool check = false;
			curr = head;
			while (curr != nullptr)
			{
				if (curr->data.BC == _BC&&curr->data.QC == _QC)
				{
					check = true;
					break;
				}
				curr = curr->next;
			}
			if (check == true)
			{
				return curr->data.danhsach->nendjcodeTime(atoi(_TimeA.c_str()), Code);
			}
			else
			{
				return 0;
			}
		}
		int djwithCodefull(const string _BC, const string _QC, const string Code)
		{
			bool check = false;
			curr = head;
			while (curr != nullptr)
			{
				if (curr->data.BC == _BC&&curr->data.QC == _QC)
				{
					check = true;
					break;
				}
				curr = curr->next;
			}
			if (check == true)
			{
				return curr->data.danhsach->nendjcodefull(Code);
			}
			else
			{
				return 0;
			}
		}
		int cumnenfull(const string _BC, const string _QC)
		{
			bool check = false;
			curr = head;
			while (curr != nullptr)
			{
				if (curr->data.BC == _BC&&curr->data.QC == _QC)
				{
					check = true;
					break;
				}
				curr = curr->next;
			}
			if (check == true)
			{
				return curr->data.danhsach->nennhanchimfull();
			}
			else
			{
				return 0;
			}
		}
		int cumnenTime(const string _BC, const string _QC, const string _TimeA)
		{
			bool check = false;
			curr = head;
			while (curr != nullptr)
			{
				if (curr->data.BC == _BC&&curr->data.QC == _QC)
				{
					check = true;
					break;
				}
				curr = curr->next;
			}
			if (check == true)
			{
				return curr->data.danhsach->nennhanchimTime(atoi(_TimeA.c_str()));
			}
			else
			{
				return 0;
			}
		}
		int cumnen(const string _BC, const string _QC, const string _TimeA, const string _TimeB)
		{
			bool check = false;
			curr = head;
			while (curr != nullptr)
			{
				if (curr->data.BC == _BC&&curr->data.QC == _QC)
				{
					check = true;
					break;
				}
				curr = curr->next;
			}
			if (check == true)
			{
				return curr->data.danhsach->nennhanchim(atoi(_TimeA.c_str()), atoi(_TimeB.c_str()));
			}
			else
			{
				return 0;
			}
		}
		int cumnenwithcodefull(const string _BC, const string _QC, const string Code)
		{
			bool check = false;
			curr = head;
			while (curr != nullptr)
			{
				if (curr->data.BC == _BC&&curr->data.QC == _QC)
				{
					check = true;
					break;
				}
				curr = curr->next;
			}
			if (check == true)
			{
				return curr->data.danhsach->nennhanchimwithCodefull(Code);
			}
			else
			{
				return 0;
			}
		}
		int cumnenwithcodeTime(const string _BC, const string _QC, const string Code, const string _TimeA)
		{
			bool check = false;
			curr = head;
			while (curr != nullptr)
			{
				if (curr->data.BC == _BC&&curr->data.QC == _QC)
				{
					check = true;
					break;
				}
				curr = curr->next;
			}
			if (check == true)
			{
				return curr->data.danhsach->nennhanchimwithCodeTime(atoi(_TimeA.c_str()), Code);
			}
			else
			{
				return 0;
			}
		}
		int cumnenwithcode(const string _BC, const string _QC, const string Code, const string _TimeA, const string _TimeB)
		{
			bool check = false;
			curr = head;
			while (curr != nullptr)
			{
				if (curr->data.BC == _BC&&curr->data.QC == _QC)
				{
					check = true;
					break;
				}
				curr = curr->next;
			}
			if (check == true)
			{
				return curr->data.danhsach->nennhanchimwithCode(atoi(_TimeA.c_str()), atoi(_TimeB.c_str()), Code);
			}
			else
			{
				return 0;
			}
		}
		void printfdata()
		{
			curr = head;
			int dem = 0;
			while (curr != nullptr)
			{
				cout <<curr->data.BC << " " << curr->data.QC << "\n";
				curr->data.danhsach->printfNen();
				curr = curr->next;
			}
		}
};

class ProcessData {
	private:
		LList<Exchange> * data;
		static const int MAXSIZECODE = 8;
		static int split(string line,string* &sp);
	public:
		ProcessData();
		~ProcessData();
		int process(string line);
		int insert(const string* sp,const int n);
		int deleteNen(const string* sp, const int n);
		int updateNen(const string* sp, const int n);
		int stNen(const string* sp, const int n);
		int mbNen(const string* sp, const int n);
		int djNen(const string* sp, const int n);
		int egNen(const string* sp, const int n);
		bool checkDetail(string line);
		void printfBCQC();
		void soluongnen();
		////
		////
};