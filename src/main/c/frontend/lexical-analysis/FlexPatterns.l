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

%%

"/*"								{ BEGIN(MULTILINE_COMMENT); BeginMultilineCommentLexemeAction(createLexicalAnalyzerContext()); }
<MULTILINE_COMMENT>"*/"				{ EndMultilineCommentLexemeAction(createLexicalAnalyzerContext()); BEGIN(INITIAL); }
<MULTILINE_COMMENT>[[:space:]]+		{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<MULTILINE_COMMENT>[^*]+			{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }
<MULTILINE_COMMENT>.				{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }



"check"                          { return CheckLexemeAction(createLexicalAnalyzerContext()); }   

"("									{ return openParenthesisPatternAction(createLexicalAnalyzerContext()); }
")"									{ return closeParenthesisPatternAction(createLexicalAnalyzerContext()); }

[[:digit:]]+						{ return IntegerLexemeAction(createLexicalAnalyzerContext()); }

[[:space:]]+						{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }
.									{ return UnknownLexemeAction(createLexicalAnalyzerContext()); }

"automata" {return automataFunctionAction(createLexicalAnalyzerContext()); }
"automatan't" {return endAutomataFunctionAction(createLexicalAnalyzerContext()); }



"rule" { return beginRuleFuncionAction(createLexicalAnalyzerContext()); }
":" { return colonPatternAction(createLexicalAnalyzerContext()); }
";" { return semicolonPatternAction(createLexicalAnalyzerContext()); }
"rulen't" {return endRuleFunctionAction(createLexicalAnalyzerContext()); }

"color" { return colorSetupRuleAction(createLexicalAnalyzerContext()); }
{color} { return colorHandlerAction(createLexicalAnalyzerContext()); }
"," { return commaPatternAction(createLexicalAnalyzerContext()); }

"bgColor" { return bgColorSetupRuleAction(createLexicalAnalyzerContext()); }

"wrapping" { return wrappingSetupRuleAction(createLexicalAnalyzerContext()); }
"true" { return truePatternAction(createLexicalAnalyzerContext()); }
"false" { return falsePatternAction(createLexicalAnalyzerContext()); }
%%

#include "FlexExport.h"
