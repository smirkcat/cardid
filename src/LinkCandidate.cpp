#include"LinkCandidate.h"

std::vector<RotatedRect> LinkCandidate::run()
{
	cgts.clear();
	link();
	finalresult();
	return cgts;
}
void LinkCandidate::finalresult()
{
	for(int i = 0;i< CandidateNum-1;i++)
	{
		bool sign = false;
		for(int j = i+1;j< CandidateNum;j++)
			sign = sign | relation[i][j];
		candidateStore[i].alive = sign;  
		candidateStore[i].chuan = 0;
	}
	
	int index = 1;
	int tempNum;
	for(int i = 0;i< CandidateNum;i++)
	{
		if(!candidateStore[i].alive)
			continue;
		Iq->reset();
		Iq->push(i);
		candidateStore[i].chuan = index;
		candidateStore[i].alive = false;
		while(Iq->length)
		{
			tempNum = Iq->pop();
			for (int j = 0; j< CandidateNum; j++)
			{
				if(relation[tempNum][j])
				{
					Iq->push(j);
					candidateStore[j].chuan = index;
					candidateStore[j].alive = false;
					relation[tempNum][j] = false;
					relation[j][tempNum] = false;
				}
			}

		}
		index++;
	}

	vector< vector<int> > store(index + 2);
	for(int i = 0;i< CandidateNum;i++)
	{
		store[candidateStore[i].chuan].push_back(i);
	}

	for(int i = 1;i< index;i++)
	{
		if(store[i].size() <=3)
			continue;

		vector<cv::Point> PointV;

		for(int j = 0; j< store[i].size();j++)
		{
			PointV.push_back(cv::Point(candidateStore[store[i][j]].min_j,candidateStore[store[i][j]].min_i));
			PointV.push_back(cv::Point(candidateStore[store[i][j]].max_j,candidateStore[store[i][j]].max_i));
			PointV.push_back(cv::Point(candidateStore[store[i][j]].min_j, candidateStore[store[i][j]].max_i));
			PointV.push_back(cv::Point(candidateStore[store[i][j]].max_j, candidateStore[store[i][j]].min_i));
		}
		//用RotatedRect保存倾斜角度
		cv::RotatedRect textline = cv::minAreaRect(PointV);
		cgts.push_back(textline);
	}
}

void LinkCandidate::findPairRegion(int i, int j)
{
	if(candidateStore[i].middle_j == candidateStore[j].middle_j && candidateStore[i].middle_i == candidateStore[j].middle_i) return;
	if(candidateStore[i].high/candidateStore[j].high > 2.0 || candidateStore[i].high/candidateStore[j].high < 0.5) return;
	if(candidateStore[i].width/candidateStore[j].width > 4 || candidateStore[i].width/candidateStore[j].width < 0.25) return;
	if(candidateStore[i].strokeWidh/candidateStore[j].strokeWidh > 4 || candidateStore[i].strokeWidh/candidateStore[j].strokeWidh < 0.2) return;
	//if(abs(candidateStore[i].avergecolor - candidateStore[j].avergecolor) > 20 ) return;
	//if(abs(candidateStore[i].averareb - candidateStore[j].averareb) > 20 ) return;
	//if(abs(candidateStore[i].averarer - candidateStore[j].averarer) > 20 ) return;
	//if(abs(candidateStore[i].averareg - candidateStore[j].averareg) > 20 ) return;
	double deltai = abs(candidateStore[i].middle_i - candidateStore[j].middle_i);
	double deltaj = abs(candidateStore[i].middle_j - candidateStore[j].middle_j);
	double Theroidi = min(candidateStore[i].width,candidateStore[j].width);
	double Theroidj = min(candidateStore[i].high,candidateStore[j].high);
	if(deltai > 0.4*Theroidi || deltaj > 4*Theroidj) return ; 
	this->relation[i][j] = true;
	this->relation[j][i] = true;
}

void LinkCandidate::link() 
{
	for(int i = 0;i< CandidateNum - 1;i++)
		for(int j = i + 1;j< CandidateNum;j++)
			findPairRegion(i,j);
}
LinkCandidate::LinkCandidate(vector<Candidate>& candidateStore){
	this->candidateStore = candidateStore;
	CandidateNum = candidateStore.size();
	this->Iq = new Iqueue(CandidateNum*CandidateNum);
	this->relation = std::vector<std::vector<bool> >(CandidateNum, std::vector<bool>(CandidateNum, false));
}