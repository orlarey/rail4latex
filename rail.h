/*
 * rail.h - global definitions for rail program
 *
 */

#define RIGHT_ARROW 'r'         /* right arrowhead (prefix for LaTeX macros)*/
#define LEFT_ARROW  'l'         /* right arrowhead (prefix for LaTeX macros)*/
#define NO_ARROW    ' '         /* no arrowhead (prefix for LaTeX macros)*/

#define	UNKNOWN	'?'		/* unknown */
#define	TOKEN	'o'		/* terminal or nonterminal */
#define	TERM	't'		/* terminal */
#define	NTERM	'n'		/* nonterminal */

typedef struct id {
	char *name;		/* identifier */
	struct id *next;	/* link to next entry */
	int kind;		/* UNKNOWN, TOKEN, TERM, NTERM */
} IDTYPE;

#define	EMPTY	'e'
#define	CAT	';'
#define	BAR	'|'
#define	PLUS	'+'
#define	ANNOTE	'a'
#define	IDENT	'i'
#define	STRNG	's'
#define	CR	'c'

#define	MAXLIST	50

typedef struct body {
	int kind;			/* kind */
	struct body *list[MAXLIST];	/* sub-bodies */
	int nlist;			/* number of bodies */
	int entry,exit;			/* entry, exit */
	int ystart;			/* starting y coordinate */
	int ynext;			/* next y coordinate */
	int done;			/* done flag */
	IDTYPE *id;			/* identifier */
	char *text;			/* text */
	char *annot;			/* annotation */
} BODYTYPE;

#define	NULLBODY	((BODYTYPE *)NULL)

typedef struct rule {
	IDTYPE *id;
	BODYTYPE *body;
	struct rule *next;
} RULETYPE;

typedef union {
	IDTYPE *id;	/* identifier */
	int num;	/* number */
	char *text;	/* text */
	BODYTYPE *body;	/* body */
	RULETYPE *rule;	/* rule */
} YYSTYPE;

extern unsigned line;
extern int copy;

extern FILE *outf;

extern int altstar;
extern int anonymous;

extern IDTYPE *errorid;

extern char* mcheck(char* s);

extern BODYTYPE* newbody(int kind, BODYTYPE* body1, BODYTYPE* body2);
extern void freebody(BODYTYPE* body);
extern int isemptybody(BODYTYPE * body);
extern BODYTYPE* addbody(int kind, BODYTYPE* body1, BODYTYPE* body2);
extern BODYTYPE *revbody();

extern RULETYPE *newrule();
extern void freerule(RULETYPE * rule);
extern RULETYPE *addrule();
extern void outrule(RULETYPE* rule);


extern IDTYPE *lookup();
extern void delete(IDTYPE *id);

extern void undef(IDTYPE* id);
extern void redef(IDTYPE* id);
extern void error(char* f, char* s);
extern int setopt(char c, char* s);
