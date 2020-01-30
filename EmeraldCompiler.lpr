program EmeraldCompiler;

{$mode objfpc}{$H+}
{$codepage utf8}
{
 TODOS:
 expression parser
}
uses {$IFDEF UNIX} {$IFDEF UseCThreads}
  cthreads, {$ENDIF} {$ENDIF} {$IFDEF WINDOWS}
  Windows, {$ENDIF}
  Hierarchy,
  SysUtils,
  StrUtils,
  Regexpr,
  Utilities,
  Variants;

const
  multiCommentStartPattern = '\s*\/(\*|#).*';
  multiCommentEndPattern = '.*(\*|#)\/\s*';
  commentPattern = '\s*(#|(\/\/)).*';
  varEx = '[^-+*/:=,.;.()[\]={}\s''`"\\]+'; // Characters used for names of identifiers (functions, vars, module names...)
  expPattern = '.+'; // Pattern that matches expressions  TODO
  modulePattern = '\s*Module\s*"[^\s"]+"\s*';
  importPattern = '\s*Import\s*"[^\s"]+"\s*';
  // TODO: add keywords and number-only-names to exceptions
  variableDeclarationPattern = '\s*' + varEx + '\s*(=\s*' + expPattern + '\s*)?';
 {variableDeclarationPattern = '\s*_NAME_\s*=\s*_VALUE_\s*';}
  functionDeclarationPattern = '\s*fn\s+' + varEx + '\s*\(\s*(' + varEx + '|(' + varEx + '\s*,\s*' + varEx + ')*|\s*)\s*\)\s*:\s*';
  assignmentPattern = '\s*' + varEx + '\s*=\s*' + expPattern + '\s*?';
  // TODO: functional assignments -=, += ...
  functionCallPattern = '\s*(' + varEx + '|(' + varEx + '\s*\.\s*' + varEx + '+)+)\s*\(\s*(' + expPattern + '+|(' + expPattern + '+\s*,\s*' + expPattern + '+)*|\s*)\s*\)\s*';
  forLoopPattern = '\s*for\s+' + varEx + '\s+in\s+.+\s+do\s*:\s*';

var
  module: TModule;
  fileIn: TextFile;
  scope: array of TScope;
  currentLine: String;
  inComment: boolean = false;
  currLnNumber, scopeNest: Integer;
  currFuncHolder: TFunction;
  currLoopHolders: array of TLoop;

procedure nestScope(const nextScope: TScope);
begin
  if scopeNest >= length(scope) then
    SetLength(scope, length(scope) + 10);

  scope[scopeNest]:= nextScope;
  Inc(scopeNest);
end;

function isComment(const line: String): boolean;
  begin
    if stringMatches(line, multiCommentStartPattern) then
      begin
        inComment:= true;
        exit(true);
      end
    else if stringMatches(line, multiCommentEndPattern) then
      begin
        inComment:= false;
        exit(true);
      end
    else if stringMatches(line, commentPattern) then
      exit(true)
    else if inComment then
      exit(true)
    else
      exit(false);
end;

function removeComments(const lineIn: String): String;
begin
  // TODO: actually remove comments in line
  removeComments:= lineIn; //temporary
end;

procedure handleModule(const line: String);

begin
  if module.name.Length > 0 then
  begin                                // TODO: replace with log function
    WriteLn('Only one module identifier is allowed! line: ', currLnNumber);
    exit;
  end
  else if (High(module.imports) > 0) or (High(module.functions) > 0) or
          (High(module.globalVariables) > 0) or (High(module.mainBody) > 0) then
  begin
   WriteLn('Module declaration must preceed any other if present! line: ', currLnNumber);
   exit;
  end;

  module.name:= line.Substring(line.IndexOf('"') + 1, line.LastIndexOf('"') -
                line.IndexOf('"') - 1);
  writeln(module.name);
end;

procedure handleImport(const line: String);

var
  temp: String;

begin
  temp:= line.Substring(line.IndexOf('"') + 1, line.LastIndexOf('"') -
         line.IndexOf('"') - 1);
  addImport(module, temp);
end;

procedure handleVarDeclaration(const line: String; isGlobal: Boolean);
var
  varName, temp: String;
  value: TExpression;
  varType: EExpTypes;
  variable: TVariable;

begin
  varName:= line.Substring(0, line.IndexOf('='));
  varName:= trimWhiteChars(varName);
  temp:= line.Substring(line.IndexOf('=') + 1);
  temp:= trimWhiteChars(temp);
  value:= parseExpression(temp); // TODO: actally implement expression parser
  varType:= getExpType(value);
  variable.name:= varName;
  variable.value:= value;
  variable.varType:= varType;

  if isGlobal then
    addGlobalVar(module, variable)
  else
    addLocalVar(currFuncHolder, variable);
end;

