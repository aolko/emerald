# Generated from C:/Users/lol11/Documents/~py-proj/rubito-emerald\rubito.g4 by ANTLR 4.7
from antlr4 import *
if __name__ is not None and "." in __name__:
    from .rubitoParser import rubitoParser
else:
    from rubitoParser import rubitoParser

# This class defines a complete listener for a parse tree produced by rubitoParser.
class rubitoListener(ParseTreeListener):

    # Enter a parse tree produced by rubitoParser#prog.
    def enterProg(self, ctx:rubitoParser.ProgContext):
        pass

    # Exit a parse tree produced by rubitoParser#prog.
    def exitProg(self, ctx:rubitoParser.ProgContext):
        pass


    # Enter a parse tree produced by rubitoParser#expression_list.
    def enterExpression_list(self, ctx:rubitoParser.Expression_listContext):
        pass

    # Exit a parse tree produced by rubitoParser#expression_list.
    def exitExpression_list(self, ctx:rubitoParser.Expression_listContext):
        pass


    # Enter a parse tree produced by rubitoParser#expression.
    def enterExpression(self, ctx:rubitoParser.ExpressionContext):
        pass

    # Exit a parse tree produced by rubitoParser#expression.
    def exitExpression(self, ctx:rubitoParser.ExpressionContext):
        pass


    # Enter a parse tree produced by rubitoParser#global_get.
    def enterGlobal_get(self, ctx:rubitoParser.Global_getContext):
        pass

    # Exit a parse tree produced by rubitoParser#global_get.
    def exitGlobal_get(self, ctx:rubitoParser.Global_getContext):
        pass


    # Enter a parse tree produced by rubitoParser#global_set.
    def enterGlobal_set(self, ctx:rubitoParser.Global_setContext):
        pass

    # Exit a parse tree produced by rubitoParser#global_set.
    def exitGlobal_set(self, ctx:rubitoParser.Global_setContext):
        pass


    # Enter a parse tree produced by rubitoParser#global_result.
    def enterGlobal_result(self, ctx:rubitoParser.Global_resultContext):
        pass

    # Exit a parse tree produced by rubitoParser#global_result.
    def exitGlobal_result(self, ctx:rubitoParser.Global_resultContext):
        pass


    # Enter a parse tree produced by rubitoParser#function_inline_call.
    def enterFunction_inline_call(self, ctx:rubitoParser.Function_inline_callContext):
        pass

    # Exit a parse tree produced by rubitoParser#function_inline_call.
    def exitFunction_inline_call(self, ctx:rubitoParser.Function_inline_callContext):
        pass


    # Enter a parse tree produced by rubitoParser#require_block.
    def enterRequire_block(self, ctx:rubitoParser.Require_blockContext):
        pass

    # Exit a parse tree produced by rubitoParser#require_block.
    def exitRequire_block(self, ctx:rubitoParser.Require_blockContext):
        pass


    # Enter a parse tree produced by rubitoParser#function_definition.
    def enterFunction_definition(self, ctx:rubitoParser.Function_definitionContext):
        pass

    # Exit a parse tree produced by rubitoParser#function_definition.
    def exitFunction_definition(self, ctx:rubitoParser.Function_definitionContext):
        pass


    # Enter a parse tree produced by rubitoParser#function_definition_body.
    def enterFunction_definition_body(self, ctx:rubitoParser.Function_definition_bodyContext):
        pass

    # Exit a parse tree produced by rubitoParser#function_definition_body.
    def exitFunction_definition_body(self, ctx:rubitoParser.Function_definition_bodyContext):
        pass


    # Enter a parse tree produced by rubitoParser#function_definition_header.
    def enterFunction_definition_header(self, ctx:rubitoParser.Function_definition_headerContext):
        pass

    # Exit a parse tree produced by rubitoParser#function_definition_header.
    def exitFunction_definition_header(self, ctx:rubitoParser.Function_definition_headerContext):
        pass


    # Enter a parse tree produced by rubitoParser#function_name.
    def enterFunction_name(self, ctx:rubitoParser.Function_nameContext):
        pass

    # Exit a parse tree produced by rubitoParser#function_name.
    def exitFunction_name(self, ctx:rubitoParser.Function_nameContext):
        pass


    # Enter a parse tree produced by rubitoParser#function_definition_params.
    def enterFunction_definition_params(self, ctx:rubitoParser.Function_definition_paramsContext):
        pass

    # Exit a parse tree produced by rubitoParser#function_definition_params.
    def exitFunction_definition_params(self, ctx:rubitoParser.Function_definition_paramsContext):
        pass


    # Enter a parse tree produced by rubitoParser#function_definition_params_list.
    def enterFunction_definition_params_list(self, ctx:rubitoParser.Function_definition_params_listContext):
        pass

    # Exit a parse tree produced by rubitoParser#function_definition_params_list.
    def exitFunction_definition_params_list(self, ctx:rubitoParser.Function_definition_params_listContext):
        pass


    # Enter a parse tree produced by rubitoParser#function_definition_param_id.
    def enterFunction_definition_param_id(self, ctx:rubitoParser.Function_definition_param_idContext):
        pass

    # Exit a parse tree produced by rubitoParser#function_definition_param_id.
    def exitFunction_definition_param_id(self, ctx:rubitoParser.Function_definition_param_idContext):
        pass


    # Enter a parse tree produced by rubitoParser#return_statement.
    def enterReturn_statement(self, ctx:rubitoParser.Return_statementContext):
        pass

    # Exit a parse tree produced by rubitoParser#return_statement.
    def exitReturn_statement(self, ctx:rubitoParser.Return_statementContext):
        pass


    # Enter a parse tree produced by rubitoParser#function_call.
    def enterFunction_call(self, ctx:rubitoParser.Function_callContext):
        pass

    # Exit a parse tree produced by rubitoParser#function_call.
    def exitFunction_call(self, ctx:rubitoParser.Function_callContext):
        pass


    # Enter a parse tree produced by rubitoParser#function_call_param_list.
    def enterFunction_call_param_list(self, ctx:rubitoParser.Function_call_param_listContext):
        pass

    # Exit a parse tree produced by rubitoParser#function_call_param_list.
    def exitFunction_call_param_list(self, ctx:rubitoParser.Function_call_param_listContext):
        pass


    # Enter a parse tree produced by rubitoParser#function_call_params.
    def enterFunction_call_params(self, ctx:rubitoParser.Function_call_paramsContext):
        pass

    # Exit a parse tree produced by rubitoParser#function_call_params.
    def exitFunction_call_params(self, ctx:rubitoParser.Function_call_paramsContext):
        pass


    # Enter a parse tree produced by rubitoParser#function_param.
    def enterFunction_param(self, ctx:rubitoParser.Function_paramContext):
        pass

    # Exit a parse tree produced by rubitoParser#function_param.
    def exitFunction_param(self, ctx:rubitoParser.Function_paramContext):
        pass


    # Enter a parse tree produced by rubitoParser#function_unnamed_param.
    def enterFunction_unnamed_param(self, ctx:rubitoParser.Function_unnamed_paramContext):
        pass

    # Exit a parse tree produced by rubitoParser#function_unnamed_param.
    def exitFunction_unnamed_param(self, ctx:rubitoParser.Function_unnamed_paramContext):
        pass


    # Enter a parse tree produced by rubitoParser#function_named_param.
    def enterFunction_named_param(self, ctx:rubitoParser.Function_named_paramContext):
        pass

    # Exit a parse tree produced by rubitoParser#function_named_param.
    def exitFunction_named_param(self, ctx:rubitoParser.Function_named_paramContext):
        pass


    # Enter a parse tree produced by rubitoParser#function_call_assignment.
    def enterFunction_call_assignment(self, ctx:rubitoParser.Function_call_assignmentContext):
        pass

    # Exit a parse tree produced by rubitoParser#function_call_assignment.
    def exitFunction_call_assignment(self, ctx:rubitoParser.Function_call_assignmentContext):
        pass


    # Enter a parse tree produced by rubitoParser#all_result.
    def enterAll_result(self, ctx:rubitoParser.All_resultContext):
        pass

    # Exit a parse tree produced by rubitoParser#all_result.
    def exitAll_result(self, ctx:rubitoParser.All_resultContext):
        pass


    # Enter a parse tree produced by rubitoParser#elsif_statement.
    def enterElsif_statement(self, ctx:rubitoParser.Elsif_statementContext):
        pass

    # Exit a parse tree produced by rubitoParser#elsif_statement.
    def exitElsif_statement(self, ctx:rubitoParser.Elsif_statementContext):
        pass


    # Enter a parse tree produced by rubitoParser#if_elsif_statement.
    def enterIf_elsif_statement(self, ctx:rubitoParser.If_elsif_statementContext):
        pass

    # Exit a parse tree produced by rubitoParser#if_elsif_statement.
    def exitIf_elsif_statement(self, ctx:rubitoParser.If_elsif_statementContext):
        pass


    # Enter a parse tree produced by rubitoParser#if_statement.
    def enterIf_statement(self, ctx:rubitoParser.If_statementContext):
        pass

    # Exit a parse tree produced by rubitoParser#if_statement.
    def exitIf_statement(self, ctx:rubitoParser.If_statementContext):
        pass


    # Enter a parse tree produced by rubitoParser#unless_statement.
    def enterUnless_statement(self, ctx:rubitoParser.Unless_statementContext):
        pass

    # Exit a parse tree produced by rubitoParser#unless_statement.
    def exitUnless_statement(self, ctx:rubitoParser.Unless_statementContext):
        pass


    # Enter a parse tree produced by rubitoParser#while_statement.
    def enterWhile_statement(self, ctx:rubitoParser.While_statementContext):
        pass

    # Exit a parse tree produced by rubitoParser#while_statement.
    def exitWhile_statement(self, ctx:rubitoParser.While_statementContext):
        pass


    # Enter a parse tree produced by rubitoParser#for_statement.
    def enterFor_statement(self, ctx:rubitoParser.For_statementContext):
        pass

    # Exit a parse tree produced by rubitoParser#for_statement.
    def exitFor_statement(self, ctx:rubitoParser.For_statementContext):
        pass


    # Enter a parse tree produced by rubitoParser#init_expression.
    def enterInit_expression(self, ctx:rubitoParser.Init_expressionContext):
        pass

    # Exit a parse tree produced by rubitoParser#init_expression.
    def exitInit_expression(self, ctx:rubitoParser.Init_expressionContext):
        pass


    # Enter a parse tree produced by rubitoParser#all_assignment.
    def enterAll_assignment(self, ctx:rubitoParser.All_assignmentContext):
        pass

    # Exit a parse tree produced by rubitoParser#all_assignment.
    def exitAll_assignment(self, ctx:rubitoParser.All_assignmentContext):
        pass


    # Enter a parse tree produced by rubitoParser#for_init_list.
    def enterFor_init_list(self, ctx:rubitoParser.For_init_listContext):
        pass

    # Exit a parse tree produced by rubitoParser#for_init_list.
    def exitFor_init_list(self, ctx:rubitoParser.For_init_listContext):
        pass


    # Enter a parse tree produced by rubitoParser#cond_expression.
    def enterCond_expression(self, ctx:rubitoParser.Cond_expressionContext):
        pass

    # Exit a parse tree produced by rubitoParser#cond_expression.
    def exitCond_expression(self, ctx:rubitoParser.Cond_expressionContext):
        pass


    # Enter a parse tree produced by rubitoParser#loop_expression.
    def enterLoop_expression(self, ctx:rubitoParser.Loop_expressionContext):
        pass

    # Exit a parse tree produced by rubitoParser#loop_expression.
    def exitLoop_expression(self, ctx:rubitoParser.Loop_expressionContext):
        pass


    # Enter a parse tree produced by rubitoParser#for_loop_list.
    def enterFor_loop_list(self, ctx:rubitoParser.For_loop_listContext):
        pass

    # Exit a parse tree produced by rubitoParser#for_loop_list.
    def exitFor_loop_list(self, ctx:rubitoParser.For_loop_listContext):
        pass


    # Enter a parse tree produced by rubitoParser#statement_body.
    def enterStatement_body(self, ctx:rubitoParser.Statement_bodyContext):
        pass

    # Exit a parse tree produced by rubitoParser#statement_body.
    def exitStatement_body(self, ctx:rubitoParser.Statement_bodyContext):
        pass


    # Enter a parse tree produced by rubitoParser#statement_expression_list.
    def enterStatement_expression_list(self, ctx:rubitoParser.Statement_expression_listContext):
        pass

    # Exit a parse tree produced by rubitoParser#statement_expression_list.
    def exitStatement_expression_list(self, ctx:rubitoParser.Statement_expression_listContext):
        pass


    # Enter a parse tree produced by rubitoParser#assignment.
    def enterAssignment(self, ctx:rubitoParser.AssignmentContext):
        pass

    # Exit a parse tree produced by rubitoParser#assignment.
    def exitAssignment(self, ctx:rubitoParser.AssignmentContext):
        pass


    # Enter a parse tree produced by rubitoParser#dynamic_assignment.
    def enterDynamic_assignment(self, ctx:rubitoParser.Dynamic_assignmentContext):
        pass

    # Exit a parse tree produced by rubitoParser#dynamic_assignment.
    def exitDynamic_assignment(self, ctx:rubitoParser.Dynamic_assignmentContext):
        pass


    # Enter a parse tree produced by rubitoParser#int_assignment.
    def enterInt_assignment(self, ctx:rubitoParser.Int_assignmentContext):
        pass

    # Exit a parse tree produced by rubitoParser#int_assignment.
    def exitInt_assignment(self, ctx:rubitoParser.Int_assignmentContext):
        pass


    # Enter a parse tree produced by rubitoParser#float_assignment.
    def enterFloat_assignment(self, ctx:rubitoParser.Float_assignmentContext):
        pass

    # Exit a parse tree produced by rubitoParser#float_assignment.
    def exitFloat_assignment(self, ctx:rubitoParser.Float_assignmentContext):
        pass


    # Enter a parse tree produced by rubitoParser#string_assignment.
    def enterString_assignment(self, ctx:rubitoParser.String_assignmentContext):
        pass

    # Exit a parse tree produced by rubitoParser#string_assignment.
    def exitString_assignment(self, ctx:rubitoParser.String_assignmentContext):
        pass


    # Enter a parse tree produced by rubitoParser#initial_array_assignment.
    def enterInitial_array_assignment(self, ctx:rubitoParser.Initial_array_assignmentContext):
        pass

    # Exit a parse tree produced by rubitoParser#initial_array_assignment.
    def exitInitial_array_assignment(self, ctx:rubitoParser.Initial_array_assignmentContext):
        pass


    # Enter a parse tree produced by rubitoParser#array_assignment.
    def enterArray_assignment(self, ctx:rubitoParser.Array_assignmentContext):
        pass

    # Exit a parse tree produced by rubitoParser#array_assignment.
    def exitArray_assignment(self, ctx:rubitoParser.Array_assignmentContext):
        pass


    # Enter a parse tree produced by rubitoParser#array_definition.
    def enterArray_definition(self, ctx:rubitoParser.Array_definitionContext):
        pass

    # Exit a parse tree produced by rubitoParser#array_definition.
    def exitArray_definition(self, ctx:rubitoParser.Array_definitionContext):
        pass


    # Enter a parse tree produced by rubitoParser#array_definition_elements.
    def enterArray_definition_elements(self, ctx:rubitoParser.Array_definition_elementsContext):
        pass

    # Exit a parse tree produced by rubitoParser#array_definition_elements.
    def exitArray_definition_elements(self, ctx:rubitoParser.Array_definition_elementsContext):
        pass


    # Enter a parse tree produced by rubitoParser#array_selector.
    def enterArray_selector(self, ctx:rubitoParser.Array_selectorContext):
        pass

    # Exit a parse tree produced by rubitoParser#array_selector.
    def exitArray_selector(self, ctx:rubitoParser.Array_selectorContext):
        pass


    # Enter a parse tree produced by rubitoParser#dynamic_result.
    def enterDynamic_result(self, ctx:rubitoParser.Dynamic_resultContext):
        pass

    # Exit a parse tree produced by rubitoParser#dynamic_result.
    def exitDynamic_result(self, ctx:rubitoParser.Dynamic_resultContext):
        pass


    # Enter a parse tree produced by rubitoParser#dynamic.
    def enterDynamic(self, ctx:rubitoParser.DynamicContext):
        pass

    # Exit a parse tree produced by rubitoParser#dynamic.
    def exitDynamic(self, ctx:rubitoParser.DynamicContext):
        pass


    # Enter a parse tree produced by rubitoParser#int_result.
    def enterInt_result(self, ctx:rubitoParser.Int_resultContext):
        pass

    # Exit a parse tree produced by rubitoParser#int_result.
    def exitInt_result(self, ctx:rubitoParser.Int_resultContext):
        pass


    # Enter a parse tree produced by rubitoParser#float_result.
    def enterFloat_result(self, ctx:rubitoParser.Float_resultContext):
        pass

    # Exit a parse tree produced by rubitoParser#float_result.
    def exitFloat_result(self, ctx:rubitoParser.Float_resultContext):
        pass


    # Enter a parse tree produced by rubitoParser#string_result.
    def enterString_result(self, ctx:rubitoParser.String_resultContext):
        pass

    # Exit a parse tree produced by rubitoParser#string_result.
    def exitString_result(self, ctx:rubitoParser.String_resultContext):
        pass


    # Enter a parse tree produced by rubitoParser#comparison_list.
    def enterComparison_list(self, ctx:rubitoParser.Comparison_listContext):
        pass

    # Exit a parse tree produced by rubitoParser#comparison_list.
    def exitComparison_list(self, ctx:rubitoParser.Comparison_listContext):
        pass


    # Enter a parse tree produced by rubitoParser#comparison.
    def enterComparison(self, ctx:rubitoParser.ComparisonContext):
        pass

    # Exit a parse tree produced by rubitoParser#comparison.
    def exitComparison(self, ctx:rubitoParser.ComparisonContext):
        pass


    # Enter a parse tree produced by rubitoParser#comp_var.
    def enterComp_var(self, ctx:rubitoParser.Comp_varContext):
        pass

    # Exit a parse tree produced by rubitoParser#comp_var.
    def exitComp_var(self, ctx:rubitoParser.Comp_varContext):
        pass


    # Enter a parse tree produced by rubitoParser#lvalue.
    def enterLvalue(self, ctx:rubitoParser.LvalueContext):
        pass

    # Exit a parse tree produced by rubitoParser#lvalue.
    def exitLvalue(self, ctx:rubitoParser.LvalueContext):
        pass


    # Enter a parse tree produced by rubitoParser#rvalue.
    def enterRvalue(self, ctx:rubitoParser.RvalueContext):
        pass

    # Exit a parse tree produced by rubitoParser#rvalue.
    def exitRvalue(self, ctx:rubitoParser.RvalueContext):
        pass


    # Enter a parse tree produced by rubitoParser#break_expression.
    def enterBreak_expression(self, ctx:rubitoParser.Break_expressionContext):
        pass

    # Exit a parse tree produced by rubitoParser#break_expression.
    def exitBreak_expression(self, ctx:rubitoParser.Break_expressionContext):
        pass


    # Enter a parse tree produced by rubitoParser#literal_t.
    def enterLiteral_t(self, ctx:rubitoParser.Literal_tContext):
        pass

    # Exit a parse tree produced by rubitoParser#literal_t.
    def exitLiteral_t(self, ctx:rubitoParser.Literal_tContext):
        pass


    # Enter a parse tree produced by rubitoParser#float_t.
    def enterFloat_t(self, ctx:rubitoParser.Float_tContext):
        pass

    # Exit a parse tree produced by rubitoParser#float_t.
    def exitFloat_t(self, ctx:rubitoParser.Float_tContext):
        pass


    # Enter a parse tree produced by rubitoParser#int_t.
    def enterInt_t(self, ctx:rubitoParser.Int_tContext):
        pass

    # Exit a parse tree produced by rubitoParser#int_t.
    def exitInt_t(self, ctx:rubitoParser.Int_tContext):
        pass


    # Enter a parse tree produced by rubitoParser#bool_t.
    def enterBool_t(self, ctx:rubitoParser.Bool_tContext):
        pass

    # Exit a parse tree produced by rubitoParser#bool_t.
    def exitBool_t(self, ctx:rubitoParser.Bool_tContext):
        pass


    # Enter a parse tree produced by rubitoParser#nil_t.
    def enterNil_t(self, ctx:rubitoParser.Nil_tContext):
        pass

    # Exit a parse tree produced by rubitoParser#nil_t.
    def exitNil_t(self, ctx:rubitoParser.Nil_tContext):
        pass


    # Enter a parse tree produced by rubitoParser#id_decl.
    def enterId_decl(self, ctx:rubitoParser.Id_declContext):
        pass

    # Exit a parse tree produced by rubitoParser#id_decl.
    def exitId_decl(self, ctx:rubitoParser.Id_declContext):
        pass


    # Enter a parse tree produced by rubitoParser#id_global.
    def enterId_global(self, ctx:rubitoParser.Id_globalContext):
        pass

    # Exit a parse tree produced by rubitoParser#id_global.
    def exitId_global(self, ctx:rubitoParser.Id_globalContext):
        pass


    # Enter a parse tree produced by rubitoParser#id_function.
    def enterId_function(self, ctx:rubitoParser.Id_functionContext):
        pass

    # Exit a parse tree produced by rubitoParser#id_function.
    def exitId_function(self, ctx:rubitoParser.Id_functionContext):
        pass


    # Enter a parse tree produced by rubitoParser#terminator.
    def enterTerminator(self, ctx:rubitoParser.TerminatorContext):
        pass

    # Exit a parse tree produced by rubitoParser#terminator.
    def exitTerminator(self, ctx:rubitoParser.TerminatorContext):
        pass


    # Enter a parse tree produced by rubitoParser#else_token.
    def enterElse_token(self, ctx:rubitoParser.Else_tokenContext):
        pass

    # Exit a parse tree produced by rubitoParser#else_token.
    def exitElse_token(self, ctx:rubitoParser.Else_tokenContext):
        pass


    # Enter a parse tree produced by rubitoParser#crlf.
    def enterCrlf(self, ctx:rubitoParser.CrlfContext):
        pass

    # Exit a parse tree produced by rubitoParser#crlf.
    def exitCrlf(self, ctx:rubitoParser.CrlfContext):
        pass


