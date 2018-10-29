function string.split(str, sep)
    sep = sep or "%s"
    local t = {}

    for token in string.gmatch(str, "([^"..sep.."]+)") do
        table.insert(t, token)
    end

    return t
end

function string.trim(s)
   local from = s:match"^%s*()"
   return from > s:len() and "" or s:match(".*%S", from)
end

local function defineType(baseName, className, fieldList)
    local fields
    do
        local tmp = string.split(fieldList, ",")

        fields = {}

        for i,v in next,tmp,nil do
            fields[i] = string.trim(v)
        end
    end


    io.write("static struct "..baseName.."::"..className.." : public "..baseName.." {\n")

    for i,field in next,fields,nil do
        io.write("\t" .. field .. ";\n")
    end

    io.write"\n"

    -- Constructor
    io.write("\t"..className .. "(" .. fieldList .. ") {\n")

    for i,field in next,fields,nil do
        local name = string.split(field, "%s")[2]

        io.write("\t\tthis." .. name .. " = " .. name .. ";\n")
    end

    io.write"\t}\n\n"

    io.write"\ttemplate <class R>\n"
    io.write"\tvirtual R accept(R& visitor) {\n"
    io.write("\t\treturn visitor.visit" .. className .. baseName .. "(*this);\n")
    io.write"\t}\n"



    io.write"};\n\n\n"
end

local function defineVisitor(baseName, types)
    io.write"template <class R>\n"
    io.write("struct " .. baseName .. "::Visitor {\n")

    for typeName, fields in next,types,nil do
        local tn = string.trim(typeName)
        io.write("\tvirtual R visit" .. tn .. baseName .. "(" .. baseName .. "::" ..
          tn .. " " .. string.lower(baseName) .. ") = 0;\n")
    end

    io.write"};\n\n"
end

local function defineAst(outputPath, baseName, types)
    local path = outputPath .. baseName .. ".h"
    local file = io.open(path, "w")
    io.output(file)

    io.write
[[
/*
 * File:   Expr.h
 * Author: thewaffledimension
 *
 * Generated on October 28, 2018, 5:08 PM
 */


]]

    io.write"#include <vector>;\n#include <any>\n#include \"Token.h\"\n\n"
    io.write("static struct " .. baseName .. " {\n")

    io.write"\tstruct Visitor;\n"

    for className, fields in next,types,nil do
      io.write("\tstruct "..className..";\n")
    end

    io.write"\n\ttemplate <class R>"
    io.write"\n\tvirtual R accept(Visitor<R> visitor) = 0;\n"

    io.write"};\n\n"

    defineVisitor(baseName, types)

    for className, fields in next,types,nil do
        defineType(baseName, className, fields)
    end
    io.close(file)
end

function main(argv)
    if #argv ~= 1 then
        print"Usage: generate_ast <output directory>"
    else
        local outputDir = argv[1]

        if outputDir:sub(-1) ~= "/" then outputDir = outputDir .. "/" end

        defineAst(
            outputDir,
            "Expr",
            {
                Assign = "Token name, Expr value",
                Binary = "Expr left, Token op, Expr right",
                Grouping = "Expr expression",
                Literal = "std::any value",
                Unary = "Token op, Expr right",
                Variable = "Token name"
            }
        )

        defineAst(
            outputDir,
            "Stmt",
            {
                Block = "List<Stmt> statements",
                Expression = "Expr expression",
            		If = "Expr condition, Stmt trueBody, Stmt falseBody",
            		Var = "Token identifier, Expr value, bool global"
            }
        )
    end
end

main(arg)
