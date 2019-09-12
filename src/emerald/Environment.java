package emerald;

import java.util.HashMap;
import java.util.Map;

public class Environment {
	final Environment enclosing;
	private final Map<String, Object> values = new HashMap<>();
	private final Map<String, Function> functions = new HashMap<>();
	public Expr lastReturn = null;
	
	Environment() {
		enclosing = null;
	}
	
	Environment(Environment enclosing) {
		this.enclosing = enclosing;
	}
	
	Object get(Token name) {
		if (values.containsKey(name.lexeme)) {
			return values.get(name.lexeme);
		}
		
		if (enclosing != null) return enclosing.get(name);
		
		throw new RuntimeError(name, "Undefined variable '" + name.lexeme + "'.");
	}
	
	void assign(Token name, Object value) {
		if (values.containsKey(name.lexeme)) {
			values.put(name.lexeme, value);
			return;
		}
		
		if (enclosing != null) {
			enclosing.values.put(name.lexeme, value);
			return;
		}
		
		throw new RuntimeError(name, "Undefined variable '" + name.lexeme + "'.");
	}
	
	void define(String name, Object value) {
		values.put(name, value);
	}
	
	void defineFunc(Function func) {
		functions.put(func.name, func);
	}
	
	Function getFunc(String name) {
		Function func = functions.get(name);
		
		if (func == null) {
			if (enclosing != null)
				return enclosing.getFunc(name);
			
			return null;
		}
		
		return func;
	}
	
	/**
	 * Assigns a variable or defines it if it does not exist
	 * @param name
	 * @param value
	 */
	void set(Token name, Object value) {
		try {
			get(name);
			assign(name, value);
		}
		catch (RuntimeError e) {
			define(name.lexeme, value);
		}
	}
}
