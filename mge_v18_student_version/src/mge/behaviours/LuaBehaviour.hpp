#ifndef  LUABEHAVIOUR_HPP
#define LUABEHAVIOUR_HPP

#include "mge/behaviours/AbstractBehaviour.hpp"
#include <iostream>
#include <lua.hpp>

class LuaBehaviour : public AbstractBehaviour
{
public:
	LuaBehaviour(lua_State* luaState);
	~LuaBehaviour();

	virtual void update(float pStep);

private:
	lua_State* main;
	float counter = 0;
};
#endif // ! LUABEHAVIOUR_HPP

