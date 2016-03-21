#include "utility.h"

/*****************************************************************************/

const char* Error::m_errorStrings[] = {"",
	"Pouziti: fill <path>",
	"Chyba pri nacitani souboru s hranici!",
	"Neplatny znak v souboru s hranici!",
	"Soubor neobsahuje pravouhle pole!",
	"V souboru s hranici neni zadane seminko!",
	"V souboru s hranici muze byt pouze jedno seminko!",
	"Mapa hran nebyla nactena.\nNeni mozno s ni pracovat!",
	"Algoritmus se dostal mimo oblast vymezenou mapou hran.\nChybny souboru s hranici nebo spatna poloha seminka!",
	"Nejedna se o algoritmus radkoveho seminkoveho vyplnovani!"};

ostream& operator<<(ostream& stream, const Error& err)
{
	stream << Error::m_errorStrings[err.m_error];
	return stream;
}

/*****************************************************************************/