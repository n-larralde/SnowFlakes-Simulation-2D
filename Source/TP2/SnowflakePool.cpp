#include "SnowflakePool.h"

#include <iostream> // <----- REMOVE AFTER DEBUG

using namespace SF;

SnowflakePool::SnowflakePool() : _nbParticles{ 0 }
{
	// Initialiser le pool d'objets
	_pool = std::make_unique<T[]>(MAX_SNOWFLAKES);
}

SnowflakePool::SnowflakePool(uint val) : _nbParticles{ 0 }, MAX_SNOWFLAKES{val}
{
	// Initialiser le pool d'objets
	_pool = std::make_unique<T[]>(MAX_SNOWFLAKES);
}

void SnowflakePool::spawn(double x, double y) // À compléter
{
	// "Créer" un snowflake de plus en activant le prochain snowflake inactif
	if (_nbParticles < MAX_SNOWFLAKES) // Valider qu'on ne dépasse pas le MAX disponible
	{
		_pool[_nbParticles].initialize(x, y); // Réinitialiser le prochain snowflake inactif
		++_nbParticles; // Le nombre total augmente de +1
		return;
	}
}

void SnowflakePool::destroy(size_t deleteIdx)
{
	// "Supprimer" le snowflake demandé en déplaçant le dernier snowflake utilisé par-dessus l'objet à supprimer
	size_t dernierIdxDuTableau = _nbParticles - 1;
	_pool[deleteIdx] = _pool[dernierIdxDuTableau]; // On déplace les valeurs du dernier snowflake de la liste par-dessus l'index à supprimer
	--_nbParticles; // Le nombre total diminue de 1
}

void SnowflakePool::reset()
{
	for (uint i = {}; i < _nbParticles; ++i)
	{
		_pool[i].clear();
	}
	_nbParticles = 0;
}

Snowflake& SnowflakePool::get(size_t idx) const
{
	// Accès à un des snowflakes
	return _pool[idx];
}
