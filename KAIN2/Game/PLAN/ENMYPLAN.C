#include "Game/CORE.H"
#include "ENMYPLAN.H"
#include "PLANAPI.H"

void ENMYPLAN_InitEnemyPlanPool(void* enemyPlanPool)//Matching - 100%
{
	int i;

	for (i = 0; i < 10; i++)
	{
		((struct EnemyPlanSlotData*)enemyPlanPool)[i].slotInUse = 0;
	}
}

int ENMYPLAN_GetNextAvailablePlanningSlot()
{
	int slotID;
	int i;
	
	slotID = -1;

	for (i = 0; i < 10; i++)
	{
		if (((struct EnemyPlanSlotData*)gameTrackerX.enemyPlanPool)[i].slotInUse == 0)
		{
			return i;
		}
	}

	return slotID;
}

int ENMYPLAN_GetInitializedPlanningWorkspaceFinal()//Matching - 99.57%
{
	struct EnemyPlanSlotData* pool;
	int slotID;

	pool = (struct EnemyPlanSlotData*)gameTrackerX.enemyPlanPool;

	slotID = ENMYPLAN_GetNextAvailablePlanningSlot();
	
	if (slotID != -1)
	{
		pool[slotID].slotInUse = 1;
		pool[slotID].state = 0;
	}

	return slotID;
}


// autogenerated function stub: 
// void /*$ra*/ ENMYPLAN_ReleasePlanningWorkspace(int slotID /*$s0*/)
void ENMYPLAN_ReleasePlanningWorkspace(int slotID)
{ // line 185, offset 0x80096660
	/* begin block 1 */
		// Start line: 186
		// Start offset: 0x80096660
		// Variables:
			struct EnemyPlanSlotData *pool; // $s1
	/* end block 1 */
	// End offset: 0x800966B4
	// End Line: 203

	/* begin block 2 */
		// Start line: 376
	/* end block 2 */
	// End Line: 377
			UNIMPLEMENTED();
}


// autogenerated function stub: 
// int /*$ra*/ ENMYPLAN_WayPointSkipped(_Position *currentPos /*$a0*/, _Position *targetPos /*$s0*/, _Position *nextTargetPos /*$s1*/)
int ENMYPLAN_WayPointSkipped(_Position *currentPos, _Position *targetPos, _Position *nextTargetPos)
{ // line 208, offset 0x800966c8
	/* begin block 1 */
		// Start line: 209
		// Start offset: 0x800966C8
		// Variables:
			long range[2]; // stack offset -40
			//_Position vector[2]; // stack offset -32

		/* begin block 1.1 */
			// Start line: 209
			// Start offset: 0x800966C8
			// Variables:
				short _x0; // $v1
				short _y0; // $v0
				short _z0; // $a1
				short _x1; // $a2
				short _y1; // $a3
				short _z1; // $t0
				_Position *_v; // $a0
		/* end block 1.1 */
		// End offset: 0x800966C8
		// End Line: 209

		/* begin block 1.2 */
			// Start line: 209
			// Start offset: 0x800966C8
			// Variables:
		/* end block 1.2 */
		// End offset: 0x800966C8
		// End Line: 209
	/* end block 1 */
	// End offset: 0x800967A0
	// End Line: 225

	/* begin block 2 */
		// Start line: 423
	/* end block 2 */
	// End Line: 424
				UNIMPLEMENTED();
	return 0;
}


// autogenerated function stub: 
// int /*$ra*/ ENMYPLAN_WayPointReached(_Position *currentPos /*$v1*/, _Position *oldCurrentPos /*$s1*/, _Position *targetPos /*$s0*/)
int ENMYPLAN_WayPointReached(_Position *currentPos, _Position *oldCurrentPos, _Position *targetPos)
{ // line 235, offset 0x80096834
	/* begin block 1 */
		// Start line: 236
		// Start offset: 0x80096834
		// Variables:
			long range[2]; // stack offset -24
	/* end block 1 */
	// End offset: 0x800968D0
	// End Line: 249

	/* begin block 2 */
		// Start line: 487
	/* end block 2 */
	// End Line: 488

	return 0;
}

void ENMYPLAN_Replan(struct EnemyPlanSlotData* planSlot)
{
	planSlot->state = 0;

	PLANAPI_DeleteNodesFromPoolByType(2);

	PLANAPI_DeleteNodesFromPoolByType(3);
}


// autogenerated function stub: 
// int /*$ra*/ ENMYPLAN_PathClear(_Position *pos /*$s1*/, _Position *target /*$s0*/)
int ENMYPLAN_PathClear(_Position *pos, _Position *target)
{ // line 274, offset 0x80096910
	/* begin block 1 */
		// Start line: 275
		// Start offset: 0x80096910
		// Variables:
			int len; // $a1
			int oldPCO; // $s2
			_Position *tpos; // $a1
			//_Position newTarget; // stack offset -24
	/* end block 1 */
	// End offset: 0x80096A68
	// End Line: 304

	/* begin block 2 */
		// Start line: 566
	/* end block 2 */
	// End Line: 567
			UNIMPLEMENTED();
	return 0;
}


