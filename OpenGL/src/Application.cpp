#include "Utils.h"
#include "Input.h"
#include "Camera.h"
#include "Texture.h"
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include "Light.h"
#include "Material.h"
#include "Model.h"
#include "Terrain.h"

class Player : public GameObject
{
private:
	Model* model;

	double prevMouseX = 0;
	double prevMouseY = 0;
	double dx = 0;
	double dy = 0;
	double zoom = 2;
	double cameraHeight = 0.3;
	float diagonalRotation = 0;
	float previewRotation = 0;

	float speed = 4;
	bool running = false;

	bool previewing = false;

	float vsp = 0;
	float gravity = 0.1;

public:
	Player()
	{
		model = new Model("res/models/spider/spider.fbx");
		model->scale = { 0.1f, 0.1f, 0.1f };
		model->currentAnimation = "Spider_Armature|breathe";

		prevMouseX = Input::mousex();
		prevMouseY = Input::mousex();
	}

	bool isColliding(glm::vec3 position)
	{
		return position.y <= 0;
	}

	void update(float delta, Camera* camera)
	{
		zoom -= Input::scrolly() * delta * 5;
		Input::scrolly(0);
		zoom = clamp(zoom, 0.5, 4.0);
		dx = Input::mousex() - prevMouseX;
		dy = Input::mousey() - prevMouseY;
		if (Input::mouseright())
		{
			cameraHeight += dy * delta / 10;
			cameraHeight = clamp(cameraHeight, -1.0, 1.0);
		}
		prevMouseX = Input::mousex();
		prevMouseY = Input::mousey();
		previewing = Input::lctrl();
		running = Input::lshift();
		float hspx = (Input::d() - Input::a()) * (running + 1);
		float hspz = (Input::s() - Input::w()) * (running + 1);
 
		previewRotation -= dx * delta * 2;
		camera->target = position;
		camera->position.x = position.x + zoom * sin(glm::radians(previewRotation));
		camera->position.y = position.y + zoom * cameraHeight;
		camera->position.z = position.z + zoom * cos(glm::radians(previewRotation));

		if (!previewing)
			rotation.z = previewRotation;

		if (Input::r())
		{
			position = { 0, 1, 0 };
			vsp = 0;
		}

		if (!isColliding(position + glm::vec3(0, vsp*delta, 0)))
		{
			vsp -= gravity;
		}
		else
		{
			position.y = 0;
			vsp = 0;
		}

		if (isColliding(position + glm::vec3(0, -0.1, 0)))
		{
			if (Input::space())
			{
				Input::space(false);
				vsp += 4;
			}
		}

		position.x += hspz * sin(glm::radians(rotation.z)) * delta;
		position.z += hspz * cos(glm::radians(rotation.z)) * delta;
		position.x += hspx * sin(glm::radians(rotation.z+90)) * delta;
		position.z += hspx * cos(glm::radians(rotation.z+90)) * delta;
		position.y += vsp * delta;

		if (hspx == 0 && hspz == 0)
		{
			model->currentAnimation = "Spider_Armature|breathe";
		}
		else
		{
			if (hspz != 0 && hspx != 0)
			{
				diagonalRotation = sign(hspx) * sign(hspz)*45;
			}
			else
			{
				diagonalRotation = 0;
			}

			if (hspz != 0)
			{
				if (hspz == 1)
					model->currentAnimation = "Spider_Armature|walk_front";
				if (hspz == -1)
					model->currentAnimation = "Spider_Armature|walk_back";
				if (hspz == 2)
					model->currentAnimation = "Spider_Armature|run_front";
				if (hspz == -2)
					model->currentAnimation = "Spider_Armature|run_back";
			}
			else
			{
				if (hspx == 1)
					model->currentAnimation = "Spider_Armature|walk_right";
				if (hspx == -1)
					model->currentAnimation = "Spider_Armature|walk_left";
				if (hspx == 2)
					model->currentAnimation = "Spider_Armature|run_right";
				if (hspx == -2)
					model->currentAnimation = "Spider_Armature|run_left";

			}
		}

		if (vsp != 0)
		{
			model->currentAnimation = "Spider_Armature|fall";
		}
			

		model->rotation = rotation + glm::vec3(-90, 0, diagonalRotation);
		model->position = position + glm::vec3(0, 0.2f, 0);
		model->update(delta*speed/2.0f);
	}

