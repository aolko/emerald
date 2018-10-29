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


    io.write("struct "..baseName.."::"..className.." : public "..baseName.." {\n")

    for i,field in next,fields,nil do
        io.write("\t" .. field .. ";\n")
    end

    io.write"\n"

    -- Constructor
    io.write("\t"..className .. "(" .. fieldList .. ") {\n")

    for i,field in next,fields,nil do
        local type = string.trim(string.split(field, "%s")[1])
        local name = string.split(field, "%s")[2]

        if type == "std::unique_ptr<Expr>" or type == "std::unique_ptr<Stmt>" or type == "std::vector<std::unique_ptr<Stmt>>" or type == "std::vector<std::unique_ptr<Expr>>" then
          io.write("\t\tthis->" .. name .. " = std::move(" .. name .. ");\n")
        else
          io.write("\t\tthis->" .. name .. " = " .. name .. ";\n")
        end
    end

    io.write"\t}\n\n"

    io.write"\ttemplate <class R>\n"
    io.write"\tR accept(R& visitor) {\n"
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

    io.write("#ifndef " .. string.upper(baseName) .. "_H\n")
    io.write("#define " .. string.upper(baseName) .. "_H\n\n")

    io.write"#include <memory>\n#include <vector>\n#include <any>\n#include \"Token.h\"\n"

    if baseName == "Stmt" then
      io.write"#include \"Expr.h\"\n\n"
    else
      io.write"\n"
    end

    io.write("struct " .. baseName .. " {\n")

    io.write("\tvirtual ~" .. baseName .. "() = default;\n\n")

    io.write"\ttemplate <class R>\n"
    io.write"\tstruct Visitor;\n"

    for className, fields in next,types,nil do
      io.write("\tstruct "..className..";\n")
    end

    io.write"\n\ttemplate <class R>"
    io.write"\n\tR accept(Visitor<R> visitor) {};\n"

    io.write"};\n\n"

    defineVisitor(baseName, types)

    for className, fields in next,types,nil do
        defineType(baseName, className, fields)
    end

    io.write("\n#endif /* " .. string.upper(baseName) .. "_H */")

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
                Assign = "Token name, std::unique_ptr<Expr> value",
                Binary = "std::unique_ptr<Expr> left, Token op, std::unique_ptr<Expr> right",
                Grouping = "std::unique_ptr<Expr> expression",
                Literal = "std::any value",
                Unary = "Token op, std::unique_ptr<Expr> right",
                Variable = "Token name, bool global"
            }
        )

        defineAst(
            outputDir,
            "Stmt",
            {
                Block = "std::vector<std::unique_ptr<Stmt>> statements",
                Expression = "std::unique_ptr<Expr> expression",
            		If = "std::unique_ptr<Expr> condition, std::unique_ptr<Stmt> trueBody, std::unique_ptr<Stmt> falseBody"
            }
        )
    end
end

main(arg)
