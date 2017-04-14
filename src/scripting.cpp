#include "scripting.hpp"
#include <exception>
#include <map>

std::map<lua_State*, ScriptingContext*> lua2ctx;

#define LUAAPI_GETCTX() \
	ScriptingContext* ctx;			\
	std::cout << L << std::endl;	\
	try {							\
		ctx = lua2ctx.at(L);		\
	} catch(std::exception& e) {	\
		lua_pushnil(L);				\
		return 1;					\
	}

static int luaapi_getlight(lua_State* L);
static int luaapi_getsphere(lua_State* L);

ScriptingContext::ScriptingContext(const Scene& s)
{
	std::cout << "ScriptingContext" << std::endl;
	this->s = &s;
	this->L = luaL_newstate();
	std::cout << L << std::endl;
	if(!L)
	{
		std::cout << "Cannot create new state!!!" << std::endl;
	}
	luaL_openlibs(L);

	int status = luaL_loadfile(L, "test.lua");
	if(status)
	{
		std::cout << "Couldn't load file " << lua_tostring(L, -1) << std::endl;
		return;
	}

	lua_call(L, 0, 0);

	lua_getglobal(L, "__scriptname");
	if(lua_isstring(L, -1))
		std::cout << "Loading script `" << lua_tostring(L, -1) << std::endl;
	else
	{
		return;
	}
	lua_pop(L, 1);
	lua2ctx[L] = this;


	#define LUA_KVF(k, v) lua_pushstring(L, (k)); lua_pushcfunction(L, (v)); lua_settable(L, -3);
	lua_newtable(L);
	LUA_KVF("getlightbyindex", luaapi_getlight);
	LUA_KVF("getspherebyindex", luaapi_getsphere);
	lua_setglobal(L, "spn");

	std::cout << "Script output" << std::endl << "==============" << std::endl;
	lua_getglobal(L, "init");
	lua_call(L, 0, 0);
	std::cout << "==============" << std::endl;
}

ScriptingContext::~ScriptingContext()
{
	lua2ctx.erase(L);
	lua_close(L); 
	L = NULL;
}

void ScriptingContext::Update(double dt)
{
	if(!L)
		return;
	lua_getglobal(L, "tick");
	lua_pushnumber(L, dt);
	lua_call(L, 1, 0);
}

static int luaapi_light_setx(lua_State* L);
static int luaapi_light_sety(lua_State* L);
static int luaapi_light_setz(lua_State* L);
static int luaapi_light_setr(lua_State* L);
static int luaapi_light_setg(lua_State* L);
static int luaapi_light_setb(lua_State* L);
static int luaapi_light_setl(lua_State* L);

static int luaapi_getlight(lua_State* L)
{
	LUAAPI_GETCTX();

	unsigned i = (unsigned)lua_tonumber(L, 1);
	Scene* s;
	Light* l;
	Vector3 v;
	s = (Scene*)ctx->GetScene();
	l = s->GetLight(i);
	if(!l)
		return 0;

	v = l->GetPosition();

	#define LUA_KVD(k, v) lua_pushstring(L, (k)); lua_pushnumber(L, (v)); lua_settable(L, -3);
	#define LUA_KVF(k, v) lua_pushstring(L, (k)); lua_pushcfunction(L, (v)); lua_settable(L, -3);

	lua_newtable(L);
	LUA_KVD("id", i);

	LUA_KVD("x", v[0]);
	LUA_KVD("y", v[1]);
	LUA_KVD("z", v[2]);

	v = l->GetColor();
	LUA_KVD("r", v[0]);
	LUA_KVD("g", v[1]);
	LUA_KVD("b", v[2]);

	LUA_KVD("l", l->GetBrightness());

	LUA_KVF("setx", luaapi_light_setx);
	LUA_KVF("sety", luaapi_light_sety);
	LUA_KVF("setz", luaapi_light_setz);
	LUA_KVF("setr", luaapi_light_setr);
	LUA_KVF("setg", luaapi_light_setg);
	LUA_KVF("setb", luaapi_light_setb);
	LUA_KVF("setl", luaapi_light_setl);
	return 1;
}

