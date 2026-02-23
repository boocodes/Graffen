#include "IdGenerator.h"


int IdGenerator::id = 1;

int IdGenerator::next()
{
	return id++;
}

IdGenerator::IdGenerator() {};