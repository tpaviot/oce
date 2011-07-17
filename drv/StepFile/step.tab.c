
/*  A Bison parser, made from /dn43/OCCT/tmp/results_31.05.2011/occt/release-sources-20110531/src/StepFile/step.yacc
 by  GNU Bison version 1.25
  */

#define YYBISON 1  /* Identify Bison output.  */

#define yyparse stepparse
#define yylex steplex
#define yyerror steperror
#define yylval steplval
#define yychar stepchar
#define yydebug stepdebug
#define yynerrs stepnerrs
#define	STEP	258
#define	HEADER	259
#define	ENDSEC	260
#define	DATA	261
#define	ENDSTEP	262
#define	SCOPE	263
#define	ENDSCOPE	264
#define	ENTITY	265
#define	TYPE	266
#define	INTEGER	267
#define	FLOAT	268
#define	IDENT	269
#define	TEXT	270
#define	NONDEF	271
#define	ENUM	272
#define	HEXA	273
#define	QUID	274

#line 3 "/dn43/OCCT/tmp/results_31.05.2011/occt/release-sources-20110531/src/StepFile/step.yacc"

#include "recfile.ph"		/* definitions des types d'arguments */
#include "recfile.pc"		/* la-dedans, tout y est */
/*
#define stepparse STEPparse
#define steplex STEPlex
#define stepwrap STEPwrap
#define steprestart STEPrestart
#define steplex STEPlex
#define steplval STEPlval
#define stepval STEPval
#define stepchar STEPchar
#define stepdebug STEPdebug
#define stepnerrs STEPnerrs
#define steperror STEPerror
*/
#define stepclearin yychar = -1
#define steperrok yyerrflag = 0

/*
#define stepin STEPin
#define yyerrflag STEPerrflag
#define yyerrstatus STEPerrflag
*/

/* ABV 19.12.00: merging porting modifications by POP (for WNT, AIX) */
#if defined(WNT) && !defined(MSDOS)
#define MSDOS WNT
#endif
#if defined(_AIX)
#include <malloc.h>
#define alloca malloc
#endif

#ifndef YYSTYPE
#define YYSTYPE int
#endif
#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		85
#define	YYFLAG		-32768
#define	YYNTBASE	27

#define YYTRANSLATE(x) ((unsigned)(x) <= 274 ? yytranslate[x] : 53)

static const char yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,    20,     2,     2,     2,     2,     2,     2,     2,    22,
    23,     2,     2,    24,     2,     2,    26,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,    21,     2,
    25,     2,     2,     2,     2,     2,     2,     2,     2,     2,
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
     2,     2,     2,     2,     2,     1,     2,     3,     4,     5,
     6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
    16,    17,    18,    19
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     2,     5,     7,    10,    19,    27,    34,    36,    38,
    40,    42,    45,    49,    51,    53,    55,    57,    59,    62,
    64,    66,    68,    70,    73,    77,    80,    82,    86,    89,
    91,    94,    99,   107,   114,   116,   119,   123,   126,   130,
   132,   134,   136,   140,   142,   144,   149,   151
};

static const short yyrhs[] = {    20,
     0,    27,    20,     0,     7,     0,     7,    27,     0,     3,
     4,    33,     5,    35,    42,     5,    28,     0,     3,     4,
     5,    35,    42,     5,     7,     0,     3,     4,     5,    35,
    42,     1,     0,    29,     0,    30,     0,    31,     0,    34,
     0,    33,    34,     0,    52,    40,    21,     0,     1,     0,
     6,     0,    14,     0,    19,     0,    40,     0,    37,    40,
     0,     1,     0,    11,     0,    22,     0,    23,     0,    38,
    39,     0,    38,    41,    39,     0,    38,     1,     0,    36,
     0,    41,    24,    36,     0,    41,     1,     0,    43,     0,
    42,    43,     0,    51,    25,    45,    21,     0,    51,    25,
    46,    42,    50,    45,    21,     0,    51,    25,    46,    50,
    45,    21,     0,     1,     0,    52,    40,     0,    44,    52,
    40,     0,    52,    40,     0,    22,    44,    23,     0,     8,
     0,    14,     0,    47,     0,    48,    24,    47,     0,    26,
     0,     9,     0,     9,    49,    48,    26,     0,    10,     0,
    11,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
    41,    42,    43,    44,    45,    46,    47,    48,    48,    48,
    51,    52,    54,    55,    57,    60,    61,    62,    63,    64,
    68,    71,    74,    79,    80,    81,    83,    84,    85,    87,
    88,    90,    91,    92,    93,    95,    96,    98,    99,   101,
   104,   107,   108,   110,   113,   115,   120,   123
};
#endif


#if YYDEBUG != 0 || defined (YYERROR_VERBOSE)

static const char * const yytname[] = {   "$","error","$undefined.","STEP","HEADER",
"ENDSEC","DATA","ENDSTEP","SCOPE","ENDSCOPE","ENTITY","TYPE","INTEGER","FLOAT",
"IDENT","TEXT","NONDEF","ENUM","HEXA","QUID","' '","';'","'('","')'","','","'='",
"'/'","finvide","finstep","stepf1","stepf2","stepf3","stepf","headl","headent",
"endhead","unarg","listype","deblist","finlist","listarg","arglist","model",
"bloc","plex","unent","debscop","unid","export","debexp","finscop","entlab",
"enttype", NULL
};
#endif

