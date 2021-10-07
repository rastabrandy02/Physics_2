#pragma once
#include "Module.h"
#include "Globals.h"
#include "Box2D/Box2D/Box2D.h"


#define GRAVITY_X 0.0f
#define GRAVITY_Y -7.0f

#define PIXELS_PER_METER 50.0f // if touched change METER_PER_PIXEL too
#define METER_PER_PIXEL 0.02f // this is 1 / PIXELS_PER_METER !

#define METERS_TO_PIXELS(m) ((int) floor(PIXELS_PER_METER * m))
#define PIXEL_TO_METERS(p)  ((float) METER_PER_PIXEL * p)

class b2World;
class b2Body;

// TODO 6: Create a small class that keeps a pointer to tghe b2Body
// and has a method to request the position
// then write the implementation in the .cpp
// Then make your circle creation function to return a pointer to that class

class PhysBody
{
public:
	
	PhysBody() : body(NULL)
	{}
	~PhysBody() {};
	void GetPosition(int &x, int &y) const
	{
		b2Vec2 pos = body->GetPosition();
		x = METERS_TO_PIXELS(pos.x) - (width);
		y = METERS_TO_PIXELS(pos.y) - (height);
		
	}
	
	float GetRotation() const
	{
		float ret = RADTODEG * body->GetAngle();
		return ret;
	}
	
	/*bool Contains(int x, int y) const;
	int RayCast(int x1, int y1, int x2, int y2, float& normal_x, float& normal_y) const;*/

public:
	b2Body* body;
	int width = 0; 
	int height = 0;
	
	
};
class ModulePhysics : public Module
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	bool Start();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();

	// TODO 4: Move body creation to 3 functions to create circles, rectangles and chains
	PhysBody* CreateCircle(int x, int y, int radius);
	PhysBody* CreateRectangle(int x, int y, int hx, int hy);
	PhysBody* CreateChain(int x, int y, int* points, int num, int scaleDown);
private:

	bool debug;
	b2World* world;
};