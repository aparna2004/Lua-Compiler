-- Basic string concatenation
str1 = "Hello, "
str2 = "World!"
result = str1 .. str2
print(result)

-- Concatenating with numbers
x = 42
message = "The answer is " .. x
print(message)

-- Multiple concatenations
a = "1"
b = "2"
c = "3"
abc = a .. b .. c
print(abc)

-- Mixed type concatenation
flag = true
num = 123
str = "Test: " .. flag .. " - " .. num
print(str)

-- Concatenation in expressions
result = ("Value: " .. x) .. " is the answer"
print(result)

print("Hello".."Hi")