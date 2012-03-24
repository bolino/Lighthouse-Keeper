#pragma once

class Timer {
	private:	
		
		int startTicks;
		bool started;
	
	public:
		Timer();
		~Timer();
		void start();
		void stop();
		int getTicks();
		bool isStarted();
};
