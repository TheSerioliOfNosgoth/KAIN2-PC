#include "Game/CORE.H"
#include "CONTROL.H"
#include "Game/RAZIEL/RAZIEL.H"

struct __Force* dword_B08390;
int PhysicsMode;
struct __Force* ExternalForcesPtr = &ExternalForces[0];

// autogenerated function stub: 
// void /*$ra*/ SetPhysics(struct _Instance *instance /*$s0*/, short gravity /*$a1*/, long x /*$s1*/, long y /*$s2*/, long z /*stack 16*/)
void SetPhysics(struct _Instance *instance, short gravity, long x, long y, long z)
{ // line 27, offset 0x8009a1b0
#if defined(PC_VERSION)
	struct __Force* v5; // eax

	v5 = dword_B08390;
	dword_B08390->LinearForce.x = 0;
	v5->LinearForce.y = 0;
	v5->LinearForce.z = gravity;
	v5->Friction = 4096;
	v5->Type = 0;
	instance->xVel = x;
	instance->yVel = y;
	instance->zVel = z;
#else
	UNIMPLEMENTED();
#endif
}

void ResetPhysics(struct _Instance *instance, short gravity)
{
#if defined(PSX_VERSION)

	int i;

	SetExternalForce(ExternalForcesPtr, 0, 0, gravity, 0, 4096);
	
	for(i = 1; i < 4; i++)
	{
		SetExternalForce(ExternalForcesPtr + i, 0, 0, 0, 0, 0);
	}

	instance->xVel = 0;
	instance->yVel = 0;
	instance->zVel = 0;
	instance->xAccl = 0;
	instance->yAccl = 0;
	instance->zAccl = gravity;

#elif defined(PC_VERSION)
	struct __Force* v2; // eax
	int v3; // ecx
	struct __Force* v4; // eax
	struct __Force* v5; // eax

	v2 = dword_B08390;
	dword_B08390->LinearForce.z = gravity;
	v2->LinearForce.x = 0;
	v2->LinearForce.y = 0;
	v2->Friction = 4096;
	v2->Type = 0;
	v3 = 1;
	do
	{
		v4 = dword_B08390;
		dword_B08390[v3].LinearForce.x = 0;
		v5 = &v4[v3++];
		v5->LinearForce.y = 0;
		v5->LinearForce.z = 0;
		v5->Friction = 0;
		v5->Type = 0;
	} while (v3 < 4);
	instance->zAccl = gravity;
	instance->xVel = 0;
	instance->yVel = 0;
	instance->zVel = 0;
	instance->xAccl = 0;
	instance->yAccl = 0;
#else
	UNIMPLEMENTED();
#endif
}


// autogenerated function stub: 
// void /*$ra*/ SetDampingPhysics(struct _Instance *instance /*$a0*/, int damping /*$a1*/)
void SetDampingPhysics(struct _Instance *instance, int damping)
{ // line 55, offset 0x8009a2e0
#if defined(PC_VERSION)
	struct __Force* v3; // eax

	instance->xAccl = damping * instance->xVel / -4096;
	instance->yAccl = damping * instance->yVel / -4096;
	instance->zAccl = damping * instance->zVel / -4096;
	v3 = dword_B08390;
	v3->LinearForce.x = instance->xAccl;
	v3->LinearForce.y = instance->yAccl;
	v3->LinearForce.z = instance->zAccl;
	v3->Friction = 4096;
	v3->Type = 0;
#else
	UNIMPLEMENTED();
#endif
}

void SetImpulsePhysics(struct _Instance* instance, struct __Player* player)//Matching - 52.50%
{
#if defined(PSX_VERSION)
	int vLength;
	int Dot;

	if (!(player->Mode & 0x40000))
	{
		Dot = (-instance->offset.x * player->iVelocity.x) + (-instance->offset.y * player->iVelocity.y) + (-instance->offset.z * player->iVelocity.z);
		vLength = (player->iVelocity.x * player->iVelocity.x) + (player->iVelocity.y * player->iVelocity.y) + (player->iVelocity.z * player->iVelocity.z);
		if (vLength)
		{
			instance->position.x += instance->offset.x + Dot * player->iVelocity.x / vLength;
			instance->position.y += instance->offset.y + Dot * player->iVelocity.y / vLength;
			instance->position.z += instance->offset.z + Dot * player->iVelocity.z / vLength;
		}
	}
#elif defined(PC_VERSION)
	int z; // esi
	int x; // edx
	int y; // eax
	int dot; // ecx
	int len; // esi

	if ((player->Mode & 0x40000) == 0)
	{
		z = player->iVelocity.z;
		x = player->iVelocity.x;
		y = player->iVelocity.y;
		dot = -(y * instance->offset.y + z * instance->offset.z + x * instance->offset.x);
		len = x * x + y * y + z * z;
		if (len)
		{
			instance->position.x += instance->offset.x + x * dot / len;
			instance->position.y += instance->offset.y + player->iVelocity.y * dot / len;
			instance->position.z += instance->offset.z + player->iVelocity.z * dot / len;
		}
	}
#endif
}

