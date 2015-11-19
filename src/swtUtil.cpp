#include"swtUtil.h"

Qqueue::Qqueue()
{
	str = new Vpoint[50];
	/*for(int i = 0;i<50;i++)
	{
		str[i].i = 0;
		str[i].j = 0;
	}*/
    inport = 0;
	outport = 0;
	length = 0;
}

Qqueue::~Qqueue()
{
	delete str;
}



void Qqueue::push(Vpoint& m)
{
	str[inport].i = m.i;
	str[inport].j = m.j;
	//str[inport].val = m.val;
    inport ++;
	length++;
}

void Qqueue::pop(Vpoint& m)
{
	m.i = str[outport].i;
	m.j = str[outport].j;
	//m.val = str[outport].val;
    outport++;
	length--;
}

void Qqueue::reset()
{
    inport = 0;
	outport = 0;
	length = 0;
}

