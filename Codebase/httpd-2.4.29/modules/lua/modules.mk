mod_lua.la: lua_apr.slo lua_config.slo mod_lua.slo lua_request.slo lua_vmprep.slo lua_dbd.slo lua_passwd.slo
	$(SH_LINK) -rpath $(libexecdir) -module -avoid-version  lua_apr.lo lua_config.lo mod_lua.lo lua_request.lo lua_vmprep.lo lua_dbd.lo lua_passwd.lo $(MOD_LUA_LDADD)
DISTCLEAN_TARGETS = modules.mk
static = 
shared =  mod_lua.la
MOD_INCLUDES = -I/usr/include/lua5.1