static int luaapi_light_setx(lua_State* L)
{
	LUAAPI_GETCTX();

	#define LUA_KVDR(k) ([L]() -> double { lua_pushstring(L, (k)); lua_gettable(L, 1); return lua_tonumber(L, -1); })()

	Scene* s;
	Light* l;
	Vector3* v;
	s = (Scene*)ctx->GetScene();

	unsigned i = (unsigned)LUA_KVDR("id");

	l = s->GetLight(i);

	v = l->GetPositionUnsafe();
	double nx = lua_tonumber(L, 2);
	v->SetX(nx);

	return 0;
}

static int luaapi_light_sety(lua_State* L)
{
	LUAAPI_GETCTX();

	#define LUA_KVDR(k) ([L]() -> double { lua_pushstring(L, (k)); lua_gettable(L, 1); return lua_tonumber(L, -1); })()

	Scene* s;
	Light* l;
	Vector3* v;
	s = (Scene*)ctx->GetScene();

	unsigned i = (unsigned)LUA_KVDR("id");

	l = s->GetLight(i);

	v = l->GetPositionUnsafe();
	double ny = lua_tonumber(L, 2);
	v->SetY(ny);

	return 0;
}

static int luaapi_light_setz(lua_State* L)
{
	LUAAPI_GETCTX();

	#define LUA_KVDR(k) ([L]() -> double { lua_pushstring(L, (k)); lua_gettable(L, 1); return lua_tonumber(L, -1); })()

	Scene* s;
	Light* l;
	Vector3* v;
	s = (Scene*)ctx->GetScene();

	unsigned i = (unsigned)LUA_KVDR("id");

	l = s->GetLight(i);

	v = l->GetPositionUnsafe();
	double nz = lua_tonumber(L, 2);
	v->SetZ(nz);

	return 0;
}

static int luaapi_light_setr(lua_State* L)
{
	LUAAPI_GETCTX();

	#define LUA_KVDR(k) ([L]() -> double { lua_pushstring(L, (k)); lua_gettable(L, 1); return lua_tonumber(L, -1); })()

	Scene* s;
	Light* l;
	Vector3* v;
	s = (Scene*)ctx->GetScene();

	unsigned i = (unsigned)LUA_KVDR("id");

	l = s->GetLight(i);

	v = l->GetColorUnsafe();
	double nr = lua_tonumber(L, 2);
	v->SetX(nr);

	return 0;
}

static int luaapi_light_setg(lua_State* L)
{
	LUAAPI_GETCTX();

	#define LUA_KVDR(k) ([L]() -> double { lua_pushstring(L, (k)); lua_gettable(L, 1); return lua_tonumber(L, -1); })()

	Scene* s;
	Light* l;
	Vector3* v;
	s = (Scene*)ctx->GetScene();

	unsigned i = (unsigned)LUA_KVDR("id");

	l = s->GetLight(i);

	v = l->GetColorUnsafe();
	double ng = lua_tonumber(L, 2);
	v->SetY(ng);

	return 0;
}

static int luaapi_light_setb(lua_State* L)
{
	LUAAPI_GETCTX();

	#define LUA_KVDR(k) ([L]() -> double { lua_pushstring(L, (k)); lua_gettable(L, 1); return lua_tonumber(L, -1); })()

	Scene* s;
	Light* l;
	Vector3* v;
	s = (Scene*)ctx->GetScene();

	unsigned i = (unsigned)LUA_KVDR("id");

	l = s->GetLight(i);

	v = l->GetColorUnsafe();
	double nb = lua_tonumber(L, 2);
	v->SetZ(nb);

	return 0;
}

static int luaapi_light_setl(lua_State* L)
{
	LUAAPI_GETCTX();

	#define LUA_KVDR(k) ([L]() -> double { lua_pushstring(L, (k)); lua_gettable(L, 1); return lua_tonumber(L, -1); })()

	Scene* s;
	Light* l;
	s = (Scene*)ctx->GetScene();

	unsigned i = (unsigned)LUA_KVDR("id");

	l = s->GetLight(i);

	l->SetBrightness(lua_tonumber(L, 2));

	return 0;
}

