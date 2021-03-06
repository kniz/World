%{
    class Node;
    #include "wrdcBison.h"
    #include <string>
    #include <iostream>
    #include <stack>
    #include <vector>
    using namespace std;

    int nowIndent = 0;
    stack<int> indentLvs;
    static const int TAB_WIDTH = 4;

    extern int nowRule;
    extern int prevRule;

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
        if (yydebug)
            cout << " ---- CHANGE RULE to " << name << "(" << new1 << ")\n";
    }
    void changePrevRule() {
        if (yydebug)
            cout << " ---- CHANGE PREV RULE TO " << prevRule << "\n";
        BEGIN(prevRule);
    }
%}

%x dquote
%s tfile
%x indent
%x dedent
%x commenting
%x arraytyping

%%

for { return tfor; }
if { return tif; }
else { return telse; }
elif { return telif; }
"def"[\(]* {
    string temp = yytext;
    if(temp[temp.size()-1] == '(') {
        temp = temp.substr(0, temp.size()-1);
        unput('(');
    }

    yylval.strVal = strdup(temp.c_str());
    return tdef;
}
from { return tfrom; }
out { return tout; }
"prop"[\(]* {
    string temp = yytext;
    if(temp[temp.size()-1] == '(') {
        temp = temp.substr(0, temp.size()-1);
        unput('(');
    }

    yylval.strVal = strdup(temp.c_str());
    return tprop;
}
import { return timport; }
aka { return taka; }
with { return twith; }
next { return tnext; }
in { return tin; }
ret { return tret; }
return { return treturn; }
(_)*@set {
    yylval.strVal = strdup(yytext);
    return tfset;
}
(_)*@get {
    yylval.strVal = strdup(yytext);
    return tfget;
}
(_)*@ctor {
    yylval.strVal = strdup(yytext);
    return tfctor;
}
(_)*@dtor {
    yylval.strVal = strdup(yytext);
    return tfdtor;
}
(_)*@res {
    yylval.strVal = strdup(yytext);
    return tfres;
}
(_)*@warn {
    yylval.strVal = strdup(yytext);
    return tfwarn;
}
(_)*@err {
    yylval.strVal = strdup(yytext);
    return tferr;
}

true|false {
    yylval.boolVal = string(yytext) == "true" ? true : false;
    return tbool;
}

<dedent>\/\/[^\n]* { if(yydebug) cout << "!!!!2"; }
<indent>\/\/[^\n]* { if(yydebug) cout << "!!!!3"; }
\/\/[^\n]* { if(yydebug) cout << "!!!!1"; }

"/*" {
    changeRule("commenting", commenting);
}
<indent>"/*" {
    changeRule("commenting", commenting);
}
<dedent>"/*" {
    changeRule("commenting", commenting);
}
<commenting>"*/" {
    changePrevRule();
    if(yydebug)
        cout << "!!!!!!!!!!!end";
}
<commenting>. { if(yydebug) cout << "1";}
<commenting>\n { if(yydebug) cout << "2"; }






[a-zA-Z][a-zA-Z0-9_]*\{ {
    string temp = yytext;
    changeRule("arraytyping", arraytyping);

    unput('{');
    temp = temp.substr(0, temp.size()-1);
    yylval.strVal = strdup(temp.c_str());
    return tconName;
}

<arraytyping>\{ {
    if(yydebug)
        cout << "----------lex: found '{' \n";
    return yytext[0];
}
<arraytyping>\}\{ {
    unput('{');
    return yytext[0];
}
<arraytyping>\} {
    changePrevRule();
    if(yydebug)
        cout << "----------lex: found '}' \n";
    return yytext[0];
}
<arraytyping>[a-zA-Z0-9_]+\} {
    string temp = yytext;
    temp = temp.substr(0, temp.size()-1);
    unput('}');
    yylval.strVal = strdup(temp.c_str());
    if(yydebug)
        cout << "----------lex: tnormalId is " << yylval.strVal << " ---- \n";
    return tnormalId;
}

@[a-zA-Z][a-zA-Z0-9_]* {
    yylval.strVal = strdup(yytext);
    return tdeckId;
}

[a-zA-Z][a-zA-Z0-9_]*   {
   yylval.strVal = strdup(yytext);
    return tnormalId;
}

(_$|_|$)[a-zA-Z0-9_]+ {
    // Accessed 컨셉:
    //  배경:
    //      * accessed란 식별자 정의시, 그 앞에 protected인지 static인지 속성을 지정하는 것을 말한다.
    //      * 이때 이 accessed가 올바르게 작성된것인지 판단을 lexer에서 하는지, parser에서 하는지를 구분하고자 한다.
    //
    //  해결:
    //      * lex에서는 accessed가 올 수 있는자리다... 라는 것 까지만 판단한다.
    //      *  이를테면 모든 시나리오를 고려했을때 해당 lexer 룰의 accessed가 와도 되는 케이스가 1개라도 존재한다면
    //      *  lex에서는 accessed가 올 수 있다는 걸 rule에 포함할 것이다.
    //      * 정말로 accessed가 올바르게 작성되었는가는 파서가 판단한다.
    //      *  왜냐하면 이것을 정확하게 알기 위해서는 파서가 앞 뒤의 문맥을 보고 판단을 해야 하기 때문이다.
    //
    //  결론:
    //      * lexer는 문맥을 보지 못한다. 해당 rule에 accessed가 올 수 있는 1가지의 시나리오라도 존재한다면 rule에 포함한다.
    //      * 파서는 문맥을 볼 수 있으므로, lexer가 건내준 accessed가 올바른 것인지 최종 판단한다.

    yylval.strVal = strdup(yytext);
    return taccessedId;
}

<INITIAL>\' {
    changeRule("dquote", dquote); // maximum parsing을 하기 때문에 state 관리를 해줘야 한다.
}

    <dquote>[^\'\n]*\' { // dquote 상태일때, <" 를 제외한 문자> + "가 붙는 경우
        changeRule("INITIAL", INITIAL);
        string parsed = "\'" + string(yytext);
        yylval.strVal = strdup(parsed.c_str());
        return tstr;
    }

\n {
    if(yydebug)
        cout << " --- enter indent rule\n";
    nowIndent = 0;
    changeRule("indent", indent);
    return teol;
}



<dedent>\n {
    nowIndent = 0;
    return teol;
}
<dedent>[ ] {
    if (yydebug) cout << "<dedent> nowIndent=" << nowIndent << "\n";
    nowIndent++;
}
<dedent>\t {
    nowIndent = (nowIndent + TAB_WIDTH) & ~(TAB_WIDTH - 1);
}
<dedent>. {
    char ch = yytext[0];

    int prevIndentLv = indentLvs.size() ? indentLvs.top() : 0;
    if(yydebug)
        cout << "  ---  ch=" << ch << "(" << (int) ch << ") dedent check finish. prevIndentLv=" << prevIndentLv << " indentLvs.size()=" << indentLvs.size() << " nowIndent=" << nowIndent << "\n";

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
\+\= { return topPlusAssign; }
-= { return topMinusAssign; }
\*= { return topSquareAssign; }
\/= { return topDivideAssign; }
%= { return topModAssign; }
^= { return topPowAssign; }
\<= { return topLessEqual; }
\>\= { return topMoreEqual; }
\=\= { return topEqual; }
\=\=\= { return topRefEqual; }
\!\= { return topNotEqual; }
\!\=\= { return topNotRefEqual; }
\?\. { return topSafeNavi; }
\.\. { return topSeq; }
\=\> { return topRedirect; }
\+\+ { return topUplus; }
\-\- { return topUminus; }

\'.\' {
    yylval.charVal = yytext[1];
    return tchar;
}

(_)[a-zA-Z0-9_]+\( {
    string temp = yytext;
    temp = temp.substr(0, temp.size()-1);
    yylval.strVal = strdup(temp.c_str());
    unput('(');
    return taccessedFuncname;
}

[a-zA-Z][a-zA-Z0-9_]*\( {
    string temp = yytext;
    temp = temp.substr(0, temp.size()-1);
    yylval.strVal = strdup(temp.c_str());
    unput('(');
    return tnormalFuncname;
}


<indent>[ ] { nowIndent++; }
<indent>\t {
    nowIndent = (nowIndent + TAB_WIDTH) & ~(TAB_WIDTH - 1);
}
<indent>\n {
    if(yydebug)
        cout << "---------------- indent newline\n";
    nowIndent = 0;
}
<indent>. {
    char ch = yytext[0];

    int prevIndentLv = indentLvs.size() ? indentLvs.top() : 0;
    if(yydebug)
        cout << "  ---  indent check finish. prevIndentLv=" << prevIndentLv << " indentLvs.size()=" << indentLvs.size() << "\n";
    if (nowIndent > prevIndentLv) {
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

<indent><<EOF>> {
    if(yydebug)
        cout << "----------------------EOF!!!!!\n";
    if (goOutdent(yytext[0]) == tdedent) {
        if(yydebug)
            cout << "----------- return tdedent from EOF!\n";
        return tdedent;
    }

    if(yydebug)
        cout << "----------- return meetEof()\n";
    return meetEof();
}

[ ]* {
}

. {
    return yytext[0];
}

<<EOF>> {
    return meetEof();
}


%%

int meetEof() {
    static int cnt = 0;
    if(yydebug)
        cout << "----------- meetEOF(" << cnt << ")\n";
    switch (++cnt) {
        case 0:
            if(yydebug)
                cout << "-------- return teol\n";
            return teol;
        case 1:
            if(yydebug)
                cout << "-------- return teof\n";
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
    if (yydebug) cout << " ----- prev=" << prev << " nowIndent=" << nowIndent << "\n";
    for (int n=0; n < nowIndent ;n++)
        unput(' ');
    if (prev != ',' && prev != ')' || top - nowIndent != TAB_WIDTH) {
        if(yydebug) cout << " ----- dedent and newline!\n";
        unput('\n');
    } else if(yydebug) cout << " ----- dedent only!\n";

    changeRule("dedent", dedent);
    if(yydebug)
        cout << " ----- dedent: pop! now " << indentLvs.size() << " dedentLv left. \n";
    nowIndent = 0;
    return tdedent;
}

int nowRule = INITIAL;
int prevRule = INITIAL;

int yywrap()
{
    return 1;
}
