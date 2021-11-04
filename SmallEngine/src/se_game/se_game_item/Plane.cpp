#include <se_game/se_game_item/Plane.h>

Plane::Plane(vec2 size)
{
	if (size[0] <= 0 || size[1] <= 0)
	{
		LOGGER_ERROR("Plane size not greater than 0!");
		return;
	}
	float half_size_x = size[0] / 2;
	float half_size_z = size[1] / 2;

	float positions[12] = {
		-half_size_x, 0.0, -half_size_z,
		half_size_x, 0.0, -half_size_z,
		half_size_x, 0.0, half_size_z,
		-half_size_x, 0.0, half_size_z,
	};

	float normals[12] = {
		0, 1, 0, 
		0, 1, 0,
		0, 1, 0,
		0, 1, 0
	};

	float textureCoords[8] = {
		0.0, 0.0, 
		1.0, 0.0,
		1.0, 1.0,
		0.0, 1.0,
	};
	int indices[6] = {
		0, 1, 2, 
		0, 2, 3
	};

	this->mesh = new Mesh(positions, 4, textureCoords, 4, normals, 4, indices, 6);
}

Plane::~Plane()
{

}