void SetDropPhysics(struct _Instance* instance, struct __Player* player)
{
#if defined(PSX_VERSION)
	SetExternalForce(ExternalForcesPtr, 0, 4, -16, 0, 4096);
#elif defined(PC_VERSION)
	struct __Force* v2; // eax

	v2 = dword_B08390;
	dword_B08390->LinearForce.x = 0;
	v2->LinearForce.y = 4;
	v2->LinearForce.z = -16;
	v2->Friction = 4096;
	v2->Type = 0;
#endif
}

// unused
void GetPhysicsVelocity(struct _Instance* instance, SVECTOR* in_pos, SVECTOR* out_pos)
{
#if defined(PC_VERSION)
	MATRIX tp;
	TransposeMatrix(instance->matrix, &tp);
	ApplyMatrixSV(&tp, in_pos, out_pos);
#else
	UNIMPLEMENTED();
#endif
}

void InitExternalForces(struct __Force* Forces, int MaxForces)
{
#if defined(PSX_VERSION)
	int i;

	MaxForces -= 1;

	for (i = MaxForces - 1; i != 0; i--)
	{
		Forces[i].Friction = 0;
		Forces[i].LinearForce.x = 0;
		Forces[i].LinearForce.y = 0;
		Forces[i].LinearForce.z = 0;
		Forces[i].Type = 0;
	}

	ExternalForcesPtr = Forces;

#elif defined(PC_VERSION)
	int v2; // edx
	struct __Force* f; // eax

	v2 = MaxForces - 1;
	if (MaxForces != 1)
	{
		f = &Forces[v2];
		do
		{
			f->Friction = 0;
			f->LinearForce.x = 0;
			f->LinearForce.y = 0;
			f->LinearForce.z = 0;
			f--;
			--v2;
		} while (v2);
	}
	dword_B08390 = Forces;
#endif
}

void SetExternalForce(struct __Force* In, short x, short y, short z, int Space, int Friction)
{
#if defined(PSX_VERSION)
	In->LinearForce.x = x;
	In->LinearForce.y = y;
	In->LinearForce.z = z;
	In->Friction = Friction;
	In->Type = Space;
#elif defined(PC_VERSION)
	In->LinearForce.x = x;
	In->LinearForce.y = y;
	In->LinearForce.z = z;
	In->Friction = Friction;
	In->Type = (__int16)Space;
#endif
}


// autogenerated function stub: 
// void /*$ra*/ SetExternalTransitionForce(struct __Force *in /*$a0*/, struct _Instance *instance /*$a1*/, int time /*$a2*/, int x /*$a3*/, int y /*stack 16*/, int z /*stack 20*/)
void SetExternalTransitionForce(struct __Force *in, struct _Instance *instance, int time, int x, int y, int z)
{ // line 173, offset 0x8009a570
#if defined(PC_VERSION)
	int zVel; // edx

	in->Type = 2;
	in->LinearForce.x = (x - instance->xVel) / time;
	in->LinearForce.y = (y - instance->yVel) / time;
	zVel = instance->zVel;
	in->Friction = time;
	in->LinearForce.z = (z - zVel) / time;
#else
	UNIMPLEMENTED();
#endif
}

