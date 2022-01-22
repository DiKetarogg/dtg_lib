#pragma once
namespace dtg {
class Timer {
	public:
	using steady_clock = std::chrono::steady_clock;
	using time_point = typename std::chrono::time_point<steady_clock>;
	using seconds = std::chrono::seconds;
	using milliseconds = std::chrono::milliseconds;
	template<class... Ts>
	using duration = std::chrono::duration<Ts...>;

	time_point start, prev_start;
	duration<float, std::ratio<1, 1>> dur;

	public:
	Timer() = default;
	Timer(float dur):start(steady_clock::now()), dur(duration<float, std::ratio<1, 1>>(dur)){};
	void Start(float dur) {
		prev_start = start;
		start = steady_clock::now();
		this->dur = duration<float, std::ratio<1, 1>>(dur);
	}
	bool TimedOut() {
		return steady_clock::now() > start + dur;
	}
	float GetElapsed() {
		return duration<float, std::ratio<1, 1>>(steady_clock::now() - prev_start).count();
	}
};
}
