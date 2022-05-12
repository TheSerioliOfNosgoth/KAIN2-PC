#include "CORE.H"
#include "OBTABLE.H"
#include "RAZIEL/RAZIEL.H"
#include "REAVER.H"
#include "GLYPH.H"
#include "PHYSOBS.H"
#include "MONSTER/MONAPI.H"
#include "FX.H"
#include "SCRIPT2.H"
#include "GENERIC.H"
#include "GAMELOOP.H"
#include "SCRIPT.H"

#ifdef PC_VERSION
#pragma warning(disable: 4101)
#endif

struct ObjectAccess objectAccess[28] =
{
	{
		"hud_____",
		NULL
	},
	{
		"flame___",
		NULL
	},
	{
		"fonts___",
		NULL
	},
	{
		"waterfx_",
		NULL
	},
	{
		"dbgfont_",
		NULL
	},
	{
		"cammode_",
		NULL
	},
	{
		"introfx_",
		NULL
	},
	{
		"mapicon_",
		NULL
	},
	{
		"paths___",
		NULL
	},
	{
		"soul____",
		NULL
	},
	{
		"particle",
		NULL
	},
	{
		"knife___",
		NULL
	},
	{
		"stick___",
		NULL
	},
	{
		"xbow____",
		NULL
	},
	{
		"fthrow__",
		NULL
	},
	{
		"moregg__",
		NULL
	},
	{
		"wcegg___",
		NULL
	},
	{
		"eggsac__",
		NULL
	},
	{
		"mound___",
		NULL
	},
	{
		"force___",
		NULL
	},
	{
		"glphicon",
		NULL
	},
	{
		"healthu_",
		NULL
	},
	{
		"sreavr__",
		NULL
	},
	{
		"wrpface_",
		NULL
	},
	{
		"healths_",
		NULL
	},
	{
		"eaggot__",
		NULL
	},
	{
		"eaggots_",
		NULL
	},
	{
		NULL,
		NULL
	}
};

/*struct ObjectFunc objectFunc[8] =
{
	{
		"sreavr__",
		&SoulReaverInit,
		&SoulReaverProcess,
		&SoulReaverCollide,
		&SoulReaverQuery,
		&SoulReaverPost,
		NULL,
		NULL,
		NULL
	},
	{
		"glphicon",
		&GlyphInit,
		NULL,
		&GlyphCollide,
		&GlyphQuery,
		&GlyphPost,
		NULL,
		NULL,
		NULL
	},
	{
		"physical",
		&InitPhysicalObject,
		&ProcessPhysicalObject,
		&CollidePhysicalObject,
		&PhysicalObjectQuery,
		&PhysicalObjectPost,
		NULL,
		&PhysicalRelocateTune,
		NULL
	},
	{
		"monster_",
		&MonsterInit,
		&MonsterProcess,
		&MonsterCollide,
		&MonsterQuery,
		&MonsterMessage,
		additional&MonsterAdditionalCollide,
		&MonsterRelocateTune,
		&MonsterRelocateInstanceObject
	},
	{
		"particle",
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		&FX_RelocateGeneric,
		NULL
	},
	{
		"litshaft",
		&LitShaftInit,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL
	},
	{
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL
	}
};*/

struct ObjectFunc objectFunc[8] =
{
	{
		"raziel__",
		RazielInit,
		RazielProcess,
		RazielCollide,
		RazielQuery,
		RazielPost,
		RazielAdditionalCollide,
		NULL,
		NULL
	},
	{
		"sreaver__",
		SoulReaverInit,
		SoulReaverProcess,
		SoulReaverCollide,
		SoulReaverQuery,
		SoulReaverPost,
		NULL,
		NULL,
		NULL
	},
	{
		"glphicon",
		GlyphInit,
		NULL,
		GlyphCollide,
		GlyphQuery,
		GlyphPost,
		NULL,
		NULL,
		NULL
	},
	{
		"physical",
		InitPhysicalObject,
		ProcessPhysicalObject,
		CollidePhysicalObject,
		PhysicalObjectQuery,
		PhysicalObjectPost,
		NULL,
		PhysicalRelocateTune,
		NULL
	},
	{
		"monster_",
		MonsterInit,
		MonsterProcess,
		MonsterCollide,
		MonsterQuery,
		MonsterMessage,
		MonsterAdditionalCollide,
		MonsterRelocateTune,
		MonsterRelocateInstanceObject
	},
	{
		"particle",
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		FX_RelocateGeneric,
		NULL
	},
	{
		"litshaft",
		LitShaftInit,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL
	}
};

