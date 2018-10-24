package emerald;

/*
 *
 * Autogenerated by Lua script
 * Script written by TheWaffleDimension
 *
 */


import java.util.List;

abstract class Stmt {
	interface Visitor<R> {
		R visitBlockStmt(Block stmt);
		R visitExpressionStmt(Expression stmt);
	}

	static class Block extends Stmt {
		final List<Stmt> statements;

		Block(List<Stmt> statements) {
			this.statements = statements;
		}

		<R> R accept(Visitor<R> visitor) {
			return visitor.visitBlockStmt(this);
		}
	}


	static class Expression extends Stmt {
		final Expr expression;

		Expression(Expr expression) {
			this.expression = expression;
		}

		<R> R accept(Visitor<R> visitor) {
			return visitor.visitExpressionStmt(this);
		}
	}



	abstract <R> R accept(Visitor<R> visitor);
}
