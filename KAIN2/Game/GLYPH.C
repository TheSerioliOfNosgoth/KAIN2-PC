#include "CORE.H"
#include "GLYPH.H"
#include "MEMPACK.H"
#include "STATE.H"
#include "FX.H"
#include "CAMERA.H"
#include "FONT.H"
#include "OBTABLE.H"
#include "SOUND.H"
#include "PSX/COLLIDES.H"
#include "Game/DEBUG.H"
#include "Game/MATH3D.H"
#include "Game/DRAW.H"

short glyph_time;
short glyph_trigger;
short glyph_cost;

int blast_range; // offset 0x800d6280
short HUD_Rotation = 0; // offset 0x800d628c
short HUD_Rot_vel = 0; // offset 0x800d628e
short HUD_Position = 0; // offset 0x800d6290
short HUD_Pos_vel = 0; // offset 0x800d6292
short HUD_State = 0; // offset 0x800d6294
short HUD_Wait = 0; // offset 0x800d6296
short HUD_Count = 0; // offset 0x800d627a
short HUD_Count_Overall = 0; // offset 0x800d627c
int warpDraw; // offset 0x800d62a8
int glowdeg; // offset 0x800d62ac
int hud_warp_arrow_flash; // offset 0x800d62b0
short MANNA_Position; // offset 0x800d6270
short MANNA_Pos_vel;
int MANNA_Pickup_Time;
short HUD_Captured;
struct _SVector HUD_Cap_Pos; // offset 0x800d6298
struct _SVector HUD_Cap_Vel; // offset 0x800d62a0


void GlyphInit(struct _Instance* instance, struct GameTracker* gameTracker)
{
	struct __GlyphData* data;

	if ((instance->flags & 0x20000))
	{
		MEMPACK_Free((char*)instance->extraData);
	}
	else
	{
		data = (struct __GlyphData*)MEMPACK_Malloc(sizeof(struct __GlyphData), 0x1D);

		instance->extraData = data;
		
		InitMessageQueue(&data->messages);

		EnMessageQueueData(&data->messages, 0x100001, 0);

		data->process = &_GlyphOffProcess;
		data->selectedGlyph = 7;
		data->target_glyph_rotation = 3510;
		data->glyph_time = 0;
		
		glyph_time = 0;
		
		data->glyph_radius = 0;
		data->glyph_scale = 0;
		data->glyph_movement = 1;
		data->glyph_open = 0;

		glyph_trigger = 0;
	
		fx_blastring = NULL;

		data->glyph_rotation = (data->selectedGlyph - 1) * 585;

		glyph_cost = 0xFFFFFFFF;

		instance->flags |= 0x10800;
	}

	HUD_Init();
}

void GlyphCollide(struct _Instance* instance, struct GameTracker* gameTracker)
{
}

void GlyphProcess(struct _Instance *instance, struct GameTracker *gameTracker)
{ 
#if defined(PSX_VERSION)
	struct __GlyphData* data;

	data = (struct __GlyphData*)instance->extraData;

	data->process(instance, 0, 0);

	instance->oldPos.x = instance->parent->position.x;
	instance->oldPos.y = instance->parent->position.y;
	instance->oldPos.z = instance->parent->position.z;

	instance->position.x = instance->parent->position.x;
	instance->position.y = instance->parent->position.y;
	instance->position.z = instance->parent->position.z;

	instance->flags |= 0xC00;

	instance->currentStreamUnitID = instance->parent->currentStreamUnitID;

#elif defined(PC_VERSION)
	struct _Instance* parent; // ecx
	int flags; // eax

	(*(void(__cdecl**)(struct _Instance*, DWORD, DWORD))instance->extraData)(instance, 0, 0);
	parent = instance->parent;
	instance->oldPos = parent->position;
	instance->position = parent->position;
	flags = instance->flags;
	flags |= 0xC00;
	instance->currentStreamUnitID = parent->currentStreamUnitID;
	instance->flags = flags;
#endif
}

unsigned long GlyphQuery(struct _Instance* instance, unsigned long query)
{
	if (query == 1)
	{
		return 0;
	}
	else if (query == 24)
	{
		return 0;
	}

	return 0;
}

void GlyphPost(struct _Instance* instance, unsigned long message, unsigned long messageData)//Matching - 99.62%
{
	struct __GlyphData* data;
	
	data = (struct __GlyphData*)instance->extraData;

	if (message != 0x100007)
	{
		EnMessageQueueData(&data->messages, message, messageData);
	}
}

void _GlyphSwitchProcess(struct _Instance* instance, void (*func)(struct _Instance* instance, int data1, int data2)) //Matching - 99.63%
{
	struct __GlyphData* data;

	data = (struct __GlyphData*)instance->extraData;

	PurgeMessageQueue(&data->messages);

	EnMessageQueueData(&data->messages, 0x100004, 0);

	data->process(instance, 0, 0);

	EnMessageQueueData(&data->messages, 0x100001, 0);

	data->process = func;

	func(instance, 0, 0);
}

