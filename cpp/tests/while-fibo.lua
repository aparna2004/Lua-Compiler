n = 10           -- Calculate first 10 Fibonacci numbers
a = 0            -- First number
b = 1            -- Second number
i = 0            -- Counter

-- Using while loop
print(a)         -- Print first number
print(b)         -- Print second number
while i < n do
    c = a + b    -- Calculate next number
    a = b        -- Shift numbers
    b = c
    print(c)     -- Print current number
    i = i + 1
end