void ProcessPhysics(struct __Player* player, struct __CharacterState* In, int CurrentSection, int Mode)
{
#if defined(PSX_VERSION)

	int time;

	if (In->CharacterInstance->matrix != NULL)
	{
		time = (In->CharacterInstance->anim.section[0].speedAdjustment * gameTrackerX.timeMult) >> 12;

		switch (Mode)
		{
		case 0:
			
			ApplyExternalLocalForces(player, In->CharacterInstance, ExternalForcesPtr, 4, (struct _Vector*)&In->CharacterInstance->xAccl);
			
			PhysicsMoveLocalZClamp(In->CharacterInstance, player->RotationSegment, time, 0);
			break;
		case 4:

			ApplyExternalLocalForces(player, In->CharacterInstance, ExternalForcesPtr, 4, (struct _Vector*)&In->CharacterInstance->xAccl);

			PhysicsMoveLocalZClamp(In->CharacterInstance, player->RotationSegment, time, 0);

			PHYSICS_StopIfCloseToTarget(In->CharacterInstance, 0, 0, 0);

			if (In->CharacterInstance->xAccl == 0 &&
				In->CharacterInstance->yAccl == 0 &&
				In->CharacterInstance->zAccl == 0)
			{
				SetExternalForce(ExternalForcesPtr, 0, 0, 0, 0, 0);
			}

			break;
		case 5:
			PhysicsMoveLocalZClamp(In->CharacterInstance, player->RotationSegment, time, 0);

			PHYSICS_StopIfCloseToTarget(In->CharacterInstance, 0, 0, player->swimTargetSpeed);

			if (In->CharacterInstance->xAccl == 0 &&
				In->CharacterInstance->yAccl == 0 &&
				In->CharacterInstance->zAccl == 0)
			{
				INSTANCE_Post(In->CharacterInstance, 0x100011, player->swimTargetSpeed);
			}

			break;
		case 6:
			PhysicsMoveLocalZClamp(In->CharacterInstance, player->RotationSegment, time, 1);

			PHYSICS_StopIfCloseToTarget(In->CharacterInstance, 0, 0, player->swimTargetSpeed);

			if (In->CharacterInstance->xAccl == 0 &&
				In->CharacterInstance->yAccl == 0 &&
				In->CharacterInstance->zAccl == 0)
			{
				INSTANCE_Post(In->CharacterInstance, 0x100011, player->swimTargetSpeed);
			}

			break;
		}
	}

#elif defined(PC_VERSION)
	struct _Instance* CharacterInstance; // esi
	unsigned int v5; // edi
	struct _Instance* v6; // ebx
	struct __Force* v7; // eax
	struct __Player* v8; // edi

	CharacterInstance = In->CharacterInstance;
	if (In->CharacterInstance->matrix)
	{
		v5 = (gameTrackerX.timeMult * CharacterInstance->anim.section[0].speedAdjustment) >> 12;
		switch (Mode)
		{
		case 0:
			ApplyExternalLocalForces(player, CharacterInstance, dword_B08390, 4, &CharacterInstance->xAccl);
			PhysicsMoveLocalZClamp(In->CharacterInstance, player->RotationSegment, v5, 0);
			break;
		case 4:
			ApplyExternalLocalForces(player, CharacterInstance, dword_B08390, 4, &CharacterInstance->xAccl);
			PhysicsMoveLocalZClamp(In->CharacterInstance, player->RotationSegment, v5, 0);
			PHYSICS_StopIfCloseToTarget(In->CharacterInstance, 0, 0, 0);
			v6 = In->CharacterInstance;
			if (!In->CharacterInstance->xAccl && !v6->yAccl && !v6->zAccl)
			{
				v7 = dword_B08390;
				dword_B08390->LinearForce.x = 0;
				v7->LinearForce.y = 0;
				v7->LinearForce.z = 0;
				v7->Friction = 0;
				v7->Type = 0;
			}
			break;
		case 5:
			v8 = player;
			PhysicsMoveLocalZClamp(
				CharacterInstance,
				player->RotationSegment,
				(gameTrackerX.timeMult * CharacterInstance->anim.section[0].speedAdjustment) >> 12,
				0);
			PHYSICS_StopIfCloseToTarget(CharacterInstance, 0, 0, player->swimTargetSpeed);
			if (!CharacterInstance->xAccl && !CharacterInstance->yAccl && !CharacterInstance->zAccl)
				goto LABEL_15;
			break;
		case 6:
			v8 = player;
			PhysicsMoveLocalZClamp(
				CharacterInstance,
				player->RotationSegment,
				(gameTrackerX.timeMult * CharacterInstance->anim.section[0].speedAdjustment) >> 12,
				1);
			PHYSICS_StopIfCloseToTarget(CharacterInstance, 0, 0, player->swimTargetSpeed);
			if (!CharacterInstance->xAccl && !CharacterInstance->yAccl && !CharacterInstance->zAccl)
				LABEL_15:
			INSTANCE_Post(CharacterInstance, 1048593, v8->swimTargetSpeed);
			break;
		default:
			return;
		}
	}
#else
	UNIMPLEMENTED();
#endif
}

