char scratchpad[1024];
char memwpsx[0x600000];

char* MemW32_GetMemBase()
{
	return memwpsx;
}

int MemW32_GetSize()
{
	return sizeof(memwpsx);
}

char* getScratchAddr(int pos)
{
	return &scratchpad[4 * pos];
}
