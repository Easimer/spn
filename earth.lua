-- Test Lua Script
__scriptname = "Test"

et = 0

earth = nil
moon = nil
m_x = 0
m_z = 50

function init()
	print("hello")
	earth = spn.getspherebyindex(0)
	moon = spn.getspherebyindex(1)
end

function tick(dt)
	et = et + dt
	moon:setx(0 + 25 * math.cos(et))
	moon:setz(50 + 25 * math.sin(et))
end