static const short yyr1[] = {     0,
    27,    27,    28,    28,    29,    30,    31,    32,    32,    32,
    33,    33,    34,    34,    35,    36,    36,    36,    36,    36,
    37,    38,    39,    40,    40,    40,    41,    41,    41,    42,
    42,    43,    43,    43,    43,    44,    44,    45,    45,    46,
    47,    48,    48,    49,    50,    50,    51,    52
};

static const short yyr2[] = {     0,
     1,     2,     1,     2,     8,     7,     6,     1,     1,     1,
     1,     2,     3,     1,     1,     1,     1,     1,     2,     1,
     1,     1,     1,     2,     3,     2,     1,     3,     2,     1,
     2,     4,     7,     6,     1,     2,     3,     2,     3,     1,
     1,     1,     3,     1,     1,     4,     1,     1
};

static const short yydefact[] = {     0,
     0,     8,     9,    10,     0,    14,     0,    48,     0,    11,
     0,    15,     0,     0,    12,    22,     0,     0,    35,    47,
     0,    30,     0,     0,    20,    21,    16,    17,    23,    27,
     0,    24,    18,     0,    13,    35,     0,    31,     0,     0,
    19,    29,     0,    25,     6,    40,     0,     0,     0,     0,
     0,    20,    28,     0,     0,    32,    45,     0,     0,    38,
     3,     5,    39,     0,    36,    44,     0,     0,     0,     1,
     4,    37,    41,    42,     0,     0,    34,     2,     0,    46,
    33,    43,     0,     0,     0
};

static const short yydefgoto[] = {    71,
    62,     2,     3,     4,    83,     9,    10,    13,    30,    31,
    17,    32,    33,    34,    21,    22,    54,    48,    49,    74,
    75,    67,    59,    23,    50
};

static const short yypact[] = {     9,
    26,-32768,-32768,-32768,    13,-32768,    11,-32768,    36,-32768,
    10,-32768,    32,    11,-32768,-32768,    12,    17,-32768,-32768,
    50,-32768,    20,    32,     4,-32768,-32768,-32768,-32768,-32768,
    10,-32768,-32768,     5,-32768,    48,    55,-32768,    -1,    51,
-32768,-32768,    35,-32768,-32768,-32768,    52,    43,    57,    10,
    58,-32768,-32768,    -7,    10,-32768,    44,    57,    -3,-32768,
    49,-32768,-32768,    10,-32768,-32768,    59,    -3,    53,-32768,
    56,-32768,-32768,-32768,   -15,    54,-32768,-32768,    59,-32768,
-32768,-32768,    71,    72,-32768
};

static const short yypgoto[] = {-32768,
-32768,-32768,-32768,-32768,-32768,-32768,    68,    64,    37,-32768,
-32768,    45,   -11,-32768,   -22,   -18,-32768,     0,-32768,     2,
-32768,-32768,    24,-32768,    -4
};


#define	YYLAST		82


static const short yytable[] = {    18,
    11,    40,    38,     8,    11,    42,    46,     8,    79,     8,
    80,     1,    25,     6,   -26,    63,    12,     7,    47,    41,
    47,    38,    26,     8,   -26,    27,    58,    29,    43,     5,
    28,    16,    19,    16,    29,    52,     6,    35,    60,    38,
    14,    20,    55,    65,    39,    26,     8,    -7,    27,    64,
    36,    19,    72,    28,    37,    51,    16,    19,    69,    20,
    20,    45,     8,    56,    61,    57,    20,    76,    70,    66,
    84,    85,    73,    77,    81,    78,    15,    24,    44,    53,
    82,    68
};

static const short yycheck[] = {    11,
     5,    24,    21,    11,     9,     1,     8,    11,    24,    11,
    26,     3,     1,     1,    11,    23,     6,     5,    22,    31,
    22,    40,    11,    11,    21,    14,    49,    23,    24,     4,
    19,    22,     1,    22,    23,     1,     1,    21,    50,    58,
     5,    10,    47,    55,    25,    11,    11,     0,    14,    54,
     1,     1,    64,    19,     5,     5,    22,     1,    59,    10,
    10,     7,    11,    21,     7,     9,    10,    68,    20,    26,
     0,     0,    14,    21,    21,    20,     9,    14,    34,    43,
    79,    58
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/dn29/PRODUCTS/maintenance/Mandriva2008/bison-1.25/share/bison.simple"

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

#ifndef alloca
#ifdef __GNUC__
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi)
#include <alloca.h>
#else /* not sparc */
#if defined (MSDOS) && !defined (__TURBOC__)
#include <malloc.h>
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
#include <malloc.h>
 #pragma alloca
