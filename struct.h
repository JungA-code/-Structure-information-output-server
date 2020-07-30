#pragma once
#include <stdio.h>

typedef struct tag_st { 
	int num;
	char ch;
}basic;

struct contain {
	basic st;	
	int *p;
	long double ldar[128];
};
