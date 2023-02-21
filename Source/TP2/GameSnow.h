#pragma once

#include <vector>

#include "Globals.h"
#include "Player.h"
#include "Snowflake.h"
#include "SnowflakePool.h"
#include "SnowflakeRebound.h"
#include "SnowflakeNoContact.h"
#include "SnowflakeSine.h"
#include "Game.h"

using namespace std;
using namespace Core;

namespace SF
{
	class GameSnow final: public Game
	{
	public:
	    GameSnow();
		~GameSnow();

	    void handleInput() override;
        void update() override;
        void render() const override;

	    void init(uint);
	    void addSnowflake();
	    void addSnowflake(double, double);

	private:
        int getClickX();
        int getClickY();

	    bool _pause;
	    
	    Player _p;
		SnowflakePool<Snowflake> _sfPool;
		SnowflakePool<SnowflakeNoContact> _sfncPool;
		SnowflakePool<SnowflakeRebound> _sfrPool;
		SnowflakePool<SnowflakeSine> _sfsPool;
	};
}
