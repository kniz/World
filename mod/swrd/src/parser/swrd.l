%{
namespace wrd { namespace swrd {
    class obj;
}}
#include "swrdParser.hpp"
#include "../common.hpp"
using namespace std;
using namespace wrd::swrd;

int nowIndent = 0;
stack<int> indentLvs;
static const int TAB_WIDTH = 4;

static const char eof = 0x05;

extern int nowRule;
extern int prevRule;
bool reachEof = false;

int goOutdent(char ch);
int meetEof();
void shiftRules(int new1) {
    prevRule = nowRule;
    nowRule = new1;
}
void changeRule(const char* name, int new1) {
    if (nowRule == new1) return;

    shiftRules(new1);
    BEGIN(new1);
    WRD_DI(" ---- CHANGE RULE to %s(%d)", name, new1);
}
void changePrevRule() {
    WRD_DI(" ---- CHANGE PREV RULE TO %d", prevRule);
    BEGIN(prevRule);
}
%}

%x DQUOTING
%x INDENTING
%x DEDENTING
%x COMMENTING
%x ARRAYING

%s tfile

%%

"def"[\(]* {
    string temp = yytext;
    if(temp[temp.size()-1] == '(') {
        temp = temp.substr(0, temp.size()-1);
        unput('(');
    }

    yylval.strVal = strdup(temp.c_str());
    return tdef;
}

true|false {
    yylval.boolVal = string(yytext) == "true" ? true : false;
    return tbool;
}

<DEDENTING>\/\/[^\n]* {
    WRD_DI("!!!!2");
}
<INDENTING>\/\/[^\n]* {
    WRD_DI("!!!!3");
}
\/\/[^\n]* {
    WRD_DI("!!!!1");
}

"/*" {
    changeRule("COMMENTING", COMMENTING);
}
<INDENTING>"/*" {
    changeRule("COMMENTING", COMMENTING);
}
<DEDENTING>"/*" {
    changeRule("COMMENTING", COMMENTING);
}
<COMMENTING>"*/" {
    changePrevRule();
    WRD_DI("!!!!!!!!!!!end");
}
<COMMENTING>. {
    WRD_DI("1");
}
<COMMENTING>\n {
    WRD_DI("2");
}






[a-zA-Z][a-zA-Z0-9_]*\{ {
    string temp = yytext;
    changeRule("ARRAYING", ARRAYING);

    unput('{');
    temp = temp.substr(0, temp.size()-1);
    yylval.strVal = strdup(temp.c_str());
    return tcontainerName;
}

<ARRAYING>\{ {
    WRD_DI("----------lex: found '{' ");
    return yytext[0];
}
<ARRAYING>\}\{ {
    unput('{');
    return yytext[0];
}
<ARRAYING>\} {
    changePrevRule();
    WRD_DI("----------lex: found '}' ");
    return yytext[0];
}
<ARRAYING>[a-zA-Z0-9_]+\} {
    string temp = yytext;
    temp = temp.substr(0, temp.size()-1);
    unput('}');
    yylval.strVal = strdup(temp.c_str());
    WRD_DI("----------lex: tid is %s ----", yylval.strVal);
    return tid;
}

[a-zA-Z][a-zA-Z0-9_]*   {
   yylval.strVal = strdup(yytext);
    return tid;
}

<INITIAL>\' {
    changeRule("DQUOTING", DQUOTING); // maximum parsing을 하기 때문에 state 관리를 해줘야 한다.
}

    <DQUOTING>[^\'\n]*\' { // DQUOTING 상태일때, <" 를 제외한 문자> + "가 붙는 경우
        changeRule("INITIAL", INITIAL);
        string parsed = string(yytext, strlen(yytext)-1);
        yylval.strVal = strdup(parsed.c_str());
        return tokStr;
    }

\n {
    nowIndent = 0;
    changeRule("INDENTING", INDENTING);
    return teol;
}



<DEDENTING>\n {
    nowIndent = 0;
    return teol;
}
<DEDENTING>[ ] {
    WRD_DI("<DEDENTING> nowIndent=%d", nowIndent);
    nowIndent++;
}
<DEDENTING>\t {
    nowIndent = (nowIndent + TAB_WIDTH) & ~(TAB_WIDTH - 1);
}

