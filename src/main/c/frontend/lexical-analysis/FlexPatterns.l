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

"("									{ return ParenthesisLexemeAction(createLexicalAnalyzerContext()); }
")"									{ return ParenthesisLexemeAction(createLexicalAnalyzerContext()); }
":"                                 { return ColonPatternAction(createLexicalAnalyzerContext()); }
";"                                 { return SemicolonPatternAction(createLexicalAnalyzerContext()); }
","                                 { return CommaPatternAction(createLexicalAnalyzerContext()); }

[[:digit:]]+						{ return IntegerLexemeAction(createLexicalAnalyzerContext()); }

[[:space:]]+						{ IgnoredLexemeAction(createLexicalAnalyzerContext()); }
.									{ return UnknownLexemeAction(createLexicalAnalyzerContext()); }

"automata"                          { return AutomataFunctionAction(createLexicalAnalyzerContext()); }
"automatan't"                       { return EndAutomataFunctionAction(createLexicalAnalyzerContext()); }

"rule"                              { return RuleFunctionAction(createLexicalAnalyzerContext()); }
"rulen't"                           { return EndRuleFunctionAction(createLexicalAnalyzerContext()); }

"grid"                              { return GridSpecificationAction(createLexicalAnalyzerContext()); }

"check"                             { return CheckLexemeAction(createLexicalAnalyzerContext()); }

"color"                             { return ColorSetupAction(createLexicalAnalyzerContext()); }
{color}                             { return ColorHandlerAction(createLexicalAnalyzerContext()); }

"bgColor"                           { return BgColorSetupAction(createLexicalAnalyzerContext()); }

"wrapping"                          { return WrappingSetupAction(createLexicalAnalyzerContext()); }
"true"                              { return BooleanPatternAction(createLexicalAnalyzerContext()); }
"false"                             { return BooleanPatternAction(createLexicalAnalyzerContext()); }

%%

#include "FlexExport.h"