void OBTABLE_InstanceInit(struct _Instance *instance)
{
	long id;
	
	id = instance->object->id;

	if (id < 0)
	{
		GenericInit(instance, &gameTrackerX);
	}
	else
	{
		if (objectFunc[id].initFunc != NULL)
		{
			objectFunc[id].initFunc(instance, &gameTrackerX);
		}
	}

	instance->flags2 |= 0x200000;

	if (!(instance->flags & 0x100000))
	{
		SCRIPT_InstanceSplineInit(instance);
	}

	if (instance->intro != NULL && (instance->intro->flags & 0x20))
	{
		instance->flags2 &= 0xFFFFFFFB;
		instance->flags2 &= 0xFFFDFFFF;
	}
}

void OBTABLE_GetInstanceCollideFunc(struct _Instance *instance)
{
	long id;

	id = instance->object->id;

	if (id >= 0)
	{
		instance->collideFunc = objectFunc[id].collideFunc;
	}
	else
	{
		instance->collideFunc = GenericCollide;
	}
}

void OBTABLE_GetInstanceAdditionalCollideFunc(struct _Instance *instance)
{ 
	long id;

	id = instance->object->id;

	if (id >= 0)
	{
		instance->additionalCollideFunc = objectFunc[id].additionalCollideFunc;
	}
	else
	{
		instance->additionalCollideFunc = NULL;
	}
}

void OBTABLE_GetInstanceProcessFunc(struct _Instance *instance)
{
	long id;
	
	id = instance->object->id;

	if (id > 0)
	{
		instance->processFunc = objectFunc[id].processFunc;
	}
	else
	{
		instance->processFunc = GenericProcess;
	}
}

void OBTABLE_GetInstanceQueryFunc(struct _Instance *instance)
{ 
	long id;

	id = instance->object->id;
	
	if (id >= 0)
	{
		instance->queryFunc = objectFunc[id].queryFunc;
	}
	else
	{
		instance->queryFunc = GenericQuery;
	}
}

void OBTABLE_GetInstanceMessageFunc(struct _Instance *instance)
{
	long id;

	id = instance->object->id;

	if (id >= 0)
	{
		instance->messageFunc = objectFunc[id].messageFunc;
	}
	else
	{
		instance->messageFunc = GenericMessage;
	}
}

void OBTABLE_InitObjectWithID(struct Object *object)
{
	long id;
	struct ObjectAccess *oa;

#define COMPARE_STRING_OA(x, y)	y = &objectAccess[0];							\
								do {											\
								int c1 = ((int*)x->name)[0];					\
							    int c2 = ((int*)y->objectName)[0];				\
								if(c1 == c2) {									\
									c1 = ((int*)x->name)[1];					\
									c2 = ((int*)y->objectName)[1];				\
									if(c1 == c2) {								\
									   y->object = x;                           \
									}                                           \
								  }												\
								}												\
								while((++y)->objectName != NULL);  	            \

#define SET_OBJECT_ID(in_id) if (objectFunc[in_id].scriptName != 0) { \
                                  object->id = in_id;       \
	                  }                                     \
	                  else {                                \
		                          object->id = -1;          \
	                  }                                     \

#define GET_OBJECT_BY_NAME(in_id, in_script_name)           \
            in_id = 0;                                      \
			if(objectFunc[in_id].scriptName == NULL) {      \
				object->id = -1;							\
			}												\
            while (objectFunc[in_id].scriptName != NULL) {  \
				if (strcmp(objectFunc[in_id].scriptName, in_script_name) == 0) { \
					SET_OBJECT_ID(in_id);                   \
				}                                           \
				in_id++;                                    \
			}							                    \
	
	if (object != NULL)
	{
		if ((object->oflags2 & 0x40000))
		{
			GET_OBJECT_BY_NAME(id, "physical");
		}
		else if ((object->oflags2 & 0x80000))
		{
			GET_OBJECT_BY_NAME(id, "monster_");
		}
		else
		{
			GET_OBJECT_BY_NAME(id, object->script);
		}

		if (objectAccess[0].objectName != NULL)
		{
			COMPARE_STRING_OA(object, oa);
		}
	}
}

void OBTABLE_ClearObjectReferences()
{
	ObjectAccess* oa = objectAccess;

	while (oa->objectName != NULL)
	{
		oa->object = NULL;
		oa++;
	}
}

void OBTABLE_RemoveObjectEntry(struct Object *object)
{
	struct ObjectAccess *oa;

	oa = &objectAccess[0];

	while (oa->objectName != NULL)
	{
		if (oa->object == object)
		{
			oa->object = NULL;
			return;
		}

		oa++;
	}
}


