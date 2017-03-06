#include "Farm.h"
#include "Transform.h"
#include "MeshRenderer.h"

void Farm::Start()
{
	corn.SetTag("Corn");
	corn.Start();
	corn.AddComponent<Transform>()->SetParent(gameObject->GetComponent<Transform>());
	corn.GetComponent<Transform>()->ScalePre(0.5);
	corn.AddComponent<MeshRenderer>()->LoadFromObj("../Assets/Crops/Corn.obj");
	corn.GetComponent<MeshRenderer>()->LoadDiffuseMap(L"../Assets/Crops/corn_d.dds");
	corn.GetComponent<MeshRenderer>()->LoadSpecularMap(L"../Assets/Crops/corn_s.dds");

	for (int x = 1; x <= 11; x += 2)
	{
		for (int z = 1; z <= 11; z += 2)
		{
			Crop temp;
			temp.position[0] = (x * 0.5f) - 2.5f;
			temp.position[1] = (z * 0.5f) - 3.5f;
			crops.push_back(temp);
		}
	}

	for (int i = 0; i < (int)crops.size(); ++i)
	{
		XMMATRIX tempMat = corn.GetComponent<Transform>()->GetWorldMatrix();
		tempMat = XMMatrixTranslation(crops[i].position[0], 0, crops[i].position[1]);
		corn.GetComponent<MeshRenderer>()->AddInstance(tempMat, i);
	}
}

void Farm::Update()
{
	if (!updateFlag)
	{
		bool succ = corn.GetComponent<MeshRenderer>()->RemoveInstance(-1);
		if (succ)
			updateFlag = true;
	}
	corn.Update();
}

void Farm::OnDelete()
{
	CleanUp();
	corn.OnDelete();
}

bool Farm::AddWorker(GameObject * _worker)
{
	if ((unsigned int)currWorkers.size() < maxWorkers)
	{
		currWorkers.push_back(_worker);
		return true;
	}

	return false;
}