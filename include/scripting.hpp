#pragma once

#include <lua.hpp>
#include "scene.hpp"

class ScriptingContext {
public:
	ScriptingContext(const Scene& s);
	~ScriptingContext();

	void Update(double dt);
	const Scene* GetScene(void) {return s;};
private:
	const Scene* s;
	lua_State* L;
};
