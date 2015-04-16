#include "PhongMaterial.hpp"

using namespace rffalcon;

const PhongMaterial PhongMaterial::Gold = { { 0.24725f, 0.1995f, 0.0745f },
											{ 0.75164f, 0.60648f, 0.22648f },
											{ 0.628281f, 0.555802f, 0.366065f },
											51.2f,
											1.0f };


const PhongMaterial PhongMaterial::Copper = { { 0.1912f, 0.0735f, 0.0225f },
											  { 0.7038f, 0.27048f, 0.0825f },
											  { 0.256777f, 0.137622f, 0.086014f },
											  12.8f,
											  1.0f };

const PhongMaterial PhongMaterial::PolishedCopper = { { 0.2295f, 0.08825f, 0.0275f },
													  { 0.5508f, 0.2118f, 0.066f },
													  { 0.580594f, 0.223257f, 0.0695701f },
													  51.2f,
													  1.0f };