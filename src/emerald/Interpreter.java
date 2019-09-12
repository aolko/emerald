package emerald;

import java.util.List;
import java.util.Stack;

import emerald.Expr;

public class Interpreter implements Expr.Visitor<Object>, Stmt.Visitor<Void> {
	@SuppressWarnings("serial")
	public class ReturnThrow extends Throwable {}
	
	private Environment global = new Environment();
	
	public Environment environment = global;
	private Stack<Environment> callStack = new Stack<>();
	
	public void interpret(List<Stmt> statements) {
		try {
			for (Stmt statement : statements) {
				try {
					execute(statement);
				}
				catch (ReturnThrow ret) {
					break;
				}
			}
		} catch (RuntimeError error) {
			Emerald.runtimeError(error);
		}
	}
	
	public void pushEnv(Environment environment) {
		callStack.push(environment);
		this.environment = environment;
	}
	
	public void popEnv() {
		if (callStack.size() == 0) {
			return; // Do something if we return from the global scope here
		}
		
		Expr result = environment.lastReturn;
		
		callStack.pop();
		
		if (callStack.size() == 0) {
			environment = global;
		}
		else {
			environment = callStack.lastElement();
		}
		
		environment.lastReturn = result;
	}
	
	@Override
	public Void visitVarStmt(Stmt.Var stmt) {
		environment.set(stmt.identifier, evaluate(stmt.value));

		return null;
	}
	
	@Override
	public Void visitExpressionStmt(Stmt.Expression stmt) {
		evaluate(stmt.expression);
		return null;
	}
	
	@Override
	public Void visitIfStmt(Stmt.If stmt) throws ReturnThrow {
		Object cond = evaluate(stmt.condition);
		
		if (isTruthy(cond)) {
			// Preserve current scope
			try {
				stmt.trueBody.accept(this);
			} catch (ReturnThrow e) {
				popEnv();
				throw e;
			}
		}
		else {
			try {
				if (stmt.falseBody == null)
					return null;
				
				stmt.falseBody.accept(this);
			} catch (ReturnThrow e) {}
		}
		
		return null;
	}
	
	@Override
	public Void visitBlockStmt(Stmt.Block stmt) throws ReturnThrow {
		executeBlock(stmt.statements, new Environment(environment));
		return null;
	}
	
	@Override
	public void visitReturnStmt(Stmt.Return ret) throws ReturnThrow {
		environment.lastReturn = ret.value;
		throw new ReturnThrow();
	}
	
	@Override
	public void visitFunctionStmt(Stmt.Func func) {
		Function function = new Function(this, func.name, func.arguments, func.body);
		
		environment.defineFunc(function);
	}
	
	@Override
	public Object visitCallExpr(Expr.Call call) {
		Function function = environment.getFunc(call.name);
		
		return function.Call(call.arguments);
	}
	
	@Override
	public Object visitAssignExpr(Expr.Assign expr) {
		Object value = evaluate(expr.value);

		environment.assign(expr.name, value);
		return value;
	}
	
	@Override
	public Object visitVariableExpr(Expr.Variable expr) {
		return environment.get(expr.name);
	}
	
	@Override
	public Object visitLiteralExpr(Expr.Literal expr) {
		return expr.value;
	}
	
	@Override
	public Object visitGroupingExpr(Expr.Grouping expr) {
		return evaluate(expr.expression);
	}
	
	@Override
	public Object visitFixExpr(Expr.Fix expr) {
		if (expr.target.type == TokenType.IDENTIFIER) {
			Object val = environment.get(expr.target);
			
			if (val instanceof Double && expr.operator.type == TokenType.PLUS_PLUS) {
				environment.assign(expr.target, ((double) val + 1));
			}
			else if (val instanceof Double && expr.operator.type == TokenType.MINUS_MINUS) {
				environment.assign(expr.target, ((double) val - 1));
			}
			
			return expr.prefix ? environment.get(expr.target) : val;
		}
		
		// Error here?
		return null;
	}
	
	@SuppressWarnings("incomplete-switch")
	@Override
	public Object visitUnaryExpr(Expr.Unary expr) {
		Object right = evaluate(expr.right);

		switch (expr.operator.type) {
			case MINUS:
				checkNumberOperand(expr.operator, right);
				return -(double)right;
			case BANG:
				return !isTruthy(right);
		}
		
		// Unreachable
		return null;
	}
	
	@Override
	public void visitPrintStmt(Expr value) {
		Object val = evaluate(value);
		
		if (val instanceof Expr) {
			System.out.println(evaluate((Expr) val));
			return;
		}
		
		System.out.println(val);
		return;
	}
	
