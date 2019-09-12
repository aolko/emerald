package emerald;

import static emerald.TokenType.*;

import java.util.ArrayList;
import java.util.List;

import emerald.Expr;
import emerald.Expr.Literal;
import emerald.Stmt;

public class Parser {
	@SuppressWarnings("serial")
	private static class ParseError extends RuntimeException {};
	@SuppressWarnings("serial")
	private static class SemiColon extends RuntimeException {};
	
	private final List<Token> tokens;
	private int current = 0;
	
	Parser(List<Token> tokens) {
		this.tokens = tokens;
	}
	
	List<Stmt> parse() {
		List<Stmt> statements = new ArrayList<>();
		
		while (!isAtEnd()) {
			Stmt stmt = declaration();
			
			if (stmt == null)
				continue;
			
			statements.add(stmt);
		}
		
		return statements;
	}
	
	private Stmt declaration() {
		try {
			if (match(IDENTIFIER))  {
				
				Token prev = previous();
				
				if (match(LEFT_PAREN)) {
					return new Stmt.Expression(new Expr.Call(prev.lexeme, parametersEx()));
				}
				
				return varDeclaration();
			};
			if (match(SIGIL)) return globalVarDeclaration();
			if (match(PLUS_PLUS)) return plusFix(advance(), true);
			if (match(MINUS_MINUS)) return minusFix(advance(), true);
			if (match(SEMICOLON)) return null;
			if (match(FN)) return function();
			if (match(RETURN)) return ret();
			
			return statement();
		} catch (ParseError error) {
			synchronize();
			return null;
		}
	}
	
	private Stmt ret() {
		return new Stmt.Return(expression());
	}
	
	private List<String> parameters() {
		List<String> result = new ArrayList<>();
		
		// Should be impossible to loop forever
		while (true) {
			if (match(RIGHT_PAREN))
				break;

			if (check(IDENTIFIER)) {
				result.add(advance().lexeme);

				if (! check(RIGHT_PAREN))
					consume(COMMA, "Expected ',' near '" + tokens.get(current - 1).lexeme + "'");
			}
			else {
				error(tokens.get(current - 1), "Unexpected token '" + advance().lexeme + "'");
			}
		}
		
		return result;
	}
	
	// Parameters as expressions
	private List<Expr> parametersEx() {
		List<Expr> result = new ArrayList<>();
		
		// Should be impossible to loop forever
		while (true) {
			if (match(RIGHT_PAREN))
				break;

			result.add(expression());
			// fn ret(num): return 15 + num end
			if (! check(RIGHT_PAREN))
				consume(COMMA, "Expected ',' near '" + tokens.get(current - 1).lexeme + "'");
		}
		
		return result;
	}
	
	private Stmt function() {
		Token name = advance();
		List<String> arguments;
		
		consume(LEFT_PAREN, "Expected '(' near '" + tokens.get(current - 1).lexeme + "'");
		
		arguments = parameters();

		Stmt.Block body = new Stmt.Block(block());
		
		return new Stmt.Func(name.lexeme, arguments, body);
	}
	
	private Stmt call(String name) {
		List<Expr> arguments = parametersEx();
		
		return new Stmt.Expression(new Expr.Call(name, arguments));
	}
	
	private Stmt plusFix(Token target, Boolean prefix) {
		return new Stmt.Expression(new Expr.Fix(new Token(PLUS_PLUS, "++", "++", tokens.get(current).line), target, prefix));
	}
	
	private Stmt minusFix(Token target, Boolean prefix) {
		return new Stmt.Expression(new Expr.Fix(new Token(MINUS_MINUS, "--", "--", tokens.get(current).line), target, prefix));
	}
	
	private Stmt varDeclaration() {
		Token identifier = previous();
		
		if (match(PLUS_PLUS)) return plusFix(identifier, false);
		if (match(MINUS_MINUS)) return minusFix(identifier, false);
		if (match(LEFT_PAREN)) return call(identifier.lexeme);

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
		if (match(PRINT)) return printStatement();
		
		return expressionStatement();
	}
	
	private Stmt printStatement() {
		return new Stmt.Print(expression());
	}
	
	private Stmt ifStatement() {
		Expr condition = expression();
		
		Stmt ifBody;
		
		ifBody = new Stmt.Block(block());
		
		Stmt elseBody = null;
		if (match(ELSE)) {
			elseBody = new Stmt.Block(block());
		} else if (match(ELSEIF)) {
			elseBody = ifStatement();
		}
		
		return new Stmt.If(condition, ifBody, elseBody);
	}
	
	private List<Stmt> block() {
		List<Stmt> statements = new ArrayList<>();
		
		consume(COLON, "Expected ':' to begin block near '" + tokens.get(current - 1).lexeme + "'");
		
		while (! match(TokenType.END) && ! check(TokenType.ELSE) && ! isAtEnd()) {
			Stmt stmt = declaration();
			
			// Might be a semicolon!
			if (stmt != null)
				statements.add(stmt);
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
			
			// previous will be invalidated after match is called so it is saved here
			Token prev = previous();
			
			if (match(PLUS_PLUS)) {
				return new Expr.Fix(new Token(PLUS_PLUS, "++", "++", tokens.get(current).line), prev, false);
			}
			
			if (match(MINUS_MINUS)) {
				return new Expr.Fix(new Token(MINUS_MINUS, "--", "--", tokens.get(current).line), prev, false);
			}
			
			if (match(LEFT_PAREN)) {
				return new Expr.Call(prev.lexeme, parametersEx());
			}
			
			return new Expr.Variable(prev);
		}
		
		if (match(PLUS_PLUS)) {
			return new Expr.Fix(new Token(PLUS_PLUS, "++", "++", tokens.get(current).line), advance(), true);
		}
		
		if (match(MINUS_MINUS)) {
			return new Expr.Fix(new Token(MINUS_MINUS, "--", "--", tokens.get(current).line), advance(), true);
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
