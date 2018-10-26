package emerald;

import static emerald.TokenType.*;

import java.util.ArrayList;
import java.util.List;

import emerald.Expr;
import emerald.Stmt;

public class Parser {
	@SuppressWarnings("serial")
	private static class ParseError extends RuntimeException {};
	
	private final List<Token> tokens;
	private int current = 0;
	
	Parser(List<Token> tokens) {
		this.tokens = tokens;
	}
	
	List<Stmt> parse() {
		List<Stmt> statements = new ArrayList<>();
		
		while (!isAtEnd()) {
			statements.add(declaration());
		}
		
		return statements;
	}
	
	private Stmt declaration() {
		try {
			if (match(IDENTIFIER)) return varDeclaration();
			if (match(SIGIL)) return globalVarDeclaration();
			
			return statement();
		} catch (ParseError error) {
			synchronize();
			return null;
		}
	}
	
	private Stmt varDeclaration() {
		Token identifier = previous();
		
		Expr value = null;
		if (!match(SEMICOLON)) {
			consume(EQUAL, "Expect '=' after identifier.");
			value = expression();
		}
		
		return new Stmt.Var(identifier, value, false);
	}
	
	private Stmt globalVarDeclaration() {
		Token identifier = consume(IDENTIFIER, "Expect identifier after '$'.");
		
		Expr value = null;
		if (!match(SEMICOLON)) {
			consume(EQUAL, "Expect '=' after identifier.");
			value = expression();
		}
		
		return new Stmt.Var(identifier, value, true);
	}
	
	private Stmt statement() {
		if (match(IF)) return ifStatement(); 
		if (match(INDENT)) return new Stmt.Block(block());
		
		return expressionStatement();
	}
	
	private Stmt ifStatement() {
		Expr condition = expression();
		
		consume(COLON, "Expect `:` after condition.");
		
		Stmt ifBody;
		if (match(INDENT)) {
			ifBody = new Stmt.Block(block());
		} else {
			ifBody = declaration();
		}
		
		Stmt elseBody = null;
		if (match(ELSE)) {
			consume(COLON, "Expect `:` after 'else'.");
			if (match(INDENT)) {
				elseBody = new Stmt.Block(block());
			} else {
				elseBody = declaration();
			}
		} else if (match(ELSEIF)) {
			elseBody = ifStatement();
		}
		
		return new Stmt.If(condition, ifBody, elseBody);
	}
	
	private List<Stmt> block() {
		List<Stmt> statements = new ArrayList<>();
		
		while (!match(DEDENT) && !isAtEnd()) {
			statements.add(declaration());
		}
		
		return statements;
	}
	
	private Stmt expressionStatement() {
		Expr expr = expression();
		return new Stmt.Expression(expr);
	}
	
	private Expr expression() {
		return assignment();
	}
	
	private Expr assignment() {
		Expr expr = bitwise();
		
		if (match(EQUAL)) {
			Token equals = previous();
			Expr value = assignment();
			
			if (expr instanceof Expr.Variable) {
				Token name = ((Expr.Variable) expr).name;
				return new Expr.Assign(name, value);
			}
			
			error(equals, "Invalid assignment target.");
		}
		
		return expr;
	}
	
	private Expr bitwise() {
		Expr expr = logical();
		
		while (match(BIT_AND, BIT_OR, BIT_XOR)) {
			Token operator = previous();
			Expr right = logical();
			expr = new Expr.Binary(expr, operator, right);
		}
		
		return expr;
	}
	
	private Expr logical() {
		Expr expr = equality();
		
		while (match(AND, OR)) {
			Token operator = previous();
			Expr right = equality();
			expr = new Expr.Binary(expr, operator, right);
		}
		
		return expr;
	}
	
	private Expr equality() {
		Expr expr = comparison();
		
		while (match(BANG_EQUAL, EQUAL_EQUAL)) {
			Token operator = previous();
			Expr right = comparison();
			expr = new Expr.Binary(expr, operator, right);
		}
		
		return expr;
	}
	
	private Expr comparison() {
		Expr expr = addition();
		while (match(GREATER, GREATER_EQUAL, LESS, LESS_EQUAL, SIGN)) {
			Token operator = previous();
			Expr right = addition();
			expr = new Expr.Binary(expr, operator, right);
		}
		
		return expr;
	}
	
	private Expr addition() {
		Expr expr = multiplication();
		while (match(MINUS, PLUS)) {
			Token operator = previous();
			Expr right = multiplication();
			expr = new Expr.Binary(expr, operator, right);
		}
		
		return expr;
	}
	
	private Expr multiplication() {
		Expr expr = unary();
		while (match(SLASH, STAR)) {
			Token operator = previous();
			Expr right = unary();
			expr = new Expr.Binary(expr, operator, right);
		}
		
		return expr;
	}
	
	private Expr unary() {
		if (match(BANG, MINUS)) {
			Token operator = previous();
			Expr right = unary();
			return new Expr.Unary(operator, right);
		}
		
		return primary();
	}
	
	private Expr primary() {
		if (match(FALSE)) return new Expr.Literal(false);
		if (match(TRUE)) return new Expr.Literal(true);
		if (match(NIL)) return new Expr.Literal(null);
		
		if (match(NUMBER, STRING)) {
			return new Expr.Literal(previous().literal);
		}
		
		if (match(IDENTIFIER)) {
			return new Expr.Variable(previous());
		}
		
		if (match(LEFT_PAREN)) {
			Expr expr = expression();
			consume(RIGHT_PAREN, "Expected ')' after expression.");
			return new Expr.Grouping(expr);
		}
		
		throw error(peek(), "Expected expression.");
	}
	
	private boolean match(TokenType... types) {
		for (TokenType type : types) {
			if (check(type)) {
				advance();
				return true;
			}
		}
		
		return false;
	}
	
	private boolean check(TokenType type) {
		if (isAtEnd()) return false;
		return peek().type == type;
	}
	
	private Token advance() {
		if (!isAtEnd()) current++;
		return previous();
	}
	
	private Token consume(TokenType type, String message) {
		if (check(type)) return advance();
		
		throw error(peek(), message);
	}
	
	private boolean isAtEnd() {
		return peek().type == EOF;
	}
	
	private Token peek() {
		return tokens.get(current);
	}
	
	private Token previous() {
		return tokens.get(current - 1);
	}
	
	private ParseError error(Token token, String message) {
		Emerald.error(token, message);
		return new ParseError();
	}
	
	private void synchronize() {
		advance();
		
		while (!isAtEnd()) {
			if (previous().type == SEMICOLON || previous().type == NEWLINE) return;
			
			switch(peek().type) {
				case FN:
				case VAR:
				case FOR:
				case IF:
				case WHILE:
				case PRINT:
				case RETURN:
					return;
				default: break;
			}
			
			advance();
		}
	}
}
