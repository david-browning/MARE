#include "mare_compiler.h"
#include "mare_compiler_type_comparator.h"
#include "mare_stmt_assignment.h"
#include "mare_stmt_func_decl.h"
#include "mare_stmt_func_call.h"
#include "mare_stmt_code.h"
#include "mare_stmt_if.h"
#include "mare_stmt_decl.h"
#include "mare_stmt_loop_times.h"
#include "mare_stmt_loop_until.h"
#include "mare_stmt_param.h"
#include "mare_stmt_compound_decl.h"
#include "mare_stmt_ret.h"

std::string MutateString(const std::string& str)
{
	return std::string("_") + str;
}

MARECompiler::MARECompiler(std::ostream & out, _IN_OPT_ bool supressErrors, _IN_OPT_ std::ostream & err) :
	_symTable(MutateString), _err(err), _supressErr(supressErrors), _out(out)
{
}

MARECompiler::~MARECompiler()
{

}

const Symbol* MARECompiler::SymbolLookup(const std::string& varName)
{
	auto s = _symTable.Lookup(varName);
	if(!s)
	{
		if(!IsSupressErrors())
		{
			WriteLineError();
			ErrStream() << "Symbol \"" << varName << "\" was not declared." << std::endl;
			ErrStream() << "You must declare a symbol before using it." << std::endl;
		}

		throw symbol_not_defined_exception(varName);
	}

	return s;
}

Symbol* MARECompiler::InsertSymbol(const std::string& symName, const IAtom& type)
{
	return _symTable.Insert(symName, type);
}

Expression MARECompiler::IndexExpression(const std::string& arrayName, const Expression& index)
{
	auto s = _symTable.Lookup(arrayName);
	if(!s)
	{
		if(!IsSupressErrors())
		{
			WriteLineError();
			ErrStream() << "Symbol \"" << arrayName << "\" was not declared." << std::endl;
			ErrStream() << "You must declare a variable before using it." << std::endl;
		}

		throw symbol_not_defined_exception(arrayName);
	}

	if(!s->IsArrayType())
	{
		if(!IsSupressErrors())
		{
			WriteLineError();
			ErrStream() << "Symbol \"" << arrayName << "\" is not an array" << std::endl;
			ErrStream() << "You can only use the index operator \"[]\" with arrays." << std::endl;
		}

		throw type_mismatch_exception();
	}

	return Expression(*s, index);
}

Expression MARECompiler::ToCMExpression(const Literal& lit)
{
	//Check that the literal is a numeric type.

	Expression e(MULTIPLY_OPERATOR);
	e.SetLeft(lit);
	e.SetRight(PIXELS_PER_CM_LITERAL);
	return e;
}

Expression MARECompiler::ToInchExpression(const Literal& lit)
{
	//Check that the literal is a numeric type.

	Expression e(MULTIPLY_OPERATOR);
	e.SetLeft(lit);
	e.SetRight(PIXELS_PER_INCH_LITERAL);
	return e;
}

Expression MARECompiler::ToArrayCountExpression(const std::string& arrayName)
{
	auto s = this->SymbolLookup(arrayName);
	if(!s)
	{
		if(!IsSupressErrors())
		{
			WriteLineError();
			ErrStream() << "Symbol \"" << arrayName << "\" was not declared." << std::endl;
			ErrStream() << "You must declare a symbol before using it." << std::endl;
		}

		throw symbol_not_defined_exception(arrayName);
	}

	auto aCount = s->GetArrayCount();

	if(aCount == 0)
	{
		std::string varCount = s->GetSymbolName() + std::string(".size()");
		Literal l(INT_TYPE_INFO_C, varCount.c_str(), varCount.length(), true);
		Expression e(l);
		return e;
	}
	else
	{
		Literal l(INT_TYPE_INFO_C, &aCount, sizeof(aCount));
		Expression e(l);
		return e;
	}
}

IAtom MARECompiler::MakeArrayType(const IAtom& type, const Literal& arrayCount)
{
	IAtom ret(type);
	try
	{
		ret.MakeArray(arrayCount.GetDataAsInt());
	}
	catch(type_mismatch_exception)
	{
		if(!IsSupressErrors())
		{
			WriteLineError();
			ErrStream() << "The array count is not an integer." << std::endl;
			ErrStream() << "An integer literal must go between the \"[]\"." << std::endl;
		}
	}

	return ret;
}

StmtPtr MARECompiler::InlineCodeStmt(const Literal& code)
{
	auto codeStrLen = code.GetDataSize();
	std::string codeStr = std::string(code.GetDataPointer<char>(), codeStrLen);
	return std::make_shared<CodeStatement>(CodeStatement(codeStr, _symTable));
}

