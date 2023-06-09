#include "CORE.H"
#include "VM.H"
#include "MEMPACK.H"

long vmRealClock; // offset 0x800d106c
long vmClock; // offset 0x800d1070

void VM_Tick(long time)
{
	vmRealClock += time;
	vmClock = vmRealClock >> 8;
#if defined(PC_VERSION)
	dword_C57FD0 += time;
	dword_C57FD4 = dword_C57FD0 >> 8;
#endif
}

void VM_UpdateMorph(struct Level* level, int initFlg)//Matching - 74.26%
{
    struct _VMObject* vmobject;
    int i;
    struct _VMOffsetTable* curTable;
    short ratio;
    int j;
    long num;
    long len;
    short dr;
    short dg;
    short db;

    vmobject = level->vmobjectList;

    for (i = 0; i != level->numVMObjects; i++)
    {
        if (vmobject[i].materialIdx == vmobject[i].spectralIdx)
        {
            curTable = vmobject[i].curVMOffsetTable;
        }

        if ((vmobject[i].flags & 0x100))
        {
            if (gameTrackerX.gameData.asmData.MorphTime == 1000)
            {
                if (curTable != vmobject[i].vmoffsetTableList[vmobject[i].currentIdx])
                {
                    MEMPACK_Free((char*)curTable);
                }

                if (initFlg != 0)
                {
                    if (gameTrackerX.gameData.asmData.MorphType == 0)
                    {
                        vmobject[i].currentIdx = vmobject[i].materialIdx;
                    }
                    else
                    {
                        vmobject[i].currentIdx = vmobject[i].spectralIdx;
                    }
                }
                else
                {
                    if (gameTrackerX.gameData.asmData.MorphType != 0)
                    {
                        vmobject[i].currentIdx = vmobject[i].materialIdx;
                    }
                    else
                    {
                        vmobject[i].currentIdx = vmobject[i].spectralIdx;
                    }
                }

                vmobject[i].curVMOffsetTable = vmobject[i].vmoffsetTableList[vmobject[i].currentIdx];
            }
            else
            {
                num = curTable->numVMOffsets;

                ratio = gameTrackerX.spectral_fadeValue;

                if (curTable == vmobject[i].vmoffsetTableList[vmobject[i].currentIdx])
                {
                    if ((vmobject[i].flags & 0x8))
                    {
                        vmobject[i].curVMOffsetTable = (struct _VMOffsetTable*)MEMPACK_Malloc(num * 6 + 4, 0x28);
                        vmobject[i].curVMOffsetTable->numVMOffsets = num;
                    }
                    else
                    {
                        vmobject[i].curVMOffsetTable = (struct _VMOffsetTable*)MEMPACK_Malloc(num * 3 + 4, 0x28);
                        vmobject[i].curVMOffsetTable->numVMOffsets = num;
                    }
                }

                if ((vmobject[i].flags & 0x8))
                {
                    struct _VMOffset* material;
                    struct _VMOffset* spectral;
                    struct _VMOffset* offset;

                    material = &vmobject[i].vmoffsetTableList[vmobject[i].materialIdx]->offsets.moveOffsets;

                    spectral = &vmobject[i].vmoffsetTableList[vmobject[i].spectralIdx]->offsets.moveOffsets;

                    offset = &vmobject[i].curVMOffsetTable->offsets.moveOffsets;

                    for (j = 0; j < num; j++)
                    {
                        offset[j].dx = material[j].dx + (((spectral[j].dx - material[j].dx) * ratio) >> 12);
                        offset[j].dy = material[j].dy + (((spectral[j].dy - material[j].dy) * ratio) >> 12);
                        offset[j].dz = material[j].dz + (((spectral[j].dz - material[j].dz) * ratio) >> 12);
                    }
                }
                else
                {
                    struct _VMColorOffset* material;
                    struct _VMColorOffset* spectral;
                    struct _VMColorOffset* offset;

                    material = &vmobject[i].vmoffsetTableList[vmobject[i].materialIdx]->offsets.colorOffsets;

                    spectral = &vmobject[i].vmoffsetTableList[vmobject[i].spectralIdx]->offsets.colorOffsets;

                    offset = &vmobject[i].curVMOffsetTable->offsets.colorOffsets;

                    for (j = 0; j < num; j++)
                    {
                        if ((vmobject[i].flags & 0x100))
                        {
                            dr = spectral[j].db - spectral[j].dr;
                        }
                        else
                        {
                            dr = spectral[j].dr - material[j].dr;
                        }

                        dg = spectral[j].db - material[j].dg;
                        db = spectral[j].dr - material[j].db;

                        offset[j].dr = material[j].dr + ((dr * ratio) >> 12);
                        offset[j].dg = material[j].dg + ((dg * ratio) >> 12);
                        offset[j].db = material[j].db + ((db * ratio) >> 12);
                    }
                }
            }
        }
    }
}


// autogenerated function stub: 
// void /*$ra*/ VM_VMObjectSetTable(struct Level *level /*$a0*/, struct _VMObject *vmobject /*$s0*/, int table /*$s1*/)
void VM_VMObjectSetTable(struct Level *level, struct _VMObject *vmobject, int table)
{ // line 521, offset 0x8004fa30
#if defined(PC_VERSION)
	struct _VMOffsetTable** vmoffsetTableList; // ecx

	if (vmobject->curVMOffsetTable != vmobject->vmoffsetTableList[vmobject->currentIdx])
		MEMPACK_Free((char*)vmobject->curVMOffsetTable);
	vmoffsetTableList = vmobject->vmoffsetTableList;
	vmobject->currentIdx = table;
	vmobject->curVMOffsetTable = vmoffsetTableList[table];
#else
	UNIMPLEMENTED();
#endif
}
