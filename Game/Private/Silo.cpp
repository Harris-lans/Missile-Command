#include "Silo.h"
#include "COGTextRenderer.h"
#include "COGTransform.h"
#include "COGSilo.h"

const int MAXIMUM_MISSILES_PER_SILO = 10;

Silo::Silo(Hash hash)
	:GameObject(hash)
{
	//Nothing for now
}

Silo::~Silo()
{
	// Nothing for now
}

void Silo::Setup(exEngineInterface* pEngine, exVector2& position, float& size)
{
	// Putting in components required for the silo
	exColor siloColor;
	siloColor.SetColor(255, 0, 0, 255);

	this->AddComponent(new COGTransform(this, position));

	COGTextRenderer* textComponent = new COGTextRenderer(pEngine, this, size, siloColor);
	textComponent->Initialize();
	this->AddComponent(textComponent);

	COGSilo* silo = new COGSilo(pEngine, this, MAXIMUM_MISSILES_PER_SILO);
	silo->Initialize();
	this->AddComponent(silo);
}