StmtPtr MARECompiler::AssignVarStmt(const std::string& varName,
												const Expression& expr)
{
	auto s = _symTable.Lookup(varName);
	if(!s)
	{
		if(!IsSupressErrors())
		{
			WriteLineError();
			ErrStream() << "Symbol \"" << varName << "\" was not declared." << std::endl;
			ErrStream() << "You must declare a variable before using it." << std::endl;
		}

		throw symbol_not_defined_exception(varName);
	}

	//Type check.
	if(!IsTypesAssignable(*s, expr))
	{
		if(!IsSupressErrors())
		{
			WriteLineError();
			ErrStream() << "Cannot assign expression to \"" << varName << "\". The types are not compatible." << std::endl;
			ErrStream() << "Type " << expr.GetType() << " cannot be assigned to type " << s->GetType() << "." << std::endl;
		}

		throw type_mismatch_exception();
	}

	return std::make_shared<AssignmentStatement>(AssignmentStatement(*s, expr));
}

StmtPtr MARECompiler::AssignVarStmt(const std::string& varName,
												const Expression& expr,
												const Expression& index)
{
	auto s = _symTable.Lookup(varName);
	if(!s)
	{

	}

	//Make sure the type is an array
	if(!s->IsArrayType())
	{
		if(!IsSupressErrors())
		{
			WriteLineError();
			ErrStream() << "Symbol \"" << varName << "\" is not an array type." << std::endl;
			ErrStream() << "You can only use [] on types that are arrays." << std::endl;
		}

		throw type_mismatch_exception();
	}

	//Make sure we can assign expression to array[index]
	if(!IsArrayIndexTypeAssignable(*s, expr))
	{
		if(!IsSupressErrors())
		{
			WriteLineError();
			ErrStream() << "Cannot assign expression to \"" << varName << "\". The types are not compatible.\n";
			ErrStream() << "Type " << expr.GetType() << " cannot be assigned to type " << s->GetType() << ".\n";
		}

		throw type_mismatch_exception();
	}

	return std::make_shared<AssignmentStatement>(AssignmentStatement(*s, index, expr));
}

StmtPtr MARECompiler::CallFunctionStmt(const std::string& fName,
													const ExprList& args)
{
	auto s = _symTable.Lookup(fName);
	if(!s)
	{
		if(!IsSupressErrors())
		{
			WriteLineError();
			ErrStream() << "Function \"" << fName << "\" was not declared." << std::endl;
			ErrStream() << "You must declare a function before using it." << std::endl;
		}

		throw symbol_not_defined_exception(fName);
	}

	if(args.size() != s->GetArgumentCount())
	{
		if(!IsSupressErrors())
		{
			WriteLineError();
			ErrStream() << "Function \"" << fName << "\" does not have the correct number of arguments." << std::endl;
			ErrStream() << "\"" << fName << "\" expects " << s->GetArgumentCount() << " arguments but got " << args.size() << "." << std::endl;
		}

		throw wrong_argument_count_exception();
	}

	int i = 0;
	for(auto it = s->ArgBegin(); it != s->ArgEnd(); ++it, i++)
	{
		//Check that the argument types match.
		if(!IsTypesAssignable(*it, args.at(i)))
		{
			if(!IsSupressErrors())
			{
				WriteLineError();
				ErrStream() << "Cannot assign expression to " << fName << "'s " << i + 1 << "th argument. The types are not compatible." << std::endl;
				ErrStream() << "Type " << args.at(i).GetType() << " cannot be assigned to type " << it->GetType() << "." << std::endl;
				if(it->IsArrayType())
				{
					ErrStream() << "The left array has " << it->GetArrayCount() <<
						" elements and the right array has " << args.at(i).GetArrayCount() << " elements." << std::endl;
				}
			}

			throw type_mismatch_exception();
		}
	}

	return std::make_shared<FunctionCallStatement>(FunctionCallStatement(*s, args));
}

