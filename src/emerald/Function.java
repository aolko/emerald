package emerald;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Function {
	final String name;
	final List<String> accepted;
	final Stmt.Block body;
	final Interpreter creator;
	Environment environment;
	
	public Object Call(List<Expr> arguments) {
		environment = new Environment(creator.environment);
		
		for (int i = 0; i < arguments.size(); i++) {
			if (i > accepted.size())
				break; // Maybe error here if there are more arguments than accepted?
			
			environment.set(new Token(TokenType.IDENTIFIER, accepted.get(i), null, -1), arguments.get(i).accept(creator));
		}
		
		creator.pushEnv(environment);
		creator.interpret(body.statements);
		Object ret = creator.environment.lastReturn != null ? creator.environment.lastReturn.accept(creator) : null;
		creator.popEnv();
		
		return ret;
	}
	
	public Function(Interpreter creator, String name, List<String> accepted, Stmt.Block body) {
		this.creator = creator;
		this.name = name;
		this.accepted = accepted;
		this.body = body;
	}
}
