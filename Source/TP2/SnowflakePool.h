#pragma once

#include <memory>
#include "Globals.h"

using namespace std;

namespace SF
{
	template <class T>
	class SnowflakePool
	{
	public:
		SnowflakePool();
		void spawn(double x, double y);
		size_t destroy();
		void destroy(size_t deleteIdx);
		void reset();
		void update();
		void collisions(Player& p);
		T& get(size_t idx) const;
		size_t getNbSnowflakes() const { return _nbParticles; }
	private:
		std::unique_ptr<T[]> _pool;
		size_t _nbParticles;
		const uint MAX_SNOWFLAKES = _presets[8];
	};

	template <class T>
	SnowflakePool<T>::SnowflakePool() : _nbParticles{ 0 }
	{
		// Initialiser le pool d'objets
		_pool = std::make_unique<T[]>(MAX_SNOWFLAKES);
	}

	template <class T>
	void SnowflakePool<T>::spawn(double x, double y) // À compléter
	{
		// "Créer" un snowflake de plus en activant le prochain snowflake inactif
		if (_nbParticles < MAX_SNOWFLAKES) // Valider qu'on ne dépasse pas le MAX disponible
		{
			_pool[_nbParticles].initialize(x, y); // Réinitialiser le prochain snowflake inactif
			++_nbParticles; // Le nombre total augmente de +1
			return;
		}
	}

	template <class T>
	size_t SnowflakePool<T>::destroy()
	{
		size_t size_before = getNbSnowflakes();

		for (uint i{}; i < size_before; ++i)
		{
			if (this->get(i).shouldDelete())
				destroy(i);
		}

		return (size_t)(size_before - getNbSnowflakes());
	}

	template <class T>
	void SnowflakePool<T>::destroy(size_t deleteIdx)
	{
		// "Supprimer" le snowflake demandé en déplaçant le dernier snowflake utilisé par-dessus l'objet à supprimer
		size_t dernierIdxDuTableau = _nbParticles - 1;
		_pool[deleteIdx] = _pool[dernierIdxDuTableau]; // On déplace les valeurs du dernier snowflake de la liste par-dessus l'index à supprimer
		--_nbParticles; // Le nombre total diminue de 1
	}

	template <class T>
	void SnowflakePool<T>::reset()
	{
		for (uint i{}; i < _nbParticles; ++i)
			_pool[i].clear();
		_nbParticles = 0;
	}

	template <class T>
	void SnowflakePool<T>::update()
	{
		for (uint i{}; i < getNbSnowflakes(); ++i)
		{
			if (this->get(i).isActive())
				this->get(i).update();
		}
	}

	template <class T>
	inline void SnowflakePool<T>::collisions(Player& p)
	{
		for (uint i{}; i < getNbSnowflakes(); ++i)
			this->get(i).testCollision(p);
	}

	template <class T>
	T& SnowflakePool<T>::get(size_t idx) const
	{
		return _pool[idx]; // Accès à un des snowflakes
	}
}
