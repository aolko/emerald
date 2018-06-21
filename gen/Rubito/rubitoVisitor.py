# Generated from C:/Users/lol11/Documents/~py-proj/rubito-emerald\rubito.g4 by ANTLR 4.7
from antlr4 import *
if __name__ is not None and "." in __name__:
    from .rubitoParser import rubitoParser
else:
    from rubitoParser import rubitoParser

# This class defines a complete generic visitor for a parse tree produced by rubitoParser.

class rubitoVisitor(ParseTreeVisitor):

    # Visit a parse tree produced by rubitoParser#prog.
    def visitProg(self, ctx:rubitoParser.ProgContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#expression_list.
    def visitExpression_list(self, ctx:rubitoParser.Expression_listContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#expression.
    def visitExpression(self, ctx:rubitoParser.ExpressionContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#global_get.
    def visitGlobal_get(self, ctx:rubitoParser.Global_getContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#global_set.
    def visitGlobal_set(self, ctx:rubitoParser.Global_setContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#global_result.
    def visitGlobal_result(self, ctx:rubitoParser.Global_resultContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#function_inline_call.
    def visitFunction_inline_call(self, ctx:rubitoParser.Function_inline_callContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#require_block.
    def visitRequire_block(self, ctx:rubitoParser.Require_blockContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#function_definition.
    def visitFunction_definition(self, ctx:rubitoParser.Function_definitionContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#function_definition_body.
    def visitFunction_definition_body(self, ctx:rubitoParser.Function_definition_bodyContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#function_definition_header.
    def visitFunction_definition_header(self, ctx:rubitoParser.Function_definition_headerContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#function_name.
    def visitFunction_name(self, ctx:rubitoParser.Function_nameContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#function_definition_params.
    def visitFunction_definition_params(self, ctx:rubitoParser.Function_definition_paramsContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#function_definition_params_list.
    def visitFunction_definition_params_list(self, ctx:rubitoParser.Function_definition_params_listContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#function_definition_param_id.
    def visitFunction_definition_param_id(self, ctx:rubitoParser.Function_definition_param_idContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#return_statement.
    def visitReturn_statement(self, ctx:rubitoParser.Return_statementContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#function_call.
    def visitFunction_call(self, ctx:rubitoParser.Function_callContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#function_call_param_list.
    def visitFunction_call_param_list(self, ctx:rubitoParser.Function_call_param_listContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#function_call_params.
    def visitFunction_call_params(self, ctx:rubitoParser.Function_call_paramsContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#function_param.
    def visitFunction_param(self, ctx:rubitoParser.Function_paramContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#function_unnamed_param.
    def visitFunction_unnamed_param(self, ctx:rubitoParser.Function_unnamed_paramContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#function_named_param.
    def visitFunction_named_param(self, ctx:rubitoParser.Function_named_paramContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#function_call_assignment.
    def visitFunction_call_assignment(self, ctx:rubitoParser.Function_call_assignmentContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#all_result.
    def visitAll_result(self, ctx:rubitoParser.All_resultContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#elsif_statement.
    def visitElsif_statement(self, ctx:rubitoParser.Elsif_statementContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#if_elsif_statement.
    def visitIf_elsif_statement(self, ctx:rubitoParser.If_elsif_statementContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#if_statement.
    def visitIf_statement(self, ctx:rubitoParser.If_statementContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#unless_statement.
    def visitUnless_statement(self, ctx:rubitoParser.Unless_statementContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#while_statement.
    def visitWhile_statement(self, ctx:rubitoParser.While_statementContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#for_statement.
    def visitFor_statement(self, ctx:rubitoParser.For_statementContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#init_expression.
    def visitInit_expression(self, ctx:rubitoParser.Init_expressionContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#all_assignment.
    def visitAll_assignment(self, ctx:rubitoParser.All_assignmentContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#for_init_list.
    def visitFor_init_list(self, ctx:rubitoParser.For_init_listContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#cond_expression.
    def visitCond_expression(self, ctx:rubitoParser.Cond_expressionContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#loop_expression.
    def visitLoop_expression(self, ctx:rubitoParser.Loop_expressionContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#for_loop_list.
    def visitFor_loop_list(self, ctx:rubitoParser.For_loop_listContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#statement_body.
    def visitStatement_body(self, ctx:rubitoParser.Statement_bodyContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#statement_expression_list.
    def visitStatement_expression_list(self, ctx:rubitoParser.Statement_expression_listContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#assignment.
    def visitAssignment(self, ctx:rubitoParser.AssignmentContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#dynamic_assignment.
    def visitDynamic_assignment(self, ctx:rubitoParser.Dynamic_assignmentContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#int_assignment.
    def visitInt_assignment(self, ctx:rubitoParser.Int_assignmentContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#float_assignment.
    def visitFloat_assignment(self, ctx:rubitoParser.Float_assignmentContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#string_assignment.
    def visitString_assignment(self, ctx:rubitoParser.String_assignmentContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#initial_array_assignment.
    def visitInitial_array_assignment(self, ctx:rubitoParser.Initial_array_assignmentContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#array_assignment.
    def visitArray_assignment(self, ctx:rubitoParser.Array_assignmentContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#array_definition.
    def visitArray_definition(self, ctx:rubitoParser.Array_definitionContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#array_definition_elements.
    def visitArray_definition_elements(self, ctx:rubitoParser.Array_definition_elementsContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#array_selector.
    def visitArray_selector(self, ctx:rubitoParser.Array_selectorContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#dynamic_result.
    def visitDynamic_result(self, ctx:rubitoParser.Dynamic_resultContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#dynamic.
    def visitDynamic(self, ctx:rubitoParser.DynamicContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#int_result.
    def visitInt_result(self, ctx:rubitoParser.Int_resultContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#float_result.
    def visitFloat_result(self, ctx:rubitoParser.Float_resultContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#string_result.
    def visitString_result(self, ctx:rubitoParser.String_resultContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#comparison_list.
    def visitComparison_list(self, ctx:rubitoParser.Comparison_listContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#comparison.
    def visitComparison(self, ctx:rubitoParser.ComparisonContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#comp_var.
    def visitComp_var(self, ctx:rubitoParser.Comp_varContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#lvalue.
    def visitLvalue(self, ctx:rubitoParser.LvalueContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#rvalue.
    def visitRvalue(self, ctx:rubitoParser.RvalueContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#break_expression.
    def visitBreak_expression(self, ctx:rubitoParser.Break_expressionContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#literal_t.
    def visitLiteral_t(self, ctx:rubitoParser.Literal_tContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#float_t.
    def visitFloat_t(self, ctx:rubitoParser.Float_tContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#int_t.
    def visitInt_t(self, ctx:rubitoParser.Int_tContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#bool_t.
    def visitBool_t(self, ctx:rubitoParser.Bool_tContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#nil_t.
    def visitNil_t(self, ctx:rubitoParser.Nil_tContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#id.
    def visitId(self, ctx:rubitoParser.IdContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#id_global.
    def visitId_global(self, ctx:rubitoParser.Id_globalContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#id_function.
    def visitId_function(self, ctx:rubitoParser.Id_functionContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#terminator.
    def visitTerminator(self, ctx:rubitoParser.TerminatorContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#else_token.
    def visitElse_token(self, ctx:rubitoParser.Else_tokenContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by rubitoParser#crlf.
    def visitCrlf(self, ctx:rubitoParser.CrlfContext):
        return self.visitChildren(ctx)



del rubitoParser