#pragma once

typedef struct _tagpos
{
	int x;
	int y;

	static _tagpos zero;
	static _tagpos up;
	static _tagpos down;
	static _tagpos left;
	static _tagpos right;

	_tagpos&& operator+(const _tagpos& b);
	_tagpos&& operator-(const _tagpos& b);
	_tagpos&& operator-();
	_tagpos&& operator+=(const _tagpos& b);
	bool operator==(const _tagpos& b);
	bool operator!=(const _tagpos& b);
	bool operator==(_tagpos&& b);
	bool operator!=(_tagpos&& b);
	
} POS, *PPOS;