	@SuppressWarnings("incomplete-switch")
	@Override
	public Object visitBinaryExpr(Expr.Binary expr) {
		Object left = evaluate(expr.left);
		Object right = evaluate(expr.right);

		switch(expr.operator.type) {
			case GREATER:
				checkNumberOperands(expr.operator, left, right);
				return (double)left > (double)right;
			case GREATER_EQUAL:
				checkNumberOperands(expr.operator, left, right);
				return (double)left >= (double)right;
			case LESS:
				checkNumberOperands(expr.operator, left, right);
				return (double)left < (double)right;
			case LESS_EQUAL:
				checkNumberOperands(expr.operator, left, right);
				return (double)left <= (double)right;
			case BANG_EQUAL:
				return !isEqual(left, right);
			case EQUAL_EQUAL:
				return isEqual(left, right);
			case PLUS:
				if (left instanceof Boolean && !(right instanceof Boolean)) left = isTruthy(left) ? 1.0d : 0.0d;
				else if (right instanceof Boolean && !(left instanceof Boolean)) right = isTruthy(right) ? 1.0d : 0.0d;
				else if (left instanceof Boolean && right instanceof Boolean) {
					double left1 = isTruthy(left) ? 1.0d : 0.0d;
					double right1 = isTruthy(right) ? 1.0d : 0.0d;
					return (left1 - right1) >= 1.0d;
				}
				
				if (left instanceof Double && right instanceof Double) {
					return (double)left + (double)right;
				}
				
				if (left instanceof String && right instanceof String) {
					return (String)left + (String)right;
				} else if (left instanceof String && right instanceof Double) {
					return (String)left + (String)right;
				} else if (left instanceof Double && right instanceof String) {
					return (String)left + (String)right;
				}
				
				throw new RuntimeError(expr.operator, "Operands must be numbers or strings.");
			case MINUS:
				if (left instanceof Boolean && !(right instanceof Boolean)) left = isTruthy(left) ? 1.0d : 0.0d;
				else if (right instanceof Boolean && !(left instanceof Boolean)) right = isTruthy(right) ? 1.0d : 0.0d;
				else if (left instanceof Boolean && right instanceof Boolean) {
					double left1 = isTruthy(left) ? 1.0d : 0.0d;
					double right1 = isTruthy(right) ? 1.0d : 0.0d;
					return (left1 - right1) >= 1.0d;
				}
				checkNumberOperands(expr.operator, left, right);
				return (double)left - (double)right;
			case SLASH:
				checkNumberOperands(expr.operator, left, right);
				return (double)left / (double)right;
			case STAR:
				if (left instanceof Boolean && !(right instanceof Boolean)) left = isTruthy(left) ? 1.0d : 0.0d;
				else if (right instanceof Boolean && !(left instanceof Boolean)) right = isTruthy(right) ? 1.0d : 0.0d;
				else if (left instanceof Boolean && right instanceof Boolean) {
					double left1 = isTruthy(left) ? 1.0d : 0.0d;
					double right1 = isTruthy(right) ? 1.0d : 0.0d;
					return (left1 - right1) >= 1.0d;
				}
				checkNumberOperands(expr.operator, left, right);
				return (double)left * (double)right;
			case AND:
				return isTruthy(left) && isTruthy(right);
			case OR:
				if (isTruthy(left)) return true;
				if (isTruthy(right)) return true;
				return false;
		}
		
		return null;
	}
	
	private Object evaluate(Expr expr) {
		return expr.accept(this);
	}
	
	/**
	 * @param object
	 * @return Whether or not the object counts as {@linkplain true} in a comparison
	 */
	private boolean isTruthy(Object object) {
		if (object == null) return false;
		if (object instanceof Boolean) return (boolean)object;
		if ((object instanceof Double) && (double)object == 0.0d) return false;
		if ((object instanceof String) && (((String)object).isEmpty() || ((String)object) == "0")) return false;
		
		return true;
	}
	
	private boolean isEqual(Object a, Object b) {
		// nil is only equal to nil.
		if (a == null && b == null) return true;
		if (a == null || b == null) return false; // Fixed exception when a is not null but b is 
		if (!a.equals(a) || !b.equals(b)) return false;
		if (a instanceof Double && !(b instanceof Double)) a = isTruthy(a);
		if (b instanceof Double && !(a instanceof Double)) b = isTruthy(b);
		if (a instanceof Double && b instanceof String) {
			double bd = Double.parseDouble((String)b);
			return Double.compare((double)a, bd) == 0;
		} else if (b instanceof Double && a instanceof String) {
			double ad = Double.parseDouble((String)a);
			return Double.compare((double)b, ad) == 0;
		}
		
		return a.equals(b);
	}
	
	private void checkNumberOperand(Token operator, Object operand) {
		if (operand instanceof Double) return;
		throw new RuntimeError(operator, "Operand must be a number");
	}
	
	private void checkNumberOperands(Token operator, Object left, Object right) {
		if (left instanceof Double && right instanceof Double) return;
		throw new RuntimeError(operator, "Operands must be numbers.");
	}
	
	@SuppressWarnings("unused")
	private String stringify(Object object) {
		if (object == null) return "nil";
		
		// Hack. Work around Java adding ".0" to integer-valued doubles.
		if (object instanceof Double) {
			String text = object.toString();
			
			if (text.endsWith(".0")) {
				text = text.substring(0, text.length() - 2);
			}
			
			return text;
		}
		
		if (object instanceof Boolean) {
			return (boolean)object ? "true" : "false";
		}
		
		return object.toString();
	}
	
	private void execute(Stmt stmt) throws ReturnThrow {
		stmt.accept(this);
	}
	
	private void executeBlock(List<Stmt> statements, Environment environment) throws ReturnThrow {
		Environment previous = this.environment;
		
		Expr returned = previous.lastReturn;
		
		try {
			this.environment = environment;
			
			for (Stmt statement : statements) {
				try {
					execute(statement);
				} catch (ReturnThrow ret) {
					popEnv();
					returned = environment.lastReturn;
					throw ret;
				}
			}
		} finally {
			this.environment = previous;
			this.environment.lastReturn = returned;
		}
	}
}
