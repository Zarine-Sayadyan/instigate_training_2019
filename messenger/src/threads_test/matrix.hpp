#ifndef DATA_H
#define DATA_H

#define SIZE 5

/**
 * @file matrix.hpp
 * @brief Contains prototype for data, multiplier and adder class
 */

#include <threads/thread.hpp>
#include <threads/mutex.hpp>

#include <cassert>
#include <iostream>

///////////// Data //////////////
class data
{
public:
        data();
        ~data();
        void print(const char* name) const;
        void init_identity();
        void set_ready();
        void set_free();
        bool is_ready() const;
        void wait();
        void lock();
        void unlock();
        // getter, setter
        int get_matrix_el(int, int) const;
        void set_matrix_el(int, int, int);

private:
        threads::mutex m_mutex;
        int m_matrix[SIZE][SIZE];
        bool m_ready;
};

////////////// Adder //////////////

/**
 * @class adder
 * @brief is inharitanced thread class and added two matrixs.
 * */
class adder : public threads::thread
{
private:
	data* in1;
	data* in2;
	data* out;
public:

	/**
	*@fn adder       
	*@brief  two matrics addition.
	@param i 
	@brief first index
	@param j 
	@brief second index
	*/
	adder(data*, data*, data*);

	/**
	* @fn run
	* @brief virtual function's overloading.
	* */
        virtual void run();
};


////////////// Multiplay ///////////////

class multiplier : public threads::thread
{
private:
	data* in1;
	data* in2;
	data* out;
public:
	/**
	* @fn multiplier
	* @brief consturcot
	**/
        multiplier(data*, data*, data*);
	/**
	* @fn run
	* @brief virtual function's overloading.
	* */
        virtual void run();
};

#endif
