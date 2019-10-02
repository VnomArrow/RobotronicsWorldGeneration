#pragma once
#include "world_info.h"
#include <string>
#include <fstream>

const std::string obj_normals = 
"vn -1.0000 0.0000 0.0000\n"
"vn 1.0000 0.0000 0.0000\n"
"vn 0.0000 -1.0000 0.0000\n"
"vn 0.0000 1.0000 0.0000\n"
"vn 0.0000 0.0000 -1.0000\n"
"vn 0.0000 0.0000 1.0000\n";

const int add_order[3][5][3] = {
		{{0, 0, 0}, {0, 0, 1}, {0, 1, 1}, {0, 1, 0}, {1, 0, 0}},
		{{0, 0, 0}, {1, 0, 0}, {1, 0, 1}, {0, 0, 1}, {0, 1, 0}},
		{{0, 0, 0}, {0, 1, 0}, {1, 1, 0}, {1, 0, 0}, {0, 0, 1}} };

int* get_block_ptr(int* block, int size, int x, int y, int z) {
	return &block[x * WORLDSIZE*WORLDSIZE + 
		y * WORLDSIZE + 
		z];
}

int* get_corner_ptr(int* corner, int x, int y, int z) {
	return &corner[x * (WORLDSIZE + 1) * (WORLDSIZE + 1) + 
		y * (WORLDSIZE + 1) +
		z];
}

inline void check_corner(int* corner_num,
	std::string& corners,
	int& corner_count,
	int x,
	int y,
	int z){
	if (*get_corner_ptr(corner_num, x, y, z) == 0) {
		*get_corner_ptr(corner_num, x, y, z) = corner_count;
		corner_count++;
		corners += "v " + std::to_string(x) + ".00000 " +
			std::to_string(y) + ".00000 " +
			std::to_string(z) + ".00000\n";
	}
}

inline void ensure_corners_x(int* corner_num,
	std::string& corners,
	int& corner_count,
	int x,
	int y,
	int z) {
	for (int y2 = y; y2 < y + 2; ++y2) {
		for (int z2 = z; z2 < z + 2; ++z2) {
			check_corner(corner_num, corners, corner_count, x, y2, z2);
		}
	}
}
inline void ensure_corners_y(int* corner_num,
	std::string& corners,
	int& corner_count,
	int x,
	int y,
	int z) {
	for (int x2 = x; x2 < x + 2; ++x2) {
		for (int z2 = z; z2 < z + 2; ++z2) {
			check_corner(corner_num, corners, corner_count, x2, y, z2);
		}
	}
}
inline void ensure_corners_z(int* corner_num,
	std::string& corners,
	int& corner_count,
	int x,
	int y,
	int z) {
	for (int x2 = x; x2 < x + 2; ++x2) {
		for (int y2 = y; y2 < y + 2; ++y2) {
			check_corner(corner_num, corners, corner_count, x2, y2, z);
		}
	}
}

void add_face(int* block,
	std::string(&material_faces)[MATERIALCOUNT],
	int* corner_num,
	int& face_count,
	int x,
	int y,
	int z,
	int add_order_num,
	bool reversed) {
	std::string face_string = "f ";
	if (reversed) {
		for (int i = 3; i >= 0; --i) {
			face_string +=
				std::to_string(*get_corner_ptr(corner_num, 
					x + add_order[add_order_num][i][0], 
					y + add_order[add_order_num][i][1], 
					z + add_order[add_order_num][i][2])) + "//" +
				std::to_string(add_order_num*2 + 2) + " ";
		}
		face_string += "\n";
		material_faces[*get_block_ptr(block, WORLDSIZE,
			x - add_order[add_order_num][4][0],
			y - add_order[add_order_num][4][1],
			z - add_order[add_order_num][4][2])] += face_string;
	}
	else {
		for (int i = 0; i < 4; ++i) {
			face_string +=
				std::to_string(*get_corner_ptr(corner_num,
					x + add_order[add_order_num][i][0],
					y + add_order[add_order_num][i][1],
					z + add_order[add_order_num][i][2])) + "//" +
				std::to_string(add_order_num * 2 + 1) + " ";
		}
		face_string += "\n";
		material_faces[*get_block_ptr(block, WORLDSIZE,
			x,
			y,
			z)] += face_string;
	}
}


