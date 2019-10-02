#include <iostream>
#include <string>
#include <vector>
#include "world_info.h"
#include "save_as_obj.h"

void smudge(int* src, int* dest, int size,
	int smudge_x1, int smudge_y1, int smudge_z1, 
	int smudge_x2, int smudge_y2, int smudge_z2) {
	int* dest_block_ptr;
	for (int x = 0 - smudge_x1; x < size - smudge_x2; ++x) {
		for (int y = 0 - smudge_y1; y < size - smudge_y2; ++y) {
			for (int z = 0 - smudge_z1; z < size - smudge_z2; ++z) {
				dest_block_ptr = get_block_ptr(dest, size, x, y, z);
				*dest_block_ptr = 0;
				for (int x2 = x + smudge_x1; x2 < x + smudge_x2; ++x2) {
					for (int y2 = y + smudge_y1; y2 < y + smudge_y2; ++y2) {
						for (int z2 = z + smudge_z1; z2 < z + smudge_z2; ++z2) {
							*dest_block_ptr += *get_block_ptr(src, size, x2, y2, z2);
						}
					}
				}
				*dest_block_ptr = *dest_block_ptr / (
					(smudge_x2 - smudge_x1) *
					(smudge_y2 - smudge_y1) *
					(smudge_z2 - smudge_z1));
			}
		}
	}
}

int main() {
	int buffer_size = 10;
	int world_size_wb = WORLDSIZE + buffer_size*2;
	int* block1 = new int[world_size_wb * world_size_wb * world_size_wb];
	/*for (int i = 0; i < world_size_wb * world_size_wb * world_size_wb; ++i) {
		block1[i] = rand() % 1000;
	}*/

	for (int x = 0; x < world_size_wb; ++x) {
		for (int y = 0; y < world_size_wb; ++y) {
			for (int z = 0; z < world_size_wb; ++z) {
				if (y < 80) {
					*get_block_ptr(block1, world_size_wb, x, y, z) = rand() % (1000);
				}
				else {
					*get_block_ptr(block1, world_size_wb, x, y, z) = 0;
				}
			}
		}
	}

	int* block2 = new int[world_size_wb * world_size_wb * world_size_wb];
	smudge(block1, block2, world_size_wb, -5, -1, -1, 6, 2, 2);
	smudge(block2, block1, world_size_wb, -1, -5, -1, 2, 6, 2);
	smudge(block1, block2, world_size_wb, -1, -1, -5, 2, 2, 6);
	smudge(block2, block1, WORLDSIZE, -1, -1, -1, 2, 2, 3);
	smudge(block1, block2, WORLDSIZE, -1, -1, -1, 2, 2, 2);


	//x, y, z
	std::cout << "generation complete!" << std::endl;
	int* block = new int[WORLDSIZE*WORLDSIZE*WORLDSIZE];
	/*for (int i = 0; i < WORLDSIZE * WORLDSIZE * WORLDSIZE; ++i) {
		block[i] = (rand()%20 == 0) * (rand() % block_type::id::count);
	}*/

	int* block_src_ptr;
	int* block_dest_ptr;



	for (int x = 0; x < WORLDSIZE; ++x) {
		for (int y = 0; y < WORLDSIZE; ++y) {
			for (int z = 0; z < WORLDSIZE; ++z) {
				block_src_ptr = get_block_ptr(block2, world_size_wb, x + buffer_size, y + buffer_size, z + buffer_size);
				block_dest_ptr = get_block_ptr(block, WORLDSIZE, x, y, z);
				if (*block_src_ptr > 490 && *block_src_ptr < 510) {
					*block_dest_ptr = 1;
				}
				else {
					*block_dest_ptr = 0;
				}

			}
		}
	}
	save_as_obj(block, "191002_2213_test");

	//for (int i = 0; i < WORLDSIZE * WORLDSIZE * WORLDSIZE; ++i) {
		/*if (block2[i] > 495 && block2[i] < 505) {
			block[i] = 1;
		}
		else {
			block[i] = 0;
		}*/

	//*get_block_ptr(block, 1, 2, 1) = block_type::id::blue;
	//*get_block_ptr(block, 1, 1, 1) = block_type::id::red;
	//*get_block_ptr(block, 1, 1, 5) = block_type::id::green;

	/*char block[x_size][y_size][z_size] = {};
	int corner_num[x_size + 1][y_size + 1][z_size + 1] = {};
	int face_num[x_size + 1][y_size + 1][z_size + 1][3] = {};

	int relevant_corner = 0;
	int relevant_face = 0;
	std::string corners = "";
	std::string faces = "";
	for (int x = 1; x < x_size-1; ++x) {
		for (int y = 1; y < y_size-1; ++y) {
			for (int z = 1; z < z_size-1; ++z) {
				if (visible_block(block, x, y, z)) {
					make_sure_all_corners_are_defined(corner_num, x, y, z, relevant_corner, corners);
					make_sure_all_sides_are_defined(corner_num, face_num, x, y, z, relevant_face, faces);
				}
			}
		}
	}*/
	//std::cout << text << std::endl;
	std::cin.get();
}

