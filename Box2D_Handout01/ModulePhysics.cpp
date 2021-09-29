#include "Globals.h"
#include "Application.h"
#include "ModulePhysics.h"
#include "math.h"

#define METERS_TO_PIXELS(a) (a/100)
#define PIXELS_TO_METERS(b) (b*100)
// DONE 1: Include Box 2 header and library
// Done in the project settings and Application.h

ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	debug = true;
	
}

// Destructor
ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Start()
{
	LOG("Creating Physics 2D environment");

	// DONE 2: Create a private variable for the world
	// - You need to send it a default gravity
	// - You need init the world in the constructor
	// - Remember to destroy the world after using it
	b2Vec2 gravity(0.0f, 10.0f);
	world = new b2World(gravity);
	


	// DONe 4: Create a a big static circle as "ground"
	b2BodyDef groundCircleDef;
	groundCircleDef.type = b2_staticBody;
	groundCircleDef.position.Set(PIXELS_TO_METERS(500), PIXELS_TO_METERS(400));
	b2Body* groundCircle = world->CreateBody(&groundCircleDef);

	b2CircleShape groundCircleShape;
	groundCircleShape.m_radius = PIXELS_TO_METERS(150);
	b2FixtureDef groundCircleFixture;
	groundCircleFixture.shape = &groundCircleShape;
	groundCircle->CreateFixture(&groundCircleFixture);


	/*b2BodyDef groundRecDef;
	groundRecDef.type = b2_staticBody;
	groundRecDef.position.Set(PIXELS_TO_METERS(500), PIXELS_TO_METERS(600));
	b2Body* groundRec = world->CreateBody(&groundRecDef);

	b2PolygonShape* groundRecShape = new b2PolygonShape;
	groundRecShape->SetAsBox(PIXELS_TO_METERS(5000), PIXELS_TO_METERS(1000));
	b2FixtureDef groundRecFixture;
	groundRecFixture.shape = groundRecShape;
	groundRec->CreateFixture(&groundRecFixture);*/
	
	return true;
}

// 
update_status ModulePhysics::PreUpdate()
{
	// DONE 3: Update the simulation ("step" the world)
	world->Step(1.0f / 60.0f, 8, 3);

	return UPDATE_CONTINUE;
}

// 
update_status ModulePhysics::PostUpdate()
{
	// TODO 5: On space bar press, create a circle on mouse position
	// - You need to transform the position / radius

	if(App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if(!debug)
		return UPDATE_CONTINUE;

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		b2BodyDef littleCircleDef;
		littleCircleDef.type = b2_dynamicBody;
		littleCircleDef.position.Set(PIXELS_TO_METERS(App->input->GetMouseX()), PIXELS_TO_METERS(App->input->GetMouseY()));
		b2Body* littleCircleBody = world->CreateBody(&littleCircleDef);

		b2CircleShape littleCircleShape;
		littleCircleShape.m_radius = PIXELS_TO_METERS(50);
		b2FixtureDef littleCircleFixture;
		littleCircleFixture.shape = &littleCircleShape;
		littleCircleBody->CreateFixture(&littleCircleFixture);
	}

	// Bonus code: this will iterate all objects in the world and draw the circles
	// You need to provide your own macro to translate meters to pixels
	
	for(b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
		for(b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
			switch(f->GetType())
			{
				case b2Shape::e_circle:
				{
					b2CircleShape* shape = (b2CircleShape*)f->GetShape();
					b2Vec2 pos = f->GetBody()->GetPosition();
					App->renderer->DrawCircle(METERS_TO_PIXELS(pos.x), METERS_TO_PIXELS(pos.y), METERS_TO_PIXELS(shape->m_radius), 255, 255, 255);
				}
				/*case b2Shape :: e_polygon:
				{
					b2PolygonShape* shape = (b2PolygonShape*)f->GetShape();
					b2Vec2 pos = f->GetBody()->GetPosition();
					App->renderer->DrawCircle(METERS_TO_PIXELS(pos.x), METERS_TO_PIXELS(pos.y), METERS_TO_PIXELS(shape->m_radius), 255, 255, 255);
					
				}*/
				break;

				// You will have to add more cases to draw boxes, edges, and polygons ...
			}
		}
	}

	return UPDATE_CONTINUE;
}


// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");

	// Delete the whole physics world!
	delete world;
	world = nullptr;

	return true;
}