int GlyphIsGlyphOpen(struct _Instance* instance)
{
#if defined(PSX_VERSION)
	return ((struct __GlyphData*)instance->extraData)->glyph_open;
#elif defined(PC_VERSION)
	return *((__int16*)instance->extraData + 71);
#endif
}

int _GlyphIsGlyphSet(int glyph)
{
	unsigned long abilities;

	abilities = INSTANCE_Query(gameTrackerX.playerInstance, 0x24) | debugRazielFlags3;
	
	return abilities & (1 << (glyph + 17));
}

int _GlyphIsGlyphUsable(int glyph)
{
	return (1 << (glyph + 17)) & INSTANCE_Query(gameTrackerX.playerInstance, 0x13);
}

int _GlyphIsAnyGlyphSet()
{
	unsigned long abilities;
	
	abilities = INSTANCE_Query(gameTrackerX.playerInstance, 0x24);

	return ((abilities | debugRazielFlags3) & 0x1FC0000);
}

int _GlyphCost(struct _GlyphTuneData* glyphtunedata, int glyphNum)//Matching - 100%
{
	return glyphtunedata->glyph_costs[glyphNum - 1];
}


// autogenerated function stub: 
// int /*$ra*/ GlyphIsPuppetShowModeOn()
int GlyphIsPuppetShowModeOn()
{ // line 324, offset 0x8007ac30
	/* begin block 1 */
		// Start line: 720
	/* end block 1 */
	// End Line: 721
	UNIMPLEMENTED();
	return 0;
}

void _GlyphDefaultProcess(struct _Instance* instance, int data1, int data2)
{
	struct __Event* Ptr;
	struct __GlyphData* data;

	data = (struct __GlyphData*)instance->extraData;

	while ((Ptr = PeekMessageQueue(&data->messages)) != NULL)
	{
		switch (Ptr->ID)
		{
		case 0x80000010:
		{
			_GlyphSwitchProcess(instance, &_GlyphSelectProcess);

			SndPlayVolPan(17, 127, 64, 0);
			break;
		}
		}

		DeMessageQueue(&data->messages);
	}
}

void HUD_GetPlayerScreenPt(DVECTOR *center)
{
	_Position position;

	PushMatrix();

	SetRotMatrix(theCamera.core.wcTransform);

	SetTransMatrix(theCamera.core.wcTransform);

	position.x = gameTrackerX.playerInstance->position.x;
	position.y = gameTrackerX.playerInstance->position.y;
	position.z = gameTrackerX.playerInstance->position.z + 448;

	gte_ldv0(&position);
	gte_rtps();
	gte_stsxy(center);

	PopMatrix();
}

