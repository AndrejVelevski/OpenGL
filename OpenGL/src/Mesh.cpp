#include "Mesh.h"
#include <glad\glad.h>
#include <iostream>

Mesh::Mesh()
{

}

Mesh::~Mesh()
{
	delete material;
}

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& elements, Material* material)
{
	create(vertices, elements, material);
}

void Mesh::create(std::vector<Vertex>& vertices, std::vector<unsigned int>& elements, Material* material)
{
	this->vertices = vertices;
	this->elements = elements;
	this->material = material;

	vbo.create(vertices);
	ebo.create(elements);
	vao.create(vbo, ebo);
}

void Mesh::draw(Shader* shader)
{
	vao.bind();

	if (shader != nullptr)
	{
		shader->bind();

		if (material != nullptr)
		{
			shader->setUniform1i("material.type", material->type);

			shader->setUniform3f("material.ambient", material->ambient);
			shader->setUniform3f("material.diffuse", material->diffuse);
			shader->setUniform3f("material.specular", material->specular);
			shader->setUniform1f("material.shininess", material->shininess);

			if ((material->type & Material::DiffuseTex) == Material::DiffuseTex)
			{
				if (material->diffuseTex != nullptr)
				{
					material->diffuseTex->bind(0);
					shader->setUniform1i("material.diffuseTex", 0);
				}
			}
			if ((material->type & Material::SpecularTex) == Material::SpecularTex)
			{
				if (material->specularTex != nullptr)
				{
					material->specularTex->bind(1);
					shader->setUniform1i("material.specularTex", 1);
				}
			}
		}
	}

	glDrawElements(GL_TRIANGLES, elements.size(), GL_UNSIGNED_INT, nullptr);
}

Mesh* Mesh::generate_plane(Material* material)
{
	std::vector<Vertex> vertices
	{
		Vertex({-0.5f,  0.0f, -0.5f}, { 0.0f, 1.0f}, { 0.0f,  1.0f,  0.0f}),
		Vertex({ 0.5f,  0.0f, -0.5f}, { 1.0f, 1.0f}, { 0.0f,  1.0f,  0.0f}),
		Vertex({ 0.5f,  0.0f,  0.5f}, { 1.0f, 0.0f}, { 0.0f,  1.0f,  0.0f}),
		Vertex({-0.5f,  0.0f,  0.5f}, { 0.0f, 0.0f}, { 0.0f,  1.0f,  0.0f})
	};

	std::vector<unsigned int> elements
	{
		2, 1, 0, 3, 2, 0
	};

	return new Mesh(vertices, elements, material);
}

Mesh* Mesh::generate_cube(Material* material)
{
	std::vector<Vertex> vertices
	{
		//front												 
		Vertex({-0.5f,  0.5f,  0.5f}, { 0.0f, 1.0f}, { 0.0f,  0.0f,  1.0f}), //0 
		Vertex({ 0.5f,  0.5f,  0.5f}, { 1.0f, 1.0f}, { 0.0f,  0.0f,  1.0f}), //1 
		Vertex({ 0.5f, -0.5f,  0.5f}, { 1.0f, 0.0f}, { 0.0f,  0.0f,  1.0f}), //2 
		Vertex({-0.5f, -0.5f,  0.5f}, { 0.0f, 0.0f}, { 0.0f,  0.0f,  1.0f}), //3 

		//right												 
		Vertex({ 0.5f,  0.5f,  0.5f}, { 0.0f, 1.0f}, { 1.0f,  0.0f,  0.0f}), //1
		Vertex({ 0.5f,  0.5f, -0.5f}, { 1.0f, 1.0f}, { 1.0f,  0.0f,  0.0f}), //5
		Vertex({ 0.5f, -0.5f, -0.5f}, { 1.0f, 0.0f}, { 1.0f,  0.0f,  0.0f}), //6
		Vertex({ 0.5f, -0.5f,  0.5f}, { 0.0f, 0.0f}, { 1.0f,  0.0f,  0.0f}), //2

		//back												 
		Vertex({ 0.5f,  0.5f, -0.5f}, { 0.0f, 1.0f}, { 0.0f,  0.0f, -1.0f}), //5
		Vertex({-0.5f,  0.5f, -0.5f}, { 1.0f, 1.0f}, { 0.0f,  0.0f, -1.0f}), //4
		Vertex({-0.5f, -0.5f, -0.5f}, { 1.0f, 0.0f}, { 0.0f,  0.0f, -1.0f}), //7
		Vertex({ 0.5f, -0.5f, -0.5f}, { 0.0f, 0.0f}, { 0.0f,  0.0f, -1.0f}), //6

		//left												 
		Vertex({-0.5f,  0.5f, -0.5f}, { 0.0f, 1.0f}, {-1.0f,  0.0f,  0.0f}), //4
		Vertex({-0.5f,  0.5f,  0.5f}, { 1.0f, 1.0f}, {-1.0f,  0.0f,  0.0f}), //0
		Vertex({-0.5f, -0.5f,  0.5f}, { 1.0f, 0.0f}, {-1.0f,  0.0f,  0.0f}), //3
		Vertex({-0.5f, -0.5f, -0.5f}, { 0.0f, 0.0f}, {-1.0f,  0.0f,  0.0f}), //7

		//top												 	    
		Vertex({-0.5f,  0.5f, -0.5f}, { 0.0f, 1.0f}, { 0.0f,  1.0f,  0.0f}), //4
		Vertex({ 0.5f,  0.5f, -0.5f}, { 1.0f, 1.0f}, { 0.0f,  1.0f,  0.0f}), //5
		Vertex({ 0.5f,  0.5f,  0.5f}, { 1.0f, 0.0f}, { 0.0f,  1.0f,  0.0f}), //1
		Vertex({-0.5f,  0.5f,  0.5f}, { 0.0f, 0.0f}, { 0.0f,  1.0f,  0.0f}), //0

		//bottom												    
		Vertex({-0.5f, -0.5f,  0.5f}, { 0.0f, 1.0f}, { 0.0f, -1.0f,  0.0f}), //3 
		Vertex({ 0.5f, -0.5f,  0.5f}, { 1.0f, 1.0f}, { 0.0f, -1.0f,  0.0f}), //2 
		Vertex({ 0.5f, -0.5f, -0.5f}, { 1.0f, 0.0f}, { 0.0f, -1.0f,  0.0f}), //6
		Vertex({-0.5f, -0.5f, -0.5f}, { 0.0f, 0.0f}, { 0.0f, -1.0f,  0.0f}), //7
	};

	std::vector<unsigned int> elements
	{
		2, 1, 0, 3, 2, 0,
		6, 5, 4, 7, 6, 4,
		10, 9, 8, 11, 10, 8,
		14, 13, 12, 15, 14, 12,
		18, 17, 16, 19, 18, 16,
		22, 21, 20, 23, 22, 20
	};

	return new Mesh(vertices, elements, material);
}

