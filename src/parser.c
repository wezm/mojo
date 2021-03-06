/* A recursive-descent parser generated by peg 0.1.2 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define YYRULECOUNT 10

  #include "mojo.h"
  #define YYSTYPE char *
  #define DUP yy = strdup(yytext)
  #define LPAREN '{'
  #define RPAREN '}'
  #define pc putchar
  #define p printf

#ifndef YY_VARIABLE
#define YY_VARIABLE(T)	static T
#endif
#ifndef YY_LOCAL
#define YY_LOCAL(T)	static T
#endif
#ifndef YY_ACTION
#define YY_ACTION(T)	static T
#endif
#ifndef YY_RULE
#define YY_RULE(T)	static T
#endif
#ifndef YY_PARSE
#define YY_PARSE(T)	T
#endif
#ifndef YYPARSE
#define YYPARSE		yyparse
#endif
#ifndef YYPARSEFROM
#define YYPARSEFROM	yyparsefrom
#endif
#ifndef YY_INPUT
#define YY_INPUT(buf, result, max_size)			\
  {							\
    int yyc= getchar();					\
    result= (EOF == yyc) ? 0 : (*(buf)= yyc, 1);	\
    yyprintf((stderr, "<%c>", yyc));			\
  }
#endif
#ifndef YY_BEGIN
#define YY_BEGIN	( yybegin= yypos, 1)
#endif
#ifndef YY_END
#define YY_END		( yyend= yypos, 1)
#endif
#ifdef YY_DEBUG
# define yyprintf(args)	fprintf args
#else
# define yyprintf(args)
#endif
#ifndef YYSTYPE
#define YYSTYPE	int
#endif

#ifndef YY_PART

typedef void (*yyaction)(char *yytext, int yyleng);
typedef struct _yythunk { int begin, end;  yyaction  action;  struct _yythunk *next; } yythunk;

YY_VARIABLE(char *   ) yybuf= 0;
YY_VARIABLE(int	     ) yybuflen= 0;
YY_VARIABLE(int	     ) yypos= 0;
YY_VARIABLE(int	     ) yylimit= 0;
YY_VARIABLE(char *   ) yytext= 0;
YY_VARIABLE(int	     ) yytextlen= 0;
YY_VARIABLE(int	     ) yybegin= 0;
YY_VARIABLE(int	     ) yyend= 0;
YY_VARIABLE(int	     ) yytextmax= 0;
YY_VARIABLE(yythunk *) yythunks= 0;
YY_VARIABLE(int	     ) yythunkslen= 0;
YY_VARIABLE(int      ) yythunkpos= 0;
YY_VARIABLE(YYSTYPE  ) yy;
YY_VARIABLE(YYSTYPE *) yyval= 0;
YY_VARIABLE(YYSTYPE *) yyvals= 0;
YY_VARIABLE(int      ) yyvalslen= 0;

YY_LOCAL(int) yyrefill(void)
{
  int yyn;
  while (yybuflen - yypos < 512)
    {
      yybuflen *= 2;
      yybuf= realloc(yybuf, yybuflen);
    }
  YY_INPUT((yybuf + yypos), yyn, (yybuflen - yypos));
  if (!yyn) return 0;
  yylimit += yyn;
  return 1;
}

YY_LOCAL(int) yymatchDot(void)
{
  if (yypos >= yylimit && !yyrefill()) return 0;
  ++yypos;
  return 1;
}

YY_LOCAL(int) yymatchChar(int c)
{
  if (yypos >= yylimit && !yyrefill()) return 0;
  if (yybuf[yypos] == c)
    {
      ++yypos;
      yyprintf((stderr, "  ok   yymatchChar(%c) @ %s\n", c, yybuf+yypos));
      return 1;
    }
  yyprintf((stderr, "  fail yymatchChar(%c) @ %s\n", c, yybuf+yypos));
  return 0;
}

YY_LOCAL(int) yymatchString(char *s)
{
  int yysav= yypos;
  while (*s)
    {
      if (yypos >= yylimit && !yyrefill()) return 0;
      if (yybuf[yypos] != *s)
        {
          yypos= yysav;
          return 0;
        }
      ++s;
      ++yypos;
    }
  return 1;
}

YY_LOCAL(int) yymatchClass(unsigned char *bits)
{
  int c;
  if (yypos >= yylimit && !yyrefill()) return 0;
  c= yybuf[yypos];
  if (bits[c >> 3] & (1 << (c & 7)))
    {
      ++yypos;
      yyprintf((stderr, "  ok   yymatchClass @ %s\n", yybuf+yypos));
      return 1;
    }
  yyprintf((stderr, "  fail yymatchClass @ %s\n", yybuf+yypos));
  return 0;
}

YY_LOCAL(void) yyDo(yyaction action, int begin, int end)
{
  while (yythunkpos >= yythunkslen)
    {
      yythunkslen *= 2;
      yythunks= realloc(yythunks, sizeof(yythunk) * yythunkslen);
    }
  yythunks[yythunkpos].begin=  begin;
  yythunks[yythunkpos].end=    end;
  yythunks[yythunkpos].action= action;
  ++yythunkpos;
}

YY_LOCAL(int) yyText(int begin, int end)
{
  int yyleng= end - begin;
  if (yyleng <= 0)
    yyleng= 0;
  else
    {
      while (yytextlen < (yyleng - 1))
	{
	  yytextlen *= 2;
	  yytext= realloc(yytext, yytextlen);
	}
      memcpy(yytext, yybuf + begin, yyleng);
    }
  yytext[yyleng]= '\0';
  return yyleng;
}

YY_LOCAL(void) yyDone(void)
{
  int pos;
  for (pos= 0;  pos < yythunkpos;  ++pos)
    {
      yythunk *thunk= &yythunks[pos];
      int yyleng= thunk->end ? yyText(thunk->begin, thunk->end) : thunk->begin;
      yyprintf((stderr, "DO [%d] %p %s\n", pos, thunk->action, yytext));
      thunk->action(yytext, yyleng);
    }
  yythunkpos= 0;
}

YY_LOCAL(void) yyCommit()
{
  if ((yylimit -= yypos))
    {
      memmove(yybuf, yybuf + yypos, yylimit);
    }
  yybegin -= yypos;
  yyend -= yypos;
  yypos= yythunkpos= 0;
}

YY_LOCAL(int) yyAccept(int tp0)
{
  if (tp0)
    {
      fprintf(stderr, "accept denied at %d\n", tp0);
      return 0;
    }
  else
    {
      yyDone();
      yyCommit();
    }
  return 1;
}

YY_LOCAL(void) yyPush(char *text, int count)	{ yyval += count; }
YY_LOCAL(void) yyPop(char *text, int count)	{ yyval -= count; }
YY_LOCAL(void) yySet(char *text, int count)	{ yyval[count]= yy; }

#endif /* YY_PART */

