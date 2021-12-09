#include "base.hpp"

int main()
{
	if (geteuid() != 0) {
		std::cout << "[!] Please run as root" << std::endl;
		return -1;
	}

	CSSMH::Init();

	return 0;
}