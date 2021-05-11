
#include <iostream>
#include <thread>
#include <deque>
#include <functional>
#include <chrono>
#include "event.h"

using namespace std::chrono_literals;

class Timer {

	std::thread m_thread;
	manual_event m_event;
	std::chrono::nanoseconds m_tick;
	unsigned long long m_ticks = 0;

	struct internal_proc
	{
		std::function <bool(void)> proc;
		unsigned long long ticks;
		mutable unsigned long long elapsed;
		std::shared_ptr<manual_event> evt;
	};
	std::deque<internal_proc> event_queue;
public:
	template<typename T>
	Timer(T&& tick) :m_tick(std::chrono::duration_cast<std::chrono::nanoseconds>(tick)), m_thread([this]() {
		//	std::cout << "Checking what is going on\n";

		auto realTimeStart = std::chrono::high_resolution_clock::now();
		std::chrono::nanoseconds drift{ 0 };
		//	std::cout << "Checking what is going ond\n";
		while (!m_event.wait_for(1ms - drift)) {

			++m_ticks;
			auto it = std::begin(event_queue);
			auto end = std::end(event_queue);

			while (it != end)
			{
				auto& event_obj = *it;
				++event_obj.elapsed;
				if (event_obj.elapsed == event_obj.ticks)
				{
					auto funcCalResult = event_obj.proc();
					if (funcCalResult) {
						event_queue.erase(it++);
						continue;
					}
					else {
						event_obj.elapsed = 0;
					}
				}
				++it;
			}

			auto realTimeEnd = std::chrono::high_resolution_clock::now();
			auto realExecTime = std::chrono::duration_cast<std::chrono::nanoseconds>(realTimeEnd - realTimeStart);
			auto progExecTime = std::chrono::duration_cast<std::chrono::nanoseconds>(1ms * m_ticks);
			drift = realExecTime - progExecTime;
		}
		}) {

	}

	template<typename T, typename F, typename... Args>
	auto setInterval(T&& interval, F  f, Args&&... args) {

		//	std::cout << "Check\n";
		auto manEvtObject = std::make_shared<manual_event>();
		auto proc = [=]() {
			if (manEvtObject->wait_for(std::chrono::seconds(0))) return true;
			f(args...);
			return false;
		};


		event_queue.push_front({ proc,
			static_cast<unsigned long long>(std::chrono::duration_cast<std::chrono::nanoseconds>(interval).count() / m_tick.count()),
			0,
			manEvtObject
			});
		//	m_thread.join();
		//std::this_thread::sleep_for(std::chrono::seconds(10));
		return manEvtObject;

	}
	~Timer() {

		m_event.signal();
		m_thread.join();
	}


};






