package emerald;

import java.util.List;

import emerald.Expr;

public class Interpreter implements Expr.Visitor<Object>, Stmt.Visitor<Void> {
	private Environment environment = new Environment();
	
	void interpret(List<Stmt> statements) {
		try {
			for (Stmt statement : statements) {
				execute(statement);
			}
		} catch (RuntimeError error) {
			Emerald.runtimeError(error);
		}
	}
	
	@Override
	public Void visitExpressionStmt(Stmt.Expression stmt) {
		evaluate(stmt.expression);
		return null;
	}
	
	@Override
	public Void visitBlockStmt(Stmt.Block stmt) {
		executeBlock(stmt.statements, new Environment(environment));
		return null;
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
		if (a == null) return false;
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
	
	private void execute(Stmt stmt) {
		stmt.accept(this);
	}
	
	private void executeBlock(List<Stmt> statements, Environment environment) {
		Environment previous = this.environment;
		
		try {
			this.environment = environment;
			
			for (Stmt statement : statements) {
				execute(statement);
			}
		} finally {
			this.environment = previous;
		}
	}
}
