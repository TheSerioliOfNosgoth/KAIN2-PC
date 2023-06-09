#ifndef STATE_H
#define STATE_H

#include "PLAYER.H"
#include "MONSTER/MONSTER.H"
#include "PHYSOBS.H"
#include "Game/EVENT.H"

struct evMonsterSoulSuckData 
{
	struct _Instance* sender; // size=668, offset=0
	struct _Position Destination; // size=6, offset=4
};

struct evAnimationControllerDoneData 
{
	struct _Instance* instance; // size=668, offset=0
	long segment; // size=0, offset=4
	long type; // size=0, offset=8
	int data; // size=0, offset=12
};


typedef void (*TDRFuncPtr_StateSwitchStateCharacterData1NewProcess)();

typedef void (*TDRFuncPtr_StateSwitchStateCharacterDataDefault1NewProcess)();

typedef void (*TDRFuncPtr_StateSwitchStateData2NewProcess)();

typedef void (*TDRFuncPtr_StateSwitchStateDataDefault2NewProcess)();

extern void InitMessageQueue(struct __MessageQueue *In); // 0x8007071C

extern struct __Event * DeMessageQueue(struct __MessageQueue *In); // 0x80070728

extern void PurgeMessageQueue(struct __MessageQueue *In); // 0x80070764

extern struct __Event * PeekMessageQueue(struct __MessageQueue *In); // 0x80070770

extern void EnMessageQueue(struct __MessageQueue *In, struct __Event *Element); // 0x80070798

extern void EnMessageQueueData(struct __MessageQueue *In, int ID, int Data); // 0x800707C4

extern void * CIRC_Alloc(int size); // 0x80070840

extern intptr_t SetCollideInfoData(struct _CollideInfo *srcCI); // 0x80070884

extern intptr_t SetMonsterHitData(struct _Instance *Sender, struct _Instance *lastHit, int Power, int knockBackDistance, int knockBackFrames); // 0x800708E0

extern intptr_t SetMonsterThrownData(struct _Instance *Sender, struct _Rotation *Direction, int Power); // 0x8007094C

extern intptr_t SetMonsterAlarmData(struct _Instance *sender, _Position *position, int type); // 0x800709B4

extern intptr_t SetMonsterSoulSuckData(struct _Instance *Sender, int x, int y, int z); // 0x80070A1C

extern intptr_t SetMonsterImpaleData(struct _Instance *weapon, struct _Rotation *direction, _Position *position, int distance); // 0x80070A78

extern intptr_t SetObjectData(int x, int y, int PathNumber, struct _Instance *Force, int node); // 0x80070B10

extern intptr_t SetPositionData(int x, int y, int z); // 0x80070B7C

extern intptr_t SetPhysicsGravityData(int UpperOffset, int LowerOffset, int x, int y, int z, int slope); // 0x80070BC8

extern intptr_t SetPhysicsEdgeData(int UpperOffset, int ForwardOffset, int AboveOffset, int x, int y, int z, struct _SVector *Normal1, struct _SVector *Normal2, struct _SVector *Delta); // 0x80070C44

extern intptr_t SetPhysicsSwimData(int CheckDepth, struct _SVector *iVelocity, int SwimDepth, int WadeDepth, int TreadDepth); // 0x80070CF0

extern intptr_t SetPhysicsDropOffData(int xOffset, int yOffset, int DropOffset, int slipSlope, int UpperOffset); // 0x80070D5C

extern intptr_t SetPhysicsSlideData(int Segment, int ForwardVectorX, int ForwardVectorY, int ForwardVectorZ, int DropOffset, int UpperOffset, int Height); // 0x80070DC8

extern intptr_t SetPhysicsWallCrawlData(int Segment, int Length, int ForwardOffset, int NormalDistance); // 0x80070E54

extern intptr_t SetPhysicsLinkedMoveData(struct _Instance *instance, int segment, struct _SVector *posDelta, struct _SVector *rotDelta); // 0x80070EB0

extern intptr_t SetPhysicsDropHeightData(_Position *offset, int dropOffset, int mode); // 0x80070F50

extern intptr_t SetAnimationControllerDoneData(struct _Instance *instance, long segment, long type, int data); // 0x80070FC0

extern intptr_t SetAnimationInstanceSwitchData(struct _Instance *instance, int anim, int frame, int frames, int mode); // 0x8007101C

extern intptr_t SetFXHitData(struct _Instance *hitter, int segment, int amount, int type); // 0x80071088

extern intptr_t SetObjectThrowData(void *target, struct _SVector *angularVel, unsigned short type, unsigned short spinType, int speed, int gravity, int zVel, int initialXRot); // 0x80071184

extern intptr_t SetObjectBreakOffData(struct _Instance *force, short node, short distance, short animation, int frame, int type, int action); // 0x800712F0

extern intptr_t SetControlInitHangData(struct _Instance *instance, long frame, long frames); // 0x8007137C

extern intptr_t SetControlInitIdleData(int mode, long frame, long frames); // 0x800713C8

extern intptr_t SetObjectDraftData(short force, unsigned short radius, unsigned short radiusCoef, unsigned short height, int maxVelocity); // 0x80071414

extern intptr_t SetObjectAbsorbData(struct _Instance *force, unsigned short node, unsigned short steps); // 0x80071480

extern intptr_t SetControlSaveDataData(long length, void *data); // 0x800714CC

extern intptr_t SetObjectIdleData(long mode, struct _Instance *instance); // 0x80071508