void GlyphDrawMenu(struct _Instance* instance)
{
#if defined(PSX_VERSION)
	struct _Position place;
	DVECTOR center;
	int n;
	int rot;
	int radius;
	int glyph_rotation_speed;
	int MANNA_Count;
	struct __GlyphData* data;
	struct _GlyphTuneData* glyphtunedata;
	int diff;
	int enabled;
	int scale_modify;
	int num;
	struct _Vector f1;

	glyph_rotation_speed = (gameTrackerX.timeMult * 64) >> 12;

	data = (struct __GlyphData*)instance->extraData;
	
	glyphtunedata = (struct _GlyphTuneData*)instance->object->data;

	MANNA_Count = INSTANCE_Query(instance, 32);

	if (data->target_glyph_rotation != data->glyph_rotation)
	{
		diff = AngleDiff(data->target_glyph_rotation, data->glyph_rotation);

		if (glyph_rotation_speed >= ABS(diff))
		{
			data->glyph_rotation = data->target_glyph_rotation;
		}
		else
		{
			if (data->glyph_movement > 0)
			{
				data->glyph_rotation = (data->glyph_rotation + glyph_rotation_speed) & 0xFFF;
			}
			else
			{
				data->glyph_rotation = (data->glyph_rotation - glyph_rotation_speed) & 0xFFF;
			}
		}
	}

	HUD_GetPlayerScreenPt(&center);

	if (center.vy < 72)
	{
		center.vy = 72;
	}

	radius = data->glyph_radius;

	rot = (data->glyph_rotation + 3072) & 0xFFF;
	
	for (n = 0; n < 7; n++)
	{
		glyph_rotation_speed = rot;

		diff = AngleDiff(glyph_rotation_speed, 3072);

		if (diff >= 0)
		{
			scale_modify = 4096 - (AngleDiff(glyph_rotation_speed, 3072) << 1);
		}
		else
		{
			scale_modify = 4096 + (AngleDiff(glyph_rotation_speed, 3072) << 1);
		}
		
		if (scale_modify < 1536)
		{
			scale_modify = 1536;
		}

		scale_modify = (data->glyph_scale * scale_modify) < 0 ? ((data->glyph_scale * scale_modify) + 0xFFF) >> 12 : ((data->glyph_scale * scale_modify) >> 12);

		place.x = center.vx + ((rcos(rot) * radius) >> 12);
		
		place.y = center.vy - ((((rsin(rot) * radius) >> 12) < 0) ? ((((rsin(rot) * radius) >> 12) + 7) >> 3) : (((rsin(rot) * radius) >> 12) >> 3));

		num = n;

		if (_GlyphIsGlyphSet(n + 1) != 0)
		{
			if (_GlyphIsGlyphUsable(n + 1) != 0)
			{
				enabled = (MANNA_Count < _GlyphCost(glyphtunedata, n + 1)) ^ 1;
			}
			else
			{
				enabled = 0;
			}
		}
		else
		{
			if ((n + 1) != 7)
			{
				num = 7;

				enabled = 1;
			}
			else
			{
				num = n;

				enabled = 0;
			}
		}

		rot -= 585;

		FX_MakeGlyphIcon(&place, instance->object, (glyphtunedata->glyph_size * scale_modify) < 0 ? ((glyphtunedata->glyph_size * scale_modify + 0x1FFF) >> 13) : ((glyphtunedata->glyph_size * scale_modify) >> 13), num, enabled);
	}

	if (data->glyph_time == 4096)
	{
		if (data->target_glyph_rotation == data->glyph_rotation)
		{
			if (MANNA_Count >= _GlyphCost(glyphtunedata, data->selectedGlyph))
			{
				f1.x = center.vx;

				f1.y = center.vy + ((radius < 0) ? ((radius + 7) >> 3) : (radius >> 3));

				DRAW_CreateAGlowingCircle(&f1, 320, gameTrackerX.primPool, gameTrackerX.drawOT, 5, 0x1404040, 20, 24, 0);
			}
		}
	}

	FX_DrawScreenPoly(2, ((data->glyph_time / glyphtunedata->glyph_darkness) << 16) | ((data->glyph_time / glyphtunedata->glyph_darkness) << 8) | (data->glyph_time / glyphtunedata->glyph_darkness), 32);

#elif defined(PC_VERSION)
	__int16* extraData; // ebp
	signed int v2; // esi
	int(__cdecl * v3)(int, int); // eax
	__int16 v4; // cx
	__int16 v5; // ax
	int v6; // eax
	int v7; // esi
	__int16 v8; // di
	int v9; // ebx
	__int16 v10; // di
	int v11; // ecx
	int v12; // eax
	__int64 v13; // rax
	int v14; // ebp
	int v15; // esi
	int v16; // eax
	int v17; // [esp+10h] [ebp-2Ch]
	__int16* data; // [esp+14h] [ebp-28h]
	__int16* v19; // [esp+18h] [ebp-24h]
	int v20; // [esp+1Ch] [ebp-20h]
	int(__cdecl * v21)(int, int); // [esp+20h] [ebp-1Ch]
	SVECTOR v22; // [esp+24h] [ebp-18h] BYREF
	__int16 v23[3]; // [esp+2Ch] [ebp-10h] BYREF
	__int16 v24[4]; // [esp+34h] [ebp-8h] BYREF

	extraData = (__int16*)instance->extraData;
	v19 = extraData;
	data = (__int16*)instance->object->data;
	v2 = gameTrackerX.timeMult << 6 >> 12;
	v3 = INSTANCE_Query(gameTrackerX.playerInstance, 32);
	v4 = extraData[75];
	v21 = v3;
	v5 = extraData[76];
	if (v5 != v4)
	{
		v6 = AngleDiff(v5, v4);
		if ((v6 & 0x8000u) != 0)
			v6 = -(__int16)v6;
		if (v6 > v2)
		{
			if (extraData[77] <= 0)
				extraData[75] = (extraData[75] - v2) & 0xFFF;
			else
				extraData[75] = (extraData[75] + v2) & 0xFFF;
		}
		else
		{
			extraData[75] = extraData[76];
		}
	}
	PushMatrix();
	SetRotMatrix(theCamera.core.wcTransform);
	SetTransMatrix(theCamera.core.wcTransform);
	*(DWORD*)&v22.vx = *(DWORD*)&gameTrackerX.playerInstance->position.x;
	v22.vz = gameTrackerX.playerInstance->position.z + 448;
	gte_ldv0(&v22);
	gte_RTPS();
	gte_stsxy(v23);
	PopMatrix();
	if (v23[1] < 72)
		v23[1] = 72;
	v7 = extraData[73];
	v8 = extraData[75] + 3072;
	v20 = v7;
	v9 = 0;
	while (1)
	{
		v10 = v8 & 0xFFF;
		v11 = AngleDiff(v10, 3072) < 0 ? -AngleDiff(v10, 3072) : AngleDiff(v10, 3072);
		v12 = 2 * (2048 - v11);
		if (v12 < 1536)
			v12 = 1536;
		v13 = extraData[74] * v12;
		v14 = ((WORD2(v13) & 0xFFF) + (int)v13) >> 12;
		v24[0] = v23[0] + ((v7 * rcos(v10)) >> 12);
		v24[1] = v23[1] - ((v7 * rsin(v10)) >> 12) / 8;
		v15 = 1 << (v9 + 18);
		if (((debugRazielFlags3 | (unsigned int)INSTANCE_Query(gameTrackerX.playerInstance, 36)) & v15) != 0)
		{
			v17 = v9;
			*(DWORD*)&v22.vx = v15 & (unsigned int)INSTANCE_Query(gameTrackerX.playerInstance, 19);
			if (*(DWORD*)&v22.vx)
			{
				v16 = *((char*)data + v9 + 4) <= (int)v21;
				goto LABEL_25;
			}
		}
		else
		{
			if (v9 != 6)
			{
				v17 = 7;
				v16 = 1;
				goto LABEL_25;
			}
			v17 = 6;
		}
		v16 = 0;
	LABEL_25:
		FX_MakeGlyphIcon(v24, instance->object, v14 * *data / 4096 / 2, v17, v16);
		v8 = v10 - 585;
		if (++v9 >= 7)
			break;
		extraData = v19;
		v7 = v20;
	}
#else
UNIMPLEMENTED();
#endif
}

