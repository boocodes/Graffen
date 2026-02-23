#pragma once


static class IdGenerator
{
private:
	static int id;
	IdGenerator();
public:
	static int next();
};