#define	YYACCEPT	yyAccept(yythunkpos0)

YY_RULE(int) yy__(); /* 10 */
YY_RULE(int) yy_id(); /* 9 */
YY_RULE(int) yy_close(); /* 8 */
YY_RULE(int) yy_open(); /* 7 */
YY_RULE(int) yy_nl(); /* 6 */
YY_RULE(int) yy_enum(); /* 5 */
YY_RULE(int) yy_var(); /* 4 */
YY_RULE(int) yy_comment(); /* 3 */
YY_RULE(int) yy_body(); /* 2 */
YY_RULE(int) yy_main(); /* 1 */

YY_ACTION(void) yy_1_id(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_1_id\n"));
   DUP ;
}
YY_ACTION(void) yy_4_enum(char *yytext, int yyleng)
{
#define a yyval[-1]
  yyprintf((stderr, "do yy_4_enum\n"));
   p("'%c) + '", RPAREN) ;
#undef a
}
YY_ACTION(void) yy_3_enum(char *yytext, int yyleng)
{
#define a yyval[-1]
  yyprintf((stderr, "do yy_3_enum\n"));
   p("'%c) + '", RPAREN) ;
#undef a
}
YY_ACTION(void) yy_2_enum(char *yytext, int yyleng)
{
#define a yyval[-1]
  yyprintf((stderr, "do yy_2_enum\n"));
   p("' + %s(o, Mojo.normalize(o), function(o)%c\n    return '", MOJO_ENUM_FN, LPAREN) ;
#undef a
}
YY_ACTION(void) yy_1_enum(char *yytext, int yyleng)
{
#define a yyval[-1]
  yyprintf((stderr, "do yy_1_enum\n"));
   p("' + %s(o, Mojo.normalize(o, \"%s\"), function(o)%c\n    return '", MOJO_ENUM_FN, a, LPAREN) ;
#undef a
}
YY_ACTION(void) yy_2_var(char *yytext, int yyleng)
{
#define a yyval[-1]
  yyprintf((stderr, "do yy_2_var\n"));
   p("' + (Mojo.escape(Mojo.normalize(o))) + '") ;
#undef a
}
YY_ACTION(void) yy_1_var(char *yytext, int yyleng)
{
#define a yyval[-1]
  yyprintf((stderr, "do yy_1_var\n"));
   p("' + (Mojo.escape(Mojo.normalize(o, \"%s\"))) + '", a) ;
#undef a
}
YY_ACTION(void) yy_2_body(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_2_body\n"));
   p("%s", yytext) ;
}
YY_ACTION(void) yy_1_body(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_1_body\n"));
   p("\\n\\\n") ;
}
YY_ACTION(void) yy_2_main(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_2_main\n"));
   pc('\'') ;
}
YY_ACTION(void) yy_1_main(char *yytext, int yyleng)
{
  yyprintf((stderr, "do yy_1_main\n"));
   pc('\'') ;
}