// autogenerated function stub: 
// int /*$ra*/ ENMYPLAN_MoveToTargetFinal(struct _Instance *instance /*stack 0*/, _Position *outputPos /*stack 4*/, int slotID /*$a2*/, _Position *targetPos /*$s1*/, int validNodeTypes /*stack 16*/)
int ENMYPLAN_MoveToTargetFinal(struct _Instance *instance, _Position *outputPos, int slotID, _Position *targetPos, int validNodeTypes)
{ // line 313, offset 0x80096a90
	/* begin block 1 */
		// Start line: 314
		// Start offset: 0x80096A90
		// Variables:
			struct EnemyPlanSlotData *pool; // $a0
			struct EnemyPlanSlotData *planSlot; // $s0
			struct EnemyPlanData *planData; // $s5
			int nextWayPointType; // $a0
			int nextNextWayPointType; // $s2
			int pathFound; // $v0
			int nextWayPointIdx; // $s1
			int nextNextWayPointIdx; // $s4
			int nextWayPointSkip; // $a3
			int i; // $v1
			_Position *nextWayPointPos; // $s6
			_Position *nextNextWayPointPos; // $fp
	/* end block 1 */
	// End offset: 0x80096F6C
	// End Line: 540

	/* begin block 2 */
		// Start line: 664
	/* end block 2 */
	// End Line: 665
			UNIMPLEMENTED();
	return 0;
}

int ValidSlotAndState(struct EnemyPlanSlotData* pool, int slotID)
{
	if (slotID != -1 && slotID < 10)
	{
		return (unsigned)((pool + slotID)->state - 2) < 2;
	}

	return 0;
}


// autogenerated function stub: 
// int /*$ra*/ ENMYPLAN_GetNodeTypeOfNextWaypoint(int slotID /*$s0*/)
int ENMYPLAN_GetNodeTypeOfNextWaypoint(int slotID)
{ // line 555, offset 0x80096fe0
	/* begin block 1 */
		// Start line: 556
		// Start offset: 0x80096FE0
		// Variables:
			struct EnemyPlanSlotData *pool; // $s1
			struct EnemyPlanSlotData *planSlot; // $v0
	/* end block 1 */
	// End offset: 0x80097038
	// End Line: 568

	/* begin block 2 */
		// Start line: 1232
	/* end block 2 */
	// End Line: 1233
			UNIMPLEMENTED();
	return 0;
}


// autogenerated function stub: 
// int /*$ra*/ ENMYPLAN_GetPosOfNextWaypoint(int slotID /*$s0*/, _Position *pos /*$s2*/)
int ENMYPLAN_GetPosOfNextWaypoint(int slotID, _Position *pos)
{ // line 570, offset 0x8009704c
	/* begin block 1 */
		// Start line: 571
		// Start offset: 0x8009704C
		// Variables:
			struct EnemyPlanSlotData *pool; // $s1
			struct EnemyPlanSlotData *planSlot; // $v1

		/* begin block 1.1 */
			// Start line: 575
			// Start offset: 0x80097080
			// Variables:
				short _x1; // $a0
				short _y1; // $a1
				short _z1; // $v1
				_Position *_v1; // $v1
		/* end block 1.1 */
		// End offset: 0x80097080
		// End Line: 575
	/* end block 1 */
	// End offset: 0x800970D4
	// End Line: 584

	/* begin block 2 */
		// Start line: 1270
	/* end block 2 */
	// End Line: 1271
				UNIMPLEMENTED();
	return 0;
}


// autogenerated function stub: 
// void /*$ra*/ ENMYPLAN_RelocatePlanPositions(int slotID /*$a0*/, _Position *offset /*$t2*/)
void ENMYPLAN_RelocatePlanPositions(int slotID, _Position *offset)
{ // line 641, offset 0x800970ec
	/* begin block 1 */
		// Start line: 642
		// Start offset: 0x800970EC
		// Variables:
			struct EnemyPlanSlotData *pool; // $v1
			struct EnemyPlanSlotData *planSlot; // $t1
			_Position *pos; // $a0
			int i; // $a3
			int numWayPoints; // $v1

		/* begin block 1.1 */
			// Start line: 659
			// Start offset: 0x80097140
			// Variables:
				short _x0; // $v0
				short _y0; // $v0
				short _z0; // $v1
				short _x1; // $v1
				short _y1; // $a1
				short _z1; // $a2
		/* end block 1.1 */
		// End offset: 0x80097140
		// End Line: 659
	/* end block 1 */
	// End offset: 0x80097180
	// End Line: 663

	/* begin block 2 */
		// Start line: 1282
	/* end block 2 */
	// End Line: 1283

	/* begin block 3 */
		// Start line: 1370
	/* end block 3 */
	// End Line: 1371
				UNIMPLEMENTED();
}