long GlyphTime(int time)//Matching - 70.71%
{
	return  (time * time < 0) ? ((time * time + 4095) >> 12) : (time * time >> 12);
}

void ShrinkGlyphMenu(struct _Instance *instance)
{
	struct __GlyphData *data;
	int time;
	short accl;

#define GET_GLYPH_RADIUS(x) (x * 150) < 0 ? ((x + 4095) >> 12) : (x >> 12)

	data = (struct __GlyphData*)instance->extraData;
	gameTrackerX.streamFlags &= 0xFFEFFFFF;

	if (data->glyph_time > 0)
	{
		data->glyph_time -= ((gameTrackerX.timeMult * 512) >> 12);

		if (data->glyph_time < 0)
		{
			data->glyph_time = 0;
		}

		glyph_time = data->glyph_time;

		time = GlyphTime(data->glyph_time);

		data->glyph_radius = GET_GLYPH_RADIUS(time);
		data->glyph_scale = time;

		if (data->glyph_time > 0)
		{
			GlyphDrawMenu(instance);
		}
	}
	else
	{
		glyph_cost = -1;
	}

	if (MANNA_Pickup_Time <= 0)
	{
		CriticalDampValue(5, &MANNA_Position, -64, &MANNA_Pos_vel, &accl, 12);

		data->glyph_open = 0;
	}
	else
	{
		MANNA_Pickup_Time -= gameTrackerX.timeMult;

		data->glyph_open = 0;
	}
}

void EnlargeGlyphMenu(struct _Instance* instance)//Matching - 84.92%
{
	struct __GlyphData* data;
	int time;
	short accl;

	data = (struct __GlyphData*)instance->extraData;

	gameTrackerX.streamFlags |= 0x100000;

	if (data->glyph_time < 4096)
	{
		data->glyph_time += (gameTrackerX.timeMult * 512) >> 12;

		if (data->glyph_time >= 0x1001)
		{
			data->glyph_time = 4096;
		}

		glyph_time = data->glyph_time;
	}

	time = GlyphTime(data->glyph_time);

	data->glyph_radius = (time * 150) < 0 ? (time * 150 + 0xFFF) >> 12 : (time * 150) >> 12;

	data->glyph_scale = time;

	GlyphDrawMenu(instance);

	MANNA_Pickup_Time = 0;

	CriticalDampValue(5, &MANNA_Position, 24, &MANNA_Pos_vel, &accl, 12);

	data->glyph_open = 1;
}

void _GlyphOffProcess(struct _Instance* instance, int data1, int data2)//Matching - 78.83%
{
	struct __Event* Ptr;
	struct __GlyphData* data;

	data = (struct __GlyphData*)instance->extraData;

	ShrinkGlyphMenu(instance);

	while ((Ptr = PeekMessageQueue(&data->messages)) != NULL)
	{
		switch (Ptr->ID)
		{
		case 0x100004:
		case 0x100001:
		{
			break;
		}
		case 0x80000010:
		{
			if (data->process == &_GlyphSelectProcess)
			{
				_GlyphSwitchProcess(instance, _GlyphOffProcess);
			}
			else
			{
				_GlyphSwitchProcess(instance, _GlyphSelectProcess);
			}
		}
		default:
		{
			_GlyphDefaultProcess(instance, data1, data2);

			break;
		}
		break;
		}

		DeMessageQueue(&data->messages);
	}

	if (data->process == &_GlyphSelectProcess)
	{
		SndPlayVolPan(17, 127, 64, 0);
	}

	Glyph_DoFX(instance);

	return;
}