StmtPtr MARECompiler::DeclareFunctionStmt(const std::string& fName,
														const IAtom& fType,
														const ParamList& args,
														const StmtList& stmts)
{
	//Check if symbol was already declared.
	if(_symTable.Lookup(fName))
	{
		if(!IsSupressErrors())
		{
			WriteLineError();
			ErrStream() << "Symbol \"" << fName << "\" was already declared." << std::endl;
			ErrStream() << "You cannot have two variables with the same name in the same scope." << std::endl;
		}

		throw symbol_already_declared_exception(fName);
	}

	IAtom fInfo = IAtom(fType);
	fInfo.MakeFunction();

	for(auto it = args.begin(); it != args.end(); ++it)
	{
		fInfo.AppendArgument(**it);
	}

	auto s = _symTable.Insert(fName, fInfo);
	if(!s)
	{
		if(!IsSupressErrors())
		{
			WriteLineError();
			ErrStream() << "The compiler could not keep track of symbol " << fName << std::endl;
		}

		throw std::exception();
	}

	return std::make_shared<FunctionDeclarationStatement>(FunctionDeclarationStatement(*s, args, stmts));
}

StmtPtr MARECompiler::DeclareParameterStmt(const std::string& paramName,
														 const IAtom& type)
{
	auto s = _symTable.Insert(paramName, type);

	return std::make_shared<ParameterStatement>(ParameterStatement(*s));
}

StmtPtr MARECompiler::DeclareCompoundTypeStmt(const std::string& compoundName, const StmtList& delcs)
{
	return std::make_shared<CompoundDeclStatement>(CompoundDeclStatement(compoundName, delcs));
}

StmtPtr MARECompiler::ReturnStmt(const Expression& expr)
{
	return std::make_shared<ReturnStatement>(ReturnStatement(expr));
}

StmtPtr MARECompiler::BreakStmt()
{
	return std::make_shared<Statement>(Statement(NOP_STATEMENT));
}

StmtPtr MARECompiler::IfStmt(const Expression& conditional,
									  StmtList& trueStmts)
{
	return std::make_shared<IfStatement>(IfStatement(conditional, trueStmts));
}

StmtPtr MARECompiler::IfStmt(const Expression& conditional,
									  StmtList& trueStmts,
									  StmtList& falseStmts)
{
	return std::make_shared<IfStatement>(IfStatement(conditional, trueStmts, falseStmts));
}

StmtPtr MARECompiler::LoopUntilStmt(const Expression& condition, StmtList& stmts)
{
	return std::make_shared<LoopUntilStatement>(LoopUntilStatement(condition, stmts));
}

StmtPtr MARECompiler::LoopTimesStmt(const Expression& count, StmtList& stmts)
{
	return std::make_shared<LoopTimesStatement>(LoopTimesStatement(count, stmts));
}

StmtPtr MARECompiler::DeclareVariableStmt(const std::string& varName,
														const IAtom& typeInfo,
														const Expression& expr)
{
	//Check that the type is not null.
	if(typeInfo.IsNullType())
	{
		if(!IsSupressErrors())
		{
			WriteLineError();
			ErrStream() << "You cannot declare a variable with no type." << std::endl;
		}

		throw invalid_type_exception();
	}

	//Check if symbol was already declared.
	if(_symTable.Lookup(varName))
	{
		if(!IsSupressErrors())
		{
			WriteLineError();
			ErrStream() << "Symbol \"" << varName << "\" was already declared." << std::endl;
			ErrStream() << "You cannot have two variables with the same name in the same scope." << std::endl;
		}

		throw symbol_already_declared_exception(varName);
	}

	//Type check the typeInfo with the expression
	if(!IsTypesAssignable(typeInfo, expr, true))
	{
		if(!IsSupressErrors())
		{
			WriteLineError();
			ErrStream() << "Cannot assign expression to \"" << varName << "\". The types are not compatible." << std::endl;
			ErrStream() << "Type " << expr.GetType() << " cannot be assigned to type " << typeInfo << "." << std::endl;
		}

		throw type_mismatch_exception();
	}

	auto s = _symTable.Insert(varName, typeInfo);
	if(!s)
	{
		if(!IsSupressErrors())
		{
			WriteLineError();
			ErrStream() << "The compiler could not keep track of symbol " << varName << std::endl;
		}

		throw std::exception();
	}

	return std::make_shared<DeclarationStatement>(DeclarationStatement(*s, expr));
}

StmtPtr MARECompiler::DeclareVariableConstStmt(const std::string& name,
															  const IAtom& typeInfo,
															  const Expression& expr)
{
	IAtom constedType = typeInfo;
	constedType.MakeConstant();
	return DeclareVariableStmt(name, constedType, expr);
}

StmtPtr MARECompiler::DeclareVariableConstExpressionStmt(const std::string& varName,
																			const IAtom& typeInfo,
																			const Expression& expr)
{
	// TODO: Assign const expression to var.
	if(!IsSupressErrors())
	{
		WriteLineError();
		ErrStream() << "You cannot assign an expression to a constant variable." << std::endl;
	}

	throw constant_not_allowed_exception();
}

