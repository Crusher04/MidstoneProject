#include "Spawner.h"
#include "Scene.h"

using namespace std;

Spawner::Spawner()
{
	pos = Vec3();
}

Spawner::Spawner(Vec3 pos_)
{
	pos = pos_;
}

void Spawner::EnemySpawn(float enemyType)
{
	
	
	if (enemyType == 1)
	{

		int maxRange = 1;
		int minRange = 10;
		srand((time(NULL)));
		randomize = rand() % (maxRange - minRange + 1);

		enemy = true;



	}
	
	

}
