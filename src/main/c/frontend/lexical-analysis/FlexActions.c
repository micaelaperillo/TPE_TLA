#include "FlexActions.h"

/* MODULE INTERNAL STATE */

static Logger * _logger = NULL;
static boolean _logIgnoredLexemes = true;

void initializeFlexActionsModule() {
	_logIgnoredLexemes = getBooleanOrDefault("LOG_IGNORED_LEXEMES", _logIgnoredLexemes);
	_logger = createLogger("FlexActions");
}

void shutdownFlexActionsModule() {
	if (_logger != NULL) {
		destroyLogger(_logger);
	}
}

/* PRIVATE FUNCTIONS */

static void _logLexicalAnalyzerContext(const char * functionName, LexicalAnalyzerContext * lexicalAnalyzerContext);

/**
 * Logs a lexical-analyzer context in DEBUGGING level.
 */
static void _logLexicalAnalyzerContext(const char * functionName, LexicalAnalyzerContext * lexicalAnalyzerContext) {
	char * escapedLexeme = escape(lexicalAnalyzerContext->lexeme);
	logDebugging(_logger, "%s: %s (context = %d, length = %d, line = %d)",
		functionName,
		escapedLexeme,
		lexicalAnalyzerContext->currentContext,
		lexicalAnalyzerContext->length,
		lexicalAnalyzerContext->line);
	free(escapedLexeme);
}

/* PUBLIC FUNCTIONS */

void BeginMultilineCommentLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	if (_logIgnoredLexemes) {
		_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	}
}

void EndMultilineCommentLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	if (_logIgnoredLexemes) {
		_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	}
}

void IgnoredLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	if (_logIgnoredLexemes) {
		_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	}
}

Token ArithmeticOperatorLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token token;
	switch (lexicalAnalyzerContext->lexeme[0]) {
		case '-': token = SUB; break;
		case '*': token = MUL; break;
		case '/': token = DIV; break;
		case '+': token = ADD; break;
	}
	lexicalAnalyzerContext->semanticValue->token = token;
	return token;
}

Token IntegerLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	lexicalAnalyzerContext->semanticValue->integer = atoi(lexicalAnalyzerContext->lexeme);
	return INTEGER;
}

Token ParenthesisLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	Token token;
	switch (lexicalAnalyzerContext->lexeme[0]) {
		case '(': token = OPEN_PARENTHESIS; break;
		case ')': token = CLOSE_PARENTHESIS; break;
	}
	lexicalAnalyzerContext->semanticValue->token = token;
	return token;
}

Token UnknownLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	_logLexicalAnalyzerContext(__FUNCTION__, lexicalAnalyzerContext);
	return UNKNOWN;
}

Token checkLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {

}

Token openParenthesisLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	
}

Token closeParenthesisLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	
}

Token integerLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	
}

Token ignoredLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	
}

Token unknownLexemeAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	
}

Token automataFunctionAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	
}

Token colonPatternAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	
}

Token commaPatternAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	
}

Token semicolonPatternAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	
}

Token endAutomataFunctionAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	
}

Token ruleFunctionAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	
}

Token endRuleFunctionAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	
}

Token colorSetupAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	
}

Token colorHandlerAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	
}

Token bgColorSetupAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	
}

Token wrappingSetupAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	
}

Token truePatternAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	
}

Token falsePatternAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {
	
}

Token gridSpecificationAction(LexicalAnalyzerContext * lexicalAnalyzerContext) {

}