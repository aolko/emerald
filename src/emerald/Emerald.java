package emerald;
import java.io.BufferedReader;                               
import java.io.IOException;                                  
import java.io.InputStreamReader;                            
import java.nio.charset.Charset;                             
import java.nio.file.Files;                                  
import java.nio.file.Paths;                                  
import java.util.List;

public class Emerald
{
	private static boolean hadError = false;
	private static boolean hadRuntimeError = false;
	private static Interpreter interpreter = new Interpreter();
	private static Compiler compiler = new Compiler();
	
	public static void main(String[] args) throws IOException {
		if (args.length > 1) {
			System.out.println("Usage: emerald [script]");
			System.exit(64);
		} else if (args.length == 1) {
			runFile(args[0]);
		} else {
			runPrompt();
		}
	}
	
	private static void runFile(String path) throws IOException {
		byte[] bytes = Files.readAllBytes(Paths.get(path));
		run(new String(bytes, Charset.defaultCharset()));
		
		if (hadError) System.exit(65);
		if (hadRuntimeError) System.exit(70);
	}
	
	private static void runPrompt() throws IOException {
		InputStreamReader input = new InputStreamReader(System.in);
		BufferedReader reader = new BufferedReader(input);
		
		for (;;) {
			System.out.print("> ");
			run(reader.readLine());
			
			hadError = false;
		}
	}
	
	private static void run(String source) {
		Scanner scanner = new Scanner(source);
		List<Token> tokens = scanner.scanTokens();
		
		Parser parser = new Parser(tokens);
		List<Stmt> statements = parser.parse();
		
		// Stop if there was a syntax error.
		if (hadError) return;
		
		interpreter.interpret(statements);
	}
	
	static void runtimeError(RuntimeError error) {
		System.err.println(error.getMessage() + "\n[line " + error.token.line + "]");
		error.printStackTrace(System.err);
		hadRuntimeError = true;
	}
	
	static void error(Token token, String message) {
		if (token.type == TokenType.EOF) {
			report(token.line, " at end", message);
		} else {
			report(token.line, " at '" + token.lexeme + "'", message);
		}
	}
	
	static void error(int line, String message) {
		report(line, "", message);
	}
	
	private static void report(int line, String where, String message) {
		System.err.println("[line " + line + "] Error" + where + ": " + message);
		hadError = true;
	}
}
