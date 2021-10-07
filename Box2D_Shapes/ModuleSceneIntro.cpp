#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModulePhysics.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	circle = box = rick = NULL;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->renderer->camera.x = App->renderer->camera.y = 0;

	circle = App->textures->Load("pinball/wheel.png"); 
	box = App->textures->Load("pinball/crate.png");
	rick = App->textures->Load("pinball/rick_head.png");
	slime = App->textures->Load("pinball/slime_transparent.png");

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	// TODO 5: Move all creation of bodies on 1,2,3 key press here in the scene
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		
		 circles.add(App->physics->CreateCircle(App->input->GetMouseX(), App->input->GetMouseY(), 25));
		//if(circles->body->GetPosition().x > 5) App->physics->CreateChain(App->input->GetMouseX(), App->input->GetMouseY(), slime_transparent, 64, 4);;
	}
	if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		boxes.add(App->physics->CreateRectangle(App->input->GetMouseX(), App->input->GetMouseY(), 50, 25));
	}
	if (App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
	{
		//BodyPointer* chains =  App->physics->CreateChain(App->input->GetMouseX(), App->input->GetMouseY(), slime_transparent, 64, 4);
		slimes.add(App->physics->CreateChain(App->input->GetMouseX() - 500, App->input->GetMouseY() - 500, slimeArray, 64, 1));
		
	}
	
	// TODO 7: Draw all the circles using "circle" texture
	
	
		

	p2List_item<PhysBody*>* c = slimes.getFirst();
	
	while (c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(slime, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}
	c = circles.getFirst();
	while (c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		x -= 25;
		y -= 25;
		//if (c->data->Contains(App->input->GetMouseX(), App->input->GetMouseY()))
			App->renderer->Blit(circle, x, y, NULL, 1.0f, c->data->GetRotation());
		c = c->next;
	}

	c = boxes.getFirst();

	while (c != NULL)
	{
		int x, y;
		c->data->GetPosition(x, y);
		App->renderer->Blit(box, x, y, NULL, 1.0f, c->data->GetRotation());
		
		c = c->next;
	}
	return UPDATE_CONTINUE;
}
