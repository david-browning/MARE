#include "mare_stmt_func_decl.h"
#include "mare_stmt_param.h"
#include <queue>

FunctionDeclarationStatement::FunctionDeclarationStatement(const Symbol& funcSym,
																			  const ParamList& args, 
																			  const StmtList& stmts) :
	Statement(NOP_OPERATOR), _s(funcSym), _stmts(stmts), _args(args)
{
	
}

FunctionDeclarationStatement::FunctionDeclarationStatement(const FunctionDeclarationStatement& c):
	Statement(c), _s(c._s), _stmts(c._stmts), _args(c._args)
{

}

FunctionDeclarationStatement::FunctionDeclarationStatement(FunctionDeclarationStatement&& m) :
	Statement(m), _s(std::move(m._s))
{
	_stmts = std::move(m._stmts);
	_args = std::move(m._args);
}

FunctionDeclarationStatement::~FunctionDeclarationStatement()
{
}

void FunctionDeclarationStatement::_Print(std::ostream& os) const
{
	size_t templateIndex = 0;
	for(auto it = _args.rbegin(); it != _args.rend(); ++it)
	{
		if((*it)->IsTemplateType())
		{
			if(templateIndex == 0)
			{
				os << "\ttemplate<";
			}

			auto& arg = *it;
			if(arg->IsArrayType())
			{
				os << "size_t " << arg->GetSymbolName() + std::string("_COUNT");
			}
			else
			{
				throw invalid_type_exception();
			}

			if(it + 1 != _args.rend())
			{
				os << ", ";
			}

			templateIndex++;
		}
	}

	if(templateIndex > 0)
	{
		os << ">\n";
	}

	
	os << '\t';
	_s.PrintDeclaration(os);
	os << '(';

	for(auto it = _args.rbegin(); it != _args.rend(); ++it)
	{
		os << ParameterStatement(**it);

		if(it + 1 != _args.rend())
		{
			os << ", ";
		}
	}

	os << ")\n\t{\n";

	for(auto it = _stmts.begin(); it != _stmts.end(); ++it)
	{
		os << "\t\t" << **it << std::endl;
	}

	os << "\t}\n";
}
