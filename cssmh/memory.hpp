#ifndef MEMORY_HPP
#define MEMORY_HPP

#include "base.hpp"

namespace Memory {
	pointer_t GetModuleBase(pid_t pid, std::string module_name);
	bool ReadMemory(pid_t pid, pointer_t src, void *dst, size_t size);
	bool WriteMemory(pid_t pid, pointer_t dst, void *src, size_t size);
	template <typename type_t>
	inline type_t ReadMemory(pid_t pid, pointer_t src)
	{
		type_t val;
		Memory::ReadMemory(pid, src, (void *)&val, sizeof(val));
		return val;
	}
	template <typename type_t>
	inline bool WriteMemory(pid_t pid, pointer_t dst, type_t val)
	{
		return Memory::WriteMemory(pid, dst, (void *)&val, sizeof(val));
	}
}

#endif
