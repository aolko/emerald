package emerald;

import java.io.StringWriter;
import java.util.List;

import emerald.Expr.Assign;
import emerald.Expr.Binary;
import emerald.Expr.Call;
import emerald.Expr.Fix;
import emerald.Expr.Grouping;
import emerald.Expr.Literal;
import emerald.Expr.Unary;
import emerald.Expr.Variable;
import emerald.Interpreter.ReturnThrow;
import emerald.Stmt.Block;
import emerald.Stmt.Expression;
import emerald.Stmt.Func;
import emerald.Stmt.If;
import emerald.Stmt.Return;
import emerald.Stmt.Var;

import emerald.compiler.*;

public class Compiler implements Expr.Visitor<Object>, Stmt.Visitor<Void> {
	public StringWriter output = new StringWriter();
	public MethodBuilder currentMethod = new MethodBuilder("int", "main");
	private Interpreter internal = new Interpreter();

	public void compile(List<Stmt> statements) {
		currentMethod = new MethodBuilder("int", "main");
		currentMethod.Begin();
		try {
			for (Stmt statement : statements) {
				try {
					compile(statement);
				}
				catch (ReturnThrow ret) {
					break;
				}
			}
		} catch (RuntimeError error) {
			Emerald.runtimeError(error);
		}
		
		currentMethod.End();
	}
	
	private void compile(Stmt stmt) throws ReturnThrow {
		stmt.accept(this);
	}

	@Override
	public Void visitExpressionStmt(Expression stmt) {
		stmt.expression.accept(this);
		return null;
	}

	@Override
	public Void visitBlockStmt(Block stmt) throws ReturnThrow {
		for (Stmt statement : stmt.statements) {
			compile(statement);
		}
		
		return null;
	}

	@Override
	public Void visitVarStmt(Var stmt) {
		currentMethod.DefineLocal("double", stmt.identifier.lexeme);
		currentMethod.SetLocal(stmt.identifier.lexeme, stmt.value.accept(this).toString());
		return null;
	}

	@Override
	public Void visitIfStmt(If stmt) throws ReturnThrow {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public void visitReturnStmt(Return stmt) throws ReturnThrow {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void visitPrintStmt(Expr value) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void visitFunctionStmt(Func func) {
		MethodBuilder builder = new MethodBuilder("void", func.name);
		
		builder.Begin();
		
		MethodBuilder mainBuilder = currentMethod;
		currentMethod = builder;
		
		try {
			func.body.accept(this);
		} catch (ReturnThrow e) {
			
		}
		
		builder.End();
		
		currentMethod = mainBuilder;
		currentMethod.output.write("\n" + builder.output.toString());
	}

	// Revisit later
	@Override
	public Object visitGroupingExpr(Grouping expr) {
		try {
			return internal.visitGroupingExpr(expr);
		}
		catch (RuntimeError err) { // Expression may not be able to be serialized at compile time
			return '(' + expr.expression.accept(this).toString() + ')';
		}
	}

	@Override
	public Object visitLiteralExpr(Literal expr) {
		// TODO Auto-generated method stub
		return expr.value;
	}

	@Override
	public Object visitVariableExpr(Variable expr) {
		// TODO Auto-generated method stub
		return expr.name.lexeme;
	}

	@Override
	public Object visitUnaryExpr(Unary expr) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public Object visitAssignExpr(Assign expr) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public Object visitBinaryExpr(Binary expr) {
		try {
			return internal.visitBinaryExpr(expr).toString();
		}
		catch (RuntimeError err) { // Can't be optimized at compile time, must be evaluated at runtime
			return expr.left.accept(this) + " " + expr.operator.lexeme + " " + expr.right.accept(this);
		}
	}

	@Override
	public Object visitFixExpr(Fix expr) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public Object visitCallExpr(Call call) {
		// TODO Auto-generated method stub
		return null;
	}

	
	
}
