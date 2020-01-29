unit Hierarchy;

{$mode objfpc}{$H+}

interface

type
  EExpTypes = (RealNumber, IntNumber, StringValue, Bool, Variable, Nested, FunctionCall);
  EActionType = (Assignment, FunctionStatement, Loop, IfBlock);
  TScope = (Whole, InFunction, InIfBlock, InLoop);

  TOperator = record
    TODO: String;
  end;

  TExpression = record
    expType: EExpTypes;
    realValue: Extended;
    intValue: Int64;
    boolValue: Boolean;
    stringValue: String;
    variableValue: String;
    operatorBefore, operatorAfter: TOperator;
    innerExpressions: array of TExpression;
    functionCall: record
      name: String;
      params: array of TExpression;
    end;
  end;

  TVariable = record
    name: String;
    value: TExpression;
    varType: EExpTypes;
  end;

  TAssignment = record
    variableName: String;
    value: TExpression;
  end;

  TAction = record
    assignment: TAssignment;
    functionCall: record
      name: String;
      params: array of TExpression;
      paramCount: Integer;
    end;
    loop: record
      stopCond: TExpression;
      innerActions: array of TAction;
      actionCount: Integer;
    end;
    actionType: EActionType;
    ifBlock: record
      condition: TExpression;
      trueBody: array of TAction;
      falseBody: array of TAction;
      counts: array[1..2] of Integer;
    end;
  end;

  TFunction = record
    name: String;
    parameters: array of String;
    localVars: array of TVariable;
    body: array of TAction;
    return: TExpression;
    retrunType: EExpTypes;
    counts: array[1..3] of Integer
  end;

  TModule = record
    name: String;
    imports: array of String;
    globalVariables: array of TVariable;
    functions: array of TFunction;
    mainBody: array of TAction;
    counts: array[1..4] of Integer // stores the counts for arrays above
  end;

implementation

end.