Mesh* Mesh::generate_uvsphere(Material* material, unsigned int meridians, unsigned int parallels)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> elements;

	float radius = 0.5f;
	float incm = glm::pi<float>() / (float)parallels; //y
	float incp = 2.0 * glm::pi<float>() / (float)meridians; //xz
	glm::vec3 sp(0, 0, 0);

	for (int i = 0; i < meridians; ++i)
	{
		glm::vec2 t;

		sp.y = -glm::pi<float>() / 2.0f;

		for (int j = 0; j <= parallels; ++j)
		{
			glm::vec3 p;
			
			p.x = radius * cos(sp.x) * cos(sp.y);
			p.y = radius * sin(sp.y);
			p.z = radius * sin(sp.z) * cos(sp.y);

			t.x = 1.0f - (float)i / meridians;
			t.y = (float)j / parallels;

			vertices.push_back(Vertex(p, t, p));

			p.x = radius * cos(sp.x + incp) * cos(sp.y);
			p.y = radius * sin(sp.y);
			p.z = radius * sin(sp.z + incp) * cos(sp.y);

			t.x = 1.0f - (float)(i+1) / meridians;

			vertices.push_back(Vertex(p, t, p));

			if (j < parallels)
			{
				elements.push_back(2 * i * (parallels + 1) + 2 * j + 0);
				elements.push_back(2 * i * (parallels + 1) + 2 * j + 2);
				elements.push_back(2 * i * (parallels + 1) + 2 * j + 1);
													    
				elements.push_back(2 * i * (parallels + 1) + 2 * j + 2);
				elements.push_back(2 * i * (parallels + 1) + 2 * j + 3);
				elements.push_back(2 * i * (parallels + 1) + 2 * j + 1);
			}

			sp.y += incm;
		}

		sp.x += incp;
		sp.z += incp;
	}

	return new Mesh(vertices, elements, material);
}

Mesh* Mesh::generate_quadsphere(Material* material, unsigned int xseams, unsigned int yseams, unsigned int zseams)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> elements;

	float xinc = 1.0f / (xseams - 1);
	float yinc = 1.0f / (yseams - 1);
	float zinc = 1.0f / (zseams - 1);

	glm::vec3 p;
	glm::vec2 t;

	unsigned int eps = 4 * (xseams-1) * (yseams-1);

	//front
	p = { -0.5f, -0.5f, 0.5f };
	t = { 0.0f, 0.0f };
	for (int y = 0; y < yseams; ++y)
	{
		p.x = -0.5f;
		for (int x = 0; x < xseams; ++x)
		{
			glm::vec3 tp = glm::normalize(p);

			vertices.push_back(Vertex(p, t, p));

			if (x < xseams - 1 && y < yseams - 1)
			{
				elements.push_back(0 * eps + ((y + 0) * xseams + x + 0));
				elements.push_back(0 * eps + ((y + 0) * xseams + x + 1));
				elements.push_back(0 * eps + ((y + 1) * xseams + x + 0));

				elements.push_back(0 * eps + ((y + 1) * xseams + x + 0));
				elements.push_back(0 * eps + ((y + 0) * xseams + x + 1));
				elements.push_back(0 * eps + ((y + 1) * xseams + x + 1));
			}

			p.x += xinc;
			t.x += xinc;
		}
		p.y += yinc;
		t.y += yinc;
	}

	//back
	p = { -0.5f, -0.5f, -0.5f };
	t = { 0.0f, 0.0f };
	for (int y = 0; y < yseams; ++y)
	{
		p.x = -0.5f;
		for (int x = 0; x < xseams; ++x)
		{
			glm::vec3 tp = glm::normalize(p);

			vertices.push_back(Vertex(p, t, p));

			if (x < xseams - 1 && y < yseams - 1)
			{
				elements.push_back(1 * eps + ((y + 0) * xseams + x + 0));
				elements.push_back(1 * eps + ((y + 1) * xseams + x + 0));
				elements.push_back(1 * eps + ((y + 0) * xseams + x + 1));
								   
				elements.push_back(1 * eps + ((y + 1) * xseams + x + 0));
				elements.push_back(1 * eps + ((y + 1) * xseams + x + 1));
				elements.push_back(1 * eps + ((y + 0) * xseams + x + 1));
			}

			p.x += xinc;
			t.x += xinc;
		}
		p.y += yinc;
		t.y += yinc;
	}

	std::cout << vertices.size() << std::endl;
	for (int i = 0; i < elements.size(); ++i)
		std::cout << elements[i] << std::endl;


	return new Mesh(vertices, elements, material);
}
