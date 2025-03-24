n = 10           -- Calculate first 10 Fibonacci numbers
a = 0            -- First number
b = 1            -- Second number
i = 0    

for i = 1, n do
    c = a + b
    a = b
    b = c
    print(c)
end