void append_empty_sides(int*block, 
	std::string (&material_faces)[MATERIALCOUNT],
	std::string& corners,
	int* corner_num,
	int& corner_count,
	int& face_count,
	int &x,
	int &y,
	int &z) {
	if (*get_block_ptr(block, WORLDSIZE, x-1, y, z) == 0) {
		ensure_corners_x(corner_num, corners, corner_count, x, y, z);
		add_face(block, material_faces, corner_num, face_count, x, y, z, 0, false);
	}
	if (*get_block_ptr(block, WORLDSIZE, x + 1, y, z) == 0) {
		ensure_corners_x(corner_num, corners, corner_count, x + 1, y, z);
		add_face(block, material_faces, corner_num, face_count, x + 1, y, z, 0, true);
	}
	if (*get_block_ptr(block, WORLDSIZE, x, y - 1, z) == 0) {
		ensure_corners_y(corner_num, corners, corner_count, x, y, z);
		add_face(block, material_faces, corner_num, face_count, x, y, z, 1, false);
	}
	if (*get_block_ptr(block, WORLDSIZE, x, y + 1, z) == 0) {
		ensure_corners_y(corner_num, corners, corner_count, x, y + 1, z);
		add_face(block, material_faces, corner_num, face_count, x, y + 1, z, 1, true);
	}
	if (*get_block_ptr(block, WORLDSIZE, x, y, z - 1) == 0) {
		ensure_corners_z(corner_num, corners, corner_count, x, y, z);
		add_face(block, material_faces, corner_num, face_count, x, y, z, 2, false);
	}
	if (*get_block_ptr(block, WORLDSIZE, x, y, z + 1) == 0) {
		ensure_corners_z(corner_num, corners, corner_count, x, y, z + 1);
		add_face(block, material_faces, corner_num, face_count, x, y, z + 1, 2, true);
	}
}

void write_mtl_file(std::string filename) {
	std::ofstream myfile;
	myfile.open(filename + ".mtl");
	std::string init_mtl =
		"# Blender MTL File : 'None'\n"
		"# Material Count : " + std::to_string(MATERIALCOUNT) + "\n";

	std::cout << init_mtl;
	myfile << init_mtl;

	std::string num_str;
	for (int i = 0; i < MATERIALCOUNT; ++i) {
		num_str = "00" + std::to_string(i);
		num_str = num_str.substr(num_str.size() - 3, num_str.size());
		num_str = "newmtl Material." + num_str + "\n";
		std::cout << num_str;
		myfile << num_str;
		std::cout << block_type::material_info[i] + "\n";
		myfile << block_type::material_info[i] + "\n";
	}
}

void save_as_obj(int* block, std::string filename) {
	std::string material_faces[MATERIALCOUNT];
	int* corner_num = new int[(WORLDSIZE+1) * (WORLDSIZE + 1) * (WORLDSIZE + 1)];
	for (int i = 0; i < (WORLDSIZE + 1) * (WORLDSIZE + 1) * (WORLDSIZE + 1); ++i) {
		corner_num[i] = 0;
	}
	int corner_count = 1;
	int face_count = 1;
	std::string corners = "";

	for (int x = 1; x < WORLDSIZE - 1; ++x) {
		for (int y = 1; y < WORLDSIZE - 1; ++y) {
			for (int z = 1; z < WORLDSIZE - 1; ++z) {
				if (*get_block_ptr(block, WORLDSIZE, x, y, z) != 0) {
					append_empty_sides(block, material_faces, corners, corner_num, corner_count, face_count, x, y, z);
				}
			}
		}
	}
	std::ofstream myfile;
	myfile.open(filename + ".obj");
	std::string init_obj = "# Blender v2.79 (sub 0) OBJ File : ''\n"
		"# www.blender.org\n"
		"mtllib " + filename + ".mtl\n"
		"o Cube.001_Cube.001\n";
	std::cout << init_obj;
	myfile << init_obj;

	std::string num_str;
	std::cout << corners;
	myfile << corners;
	std::cout << obj_normals;
	myfile << obj_normals;
	for (int i = 0; i < MATERIALCOUNT; ++i) {
		if (material_faces[i] != "") {
			num_str = "00" + std::to_string(i);
			num_str = num_str.substr(num_str.size() - 3, num_str.size());
			num_str = "usemtl Material." + num_str + "\ns off\n";
			std::cout << num_str;
			myfile << num_str;
			std::cout << material_faces[i];
			myfile << material_faces[i];
		}
	}
	std::cout << "\n\n\n\n\n";
	std::cout << "----------------------" << std::endl;
	myfile.close();

	write_mtl_file(filename);
}