static int luaapi_sphere_setx(lua_State* L);
static int luaapi_sphere_sety(lua_State* L);
static int luaapi_sphere_setz(lua_State* L);
static int luaapi_sphere_setr(lua_State* L);

static int luaapi_getsphere(lua_State* L)
{
	LUAAPI_GETCTX();

	unsigned i = (unsigned)lua_tonumber(L, 1);
	Scene* s;
	Sphere* g;
	Vector3 v;
	s = (Scene*)ctx->GetScene();
	g = s->GetSphere(i);
	if(!g)
		return 0;

	v = g->GetPosition();

	#define LUA_KVD(k, v) lua_pushstring(L, (k)); lua_pushnumber(L, (v)); lua_settable(L, -3);
	#define LUA_KVF(k, v) lua_pushstring(L, (k)); lua_pushcfunction(L, (v)); lua_settable(L, -3);

	lua_newtable(L);
	LUA_KVD("id", i);

	LUA_KVD("x", v[0]);
	LUA_KVD("y", v[1]);
	LUA_KVD("z", v[2]);

	LUA_KVD("l", g->GetRadius());

	LUA_KVF("setx", luaapi_sphere_setx);
	LUA_KVF("sety", luaapi_sphere_sety);
	LUA_KVF("setz", luaapi_sphere_setz);
	LUA_KVF("setr", luaapi_sphere_setr);
	return 1;
}

static int luaapi_sphere_setx(lua_State* L)
{
	LUAAPI_GETCTX();

	#define LUA_KVDR(k) ([L]() -> double { lua_pushstring(L, (k)); lua_gettable(L, 1); return lua_tonumber(L, -1); })()

	Scene* s;
	Sphere* g;
	Vector3* v;
	s = (Scene*)ctx->GetScene();

	unsigned i = (unsigned)LUA_KVDR("id");

	g = s->GetSphere(i);
	if(!g)
		return 0;

	v = g->GetPositionUnsafe();
	double nx = lua_tonumber(L, 2);
	v->SetX(nx);

	return 0;
}

static int luaapi_sphere_sety(lua_State* L)
{
	LUAAPI_GETCTX();

	#define LUA_KVDR(k) ([L]() -> double { lua_pushstring(L, (k)); lua_gettable(L, 1); return lua_tonumber(L, -1); })()

	Scene* s;
	Sphere* g;
	Vector3* v;
	s = (Scene*)ctx->GetScene();

	unsigned i = (unsigned)LUA_KVDR("id");

	g = s->GetSphere(i);
	if(!g)
		return 0;

	v = g->GetPositionUnsafe();
	double ny = lua_tonumber(L, 2);
	v->SetY(ny);

	return 0;
}

static int luaapi_sphere_setz(lua_State* L)
{
	LUAAPI_GETCTX();

	#define LUA_KVDR(k) ([L]() -> double { lua_pushstring(L, (k)); lua_gettable(L, 1); return lua_tonumber(L, -1); })()

	Scene* s;
	Sphere* g;
	Vector3* v;
	s = (Scene*)ctx->GetScene();

	unsigned i = (unsigned)LUA_KVDR("id");

	g = s->GetSphere(i);
	if(!g)
		return 0;

	v = g->GetPositionUnsafe();
	double nz = lua_tonumber(L, 2);
	v->SetZ(nz);

	return 0;
}

static int luaapi_sphere_setr(lua_State* L)
{
	LUAAPI_GETCTX();

	#define LUA_KVDR(k) ([L]() -> double { lua_pushstring(L, (k)); lua_gettable(L, 1); return lua_tonumber(L, -1); })()

	Scene* s;
	Sphere* g;
	s = (Scene*)ctx->GetScene();

	unsigned i = (unsigned)LUA_KVDR("id");

	g = s->GetSphere(i);
	if(!g)
		return 0;

	double nr = lua_tonumber(L, 2);
	g->SetRadius(nr);

	return 0;
}

