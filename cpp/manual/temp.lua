-- Sample Lua Program without functions

-- Calculate the factorial of a number
n = 5
factorial = 1


for i = 2, n do
    factorial = factorial * i
end


print("Factorial of 5: " .. factorial)

-- Print the first n Fibonacci numbers
n = 10

a = 0
b = 1
print("First 10 Fibonacci numbers:")
for i = 1, n do
    print(a)
    a = b
    b = a+b
end