extern intptr_t SetActionPlayHostAnimationData(struct _Instance *instance, struct _Instance *host, int newAnim, int newFrame, int frames, int mode); // 0x80071544

extern intptr_t SetObjectBirthProjectileData(struct _Instance *instance, int joint, int type); // 0x800715C0

extern intptr_t SetShadowSegmentData(unsigned long total); // 0x80071610

extern void G2EmulationInit(); // 0x8007163C

extern void G2EmulationInstancePlayAnimation(struct _Instance *instance); // 0x80071828

extern void G2EmulatePlayAnimation(struct __CharacterState *In); // 0x80071890

extern void G2EmulationInstanceToInstanceSwitchAnimation(struct _Instance *instance, struct _Instance *host, int CurrentSection, int NewAnim, int NewFrame, int Frames, int Mode); // 0x800718B4

extern void G2EmulationInstanceSwitchAnimation(struct _Instance *instance, int CurrentSection, int NewAnim, int NewFrame, int Frames, int Mode); // 0x800719AC

extern void G2EmulationInstanceSwitchAnimationAlpha(struct _Instance *instance, int CurrentSection, int NewAnim, int NewFrame, int Frames, int Mode, int AlphaTable); // 0x80071AA0

extern void G2EmulationSwitchAnimation(struct __CharacterState *In, int CurrentSection, int NewAnim, int NewFrame, int Frames, int Mode); // 0x80071B0C

extern void G2EmulationSwitchAnimationAlpha(struct __CharacterState *In, int CurrentSection, int NewAnim, int NewFrame, int Frames, int Mode, int AlphaTable); // 0x80071B50

extern void G2EmulationSwitchAnimationSync(struct __CharacterState *In, int SlaveSectionID, int MasterSectionID, int Frames); // 0x80071BC4

extern void G2EmulationInstanceToInstanceSwitchAnimationCharacter(struct _Instance *instance, struct _Instance *host, int NewAnim, int NewFrame, int Frames, int Mode); // 0x80071D90

extern void G2EmulationSwitchAnimationCharacter(struct __CharacterState *In, int NewAnim, int NewFrame, int Frames, int Mode); // 0x80071E7C

extern void G2EmulationInstanceSetAnimation(struct _Instance *instance, int CurrentSection, int NewAnim, int NewFrame, int Frames); // 0x80071F70

extern void G2EmulationSetAnimation(struct __CharacterState *In, int CurrentSection, int NewAnim, int NewFrame, int Frames); // 0x80072018

extern void G2EmulationInstanceSetMode(struct _Instance *instance, int CurrentSection, int Mode); // 0x80072050

extern void G2EmulationSetMode(struct __CharacterState *In, int CurrentSection, int Mode); // 0x800720D0

extern void G2EmulationInstanceSetAnimSpeed(struct _Instance *instance, int CurrentSection, int speed); // 0x800720F4

extern int G2EmulationInstanceQueryAnimation(struct _Instance *instance, int CurrentSection); // 0x80072110

extern int G2EmulationQueryAnimation(struct __CharacterState *In, int CurrentSection); // 0x80072130

extern int G2EmulationInstanceQueryFrame(struct _Instance *instance, int CurrentSection); // 0x80072154

extern int G2EmulationInstanceQueryLastFrame(struct _Instance *instance, int CurrentSection); // 0x80072188

extern int G2EmulationInstanceQueryPassedFrame(struct _Instance *instance, int CurrentSection, int frame); // 0x800721BC

extern int G2EmulationQueryFrame(struct __CharacterState *In, int CurrentSection); // 0x80072264

extern int G2EmulationInstanceQueryMode(struct _Instance *instance, int CurrentSection); // 0x80072288

extern int G2EmulationQueryMode(struct __CharacterState *In, int CurrentSection); // 0x800722D0

extern void G2EmulationInstanceSetStartAndEndSegment(struct _Instance *instance, int CurrentSection, short Start, short End); // 0x800722F4

extern void G2EmulationSetStartAndEndSegment(struct __CharacterState *In, int CurrentSection, short Start, short End); // 0x80072320

extern void G2EmulationInstanceSetTotalSections(struct _Instance *instance, short Total); // 0x80072350

extern void G2EmulationSetTotalSections(struct __CharacterState *In, short Total); // 0x800723D4

extern void G2EmulationInstanceInitSection(struct _Instance *instance, int CurrentSection, void *callback, void *data); // 0x80072404

extern void G2EmulationSetInterpController_Vector(struct _Instance *instance, long segment, long type, struct _G2SVector3_Type *vec, int Frames, int Data); // 0x80072428

extern void StateSwitchStateDataDefault(struct __CharacterState *In, int CurrentSection, void (*NewProcess)(struct __CharacterState* In, int CurrentSection, int Data), int Data); // 0x800724B0

extern void StateSwitchStateCharacterDataDefault(struct __CharacterState *In, void(*NewProcess)(struct __CharacterState* In, int CurrentSection, int Data), int Data); // 0x80072518

extern void StateSwitchStateData(struct __CharacterState *In, int CurrentSection, void (*NewProcess)(struct __CharacterState* In, int CurrentSection, int Data), int Data); // 0x80072590

extern void StateSwitchStateCharacterData(struct __CharacterState *In, void (*NewProcess)(struct __CharacterState* In, int CurrentSection, int Data), int Data); // 0x8007265C

extern void StateGovernState(struct __CharacterState *In, int Frames); // 0x80072750

#endif
