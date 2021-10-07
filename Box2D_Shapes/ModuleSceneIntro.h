#pragma once
#include "Module.h"
#include "p2List.h"
#include "Globals.h"

class PhysBody;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* circle;
	SDL_Texture* box;
	SDL_Texture* rick;
	SDL_Texture* slime;

	//BodyPointer* chains;
	p2List<PhysBody*> circles;
	p2List<PhysBody*> boxes;
	p2List <PhysBody*> slimes;

int slimeArray[64] = {
575, 365,
553, 333,
533, 270,
518, 198,
499, 155,
473, 158,
459, 190,
445, 251,
429, 296,
410, 330,
354, 368,
273, 405,
207, 448,
160, 497,
124, 574,
128, 667,
171, 734,
229, 775,
288, 797,
350, 809,
429, 816,
503, 816,
568, 807,
651, 788,
708, 760,
762, 715,
797, 656,
810, 565,
781, 489,
739, 448,
684, 416,
619, 389
	};
};