void _GlyphSelectProcess(struct _Instance* instance, int data1, int data2)
{
	struct __Event* Ptr; // $v0
	struct __GlyphData* data; // $s1
	struct _GlyphTuneData* glyphtunedata; // $s4
	int dontdraw_flag; // $s2
	int MANNA_Count; // $s0

	//s3 = instance
	//s6 = data1
	//s7 = data2

	dontdraw_flag = 0;
	//s5 = -1

	//v0 = instance->object
	data = (struct __GlyphData*)instance->extraData;
	glyphtunedata = (struct _GlyphTuneData*)instance->object->data;

	//loc_8007B720
	

	//a0 = 0x100000
	while ((Ptr = PeekMessageQueue(&data->messages)) != NULL)
	{
		switch (Ptr->ID)
		{
		case 0x100001:
		{
			//loc_8007B7A4
			dontdraw_flag = 1;

			data->selectedGlyph = 7;

			data->target_glyph_rotation = 0xDB6;

			data->glyph_rotation = data->selectedGlyph * 585;

			data->glyph_rotation = data->target_glyph_rotation;
			break;
		}
		case 0x100004:
		{
			//loc_8007B7E0
			dontdraw_flag = 1;
			break;
		}
		case 0x10000002:
		{
			//loc_8007B94C
			if (_GlyphIsAnyGlyphSet())
			{
				if (AngleDiff(data->glyph_rotation, data->target_glyph_rotation) >= 0 && AngleDiff(data->glyph_rotation, data->target_glyph_rotation) < 64 ||
					AngleDiff(data->glyph_rotation, data->target_glyph_rotation) >= 0 && -AngleDiff(data->glyph_rotation, data->target_glyph_rotation) >= 64)
				{
					//loc_8007B884
					do
					{
						data->selectedGlyph++;

						data->glyph_movement = 1;

						if (data->selectedGlyph >= 8)
						{
							data->selectedGlyph = 1;
						}

						//loc_8007B8A4

						data->target_glyph_rotation = (data->selectedGlyph - 1) * 585;

					} while (_GlyphIsGlyphSet(data->selectedGlyph) == 0);

					if (AngleDiff(data->glyph_rotation, data->target_glyph_rotation) >= 0 && AngleDiff(data->glyph_rotation, data->target_glyph_rotation) < 64 ||
						AngleDiff(data->glyph_rotation, data->target_glyph_rotation) >= 0 && -AngleDiff(data->glyph_rotation, data->target_glyph_rotation) >= 64)
					{
						SndPlayVolPan(0x12, 0x64, 0x40, 0);
					}
				}
			}
			break;
		}
		case 0x10000004:
		{
			//loc_8007B804
			if (_GlyphIsAnyGlyphSet())
			{
				if (AngleDiff(data->glyph_rotation, data->target_glyph_rotation) >= 0 && AngleDiff(data->glyph_rotation, data->target_glyph_rotation) >= 64 ||
					AngleDiff(data->glyph_rotation, data->target_glyph_rotation) >= 0 && -AngleDiff(data->glyph_rotation, data->target_glyph_rotation) < 64)
				{
					//loc_8007B884
					do
					{
						data->selectedGlyph--;

						data->glyph_movement = -1;

						if (data->selectedGlyph <= 0)
						{
							data->selectedGlyph = 7;
						}

						//loc_8007B8A4

						data->target_glyph_rotation = (data->selectedGlyph - 1) * 585;

					} while (_GlyphIsGlyphSet(data->selectedGlyph) == 0);

					if (AngleDiff(data->glyph_rotation, data->target_glyph_rotation) >= 0 && AngleDiff(data->glyph_rotation, data->target_glyph_rotation) >= 64 ||
						AngleDiff(data->glyph_rotation, data->target_glyph_rotation) >= 0 && -AngleDiff(data->glyph_rotation, data->target_glyph_rotation) >= 64)
					{
						SndPlayVolPan(0x12, 0x64, 0x40, 0);
					}
				}
			}
			break;
		}
		case 0x80000000:
		{
			//loc_8007BA9C
			if (fx_going == 0)
			{
				if (_GlyphIsGlyphSet(data->selectedGlyph))
				{
					MANNA_Count = INSTANCE_Query(gameTrackerX.playerInstance, 0x20);

					if (MANNA_Count >= _GlyphCost(glyphtunedata, data->selectedGlyph))
					{
						if (_GlyphIsGlyphUsable(data->selectedGlyph))
						{
							dontdraw_flag = 1;

							_GlyphSwitchProcess(instance, &_GlyphGenericProcess);
						}
						else
						{
							SndPlayVolPan(16, 100, 64, 0);
						}
					}
					else
					{
						SndPlayVolPan(16, 100, 64, 0);
					}
				}
				else
				{
					SndPlayVolPan(16, 100, 64, 0);
				}
			}
			//loc_8007BB18
			break;
		}
		case 0x80000001:
		{
			//loc_8007BA9C
			//assert(FALSE);
			break;
		}
		case 0x80000010:
		{
			//loc_8007B7E8
			dontdraw_flag = 1;

			_GlyphSwitchProcess(instance, &_GlyphOffProcess);

			SndPlayVolPan(15, 127, 64, 0);

			break;
		}
		default:
			//assert(FALSE);
			break;
		}

		DeMessageQueue(&data->messages);
	}
	//loc_8007BB4C
	if (dontdraw_flag == 0)
	{
		glyph_cost = _GlyphCost(glyphtunedata, data->selectedGlyph);

		EnlargeGlyphMenu(instance);
	}

	Glyph_DoFX(instance);
}

void Glyph_StartSpell(struct _Instance* instance, int glyphnum)
{
	int message; // $a2

	message = 0;

	switch (glyphnum)
	{
	case 7:
	{
		INSTANCE_Post(gameTrackerX.playerInstance, 0x80007, 0);

		break;
	}
	}
}


