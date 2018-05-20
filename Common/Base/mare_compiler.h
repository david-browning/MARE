#pragma once
#include <annotations.h>
#include "mare_isymbol_table.h"
#include "mare_stmt.h"
#include "mare_expression.h"

/*
 The compiler class handles converting text and symbols into statements that are
 written to an output file. The parser calls these functions to compile a MARE program.
 */
class LIB_EXPORT MARECompiler
{
	public:
	/*
	 Constructor.
	 "out" is the output stream where the compiler output, i.e. statements, will be written.
	 Set "supressErrors" to true if the compiler should not print messages when it encounters an
	 error. The compiler will still throw an exception if it encounters an error.
	 "err" is the out stream to print compiler errors to. By default, it uses standard error.
	 */
	MARECompiler(std::ostream& out,
					 _IN_OPT_ bool supressErrors = false,
					 _IN_OPT_ std::ostream& err = std::cerr);

	MARECompiler(const MARECompiler& c) = delete;

	MARECompiler(MARECompiler&& m) = delete;

	/*
	 Destructor.
	 */
	virtual ~MARECompiler();

	/*
	 Returns a pointer to the symbol with name "varName".
	 The symbol table throws symbol_not_defined_exception if the symbol is not found.
	 */
	const Symbol* SymbolLookup(const std::string& varName);

	/*
	 Inserts a symbol with name "symName" and type "type" and returns a pointer to it.
	 If a symbol cannot be inserted, this is likely because the symbol name collides with another
	 symbol in the same or greater scope.
	 The symbol table throws an exception if the symbol cannot be inserted.
	 */
	Symbol* InsertSymbol(const std::string& symName, const IAtom& type);

	/*
	 Returns an expression that, when evaluated, gives the "index"'th element from the array
	 "arrayName"
	 This function throws:
	  symbol_not_defined_exception if "arrayName" is not a symbol in scope.
	  type_mismatch_exception is "arrayName" is not an array.
	 */
	Expression IndexExpression(const std::string& arrayName, const Expression& index);

	/*
	 */
	Expression ToCMExpression(const Literal& lit);

	/*
	 */
	Expression ToInchExpression(const Literal& lit);

	/*
	 */
	Expression ToArrayCountExpression(const std::string& arrayName);

	/*
	 */
	IAtom MakeArrayType(const IAtom& type, const Literal& arrayCount);

	/*
	 */
	StmtPtr InlineCodeStmt(const Literal& code);

	/*
	 */
	StmtPtr AssignVarStmt(const std::string& varName, const Expression& expr);

	/*
	 */
	StmtPtr AssignVarStmt(const std::string& varName,
								 const Expression& expr,
								 const Expression& index);

	/*
	 */
	StmtPtr ReturnStmt(const Expression& expr);

	/*
	 */
	StmtPtr BreakStmt();

	/*
	 */
	StmtPtr IfStmt(const Expression& conditional, StmtList& trueStmts);

	/*
	 */
	StmtPtr IfStmt(const Expression& conditional, StmtList& trueStmts, StmtList& falseStmts);

	/*
	 */
	StmtPtr LoopUntilStmt(const Expression& condition, StmtList& stmts);

	/*
	 */
	StmtPtr LoopTimesStmt(const Expression& count, StmtList& stmts);

	/*
	 */
	StmtPtr DeclareVariableStmt(const std::string& varName,
										 const IAtom& typeInfo,
										 const Expression& expr);

	/*
	 */
	StmtPtr DeclareVariableConstStmt(const std::string&,
												const IAtom& typeInfo,
												const Expression& expr);

	/*
	 */
	StmtPtr DeclareVariableConstExpressionStmt(const std::string& varName,
															 const IAtom& typeInfo,
															 const Expression& expr);

	/*
	 */
	StmtPtr DeclareVariableArrayStmt(const std::string& varName,
												const IAtom& typeInfo,
												const ExprList& exprs);

	/*
	 */
	StmtPtr DeclareFunctionStmt(const std::string& fName,
										 const IAtom& fType,
										 const ParamList& args,
										 const StmtList& stmts);

	/*
	 */
	StmtPtr CallFunctionStmt(const std::string& fName,
									 const ExprList& args);

	/*
	 */
	StmtPtr DeclareParameterStmt(const std::string& paramName,
										  const IAtom& type);

	/*
	 */
	StmtPtr DeclareCompoundTypeStmt(const std::string& compoundName, const StmtList& delcs);

	/*
	 Writes the statement to the compiler output.
	 */
	void WriteStmt(const StmtPtr stmt_p);

	/*
	 Writes the list of statements to the compiler output.
	 */
	void WriteStmtList(const StmtList& stmts);

	/*
	 */
	void OpenScope();

	/*
	 */
	void CloseScope();

	/*
	 */
	void WriteProgram(StmtList& decls1, StmtList& decls2, StmtList& decls3);

	/*
	 Prints the compiler metrics to the the output stream "screen".
	 If compiler metrics were not enabled when this class was constructed, then the 
	 output is indeterminate.
	 */
	void PrintMetrics(_IN_OPT_ std::ostream& screen = std::cout);

	/*
	 */
	inline void SetLineNumber(size_t lineNum)
	{
		_lineNum = lineNum;
	}
	
	/*
	 Gets the stream where the compiler prints its errors to.
	 */
	inline std::ostream& ErrStream()
	{
		return _err;
	}

	/*
	 Returns true if errors should not be printed to the error stream.
	 */
	inline bool IsSupressErrors() const
	{
		return _supressErr;
	}

	/*
	 Gets the stream where the compiler prints its output to.
	 */
	inline std::ostream& OutStream()
	{
		return _out;
	}

	/*
	 Compiler metrics.
	 */
	struct COMPILER_METRICS
	{
		friend std::ostream& operator<<(std::ostream& os, const COMPILER_METRICS& m);

		size_t StatementCount;
	};

	protected:
	
	/*
	 Prints an error message indicating which line in the source file contains the error.
	 */
	virtual void WriteLineError()
	{
		ErrStream() << "Error at line " << _lineNum << ".\n";
	}

	private:

	/*
	 Compiler metrics.
	 */
	COMPILER_METRICS _m;

	/*
	 Compiler symbol table.
	 */
	ISymbolTable<std::string, int> _symTable;
	
	/*
	 The stream where the compiler output is written to.
	 */
	std::ostream& _out;
	
	/*
	 The stream where compiler errors are written to.
	 */
	std::ostream& _err;
	
	/*
	 True if the compiler should not write errors to the error stream.
	 */
	bool _supressErr;
	
	/*
	 Current line number.
	 */
	size_t _lineNum;
};