// autogenerated function stub: 
// struct Object * /*$ra*/ OBTABLE_FindObject(char *objectName /*$s3*/)
struct Object * OBTABLE_FindObject(char *objectName)
{ // line 394, offset 0x8003de44
	/* begin block 1 */
		// Start line: 395
		// Start offset: 0x8003DE44
		// Variables:
			struct Object *object; // $s0
			struct _ObjectTracker *otr; // $v0
			int i; // $s2
	/* end block 1 */
	// End offset: 0x8003DED4
	// End Line: 412

	/* begin block 2 */
		// Start line: 812
	/* end block 2 */
	// End Line: 813

	/* begin block 3 */
		// Start line: 817
	/* end block 3 */
	// End Line: 818

	return null;
}


// autogenerated function stub: 
// void /*$ra*/ OBTABLE_ChangeObjectAccessPointers(struct Object *oldObject /*$a0*/, struct Object *newObject /*$a1*/)
void OBTABLE_ChangeObjectAccessPointers(struct Object *oldObject, struct Object *newObject)
{ // line 414, offset 0x8003def0
	/* begin block 1 */
		// Start line: 416
		// Start offset: 0x8003DEF0
		// Variables:
			struct ObjectAccess *oa; // $a2
	/* end block 1 */
	// End offset: 0x8003DF30
	// End Line: 426

	/* begin block 2 */
		// Start line: 869
	/* end block 2 */
	// End Line: 870

	/* begin block 3 */
		// Start line: 870
	/* end block 3 */
	// End Line: 871

	/* begin block 4 */
		// Start line: 872
	/* end block 4 */
	// End Line: 873

}


// autogenerated function stub: 
// void /*$ra*/ OBTABLE_RelocateObjectTune(struct Object *object /*$a0*/, long offset /*$a1*/)
void OBTABLE_RelocateObjectTune(struct Object *object, long offset)
{ // line 428, offset 0x8003df38
	/* begin block 1 */
		// Start line: 429
		// Start offset: 0x8003DF38
		// Variables:
			long id; // $a2

		/* begin block 1.1 */
			// Start line: 442
			// Start offset: 0x8003DF84
		/* end block 1.1 */
		// End offset: 0x8003DF8C
		// End Line: 444
	/* end block 1 */
	// End offset: 0x8003DF8C
	// End Line: 445

	/* begin block 2 */
		// Start line: 902
	/* end block 2 */
	// End Line: 903

}


// autogenerated function stub: 
// void /*$ra*/ OBTABLE_RelocateInstanceObject(struct _Instance *instance /*$a0*/, long offset /*$a1*/)
void OBTABLE_RelocateInstanceObject(struct _Instance *instance, long offset)
{ // line 447, offset 0x8003df9c
	/* begin block 1 */
		// Start line: 448
		// Start offset: 0x8003DF9C
		// Variables:
			long id; // $a2
	/* end block 1 */
	// End offset: 0x8003DFE8
	// End Line: 459

	/* begin block 2 */
		// Start line: 940
	/* end block 2 */
	// End Line: 941

}


// autogenerated function stub: 
// void /*$ra*/ OBTABLE_InitAnimPointers(struct _ObjectTracker *objectTracker /*$s5*/)
void OBTABLE_InitAnimPointers(struct _ObjectTracker *objectTracker)
{ // line 461, offset 0x8003dff8
	/* begin block 1 */
		// Start line: 462
		// Start offset: 0x8003DFF8
		// Variables:
			struct Object *object; // $s3

		/* begin block 1.1 */
			// Start line: 467
			// Start offset: 0x8003E038
			// Variables:
				int i; // $s2
				char *earlyOut; // $s4
				struct _G2AnimKeylist_Type **keyPtr; // $s1

			/* begin block 1.1.1 */
				// Start line: 473
				// Start offset: 0x8003E048
				// Variables:
					struct _ObjectOwnerInfo *oi; // $s0

				/* begin block 1.1.1.1 */
					// Start line: 477
					// Start offset: 0x8003E060
					// Variables:
						struct _ObjectTracker *otr; // $a2
						struct Object *ownerOb; // $a3
						int j; // $a1
						int objectIndex; // $a0
				/* end block 1.1.1.1 */
				// End offset: 0x8003E130
				// End Line: 504
			/* end block 1.1.1 */
			// End offset: 0x8003E130
			// End Line: 505
		/* end block 1.1 */
		// End offset: 0x8003E154
		// End Line: 514
	/* end block 1 */
	// End offset: 0x8003E170
	// End Line: 521

	/* begin block 2 */
		// Start line: 968
	/* end block 2 */
	// End Line: 969

}



