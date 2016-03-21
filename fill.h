/** @file fill.h*/

#ifndef __FILL_H__
#define __FILL_H__

#include <vector>
#ifdef INCLUDE_HEADER
	#include INCLUDE_HEADER
#else
	#include "utility.h"
#endif

using std::vector;
using std::string;

/*****************************************************************************/

const char PIXEL_BORDER	=	'#';
const char PIXEL_BLANK	=	'-';
const char PIXEL_FILLED	=	'+';
const char PIXEL_SEED		=	'o';

/*****************************************************************************/

/**
 * Class holding the edge map and performing operations above it.
 */
class EdgeMap
{
public:
	/**
	 * Default constructor.
	 */
	EdgeMap() { m_correct = false; }

	/**
	 * Load edge map from a file.
	 *
	 * @param [in]  path         file path to the edge map file
	 * @return                   error code
	 */
	Error Load(const string &path);

	/**
	 * Fill edge map from the seed position.
	 *
	 * @param [out] area         number of filled pixels
	 * @return                   error code
	 */
	Error Fill(ushort &area);

	/**
	 * Print edge map to the console.
	 *
	 * @return                   nothing
	 */
	Error Print() const;

	/**
	 * Reports whether the edge map is correctly loaded.
	 *
	 * @return                   true if the map is correctly loaded, false otherwise
	 */
	bool IsValid() const { return m_correct; }

private:
	/**
	 * Converts 2D coordinates to 1D array index
	 *
	 * @param [in] x             x-coordinate
	 * @param [in] y             y-coordinate
	 * @return                   1D array index computed from x and y
	 */
	inline ushort getIndex(ushort x, ushort y) const;

private:
	Point m_mapSize;		/**< size of the loaded map. */
	Point m_seed;			/**< position of the seed. */
	vector<char> m_edgeMap;		/**< edge map 1D array. */
	bool m_correct;
};

/*****************************************************************************/

#endif