	void draw(Shader* shader, Camera* camera, std::vector<Light*>* lights)
	{
		model->draw(shader, camera, lights);
	}
};

int scene1();
int scene2();
int scene3();
int scene4();

int main()
{
	scene1();
}

int scene1()
{
	init();
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	//glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	GLFWwindow* window = createWindow(1920, 1080, "OpenGL", true);
	glfwSetKeyCallback(window, keyboard_callback);
	glfwSetCursorPosCallback(window, mousepos_callback);
	glfwSetMouseButtonCallback(window, mousebutton_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	Shader* shader = new Shader("res/shaders/blinn-phong.vs", "res/shaders/blinn-phong.fs");
	Player player;
	Material* floorMaterial = new Material(glm::vec3(0), glm::vec3(0), glm::vec3(0));
	floorMaterial->setDiffuseTexture(new Texture("res/textures/grass/diffuse.png", GL_RGBA));

	Model* floor = new Model(Mesh::generate_plane(floorMaterial));
	floor->scale = { 10, 1, 10 };

	std::vector<Light*> lights;
	Light* directionalLight = new Light();
	directionalLight->type = Light::DirectionalLight;
	directionalLight->direction = { -0.2f, -1.0f, -0.3f };
	lights.push_back(directionalLight);

	Camera* camera = new Camera();
	camera->lookAtTarget = true;

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	float delta = 0;

	while (!glfwWindowShouldClose(window))
	{
		float time = glfwGetTime();
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		floor->draw(shader, camera, &lights);
		player.update(delta, camera);
		player.draw(shader, camera, &lights);

		glfwSwapBuffers(window);
		if (Input::escape())
			glfwSetWindowShouldClose(window, true);
		glfwPollEvents();

		delta = glfwGetTime() - time;
	}

	glfwTerminate();

	return 0;
}

int scene2()
{
	init();
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	//glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	GLFWwindow* window = createWindow(1920, 1080, "OpenGL", true);
	glfwSetKeyCallback(window, keyboard_callback);
	glfwSetCursorPosCallback(window, mousepos_callback);
	glfwSetMouseButtonCallback(window, mousebutton_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	Shader* shader = new Shader("res/shaders/blinn-phong.vs", "res/shaders/blinn-phong.fs");

	std::vector<Light*> lights;
	Light* pointLight = new Light();
	float range = 10;
	float maxRange = 100;
	float minRange = 0;
	pointLight->setRange(10);
	lights.push_back(pointLight);
	Light* directionalLight = new Light();
	directionalLight->type = Light::DirectionalLight;

	Terrain t1(64, 64, 64, Material::Default(), false);
	Terrain t2(64, 64, 64, Material::Default(), true);
	t1.position.x -= 32;
	t2.position.x += 32;

	Camera* camera = new Camera();

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	float delta = 0;

	while (!glfwWindowShouldClose(window))
	{
		float time = glfwGetTime();
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//camera movement
		float xAxis = Input::d() - Input::a();
		float yAxis = Input::space() - Input::lctrl();
		float zAxis = Input::w() - Input::s();
		glm::vec3 deltaPosition = { 0, 0, 0 };
		deltaPosition += zAxis * glm::normalize(camera->front);
		deltaPosition += yAxis * glm::normalize(camera->up);
		deltaPosition += xAxis * glm::normalize(glm::cross(camera->front, camera->up));
		camera->position += deltaPosition * 5.0f * delta;
		camera->update(delta);

		pointLight->diffuse = glm::vec3((cos(time) + 1.0f) / 2.0f, (sin(time * 2.0f) + 1.0f) / 2.0f, (cos(time * -2.0f) + 1.0f) / 2.0f);
		pointLight->position = camera->position;
		range += Input::scrolly();
		Input::scrolly(0);
		range = clamp(range, minRange, maxRange);
		pointLight->setRange(range);
		if (Input::b())
		{
			Input::b(false);
			if (lights.size() == 1)
				lights.push_back(directionalLight);
			else
				lights.pop_back();
		}

		t1.draw(shader, camera, &lights);
		t2.draw(shader, camera, &lights);

		glfwSwapBuffers(window);
		if (Input::escape())
			glfwSetWindowShouldClose(window, true);
		glfwPollEvents();

		delta = glfwGetTime() - time;
	}

	glfwTerminate();

	return 0;
}

int scene3()
{
	init();
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	//glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	GLFWwindow* window = createWindow(1920, 1080, "OpenGL", true);
	glfwSetKeyCallback(window, keyboard_callback);
	glfwSetCursorPosCallback(window, mousepos_callback);
	glfwSetMouseButtonCallback(window, mousebutton_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	float delta = 0;

	Shader* shader = new Shader("res/shaders/blackhole.vs", "res/shaders/blackhole.fs");

	float vertices[] = {
		 -1.0f, 1.0f,
		 1.0f, 1.0f,
		 -1.0f, -1.0f,
		 1.0f, -1.0f
	};

	unsigned int elements[] = {
		0, 1, 2,
		1, 2, 3
	};

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	shader->bind();

	while (!glfwWindowShouldClose(window))
	{
		float time = glfwGetTime();
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader->setUniform2f("iResolution", glm::vec2(1920, 1080));
		shader->setUniform1f("iTime", time);
		shader->setUniform2f("iMouse", glm::vec2(Input::mousex(), Input::mousey()));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, elements);

		glfwSwapBuffers(window);
		if (Input::escape())
			glfwSetWindowShouldClose(window, true);
		glfwPollEvents();

		delta = glfwGetTime() - time;
	}

	glfwTerminate();

	return 0;
}

int scene4()
{
	init();
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	//glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
	GLFWwindow* window = createWindow(1920, 1080, "OpenGL", true);
	glfwSetKeyCallback(window, keyboard_callback);
	glfwSetCursorPosCallback(window, mousepos_callback);
	glfwSetMouseButtonCallback(window, mousebutton_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	Shader* shdPhong = new Shader("res/shaders/phong.vs", "res/shaders/phong.fs");
	Shader* shdBlinnPhong = new Shader("res/shaders/blinn-phong.vs", "res/shaders/blinn-phong.fs");
	Shader* shdLight = new Shader("res/shaders/light.vs", "res/shaders/light.fs");
	Shader* shdCurrent = shdBlinnPhong;

	std::vector<Material*> materials
	{
		new Material(new Texture("res/textures/container/diffuse.png", GL_SRGB_ALPHA), new Texture("res/textures/container/specular.png", GL_RGBA)),
		new Material(new Texture("res/textures/earth/diffuse.png", GL_SRGB_ALPHA), new Texture("res/textures/earth/specular.png", GL_RGBA)),
		Material::Default(),
	
		Material::Emerald(),
		Material::Jade(),
		Material::Obsidian(),
		Material::Pearl(),
		Material::Ruby(),
		
		Material::Turquoise(),
		Material::Brass(),
		Material::Bronze(),
		Material::Chrome(),
		Material::Copper(),
		Material::Gold(),
		Material::Silver(),
	
		Material::Black_plastic(),
		Material::Cyan_plastic(),
		Material::Green_plastic(),
		Material::Red_plastic(),
		Material::White_plastic(),
		Material::Yellow_plastic(),
		
		Material::Black_rubber(),
		Material::Cyan_rubber(),
		Material::Green_rubber(),
		Material::Red_rubber(),
		Material::White_rubber(),
		Material::Yellow_rubber(),
	};

	std::vector<Model*> models;

	Model* spider = new Model("res/models/spider/spider.fbx");
	spider->position = { 2.0f, 0, 2.0f };
	spider->scale = { 0.1f, 0.1f, 0.1f };
	spider->rotation.x = -90.0f;
	spider->currentAnimation = "Spider_Armature|die";
	spider->printAnimationNames();
	models.push_back(spider);

	Model* female = new Model("res/models/female/female.obj");
	female->scale = { 0.01f, 0.01f, 0.01f };
	female->position = { -2.0f, 0, 2.0f };
	models.push_back(female);

	Model* pigeon = new Model("res/models/pigeon/pigeon.obj");
	pigeon->scale = { 0.1f, 0.1f, 0.1f };
	pigeon->position = { 1.75f, 0.5f, 0.0f };
	pigeon->rotation.y = -90.0f;
	models.push_back(pigeon);

	Model* jeep = new Model("res/models/jeep/jeep.obj");
	jeep->position = { 2.0f, 0.0f, 4.0f };
	jeep->rotation.y = -90.0f;
	models.push_back(jeep);

	Model* character = new Model("res/models/character/character.fbx");
	character->rotation.x = -90.0f;
	character->scale = { 0.2f, 0.2f, 0.2f };
	character->position = { -2.0f, 0.0f, 4.0f };
	character->currentAnimation = "Armature|ArmatureAction";
	models.push_back(character);

	Model* wolf = new Model("res/models/wolf/wolf.fbx");
	wolf->rotation.x = -90.0f;
	wolf->scale = { 0.1f, 0.1f, 0.1f };
	wolf->position = { -2.0f, 0.0f, 6.0f };
	wolf->currentAnimation = "wolf_rig|running";
	models.push_back(wolf);

	for (int i = 0; i < materials.size(); ++i)
	{
		Model* cube = new Model(Mesh::generate_cube(materials[i]));
		cube->position = { 2.0f , 0.0f, -i * 2.0f };
		models.push_back(cube);

		Model* sphere = new Model(Mesh::generate_uvsphere(materials[i]));
		sphere->position = { -2.0f, 0.0f, -i * 2.0f };
		models.push_back(sphere);
	}

	Model* lightModel = new Model(Mesh::generate_uvsphere(Material::Default()));
	lightModel->scale = { 0.2, 0.2, 0.2 };
	std::vector<Light*> lights;
	Light* pointLight = new Light();
	lights.push_back(pointLight);
	Light* directionalLight = new Light();
	directionalLight->type = Light::DirectionalLight;
	lights.push_back(directionalLight);
	Light* spotLight = new Light();
	spotLight->type = Light::SpotLight;
	lights.push_back(spotLight);

	Material* terrainMaterial = new Material(new Texture("res/textures/grass/diffuse.png", GL_SRGB_ALPHA));
	terrainMaterial->specular = { 0,0,0 };
	Terrain terrain(64, 64, 64, terrainMaterial, false, true);
	terrain.scale = glm::vec3(1.0f / terrain.width, 1.0f / terrain.height, 1.0f / terrain.depth);

	Camera* camera = new Camera();

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);

	float delta = 0;

	while (!glfwWindowShouldClose(window))
	{
		float time = glfwGetTime();
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//camera movement
		float xAxis = Input::d() - Input::a();
		float yAxis = Input::space() - Input::lctrl();
		float zAxis = Input::w() - Input::s();
		glm::vec3 deltaPosition = { 0, 0, 0 };
		deltaPosition += zAxis * glm::normalize(camera->front);
		deltaPosition += yAxis * glm::normalize(camera->up);
		deltaPosition += xAxis * glm::normalize(glm::cross(camera->front, camera->up));
		camera->position += deltaPosition * 5.0f *  delta;
		camera->update(delta);
		
		//lights
		for (Light* light : lights)
		{
			if (light->type == Light::PointLight)
			{
				lightModel->position = light->position;
				shdLight->bind();
				shdLight->setUniform3f("color", light->diffuse);
				lightModel->draw(shdLight, camera);
			}
		}
		spotLight->position = camera->position;
		spotLight->direction = camera->direction;
		pointLight->diffuse = glm::vec3((cos(time) + 1.0f) / 2.0f, (cos(time * 2.0f) + 1.0f) / 2.0f, (cos(time * -2.0f) + 1.0f) / 2.0f);
		pointLight->position.x = 3.0f * cos(time);
		pointLight->position.y = 2.0;
		pointLight->position.z = 3.0f * sin(time);

		if (Input::f())
		{
			Input::f(false);
			if (spotLight->range != 0.0f)
				spotLight->setRange(0.0f);
			else
				spotLight->setRange(5.0f);
		}

		if (Input::b())
		{
			Input::b(false);
			if (shdCurrent == shdPhong)
				shdCurrent = shdBlinnPhong;
			else
				shdCurrent = shdPhong;
		}

		//models
		for (Model* model : models)
		{
			model->update(delta);
			model->draw(shdCurrent, camera, &lights);
		}

		terrain.draw(shdCurrent, camera, &lights);
		
		
		
		glfwSwapBuffers(window);
		if (Input::escape())
			glfwSetWindowShouldClose(window, true);
		glfwPollEvents();

		delta = glfwGetTime() - time;
	}

	glfwTerminate();

	return 0;
}