// autogenerated function stub: 
// void /*$ra*/ Glyph_Broadcast(struct _Instance *sender /*$s6*/, int glyphnum /*$a1*/)
void Glyph_Broadcast(struct _Instance *sender, int glyphnum)
{ // line 794, offset 0x8007ba18
	/* begin block 1 */
		// Start line: 795
		// Start offset: 0x8007BA18
		// Variables:
			struct _Instance *instance; // $s2
			int plane; // $s7
			long whatAmIMask; // $s4
			int Message; // $s3
			int radius; // stack offset -48
			int radius_old; // $fp
			int range; // $s5

		/* begin block 1.1 */
			// Start line: 847
			// Start offset: 0x8007BB28
			// Variables:
				int dist; // $s0
				int old_dist; // $v0
				int old_x; // $s0
				int old_y; // $s1
				int new_x; // $v0
				int new_y; // $v1
				long whatAmI; // $s0
		/* end block 1.1 */
		// End offset: 0x8007BC30
		// End Line: 878
	/* end block 1 */
	// End offset: 0x8007BC40
	// End Line: 879

	/* begin block 2 */
		// Start line: 1865
	/* end block 2 */
	// End Line: 1866

	/* begin block 3 */
		// Start line: 1875
	/* end block 3 */
	// End Line: 1876
				UNIMPLEMENTED();
}


// autogenerated function stub: 
// void /*$ra*/ Glyph_DoSpell(struct _Instance *instance /*stack 0*/, int glyphnum /*$s1*/)
void Glyph_DoSpell(struct _Instance *instance, int glyphnum)
{ // line 881, offset 0x8007bc70
	/* begin block 1 */
		// Start line: 882
		// Start offset: 0x8007BC70
		// Variables:
			int fx_radius; // $fp
			int fx_accl; // $v0
			int fx_vel; // $s5
			long fx_color; // $a3
			int fx_height1; // $s7
			int fx_height2; // $s6
			int fx_height3; // $s4
			int fx_rad2; // $s3
			int fx_rad3; // $s2
			int pred_offset; // $s0
			int color_change_radius; // $s1
			//MATRIX mat; // stack offset -80
			struct _GlyphTuneData *glyphtunedata; // $s0
	/* end block 1 */
	// End offset: 0x8007BED8
	// End Line: 981

	/* begin block 2 */
		// Start line: 2104
	/* end block 2 */
	// End Line: 2105
			UNIMPLEMENTED();
}

void Glyph_EndFX() //Matching - 97%
{
	fx_blastring->lifeTime = 0;
	fx_blastring = NULL;

	fx_going = 0;
}

void Glyph_DoFX(struct _Instance *instance)
{ 
	if (gameTrackerX.gameMode != 6 && !(gameTrackerX.streamFlags & 0x100000) && fx_going != 0)
	{
		Glyph_Broadcast(instance, fx_going);

		if (blast_range < fx_blastring->radius)
		{
			Glyph_EndFX();
		}

		if (fx_going == 5)
		{
			fx_blastring->height1 -= 60;
			fx_blastring->height3 += 60;
		}
	}
}

void _GlyphGenericProcess(struct _Instance* instance, int data1, int data2)
{
	struct __Event* Ptr; // $v0
	struct __GlyphData* data; // $s1
	struct _GlyphTuneData* glyphtunedata; // $s0

	//s2 = instance
	//s3 = data1
	//s4 = data2
	data = (struct __GlyphData*)instance->extraData;

	//s0 = 0x100001

	while (Ptr = PeekMessageQueue(&data->messages))
	{
		switch (Ptr->ID)
		{
		case 0x00100001:
		{
			Glyph_StartSpell(instance, data->selectedGlyph);

			break;
		}
		default:
			//_GlyphDefaultProcess(instance, data1, data2);
			break;
		}

		DeMessageQueue(&data->messages);
	}

	if (glyph_trigger != 0)
	{
		glyphtunedata = (struct _GlyphTuneData*)instance->object->data;

		Glyph_DoSpell(instance, data->selectedGlyph);

		glyph_trigger = 0;

		INSTANCE_Post(gameTrackerX.playerInstance, 0x40008, _GlyphCost(glyphtunedata, data->selectedGlyph));
	
		Glyph_DoFX(instance);
	}
}

void GlyphTrigger() //Matching - 98.57%
{ 
	if (fx_going == 0)
	{
		glyph_trigger = 1;
	}
}

void MANNA_Pickup() //Matching - 98.57%
{
#if defined(PSX_VERSION)
	MANNA_Pickup_Time = 122880;

	MANNA_Position = 24;

#elif defined(PC_VERSION)
	dword_C55068 = 0x1E000;
	LOWORD(dword_C5508C) = 24;
#endif
}


// autogenerated function stub: 
// void /*$ra*/ HEALTHU_Pickup(struct _Instance *instance /*$s0*/)
void HEALTHU_Pickup(struct _Instance *instance)
{ // line 1090, offset 0x8007c148
	/* begin block 1 */
		// Start line: 2566
	/* end block 1 */
	// End Line: 2567
	UNIMPLEMENTED();
}

void HUD_Damp(short* val, short target, short* vel, short max)
{
	short accl;

	CriticalDampValue(1, val, target, vel, &accl, max);
}

