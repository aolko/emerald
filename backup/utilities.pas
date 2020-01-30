unit Utilities;

{$mode objfpc}{$H+}

interface

uses
  Hierarchy,
  SysUtils;

procedure addImport(var module: TModule; value: String);

function nullFunc(): TFunction;

function buildFuncParams(const inParams: String): TStringArray;

procedure addGlobalVar(var module: TModule; value: TVariable);

procedure addLocalVar(var func: TFunction; value: TVariable);

procedure addGlobalAction(var module: TModule; action: TAction);

procedure addLocalAction(var func: TFunction; action: TAction);

function getExpType(const expIn: TExpression): EExpTypes;

function parseExpression(const input: String): TExpression;

function stringMatches(const inString, pattern: String): boolean;

function trimWhiteChars(const value: String): String;

implementation

uses
  RegExpr,
  SysUtils;

var
  regex: TRegExpr;

function nullFunc(): TFunction;

var
  ret: TFunction;

begin
  nullFunc:= ret;
end;

function buildFuncParams(const inParams: String): TStringArray;

var
  temp: TStringArray;
  i: Integer;
begin
  temp:= inParams.Split(',');

  for i:=0 to Length(temp) do
  begin
    temp[i]:= trimWhiteChars(temp[i]);
  end;

  buildFuncParams:= temp;
end;

procedure addImport(var module: TModule; value: String);
begin
  if module.counts[1] >= length(module.imports) then
    SetLength(module.imports, length(module.imports) + 10);

  module.imports[module.counts[1]]:= value;
  Inc(module.counts[1]);
end;

procedure addGlobalVar(var module: TModule; value: TVariable);
begin
  if module.counts[2] >= length(module.globalVariables) then
    SetLength(module.globalVariables, length(module.globalVariables) + 10);

  module.globalVariables[module.counts[2]]:= value;
  Inc(module.counts[2]);
end;

procedure addLocalVar(var func: TFunction; value: TVariable);
begin
  if func.counts[2] >= length(func.localVars) then
    SetLength(func.localVars, length(func.localVars) + 10);

  func.localVars[func.counts[2]]:= value;
  Inc(func.counts[2]);
end;

procedure addGlobalAction(var module: TModule; action: TAction);
begin
  if module.counts[4] >= length(module.mainBody) then
    SetLength(module.mainBody, length(module.mainBody) + 10);

  module.mainBody[module.counts[4]]:= action;
  Inc(module.counts[4]);
end;

procedure addLocalAction(var func: TFunction; action: TAction);
begin
  if func.counts[3] >= length(func.body) then
    SetLength(func.body, length(func.body) + 10);

  func.body[func.counts[3]]:= action;
  Inc(func.counts[3]);
end;

function getExpType(const expIn: TExpression): EExpTypes;
begin
  // TODO with expression parser
end;

function parseExpression(const input: String): TExpression;
begin
  // TODO expression parser
end;

function stringMatches(const inString, pattern: String) : boolean;
begin
  regex:= TRegExpr.Create;
  regex.Expression:= pattern;

  if regex.exec(inString) then
  begin
    if CompareText(regex.match[0], inString) = 0 then
      stringMatches:= true
    else
      stringMatches:= false;
  end
  else
    stringMatches:= false;

  regex.Free;
end;

function trimWhiteChars(const value: String): String;
begin
  regex:= TRegExpr.Create;
  regex.Expression:= '([^\s].*[^\s])';

  if regex.exec(value) then
    trimWhiteChars:= regex.match[0]
  else
    trimWhiteChars:= value;
end;

begin

end.
