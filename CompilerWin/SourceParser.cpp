/* A Bison parser, made by GNU Bison 2.7.  */

/* Skeleton implementation for Bison LALR(1) parsers in C++
   
      Copyright (C) 2002-2012 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* First part of user declarations.  */
/* Line 279 of lalr1.cc  */
#line 28 "SourceParser.y"


#include "SourceScanner.h"
#include <mare_expression.h>
#include <mare_symbol.h>
#include <mare_iatom.h>
#include <mare_literal.h>
#include <mare_compiler_functions.h>
#include <mare_stmt.h>

#undef yylex
#define yylex sourceScanner.yylex


/* Line 279 of lalr1.cc  */
#line 53 "C:\\Users\\david\\OneDrive\\Programming\\MARE\\CompilerWin\\SourceParser.cpp"


#include "SourceParser.h"

/* User implementation prologue.  */

/* Line 285 of lalr1.cc  */
#line 61 "C:\\Users\\david\\OneDrive\\Programming\\MARE\\CompilerWin\\SourceParser.cpp"


# ifndef YY_NULL
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULL nullptr
#  else
#   define YY_NULL 0
#  endif
# endif

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* FIXME: INFRINGES ON USER NAME SPACE */
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


/* Suppress unused-variable warnings by "using" E.  */
#define YYUSE(e) ((void) (e))

/* Enable debugging if requested.  */
#if YYDEBUG

/* A pseudo ostream that takes yydebug_ into account.  */
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Type, Value, Location)	\
do {							\
  if (yydebug_)						\
    {							\
      *yycdebug_ << Title << ' ';			\
      yy_symbol_print_ ((Type), (Value), (Location));	\
      *yycdebug_ << std::endl;				\
    }							\
} while (false)

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug_)				\
    yy_reduce_print_ (Rule);		\
} while (false)

# define YY_STACK_PRINT()		\
do {					\
  if (yydebug_)				\
    yystack_print_ ();			\
} while (false)

#else /* !YYDEBUG */

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Type, Value, Location) YYUSE(Type)
# define YY_REDUCE_PRINT(Rule)        static_cast<void>(0)
# define YY_STACK_PRINT()             static_cast<void>(0)

#endif /* !YYDEBUG */

#define yyerrok		(yyerrstatus_ = 0)
#define yyclearin	(yychar = yyempty_)

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)


namespace yy {
/* Line 353 of lalr1.cc  */
#line 156 "C:\\Users\\david\\OneDrive\\Programming\\MARE\\CompilerWin\\SourceParser.cpp"

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  SourceParser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              /* Fall through.  */
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  SourceParser::SourceParser (SourceScanner& sourceScanner_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      sourceScanner (sourceScanner_yyarg)
  {
  }

  SourceParser::~SourceParser ()
  {
  }

#if YYDEBUG
  /*--------------------------------.
  | Print this symbol on YYOUTPUT.  |
  `--------------------------------*/

  inline void
  SourceParser::yy_symbol_value_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yyvaluep);
    std::ostream& yyo = debug_stream ();
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    switch (yytype)
      {
         default:
	  break;
      }
  }


  void
  SourceParser::yy_symbol_print_ (int yytype,
			   const semantic_type* yyvaluep, const location_type* yylocationp)
  {
    *yycdebug_ << (yytype < yyntokens_ ? "token" : "nterm")
	       << ' ' << yytname_[yytype] << " ("
	       << *yylocationp << ": ";
    yy_symbol_value_print_ (yytype, yyvaluep, yylocationp);
    *yycdebug_ << ')';
  }
