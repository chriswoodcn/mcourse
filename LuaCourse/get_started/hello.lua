print("Hello World")

function fact(n)
    if n == 0 then
        return 1
    else
        return n * fact(n - 1)
    end
end

-- print("enter a number:")
-- a = io.read("*number")
-- print(fact(a))

-- 保留字
-- and       break     do        else      elseif
-- end       false     for       function  if
-- in        local     nil       not       or
-- repeat    return    then      true      until
-- while

-- lua大小写敏感

-- 注释
--[[
    print(10)         -- no action (comment)
--]]
---[[
print(10) -- > 10
-- ]]