-- Variable assignments
x = 10
y = 5
z = -20

-- Arithmetic expressions
a = 1 + 2 * 3
b = (4 + 5) / 2
c = x - y * z

-- Boolean expressions
flag1 = true
flag2 = false

-- Comparison operators
test1 = x > y
test2 = z < 0
test3 = a == b

-- Logical operators
result1 = flag1 and flag2
result2 = test1 or test2
result3 = not flag1

-- If statement
if x > 5 then
    y = y + 1
end

-- If-else statement
if x < 0 then
    x = - x
else
    x = x + 1
end

-- If-elseif-else statement
-- if x > 100 then
--     result = "large"
-- elseif x > 50 then
--     result = "medium"
-- elseif x > 10 then
--     result = "small"
-- else
--     result = "tiny"
-- end

-- While loop
i = 0
while i < 5 do
    i = i + 1
end

-- For loop with positive step
for i = 1, 10 do
    sum = sum + i
end

-- For loop with custom step
for i = 0, 10, 2 do
    even = even + i
end

-- For loop with negative step
for i = 100, 1, -1 do
    countdown = countdown - 1
end

-- Nested control structures
if x > 0 then
    while x > 0 do
        for i = 1, x do
            sum = sum + i
        end
        x = x - 1
    end
else
    x = 0
end

print(x)
print(y)
print(a *b)
print(z < 2)