YY_RULE(int) yy__()
{
  yyprintf((stderr, "%s\n", "_"));
  l2:;	
  {  int yypos3= yypos, yythunkpos3= yythunkpos;  if (!yymatchClass((unsigned char *)"\000\002\000\000\001\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000")) goto l3;  goto l2;
  l3:;	  yypos= yypos3; yythunkpos= yythunkpos3;
  }
  yyprintf((stderr, "  ok   %s @ %s\n", "_", yybuf+yypos));
  return 1;
}
YY_RULE(int) yy_id()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "id"));  yyText(yybegin, yyend);  if (!(YY_BEGIN)) goto l4;  if (!yymatchClass((unsigned char *)"\000\000\000\000\000\000\377\003\376\377\377\207\376\377\377\007\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000")) goto l4;
  l5:;	
  {  int yypos6= yypos, yythunkpos6= yythunkpos;  if (!yymatchClass((unsigned char *)"\000\000\000\000\000\000\377\003\376\377\377\207\376\377\377\007\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000\000")) goto l6;  goto l5;
  l6:;	  yypos= yypos6; yythunkpos= yythunkpos6;
  }  yyText(yybegin, yyend);  if (!(YY_END)) goto l4;  yyDo(yy_1_id, yybegin, yyend);
  yyprintf((stderr, "  ok   %s @ %s\n", "id", yybuf+yypos));
  return 1;
  l4:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "id", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_close()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "close"));  if (!yy__()) goto l7;  if (!yymatchChar('}')) goto l7;
  l8:;	
  {  int yypos9= yypos, yythunkpos9= yythunkpos;  if (!yymatchChar('}')) goto l9;  goto l8;
  l9:;	  yypos= yypos9; yythunkpos= yythunkpos9;
  }
  yyprintf((stderr, "  ok   %s @ %s\n", "close", yybuf+yypos));
  return 1;
  l7:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "close", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_open()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "open"));  if (!yymatchChar('{')) goto l10;
  l11:;	
  {  int yypos12= yypos, yythunkpos12= yythunkpos;  if (!yymatchChar('{')) goto l12;  goto l11;
  l12:;	  yypos= yypos12; yythunkpos= yythunkpos12;
  }  if (!yy__()) goto l10;
  yyprintf((stderr, "  ok   %s @ %s\n", "open", yybuf+yypos));
  return 1;
  l10:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "open", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_nl()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "nl"));
  {  int yypos14= yypos, yythunkpos14= yythunkpos;  if (!yymatchChar('\r')) goto l15;  goto l14;
  l15:;	  yypos= yypos14; yythunkpos= yythunkpos14;  if (!yymatchString("\r\n")) goto l16;  goto l14;
  l16:;	  yypos= yypos14; yythunkpos= yythunkpos14;  if (!yymatchChar('\n')) goto l13;
  }
  l14:;	
  yyprintf((stderr, "  ok   %s @ %s\n", "nl", yybuf+yypos));
  return 1;
  l13:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "nl", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_enum()
{  int yypos0= yypos, yythunkpos0= yythunkpos;  yyDo(yyPush, 1, 0);
  yyprintf((stderr, "%s\n", "enum"));
  {  int yypos18= yypos, yythunkpos18= yythunkpos;  if (!yy_open()) goto l19;  if (!yymatchChar('#')) goto l19;  if (!yy__()) goto l19;  if (!yy_id()) goto l19;  yyDo(yySet, -1, 0);  if (!yy_close()) goto l19;  yyDo(yy_1_enum, yybegin, yyend);  goto l18;
  l19:;	  yypos= yypos18; yythunkpos= yythunkpos18;  if (!yy_open()) goto l20;  if (!yymatchChar('#')) goto l20;  if (!yy__()) goto l20;  if (!yymatchChar('.')) goto l20;  if (!yy_close()) goto l20;  yyDo(yy_2_enum, yybegin, yyend);  goto l18;
  l20:;	  yypos= yypos18; yythunkpos= yythunkpos18;  if (!yy_open()) goto l21;  if (!yymatchChar('/')) goto l21;  if (!yy__()) goto l21;  if (!yy_id()) goto l21;  yyDo(yySet, -1, 0);  if (!yy_close()) goto l21;  yyDo(yy_3_enum, yybegin, yyend);  goto l18;
  l21:;	  yypos= yypos18; yythunkpos= yythunkpos18;  if (!yy_open()) goto l17;  if (!yymatchChar('/')) goto l17;  if (!yy__()) goto l17;  if (!yymatchChar('.')) goto l17;  if (!yy_close()) goto l17;  yyDo(yy_4_enum, yybegin, yyend);
  }
  l18:;	
  yyprintf((stderr, "  ok   %s @ %s\n", "enum", yybuf+yypos));  yyDo(yyPop, 1, 0);
  return 1;
  l17:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "enum", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_var()
{  int yypos0= yypos, yythunkpos0= yythunkpos;  yyDo(yyPush, 1, 0);
  yyprintf((stderr, "%s\n", "var"));
  {  int yypos23= yypos, yythunkpos23= yythunkpos;  if (!yy_open()) goto l24;  if (!yy_id()) goto l24;  yyDo(yySet, -1, 0);  if (!yy_close()) goto l24;  yyDo(yy_1_var, yybegin, yyend);  goto l23;
  l24:;	  yypos= yypos23; yythunkpos= yythunkpos23;  if (!yy_open()) goto l22;  if (!yymatchChar('.')) goto l22;  if (!yy_close()) goto l22;  yyDo(yy_2_var, yybegin, yyend);
  }
  l23:;	
  yyprintf((stderr, "  ok   %s @ %s\n", "var", yybuf+yypos));  yyDo(yyPop, 1, 0);
  return 1;
  l22:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "var", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_comment()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "comment"));  if (!yy_open()) goto l25;  if (!yymatchChar('!')) goto l25;  yyText(yybegin, yyend);  if (!(YY_BEGIN)) goto l25;
  l26:;	
  {  int yypos27= yypos, yythunkpos27= yythunkpos;
  {  int yypos28= yypos, yythunkpos28= yythunkpos;  if (!yy_close()) goto l28;  goto l27;
  l28:;	  yypos= yypos28; yythunkpos= yythunkpos28;
  }  if (!yymatchDot()) goto l27;  goto l26;
  l27:;	  yypos= yypos27; yythunkpos= yythunkpos27;
  }  yyText(yybegin, yyend);  if (!(YY_END)) goto l25;  if (!yy_close()) goto l25;
  yyprintf((stderr, "  ok   %s @ %s\n", "comment", yybuf+yypos));
  return 1;
  l25:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "comment", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_body()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "body"));
  {  int yypos30= yypos, yythunkpos30= yythunkpos;  if (!yy_comment()) goto l31;  goto l30;
  l31:;	  yypos= yypos30; yythunkpos= yythunkpos30;  if (!yy_var()) goto l32;  goto l30;
  l32:;	  yypos= yypos30; yythunkpos= yythunkpos30;  if (!yy_enum()) goto l33;  goto l30;
  l33:;	  yypos= yypos30; yythunkpos= yythunkpos30;  if (!yy_nl()) goto l34;  yyDo(yy_1_body, yybegin, yyend);  goto l30;
  l34:;	  yypos= yypos30; yythunkpos= yythunkpos30;  yyText(yybegin, yyend);  if (!(YY_BEGIN)) goto l29;  if (!yymatchDot()) goto l29;  yyText(yybegin, yyend);  if (!(YY_END)) goto l29;  yyDo(yy_2_body, yybegin, yyend);
  }
  l30:;	
  yyprintf((stderr, "  ok   %s @ %s\n", "body", yybuf+yypos));
  return 1;
  l29:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "body", yybuf+yypos));
  return 0;
}
YY_RULE(int) yy_main()
{  int yypos0= yypos, yythunkpos0= yythunkpos;
  yyprintf((stderr, "%s\n", "main"));  yyDo(yy_1_main, yybegin, yyend);  if (!yy_body()) goto l35;
  l36:;	
  {  int yypos37= yypos, yythunkpos37= yythunkpos;  if (!yy_body()) goto l37;  goto l36;
  l37:;	  yypos= yypos37; yythunkpos= yythunkpos37;
  }  yyDo(yy_2_main, yybegin, yyend);
  yyprintf((stderr, "  ok   %s @ %s\n", "main", yybuf+yypos));
  return 1;
  l35:;	  yypos= yypos0; yythunkpos= yythunkpos0;
  yyprintf((stderr, "  fail %s @ %s\n", "main", yybuf+yypos));
  return 0;
}

