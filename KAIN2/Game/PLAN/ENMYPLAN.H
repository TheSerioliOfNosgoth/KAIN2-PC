#ifndef ENMYPLAN_H
#define ENMYPLAN_H

#include "PLANAPI.H"

extern void ENMYPLAN_InitEnemyPlanPool(void *enemyPlanPool); // 0x800965A4

extern int ENMYPLAN_GetNextAvailablePlanningSlot(); // 0x800965C4

extern int ENMYPLAN_GetInitializedPlanningWorkspaceFinal(); // 0x80096604

extern void ENMYPLAN_ReleasePlanningWorkspace(int slotID); // 0x80096660

extern int ENMYPLAN_WayPointSkipped(_Position *currentPos, _Position *targetPos, _Position *nextTargetPos); // 0x800966C8

extern int ENMYPLAN_WayPointReached(_Position *currentPos, _Position *oldCurrentPos, _Position *targetPos); // 0x80096834

extern void ENMYPLAN_Replan(struct EnemyPlanSlotData *planSlot); // 0x800968E4

extern int ENMYPLAN_PathClear(_Position *pos, _Position *target); // 0x80096910

extern int ENMYPLAN_MoveToTargetFinal(struct _Instance *instance, _Position *outputPos, int slotID, _Position *targetPos, int validNodeTypes); // 0x80096A90

extern int ValidSlotAndState(struct EnemyPlanSlotData *pool, int slotID); // 0x80096F9C

extern int ENMYPLAN_GetNodeTypeOfNextWaypoint(int slotID); // 0x80096FE0

extern int ENMYPLAN_GetPosOfNextWaypoint(int slotID, _Position *pos); // 0x8009704C

extern void ENMYPLAN_RelocatePlanPositions(int slotID, _Position *offset); // 0x800970EC


#endif
