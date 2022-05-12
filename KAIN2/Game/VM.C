#include "CORE.H"
#include "VM.H"

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


// autogenerated function stub: 
// void /*$ra*/ VM_UpdateMorph(struct Level *level /*$a0*/, int initFlg /*$s5*/)
void VM_UpdateMorph(struct Level *level, int initFlg)
{ // line 295, offset 0x8004f658
	/* begin block 1 */
		// Start line: 296
		// Start offset: 0x8004F658
		// Variables:
			struct _VMObject *vmobject; // $s3
			int i; // $s4

		/* begin block 1.1 */
			// Start line: 305
			// Start offset: 0x8004F6B4
			// Variables:
				struct _VMOffsetTable *curTable; // $a0

			/* begin block 1.1.1 */
				// Start line: 308
				// Start offset: 0x8004F6C4
			/* end block 1.1.1 */
			// End offset: 0x8004F738
			// End Line: 337

			/* begin block 1.1.2 */
				// Start line: 341
				// Start offset: 0x8004F754
				// Variables:
					short ratio; // $s2
					int j; // $t1
					long num; // $s1

				/* begin block 1.1.2.1 */
					// Start line: 353
					// Start offset: 0x8004F778
					// Variables:
						long len; // $a0
				/* end block 1.1.2.1 */
				// End offset: 0x8004F7B0
				// End Line: 360

				/* begin block 1.1.2.2 */
					// Start line: 362
					// Start offset: 0x8004F7C4
					// Variables:
						struct _VMOffset *material; // $a1
						struct _VMOffset *spectral; // $a0
						struct _VMOffset *offset; // $v1
				/* end block 1.1.2.2 */
				// End offset: 0x8004F898
				// End Line: 374

				/* begin block 1.1.2.3 */
					// Start line: 374
					// Start offset: 0x8004F8A0
					// Variables:
						short dr; // $a3
						short dg; // $a0
						short db; // $v1
						//struct _VMColorOffset *material; // $a1
						//struct _VMColorOffset *spectral; // $a0
						//struct _VMColorOffset *offset; // $v1
				/* end block 1.1.2.3 */
				// End offset: 0x8004F9FC
				// End Line: 403
			/* end block 1.1.2 */
			// End offset: 0x8004F9FC
			// End Line: 405
		/* end block 1.1 */
		// End offset: 0x8004F9FC
		// End Line: 406
	/* end block 1 */
	// End offset: 0x8004FA0C
	// End Line: 408

	/* begin block 2 */
		// Start line: 590
	/* end block 2 */
	// End Line: 591

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
#endif
}