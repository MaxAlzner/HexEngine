#include "../MainCore.h"

using namespace CORE;

CORE::Material::Material()
{
	this->overlay = COLOR();
	this->specColor = COLOR();
	this->specIntensity = 1.f;
	this->roughness = 0.2f;
	this->refIndex = 1.4f;
	this->animation = NULL;
	this->root = NULL;
}
CORE::Material::~Material()
{
}

void CORE::Material::initialize()
{
}
void CORE::Material::uninitialize()
{
	this->Resources.clear();
	this->Samplers.clear();
	this->remove();
}
void CORE::Material::update()
{
}
void CORE::Material::load()
{
	if (DataCore::CurrentInputLayout != NULL) 
		DataCore::Root->d3dContext->IASetInputLayout(DataCore::CurrentInputLayout);

	if (DataCore::CurrentVertexShader != NULL) 
		DataCore::Root->d3dContext->VSSetShader(DataCore::CurrentVertexShader, 0, 0);
	if (DataCore::CurrentFragmentShader != NULL) 
		DataCore::Root->d3dContext->PSSetShader(DataCore::CurrentFragmentShader, 0, 0);
	
	for (unsigned i = 0; i < this->Resources.size(); i++) 
		DataCore::Root->d3dContext->PSSetShaderResources(i, 1, &this->Resources[i]);
	for (unsigned i = 0; i < this->Samplers.size(); i++) 
		DataCore::Root->d3dContext->PSSetSamplers(i, 1, &this->Samplers[i]);
}
void CORE::Material::remove()
{
	if (this->root != NULL) 
		this->root->material = NULL;
	DataCore::RemoveMaterial(this);
}

void CORE::Material::addTexture(const char* filename)
{
	this->Resources.push_back(DataCore::RegisterResource(filename));
}
void CORE::Material::addTexture(ID3D11ShaderResourceView* resource)
{
	this->Resources.push_back(resource);
}
void CORE::Material::addSampler(ID3D11SamplerState* sampler)
{
	this->Samplers.push_back(sampler);
}