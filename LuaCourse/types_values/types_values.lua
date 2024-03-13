-- 8种基本类型 nil, boolean, number, string, userdata, function, thread, and table. 
print(type("Hello world")) -- > string
print(type(10.4 * 3)) -- > number
print(type(print)) -- > function
print(type(type)) -- > function
print(type(true)) -- > boolean
print(type(nil)) -- > nil
print(type(type(X))) -- > string

-- 动态语言类型 函数一等公民
print(a)
a = "a"
print(a)
a = false
a = print
a = nil
-- 数字 只有一种双精度浮点类型
num = 4
num = 0.4
num = 4.57e-3
num = 0.3e12
num = 5e+20

a = "one string"
b = string.gsub(a, "one", "another") -- change string parts
print(a) -- > one string
print(b) -- > another string
a = "a line"
b = 'another line' -- 单引号也可以
-- Strings in Lua can contain the following C-like escape sequences
-- \a	bell
-- \b	back space
-- \f	form feed
-- \n	newline
-- \r	carriage return
-- \t	horizontal tab
-- \v	vertical tab
-- \\	backslash
-- \"	double quote
-- \'	single quote
-- \[	left square bracket
-- \]	right square bracket

-- [[]]之间的文本
page = [[
  <HTML>
  <HEAD>
  <TITLE>An HTML Page</TITLE>
  </HEAD>
  <BODY>
  <A HREF="http://www.lua.org">Lua</A>
  </BODY>
  </HTML>
  ]]
print(page)

print("10" + 1) -- > 11
print("10 + 1") -- > 10 + 1
print("-5.3e-10" * "2") -- > -1.06e-09
-- print("hello" + 1) -- ERROR (cannot convert "hello")
print(10 .. 20) -- > 1020

line = io.read() -- read a line
n = tonumber(line) -- try to convert it to a number
if n == nil then
    print(line .. " is not a valid number")
else
    print(n * 2)
end

print(tostring(10) == "10") -- > true
print(10 .. "" == "10") -- > true