#endif

  void
  SourceParser::yydestruct_ (const char* yymsg,
			   int yytype, semantic_type* yyvaluep, location_type* yylocationp)
  {
    YYUSE (yylocationp);
    YYUSE (yymsg);
    YYUSE (yyvaluep);

    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

    switch (yytype)
      {
  
	default:
	  break;
      }
  }

  void
  SourceParser::yypop_ (unsigned int n)
  {
    yystate_stack_.pop (n);
    yysemantic_stack_.pop (n);
    yylocation_stack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  SourceParser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  SourceParser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  SourceParser::debug_level_type
  SourceParser::debug_level () const
  {
    return yydebug_;
  }

  void
  SourceParser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif

  inline bool
  SourceParser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  SourceParser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  SourceParser::parse ()
  {
    /// Lookahead and lookahead in internal form.
    int yychar = yyempty_;
    int yytoken = 0;

    // State.
    int yyn;
    int yylen = 0;
    int yystate = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// Semantic value of the lookahead.
    static semantic_type yyval_default;
    semantic_type yylval = yyval_default;
    /// Location of the lookahead.
    location_type yylloc;
    /// The locations where the error started and ended.
    location_type yyerror_range[3];

    /// $$.
    semantic_type yyval;
    /// @$.
    location_type yyloc;

    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stacks.  The initial state will be pushed in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystate_stack_ = state_stack_type (0);
    yysemantic_stack_ = semantic_stack_type (0);
    yylocation_stack_ = location_stack_type (0);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* New state.  */
  yynewstate:
    yystate_stack_.push (yystate);
    YYCDEBUG << "Entering state " << yystate << std::endl;

    /* Accept?  */
    if (yystate == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    /* Backup.  */
  yybackup:

    /* Try to take a decision without lookahead.  */
    yyn = yypact_[yystate];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    /* Read a lookahead token.  */
    if (yychar == yyempty_)
      {
        YYCDEBUG << "Reading a token: ";
        yychar = yylex (&yylval, &yylloc);
      }

    /* Convert token to internal form.  */
    if (yychar <= yyeof_)
      {
	yychar = yytoken = yyeof_;
	YYCDEBUG << "Now at end of input." << std::endl;
      }
    else
      {
	yytoken = yytranslate_ (yychar);
	YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
      }

    /* If the proper action on seeing token YYTOKEN is to reduce or to
       detect an error, take that action.  */
    yyn += yytoken;
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yytoken)
      goto yydefault;

    /* Reduce or error.  */
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
	if (yy_table_value_is_error_ (yyn))
	  goto yyerrlab;
	yyn = -yyn;
	goto yyreduce;
      }

    /* Shift the lookahead token.  */
    YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

    /* Discard the token being shifted.  */
    yychar = yyempty_;

    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yylloc);

    /* Count tokens shifted since error; after three, turn off error
       status.  */
    if (yyerrstatus_)
      --yyerrstatus_;

    yystate = yyn;
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystate];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    /* If YYLEN is nonzero, implement the default value of the action:
       `$$ = $1'.  Otherwise, use the top of the stack.

       Otherwise, the following line sets YYVAL to garbage.
       This behavior is undocumented and Bison
       users should not rely upon it.  */
    if (yylen)
      yyval = yysemantic_stack_[yylen - 1];
    else
      yyval = yysemantic_stack_[0];

    // Compute the default @$.
    {
      slice<location_type, location_stack_type> slice (yylocation_stack_, yylen);
      YYLLOC_DEFAULT (yyloc, slice, yylen);
    }

    // Perform the reduction.
    YY_REDUCE_PRINT (yyn);
    switch (yyn)
      {
          case 2:
/* Line 670 of lalr1.cc  */
#line 92 "SourceParser.y"
    {
	sourceScanner.GetCPtr()->WriteProgram(*(yysemantic_stack_[(8) - (1)].Statements), *(yysemantic_stack_[(8) - (4)].Statements), *(yysemantic_stack_[(8) - (7)].Statements));
}
    break;

  case 3:
/* Line 670 of lalr1.cc  */
#line 97 "SourceParser.y"
    {
	sourceScanner.GetCPtr()->OpenScope();
}
    break;

  case 4:
/* Line 670 of lalr1.cc  */
#line 102 "SourceParser.y"
    {
	sourceScanner.GetCPtr()->CloseScope();
}
    break;

  case 5:
/* Line 670 of lalr1.cc  */
#line 107 "SourceParser.y"
    {
	(yyval.Info) = (yysemantic_stack_[(1) - (1)].Info);
}
    break;

  case 6:
/* Line 670 of lalr1.cc  */
#line 112 "SourceParser.y"
    {
	auto tInfo = *(yysemantic_stack_[(2) - (2)].Info);
	tInfo.MakeConstant();
	(yyval.Info) = new IAtom(tInfo);
}
    break;

  case 7:
/* Line 670 of lalr1.cc  */
#line 119 "SourceParser.y"
    {
	(yyval.Info) = new IAtom(sourceScanner.GetCPtr()->MakeArrayType(*(yysemantic_stack_[(4) - (1)].Info), *(yysemantic_stack_[(4) - (3)].Lit)));
}
    break;

  case 8:
/* Line 670 of lalr1.cc  */
#line 124 "SourceParser.y"
    {
	(yyval.Statements) = new StmtList();
	(yyval.Statements)->push_back(*(yysemantic_stack_[(1) - (1)].Stmt));
}
    break;

  case 9:
/* Line 670 of lalr1.cc  */
#line 130 "SourceParser.y"
    {
	(yyval.Statements) = (yysemantic_stack_[(2) - (1)].Statements);
	(yyval.Statements)->push_back(*(yysemantic_stack_[(2) - (2)].Stmt));
}
    break;

  case 10:
/* Line 670 of lalr1.cc  */
#line 136 "SourceParser.y"
    {
	(yyval.Arguments) = (yysemantic_stack_[(3) - (2)].Arguments);
}
    break;

  case 11:
/* Line 670 of lalr1.cc  */
#line 141 "SourceParser.y"
    { 
	(yyval.Arguments) = new ExprList(); 
}
    break;

  case 12:
/* Line 670 of lalr1.cc  */
#line 146 "SourceParser.y"
    { 
	(yyval.Arguments) = (yysemantic_stack_[(1) - (1)].Arguments); 
}
    break;

  case 13:
/* Line 670 of lalr1.cc  */
#line 151 "SourceParser.y"
    { 
	(yyval.Arguments) = new ExprList();
	(yyval.Arguments)->push_back(*(yysemantic_stack_[(1) - (1)].Expr));
}
    break;

  case 14:
/* Line 670 of lalr1.cc  */
#line 157 "SourceParser.y"
    { 
	(yyval.Arguments)->push_back(*(yysemantic_stack_[(3) - (3)].Expr));
}
    break;

  case 15:
/* Line 670 of lalr1.cc  */
#line 162 "SourceParser.y"
    { 
	(yyval.Parameters) = (yysemantic_stack_[(3) - (2)].Parameters); 
}
    break;

  case 16:
/* Line 670 of lalr1.cc  */
#line 167 "SourceParser.y"
    { 
	//Params could be an empty list
	(yyval.Parameters) = new ParamList(); 
}
    break;

  case 17:
/* Line 670 of lalr1.cc  */
#line 173 "SourceParser.y"
    { 
	//Params could be a list of at least one symbol
	(yyval.Parameters) = (yysemantic_stack_[(1) - (1)].Parameters);
}
    break;

  case 18:
/* Line 670 of lalr1.cc  */
#line 179 "SourceParser.y"
    {
	(yyval.Parameters) = new ParamList();
	(yyval.Parameters)->push_back(std::make_shared<Symbol>(*sourceScanner.GetCPtr()->InsertSymbol(*(yysemantic_stack_[(2) - (2)].Str), *(yysemantic_stack_[(2) - (1)].Info))));
}
    break;

  case 19:
/* Line 670 of lalr1.cc  */
#line 185 "SourceParser.y"
    {
	(yyval.Parameters) = (yysemantic_stack_[(4) - (4)].Parameters);
	(yyval.Parameters)->push_back(std::make_shared<Symbol>(*sourceScanner.GetCPtr()->InsertSymbol(*(yysemantic_stack_[(4) - (2)].Str), *(yysemantic_stack_[(4) - (1)].Info))));
}
    break;

  case 20:
/* Line 670 of lalr1.cc  */
#line 191 "SourceParser.y"
    {
	(yyval.Info) = (yysemantic_stack_[(1) - (1)].Info);
}
    break;

  case 21:
/* Line 670 of lalr1.cc  */
#line 196 "SourceParser.y"
    {
	//Param type could be an array with an unknown size.
	(yyval.Info) = new IAtom(sourceScanner.GetCPtr()->MakeArrayType(*(yysemantic_stack_[(3) - (1)].Info), ZERO_LITERAL));
}
    break;

  case 22:
/* Line 670 of lalr1.cc  */
#line 202 "SourceParser.y"
    {
	(yyval.Statements) = new StmtList();
}
    break;

  case 23:
/* Line 670 of lalr1.cc  */
#line 207 "SourceParser.y"
    {
	(yyval.Statements) = (yysemantic_stack_[(1) - (1)].Statements);
}
    break;

  case 24:
/* Line 670 of lalr1.cc  */
#line 212 "SourceParser.y"
    {
	(yyval.Statements) = new StmtList();
	(yyval.Statements)->push_back(*(yysemantic_stack_[(1) - (1)].Stmt));
}
    break;

  case 25:
/* Line 670 of lalr1.cc  */
#line 218 "SourceParser.y"
    {
	(yyval.Statements)->push_back(*(yysemantic_stack_[(2) - (2)].Stmt));
}
    break;

  case 26:
/* Line 670 of lalr1.cc  */
#line 223 "SourceParser.y"
    {
	(yyval.Expr) = new Expression(*(yysemantic_stack_[(3) - (2)].Op));
	(yyval.Expr)->SetRight(*(yysemantic_stack_[(3) - (3)].Expr));
	(yyval.Expr)->SetLeft(*(yysemantic_stack_[(3) - (1)].Expr));
}
    break;

  case 27:
/* Line 670 of lalr1.cc  */
#line 230 "SourceParser.y"
    {
	(yyval.Expr) = new Expression(*(yysemantic_stack_[(3) - (2)].Op));
	(yyval.Expr)->SetRight(*(yysemantic_stack_[(3) - (3)].Expr));
	(yyval.Expr)->SetLeft(*(yysemantic_stack_[(3) - (1)].Expr));
}
    break;

  case 28:
/* Line 670 of lalr1.cc  */
#line 237 "SourceParser.y"
    {
	(yyval.Expr) = new Expression(*(yysemantic_stack_[(3) - (2)].Op));
	(yyval.Expr)->SetRight(*(yysemantic_stack_[(3) - (3)].Expr));
	(yyval.Expr)->SetLeft(*(yysemantic_stack_[(3) - (1)].Expr));
}
    break;

  case 29:
/* Line 670 of lalr1.cc  */
#line 244 "SourceParser.y"
    {
	(yyval.Expr) = new Expression(*(yysemantic_stack_[(3) - (2)].Op));
	(yyval.Expr)->SetRight(*(yysemantic_stack_[(3) - (3)].Expr));
	(yyval.Expr)->SetLeft(*(yysemantic_stack_[(3) - (1)].Expr));
}
    break;

  case 30:
/* Line 670 of lalr1.cc  */
#line 251 "SourceParser.y"
    {
	(yyval.Expr) = new Expression(*(yysemantic_stack_[(3) - (2)].Op));
	(yyval.Expr)->SetRight(*(yysemantic_stack_[(3) - (3)].Expr));
	(yyval.Expr)->SetLeft(*(yysemantic_stack_[(3) - (1)].Expr));
}
    break;

  case 31:
/* Line 670 of lalr1.cc  */
#line 258 "SourceParser.y"
    {
	(yyval.Expr) = (yysemantic_stack_[(1) - (1)].Expr);
}
    break;

  case 32:
/* Line 670 of lalr1.cc  */
#line 263 "SourceParser.y"
    {
	(yyval.Expr) = (yysemantic_stack_[(1) - (1)].Expr);
}
    break;

  case 33:
/* Line 670 of lalr1.cc  */
#line 268 "SourceParser.y"
    {
	(yyval.Expr) = (yysemantic_stack_[(1) - (1)].Expr);
}
    break;

  case 34:
/* Line 670 of lalr1.cc  */
#line 273 "SourceParser.y"
    {
	(yyval.Expr) = new Expression(*(yysemantic_stack_[(2) - (1)].Op));
	(yyval.Expr)->SetRight(*(yysemantic_stack_[(2) - (2)].Expr));
	(yyval.Expr)->SetLeft(ZERO_LITERAL);
}
    break;

  case 35:
/* Line 670 of lalr1.cc  */
#line 280 "SourceParser.y"
    {
	(yyval.Expr) = new Expression(sourceScanner.GetCPtr()->ToArrayCountExpression(*(yysemantic_stack_[(2) - (2)].Str)));
}
    break;

  case 36:
/* Line 670 of lalr1.cc  */
#line 285 "SourceParser.y"
    {
	(yyval.Expr) = new Expression(*(yysemantic_stack_[(1) - (1)].Lit));
}
    break;

  case 37:
/* Line 670 of lalr1.cc  */
#line 290 "SourceParser.y"
    {
	(yyval.Expr) = new Expression(*(yysemantic_stack_[(1) - (1)].Lit));
}
    break;

  case 38:
/* Line 670 of lalr1.cc  */
#line 295 "SourceParser.y"
    {
	(yyval.Expr) = new Expression(sourceScanner.GetCPtr()->ToCMExpression(*(yysemantic_stack_[(2) - (1)].Lit)));
}
    break;

  case 39:
/* Line 670 of lalr1.cc  */
#line 300 "SourceParser.y"
    {
	(yyval.Expr) = new Expression(sourceScanner.GetCPtr()->ToInchExpression(*(yysemantic_stack_[(2) - (1)].Lit)));
}
    break;

  case 40:
/* Line 670 of lalr1.cc  */
#line 305 "SourceParser.y"
    {
	(yyval.Expr) = new Expression(*sourceScanner.GetCPtr()->SymbolLookup(*(yysemantic_stack_[(1) - (1)].Str)));
}
    break;

  case 41:
/* Line 670 of lalr1.cc  */
#line 310 "SourceParser.y"
    {
	(yyval.Expr) = new Expression(sourceScanner.GetCPtr()->IndexExpression(*(yysemantic_stack_[(4) - (1)].Str), *(yysemantic_stack_[(4) - (3)].Expr)));
}
    break;

  case 42:
/* Line 670 of lalr1.cc  */
#line 315 "SourceParser.y"
    {
	(yyval.Expr) = (yysemantic_stack_[(3) - (2)].Expr);
}
    break;

  case 43:
/* Line 670 of lalr1.cc  */
#line 320 "SourceParser.y"
    {
	(yyval.Expr) = new Expression(NOP_OPERATOR);
	Expression sym = Expression(*sourceScanner.GetCPtr()->SymbolLookup(*(yysemantic_stack_[(2) - (1)].Str)));
	(yyval.Expr)->SetRight(sym);
	(yyval.Expr)->SetList(*(yysemantic_stack_[(2) - (2)].Arguments));
}
    break;

  case 44:
/* Line 670 of lalr1.cc  */
#line 328 "SourceParser.y"
    {
	(yyval.Expr) = new Expression(EQUALS_OPERATOR);
	(yyval.Expr)->SetLeft(*(yysemantic_stack_[(4) - (1)].Expr));
	(yyval.Expr)->SetRight(*(yysemantic_stack_[(4) - (4)].Expr));
}
    break;

  case 45:
/* Line 670 of lalr1.cc  */
#line 335 "SourceParser.y"
    {
	(yyval.Expr) = new Expression(LTE_OPERATOR);
	(yyval.Expr)->SetLeft(*(yysemantic_stack_[(5) - (1)].Expr));
	(yyval.Expr)->SetRight(*(yysemantic_stack_[(5) - (5)].Expr));
}
    break;

  case 46:
/* Line 670 of lalr1.cc  */
#line 342 "SourceParser.y"
    {
	(yyval.Expr) = new Expression(GTE_OPERATOR);
	(yyval.Expr)->SetLeft(*(yysemantic_stack_[(5) - (1)].Expr));
	(yyval.Expr)->SetRight(*(yysemantic_stack_[(5) - (5)].Expr));
}
    break;

  case 47:
/* Line 670 of lalr1.cc  */
#line 349 "SourceParser.y"
    {
	(yyval.Expr) = new Expression(LT_OPERATOR);
	(yyval.Expr)->SetLeft(*(yysemantic_stack_[(4) - (1)].Expr));
	(yyval.Expr)->SetRight(*(yysemantic_stack_[(4) - (4)].Expr));
}
    break;

  case 48:
/* Line 670 of lalr1.cc  */
#line 356 "SourceParser.y"
    {
	(yyval.Expr) = new Expression(GT_OPERATOR);
	(yyval.Expr)->SetLeft(*(yysemantic_stack_[(4) - (1)].Expr));
	(yyval.Expr)->SetRight(*(yysemantic_stack_[(4) - (4)].Expr));
}
    break;

  case 49:
/* Line 670 of lalr1.cc  */
#line 363 "SourceParser.y"
    {
	(yyval.Expr) = (yysemantic_stack_[(3) - (2)].Expr);
}
    break;

  case 50:
/* Line 670 of lalr1.cc  */
#line 368 "SourceParser.y"
    {
	(yyval.Expr) = new Expression(NOT_OPERATOR);
	(yyval.Expr)->SetLeft(*(yysemantic_stack_[(2) - (2)].Expr));
}
    break;

  case 51:
/* Line 670 of lalr1.cc  */
#line 374 "SourceParser.y"
    {
	(yyval.Expr) = new Expression(OR_OPERATOR);
	(yyval.Expr)->SetLeft(*(yysemantic_stack_[(3) - (1)].Expr));
	(yyval.Expr)->SetRight(*(yysemantic_stack_[(3) - (3)].Expr));
}
    break;

  case 52:
/* Line 670 of lalr1.cc  */
#line 381 "SourceParser.y"
    {
	(yyval.Expr) = (yysemantic_stack_[(1) - (1)].Expr);
}
    break;

  case 53:
/* Line 670 of lalr1.cc  */
#line 386 "SourceParser.y"
    {
	(yyval.Expr) = (yysemantic_stack_[(1) - (1)].Expr);
}
    break;

  case 54:
/* Line 670 of lalr1.cc  */
#line 391 "SourceParser.y"
    {
	(yyval.Expr) = new Expression(AND_OPERATOR);
	(yyval.Expr)->SetLeft(*(yysemantic_stack_[(3) - (1)].Expr));
	(yyval.Expr)->SetRight(*(yysemantic_stack_[(3) - (3)].Expr));
}
    break;

  case 55:
/* Line 670 of lalr1.cc  */
#line 398 "SourceParser.y"
    {
	(yyval.Stmt) = new StmtPtr(sourceScanner.GetCPtr()->DeclareVariableStmt(*(yysemantic_stack_[(5) - (2)].Str), *(yysemantic_stack_[(5) - (1)].Info), *(yysemantic_stack_[(5) - (4)].Expr)));
}
    break;

  case 56:
/* Line 670 of lalr1.cc  */
#line 403 "SourceParser.y"
    {
	(yyval.Stmt) = new StmtPtr(sourceScanner.GetCPtr()->DeclareVariableArrayStmt(*(yysemantic_stack_[(7) - (2)].Str), *(yysemantic_stack_[(7) - (1)].Info), *(yysemantic_stack_[(7) - (5)].Arguments)));
}
    break;

  case 57:
/* Line 670 of lalr1.cc  */
#line 408 "SourceParser.y"
    {
	(yyval.Stmt) = new StmtPtr(sourceScanner.GetCPtr()->DeclareFunctionStmt(*(yysemantic_stack_[(10) - (3)].Str), *(yysemantic_stack_[(10) - (2)].Info), *(yysemantic_stack_[(10) - (5)].Parameters), *(yysemantic_stack_[(10) - (7)].Statements)));
}
    break;

  case 58:
/* Line 670 of lalr1.cc  */
#line 413 "SourceParser.y"
    {
	(yyval.Stmt) = new StmtPtr(sourceScanner.GetCPtr()->DeclareCompoundTypeStmt(*(yysemantic_stack_[(9) - (2)].Str), *(yysemantic_stack_[(9) - (6)].Statements)));
}
    break;

  case 59:
/* Line 670 of lalr1.cc  */
#line 418 "SourceParser.y"
    {
	(yyval.Stmt) = new StmtPtr(sourceScanner.GetCPtr()->IfStmt(*(yysemantic_stack_[(10) - (3)].Expr), *(yysemantic_stack_[(10) - (7)].Statements)));
}
    break;

  case 60:
/* Line 670 of lalr1.cc  */
#line 424 "SourceParser.y"
    {
	(yyval.Stmt) = new StmtPtr(sourceScanner.GetCPtr()->IfStmt(*(yysemantic_stack_[(15) - (3)].Expr), *(yysemantic_stack_[(15) - (7)].Statements), *(yysemantic_stack_[(15) - (12)].Statements)));
}
    break;

  case 61:
/* Line 670 of lalr1.cc  */
#line 430 "SourceParser.y"
    {
	(yyval.Stmt) = new StmtPtr(sourceScanner.GetCPtr()->LoopUntilStmt(*(yysemantic_stack_[(10) - (3)].Expr), *(yysemantic_stack_[(10) - (7)].Statements)));
}
    break;

  case 62:
/* Line 670 of lalr1.cc  */
#line 435 "SourceParser.y"
    {
	(yyval.Stmt) = new StmtPtr(sourceScanner.GetCPtr()->CallFunctionStmt(*(yysemantic_stack_[(2) - (1)].Str), *(yysemantic_stack_[(2) - (2)].Arguments)));
}
    break;

  case 63:
/* Line 670 of lalr1.cc  */
#line 440 "SourceParser.y"
    {
	(yyval.Stmt) = new StmtPtr(sourceScanner.GetCPtr()->InlineCodeStmt(*(yysemantic_stack_[(2) - (2)].Lit)));
}
    break;

  case 64:
/* Line 670 of lalr1.cc  */
#line 445 "SourceParser.y"
    {
	(yyval.Stmt) = new StmtPtr(sourceScanner.GetCPtr()->AssignVarStmt(*(yysemantic_stack_[(3) - (1)].Str), *(yysemantic_stack_[(3) - (3)].Expr)));
}
    break;

  case 65:
/* Line 670 of lalr1.cc  */
#line 450 "SourceParser.y"
    {
	(yyval.Stmt) = new StmtPtr(sourceScanner.GetCPtr()->AssignVarStmt(*(yysemantic_stack_[(6) - (1)].Str), *(yysemantic_stack_[(6) - (6)].Expr), *(yysemantic_stack_[(6) - (3)].Expr)));
}
    break;

  case 66:
/* Line 670 of lalr1.cc  */
#line 455 "SourceParser.y"
    {
	(yyval.Stmt) = new StmtPtr(sourceScanner.GetCPtr()->BreakStmt());
}
    break;

  case 67:
/* Line 670 of lalr1.cc  */
#line 460 "SourceParser.y"
    {
	(yyval.Stmt) = new StmtPtr(sourceScanner.GetCPtr()->ReturnStmt(*(yysemantic_stack_[(3) - (2)].Expr)));
}
    break;

  case 68:
/* Line 670 of lalr1.cc  */
#line 465 "SourceParser.y"
    {
	(yyval.Stmt) = (yysemantic_stack_[(1) - (1)].Stmt);
}
    break;

  case 69:
/* Line 670 of lalr1.cc  */
#line 470 "SourceParser.y"
    {
	(yyval.Stmt) = (yysemantic_stack_[(1) - (1)].Stmt);
}
    break;

  case 70:
/* Line 670 of lalr1.cc  */
#line 475 "SourceParser.y"
    {
	(yyval.Stmt) = (yysemantic_stack_[(2) - (1)].Stmt);
}
    break;

  case 71:
/* Line 670 of lalr1.cc  */
#line 480 "SourceParser.y"
    {
	(yyval.Stmt) = (yysemantic_stack_[(1) - (1)].Stmt);
}
    break;

  case 72:
/* Line 670 of lalr1.cc  */
#line 485 "SourceParser.y"
    {
	(yyval.Stmt) = (yysemantic_stack_[(2) - (1)].Stmt);
}
    break;

  case 73:
/* Line 670 of lalr1.cc  */
#line 490 "SourceParser.y"
    {
	(yyval.Stmt) = (yysemantic_stack_[(2) - (1)].Stmt);
}
    break;


/* Line 670 of lalr1.cc  */
#line 1084 "C:\\Users\\david\\OneDrive\\Programming\\MARE\\CompilerWin\\SourceParser.cpp"
      default:
        break;
      }

    /* User semantic actions sometimes alter yychar, and that requires
       that yytoken be updated with the new translation.  We take the
       approach of translating immediately before every use of yytoken.
       One alternative is translating here after every semantic action,
       but that translation would be missed if the semantic action
       invokes YYABORT, YYACCEPT, or YYERROR immediately after altering
       yychar.  In the case of YYABORT or YYACCEPT, an incorrect
       destructor might then be invoked immediately.  In the case of
       YYERROR, subsequent parser actions might lead to an incorrect
       destructor call or verbose syntax error message before the
       lookahead is translated.  */
    YY_SYMBOL_PRINT ("-> $$ =", yyr1_[yyn], &yyval, &yyloc);

    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();

    yysemantic_stack_.push (yyval);
    yylocation_stack_.push (yyloc);

    /* Shift the result of the reduction.  */
    yyn = yyr1_[yyn];
    yystate = yypgoto_[yyn - yyntokens_] + yystate_stack_[0];
    if (0 <= yystate && yystate <= yylast_
	&& yycheck_[yystate] == yystate_stack_[0])
      yystate = yytable_[yystate];
    else
      yystate = yydefgoto_[yyn - yyntokens_];
    goto yynewstate;

  /*------------------------------------.
  | yyerrlab -- here on detecting error |
  `------------------------------------*/
  yyerrlab:
    /* Make sure we have latest lookahead translation.  See comments at
       user semantic actions for why this is necessary.  */
    yytoken = yytranslate_ (yychar);

    /* If not already recovering from an error, report this error.  */
    if (!yyerrstatus_)
      {
	++yynerrs_;
	if (yychar == yyempty_)
	  yytoken = yyempty_;
	error (yylloc, yysyntax_error_ (yystate, yytoken));
      }

    yyerror_range[1] = yylloc;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */
        if (yychar <= yyeof_)
          {
            /* Return failure if at end of input.  */
            if (yychar == yyeof_)
              YYABORT;
          }
        else
          {
            yydestruct_ ("Error: discarding", yytoken, &yylval, &yylloc);
            yychar = yyempty_;
          }
      }

    /* Else will try to reuse lookahead token after shifting the error
       token.  */
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;

    yyerror_range[1] = yylocation_stack_[yylen - 1];
    /* Do not reclaim the symbols of the rule which action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    yystate = yystate_stack_[0];
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;	/* Each real token shifted decrements this.  */

    for (;;)
      {
	yyn = yypact_[yystate];
	if (!yy_pact_value_is_default_ (yyn))
	{
	  yyn += yyterror_;
	  if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
	    {
	      yyn = yytable_[yyn];
	      if (0 < yyn)
		break;
	    }
	}

	/* Pop the current state because it cannot handle the error token.  */
	if (yystate_stack_.height () == 1)
	  YYABORT;

	yyerror_range[1] = yylocation_stack_[0];
	yydestruct_ ("Error: popping",
		     yystos_[yystate],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);
	yypop_ ();
	yystate = yystate_stack_[0];
	YY_STACK_PRINT ();
      }

    yyerror_range[2] = yylloc;
    // Using YYLLOC is tempting, but would change the location of
    // the lookahead.  YYLOC is available though.
    YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
    yysemantic_stack_.push (yylval);
    yylocation_stack_.push (yyloc);

    /* Shift the error token.  */
    YY_SYMBOL_PRINT ("Shifting", yystos_[yyn],
		     &yysemantic_stack_[0], &yylocation_stack_[0]);

    yystate = yyn;
    goto yynewstate;

    /* Accept.  */
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    /* Abort.  */
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (yychar != yyempty_)
      {
        /* Make sure we have latest lookahead translation.  See comments
           at user semantic actions for why this is necessary.  */
        yytoken = yytranslate_ (yychar);
        yydestruct_ ("Cleanup: discarding lookahead", yytoken, &yylval,
                     &yylloc);
      }

    /* Do not reclaim the symbols of the rule which action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystate_stack_.height ())
      {
        yydestruct_ ("Cleanup: popping",
                     yystos_[yystate_stack_[0]],
                     &yysemantic_stack_[0],
                     &yylocation_stack_[0]);
        yypop_ ();
      }

    return yyresult;
    }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (yychar != yyempty_)
          {
            /* Make sure we have latest lookahead translation.  See
               comments at user semantic actions for why this is
               necessary.  */
            yytoken = yytranslate_ (yychar);
            yydestruct_ (YY_NULL, yytoken, &yylval, &yylloc);
          }

        while (1 < yystate_stack_.height ())
          {
            yydestruct_ (YY_NULL,
                         yystos_[yystate_stack_[0]],
                         &yysemantic_stack_[0],
                         &yylocation_stack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  // Generate an error message.
  std::string
  SourceParser::yysyntax_error_ (int yystate, int yytoken)
  {
    std::string yyres;
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yytoken) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yychar.
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (yytoken != yyempty_)
      {
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            /* Stay within bounds of both yycheck and yytname.  */
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULL;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
  const signed char SourceParser::yypact_ninf_ = -108;
  const short int
  SourceParser::yypact_[] =
  {
        60,   -22,   -22,   -11,    33,    67,    28,    65,    60,  -108,
      40,  -108,    76,    79,  -108,   114,   144,  -108,  -108,   103,
     139,     9,   129,   156,  -108,  -108,    59,    59,    98,   143,
      77,  -108,    88,    57,   161,  -108,  -108,    59,   108,   173,
     184,   179,   106,   117,  -108,  -108,  -108,   186,   187,   188,
    -108,   -15,   189,    60,   104,   120,    90,  -108,  -108,    59,
      59,  -108,  -108,  -108,  -108,    59,    59,    59,    59,    59,
      61,  -108,     2,  -108,     2,    59,    59,  -108,   166,  -108,
    -108,  -108,  -108,   183,  -108,   185,  -108,   153,   129,  -108,
      59,   194,  -108,   190,   197,    11,   161,   161,  -108,  -108,
    -108,  -108,    92,    92,    20,  -108,   176,    10,    12,   152,
     120,    60,     3,  -108,   200,   129,   195,   120,  -108,  -108,
    -108,     7,   192,  -108,   159,    92,   201,    92,   202,   191,
     206,  -108,   -15,   172,   205,  -108,    59,    50,    54,  -108,
    -108,  -108,  -108,    59,  -108,  -108,   182,  -108,   120,    59,
     120,    59,   120,   129,   129,   120,  -108,   120,   120,   129,
     129,   134,   175,   208,   180,   177,  -108,  -108,  -108,   129,
     129,   181,   193,  -108
  };

  /* YYDEFACT[S] -- default reduction number in state S.  Performed when
     YYTABLE doesn't specify something else to do.  Zero means the
     default is an error.  */
  const unsigned char
  SourceParser::yydefact_[] =
  {
        22,     0,     0,     0,     5,     0,     0,     0,    23,    24,
       0,     6,     0,     0,     1,     0,     0,    25,     3,     0,
       0,     0,     0,     0,     3,     7,     0,     0,     0,     0,
      40,    36,    37,     0,    31,    32,    33,     0,     0,     0,
       0,     0,     0,     0,    71,    68,    69,     0,     0,     0,
       8,    16,     0,    22,     0,    13,     0,    34,    35,    11,
       0,    43,    38,    39,    55,     0,     0,     0,     0,     0,
       0,    63,     0,    66,     0,     0,     0,    62,     0,     9,
      70,    72,    73,     5,    20,     0,    17,     0,     0,     4,
       0,     0,    42,     0,    12,     0,    26,    27,    29,    28,
      30,    67,     0,     0,     0,    52,    53,     0,     0,     0,
      64,    22,     0,    15,    18,     4,     0,    14,    56,    10,
      41,     0,     0,    50,     0,     0,     0,     0,     0,     0,
       0,    21,     0,     0,     0,    49,     0,     0,     0,    54,
       3,    51,     3,     0,     2,    19,     0,    58,    44,     0,
      47,     0,    48,     0,     0,    65,    57,    45,    46,     4,
       4,     0,     0,     0,     0,     0,     3,    59,    61,     0,
       4,     0,     0,    60
  };

  /* YYPGOTO[NTERM-NUM].  */
  const short int
  SourceParser::yypgoto_[] =
  {
      -108,  -108,   -24,  -107,     0,   -85,   174,  -108,   160,  -108,
    -108,    89,  -108,   -47,  -108,   -16,   110,   118,   196,   -88,
    -108,   146,     4,  -108,  -108,  -108,  -108,  -108,   -36
  };

  /* YYDEFGOTO[NTERM-NUM].  */
  const signed char
  SourceParser::yydefgoto_[] =
  {
        -1,     5,    23,   116,     6,    43,    61,    93,    54,    52,
      85,    86,    87,     7,     8,   104,    34,    35,    36,   105,
     106,   107,    44,    45,    46,    47,    48,    49,    50
  };

  /* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule which
     number is the opposite.  If YYTABLE_NINF_, syntax error.  */
  const signed char SourceParser::yytable_ninf_ = -1;
  const unsigned char
  SourceParser::yytable_[] =
  {
        53,    10,    11,   115,     9,    33,    89,    79,   133,     2,
      55,    56,    17,   102,   122,   123,     2,   131,    26,    92,
      27,    70,   126,    28,   128,   120,     4,    65,    66,   103,
      28,    65,    66,    83,    12,    29,   127,   139,   127,   141,
      65,    66,    29,    55,    95,   124,    13,    30,    31,    32,
      20,    84,   161,   162,    30,    31,    32,     9,   124,   109,
     110,    27,    64,   171,   130,    27,   101,    14,   159,   160,
      27,    28,   149,    15,   117,    28,   151,    65,    66,    79,
      28,    65,    66,    29,   170,    18,   121,    29,    59,     1,
      60,     2,    29,    16,     3,    30,    31,    32,    19,    30,
      31,    32,    92,   102,    30,    31,    32,    90,     4,    27,
      65,    66,    24,    28,    91,     9,   153,    59,   154,    75,
     148,   150,   152,    79,    79,    29,    20,   155,    76,    62,
      63,    29,    84,   157,    79,   158,    21,    30,    31,    32,
      65,    66,   169,    30,    31,    32,     1,    37,     2,    38,
      22,     3,    39,    25,    78,    71,    40,    41,     1,    37,
       2,    38,    42,     3,    39,     4,   129,    51,    40,    41,
     163,   164,    65,    66,    42,    96,    97,     4,    67,    68,
      69,   136,   137,   138,    72,    98,    99,   100,    58,    73,
      74,    80,    81,    82,   111,    88,   112,   113,   114,   118,
      90,   125,   119,   132,   135,   134,   144,   140,   142,   146,
     147,   156,   165,   143,   166,   167,    77,   168,   172,    94,
     108,   145,     0,     0,    57,     0,     0,     0,   173
  };

  /* YYCHECK.  */
  const short int
  SourceParser::yycheck_[] =
  {
        24,     1,     2,    88,     0,    21,    53,    43,   115,    31,
      26,    27,     8,    11,   102,   103,    31,    14,     9,    12,
      11,    37,    12,    21,    12,    14,    48,    20,    21,    27,
      21,    20,    21,    48,    45,    33,    26,   125,    26,   127,
      20,    21,    33,    59,    60,    38,    13,    45,    46,    47,
      47,    51,   159,   160,    45,    46,    47,    53,    38,    75,
      76,    11,     5,   170,   111,    11,     5,     0,   153,   154,
      11,    21,    22,    45,    90,    21,    22,    20,    21,   115,
      21,    20,    21,    33,   169,    45,   102,    33,    11,    29,
      13,    31,    33,    28,    34,    45,    46,    47,    22,    45,
      46,    47,    12,    11,    45,    46,    47,     3,    48,    11,
      20,    21,     9,    21,    10,   111,   140,    11,   142,    13,
     136,   137,   138,   159,   160,    33,    47,   143,    22,    41,
      42,    33,   132,   149,   170,   151,    22,    45,    46,    47,
      20,    21,   166,    45,    46,    47,    29,    30,    31,    32,
       6,    34,    35,    14,    37,    47,    39,    40,    29,    30,
      31,    32,    45,    34,    35,    48,    14,    11,    39,    40,
      36,    37,    20,    21,    45,    65,    66,    48,    17,    18,
      19,    22,    23,    24,    11,    67,    68,    69,    45,     5,
      11,     5,     5,     5,    28,     6,    13,    12,    45,     5,
       3,    25,    12,     3,    12,    10,     0,     6,     6,    37,
       5,    29,    37,    22,     6,    35,    42,    40,    37,    59,
      74,   132,    -1,    -1,    28,    -1,    -1,    -1,    35
  };

  /* STOS_[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
  const unsigned char
  SourceParser::yystos_[] =
  {
         0,    29,    31,    34,    48,    50,    53,    62,    63,    71,
      53,    53,    45,    13,     0,    45,    28,    71,    45,    22,
      47,    22,     6,    51,     9,    14,     9,    11,    21,    33,
      45,    46,    47,    64,    65,    66,    67,    30,    32,    35,
      39,    40,    45,    54,    71,    72,    73,    74,    75,    76,
      77,    11,    58,    51,    57,    64,    64,    67,    45,    11,
      13,    55,    41,    42,     5,    20,    21,    17,    18,    19,
      64,    47,    11,     5,    11,    13,    22,    55,    37,    77,
       5,     5,     5,    48,    53,    59,    60,    61,     6,    62,
       3,    10,    12,    56,    57,    64,    65,    65,    66,    66,
      66,     5,    11,    27,    64,    68,    69,    70,    70,    64,
      64,    28,    13,    12,    45,    54,    52,    64,     5,    12,
      14,    64,    68,    68,    38,    25,    12,    26,    12,    14,
      62,    14,     3,    52,    10,    12,    22,    23,    24,    68,
       6,    68,     6,    22,     0,    60,    37,     5,    64,    22,
      64,    22,    64,    51,    51,    64,    29,    64,    64,    54,
      54,    52,    52,    36,    37,    37,     6,    35,    40,    51,
      54,    52,    37,    35
  };

#if YYDEBUG
  /* TOKEN_NUMBER_[YYLEX-NUM] -- Internal symbol number corresponding
     to YYLEX-NUM.  */
  const unsigned short int
  SourceParser::yytoken_number_[] =
  {
         0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303
  };
#endif

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
  const unsigned char
  SourceParser::yyr1_[] =
  {
         0,    49,    50,    51,    52,    53,    53,    53,    54,    54,
      55,    56,    56,    57,    57,    58,    59,    59,    60,    60,
      61,    61,    62,    62,    63,    63,    64,    64,    65,    65,
      65,    64,    65,    66,    66,    67,    67,    67,    67,    67,
      67,    67,    67,    67,    68,    68,    68,    68,    68,    68,
      69,    69,    69,    70,    70,    71,    71,    71,    71,    72,
      72,    73,    74,    75,    76,    76,    77,    77,    77,    77,
      77,    77,    77,    77
  };

  /* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
  const unsigned char
  SourceParser::yyr2_[] =
  {
         0,     2,     8,     0,     0,     1,     2,     4,     1,     2,
       3,     0,     1,     1,     3,     3,     0,     1,     2,     4,
       1,     3,     0,     1,     1,     2,     3,     3,     3,     3,
       3,     1,     1,     1,     2,     2,     1,     1,     2,     2,
       1,     4,     3,     2,     4,     5,     5,     4,     4,     3,
       2,     3,     1,     1,     3,     5,     7,    10,     9,    10,
      15,    10,     2,     2,     3,     6,     2,     3,     1,     1,
       2,     1,     2,     2
  };


  /* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
     First, the terminals, then, starting at \a yyntokens_, nonterminals.  */
  const char*
  const SourceParser::yytname_[] =
  {
    "\"End of file\"", "error", "$undefined", "\",\"", "\".\"", "\";\"",
  "\":\"", "\"\\\\\"", "\"^\"", "\"{\"", "\"}\"", "\"(\"", "\")\"",
  "\"[\"", "\"]\"", "\"++\"", "\"--\"", "\"*\"", "\"/\"", "\"%\"", "\"+\"",
  "\"-\"", "\"=\"", "\"<\"", "\">\"", "\"and\"", "\"or\"", "\"not\"",
  "\"program\"", "\"function\"", "\"return\"", "\"const\"", "\"__code\"",
  "\"count\"", "\"compound_t\"", "\"if\"", "\"else\"", "\"end\"", "\"is\"",
  "\"break\"", "\"until\"", "\"cm\"", "\"inch\"", "\"pixel\"", "SYMBOL",
  "ID", "CONSTANT", "LITERAL", "TYPE", "$accept", "program", "code_start",
  "code_end", "type_info", "stmt_list", "arguments", "args", "arglist",
  "parameters", "params", "param_list", "param_type", "decls",
  "declaration_list", "expr", "factor", "unary", "atom", "relation",
  "bool_op", "bool", "declaration", "if_stmt", "loop_stmt",
  "function_call", "inline_code", "assignment", "stmt", YY_NULL
  };

#if YYDEBUG
  /* YYRHS -- A `-1'-separated list of the rules' RHS.  */
  const SourceParser::rhs_number_type
  SourceParser::yyrhs_[] =
  {
        50,     0,    -1,    62,    28,     6,    54,    37,    28,    62,
       0,    -1,    -1,    -1,    48,    -1,    31,    53,    -1,    48,
      13,    47,    14,    -1,    77,    -1,    54,    77,    -1,    11,
      56,    12,    -1,    -1,    57,    -1,    64,    -1,    57,     3,
      64,    -1,    11,    59,    12,    -1,    -1,    60,    -1,    61,
      45,    -1,    61,    45,     3,    60,    -1,    53,    -1,    48,
      13,    14,    -1,    -1,    63,    -1,    71,    -1,    63,    71,
      -1,    64,    20,    65,    -1,    64,    21,    65,    -1,    65,
      18,    66,    -1,    65,    17,    66,    -1,    65,    19,    66,
      -1,    65,    -1,    66,    -1,    67,    -1,    21,    67,    -1,
      33,    45,    -1,    46,    -1,    47,    -1,    47,    41,    -1,
      47,    42,    -1,    45,    -1,    45,    13,    64,    14,    -1,
      11,    64,    12,    -1,    45,    55,    -1,    64,    38,    22,
      64,    -1,    64,    38,    23,    22,    64,    -1,    64,    38,
      24,    22,    64,    -1,    64,    38,    23,    64,    -1,    64,
      38,    24,    64,    -1,    11,    68,    12,    -1,    27,    68,
      -1,    70,    26,    68,    -1,    68,    -1,    69,    -1,    69,
      25,    68,    -1,    53,    45,    22,    64,     5,    -1,    53,
      45,    22,     9,    57,    10,     5,    -1,    29,    53,    45,
      51,    58,     6,    54,    52,    37,    29,    -1,    34,    45,
      22,     9,    51,    62,    52,    10,     5,    -1,    35,    11,
      70,    12,     6,    51,    54,    52,    37,    35,    -1,    35,
      11,    70,    12,     6,    51,    54,    52,    36,     6,    51,
      54,    52,    37,    35,    -1,    40,    11,    70,    12,     6,
      51,    54,    52,    37,    40,    -1,    45,    55,    -1,    32,
      47,    -1,    45,    22,    64,    -1,    45,    13,    64,    14,
      22,    64,    -1,    39,     5,    -1,    30,    64,     5,    -1,
      72,    -1,    73,    -1,    74,     5,    -1,    71,    -1,    75,
       5,    -1,    76,     5,    -1
  };

  /* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
     YYRHS.  */
  const unsigned short int
  SourceParser::yyprhs_[] =
  {
         0,     0,     3,    12,    13,    14,    16,    19,    24,    26,
      29,    33,    34,    36,    38,    42,    46,    47,    49,    52,
      57,    59,    63,    64,    66,    68,    71,    75,    79,    83,
      87,    91,    93,    95,    97,   100,   103,   105,   107,   110,
     113,   115,   120,   124,   127,   132,   138,   144,   149,   154,
     158,   161,   165,   167,   169,   173,   179,   187,   198,   208,
     219,   235,   246,   249,   252,   256,   263,   266,   270,   272,
     274,   277,   279,   282
  };

  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
  const unsigned short int
  SourceParser::yyrline_[] =
  {
         0,    89,    89,    97,   102,   106,   111,   118,   123,   129,
     135,   141,   145,   150,   156,   161,   167,   172,   178,   184,
     190,   195,   202,   206,   211,   217,   222,   229,   236,   243,
     250,   257,   262,   267,   272,   279,   284,   289,   294,   299,
     304,   309,   314,   319,   327,   334,   341,   348,   355,   362,
     367,   373,   380,   385,   390,   397,   402,   407,   412,   417,
     422,   428,   434,   439,   444,   449,   454,   459,   464,   469,
     474,   479,   484,   489
  };

  // Print the state stack on the debug stream.
  void
  SourceParser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (state_stack_type::const_iterator i = yystate_stack_.begin ();
	 i != yystate_stack_.end (); ++i)
      *yycdebug_ << ' ' << *i;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  SourceParser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    /* Print the symbols being reduced, and their result.  */
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
	       << " (line " << yylno << "):" << std::endl;
    /* The symbols being reduced.  */
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
		       yyrhs_[yyprhs_[yyrule] + yyi],
		       &(yysemantic_stack_[(yynrhs) - (yyi + 1)]),
		       &(yylocation_stack_[(yynrhs) - (yyi + 1)]));
  }
#endif // YYDEBUG

  /* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
  SourceParser::token_number_type
  SourceParser::yytranslate_ (int t)
  {
    static
    const token_number_type
    translate_table[] =
    {
           0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48
    };
    if ((unsigned int) t <= yyuser_token_number_max_)
      return translate_table[t];
    else
      return yyundef_token_;
  }

  const int SourceParser::yyeof_ = 0;
  const int SourceParser::yylast_ = 228;
  const int SourceParser::yynnts_ = 29;
  const int SourceParser::yyempty_ = -2;
  const int SourceParser::yyfinal_ = 14;
  const int SourceParser::yyterror_ = 1;
  const int SourceParser::yyerrcode_ = 256;
  const int SourceParser::yyntokens_ = 49;

  const unsigned int SourceParser::yyuser_token_number_max_ = 303;
  const SourceParser::token_number_type SourceParser::yyundef_token_ = 2;


} // yy
/* Line 1141 of lalr1.cc  */
#line 1756 "C:\\Users\\david\\OneDrive\\Programming\\MARE\\CompilerWin\\SourceParser.cpp"
/* Line 1142 of lalr1.cc  */
#line 494 "SourceParser.y"


void yy::SourceParser::error(const location_type& l, const std::string &m)
{
	std::cerr << m << " at " << l << std::endl;
}