procedure handleForLoop(const line: String; isGlobal: boolean);
var
  loopVarName, loopExpr, temp: String;
  loopExpression: TExpression;
  action: TAction;
  regex: TRegExpr;

begin
  nestScope(InLoop);
  temp:= trimWhiteChars(line.Substring(line.IndexOf('for') + 3));
  regex.Create;
  regex.Expression:= varEx + '\s+';

  if regex.Exec(temp) then
    begin
      loopVarName:= regex.match[0];
      temp:= temp.Substring(Length(loopVarName));
      temp:= temp.Substring(temp.IndexOf('in') + 2);
      temp:= temp.Substring(0, temp.LastIndexOf('do'));
      loopExpr:= trimWhiteChars(temp);
      loopExpression:= parseExpression(loopExpr);
      action.actionType:= Loop;
      //action.loop.;
    end;
end;

procedure handleStartFunction(const line: String);
var
  name, params: String;

begin
  nestScope(InFunction);
  currFuncHolder:= nullFunc();
  name:= trimWhiteChars(line.Substring(line.IndexOf('n') + 1, line.IndexOf('(') -
         line.IndexOf('n') - 1));
  params:= line.Substring(line.IndexOf('(') + 1, line.LastIndexOf(')') - line.IndexOf('(') - 1);

  if Length(params) > 0 then
    currFuncHolder.parameters:= buildFuncParams(params);

  currFuncHolder.name:= name;
end;

procedure handleAssignment(const line: String; isGlobal: boolean);
var
  newAssignment: TAssignment;
  newAction: TAction;
  varName, temp: String;
  value: TExpression;

begin
  varName:= line.Substring(0, line.IndexOf('='));
  varName:= trimWhiteChars(varName);
  temp:= line.Substring(line.IndexOf('=') + 1);
  temp:= trimWhiteChars(temp);
  value:= parseExpression(temp);
  newAssignment.variableName:= varName;
  newAssignment.value:= value;
  newAction.actionType:= Assignment;
  newAction.assignment:= newAssignment;

  if isGlobal then
    addGlobalAction(module, newAction)
  else
    addLocalAction(currFuncHolder, newAction);
end;

procedure handleFunctionCall(const line: String; isGlobal: boolean);
begin

end;

procedure processLine(var line: String);
begin
  line:= removeComments(line); //remove any "inside" comments

  if isComment(line) then
    exit;

  case scope[scopeNest] of
    Whole:
      begin
        if stringMatches(line, modulePattern) then
          handleModule(line)
        else if stringMatches(line, importPattern) then
          handleImport(line)
        else if stringMatches(line, variableDeclarationPattern) then
          handleVarDeclaration(line, true)
        else if stringMatches(line, functionDeclarationPattern) then
          handleStartFunction(line)
        else if stringMatches(line, assignmentPattern) then
          handleAssignment(line, true)
        {else if stringMatches(line, functionCallPattern) then
          handleFunctionCall(line, true)
        else if stringMatches(line, forLoopPattern) then
          handleForLoop(line, true)
        else if stringMatches(line, whileLoopPattern) then
          handleWhileLoop(line, true)
        else if stringMatches(line, doXLoopPattern) then
          handleDoXLoop(line, true)
        else if stringMatches(line, echoPattern) then
          handleEcho(line, true)
        else if stringMatches(line, ifPattern) then
          handleIfBlock(line)};
      end;
    {InFunction:
      begin
        if stringMatches(line, variableDeclarationPattern) then
          handleVarDeclaration(line, false)
        else if stringMatches(line, assignmentPattern) then
          handleAssignment(line, false)
        else if stringMatches(line, functionCallPattern) then
          handleFunctionCall(line, false)
        else if stringMatches(line, forLoopPattern) then
          handleForLoop(line, false)
        else if stringMatches(line, whileLoopPattern) then
          handleWhileLoop(line, false)
        else if stringMatches(line, doXLoopPattern) then
          handleDoXLoop(line, false)
        else if stringMatches(line, echoPattern) then
          handleEcho(line, false)
        else if stringMatches(line, ifPattern) then
          handleIfBlock(line, false)
        else if stringMatches(line, endPattern) then
          handleEnd(line);
      end;               }
  end;
end;

begin
  {INITIALIZER START}
  {$IFDEF WINDOWS}
  setConsoleOutputCP(CP_UTF8);
  setConsoleCP(CP_UTF8);
  {$ENDIF}
  assignFile(fileIn, 'test.txt');
  reset(fileIn);
  currLnNumber:= 0;
  setLength(scope, 10);
  scopeNest:= 0;
  scope[0]:= Whole;
  {INITIALIZER END}

  {PARSER START}
  while not EOF(fileIn) do
  begin
    Inc(currLnNumber);
    readLn(fileIn, currentLine);
    currentLine:= currentLine + LineEnding;
    processLine(currentLine);
  end;
  {PARSER END}

  Readln;
end.




