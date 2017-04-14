-- Test Lua Script
__scriptname = "Test"

et = 0
s = nil

function init()
	print("hello")
	s = spn.getspherebyindex(0)
end

function tick(dt)
	et = et + dt
	s:setr(5 + 10 * math.abs(math.sin(et)))
end