<DEDENTING>. {
    char ch = yytext[0];

    int prevIndentLv = indentLvs.size() ? indentLvs.top() : 0;
    WRD_DI("  ---  ch=%c(%d) dedent check finish. prevIndentLv=%d intentLvs.size()=%d nowIndent=%d",
        ch, ch, prevIndentLv, indentLvs.size(), nowIndent);

    if (nowIndent < prevIndentLv) {
        int res = goOutdent(ch);
        nowIndent = 0;
        return res;
    }
    else if (nowIndent == prevIndentLv) {
        unput(ch);
        changeRule("INITIAL", INITIAL);
        nowIndent = 0;
    }
}






([1-9][0-9]*|0) {
    yylval.floatVal = atof(yytext);
    return tnum;
}

([1-9][0-9]*.[0-9]+|0.[0-9]+) {
    yylval.floatVal= atof(yytext);
    return tnum;
}

:= { return topDefAssign; }

\'.\' {
    yylval.charVal = yytext[1];
    return tokChar;
}

<INDENTING>[ ] { nowIndent++; }
<INDENTING>\t {
    nowIndent = (nowIndent + TAB_WIDTH) & ~(TAB_WIDTH - 1);
}
<INDENTING>\n {
    WRD_DI("---------------- indent newline");
    nowIndent = 0;
}
<INDENTING>. {
    char ch = yytext[0];

    int prevIndentLv = indentLvs.size() ? indentLvs.top() : 0;
    WRD_DI("  ---  indent check finish. nowIndent=%d, prevIndentLv=%d indentLvs.size()=%d", nowIndent, prevIndentLv, indentLvs.size());
    if (nowIndent > prevIndentLv) {
        WRD_DI("nowIndent(%d) > prevIndentLv(%d)", nowIndent, prevIndentLv);
        indentLvs.push(nowIndent);
        unput(ch);
        return tindent;
    } else if (nowIndent == prevIndentLv) {
        changeRule("INITIAL", INITIAL);
        unput(ch);
    } else {
        return goOutdent(ch);
    }
}

<INDENTING><<EOF>> {
    WRD_DI("----------------------EOF!!!!!");
    if (goOutdent(yytext[0]) == tdedent) {
        WRD_DI("----------- return tdedent from EOF!");
        return tdedent;
    }

    WRD_DI("----------- return meetEof()");
    return meetEof();
}

[ ]* {
}

. {
    return yytext[0];
}

<INITIAL><<EOF>> {
    nowIndent = 0;
    changeRule("INDENTING", INDENTING);
    return teol;
}


%%

int nowRule = INITIAL;
int prevRule = INITIAL;
wrd::swrd::obj* root = nullptr;

int meetEof() {
    static int cnt = 0;
    WRD_DI("----------- meetEOF(%d)", cnt);
    switch (++cnt) {
        case 0:
            WRD_DI("-------- return teol");
            return teol;
        case 1:
            WRD_DI("-------- return teof");
            return teof;
    }
    return 0;
}

int goOutdent(char prev)
{
    int top = indentLvs.size() ? indentLvs.top() : 0;
    if (nowIndent >= top) return 0;

    indentLvs.pop();
    unput(prev);
    WRD_DI(" ----- prev=%d nowIndent=%d", prev, nowIndent);
    for (int n=0; n < nowIndent ;n++)
        unput(' ');
    if (prev != ',' && prev != ')' || top - nowIndent != TAB_WIDTH) {
        WRD_DI(" ----- dedent and newline!");
        unput('\n');
    } else {
        WRD_DI(" ----- dedent only!");
    }

    changeRule("DEDENTING", DEDENTING);
    WRD_DI(" ----- dedent: pop! now %d dedentLv left.", indentLvs.size());
    nowIndent = 0;
    return tdedent;
}

void yyerror(const char* s) {
    WRD_E("error #%d: %s, %s", yylineno, s, yytext);
}

int yywrap() {
    return 1;
}