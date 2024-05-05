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



"check"                          { return checkLexemeAction(createLexicalAnalyzerContext()); }   

"("									{ return openParenthesisPatternAction(createLexicalAnalyzerContext()); }
")"									{ return closeParenthesisPatternAction(createLexicalAnalyzerContext()); }

[[:digit:]]+						{ return integerLexemeAction(createLexicalAnalyzerContext()); }

[[:space:]]+						{ ignoredLexemeAction(createLexicalAnalyzerContext()); }
.									{ return unknownLexemeAction(createLexicalAnalyzerContext()); }

"automata" {return automataFunctionAction(createLexicalAnalyzerContext()); }
"automatan't" {return endAutomataFunctionAction(createLexicalAnalyzerContext()); }



"rule" { return ruleFuncionAction(createLexicalAnalyzerContext()); }
":" { return colonPatternAction(createLexicalAnalyzerContext()); }
";" { return semicolonPatternAction(createLexicalAnalyzerContext()); }
"rulen't" {return endRuleFunctionAction(createLexicalAnalyzerContext()); }

"color" { return colorSetupAction(createLexicalAnalyzerContext()); }
{color} { return colorHandlerAction(createLexicalAnalyzerContext()); }
"," { return commaPatternAction(createLexicalAnalyzerContext()); }

"bgColor" { return bgColorSetupAction(createLexicalAnalyzerContext()); }

"wrapping" { return wrappingSetupAction(createLexicalAnalyzerContext()); }
"true" { return truePatternAction(createLexicalAnalyzerContext()); }
"false" { return falsePatternAction(createLexicalAnalyzerContext()); }
%%

#include "FlexExport.h"