StmtPtr MARECompiler::DeclareVariableArrayStmt(const std::string& varName,
															  const IAtom& typeInfo,
															  const ExprList& exprs)
{
	//Check that the type is not null.
	if(typeInfo.IsNullType())
	{
		if(!IsSupressErrors())
		{
			ErrStream() << "You cannot declare a variable with no type." << std::endl;
		}

		throw invalid_type_exception();
	}

	//Check if symbol was already declared.
	if(_symTable.Lookup(varName))
	{
		if(!IsSupressErrors())
		{
			WriteLineError();
			ErrStream() << "Symbol \"" << varName << "\" was already declared." << std::endl;
			ErrStream() << "You cannot have two variables with the same name in the same scope." << std::endl;
		}

		throw symbol_already_declared_exception(varName);
	}

	//If the array specifier was included, make sure the number of statements match.
	if(typeInfo.IsArrayType() && typeInfo.GetArrayCount() != exprs.size())
	{
		if(!IsSupressErrors())
		{
			WriteLineError();
			ErrStream() << "The number of expressions does not match the array size." << std::endl;
			ErrStream() << "There are " << exprs.size() << " expressions but " << varName <<
				" is a " << typeInfo.GetArrayCount() << " sized array." << std::endl;
		}

		throw type_mismatch_exception();
	}


	IAtom arrayInfo(typeInfo);
	arrayInfo.MakeArray(exprs.size());

	auto s = _symTable.Insert(varName, arrayInfo);
	if(!s)
	{
		if(!IsSupressErrors())
		{
			WriteLineError();
			ErrStream() << "The compiler could not keep track of symbol " << varName << std::endl;
		}

		throw std::exception();
	}

	return std::make_shared<DeclarationStatement>(DeclarationStatement(*s, exprs));
}

void MARECompiler::WriteStmt(const StmtPtr stmt_p)
{
	OutStream() << *stmt_p << std::endl;
}

void MARECompiler::WriteStmtList(const StmtList& stmts)
{
	for(auto it = stmts.begin(); it != stmts.end(); ++it)
	{
		WriteStmt(*it);
	}
}

void MARECompiler::OpenScope()
{
	_symTable.OpenScope();
}

void MARECompiler::CloseScope()
{
	_symTable.CloseScope();
}

void MARECompiler::WriteProgram(StmtList& decls1, StmtList& decls2, StmtList& decls3)
{
	OutStream() <<
		"#pragma once" << std::endl <<

		"#pragma warning(push)\n" <<

		//Ignore warnings about unused variables
		"#pragma warning(disable: 4189)\n" <<
		"#include <mare_rt.h>\n" <<
		"#include <cstdint>\n" <<
		"#include <array>\n" <<
		"#include <vector>\n\n" <<
		"extern \"C\" void " << LIB_EXPORT_STR << " " << MARE_PROGRAM_ENTRY << "(MareRT& runtime);\n\n" <<

		"extern \"C\" " << LIB_EXPORT_STR << " int32_t " << MARE_GET_PAGE_WIDTH_ENTRY << "()\n" <<
		"{\n" <<
		"\treturn " << GetMAREPageWidth() << ";\n" <<
		"}\n" <<

		"extern \"C\" " << LIB_EXPORT_STR << " int32_t " << MARE_GET_PAGE_HEIGHT_ENTRY << "()\n" <<
		"{\n" <<
		"\treturn " << GetMAREPageHeight() << ";\n" <<
		"}\n\n" <<

		"class " << MARE_PROG_CLASS_NAME << "\n" <<
		"{\n\t" <<
		"public:\n\t" <<
		MARE_PROG_CLASS_NAME << "(MareRT& rt) : _rt(rt) { }\n\t" <<
		"virtual ~" << MARE_PROG_CLASS_NAME << "() { }\n\n";


	WriteStmtList(decls1);

	OutStream() <<
		"\tvirtual void Run()\n\t" <<
		"{\n";

	WriteStmtList(decls2);

	OutStream() << "\t}\n";

	WriteStmtList(decls3);

	OutStream() << "\n\tprivate:\n\tMareRT _rt;\n};" << std::endl;

	OutStream() << "#pragma warning(pop)";
}

void MARECompiler::PrintMetrics(std::ostream& screen)
{
	screen << _m << std::endl;
}

std::ostream& operator<<(std::ostream& os, const MARECompiler::COMPILER_METRICS& m)
{
	os << "Compiler Metrics:" << std::endl;
	os << "Statements: " << m.StatementCount << std::endl;
	return os;
}
