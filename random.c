#include<stdio.h>
#include<time.h>
#define UPPER_MASK 0x80000000ULL
#define LOWER_MASK 0x7fffffffULL

typedef struct MT19937
{
	unsigned long long _data[624];
	unsigned short index;
} mt19937;

void mt_init(mt19937 *mt, unsigned long long seed)
{
	unsigned long long *p, *pend;
	mt->index = 0;
	unsigned short i = 1;
	pend = &(mt->_data[623]);
	mt->_data[0] = seed & 0xffffffffULL;
	for(p = mt->_data + 1; p != pend; p++)
	{
		unsigned long long tmp = *(p - 1);
		*p = (1812433253 * (tmp ^ (tmp >> 30)) + i);
		*p &= 0xffffffffULL;
		i++;
	}
}

unsigned int mt_gen(mt19937 *mt)
{
	unsigned short next = (mt->index + 1) % 624;
	unsigned long long *p = &mt->_data[mt->index];
	unsigned int tmp = (*p & UPPER_MASK) | (mt->_data[next] & LOWER_MASK);
	tmp = (*p = mt->_data[(mt->index + 397) % 624] ^ (tmp >> 1) ^ ((tmp & 1ul) ? 0x9908b0dful : 0));
	tmp ^= (tmp >> 11);
	tmp ^= (tmp << 7) & 0x9d2c5680ul;
	tmp ^= (tmp << 15) & 0xefc60000ul;
	tmp ^= (tmp >> 18);
	mt->index = next;
	return tmp;
}
