#pragma once
namespace block_type {
	namespace id {
		enum {
			trash,
			red,
			green,
			blue,
			count
		};
	}
	const std::string material_info[id::count] = {
		"Ns 96.078431\n"
		"Ka 1.000000 1.000000 1.000000\n"
		"Kd 0.800000 0.800000 0.000000\n" //color
		"Ks 0.500000 0.500000 0.500000\n"
		"Ke 0.000000 0.000000 0.000000\n"
		"Ni 1.000000\n"
		"d 1.000000\n"
		"illum 2\n",

		"Ns 96.078431\n"
		"Ka 1.000000 1.000000 1.000000\n"
		"Kd 0.800000 0.000000 0.000000\n" //color
		"Ks 0.500000 0.500000 0.500000\n"
		"Ke 0.000000 0.000000 0.000000\n"
		"Ni 1.000000\n"
		"d 1.000000\n"
		"illum 2\n",

		"Ns 96.078431\n"
		"Ka 1.000000 1.000000 1.000000\n"
		"Kd 0.000000 0.800000 0.000000\n" //color
		"Ks 0.500000 0.500000 0.500000\n"
		"Ke 0.000000 0.000000 0.000000\n"
		"Ni 1.000000\n"
		"d 1.000000\n"
		"illum 2\n",

		"Ns 96.078431\n"
		"Ka 1.000000 1.000000 1.000000\n"
		"Kd 0.000000 0.000000 0.800000\n" //color
		"Ks 0.500000 0.500000 0.500000\n"
		"Ke 0.000000 0.000000 0.000000\n"
		"Ni 1.000000\n"
		"d 1.000000\n"
		"illum 2\n",
	};
}

const int WORLDSIZE = 100;
const int MATERIALCOUNT = block_type::id::count;