#else /* not MSDOS, __TURBOC__, or _AIX */
#ifdef __hpux
#ifdef __cplusplus
extern "C" {
void *alloca (unsigned int);
};
#else /* not __cplusplus */
void *alloca ();
#endif /* not __cplusplus */
#endif /* __hpux */
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc.  */
#endif /* not GNU C.  */
#endif /* alloca not defined.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	return(0)
#define YYABORT 	return(1)
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
int yyparse (void);
#endif

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_memcpy(TO,FROM,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (to, from, count)
     char *to;
     char *from;
     int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (char *to, char *from, int count)
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 196 "/dn29/PRODUCTS/maintenance/Mandriva2008/bison-1.25/share/bison.simple"

/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#ifdef __cplusplus
#define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#else /* not __cplusplus */
#define YYPARSE_PARAM_ARG YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#endif /* not __cplusplus */
#else /* not YYPARSE_PARAM */
#define YYPARSE_PARAM_ARG
#define YYPARSE_PARAM_DECL
#endif /* not YYPARSE_PARAM */

int
yyparse(YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
      yyss = (short *) alloca (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss, (char *)yyss1, size * sizeof (*yyssp));
      yyvs = (YYSTYPE *) alloca (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs, (char *)yyvs1, size * sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) alloca (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls, (char *)yyls1, size * sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 10:
#line 49 "/dn43/OCCT/tmp/results_31.05.2011/occt/release-sources-20110531/src/StepFile/step.yacc"
{  rec_finfile();  return(0);  /*  fini pour celui-la  */  ;
    break;}
case 15:
#line 58 "/dn43/OCCT/tmp/results_31.05.2011/occt/release-sources-20110531/src/StepFile/step.yacc"
{  rec_finhead();  ;
    break;}
case 16:
#line 60 "/dn43/OCCT/tmp/results_31.05.2011/occt/release-sources-20110531/src/StepFile/step.yacc"
{  rec_typarg(rec_argIdent);     rec_newarg();  ;
    break;}
case 17:
#line 61 "/dn43/OCCT/tmp/results_31.05.2011/occt/release-sources-20110531/src/StepFile/step.yacc"
{  /* deja fait par lex*/ 	 rec_newarg();  ;
    break;}
case 18:
#line 62 "/dn43/OCCT/tmp/results_31.05.2011/occt/release-sources-20110531/src/StepFile/step.yacc"
{  rec_newarg();  ;
    break;}
case 19:
#line 63 "/dn43/OCCT/tmp/results_31.05.2011/occt/release-sources-20110531/src/StepFile/step.yacc"
{  rec_newarg();  ;
    break;}
case 20:
#line 64 "/dn43/OCCT/tmp/results_31.05.2011/occt/release-sources-20110531/src/StepFile/step.yacc"
{  rec_typarg(rec_argMisc);      rec_newarg();
			   yyerrstatus = 1; yyclearin;  ;
    break;}
case 21:
#line 69 "/dn43/OCCT/tmp/results_31.05.2011/occt/release-sources-20110531/src/StepFile/step.yacc"
{  rec_listype();  ;
    break;}
case 22:
#line 72 "/dn43/OCCT/tmp/results_31.05.2011/occt/release-sources-20110531/src/StepFile/step.yacc"
{  rec_deblist();  ;
    break;}
case 23:
#line 75 "/dn43/OCCT/tmp/results_31.05.2011/occt/release-sources-20110531/src/StepFile/step.yacc"
{  if (modeprint > 0)
		{  printf("Record no : %d -- ",nbrec+1);  rec_print(currec);  }
	   rec_newent ();  yyerrstatus = 0; ;
    break;}
case 40:
#line 102 "/dn43/OCCT/tmp/results_31.05.2011/occt/release-sources-20110531/src/StepFile/step.yacc"
{  scope_debut();  ;
    break;}
case 41:
#line 105 "/dn43/OCCT/tmp/results_31.05.2011/occt/release-sources-20110531/src/StepFile/step.yacc"
{  rec_typarg(rec_argIdent);    rec_newarg();  ;
    break;}
case 44:
#line 111 "/dn43/OCCT/tmp/results_31.05.2011/occt/release-sources-20110531/src/StepFile/step.yacc"
{  rec_deblist();  ;
    break;}
case 45:
#line 114 "/dn43/OCCT/tmp/results_31.05.2011/occt/release-sources-20110531/src/StepFile/step.yacc"
{  scope_fin();  ;
    break;}
case 46:
#line 116 "/dn43/OCCT/tmp/results_31.05.2011/occt/release-sources-20110531/src/StepFile/step.yacc"
{  printf("***  Warning : Export List not yet processed\n");
	   rec_newent();  scope_fin() ; ;
    break;}
case 47:
#line 121 "/dn43/OCCT/tmp/results_31.05.2011/occt/release-sources-20110531/src/StepFile/step.yacc"
{  rec_ident();  ;
    break;}
case 48:
#line 124 "/dn43/OCCT/tmp/results_31.05.2011/occt/release-sources-20110531/src/StepFile/step.yacc"
{  rec_type ();  ;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 498 "/dn29/PRODUCTS/maintenance/Mandriva2008/bison-1.25/share/bison.simple"

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;
}
#line 126 "/dn43/OCCT/tmp/results_31.05.2011/occt/release-sources-20110531/src/StepFile/step.yacc"
