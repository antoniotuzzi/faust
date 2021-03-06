/************************************************************************
 ************************************************************************
    FAUST compiler
	Copyright (C) 2003-2004 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 ************************************************************************
 ************************************************************************/

#include    <stdlib.h>
#include    <stdio.h>
#include    <string.h>
#include    "symbol.hh"
#include    "compatibility.hh"
#include    <iostream>
#include    <cstring>
#include    <assert.h>

using namespace std;

/**
 * Hash table used to store the symbols
 */
 
Symbol*	Symbol::gSymbolTable[kHashTableSize];


/**
 * Search the hash table for the symbol of name \p str or returns a new one.
 * \param str the name of the symbol
 * \return a symbol of name str
 */
  
Symbol* Symbol::get(const string& str)
{
	char 	buf[1024];
	int		i;
	int		n = (int)str.length();
	
	if (n>1023) n = 1023;
	for (i = 0; i < n; i++) { buf[i] = str[i]; }
	buf[i] = 0;
	
	return Symbol::get(buf);
}



/**
 * Search the hash table for the symbol of name \p str or returns a new one.
 * \param str the name of the symbol
 * \return a symbol of name str
 */ 

Symbol* Symbol::get(const char* str)
{
    unsigned int 			hsh  = calcHashKey(str);
    int 			bckt = hsh % kHashTableSize;
	Symbol*			item = gSymbolTable[bckt];

    while ( item && !item->equiv(hsh,str) ) item = item->fNext;
	Symbol* r = item ? item : gSymbolTable[bckt] = new Symbol(str, hsh, gSymbolTable[bckt]);
	return r;
}


/**
 * Static method that searches the symbol table for a string. 
 * \param str string to search 
 * \return true if the string is NOT in the table (it is a new string) 
 */

bool Symbol::isnew(const char* str)
{
    unsigned int 			hsh  = calcHashKey(str);
    int 			bckt = hsh % kHashTableSize;
	Symbol*			item = gSymbolTable[bckt];
	
    while ( item && !item->equiv(hsh,str) ) item = item->fNext;
	return item == 0;
}


/**
 * Creates a new symbol with a name obtained by concatenating the \p str prefix with a number in order to make it unique
 * \param str the prefix of the name
 * \return a symbol of name \p prefix++n 
 */

Symbol* Symbol::prefix (const char* str)
{
	char 	name[256];
    
    static map<const char*, unsigned int> gPrefixCounters;
	
	for (int n = 0; n<10000; n++) {
		snprintf(name, 256, "%s%d", str, gPrefixCounters[str]++);
		if (isnew(name)) return get(name);
	}
	assert(false);
	return get("UNIQUEOVERFLOW");
}	


/**
 * Check if the name of the symbol is equal to string \p str
 * This method is used by isnew() and make() when searching the hashtable 
 * for an existing symbol.
 *
 * \param hash the hash key of the string (used to speedup the comparison)
 * \param str the string to compare
 * \return \p true if the name of the symbol and \p str are the same
 */
 
bool Symbol::equiv (unsigned int hash, const char *str) const
{
	return (fHash == hash) && (strcmp(fName,str) == 0);
}



/**
 * Compute the 32-bits hash key of string \p str
 * \param str the string
 * \return a 32-bits hash key
 */

unsigned int Symbol::calcHashKey (const char* str)
{
    unsigned int h = 0;

    while (*str) h = (h << 1) ^ (h >> 20) ^ (*str++);
    return h;
}



/**
 * Constructs a symbol ready to be placed in the hash table. 
 * It makes a private copy of its name.
 * \param str the name of the symbol
 * \param hsh the hash key of the symbol
 * \param nxt a pointer to the next symbol in the hash table entry
 */

Symbol::Symbol(const char* str, unsigned int hsh, Symbol* nxt)
{
	int len = (int)strlen(str);
	
    fName = new char [len+1];
    memcpy(fName, str, len+1);
    fHash = hsh;
    fNext = nxt;
	fData = 0;
}

Symbol::~Symbol ()
{
	delete [] fName;
}

ostream& Symbol::print (ostream& fout) const 					///< print a symbol on a stream
{
	return fout << fName;
}