void ApplyExternalLocalForces(struct __Player* player, struct _Instance* instance, struct __Force* Forces, int MaxForces, struct _Vector* Out)
{
#if defined(PSX_VERSION)
	int i;
	int friction;

	Out->z = 0;
	Out->y = 0;
	Out->x = 0;

	for (i = 0; i < MaxForces; i++)
	{
		if (Forces[i].Friction != 0)
		{
			if (Forces[i].Type == 0)
			{
				Out->x += Forces[i].LinearForce.x;
				Out->y -= Forces[i].LinearForce.y;
				Out->z += Forces[i].LinearForce.z;
			}
			else if (Forces[i].Type == 1)
			{
				Out->x += Forces[i].LinearForce.x;
				Out->y += Forces[i].LinearForce.y;
				Out->z += Forces[i].LinearForce.z;
			}
			else if (Forces[i].Type == 2)
			{
				Out->x += Forces[i].LinearForce.x;
				Out->y -= Forces[i].LinearForce.y;
				Out->z += Forces[i].LinearForce.z;

				Forces[i].Friction--;
			}
			else
			{
				friction = Forces[i].Friction;

				Forces[i].LinearForce.x = (Forces[i].LinearForce.x * friction) < 0 ? ((Forces[i].LinearForce.x * friction) + 0xFFF) >> 12 : (Forces[i].LinearForce.x * friction) >> 12;
				Forces[i].LinearForce.y = (Forces[i].LinearForce.y * friction) < 0 ? ((Forces[i].LinearForce.y * friction) + 0xFFF) >> 12 : (Forces[i].LinearForce.y * friction) >> 12;
				Forces[i].LinearForce.z = (Forces[i].LinearForce.z * friction) < 0 ? ((Forces[i].LinearForce.z * friction) + 0xFFF) >> 12 : (Forces[i].LinearForce.z * friction) >> 12;

				if (Forces[i].LinearForce.x == 0 && Forces[i].LinearForce.y == 0 && Forces[i].LinearForce.z == 0)
				{
					Forces[i].Friction = 0;
				}
			}
		}
	}

	Out->y = -Out->y;

#elif defined(PC_VERSION)
	struct __Force* f; // ecx
	int v6; // ebp
	int v7; // eax
	__int32 v8; // edx
	__int32 v9; // eax
	__int32 y; // edi
	__int32 z; // edx
	__int32 v12; // edx
	__int32 v13; // edi
	int v14; // edi
	int v15; // eax

	Out->z = 0;
	Out->y = 0;
	Out->x = 0;
	if (MaxForces > 0)
	{
		f = Forces;
		v6 = MaxForces;
		do
		{
			if (f->Friction)
			{
				v7 = f->Type;
				if (v7)
				{
					if (v7 == 1)
					{
						y = Out->y;
						Out->x += f->LinearForce.x;
						z = Out->z;
						Out->y = f->LinearForce.y + y;
						Out->z = f->LinearForce.z + z;
					}
				}
				else
				{
					v8 = Out->y;
					Out->x += f->LinearForce.x;
					v9 = Out->z;
					Out->y = v8 - f->LinearForce.y;
					Out->z = f->LinearForce.z + v9;
				}
				if (f->Type == 2)
				{
					v12 = Out->y;
					Out->x += f->LinearForce.x;
					v13 = Out->z;
					Out->y = v12 - f->LinearForce.y;
					Out->z = f->LinearForce.z + v13;
					--f->Friction;
				}
				else
				{
					v14 = f->Friction;
					f->LinearForce.x = f->LinearForce.x * v14 / 4096;
					f->LinearForce.y = f->LinearForce.y * v14 / 4096;
					v15 = f->LinearForce.z * v14 / 4096;
					f->LinearForce.z = v15;
					if (!f->LinearForce.x && !f->LinearForce.y && !v15)
						f->Friction = 0;
				}
			}
			++f;
			--v6;
		} while (v6);
	}
	Out->y = -Out->y;
#else
	UNIMPLEMENTED();
#endif
}




