local function getdirectory(p)
	for i = #p, 1, -1 do
		if p:sub(i,i) == "/" then
			return p:sub(1,i)
		end
	end

	return "./"
end
local sd = getdirectory(arg[0])

local args = {...}
local arch = "okami1041"

local nl = string.char(10) -- newline
function serialize_list (tabl, indent)
    indent = indent and (indent.."  ") or ""
    local str = ''
    str = str .. indent.."{"..nl
    for key, value in pairs (tabl) do
        local pr = (type(key)=="string") and ('["'..key..'"]=') or ""
        if type (value) == "table" then
            str = str..pr..serialize_list (value, indent)
        elseif type (value) == "string" then
            str = str..indent..pr..'"'..tostring(value)..'",'..nl
        else
            str = str..indent..pr..tostring(value)..','..nl
        end
    end
    str = str .. indent.."},"..nl
    return str
end

function table.slice(tbl, first, last, step)
    local sliced = {}
  
    for i = first or 1, last or #tbl, step or 1 do
      sliced[#sliced+1] = tbl[i]
    end
  
    return sliced
  end

while #args > 0 and string.sub(args[1],1,1) == "-" do
    if string.sub(args[1],2,6) == "arch=" then
        arch = string.sub(args[1],7)
    else
        print("Unknown option \""..args[1].."\"")
        return
    end
    table.remove(args,1)
end

if #args < 2 then
    print("Usage: vos [-arch=okami1041] [sourcefile] [assemblyfile]")
    return
end

local function getParentDir(path)
    if path:reverse():find("/") == nil then
        return "./"
    end
    return path:sub(1,#path-table.pack(path:reverse():find("/"))[1]+1)
end

local asmCode = ""

local function include(path,str) -- Basically the Preprocessor
    local lines = {}
    for i in str:gmatch("([^\n]*)\n") do
        if i:sub(1,10) == "(include \"" and i:sub(#i-1,#i) == "\")" then
            local incPath = path..load("return "..i:sub(10,#i-1),"=includeparse","t",{})()
            local file = io.open(incPath,"rb")
            local data = file:read("*a").."\n"
            file:close()
            local tab = include(getParentDir(incPath),data)
            for _,j in ipairs(tab) do
                table.insert(lines,j)
            end
        elseif i:sub(1,14) == "(include_asm \"" and i:sub(#i-1,#i) == "\")" then
            local incPath = path..load("return "..i:sub(14,#i-1),"=includeparse","t",{})()
            local file = io.open(incPath,"rb")
            local data = file:read("*a").."\n"
            file:close()
            asmCode = asmCode .. data
        else
            table.insert(lines,i)
        end
    end
    return lines
end

local codegen = dofile(sd.."codegen-"..arch..".lua")
local lexer = dofile(sd.."lexer.lua")
local parser = dofile(sd.."parser.lua")
local infile = io.open(args[1],"rb")
local code = table.concat(include(getParentDir(args[1]),infile:read("*a").."\n"),"\n")
infile:close()

local tokens = lexer(code)
local astNodes = parser(tokens)
local finalASM = codegen(asmCode,astNodes,sd)
local outfile = io.open(args[2],"w")
outfile:write(finalASM)
outfile:close()
