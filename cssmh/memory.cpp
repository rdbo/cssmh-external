#include "memory.hpp"

uintptr_t Memory::GetModuleBase(pid_t pid, std::string module_name)
{
	uintptr_t base_address = 0;
	std::stringstream regex_str;
	regex_str << "([a-z0-9]+)-[a-z0-9]+.*/.*" << module_name;
	std::regex regex = std::regex(regex_str.str());

	std::stringstream path;
	path << "/proc/" << pid << "/maps";

	std::ifstream fs = std::ifstream(path.str());
	std::string line;
	std::smatch matches;

	while (std::getline(fs, line)) {
		if (std::regex_search(line, matches, regex)) {
			base_address = (uintptr_t)strtoul(matches[1].str().c_str(), NULL, 16);
			break;
		}
	}

	return base_address;
}

bool Memory::ReadMemory(pid_t pid, uintptr_t src, void *dst, size_t size)
{
	ssize_t rdsize;
	struct iovec iosrc;
	struct iovec iodst;
	iodst.iov_base = dst;
	iodst.iov_len  = size;
	iosrc.iov_base = (void *)src;
	iosrc.iov_len  = size;
	rdsize = process_vm_readv(pid, &iodst, 1, &iosrc, 1, 0);
	return rdsize != -1;
}

bool Memory::WriteMemory(pid_t pid, uintptr_t dst, void *src, size_t size)
{
	ssize_t wrsize;
	struct iovec iosrc;
	struct iovec iodst;
	iosrc.iov_base = src;
	iosrc.iov_len = size;
	iodst.iov_base = (void *)dst;
	iodst.iov_len = size;
	wrsize = process_vm_writev(pid, &iosrc, 1, &iodst, 1, 0);

	return wrsize != -1;
}