/*const std::string text =
"# Blender v2.79 (sub 0) OBJ File : '' \n"
"# www.blender.org\n"
"mtllib rotation_help.mtl\n"
"o Cube.001_Cube.001;\n";

const int x_size = 100;
const int y_size = 100;
const int z_size = 100;

inline bool visible_block(char (&block)[x_size][y_size][z_size], int& x, int& y, int& z) {
	if ((block[x][y][z] != 0) && (
		(block[x + 1][y][z] == 0) ||
		(block[x - 1][y][z] == 0) ||
		(block[x][y + 1][z] == 0) ||
		(block[x][y - 1][z] == 0) ||
		(block[x][y][z + 1] == 0) ||
		(block[x][y][z - 1] == 0))) {
		return true;
	}
	return false;
}

inline void make_sure_all_corners_are_defined(int (&corner_num)[x_size + 1][y_size + 1][z_size + 1],
	int& x,
	int& y,
	int& z,
	int& relevant_corner,
	std::string& corners) {

	for (int cx = x; cx < x + 2; ++cx) {
		for (int cy = y; cy < y + 2; ++cy) {
			for (int cz = z; cz < z + 2; ++cz) {
				if (corner_num[cx][cy][cz] == 0) {
					corner_num[cx][cy][cz] = relevant_corner;
					relevant_corner++;
					corners += std::to_string(cx) +
						" " + std::to_string(cy) +
						" " + std::to_string(cz) +
						"\n";
				}
			}
		}
	}
}

inline void make_sure_all_sides_are_defined(int(&corner_num)[x_size + 1][y_size + 1][z_size + 1],
	int(&face_num)[x_size + 1][y_size + 1][z_size + 1][3],
	int& x,
	int& y,
	int& z,
	int& relevant_face,
	std::string& faces) {

	int p[4];

	for (int a = 0; a < 3; ++a) {
		for (int b = 0; b < 2; ++b) {
			if (a == 0) {
				if (face_num[x+b][y][z][0] == 0) {
					face_num[x + b][y][z][0] = relevant_face;
					p[0] = corner_num[x+b][y][z];
					p[1] = corner_num[x+b][y+1][z];
					p[2] = corner_num[x+b][y][z+1];
					p[3] = corner_num[x+b][y+1][z+1];
				}
				else {
					continue;
				}
			}
			if (a == 1) {
				if (face_num[x][y + b][z][1] == 0) {
					face_num[x][y + b][z][1] = relevant_face;
					p[0] = corner_num[x][y + b][z];
					p[1] = corner_num[x + 1][y + b][z];
					p[2] = corner_num[x][y + b][z + 1];
					p[3] = corner_num[x + 1][y + b][z + 1];
				}
				else {
					continue;
				}
			}
			else {
				if (face_num[x][y][z + b][2] == 0) {
					face_num[x][y][z + b][2] = relevant_face;
					p[0] = corner_num[x][y][z + b];
					p[1] = corner_num[x + 1][y][z + b];
					p[2] = corner_num[x][y + 1][z + b];
					p[3] = corner_num[x + 1][y + 1][z + b];
				}
				else {
					continue;
				}
			}
			faces += std::to_string(p[0]) + "//" + std::to_string(a*2 + b) +
				" " + std::to_string(p[1]) + "//" + std::to_string(a * 2 + b) +
				" " + std::to_string(p[2]) + "//" + std::to_string(a * 2 + b) +
				" " + std::to_string(p[3]) + "//" + std::to_string(a * 2 + b) + "\n";
			relevant_face++;

		}
	}
}




*/