package emerald.compiler;

import java.io.StringWriter;
import java.security.KeyPair;
import java.util.HashMap;
import java.util.Map;

public class MethodBuilder {
	public StringWriter output = new StringWriter();
	public String returnType;
	public String name;
	public Map<String, String> accepted = new HashMap<>();
	
	public void Begin() {
		output.write(returnType + " " + name);
		output.write('(');
		
		int cur = 0;
		
		for (Map.Entry<String, String> arg : accepted.entrySet()) {
			output.write(arg.getValue() + " " + arg.getKey());
			cur++;
			if (cur < accepted.size())
				output.write(',');
		}
		
		output.write(") {\n");
	}
	
	public void End() {
		output.write("\n}\n");
	}
	
	public void DefineLocal(String type, String name) {
		output.write(type + ' ' + name + ";\n");
	}
	
	public void SetLocal(String name, String value) {
		output.write(name + " = " + value + ";\n");
	}
	
	public MethodBuilder(String returnType, String name) {
		this.returnType = returnType;
		this.name = name;
	}
}
