#pragma once

typedef struct _tagpos
{
	int x;
	int y;

	_tagpos&& operator+(const _tagpos& b);
	_tagpos&& operator-(const _tagpos& b);
	_tagpos&& operator-();
	_tagpos&& operator+=(const _tagpos& b);
	bool operator==(const _tagpos& b);
	bool operator!=(const _tagpos& b);
	bool operator==(_tagpos&& b);
	bool operator!=(_tagpos&& b);
	
} POS, *PPOS;