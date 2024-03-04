#include "pch.h"
#include "CppUnitTest.h"
#include "../core-test/OddChecker.cpp"
#include "../core-test/MyFIFO.h"
#include "../core-test/FastSort.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CoreTest
{
	TEST_CLASS(CoreTest)
	{
	public:
		TEST_METHOD(checkOdd)
		{
			Assert::IsTrue(OddChecker::OddChecker::odd(1), L"1 is odd");
			Assert::IsFalse(OddChecker::OddChecker::odd(2), L"2 is not odd");
			Assert::IsTrue(OddChecker::OddChecker::odd(3), L"3 is odd");
			Assert::IsFalse(OddChecker::OddChecker::odd(4), L"4 is not odd");
			Assert::IsTrue(OddChecker::OddChecker::odd(5), L"5 is odd");
			Assert::IsFalse(OddChecker::OddChecker::odd(6), L"6 is not odd");

			Assert::IsFalse(OddChecker::OddChecker::even(1), L"1 is not even");
			Assert::IsTrue(OddChecker::OddChecker::even(2), L"2 is even");
			Assert::IsFalse(OddChecker::OddChecker::even(3), L"3 is not even");
			Assert::IsTrue(OddChecker::OddChecker::even(4), L"4 is even");
			Assert::IsFalse(OddChecker::OddChecker::even(5), L"5 is not even");
			Assert::IsTrue(OddChecker::OddChecker::even(6), L"6 is odd");
		}

		TEST_METHOD(checkArraiedFifo)
		{
			MyFIFO::FIFOArrayed<int, 10> fifoArraied = MyFIFO::FIFOArrayed<int, 10>();
			Assert::IsTrue(fifoArraied.isEmpty(), L"Created FIFO is Empty");
			
			fifoArraied.push(0);
			Assert::IsFalse(fifoArraied.isEmpty(), L"After add item FIFO is not empty");

			Assert::AreEqual(0, fifoArraied.first(), L"After add 0 to FIFO, it has only 0ne element - 0");

			fifoArraied.push(1);
			Assert::AreEqual(0, fifoArraied.first(), L"After add 1 to FIFO, it has on top - 0");

			fifoArraied.pop();
			Assert::AreEqual(1, fifoArraied.first(), L"After pop 0 from FIFO, next is 1");

			try {
				fifoArraied.push(1);
				fifoArraied.push(2);
				fifoArraied.push(3);
				fifoArraied.push(4);
				fifoArraied.push(5);
				fifoArraied.push(6);
				fifoArraied.push(7);
				fifoArraied.push(8);
				fifoArraied.push(9);
				Assert::Fail(L"Did not trown on full queue");
			}
			catch (MyFIFO::ListFull) {

			}

			try {
				fifoArraied.pop();
				fifoArraied.pop();
				fifoArraied.pop();
				fifoArraied.pop();
				fifoArraied.pop();
				fifoArraied.pop();
				fifoArraied.pop();
				fifoArraied.pop();
				fifoArraied.pop();
				fifoArraied.pop();
				Assert::Fail(L"Did not trown on empty queue");
			}
			catch (MyFIFO::ListEmpty) {

			}
		}

		TEST_METHOD(checkListFifo)
		{
			MyFIFO::FIFOListed<int> fifoListed = MyFIFO::FIFOListed<int>();
			Assert::IsTrue(fifoListed.isEmpty(), L"Created FIFO is Empty");

			fifoListed.push(0);
			Assert::IsFalse(fifoListed.isEmpty(), L"After add item FIFO is not empty");

			Assert::AreEqual(0, fifoListed.first(), L"After add 0 to FIFO, it has only 0ne element - 0");

			fifoListed.push(1);
			Assert::AreEqual(0, fifoListed.first(), L"After add 1 to FIFO, it has on top - 0");

			fifoListed.pop();
			Assert::AreEqual(1, fifoListed.first(), L"After pop 0 from FIFO, next is 1");

			try {
				fifoListed.push(1);
				fifoListed.push(2);
				fifoListed.push(3);
				fifoListed.push(4);
				fifoListed.push(5);
				fifoListed.push(6);
				fifoListed.push(7);
				fifoListed.push(8);
				fifoListed.push(9);
				fifoListed.pop();
				fifoListed.pop();
				fifoListed.pop();
				fifoListed.pop();
				fifoListed.pop();
				fifoListed.pop();
				fifoListed.pop();
				fifoListed.pop();
				fifoListed.pop();
				fifoListed.pop();
				fifoListed.pop();
				Assert::Fail(L"Did not trown on empty queue");
			}
			catch (MyFIFO::ListEmpty) {

			}
		}

		TEST_METHOD(testDepthListed) {
			MyFIFO::FIFOListed<int> fifoListed = MyFIFO::FIFOListed<int>();
			fifoListed.push(1);
			fifoListed.push(2);
			fifoListed.push(3);
			fifoListed.push(4);
			fifoListed.push(5);
			fifoListed.push(6);
			fifoListed.push(7);
			fifoListed.push(8);
			fifoListed.push(9);

			Assert::AreEqual(1, fifoListed.first(0), L"first(0) must be 1");
			Assert::AreEqual(2, fifoListed.first(1), L"first(1) must be 2");
			Assert::AreEqual(3, fifoListed.first(2), L"first(2) must be 3");
			Assert::AreEqual(4, fifoListed.first(3), L"first(3) must be 4");
			Assert::AreEqual(5, fifoListed.first(4), L"first(4) must be 5");
			Assert::AreEqual(6, fifoListed.first(5), L"first(5) must be 6");

			Assert::AreEqual(9, fifoListed.last(0), L"last(0) must be 9");
			Assert::AreEqual(8, fifoListed.last(1), L"last(1) must be 8");
			Assert::AreEqual(7, fifoListed.last(2), L"last(2) must be 7");
			Assert::AreEqual(6, fifoListed.last(3), L"last(3) must be 6");
			Assert::AreEqual(5, fifoListed.last(4), L"last(4) must be 5");
		}


		TEST_METHOD(testFastSort) {
			std::list<char> list1 = {0};
			Assert::IsTrue(list1 == FastSort::sort(list1));

			list1 = { 0, 1 };
			Assert::IsTrue(list1 == FastSort::sort(list1));

			list1 = { 1, 0 };
			std::list<char> list2 = { 0, 1 };
			Assert::IsTrue(list2 == FastSort::sort(list1));
		}
	};
}
