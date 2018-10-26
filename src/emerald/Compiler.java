package emerald;

//General stuff
import org.bytedeco.javacpp.*;

//Headers required by LLVM
import static org.bytedeco.javacpp.LLVM.*;

import java.util.HashMap;
import java.util.Map;

public class Compiler {
	static LLVMContextRef Context;
	static LLVMBuilderRef Builder = new LLVMBuilderRef(Context);
	static LLVMModuleRef Module;
	static Map<String, LLVMValueRef> NamedValues = new HashMap<>();
}
