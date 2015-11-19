#include"LinkCandidateUtil.h"

Iqueue::Iqueue(int size)
{
	length = 0;
	inport = 0;
	outport = 0;
	str = new int[size];
}

Iqueue::~Iqueue()
{
	delete str;
}

int Iqueue::pop()
{
    outport ++;
	length --;
	return str[outport - 1];
}

void Iqueue::push(int n)
{
	str[inport] = n;
    inport ++;
	length ++;
}

void Iqueue::reset()
{
 	length = 0;
	inport = 0;
	outport = 0;
}


