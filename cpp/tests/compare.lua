-- x = 10
-- y = 5
-- z = -20

-- -- Arithmetic expressions
-- a = 1 + 2 * 3
-- b = (4 + 5) / 2
-- c = x - y * z

-- -- Comparison operators
-- test1 = x > y
-- test2 = z < 0
-- test3 = a == b
-- test4 = 1 == 1

-- print(test1)
-- print(test2)
-- print(test3)
-- print(test4)

print("DONE! NOW ==, <=, >=, ~=")
-- Test all comparison operators
x = 10
y = 5
print("x = " .. x .. " y = " .. y)

-- Equal and Not Equal
print("Equal and Not Equal")
print(x == y)  -- false
print(x ~= y)  -- true
print(x == 10) -- true

-- Greater/Less Than or Equal
print("Greater/Less Than or Equal")
print(x >= y)  -- true
print(x <= y)  -- false
print(y <= 5)  -- true
print(y >= 5)  -- true

-- Combined comparisons
result = (x >= 10) and (y <= 5)
print(result)  -- true

-- Testing with expressions
a = 3
b = 2
print((a + b) <= (x - y))  -- true
print(a * b .. " " ..  x / y) -- false
print((a * b) >= (x / y)) 