void HUD_Init() //Matching - 96.07%
{ 
	HUD_Rotation = 0;
	HUD_Rot_vel = 0;
	HUD_Pos_vel = 0;
	HUD_State = 0;
	HUD_Wait = 0;
	HUD_Position = -1000;
	HUD_Count = 0;
	HUD_Count_Overall = 0;
	
	warpDraw = 0;
	
	glowdeg = 0;
	
	hud_warp_arrow_flash = 0;
}

void HUD_Setup_Chit_Count(int chits) //Matching - 99.29%
{
	HUD_Count_Overall = chits;

	HUD_Count = chits % 5;
}


void HUD_Update()
{
	short accl;

	if (gameTrackerX.gameMode == 6 && HUD_State == 0)
	{
		HUD_State = 10;
	}
	else if (gameTrackerX.gameMode != 6)
	{
		if ((unsigned int)(HUD_State - 10) < 2)
		{
			HUD_State = 12;
		}
	}
	else
	{
		if (HUD_State >= 2 && HUD_State < 7)
		{
			return;
		}
	}

	if (HUD_Wait > 0)
	{
		HUD_Wait--;
		return;
	}

	switch (HUD_State)
	{
	default:
	case 0:
	case 7:
	case 8:
	case 9:
	{
		HUD_Position = -1000;
		HUD_Rotation = 0;
		HUD_Rot_vel = 0;
		HUD_Pos_vel = 0;

		if (HUD_Count == 5)
		{
			HUD_Count = 0;
		}

		break;
	}
	case 1:
	case 10:
	{
		HUD_Damp(&HUD_Position, 0, &HUD_Pos_vel, 96);

		if (HUD_Position >= 0)
		{
			HUD_Position = 0;

			if (HUD_State != 10)
			{
				if (HUD_Count <= 0)
				{
					HUD_State = 3;
				}
				else
				{
					HUD_State = 2;
				}
			}
			else
			{
				HUD_State = 11;
			}
		}

		if (HUD_State == 10)
		{
			MANNA_Pickup_Time = 0;

			CriticalDampValue(5, &MANNA_Position, 24, &MANNA_Pos_vel, &accl, 12);
		}

		break;

	case 2:
	{
		HUD_Damp(&HUD_Rotation, 819, &HUD_Rot_vel, 80);

		if (HUD_Rotation >= 819)
		{
			HUD_Rotation = 819;
			HUD_State = 3;
		}

		break;
	}
	case 3:
	case 4:
	case 11:
	{
		break;
	}
	case 5:
	{
		HUD_State = 6;
		
		HUD_Wait = 10;

		HUD_Rotation = 0;

		HUD_Captured = 0;

		HUD_Count++;

		HUD_Count_Overall++;

		break;
	}
	case 6:
	case 12:
	{
		HUD_Damp(&HUD_Position, -1000, &HUD_Pos_vel, 96);

		if (HUD_Position < -999)
		{
			HUD_State = 0;
		}

		break;
	}
	}
	}
}

