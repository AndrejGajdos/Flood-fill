/** @file utility.h*/

#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <iostream>
#include <fstream>
#include <stack>

using std::cout;
using std::cerr;
using std::endl;
using std::ostream;
using std::ifstream;
using std::istringstream;
using std::stack;

/*****************************************************************************/

typedef unsigned short ushort;
typedef unsigned long ulong;

/*****************************************************************************/

class Error
{
public:
	/**
	 * Named defined error values.
	 */
	enum Err {E_OK, E_USAGE, E_CANTOPEN, E_INVALIDCHAR, E_SIZE, E_NOSEED, E_MORESEEDS, E_NOTLOADED, E_OUTOFMAP, E_NOTSCANLINE};

	friend ostream& operator<<(ostream& stream, const Error& err);

	/**
	 * Default constructor.
	 */
	Error() { m_error = E_OK; }

	/**
	 * Constructor.
	 * @param [in]  err          new error code
	 */
	Error(Err err) { m_error = err; }

	/**
	 * Returns the currently set error.
	 *
	 * @return                   error code
	 */
	Err getError() const { return m_error; }
	
	/**
	 * Set the current error.
	 *
	 * @param [in]  err          new error code
	 * @return                   nothing
	 */
	void setError(Err err) { m_error = err; }

	/**
	 * Check if an error occured.
	 *
	 * @return                   returns true if error occures
	 */
	operator bool() const { return m_error == E_OK; }

private:
	Err m_error; /**< error code */
	static const char* m_errorStrings[]; /**< error messages */
};

/**
 * Write the error into the stream stream.
 *
 * @param [in]  stream       the stream to write into
 * @return                   the modified stream
 */
ostream& operator<<(ostream& stream, const Error& err);

/*****************************************************************************/

/**
 * Class for saving size and point data in 2D
 */
class Point
{
public:
	/**
	 * Default constructor.
	 */
	Point() { m_x = 0; m_y = 0; }

	/**
	 * Constructor.
	 * @param [in]  x						x-coordinate of the point
	 * @param [in]  y						y-coordinate of the point
	 */
	Point(ushort x, ushort y) { m_x = x; m_y = y; }

	/**
	 * Returns the x-coordinate.
	 *
	 * @return                   x-coordinate of the point
	 */
	ushort getX() const { return m_x; }

	/**
	 * Sets the x-coordinate.
	 *
	 * @return                   nothing
	 */
	void setX(ushort x) { m_x = x; }

	/**
	 * Returns the y-coordinate.
	 *
	 * @return                   y-coordinate of the point
	 */
	ushort getY() const { return m_y; }

	/**
	 * Sets the y-coordinate.
	 *
	 * @return                   nothing
	 */
	void setY(ushort y) { m_y = y; }

private:
	ushort m_x; /**< x-coordinate */
	ushort m_y; /**< y-coordinate */
};

/*****************************************************************************/

/**
 * Class implementing a dynamic data structure for point.
 */
class DynamicData
{
public:
	/**
	 * Checks if the dynamic data structure is empty.
	 *
	 * @param [in]  stc          name of the data structure
	 * @return                   true if stc is empty, false otherwise
	 */
	bool empty() const { return stc.empty(); }

	/**
	 * Pushes data into the dynamic data structure.
	 *
	 * @param [in]  stc          name of the data structure
	 * @param [in]  item         data to save
	 * @return                   nothing
	 */
	void push(Point item) { stc.push(item); }

	/**
	 * Pops data from the dynamic data structure.
	 *
	 * @param [in]  stc          name of the data structure
	 * @param [in]  item         data to load
	 * @return                   nothing
	 */
	void pop(Point &item) { item = stc.top(); stc.pop(); }

private:
	stack<Point> stc; /**< this class delegates work to stack data structure from STL */
};

/*****************************************************************************/

#endif
