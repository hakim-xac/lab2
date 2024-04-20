#include "common.h"
#include "FordBellman.h"

int main()
{
	LAB2::FordBellman fb{ "in.txt"
		, LAB2::FordBellman::count_vertex_t{ 10 }
		, LAB2::FordBellman::start_vertex_t{ 0 } };

	fb.printHeader();
	fb.printShortCut();

	[[maybe_unused]] int c{ getchar() };

	return 0;
}