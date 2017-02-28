#include "VillagerController.h"

VillagerController::VillagerController()
{
}

VillagerController::~VillagerController()
{
}

void VillagerController::Start()
{
}

void VillagerController::Update()
{
	//float time = GameController::gameController->gameObject->GetComponent<GameController>()->GetGameTime();
	float hours = GameObject::FindFromTag("GameController")[0]->GetComponent<GameController>()->GetHours();
	//if(hours >= )
}

void VillagerController::OnDelete()
{
}
