Harness = require('harness')
Vis = require('Vis')
VisUtil = require('visutil')
Emit = require('emit')
string = require('string')
debug = require('debug')

function debugmsg(msg, ...)
    if ... and #... > 0 then
        msg = msg:format(...)
    end
    if os.getenv('VIS_DEBUG') then print(msg) end
end

function doassert(cond, msg)
    if not cond then print(package.loaded.debug.traceback()) end
    assert(cond, msg)
    debugmsg(msg .. ": PASS")
end

function assert_field_eq(e1, e2, field, s)
    s = s or "<no message>"
    estr = "%s: (e1.%s == %s) ~= (e2.%s == %s)"
    estr = estr:format(s, field, e1:get(field), field, e2:get(field))
    doassert(e1:get(field) == e2:get(field), estr)
end

function assert_field_ne(e1, e2, field, s)
    s = s or "<no message>"
    estr = "%s: (e1.%s == %s) == (e2.%s == %s)"
    estr = estr:format(s, field, e1:get(field), field, e2:get(field))
    doassert(e1:get(field) ~= e2:get(field), estr)
end

function assert_field_eq1(e1, field, value, s)
    s = s or "<no message>"
    estr = "%s: (e1.%s == %s) == %s"
    estr = estr:format(s, field, e1:get(field), value)
    doassert(e1:get(field) == value, estr)
end

function assert_field_ne1(e1, field, value, s)
    s = s or "<no message>"
    estr = "%s: (e1.%s == %s) ~= %s"
    estr = estr:format(s, field, e1:get(field), value)
    doassert(e1:get(field) ~= value, estr)
end

raw_et = VisUtil.make_emit_table()
e1 = Emit:new()

-- Test block 1: special functions

-- Test 1: ctor
local estr = "%s == %s: %s"
for k,v in pairs(raw_et) do
    assert_field_eq1(e1, k, v, 'test 1: ctor')
end

-- Test 2: copy
e1:count(500)
e2 = e1:clone()
assert_field_eq(e1, e2, 'count', 'test 2: copy')
e2:count(1000)
assert_field_ne(e1, e2, 'count', 'test 2: copy')

-- Test 3: set
e2:set('count', 1)
assert_field_eq1(e2, 'count', 1, 'test 3: set')

-- Test 4: center
e1:center(0, 0)
assert_field_eq1(e1, 'x', 0, 'test 4: center')
assert_field_eq1(e1, 'y', 0, 'test 4: center')

-- Test 5: color
e1:color(0.5, 0.5, 0.5)
assert_field_eq1(e1, 'r', 0.5)
assert_field_eq1(e1, 'g', 0.5)
assert_field_eq1(e1, 'b', 0.5)
assert_field_eq1(e1, 'ur', 0)
assert_field_eq1(e1, 'ug', 0)
assert_field_eq1(e1, 'ub', 0)
e1:color(0, 0, 0, 1, 1, 1)

e1:color() -- defaults: rgb=1, urgb=0
assert_field_eq1(e1, 'r', 1)
assert_field_eq1(e1, 'g', 1)
assert_field_eq1(e1, 'b', 1)
assert_field_eq1(e1, 'ur', 0)
assert_field_eq1(e1, 'ug', 0)
assert_field_eq1(e1, 'ub', 0)
e1:color(0, 0, 0, 1, 1, 1)

e1:color({0.5, 0.5, 0.5}) -- defaults: urgb=0
assert_field_eq1(e1, 'r', 0.5)
assert_field_eq1(e1, 'g', 0.5)
assert_field_eq1(e1, 'b', 0.5)
assert_field_eq1(e1, 'ur', 0)
assert_field_eq1(e1, 'ug', 0)
assert_field_eq1(e1, 'ub', 0)
e1:color(0, 0, 0, 1, 1, 1)

e1:color({0.5, 0.5, 0.5}, {0.5, 0.5, 0.5})
assert_field_eq1(e1, 'r', 0.5)
assert_field_eq1(e1, 'g', 0.5)
assert_field_eq1(e1, 'b', 0.5)
assert_field_eq1(e1, 'ur', 0.5)
assert_field_eq1(e1, 'ug', 0.5)
assert_field_eq1(e1, 'ub', 0.5)
e1:color(0, 0, 0, 1, 1, 1)

e1:color({0.5, 0.5, 0.5, 0.5, 0.5, 0.5})
assert_field_eq1(e1, 'r', 0.5)
assert_field_eq1(e1, 'g', 0.5)
assert_field_eq1(e1, 'b', 0.5)
assert_field_eq1(e1, 'ur', 0.5)
assert_field_eq1(e1, 'ug', 0.5)
assert_field_eq1(e1, 'ub', 0.5)
e1:color(0, 0, 0, 1, 1, 1)

e1:color(0.5, 0.5, 0.5, 0.5, 0.5, 0.5)
assert_field_eq1(e1, 'r', 0.5)
assert_field_eq1(e1, 'g', 0.5)
assert_field_eq1(e1, 'b', 0.5)
assert_field_eq1(e1, 'ur', 0.5)
assert_field_eq1(e1, 'ug', 0.5)
assert_field_eq1(e1, 'ub', 0.5)
e1:color(0, 0, 0, 1, 1, 1)

Vis.exit(Vis.flist, 0)
