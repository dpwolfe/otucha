#include "ModelBase.hpp"

using namespace rffalcon;

ModelBase::ModelBase()
{

}

ModelBase::~ModelBase()
{

}

std::shared_ptr<PhongMaterial> ModelBase::getPhongMaterial()
{
	return _phongMaterial;
}