void HUD_Draw()
{
	struct _SVector Rotation;
	struct _SVector Pos;
	struct _SVector offset;
	int n;
	DVECTOR center;
	int glow;
	int left;
	int right;
	int oldx;
	int oldy;
	int MANNA_Count;
	int MANNA_Max;
	struct _SVector targetPos;
	struct _SVector accl;
	struct _SVector HUD_Cap_Rot;

#if !defined(EDITOR)
	if ((theCamera.instance_mode & 0x80000000))
	{
		warpDraw += (gameTrackerX.timeMult >> 4);

		if (warpDraw >= 4097)
		{
			warpDraw = 4096;
		}

		HUD_GetPlayerScreenPt(&center);

		glow = (warpDraw / 10) * rcos(glowdeg);

		if (glow < 0)
		{
			glow = glow + 4095;
		}

		glow = (warpDraw / 3) + (glow >> 12);

		if (glow < 0)
		{
			glow = 0;
		}

		glowdeg += (gameTrackerX.timeMult >> 5);

		if (hud_warp_arrow_flash > 0)
		{
			right = glow + hud_warp_arrow_flash;

			hud_warp_arrow_flash -= (gameTrackerX.timeMult >> 3);

			if (hud_warp_arrow_flash < 0)
			{
				hud_warp_arrow_flash = 0;

				left = glow;

				if (hud_warp_arrow_flash < 0)
				{
					left = glow - hud_warp_arrow_flash;

					hud_warp_arrow_flash += (gameTrackerX.timeMult >> 3);

					if (hud_warp_arrow_flash > 0)
					{
						hud_warp_arrow_flash = 0;
					}
				}
			}
			else
			{
				right = glow;
			}
		}
		else
		{
			right = glow;
			left = glow;

			if (hud_warp_arrow_flash < 0)
			{
				left = glow - hud_warp_arrow_flash;

				hud_warp_arrow_flash += (gameTrackerX.timeMult >> 3);

				if (hud_warp_arrow_flash > 0)
				{
					hud_warp_arrow_flash = 0;
				}
			}
		}

		FX_MakeWarpArrow(center.vx + -64, center.vy, -64, 32, left);
		FX_MakeWarpArrow(center.vx + 64, center.vy, 64, 32, right);
	}
	else
	{
		if (warpDraw != 0)
		{
			if (theCamera.instance_mode != 0)
			{
				warpDraw += (gameTrackerX.timeMult >> 4);

				if (warpDraw >= 4097)
				{
					warpDraw = 4096;
				}
			}
			else
			{
				warpDraw -= (gameTrackerX.timeMult >> 4);

				if (warpDraw < 0)
				{
					warpDraw = 0;
				}
			}
		}

		HUD_GetPlayerScreenPt(&center);

		glow = (warpDraw / 10) * rcos(glowdeg);

		if (glow < 0)
		{
			glow = glow + 4095;
		}

		glow = (warpDraw / 3) + (glow >> 12);

		if (glow < 0)
		{
			glow = 0;
		}

		glowdeg += (gameTrackerX.timeMult >> 5);

		if (hud_warp_arrow_flash > 0)
		{
			right = glow + hud_warp_arrow_flash;

			hud_warp_arrow_flash -= (gameTrackerX.timeMult >> 3);

			if (hud_warp_arrow_flash < 0)
			{
				hud_warp_arrow_flash = 0;

				left = glow;

				if (hud_warp_arrow_flash < 0)
				{
					left = glow - hud_warp_arrow_flash;

					hud_warp_arrow_flash += (gameTrackerX.timeMult >> 3);

					if (hud_warp_arrow_flash > 0)
					{
						hud_warp_arrow_flash = 0;
					}
				}
			}
			else
			{
				right = glow;
			}
		}
		else
		{
			right = glow;
			left = glow;

			if (hud_warp_arrow_flash < 0)
			{
				left = glow - hud_warp_arrow_flash;

				hud_warp_arrow_flash += (gameTrackerX.timeMult >> 3);

				if (hud_warp_arrow_flash > 0)
				{
					hud_warp_arrow_flash = 0;
				}
			}
		}

		FX_MakeWarpArrow(center.vx + -64, center.vy, -64, 32, left);
		FX_MakeWarpArrow(center.vx + 64, center.vy, 64, 32, right);
	}

	HUD_Update();

	offset.x = 0;
	offset.y = 0;
	offset.z = 135;

	if (MANNA_Position >= -63)
	{
		oldx = fontTracker.font_xpos;
		oldy = fontTracker.font_ypos;

		MANNA_Count = INSTANCE_Query(gameTrackerX.playerInstance, 32);
		MANNA_Max = INSTANCE_Query(gameTrackerX.playerInstance, 45);

		FX_MakeMannaIcon(MANNA_Position, 23, 51, 32);

		FONT_Flush();

		FONT_SetCursor(MANNA_Position + 58, 32);

		if (glyph_cost != -1)
		{
			FONT_Print("%d/", glyph_cost);
		}

		if (MANNA_Count >= MANNA_Max)
		{
			FONT_SetColorIndex(2);
		}

		FONT_Print("%d", MANNA_Count);

		FONT_SetColorIndex(0);

		FONT_SetCursor(oldx, oldy);

		FONT_Flush();
	}

	if (HUD_Position >= -999)
	{
		if (HUD_Captured != 0 && gameTrackerX.gameMode != 6)
		{
			HUD_Cap_Rot.x = 1024;
			HUD_Cap_Rot.y = 0;
			HUD_Cap_Rot.z = 0;

			targetPos.x = -1536;
			targetPos.y = 2560;

			if (HUD_State < 4)
			{
				targetPos.z = 288;
			}
			else
			{
				targetPos.z = 608;
			}

			CriticalDampPosition(1, (struct _Position*)&HUD_Cap_Pos, (struct _Position*)&targetPos, &HUD_Cap_Vel, &accl, 128);

			if (HUD_Cap_Vel.x == 0 && HUD_Cap_Vel.y == 0 && HUD_Cap_Vel.z == 0)
			{
				if (HUD_State == 3)
				{
					HUD_State = 4;
				}
				else if (HUD_State == 4)
				{
					HUD_State = 5;
				}
			}

			FX_DrawModel((struct Object*)objectAccess[21].object, 0, &HUD_Cap_Rot, &HUD_Cap_Pos, &offset, 0);
		}

		Rotation.x = 1024;
		Pos.y = 608;
		Pos.z = 2560;
		Rotation.y = 0;
		offset.z = 0;
		Rotation.z = HUD_Rotation;
		Pos.x = HUD_Position - 1536;

		if (HUD_Count != 0 || HUD_Count_Overall < 15)
		{
			for (n = 0; n < 5; n++)
			{
				switch (n)
				{
				case 0:
				{
					Rotation.z = 0;
					break;
				}
				case 1:
				{
					Rotation.z = 3277;
					break;
				}
				case 2:
				{
					Rotation.z = 2458;
					break;
				}
				case 3:
				{
					Rotation.z = 1638;
					break;
				}
				case 4:
				{
					Rotation.z = 819;
					break;
				}
				}

				Pos.z = (Pos.z - HUD_Rotation) & 0xFFF;

				FX_DrawModel((struct Object*)objectAccess[24].object, 0, &Rotation, &Pos, &offset, (n < HUD_Count) ^ 1);
			}
		}
	}
#endif
}
