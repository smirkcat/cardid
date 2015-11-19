#ifndef _LINKCANDIDATE_
#define _LINKCANDIDATE_
#include "Candidate.h"
#include "LinkCandidateUtil.h"
#include "headline.h"
#include <math.h>
#include <vector>

class LinkCandidate{
public:
	LinkCandidate(vector<Candidate>&);
	std::vector<RotatedRect> run();
	void findPairRegion(int, int);
	void finalresult();
	void link();
private:
	std::vector<Candidate> candidateStore;
	int CandidateNum;
	std::vector< std::vector<bool> > relation;
	Iqueue* Iq;
	std::vector<cv::RotatedRect> cgts;
};

#endif
