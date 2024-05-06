%{

#include "FlexActions.h"

%}

/**
 * Enable start condition manipulation functions.
 */
%option stack

/**
 * Flex contexts (a.k.a. start conditions).
 *
 * @see https://westes.github.io/flex/manual/Start-Conditions.html
 */
%x MULTILINE_COMMENT


/**
 * Reusable patterns.
 *
 * @see https://westes.github.io/flex/manual/Matching.html
 * @see https://westes.github.io/flex/manual/Patterns.html
 */

color #[a-f|A-F|0-9]{6}
prop ^prop:[A-Za-z0-9]+$

%%

"/*"								{ BEGIN(MULTILINE_COMMENT); BeginMultilineCommentLexemeAction(createLexicalAnalyzerContext()); }
<MULTILINE_COMMENT>"*/"				{ EndMultilineCommentLexemeAction(createLexicalAnalyzerContext()); BEGIN(INITIAL); }
<MULTILINE_COMMENT>[[:space:]]+		{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<MULTILINE_COMMENT>[^*]+			{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<MULTILINE_COMMENT>.				{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }

"("									{ return ParenthesisLexemeAction(createLexicalAnalyzerContext()); }
")"									{ return ParenthesisLexemeAction(createLexicalAnalyzerContext()); }
":"                                 { return ColonPatternAction(createLexicalAnalyzerContext()); }
";"                                 { return SemicolonPatternAction(createLexicalAnalyzerContext()); }
","                                 { return CommaPatternAction(createLexicalAnalyzerContext()); }
"="                                 { return EqualPatternAction(createLexicalAnalyzerContext()); }

[[:space:]]+						{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }
.									{ return UnknownLexemeAction(createLexicalAnalyzerContext()); }

"automata"                          { return AutomataFunctionAction(createLexicalAnalyzerContext()); }
"automatan't"                       { return EndAutomataFunctionAction(createLexicalAnalyzerContext()); }

"rule"                              { return RuleFunctionAction(createLexicalAnalyzerContext()); }
"rulen't"                           { return EndRuleFunctionAction(createLexicalAnalyzerContext()); }

"grid"                              { return GridSpecificationAction(createLexicalAnalyzerContext()); }

"check"                             { return CheckLexemeAction(createLexicalAnalyzerContext()); }

{prop}                              { return PropertyPatternAction(createLexicalAnalyzerContext()); }

{color}                             { return ColorHandlerAction(createLexicalAnalyzerContext()); }
"true"                              { return BooleanPatternAction(createLexicalAnalyzerContext()); }
"false"                             { return BooleanPatternAction(createLexicalAnalyzerContext()); }
[[:digit:]]+						{ return IntegerLexemeAction(createLexicalAnalyzerContext()); }

%%

#include "FlexExport.h"
