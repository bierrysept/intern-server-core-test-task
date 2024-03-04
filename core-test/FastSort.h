#pragma once
#include <exception>
#include <list>

namespace {
	template <typename T>
	T selectPivot(T first, T middle, T last)
	{
		if (first < middle) {
			if (middle < last) {
				return middle;
			}
			else {
				if (first < last) {
					return last;
				}
				else {
					return first;
				}
			}
		}
		else {
			if (middle < last) {
				if (first < last) {
					return first;
				}
				else {
					return last;
				}
			}
			else {
				return middle;
			}
		}
	}
	
}


namespace FastSort {
	template <typename T>
	std::list<T> sort(std::list<T> array) {

		if (array.size() < 2)
			return array;

		T first = array.front();
		T last = array.back();
		std::list<T>::iterator middleIterator = array.begin();
		std::advance(middleIterator, (array.size() / 2));
		T middle = *middleIterator;
		T pivot = selectPivot<T>(first, middle, last);

		std::list<T> firsts = std::list<T>();
		std::list<T> middles = std::list<T>();
		std::list<T> lasts = std::list<T>();

		for (T &it : array) {
			if (it == pivot) {
				middles.push_back(it);
			} else if(it < pivot) {
				firsts.push_back(it);
			}
			else {
				lasts.push_back(it);
			}
		}
		firsts = sort(firsts);
		lasts = sort(lasts);

		std::list<T> finals = firsts;

		finals.insert(finals.end(), middles.begin(), middles.end());
		finals.insert(finals.end(), lasts.begin(), lasts.end());

		return finals;
	}
}