#ifndef YY_PART

typedef int (*yyrule)();

YY_PARSE(int) YYPARSEFROM(yyrule yystart)
{
  int yyok;
  if (!yybuflen)
    {
      yybuflen= 1024;
      yybuf= malloc(yybuflen);
      yytextlen= 1024;
      yytext= malloc(yytextlen);
      yythunkslen= 32;
      yythunks= malloc(sizeof(yythunk) * yythunkslen);
      yyvalslen= 32;
      yyvals= malloc(sizeof(YYSTYPE) * yyvalslen);
      yybegin= yyend= yypos= yylimit= yythunkpos= 0;
    }
  yybegin= yyend= yypos;
  yythunkpos= 0;
  yyval= yyvals;
  yyok= yystart();
  if (yyok) yyDone();
  yyCommit();
  return yyok;
  (void)yyrefill;
  (void)yymatchDot;
  (void)yymatchChar;
  (void)yymatchString;
  (void)yymatchClass;
  (void)yyDo;
  (void)yyText;
  (void)yyDone;
  (void)yyCommit;
  (void)yyAccept;
  (void)yyPush;
  (void)yyPop;
  (void)yySet;
  (void)yytextmax;
}

YY_PARSE(int) YYPARSE(void)
{
  return YYPARSEFROM(yy_main);
}

#endif


void 
Mojo_parse() {
  while (YYPARSE()); 
}

